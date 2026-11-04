### Projected-shadow pair header adoption rejects a semicolon on the next line

Status: Adoption span repaired; downstream layout parser blocks adoption. Updated: 2026-11-04; original inspected revision: `72e402b4e1`.
Affected unit: `W3DProjectedShadowManagerRva0010C145.cpp`; canonical `Rva000B3F84Pair` adoption now passes the span parser but reports `field renames: Rva000B3F84Pair: unterminated definition` from `tu_views.class_span`, which has the same horizontal-whitespace restriction. Next: repair that parser and retry ordinary adoption and queue acceptance.
[Reproduction and consolidation context](../../reverse/attempt_support/projected-shadow-pair-adoption-20261104-codex5.md). No source, link or census gain claimed.
