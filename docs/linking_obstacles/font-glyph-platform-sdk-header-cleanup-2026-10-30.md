### Font glyph Platform SDK header cleanup (2026-10-30)

At base `4a9c1bf77d`, the rasterizer, character-data loader and missing-glyph
check replace their copied glyph API declarations with the real Platform SDK.
The SDK's Windows 2000 API configuration exposes `GetGlyphIndicesW`; supported
opaque-handle configuration preserves the rasterizer's constructor ABI. The
owning auditor retires three queue entries covering nine local definitions.
Strict preparation passes 6/6 rows and eleven imports; EH is EXACT 1. All seven
external COMDAT fingerprints and all three external binding graphs remain
identical. Ordinary combined preview retains 3/3 LINKS and 1,754 authored
bytes against `12b9e7a7c0` (2026-10-30 10:11 UTC).

The staged-tree audit is INCONCLUSIVE on the older index and the missing current
`Common/0CreateAHeroManager21FE49.cpp` consumer receipt. Full affected-consumer
selection/loss checks and census confirmation remain pending; carry these
providers and consumers into the next scheduled census. No census gain or full
header-closure clearance is claimed.
[Configuration prerequisites and verification](../../reverse/attempt_support/font-glyph-sdk-20261030-codexb4.md).
