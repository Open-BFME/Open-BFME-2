# Adopt canonical Vector3 in BaseHeightMapScorchOverlap: bounded unsuccessful adoption trial

Source `Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapScorchOverlap.cpp`, existing parent `?rva00069C5F@BaseHeightMapRenderObjClass@@QAEXVVector3@@M@Z` at
0x00069C5F/135B. Native1/1 and all3 external bodies match, but the stricter whole-runtime-section comparison fails: the local Length replacement emits2 additional static helpers (scorchSqrt and scorchVectorLength). Static incoming-root check finds no retained root; whole-section equality remains unproved. No gate or comparator relaxed; original restored and native gate passes.

The private candidate does not replace the committed source. No new native
row, completed adoption or runtime improvement is claimed. The existing
source remains byte-verified. Diagnostic sources and comparisons are retained
in ignored build/up-to-eighteen-each-20261102-2256/b2-06-*. The adjacent patch preserves the latest
private trial. Other trial variants, if performed, remain in the diagnostic controls.
No shared header, compiler flag, pin, alias or gate change is attempted.
