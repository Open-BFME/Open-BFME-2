# ??_7BfmeSubobject0022CE19@@6B@ (VA 0x00BE7560): slot 2 bridge

Target facts:
- Retail table VA 0x00BE7560 slots: 0x0022CEF7 (deleting dtor), 0x000B3FD0 (ret),
  0x0022CEF1 (`mov eax,"SaveGameInfo"; ret`), 0x002DDEC0 (xfer).
- The constructors 0x0022CE19/0x002DD173 and destructor 0x002DD1E9 (rowed under
  BfmeSubobject0022CE19) install it.
- 0x0022CEF1 is rowed as `?name@Rva0022CEF1Named@@QBEPBDXZ` in
  Code/GameEngine/Source/Common/SubsystemNameGetters.cpp (no approved unit in tu_map).

Why it is bridged:
- The unit views (SaveGameInfoConstructorBFME2.cpp, SaveGameInfoCopyBFME2.cpp,
  BfmeSubobject0022CE19Assign.cpp) name slot 2 `typeName` through the private base
  `Rva0022CE19SnapshotBase`; SaveGameInfoCopyBFME2.cpp binds
  `?typeName@BfmeSubobject0022CE19@@UBEPBDXZ` to the placeholder with an
  `/alternatename` hatch (line ~482), which the bridge queue reports at slot 2.

Tried (claude-opus-5.5):
- `rename.py function --rva 0x0022CEF1 --to-class BfmeSubobject0022CE19 --new typeName
  --prepared SubsystemNameGetters.cpp=<definition under the class> --dry-run` refuses:
  "BfmeSubobject0022CE19 has no canonical header in reverse/canonical_classes.csv: the
  name of retail table 0x00BE7560 slot 2 is voted on the registered class".

Next steps:
1. Register BfmeSubobject0022CE19 (Code/GameEngine/Include/GameClient/BfmeSubobject0022CE19.h,
   parent Snapshot, slot 2 GetSnapshotName per reference/shims/moduledata/Common/Snapshot.h)
   through the class-header lane.
2. Two name_lane votes for slot 2 (canonical Snapshot slot name: GetSnapshotName).
3. Respell the family's private base `Rva0022CE19SnapshotBase::typeName` to the voted
   name in the three views (also covers GameSlot's ICF row 0x002296E6, SaveMapPreview's
   and BfmeSubobject00229875's `/alternatename` hatches, which should go with it),
   then `--to-class` with `--also` for the sibling slots, removing the hatches.
