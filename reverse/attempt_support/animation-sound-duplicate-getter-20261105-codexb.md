# Animation-sound duplicate getter declaration repair

Inspected revision: `34acb89777d21dff1f0182a21ba356b1b9604dff`.
Scope: `Code/GameEngine/Source/GameClient/Drawable/Update/AnimationSoundClientBehavior.cpp`.

The default picker served this unit's existing real-link blocker. The getter
call had already been repaired by `fb2936dc85`, which also declared the existing
`Rva0055A88BDwordField` provider. Later commit `306f6f33e7` added a second
definition of that class immediately above it. The current unmodified unit
failed `./build.sh` during its data-row compile. This is a compilation regression
in an already repaired consumer, rather than a missing body or coverage row.

Remove the second definition and its redundant comment, retaining the original
provider declaration and the repaired call. No executable statements, rows,
pins, aliases, debt keys, source paths or shared headers change. The repair
does not establish the opaque provider's complete class identity.

Verification after removal:

- `./build.sh` passes 31/31 functions, one data row, seven funclet pins,
  eleven string literals and an empty-string reference, one float literal and
  one named import.
- `find_declared_unmatched.py` passes before and after the edit.
- `eh_verify.py` reports five EH graphs EXACT, none missing or non-exact.
- `link_check.py --prepare-current` byte-verifies the explicit unit and saves
  its strict reusable receipt.
- Ordinary `link_check.py` reports LINKS, LINKED 2,316 -> 2,316 bytes, against
  the local census index at `112a456a2c` (2026-11-05 15:52). Fetching the
  published index retained this newer local index.
- `git diff --check` passes.

The preview verifies only this unit's current closure. The next real link must
confirm the missing-name error is gone; no new census or runtime result is
claimed. Other consumers and full consumer selection remain outside this repair.
