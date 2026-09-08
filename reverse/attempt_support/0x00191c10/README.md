# SegLine rendering research bank

This is an unmatched C++ candidate, not an executable claim. The matching ledger receives no row or pin from this bank.

The sibling `../../attempts/0x00191c10.cpp` is the donor-derived render implementation with a verified BFME2 texture-mode fallback: modes 0 and 1 have their own paths, and every other mode enters the tiled path. The target retains a final subtract before that fallback; its original C++ spelling remains unknown. The candidate still lacks the initial four-element, 16-byte constructor iterator at target offset 0x270, and differs in stack layout and later code generation.

The headers in `reference/shims/banked_segline` are local dependencies for this candidate only. Its compiler directive puts that directory first. Compile with `tools.build.compile_source` to a scratch object and inspect `?Render@SegLineRendererClass@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@ABVSphereClass@@PAVVector4@@@Z`; do not add a matching row until the full 16,018-byte target and every reference pass verification.

`comparison.json` records an independent recompilation: 15,730 candidate bytes, 153 relocations, 955 concrete bytes equal at the same offset, 14,163 concrete differences, and a 288-byte missing tail. A normalized instruction-shape score is deliberately excluded from the bank ranking. This is not close in byte terms.

A separate diagnostic using a real Matrix4 local inside the original Set_Transform member reproduced the constructor at offset 0x270, but introduced an extra final constructor. That diagnostic is not this bank and is not verified source behavior. The next useful anchor is the sibling StreakRendererClass::RenderStreak, whose donor matrix setup and restoration may clarify the original temporary lifetime.

Investigation: Luna geometry followed by Astra, with root review. No unused arrays, lifted assembly, speculative pins, or matching exceptions were added.
