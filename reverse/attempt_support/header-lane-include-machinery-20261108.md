# 7% of header adoptions are refused by the include walker, not by a layout

Measured 2026-11-08 over 210 units probed with `header_adopt_lane.py adopt`
across `UpgradeMux`, the 195-row re-run group and the first two cohorts of the
merge-blocker ranking.

## The measurement

15 of 210 units (**7.1%**) are refused by `include_walk`, before any layout
question is reached. Three causes, and they are concentrated:

| units | refusal |
| ---: | --- |
| 9 | `Vc7/include/typeinfo: include cycle cannot be ordered` |
| 5 | `Vc7/PlatformSDK/Include/Ole2.h: unresolved include macname1.h` |
| 1 | `reference/shims/bfme2_vector3/vector3.h: unresolved include osdep.h` |

The committed queue records 76 rows with these two failure shapes already, but
naming *different* headers -- `vendor\stlport\stl\_prolog.h` 63 rows,
`vendor\stlport\string.h` 8, `vendor\stlport\math.h` 2, and 3 `unresolved
include osdep.h`. So the recorded population and the live one are largely
disjoint, and 76 is a floor rather than the total.

If 7.1% holds across the 6270 live rows, this is on the order of 440 units
refused for a reason that has nothing to do with the class being adopted. That
is an order of magnitude more than the padding-span allowance would reach (45
rows, forecast four adoptions), and it is the largest single lever this session
found in the header lane.

## Ole2.h: the branch is provably dead

`Vc7/PlatformSDK/Include/Ole2.h` lines 18-30:

```c
#ifndef _MAC
// Set packing to 8
#include <pshpack8.h>
...
#else //_MAC
#ifdef _WIN32
#include "macname1.h"
#endif // _WIN32
#endif //_MAC
```

`macname1.h` is reached only when `_MAC` is defined, and the toolchain ships no
`macname1.h` anywhere (`find ... -iname 'macname*'` is empty). A Win32 build
never takes the branch. More to the point: **every one of these units is a
byte-matched row in the tree today**, so the real preprocessor already walks
`Ole2.h` without trouble. The directive is dead code, proven by the fact that
the file compiles.

`include_walk` follows it anyway. It says so in its own comment --

> A guard is a barrier only while its macro stays defined. Treat resets
> anywhere in the closure conservatively, including spliced directives and
> compiler macro-stack operations; **do not evaluate conditions.**

-- and refuses any *quoted* include it cannot resolve
(`header_adopt_lane.py:477`). Note the existing asymmetry: an **angled** include
that resolves nowhere is already tolerated two lines below, contributing nothing
to the closure. Only quoted ones refuse.

## Why I did not change it

The obvious narrow fix is to let an unresolvable quoted include contribute
nothing, exactly as an unresolvable angled one already does, and let the probe
compile be the arbiter -- the same argument that justified the vftable-pointer
allowance in `header-lane-vptr-standin-20261107.md`.

I did not make it, for two reasons.

1. It is a **specified** property with a named test,
   `test_r4_include_scan_refuses_unresolved_and_angle_code`, not an oversight.
   R4 appears to be a requirement number; flipping it changes how much the
   walker is permitted not to know about a closure it claims to have read.
2. The proof that the branch is dead is "the unit compiles today", and
   `include_walk` does not have that evidence at the point it decides. So the
   conservative refusal is not wrong on the information available to it -- only
   expensive. Weakening it is a judgement about the safety property, which
   belongs to a maintainer or a tooling seat, not to a pass that merely tripped
   over it.

Both cases are recorded as false rejects in `reverse/re_attempts.log`
(`?screenPixelToWorld@Radar@@...` 0x002D82E4 for the Ole2.h case,
`?rva00278C7C@Drawable@@...` 0x00278C7C for the typeinfo cycle) per AGENTS.md's
false-reject lane.

## typeinfo is the harder half, and the bigger one

Nine of the fifteen are `Vc7/include/typeinfo: include cycle cannot be
ordered`, so the cycle case is worth more than the unresolved-include case and
is not fixed by the same change. An unresolvable include has no body and no
children, so dropping it cannot hide a cycle; a real cycle through `typeinfo`
can only be ordered by either evaluating conditions or carrying a known-barrier
list for toolchain headers. Both are larger designs than a one-line allowance,
and the second is the sort of allowlist this repo's rules are rightly suspicious
of.

Whoever takes it should start from the measurement above rather than from one
unit: the cause is three headers, not three hundred.

## Caveat

210 units is a small and non-random sample -- it is whatever the classes I
probed happened to include. `Drawable` alone contributed 12 of the 15, because
`Drawable.h`'s closure reaches `Ole2.h` and `typeinfo`. The 7.1% should be
re-measured over a wider sweep before it is used to size the work; what it
establishes is the shape and the concentration, not the rate.
