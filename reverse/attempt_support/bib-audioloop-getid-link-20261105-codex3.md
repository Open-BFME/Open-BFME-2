# Terrain bib and model-condition audio Drawable ID binding

Inspected revision: `0e379acc72e5abaedf2a62f49a48a01fc2ec50d3` (2026-11-05).
Scope: `W3DTerrainVisualAddFactionBibDrawable.cpp` and
`ModelConditionAudioLoopClientBehaviorUpdate.cpp`.

## Target facts

The real-link blocker register lists both units as references to undefined
`?getID@Drawable@@QBE?AW4DrawableID@@XZ`. The existing provider is
`?get@Rva0055A88BDwordField@@QBEHXZ`, rowed at RVA `0x0055A88B` in
`Code/GameEngine/Source/Common/DispDwordFieldGetters.cpp`. Retail's complete
seven-byte body is `8b 81 00 01 00 00 c3`: return the dword at this +0x100.

Retail independently proves both caller destinations:

| Parent RVA / size | Call RVA | Retail bytes | Destination RVA |
| --- | --- | --- | --- |
| addFactionBibDrawable: 0x00092A95 / 835 | 0x00092DA6 | e8 e0 7a 4c 00 | 0x0055A88B |
| model-condition audio update: 0x004CBFC7 / 165 | 0x004CC012 | e8 74 e8 08 00 | 0x0055A88B |

Both calls now use a declaration-only view of that existing provider, casting
the returned value to DrawableID to preserve the original consumer signature.
The Object ID access in the terrain unit's second function is unchanged.
No recovered provider name or additional layout is claimed. Earlier repairs
in AnimationSoundClientBehavior and InGameUI are leads, not target proof.

## Verification

- Normal scoped builds before and after pass all nine function rows across
  the two units, including EH handlers and funclets. String, float and import
  reference checks pass.
- Declared-unmatched checks pass before and after. The audio unit's existing
  two marked inline definitions are unchanged.
- Each compiled object's undefined externals differ only by replacing
  `?getID@Drawable@@QBE?AW4DrawableID@@XZ` with
  `?get@Rva0055A88BDwordField@@QBEHXZ`. External definitions, weak externals
  and alternate names are unchanged; the provider object defines the new name.
- After fetching the published index, combined preview: both LINKS,
  1,556 terrain bytes and 239 audio bytes. Index: c95fcfcfcd,
  2026-11-05 05:17. The preview already accepts the old spelling, so this
  establishes no census improvement or successful real link.
- `git diff --check` passes. No ledger, pin, alias or header changes.

Await the next automated real link to confirm that these two units stop listing
the undefined getter. Other callers and provider identity recovery remain
outside this scope.
