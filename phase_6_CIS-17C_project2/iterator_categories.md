# Iterator categories per container — Phase 6 v6.0

One row per live container in `unoV6.0.cpp`. The rubric asks for a
*description* of the iterator each container exposes, not full category
coverage; the table is the form the writeup PDF embeds and the Notion
Checkoff Sheet mirrors.

| Container | Iterator category | Operations actually used | Call sites |
|---|---|---|---|
| `list<Card> hand` (member of `Player`) | **Bidirectional** | `begin`, `end`, `++`, `--`, `*`, `->`, `next(it, n)` (`O(n)`), `erase(it)` | `Player.h:20`; walked in `usrInt` display loop; indexed via `next(begin, choice)` in `play`; scanned in `npcTrn` first-fit loop; sorted via member `sort` in `srtHnd`; counted via `count_if` in `usrInt` |
| `unordered_set<Card> legal` (built per player turn) | **Forward** (const) | `begin`, `end`, `insert`, `find` (`O(1)` average via `std::hash<Card>`) | constructed by `legalPlays`; consumed by `count_if` predicate and by `play` validation. Migrated from `set<Card>` once `std::hash<Card>` landed (BKDR seed=131); zero collisions on the 65-card deck, so the average bound is tight in practice |
| `map<string, Scores> scores` (score lookup) | **Bidirectional** | `begin`, `end`, `insert`, `find`, dereference of `pair<const K, V>` | `loadScoreMap`, `readScrs`, `updtScr` (`:779–856`); walked via `for_each` lambda in `readScrs` (`:873–880`) |
| `map<CardClr, int> tally` (NPC color picker) | **Bidirectional** (const on walk) | `begin`, `end`, `operator[]` (value-init on missing key), `++`, dereference of `pair<const K, V>` | built and walked entirely inside `pickClr` (`:613–633`); consumers at `:666`, `:722` |
| `stack<Card> discard` (active card / pile) | **None** (adaptor) | `push`, `pop`, `top`, `empty` | declared at `:133`; threaded through `plyrTrn` / `npcTrn` / `play` / `takeTurn` |
| `queue<Card> deck` (draw pile) | **None** (adaptor) | `push`, `pop`, `front`, `empty` | declared at `:131`; populated in `initDeck` (`:226–272`); drained one card at a time by `draw` (`:275`) |

## Observations the rubric grades

- **Bidirectional still dominates.** Three of six live containers expose
  bidirectional iterators. `list` and both `map` instances satisfy the
  same iterator contract: `++` and `--` work, arithmetic (`+ n`, `- n`,
  `[]`) does not. `unordered_set` is the one forward-only container; it
  only walks the open chains in one direction, so `--` is not available.
- **`stack` and `queue` expose no iterators.** Both are STL adaptors
  layered over an underlying sequence container; the adaptation hides
  the iteration interface deliberately. This counts as a description in
  its own right, not a coverage gap.
- **Random-access is not exercised** in Phase 5 active code. Phase 4
  used `vector<Card> hand`, which gave random-access iterators, but the
  lecture-rubric ban on vectors removed the only random-access call
  site. The deck-init `Card pool[100]` array does decay to a
  random-access iterator pair for `shuffle` (v5.1 Step 01); the
  `pool` is not itself a container so it does not appear in this
  table. The honest framing is: random-access is touched once via a
  C array, never via an STL container.
- **The "no `auto`" rule** (per `.claude/context/conventions.md`)
  shows up in every walk: iterator types are spelled out longhand
  (`map<string, Scores>::iterator`, `list<Card>::const_iterator`),
  which is what makes the iterator-category claim above directly
  verifiable from the source.
- **Algorithm/iterator pairing** is the rubric-worthy observation:
  `list::sort` is the member algorithm because `std::sort` requires
  random-access; `shuffle` is the free algorithm because the deck-init
  array gives random-access via pointer decay; `count_if` and
  `for_each` accept any forward-or-better iterator, which is why both
  drop straight onto `list<Card>` and `map<string, Scores>` without
  intermediate adaptation.
