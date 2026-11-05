# LAN handler composition prerequisite, 2026-11-05

Inspected master: `4f18c94984`. Scope claimed: LANAPIhandlers.cpp and its
handleGameOptions, handleGameStartTimer and handleSetAccept fragments.

Replaced the seed's BFME_GSLOT/BFME_VSLOT expansions with the identical virtual
method declarations, preserving names, slots and pure/non-pure attributes.
No body, header, pin, ledger or protected-register change.

Checks:
- `./build.sh Code/GameEngine/Source/GameNetwork/LANAPIhandlers.cpp`: 45/45
  matched; 24 funclet labels verified through parent EH data, string/import
  references pass. `find_declared_unmatched.py`: no unrowed definitions.
- `link_check.py` on all four files: all link; preview retains 6,419 bytes
  (6,171 + 99 + 63 + 86), against census index c95fcfcfcd, 2026-11-05 05:17.
  This is a preview, not a new census or headline gain.
- `tu_views.py --dry-run --no-merge-check`: LANGame and SlotEntry already
  shared; LANMessage's anonymous union remains unsupported.
- `tu_skeleton.py --merge ... --dry-run`: accepts none; seed failure changes
  from the prior macro compile error to `bytes`. No rows moved or files removed.

Next prerequisite: retain packing directives around the wire declaration.
A single-seed call to the current composer places `#pragma pack(push, 1)` and
`#pragma pack(pop)` on adjacent lines 54/55, while `struct LANMessage` begins
at line 388. The seed's original push/pop enclose only that structure. Hoisting
both directives loses that scope; replacing virtual-slot macros alone cannot
make the seed compose. Any composer fix must verify packing scope and byte
matching; do not accept the mismatching candidate. The canonical header/view
prerequisites remain after that (GameInfo, GameSlot, GlobalData, LANAPI,
NetworkInterface and TreeHintOpaque0043671B). No source recovery credited.
