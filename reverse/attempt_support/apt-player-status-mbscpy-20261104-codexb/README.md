# AptPlayerStatus objective-text CRT prerequisite

Base: `244934db8d`. Scope: claimed AptPlayerStatus TU and its three clean donors.
The current consolidation dry run accepts none: callback GameWindow declarations
conflict, objective text has incompatible `_mbscpy` C linkage, and the standalone
check body needs its `/Oy-` frame. `tu_views --dry-run --no-merge-check` additionally
finds the callback's 8-byte color view conflicts with the seed's 12-byte vector,
and Rva004266A1 differs by class key. No merge or source-file reduction is claimed.
The supported consolidation planner was run and its original-path alternatives
reviewed; they supply no approval beyond tu_skeleton's current in-memory map.

## Repair and target evidence

Replace the objective-text donor's hand-written `char*` `_mbscpy` declaration
with `<mbstring.h>` and explicit unsigned-character pointer casts. Keep the
header's non-import declaration for this call, matching the containing TU.
Retail parent RVA `0x004E4553`, size 167, calls RVA `0x00629176` at RVA
`0x004E45D7`. The existing import-thunk row and `__mbscpy` symbol identify that
6-byte thunk as `msvcr71.dll!_mbscpy`, IAT VA `0x00BBA6D0`.
No donor naming or layout inference is needed for this repair.

## Checks

- Normal builds before and after: all 3/3 function rows exact. The source's
  compiler-local funclet label renumbers; the parent EH graph resolves it.
- Frozen-source checks before and after: all definitions already matched.
- EH verification: 1/1 EXACT, no missing object or baseline.
- Microsoft-header owning scoped scan with `--write-queue`: zero local
  definitions; removes only this source's one conflicting ABI queue row.
- [Before/after external object facts](object-facts.json): identical 10 COMDAT
  fingerprints/sizes, 1 exclusive definition, 9 undefined references, no weak
  aliases. Collected with `link_census.object_facts` and a neutral truth callback;
  the separate normal build supplies byte verification.
- `link_check --prepare-current`: strict receipt prepared for this source.
  Ordinary preview: LINKS, LINKED 177 -> 177 bytes, against the census index
  dated 2026-11-04 20:47 at `f12552d0a7`. This is a prediction, not a new census.

Next: retry the composition with this C-linkage conflict removed, then repair
remaining class declarations in separate verified commits. No source path,
ledger, pin or shared header changes in this prerequisite commit.
