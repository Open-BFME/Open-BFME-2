# Animation sound uses the recovered Drawable ID provider

Inspected base: `dcb5c045f4db1cc43e04bf7452d801c44910ce76`.
Scope: `Code/GameEngine/Source/GameClient/Drawable/Update/AnimationSoundClientBehavior.cpp`,
`updateAnimationSounds` at RVA `0x004CA328`.

The default picker still serves the real-link artifact's missing
`?getID@Drawable@@QBE?AW4DrawableID@@XZ` reference. Earlier repairs replaced
that call with `Rva0055A88BDwordField::get`. Since those repairs, upstream
`85b46a09f3` added the named getter in `Drawable.cpp`, rowed at `0x0055A88B`
as an ICF twin of the existing disp32 getter. Its seven retail bytes load
the ID at `this + 0x100`. This is an existing provider and ledger identity,
not a newly inferred name or a new pin.

Use `Drawable::getID()` directly for the audio-event constructor and remove
the unused address-named getter declaration and obsolete missing-provider
comment. Its `DrawableID` return preserves the constructor overload without
the previous cast. No layout, provider, ledger, alias or header changes.

Verification:

- `find_declared_unmatched.py` before and after: all defined functions are
  already matched (32 matched rows, two unclaimed definitions noted).
- `./build.sh` on the animation-sound TU before and after: 31/31 function
  rows, one data row, string/float/import checks pass; existing funclet rows
  verify through label renumbering.
- `./build.sh '?getID@Drawable@@QBE?AW4DrawableID@@XZ'`: 1/1 exact.
- COFF inspection: the animation object references the named getter and no
  longer references `?get@Rva0055A88BDwordField@@QBEHXZ`; the current Drawable
  object defines the named getter.
- Published index: `c95fcfcfcd`, 2026-11-05 05:17 (fetch retained this same
  local index). The animation unit's preview remains LINKS / 2,316 bytes.
- Previewing Drawable against the unchanged index alone reports a duplicate
  getter from `DrawableHealthBarGate.obj`. Its current source instead includes
  the canonical Drawable header and its current object defines no getter.
  Previewing all three current objects together passes: animation 2,316 bytes,
  Drawable 8,392 bytes, health-bar gate 472 bytes. This is a stale index copy,
  not a current provider collision; no provider edit was necessary.
- `link_check.py --prepare-current` on animation and Drawable passes the normal
  combined gates (181/181 code rows, four data rows), but refuses its reusable
  preparation receipt because Drawable's receipt went stale during those gates.
  No strict reusable witness is claimed; the bounded preview above is the
  available link evidence. A future census still needs current receipts.

The getter provider and animation call are locally verified. The next
authorized real-link run must confirm the old missing-name errors are gone.
Other workaround consumers are outside this source edit. No census or runtime
gain is claimed, and no restricted measurement runner was started.
