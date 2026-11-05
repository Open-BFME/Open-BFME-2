# Strategic UI destructor holder adoption

Inspected revision: `f3aed93b65`. Scope:
`Code/GameEngine/Source/Common/Rva005E5FFBDtor.cpp`, selected as the only
whole-file donor for the approved provisional
`Code/GameEngine/Source/GameClient/GUI/StrategicInGameUI.cpp` TU.

The initial `tu_skeleton.py --merge ... --dry-run` accepted no donor and
rejected this file on bytes. The destination already includes canonical
`Rva000AD6F4`; the donor instead declared an eight-byte private holder.
The canonical header establishes four-byte pointer storage and the rowed
destructor at `0x000AD6F4`, folded with `clear`.

The repair includes that header, preserves each enclosing owned slot's
eight-byte extent with four bytes of padding, and lets member destruction
release the holder once. The enclosing slot padding is a structural view,
not a recovered original member identity. Application class names remain
unknown.

Verification:

- Before and after: `./build.sh` passes all seven donor rows, including the
  parent `0x005E5FFB`, deleting wrapper and emitted EH entries.
- `find_declared_unmatched.py`: all defined functions already matched; the
  existing absent-from-retail delete anchor remains accounted for.
- `eh_verify.py`: one EH parent, EXACT; no missing object or baseline debt.
- `header_adopt_lane.py accept --class Rva000AD6F4 <donor>`: PASS, retiring
  exactly one header-queue row through its owning verifier and link check.

No source paths move in this prerequisite repair. No new census or real-link
result is claimed. Retry the supported TU merge after this separate commit.
