# Phase 6 Concept Flowcharts

Five concept diagrams, one per Phase 6 algorithmic concept. The `.mmd`
files are Mermaid source; render to PNG with:

```bash
cd phase_6_CIS-17C_project2/flowcharts
npx -p @mermaid-js/mermaid-cli mmdc -i effect_chain.mmd    -o effect_chain.png    -t default -b white -w 1600
npx -p @mermaid-js/mermaid-cli mmdc -i merge_vs_quick.mmd  -o merge_vs_quick.png  -t default -b white -w 1600
npx -p @mermaid-js/mermaid-cli mmdc -i hash_lookup.mmd     -o hash_lookup.png     -t default -b white -w 1600
npx -p @mermaid-js/mermaid-cli mmdc -i score_bst.mmd       -o score_bst.png       -t default -b white -w 1600
npx -p @mermaid-js/mermaid-cli mmdc -i hand_graph.mmd      -o hand_graph.png      -t default -b white -w 1600
```

## Contents

| File | Concept | Rubric anchor |
|---|---|---|
| `effect_chain.mmd` | Recursive `resolveEffect` with three base conditions and one recursion site | Recursion + chained-effect resolver |
| `merge_vs_quick.mmd` | `mrgSort` halving versus `qkSort` Hoare partition recursion shape | Recursive sorts |
| `hash_lookup.mmd` | `HashTable<V>` BKDR hash, bucket-chain walk, insert / find lifecycle | Hand-written hashing |
| `score_bst.mmd` | `ScoreBST` insertion then in-order recursive walk for the leaderboard | Tree concept |
| `hand_graph.mmd` | `HandGraph` adjacency build and `largestCompAfter` NPC scoring | Graph + BFS scoring |

## Notes

- The master V6.0 architecture flowchart remains a single wide `.drawio` page exported to PDF, mirroring the V4.3 and V5.2 cadence. The five concept insets here live alongside it as standalone PNGs and embed into the writeup at the relevant section anchors.
- The Mermaid sources use only the `flowchart` directive and built-in node shapes so they render with stock `mmdc` (no plugins, no theme files).
