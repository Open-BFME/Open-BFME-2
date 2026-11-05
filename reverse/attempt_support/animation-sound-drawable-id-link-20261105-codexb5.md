# AnimationSound drawable-ID call binding

Inspected revision: `9497d7bad5a93816ec6f777ceff7b16ae22928f9`.
Scope: `Code/GameEngine/Source/GameClient/Drawable/Update/AnimationSoundClientBehavior.cpp`,
`AnimationSoundClientBehavior::updateAnimationSounds` at RVA `0x004CA328`.

The real-link blocker register lists this unit's unresolved
`?getID@Drawable@@QBE?AW4DrawableID@@XZ`. Its existing pin targets RVA
`0x0055A88B`, whose single matched owner is
`?get@Rva0055A88BDwordField@@QBEHXZ` in `DispDwordFieldGetters.cpp`.
That provider reads a dword at `this + 0x100`; the canonical Drawable header
also identifies this offset as the drawable ID. Other consumers, including
`LaserUpdate.cpp`, already call this provider through its existing view.
These are target/ledger facts, not newly recovered donor names.

Replace the audio-event call's unprovided spelling with the existing getter,
casting the returned value to `DrawableID` to preserve the selected audio-event
constructor overload. Remove the unused private `Drawable::getID` declaration.
No pin, alias, ledger row or provider definition changes.

Checks:

- `./build.sh Code/GameEngine/Source/GameClient/Drawable/Update/AnimationSoundClientBehavior.cpp`
  passes before and after: 31/31 function rows, one data row, string, float and
  import checks. Seven existing funclet rows verify across label renumbering.
- `find_declared_unmatched.py` before and after reports all defined functions
  already matched (32 matched rows, two unclaimed definitions noted).
- Comparing `link_census.object_symbols` on the saved original and rebuilt
  objects removes exactly `?getID@Drawable@@QBE?AW4DrawableID@@XZ` from the
  undefined symbols and adds exactly `?get@Rva0055A88BDwordField@@QBEHXZ`.
  Defined symbols, weak bindings, linker aliases and forced includes are equal.
  The existing compiled `DispDwordFieldGetters.obj` defines the added name.
- `link_check.py` before and after reports LINKS, 2,316 -> 2,316 bytes,
  against the 2026-11-05 05:17 census at `c95fcfcfcd`. This preview already
  considered the old spelling satisfiable; the object-symbol comparison is the
  evidence that this real-link blocker reference changed.

No real-link or census run was started. The next real link must confirm removal
of this unit's missing-getter error. Other units in the blocker register still
reference the same unprovided name; this repair makes no claim about them.
