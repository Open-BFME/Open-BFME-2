# Adopt canonical Vector4 in W3DQuadrupedDrawGetFootLocations: bounded unsuccessful adoption trial

Source `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DQuadrupedDrawGetFootLocations.cpp`, existing parent `?getFootLocations@W3DQuadrupedDraw@@UAE_NAAV?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@_N@Z` at
0x000CA352/988B. Canonical Vector4 introduces an out-of-line Matrix3D construction call. Explicit force-inlining removes that call but leaves a995B parent versus native988B, with changed SSE multiplication operand scheduling from offset0xF9; recorded instruction diff. Further alias/inline-shape reconciliation is required.

The private candidate does not replace the committed source. No new native
row, completed adoption or runtime improvement is claimed. The existing
source remains byte-verified. Diagnostic sources and comparisons are retained
in ignored build/up-to-eighteen-each-20261102-1632/b2-05-*. The adjacent patch preserves the latest
private trial; direct-adoption and component-copy variants are retained too.
No shared header, compiler flag, pin, alias or gate change is attempted.
