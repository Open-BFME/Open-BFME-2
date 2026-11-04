# PathfinderPosGoalManager constructor merge: definition-order blocker

Inspected revision: `3d7a923798`. Donor: `Code/Libraries/Source/WWVegas/WWLib/Rva004DD7E3Ctor.cpp`.
Destination: `Code/GameEngine/Source/GameLogic/Object/PathfinderPosGoalManager.cpp`.

The current in-memory TU map approves the donor at RVA 0x004DD7E3 for this provisional TU. The evidence planner retains alternate Pathfinder/AI paths as hints; no map changes are proposed. Five mixed donors stay outside this merge.

`tu_skeleton.py --merge <destination> --dry-run` rejects the sole clean donor with `bytes`. The link guard recognizes both files as census-linked; it does not accept a byte-failing composition.

Target facts: the outer constructor is 39 bytes, keeps this in ESI with push/pop, and calls member constructor RVA 0x004DD7C4 three times. The member constructor is 31 bytes and does not modify EDX.

Compiled observation: the merged outer constructor is 37 bytes and keeps this in EDX, while preserving the three direct calls. Adding noinline to the member constructor leaves this unchanged. That annotation passes all 15 destination rows, the literal checks and the frozen-file check, but does not repair the merge. Moving the outer body into its class with noinline fails the standalone build because VC7.1 emits no symbol for that unreferenced inline definition. Both changes were reverted.

Inference: visibility of the member definition before the caller allows VC7.1 to exploit its register usage. A useful next check is legitimate definition-order control that emits the outer body before the member body; no compiler gate, hatch, alias or map workaround was added. No linked-byte or source-file reduction is claimed.
