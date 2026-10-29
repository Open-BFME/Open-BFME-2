# Canonical getter aliases need a supported admission path

Inspected 2026-10-29, base `d701d875b`; the reference-refresh commit above
that base changes no BFME 2 source. This was cleanup of existing matched
rows, not recovery of new bytes.

`GlobalGetterSingles.cpp` has two six-byte getters:

- RVA `0x0043C969`, VA `0x00E03314`, whose data-ledger owner is
  `GlobalA03314 *g_Va00A03314` in `Rva0050E9D3Enable.cpp`.
- RVA `0x00658200`, VA `0x00E09FA4`, whose owner is
  `T_007ea120 *g_Va0130A588` in `Rva007EB310Destroy.cpp`.

The trial declared those existing pointers, returned their values cast to
`int`, and removed the two old `/alternatename` pragmas. The normal build
passed all 46 rows and five data rows across consumer and providers. The
data-retirement tool confirmed both old keys absent.

The enforced hatch register then refused the two new per-file
`address_global` occurrence keys, even though they name existing owners
and replace two earlier spellings. This is an admission-policy prerequisite,
not a machine-byte mismatch. `name_globals.py` admits verified rewrites of
literal address casts; its current interface does not rewrite these named
aliases. No manual `--allow`/`--admit`, check edit or whitelist was used.

The source and the two attempted data-register deletions were restored to
HEAD, and all three claims were released. A diagnostic patch remains in
`build/continuation-20261029/getter-canonical-trial.patch` on this host.
The transformation above is sufficient to reproduce it when an approved
alias-to-owner rewrite path is available. Preserve the existing opaque owner
types; their historical EA names have not been established by this trial.
