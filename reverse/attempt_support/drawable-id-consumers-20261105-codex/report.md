# Drawable ID getter consumer link repair

Inspected revision: `7d786ca949` (2026-11-05). Scope: the eight sources in
[sources.txt](sources.txt), all listed by the existing real-link blocker register.

## Target facts and change

The pin `?getID@Drawable@@QBE?AW4DrawableID@@XZ` agrees with retail RVA
`0x0055A88B`, but there is no object definition under that spelling. The ledger
already owns this seven-byte body as `?get@Rva0055A88BDwordField@@QBEHXZ` in
`Code/GameEngine/Source/Common/DispDwordFieldGetters.cpp`. The native body reads
a dword at `this + 0x100`; the provider's displacement and compiled definition
agree. `pin_consistency.py --symbol` reports consistent, and the provider's
scoped build passes 1/1 function checks. These facts establish the callable
provider and byte shape; they do not recover the opaque holder's class identity.

Each consumer now declares and calls that existing provider, casting the result
to its existing DrawableID enum when required. Four unused private declarations
of Drawable::getID are removed. Canonical headers, ledger rows, pins, aliases,
hatches, data definitions and source paths are unchanged. The Object::getID call
in addFactionBib remains untouched.

## Verification

- Before editing, declared-unmatched checks and the scoped build pass for all
  eight sources: 304/304 rows. The existing present-unmatched markers remain.
- After the first six edits, [build-after.log](build-after.log) passes 304/304
  rows across all eight sources, four data rows, 67 string literals, 19 empty
  string references, three float literals and seven named imports. The last two
  sources were still unchanged in that run.
- After editing the terrain-bib and ghost-object sources,
  [build-after-terrain-ghost.log](build-after-terrain-ghost.log) passes their
  56/56 rows, seven funclet pins, three string literals and two empty-string
  references. Thus all 304 rows have passing verification for their final inputs.
- Declared-unmatched checks pass for the final edits.
- [object-audit.json](object-audit.json) compares saved pre-edit objects with the
  final objects: all 1,938 external definitions and 1,933 external COMDATs are
  preserved. In each unit exactly one undefined external changes, from the
  missing Drawable::getID spelling to the defined matched accessor. Exactly one
  COMDAT fingerprint per unit changes. Raw COMDAT contents, sizes and relocation
  targets match after normalizing only that external-name substitution. The
  provider object defines the replacement symbol. This also checks unchanged
  unrowed bodies and inline providers in these objects.
- The [before](link-before.log) and [after](link-after.log) previews both report
  LINKS for all eight units: the same LINKED 30,229 -> 30,284 bytes against
  census `c95fcfcfcd` at 2026-11-05 05:17. The preview already accepted the old
  pin, so this is preservation evidence, not a measured link gain. The four
  InGameUI diagnostics were already present and remain unreferenced/nonblocking.

Commands: `find_declared_unmatched.py --fail` on the scoped source list;
`./build.sh` on that list and then the final two sources;
`link_check.py` on the same list before and after; and
`./build.sh '?get@Rva0055A88BDwordField@@QBEHXZ'` for the provider.
The COFF comparison uses `link_census._coff_symbols` and `_comdat_sections` to
compare definitions, undefined externals and every external COMDAT's raw bytes,
size and relocation tuples, normalizing local targets as the census does.

## Remaining work

The prior animation-sound repair is already on master. This batch covers eight
more of LINK-534's twelve original consumers. GameClient.cpp,
InGameUISelectDrawable.cpp and ObjectDoXfer.cpp were held by other workers and
were not edited. Verify removal of these eight sources' missing-name errors in
the next real-link run. No new real-link, census, boot or runtime result is claimed.
