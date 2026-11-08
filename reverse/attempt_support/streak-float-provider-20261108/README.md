# Streak float-vector providers, 2026-11-08

The default picker served streak.cpp's float-vector table at RVA 0x007D41AC.
The file also has the derived float table at 0x007D41B8 and the separate
StreakLine RenderObj bounds refusal. This change repairs the two float
providers; the existing bounds handoff remains open.

A fresh private compilation passes all 68 existing rows, but emits complete
float destructors of 41/70 bytes and deleting wrappers of 61/30 bytes, with
flags 0x60501020. The native owner has 33/35/28/28-byte bodies with flags
0x60101020. Thus the older alignment-only diagnosis does not describe the
current source: these copies also differ in code. A fresh in-memory TU map
approves no TU for the two deleting-wrapper RVAs, so neither row is moved.

The source now defines the two real float destructor specializations in
its existing size-optimized region. Their stock cleanup semantics follow
the existing simplevec template and native owner: conditionally delete the
buffer, clear its pointer, and clear the base capacity. The include and
three existing float specialization declarations move earlier so these
definitions precede first use. The optimization directives and dllimport
occurrences are unchanged. No new pragma, import, alias, row, pin or hatch
is introduced; no shared header or compiler flag changes.

All four emitted bodies independently verify against their existing
native rows: 0x00167F67/33, 0x00167FF7/35, 0x00168083/28 and 0x00168067/28.
Their code, relocations, flags and selection policies equal the current
simplevec_float_cleanup.cpp owner. The other 274 of 278 code COMDAT facts,
all 18 named external data allocations, external definitions, undefined
references and compiler weak defaults are unchanged. No provider is added
or removed. A public-build object agrees with the private candidate.

Normal build.sh passes 102/102 rows across streak and the three explicit
providers, including one data row, strings, floats and imports. All five
parent EH graphs are exact. Frozen-source and paired new-variant checks
pass. Strict preparation covers the owned supporting providers. Bounded
before/after bridge planning changes two target-not-winning-provider
refusals to two tables/six slots with no refusals in this pair. This is an
offline provider check, not a newly linked image or runtime result.

Extern-template trials preserved only 66/68 or 67/68 rows and still emitted
30-byte wrappers. Merely moving the include or explicit instantiations
into an existing size region preserved 68/68 but left all four wrong
bodies. Only the genuine size-region specializations retain every row
and emit all four native bodies. Failed controls remain under build/.

Preview against c885072a48 (2026-11-08 19:18) retains LINKS/5,575 bytes for
streak and LINKS/175 for the native owner. The two unchanged, unreferenced
SegLineRenderer getter diagnostics remain. The next published real link
must confirm that the two float tables leave the refusal queue; the
RenderObj bounds slots 65/66 remain the separate LINK-619 obstacle. No
coverage, census or runtime gain is claimed by this package.

Published as 6b9ecd0ea1 on push.py attempt 1 in 31.4 seconds. Required
publication checks pass, including all 68 source rows, four exact source
EH graphs, converged data and scoped DIR32 consistency. The post-publication
body/provider comparison also passes. The broader audit remains INCONCLUSIVE:
index c885072a48 versus outgoing base a05bf4a06da5570e87d8eac2f4a01d99c9b1c01e;
Common/AICowerState_onEnter.cpp lacks a current strict receipt. The bounded
two-table result remains pending confirmation by the next real image.
