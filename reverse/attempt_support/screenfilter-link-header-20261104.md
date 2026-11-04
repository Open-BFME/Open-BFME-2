# Screen filter current-link check and ShaderClass adoption blocker

Inspected revision: `4b521e48a39921ed23ccbca6aba6b01ef7423b2e`.
Source: `Code/GameEngineDevice/Source/W3DDevice/GameClient/ScreenFilterRva000FC63DSet.cpp`.

The exit-link picker served missing `?g_Va00DEC1CC@@3IA` and
`?g_Va00DEC1DC@@3IA`. Current master already defines both as 16-byte storage
in `Rva007B6880Thunks.cpp`, from `586e10cab3`. No new provider was needed.

`./build.sh` passed 21/21 functions, 11 data rows, seven funclet bindings,
two string literals and 30 float literals. `find_declared_unmatched.py`
reported all defined functions matched.

`link_check.py` against local index `a62ac1c10b` (2026-11-04 07:28) reports:
- ScreenFilterRva000FC63DSet.cpp: LINKS, 5,200 -> 5,200 bytes.
- Rva007AC9B0FilterInits.cpp: LINKS, 66 -> 66 bytes.
- Rva007B6880Thunks.cpp: unresolved `?g_Va00DF2984@@3PAIA`; outside this repair scope.

These are local predictions, not a new real-link result or census.
The published objects bundle was truncated; fetch-index kept the identical local index.

## Header trial (reverted)

The ShaderClass header queue names a line-splice guard. The only source splice
is the unused PAD_VIRTUALS10 macro (no invocations in the unit). Removing that
macro lets `header_adopt_lane.py adopt --class ShaderClass --header
Code/Libraries/Source/WWVegas/WW3D2/ShaderClass.h SOURCE --apply` reach its
include inventory, which refuses:

```
field renames: .../Vc7/PlatformSDK/Include/Ole2.h: unresolved include macname1.h
```

This is an inactive Macintosh include, also observed for W3DLaserDraw in the
attempt log. No adopted source or header debt retirement remains. Both the
macro deletion and trial were restored. Next step: tooling lane must repair
the inactive-include inventory in a separate verifier change before retrying
ShaderClass adoption. After that, reconcile the private Force_Dirty helper
with canonical Invalidate and verify the entire unit and its link bindings.
