# BattlePromptMovieClip header adoption, 2026-11-04

Inspected revision: `70e2c4419f`. Claim owner: `yasinschroeder-codex3`.

## Completed scope

`Code/GameEngine/Source/Common/VslotSmallBodiesAJ_Rva00034D00.cpp` and
`Code/GameEngine/Source/Common/VslotSmallBodiesW5SN4.cpp` now include
`Code/GameEngine/Include/GameClient/BattlePromptMovieClip.h` at global scope.
Each retains its existing nested `StrategicHUD::BattlePromptMovieClip::Impl`
declaration outside the enclosing class. These declarations only describe the
existing callees; no function, parameter, symbol, layout or binding is changed.

The automatic adoption removed the nested declarations along with the private
outer class and placed the include inside `namespace StrategicHUD`. The manual
adoption preserves the necessary nested declaration and places the namespaced
header outside that namespace, as existing adopted consumers do.

Verification:

- `./build.sh` on both sources: 29/29 matched; one renumbered unwind label
  verified through its parent's EH data (`$L1796` -> `$L2472`, RVA 0x007A12A5).
- `find_declared_unmatched.py` on both: all definitions already matched.
- `header_adopt_lane.py accept --class BattlePromptMovieClip` on both: PASS;
  the tool retired exactly their two rows from `reverse/header_queue.tsv`.
- `link_check.py` on both current objects: LINKS; 111 -> 111 bytes and
  446 -> 446 bytes, respectively. Comparison census: 2026-11-04 13:15 at
  `f6d845ecd4`. This is a preview preserving 557 bytes, not a new census.

## Remaining queued scope

The five-source automatic trial restored all failures before the two manual
adoptions. The following three originals and their debt rows remain unchanged:

- `Rva005E9625Dtor.cpp`: automatic trial fails its 53-byte destructor row at
  0x005E9625. Its original private base has a virtual destructor and size 4;
  its 8-byte pad places the member at +0xC. The canonical base is size 8 and
  has a nonvirtual destructor. Reconcile the derived member offset and
  destructor call identity with the base provider as one dependency group.
- `Rva005FA393Dtor.cpp`: automatic trial loses the nested Impl constructor
  declaration (C2514). Preserving that declaration is necessary but insufficient:
  the original destructor is `??1BattlePromptMovieClip@StrategicHUD@@UAE@XZ`,
  whereas the canonical header declares the nonvirtual destructor. Reconcile
  its provider and consumers before changing that identity. Its existing
  present-unmatched constructor and guarded-delete helper also need to survive.
- `StrategicInGameUIBattlePromptDialog.cpp`: automatic trial puts the header
  inside the namespace, producing a nested namespace and a record-type
  conversion failure. Move the include to global scope first. The existing
  queue already records the next structural blocker: the derived Rva005E9625
  has no implementations of the canonical base's five pure virtual callbacks.
  Retail callback rows exist at 0x005E95A8, 0x005E95B9, 0x005E965A,
  0x005E9669 and 0x005E9678 under different private owner identities. Establish
  their common owner and reconcile declarations/providers with evidence; do
  not supply empty overrides to instantiate the derived clip.

The base's five-slot vtable and nonvirtual destructor are target facts recorded
in the canonical header. The proposed dependency-group repairs above are next
steps, not verified reconstructions. No new pins, aliases or hatches were added.
