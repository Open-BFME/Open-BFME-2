# Narrow ostringstream constructor: STLport 4.6 migration

Base: `cd1e14b147abcd7a5868d9ddcc893ebc70e31025` (2026-10-30). Scope:
`Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_ostringstream_ctor.cpp`.
No source paths, row names, addresses, extents, pins or debt registers change.

## Target facts and prior attempt

The default picker claimed this whole file. Its library-copy trial reproduced
three rows under 4.6 but had not tested the actual TU. The current TU owns nine
rows, totaling 1028 bytes, including the parent constructor,
stringbuf constructor, xsputnc, seekoff/seekpos, EH handler and three funclets.
The unchanged 4.5.3 control passes 9/9. The prior attempt in re_attempts.log
stopped at the proxy allocate/deallocate specialization compile boundary.

Retail's STLport version is documented in vendor/stlport-4.6/PROVENANCE.md.
The actual change selects the supported stlport46 header/patch layer and removes
the obsolete `_STLP_alloc_proxy<char*,char,allocator<char> >::allocate`
declaration. In 4.6 allocate is inherited from allocator; the old member
specialization is invalid. The existing deallocate declaration compiles and is
retained, as in the already migrated destructor TU. No shared header changes.
All nine rows gain migrated=stlport-4.6 through add_match --replace-existing;
the tool also records each verification in re_attempts.log. Existing comma
punctuation in one notes field is normalized because the tool rejects commas.

## Verification

- Whole-file normal build: 9/9 rows. Frozen-file check: all definitions matched.
- Parent EH graphs: EXACT 2; the three compiler-local ordinals are independently
  bound by the parent graph to the same existing native funclet addresses.
- Final strict preparation: 22/22 rows across constructor, destructor and
  stringbuf overflow/setbuf. Reusable receipts accepted; no census modified.
  An earlier preparation overlapped the add_match ledger writes and correctly
  refused moving inputs; the final preparation runs after those writes finish.
- External COMDATs: 570 -> 30. Every retained name/digest/size is identical;
  no COMDAT added, 540 removed (mostly old static constants). Undefined and
  weak external sets are identical. This comparison uses link_census parsing,
  with the original object saved before the migration.
- Ordinary joint preview against index 12b9e7a7c0, 2026-10-30 10:11:
  constructor LINKS 978 -> 978 authored bytes; destructor 418 -> 418;
  overflow/setbuf 567 -> 567. Total 1,963 -> 1,963, 3/3 LINKS.
  Existing unreferenced-helper diagnostics in the unchanged peers remain.
- Owning stlport queue no longer serves this file. check_csv passes.

## Remaining boundary

The staged-tree outgoing audit is INCONCLUSIVE (exit 2): its index predates
the base and 33 source objects lack current receipts, first
`Code/GameEngine/Source/Common/Rva003A5DA0Write.cpp`. Full affected-consumer
selection/loss checks remain unverified. Carry the migrated constructor,
removed helper/constants and their consumers into the next scheduled census.
No census gain, image-ownership gain or debt retirement is claimed.
LINK-140's wider old proxy-helper cohort remains separate work.

Scratch logs and object comparison: build/ostringstream-ctor46-codexb4/.
