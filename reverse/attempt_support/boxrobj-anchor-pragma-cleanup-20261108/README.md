# BoxRenderObj unused compiler controls, 2026-11-08

boxrobj.cpp removes its unused BfmeVciAnchorElem/bfmeVciAnchor pair, twelve
optimization pragmas in that unused scope or adjacent empty pairs, and two
empty inline-depth pairs. The RefCountClass include remains inside its
required size-optimization pair. The stale present-unmatched annotation on
AABoxRenderObjClass::Render is removed: its 243-byte row at 0x00175E50 already
belongs to this source. No function body, compiler command, source path or
ledger owner changes.

Verification covers the complete file: all 57 code rows and all 12 parent EH
graphs pass normal verification. The six float references pass, and the source
remains unfrozen. Private verification also passes 57/57 with a clean LinkGuard.
All 246 external COMDAT byte/relocation facts and section flags are unchanged;
external definition names and all 25 named data allocations are identical.
The final object hashes and comparison scope are in final-proof.json.

Supported hatch-counter update finds thirteen retirements in this source:
twelve pragma_optimize occurrences and the stale present_unmatched occurrence.
Only these source keys are retained from its generated result; every register
record outside boxrobj.cpp remains byte-identical to the original baseline.
The final baseline diff removes no other contributor's debt. No allowance or
growth is introduced. This baseline edit carries a Verifier-Change trailer.

Strict source preparation passes; ordinary current-object preview against
d171e84869 (2026-11-08 15:35) conserves LINKS/6,110 authored bytes. This cleanup
does not resolve the served BoxRenderObj/AABox/OBBox table refusals. Their
shared RenderObj bounding-getter provider/alignment boundary remains recorded
in LINK-619 and renderobj-bounding-order-20261108. No check, alignment exception
or bridge is changed, and no full-link or runtime clearance is claimed.
