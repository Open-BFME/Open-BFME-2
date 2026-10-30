# Narrow string record STLport 4.6 link repair, 2026-10-30

Inspected base: `1726d2b12a`. Source:
`Code/GameEngine/Source/Common/NarrowStringRecordCopyBFME2.cpp`.
Scope: 34 existing matched rows, 947 bytes; no source moves or added coverage.

## Blocker and bounded repair

The default link picker claimed 0x00079C23 and its complete source. LINK-140
records this unit among the consumers left without the 4.5.3 proxy<char>
allocate helper after its providers migrated to STLport 4.6. The fetched index
remains 85f6b7f40c (2026-10-29 15:08 UTC). The current original object requires
`?allocate@?$_STLP_alloc_proxy@PADDV?$allocator@D@_STL@@@_STL@@QAEPADI@Z`.
The history and earlier narrow ostringstream migration were inspected first.

A trial removing only the obsolete proxy specialization under 4.5.3 passes
34/34 byte checks, but emits a different 14-byte proxy body (digest
cc9d23f9cdf5) from the first copy selected by the link. Joint preview rejects
this unit while all four companion providers link. This trial is discarded.

The final source uses the supported stlport46 marker, removes the obsolete
proxy specialization and adapts the allocator declarations to 4.6's non-const
signatures. The object no longer requires the obsolete proxy member. The first migrated
trial retains the adapted allocator<char>::allocate suppression: this unit
links, but overflow/setbuf loses allocator COMDAT selection (4/5 preview).
The final source removes that suppression so the existing 4.6 allocator
helper can instantiate. The other suppressions are retained. This restores
joint closure while all 34 owned rows remain exact.

## Native signature and ownership evidence

The old const deallocate instantiation at 0x0046264A and the newly emitted
non-const instantiation have identical complete 20-byte bodies and relocation:
`837c240400740aff742404e80000000059c20800`, REL32 at offset 12 to `_free`.
Retail has `837c240400740aff742404e8d6e1bcff59c20800`. The row gate verifies the
actual relocation target and full extent. This is the library's signature
change, not a new application name. Upstream 4.6's `_alloc.h` declares these
allocator members without 4.5.3's const qualifier.

The obsolete QBE row is retired with a deleted_rows receipt; add_match admits
the native QAE instantiation at the same address and extent. Every other row
retains its identity, extent and metadata and gains migrated=stlport-4.6
through add_match --replace-existing. No pin or hatch is added. No original
application class name or BFME translation-unit path is inferred from this
library migration.

Two existing rows overlap pre-existing five-byte wrapper owners in
Rva0055011ACtor.cpp: 0x0054FF9B / ??1Rva00550083@@QAE@XZ and 0x0054FFA0 /
??1Rva0055011ADeque44@@QAE@XZ. Both native jumps reach 0x0054FF17; the
peer object names its existing Rva00660470Deque pin at that address, while
this unit names the rowed deque<BfmePod16> destructor there. The initial
notes-only replacement is refused for that existing overlap. The normal
--icf-owner option supplies each existing same-range peer to admit the
replacement, without changing either row's identity or adding alias/fold
metadata. This does not establish a new fold or resolve those duplicate
application views, and does not claim either peer as new recovered coverage.

The final object has 35 external COMDATs, as did the original. The only
changed same-name COMDAT is the unrowed default basic_string constructor
(73 to 80 bytes). The old const deallocator and npos data COMDAT disappear;
the non-const deallocator and allocator helper are added. All owned bodies remain byte exact.
All ten emitted parent EH graphs verify EXACT against retail, with no baseline
exception. Renumbered cleanup labels retain their existing parent ownership.
Broader provider/consumer selection still needs the scheduled census.

Scratch evidence is under build/narrow-record-link-20261030/: original.cpp,
before.obj, before-build.log, proxy-build.log, proxy-joint-link.log,
stlport46-build.log, admit-deallocate.log, repoint-*.log, resume-repoint-*.log,
object-facts-provider-final.json, allocator-provider-build.log,
eh-provider-final.{log,json}, strict-provider-final.log and joint-provider-final.log.

## Final verification

- Whole-source builds and each gated row update pass 34/34 rows (947 bytes).
- Frozen-file checking passes; the remaining unrowed anchor has its existing
  absent-from-retail marker. No unmatched reconstruction is retained.
- All ten parent EH graphs are EXACT.
- Strict current preparation passes, reusing its prepared object through the
  ordinary body, source and reference gates. It changes no census/index/status.
- CSV validation and diff integrity checks pass. The latter confirms identical
  address/extent sets, the single deallocator signature change and the required
  migration notes; all other row metadata is unchanged.
- The final joint preview with current narrow ios, overflow/setbuf, float-format,
  narrow money-put and narrow ostringstream objects reports 6/6 LINKS,
  5,457 -> 7,567 authored bytes. This unit contributes 850; the ledger's 947
  also includes compiler EH rows. This is a prediction against the older index,
  not a census headline gain.
- The allocator helper is 35 bytes and calls malloc and _S_oom_malloc; the
  preview reports it as an unreferenced difference from the 25-byte majority.
  The overflow/setbuf and ostringstream 21-byte node-allocator variants also
  remain diagnostic-only in this joint preview. Suppressing this unit's helper
  is a demonstrated joint failure, not a safe isolated identity cleanup.
  No identity key or debt is retired. Reconcile this cohort before removing
  these differing helper copies; broader consumers remain for the census.
- The staged identity gate reports one new shadow definition finding for the
  allocator helper; it is preserved as a known provider-cohort prerequisite.
  No baseline or whitelist is changed.
- The staged-tree batch audit exits 2 (INCONCLUSIVE). Its index at 85f6b7f40c
  predates the inspected base, and 27 affected source objects lack current
  receipts, first Common/NarrowStringRecord00427F75Helpers.cpp. Carry this
  selected unit and those affected owners/consumers into the next scheduled
  census. The six-unit preview does not verify that wider cohort.
