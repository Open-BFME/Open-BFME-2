# Six FX module template writers: retail export signatures

2026-11-06; base `6462724dfad`. Status: repair verified locally, awaiting the
automated real link.

## Target facts

Each row was already virtual under its real class, with a placeholder identifier,
a pointer parameter and no const. Retail's exports give the exact spelling
`?writeINI@<Class>@FXParticleSystem@@UBEXAAVFile@@I@Z` at these addresses:

| Ordinal | RVA | Class |
| --- | --- | --- |
| 1945 | `0x00563D3F` | GpuDrawModuleTemplate |
| 1947 | `0x00561DB3` | LightningDrawModuleTemplate |
| 1948 | `0x0055E39E` | LightningEmissionModuleTemplate |
| 1951 | `0x0055ED5F` | OutwardEmissionVelocityModuleTemplate |
| 1958 | `0x0055EAAD` | SphericalEmissionVelocityModuleTemplate |
| 1960 | `0x0056499B` | TerrainCollisionModuleTemplate |

## Change

Parents, handlers and funclet parent notes are respelled in place and the old
names are tombstoned. No second body or alias was added. This is a hand rename
with export evidence, as in `8858a90aa54` and `96ddcc5a9d`, because `rename.py`
refuses a signature change beyond the identifier.

## Verification

- `./build.sh` on all six units: **25/25** rows exact, 32 literals verified.
- `link_check.py --prepare-current`: 6 providers byte-verified.
- `link_check.py`: 6 of 6 LINKS, 2,245 -> 2,245 bytes against index `d707d2f53b`.
  This is a preview, not an export-link check.
- A search of `Code/` and the reverse registers finds the old names only in the
  tombstones and in `reverse/wb_name_leads.csv`, which holds old name leads.

No real-link or runtime result is claimed. The last real link in the blocker list,
at `95341e20cc`, predates this change.
