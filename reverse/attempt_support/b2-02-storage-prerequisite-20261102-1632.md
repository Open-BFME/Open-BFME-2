# Adopt canonical Vector3 in W3DViewIterateDrawablesInRegion: bounded unsuccessful adoption trial

Source `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewIterateDrawablesInRegion.cpp`, existing parent `?iterateDrawablesInRegion@W3DView@@UAEHPAUIRegion2D@@P6AHPAVDrawable@@PAX@Z2@Z` at
0x00086245/567B. Canonical Vector3 changes the parent frame and copy shape. Direct adoption adds an out-of-line assignment; a local component-copy helper removes that call but remains non-exact; an explicit 12-byte block copy also remains non-exact. Lifetime/stack-shape prerequisite remains unresolved.

The private candidate does not replace the committed source. No new native
row, completed adoption or runtime improvement is claimed. The existing
source remains byte-verified. Diagnostic sources and comparisons are retained
in ignored build/up-to-eighteen-each-20261102-1632/b2-02-*. The adjacent patch preserves the latest
private trial; direct-adoption and component-copy variants are retained too.
No shared header, compiler flag, pin, alias or gate change is attempted.
