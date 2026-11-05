# W3DLightDraw::GetSnapshotName respell: rename.py modes refuse (2026-11-05, claudeb4)

Target fact: 0x000CFA3C (6 B, returns "W3DLightDraw") is rowed as the nonvirtual
`?name@W3DLightDraw@@QBEPBDXZ` in `Code/GameEngine/Source/Common/W3DDrawNameGetters.cpp`;
`319deafdc1` names it slot 2 (GetSnapshotName) of the table W3DLightDraw's ctor 0x000CF91D installs.

Tried (dry runs, nothing written; prepared getter in build/, as W3DPropDraw's in the same file):

- `rename.py function --rva 0x000CFA3C --to-class W3DLightDraw --new GetSnapshotName --prepared ...`
  -> `refused: ?name@W3DLightDraw@@QBEPBDXZ is already a member of W3DLightDraw`
  (`--to-class` moves only a placeholder-class member, `plan_to_class`).
- `--basis` with `--to-class` -> refused ("pass no --basis").

The remaining routes are an identifier rename `name` -> `GetSnapshotName` (needs a naming
basis/approval), then `--virtual --access protected` (QBE -> MBE). `--virtual` requires the
installer unit's compiled vftable to hold the slot, so `W3DLightDraw.cpp` must first adopt
the canonical header, and that leaves the eight provider-less overrides `319deafdc1` lists.
