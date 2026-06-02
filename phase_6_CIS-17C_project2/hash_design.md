# hash_design.md

_Phase 6 (CIS-17C Project 2) hashing rationale. Companion document to the `std::hash<Card>` and `std::hash<CardClr>` specializations in `Card.h`._

## What we are hashing

The UNO deck holds 65 distinct `Card` values: five `CardClr` enumerators (`RED`, `BLUE`, `YELLOW`, `GREEN`, `WILD`) crossed with thirteen `CardSuit` enumerators (`ZERO` through `NINE`, `SKIP`, `DRAW_TWO`, `DRAW_FOUR`). Two cards compare equal iff both fields match. The hash function therefore needs to map the pair `(color, suit)` to a single `size_t` value.

The first consumer is the legal-plays cache, which Step 03 migrates from `set<Card>` to `unordered_set<Card>`. The second consumer is the hand-rolled `HashTable<string,Scores>` in Step 04, which uses a different (string-keyed) hash; this file scopes only to the two `Card.h` specializations.

## Why BKDR with seed 131

BKDR is the standard multiplicative-shift pattern: start the accumulator at zero, and for each field, multiply the accumulator by the seed and add the field's integer value. With seed 131 and two fields, the closed form is `131 * color + suit`. Seed 131 is the classic value used in Brian Kernighan and Dennis Ritchie's `The C Programming Language` for string hashing, picked because it is prime, not a power of two, and small enough to keep intermediate products inside a 32-bit register on legacy hardware. The same properties carry over: the multiplier distributes neighboring inputs into widely separated bucket positions without overflow on any platform the project targets.

We picked BKDR over `boost::hash_combine`-style XOR-and-shift because the input space here is small enough that a closed-form analysis is possible and BKDR produces zero collisions across all 65 cards (proof below). A hash function this regular is also easier to reason about under `-Wall` and easier to point at during the writeup.

## Why not plain XOR

Plain XOR of the two field values, `hash = color ^ suit`, collides aggressively. Both fields are small integers starting at zero, so any pair where `color == suit` hashes to zero. `RED == ZERO`, `BLUE == ONE`, `YELLOW == TWO`, `GREEN == THREE`, and `WILD == FOUR` all map to the same bucket. That is five guaranteed collisions on a 65-card deck before any input variance enters. XOR also commutes, so `(RED, ONE)` and `(BLUE, ZERO)` collide. BKDR's asymmetric `131 *` factor breaks both pathologies.

## Distribution analysis

With BKDR seed 131 applied to `(color, suit)` where `color` is in `[0, 4]` and `suit` is in `[0, 12]`:

| color | hash range | values |
|---|---|---|
| `RED` (0) | `[0, 12]` | 0 through 12 |
| `BLUE` (1) | `[131, 143]` | 131 through 143 |
| `YELLOW` (2) | `[262, 274]` | 262 through 274 |
| `GREEN` (3) | `[393, 405]` | 393 through 405 |
| `WILD` (4) | `[524, 536]` | 524 through 536 |

Every one of the 65 valid `(color, suit)` pairs gets a unique value in `[0, 536]`. Zero collisions across the entire deck. The output range is tiny relative to a 64-bit `size_t`, but the standard library bucket index is computed by the unordered container itself (typically `hash(k) % bucket_count`), so an output range of a few hundred is fine as long as the values within that range are well separated, which they are.

For `CardClr` alone the specialization just returns the enumerator value cast to `size_t`. The five enumerators are 0 through 4. The mapping is trivially perfect; the specialization exists so that `unordered_map<CardClr,int>` (the Step 04 retarget of the color-tally `map`) does not need a custom transparent comparator.

## Why we open `namespace std`

The project's house style forbids `std::` prefixes anywhere outside of header includes. Template specializations of `std::hash` must live inside `namespace std` regardless of house style; this is one of the few cases where the standard library mandates the opening. The specialization block in `Card.h:49-71` is the smallest legal opening of `namespace std` that satisfies the rule, contains exactly the two specializations, and closes immediately. No other declarations leak into `std`.

## Files

- `phase_6_CIS-17C_project2/Card.h:46-71`: the specialization block.
- `phase_6_CIS-17C_project2/hash_design.md`: this file.

## Future references

Step 03 (`migrate_set`) consumes `std::hash<Card>` via `unordered_set<Card>`. Step 04 (`hash_table`) writes a hand-rolled BKDR over `string` for the leaderboard `HashTable<string,Scores>`; the seed value is shared (131) so the writeup can point at one rationale section rather than two. Step 13 (`pseudo_update`) records the hash signatures in `pseudo_code.cpp`.
