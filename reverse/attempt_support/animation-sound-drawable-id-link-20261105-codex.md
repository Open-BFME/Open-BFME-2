# AnimationSoundClientBehavior drawable-ID link repair

Inspected source revision: `2af8c01e565472ad1bd8647cdbb95c93f54bceea`.
Scope: `Code/GameEngine/Source/GameClient/Drawable/Update/AnimationSoundClientBehavior.cpp`.

## Target and provider evidence

The real-link blocker register lists twelve sources referring to
`?getID@Drawable@@QBE?AW4DrawableID@@XZ`, including this unit. Its existing pin
maps to RVA `0x0055A88B`, but no compiled object provides that spelling.
`pin_consistency.py --symbol` confirms the pin agrees with the matched owner
`?get@Rva0055A88BDwordField@@QBEHXZ` in
`Code/GameEngine/Source/Common/DispDwordFieldGetters.cpp`.

Retail's entire seven-byte body is `8b 81 00 01 00 00 c3`: load the dword at
`this + 0x100` and return. The provider's existing macro specifies displacement
`0x100`, and its compiled object defines the matched owner symbol.
`./build.sh '?get@Rva0055A88BDwordField@@QBEHXZ'` passes 1/1 functions with
the current inputs. These facts establish a usable provider and the access
shape; they do not recover a class name from that body alone.

## Change and checks

The animation-sound unit now calls that existing accessor through its existing
opaque class spelling and converts the returned dword to `DrawableID` for the
audio-event constructor. Its unused `Drawable::getID` declaration is removed.
No provider, ledger, pin, alias, hatch or source path changes.

`./build.sh Code/GameEngine/Source/GameClient/Drawable/Update/AnimationSoundClientBehavior.cpp`:

- 31/31 function checks and one data row pass.
- Seven funclet pins verify, including compiler-label renumbering.
- Eleven string literals plus the empty-string references, one float literal
  and one named import pass.
- `find_declared_unmatched.py` passes before and after the change.

COFF comparison against the saved pre-edit object:

- All 68 external definitions and all 67 COMDAT names remain present.
- Exactly one undefined external is replaced: the unprovided `Drawable::getID`
  spelling becomes the existing matched accessor's spelling.
- Only `?updateAnimationSounds@AnimationSoundClientBehavior@@QAEXXZ` changes
  its COMDAT fingerprint (`b5dab35a3056` -> `05ee41b5ea1f`); its full extent
  remains 811 bytes. Other COMDAT fingerprints remain identical.
- The provider object defines the replacement external.

`link_check.py` passes before and after: LINKS, LINKED 2,316 -> 2,316 bytes,
using the census at `c95fcfcfcd` (2026-11-05 05:17). This preview already
accepted the pin and therefore cannot measure the real-link repair. No census
or real-link result is claimed. The next real-link run must confirm removal of
this source's missing-name error.

## Remaining scope

The other eleven sources in `reverse/exit_link_blockers.tsv` still require a
usable object spelling for this call, or a separately verified reconciliation
of the provider and its opaque-name consumers. This change handles only the
animation-sound unit; it does not recover the accessor's class identity.
