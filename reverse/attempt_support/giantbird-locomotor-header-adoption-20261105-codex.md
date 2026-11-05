# Giant-bird Locomotor header adoption (2026-11-05)

Inspected base: `bb62c41a782af9600d56eaf6bcc30dd653f488f1`. Owner: `yasinschroeder-codex`.

Scope:
- `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdFollowPathStates.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdNormalFlightStates.cpp`

The two private Locomotor views expose only a float at +0x48 through
`getBfme48()`. The existing canonical `LocomotorClass.h` declares
`m_preferredHeight` at that same offset and supplies `getPreferredHeight()`.
Both consumers now include that header and call its existing accessor.
This adopts an established declaration; it adds no new name or ABI claim.

Verification:
- Initial `check_csv.py`: PASS (99,458 function rows).
- `find_declared_unmatched.py`: PASS for both files, before and after edits.
- Scoped `./build.sh` for both sources: PASS, 12/12 matched functions;
  three compiler float literals verified.
- `header_adopt_lane.py accept --class Locomotor` for both sources: PASS
  individually, with the lane's combined ordinary link preview preserving
  census-linked bytes. The owning tool retired exactly two header-queue rows.
- No source paths, ledger identities, shared headers, pins or aliases changed.

The initial 13-source automatic adoption trial applied nothing. The other
11 consumers retain their existing queued layout, missing-method, byte or data
obstacles and their original sources. Searches of the obstacle register for
Locomotor and the two giant-bird source names found no entry requiring a changed
next step for this accessor cleanup. No census, real-link, ownership or smoke
gain is claimed.
