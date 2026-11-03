# LinearCampaign erase: real STLport header prerequisite

Inspected base: `85e1c8d401`. Source scope claimed by the default picker.

Target facts: the ledger owns range erase at RVA `0x001EBDFA`, 51 bytes,
in `Code/Libraries/Source/WWVegas/WWLib/stlport_vector_bfmeassignrecord172_erase.cpp`.
The source previously redeclared allocator, vector, iterator tags and the copy
wrapper, then emitted erase through an artificial `bfmeAnchor...` function.
`LinearCampaignManager.cpp` already uses the real STLport vector declaration.

Change: include `<vector>`, retain declaration-only specializations for the
separately rowed copy/destroy providers, and explicitly instantiate range erase.
Remove the private STL declarations, handwritten erase and anchor. The existing
BfmeAssignRecord172 identity is retained; no class-family recovery is claimed.
No aliases, pins, ledger paths, protected registers or compiler flags changed.

Verification:
- `./build.sh Code/Libraries/Source/WWVegas/WWLib/stlport_vector_bfmeassignrecord172_erase.cpp`:
  1/1 matched, all 51 bytes and relocation checks pass; zero string/float/import issues.
- `find_declared_unmatched.py` on that source: all definitions matched, no
  artificial anchor remains.
- Ordinary `link_check.py` before and after: LINKS, 51 -> 51 bytes, using census
  2026-11-03 20:03 at `8661f15284`. This is a provider preview, not a new census.
- Narrow register search finds no donor keys in header/MS-header, identity,
  data, hatch or gate baselines; no key retirement is claimed.
- `git diff --check` passes. The normal commit/push hooks remain required.

Next: refresh the supported merge probe after this prerequisite lands. In
particular, the seed has declaration-only range-erase specializations; check
whether those suppress this donor's explicit instantiation. The other private
views, element-family identities and flag differences in the earlier handoff
remain independent blockers. No source-file reduction or linked-byte gain is
claimed by this prerequisite alone.
