### Projected-shadow pair header adoption rejects a semicolon on the next line

Status: Blocked on the adoption parser. Updated: 2026-11-04; inspected revision: `72e402b4e1`.
Affected unit: `W3DProjectedShadowManagerRva0010C145.cpp`; canonical `Rva000B3F84Pair` adoption reports `no private view found` because the definition ends with `}` and `;` on separate lines. Next: fix the span parser separately, then retry adoption and queue acceptance.
[Reproduction and consolidation context](../../reverse/attempt_support/projected-shadow-pair-adoption-20261104-codex5.md). No source, link or census gain claimed.
