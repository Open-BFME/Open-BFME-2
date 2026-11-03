# EntEnragedUpdate scan merge: class-gate refusal

Base: `10ead20037`. The declaration prerequisite is committed; the merge
described here was reverted before committing. No source-file reduction or
census gain is claimed.

Reproducer at that base:

1. `python3 tools/tu_skeleton.py --merge Code/GameEngine/Source/Common/EntEnragedUpdate.cpp`
2. `./build.sh Code/GameEngine/Source/Common/EntEnragedUpdate.cpp`
3. `python3 tools/class_gate.py --staged`

The supported merger accepts the seed and EntEnragedUpdateScan.cpp, reports
25 planned rows, and repoints 11 function rows plus the source columns of the
TU map and one header-queue entry. The resulting build verifies 26/26 ledger
rows, including the existing folded row. Frozen-source and CSV checks pass.
The link preview predicts LINKS 524 -> 866 authored bytes in the seed,
accounting for the scan's existing 342 bytes; this is not a census increase.

The required class gate returns 1:

```
Code/GameEngine/Source/Common/EntEnragedUpdate.cpp: declares its own `Rva000421C8`; include Code/GameEngine/Include/GameLogic/PartitionFilter.h instead
```

The existing global-scope Rva000421C8 declaration, including its inline empty
virtual destructor, transfers unchanged from the deleted scan donor; the
number of private copies stays one. `class_gate.py` supports deleted-donor
move credit but conservatively refuses that credit for any non-include
preprocessor directive anywhere in the receiving unit. The seed already has
`#define LogicFramesPerSecond BfmeLogicFramesPerSecond`, which does not occur
in the transferred filter declaration. This is the apparent false reject;
neither the directive nor the gate was changed to get past it.

`tu_ownership.py --staged --shadow` also reports B1 for the transferred private
filter declaration, as a shadow finding. No alias, pin or hatch was changed.
The scan's existing failed PartitionFilter header-adoption queue entry remains
at its original source after the merge was reverted. Adopting the shared
header still needs separate byte evidence because its destructor is only
declared, whereas this donor requires its inline destructor definition.

Remaining merge donors are unchanged: the family deleting-dtor donor lacks a
compatible EmitVtableTag constructor; the update donor needs combined Object
and derived-data declarations; the module-data destructor donor fails bytes.
Next step: tooling lane reproduces the conservative move-credit refusal with
regression coverage, or header adoption independently reconciles the filter
destructor. Retry the supported merge afterward. Full affected-consumer
verification and scheduled-census confirmation remain pending; the reverted
merge was not submitted as a linking improvement.
