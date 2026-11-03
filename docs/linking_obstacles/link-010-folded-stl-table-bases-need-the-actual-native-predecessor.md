### LINK-010: folded STL table bases need the actual native predecessor

**Status: Blocked on supported native data-placement / ownership reconciliation.
Updated: 2026-10-25; inspected revision: `4f111811802`.**

- **Evidence / scope:** [the signed-reference handoff](../../reverse/attempt_support/stl-tenscale-predecessor-link-20261025/readme.md)
  proves the full 640-byte tenpow and 160-byte twoexp arrays in
  `stlport_stl_atod.cpp`, all six native DIR32 references, and a normal 5/5
  body control. A read-only replay of `a7637e3b22` re-proves inputs and
  reproduces all 98,202 status rows and the fixed-comparison credit.
- **Completed:** the cause is narrowed beyond symbol visibility. Tenpow's
  folded -4/-8 references precede its own COFF contribution and collide with
  Initialize_get_float's digits literal in the measured image. Retail instead
  reaches the end/padding of the canonical `__hex_char_table_hi` at VA BBC910,
  owned by `stlport_write_integer_backward.cpp`. Twoexp's -2 reference already
  has a valid named predecessor and passes the existing before-symbol rule.
  Game source is unchanged; no new credit is claimed.
- **Remaining / next check:** reconcile real native data placement and the
  existing hex-table owner without duplicating or over-sizing that datum.
  Establish a fresh approved TU/ownership plan before any consolidation; the
  inspected committed map supplies no approved merge for these two units.
  Verify both predecessor and array, other consumers, and one-to-one maps.
  Do not repeat visibility-only or expression changes, add an artificial
  prefix, or weaken the check. Clearance and census confirmation are pending.
