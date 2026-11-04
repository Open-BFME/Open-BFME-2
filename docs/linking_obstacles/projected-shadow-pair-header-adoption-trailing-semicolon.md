### Projected-shadow pair header adoption rejects a semicolon on the next line

Status: Cleared for this unit. Updated: 2026-11-04; original inspected revision: `72e402b4e1`.
Affected unit: `W3DProjectedShadowManagerRva0010C145.cpp`; both span parsers now accept C++ whitespace before the semicolon while refusing declarators. Canonical `Rva000B3F84Pair` adoption and queue acceptance pass; the unit retains all seven matched rows and exact EH data.
[Reproduction, checks and consolidation context](../../reverse/attempt_support/projected-shadow-pair-adoption-20261104-codex5.md). One header-debt row retired; no link or census gain claimed.
