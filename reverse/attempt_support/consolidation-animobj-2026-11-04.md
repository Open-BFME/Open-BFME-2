# animobj.cpp consolidation trial (2026-11-04)

Allocated destination: `Code/Libraries/Source/WWVegas/WW3D2/animobj.cpp`; `consolidation_queue.py --check-tu` passed. A fresh WW3D2-scoped planner and its `--check` passed. The plan had 46 approved rows, three pull donors and no mixed or refused files.

The merge dry run accepted no donors. `AnimatableGetBoneTransform.cpp` was rejected because its `Get_Bone_Transform(const char *)` differs only by return type from the declaration in the composed view. `Animatable3DObjClassRva001A5460.cpp` was rejected because `Rva001A5460` and `_slave` are absent from that view. The tool recommends class-view reconciliation for `Animatable3DObjClass` and `BfmeVciAnchorElem`. No changes or claims were made; no source reduction or identity/link progress is claimed.
