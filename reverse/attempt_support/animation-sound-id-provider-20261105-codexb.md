# Animation sound ID provider binding, 2026-11-05

Inspected source revision: `5a1f7a409fa78ba257386060e70ffce5875ae189`.
Scope: `Code/GameEngine/Source/GameClient/Drawable/Update/AnimationSoundClientBehavior.cpp`,
particularly `AnimationSoundClientBehavior::updateAnimationSounds` at RVA `0x004CA328`.

## Target facts and repair

The real-link blocker register names an unresolved
`?getID@Drawable@@QBE?AW4DrawableID@@XZ` in this unit. Its existing pin is
`0x0055A88B`. The ledger already owns that seven-byte body as
`?get@Rva0055A88BDwordField@@QBEHXZ` in
`Code/GameEngine/Source/Common/DispDwordFieldGetters.cpp`: a dword load at
`this + 0x100`, followed by return. Drawable's existing canonical headers also
identify its ID at that offset. This is an existing provider, not an unrowed
body or lost coverage.

The audio-event constructor now receives the result of that compiled getter,
cast to the already used `DrawableID` type. The same function already binds
its draw-module lookup to the rowed getter at `0x002B224B`. This repair does
not establish the opaque getter class's full identity, rename it, or change
its other consumers. No donor evidence is claimed.

## Verification

- Original and final `./build.sh` pass all 31 code rows, one data row,
  11 literals plus the empty-string reference, one float literal and one
  named import. The complete 811-byte update body remains matched.
- `find_declared_unmatched.py` passes before and after the edit.
- `eh_verify.py` reports five EH graphs EXACT, with no missing objects or
  non-exact graphs.
- `link_check.py --prepare-current` passes the explicit unit and writes its
  strict reusable receipt; it leaves the census/index/status unchanged.
- Ordinary preview uses the local index dated 2026-11-05 15:52 at
  `112a456a2c`. Fetching the published index retained this newer local index.
  The original source fails solely on `?getID@Drawable@@QBE?AW4DrawableID@@XZ`,
  with `LINKED 2,316 -> 0`. The final source reports `LINKS`,
  `LINKED 2,316 -> 2,316`. This is a bounded before/after repair, not an
  increase to the census headline.
- Read-only inspection of the final COFF symbol tables finds no `Drawable::getID`
  reference in the consumer. It finds the rowed getter undefined there and
  defined in section 385 of `DispDwordFieldGetters.cpp`'s object.
  Consumer object SHA-256:
  `ea30e7add2dd727a7804e1d02cb15d14a93c427c1e66063067d69eafc403a6dd`.
  Getter-provider object SHA-256:
  `ff5d55d3600580136d6cc75abf311ea7a30538fa2b8c98e8692640be7d9900ac`.

No source paths, ledger identities, pins, aliases, hatches or debt keys change.
The next real link must confirm that this unit stops listing the missing name.
Other consumers of the same missing spelling in `reverse/exit_link_blockers.tsv`
remain separate work. Full current consumer selection, census and runtime
confirmation are not claimed.
