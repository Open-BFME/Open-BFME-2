# Audio-loop and faction-bib Drawable ID provider binding, 2026-11-05

Inspected revision: `4226981a96eed2fedaa9c7935836e22ee83415ea`.
Scope: `GameLogic/Object/Behavior/ModelConditionAudioLoopClientBehaviorUpdate.cpp`
under GameEngine and `W3DDevice/GameClient/W3DTerrainVisualAddFactionBibDrawable.cpp`
under GameEngineDevice.

## Target facts and repair

Both units are listed in the real-link blocker register for
`?getID@Drawable@@QBE?AW4DrawableID@@XZ`. Original current-object previews
reproduce that sole unresolved reference in each unit. The pin binds that
spelling to `0x0055A88B`, already owned by the seven-byte
`?get@Rva0055A88BDwordField@@QBEHXZ` row in `DispDwordFieldGetters.cpp`.
The existing provider reads the dword at `this + 0x100`, matching the ID
offset evidenced by the canonical Drawable header. This is an existing
placeholder provider, not missing byte coverage.

Following LINK-538's existing consumer repairs, the two calls now use that
compiled provider through its existing opaque view. Explicit DrawableID casts
preserve the audio constructor overload and bib-forwarder argument domain.
No additional donor identity or class layout is inferred. The ObjectID bib
overload remains unchanged. No rows, extents, pins, aliases, source paths or
debt-register keys change; existing header-queue prerequisites remain open.

## Verification

- Original and final `./build.sh` pass all nine code rows (five audio-loop,
  four bib), including string, float and import checks.
- `find_declared_unmatched.py` passes before and after both edits.
- Both explicit units pass `link_check.py --prepare-current`, producing
  strict reusable receipts without altering the census/index/status.
- `eh_verify.py` reports three EH graphs EXACT (one audio-loop, two bib),
  zero non-exact and zero missing objects.
- Against index `112a456a2c`, dated 2026-11-05 15:52, final combined previews
  report both units LINKS: audio-loop 239 authored bytes and bib 1,556.
  The 1,795-byte total is bounded preview scope; the index already counts
  those bytes, while the original current objects fail. No census gain is
  inferred from these results.
- Read-only COFF inspection confirms that each final consumer references
  the rowed getter and no longer references Drawable::getID. The provider
  defines the rowed getter in section 385. Trial object SHA-256 values:

  | Unit | SHA-256 |
  | --- | --- |
  | ModelConditionAudioLoopClientBehaviorUpdate.cpp | `00eea876b032cac6be0c6f29459f9d70e3bb0bb61a0e16b03f90bfce75e18498` |
  | W3DTerrainVisualAddFactionBibDrawable.cpp | `722500e74ea443afb5f502f184b69de5946aa254f17050de9cab25f732ecadd6` |
  | DispDwordFieldGetters.cpp | `ff5d55d3600580136d6cc75abf311ea7a30538fa2b8c98e8692640be7d9900ac` |

## Publication reconciliation

The publication rebase met independent upstream repair `2825058d58`, which
already makes the identical two call changes. Its declaration formatting was
retained; this commit consequently adds verification evidence rather than a
second source repair. The resolved sources pass all nine rows again and both
previews still LINKS against the same index. Resolved object SHA-256 values:
audio-loop `092709d0e6a336ca381897f675d991fcaa3612835386c6922c262671fa4ca2ca`;
bib `4c15f05a6209cd070098202401a7447bebefeeac5b04a6bdf4fd2ca6a793eb05`.

Next check: the next real link should stop listing these two missing-name
errors. Other consumers of the pinned spelling, full consumer selection,
census and runtime confirmation remain separate work. No headline gain is
claimed.
