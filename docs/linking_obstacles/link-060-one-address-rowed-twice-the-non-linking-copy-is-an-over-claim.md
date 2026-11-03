### LINK-060: one address rowed twice; the non-linking copy is an over-claim
Status: Open (14 retired, leads below). Updated: 2026-10-27; inspected revision: b1071e9a26; index d1f046749a.
Evidence / affected units: a scan of `reverse/functions.csv` for `matched` rows sharing a `target_rva`
(notes without alias/ICF/fold/dup-of/object-symbol) against `reverse/link_status.csv` finds addresses
where one row's unit links and a second row's unit never did. The second row is usually an older
address-named view, a BFME 1 donor port or an StlSweepR3 sweep instantiation.
Completed (each `./build.sh` exact on the surviving owner, link_check LINKS for it, row recorded in
`reverse/deleted_rows.csv`, re_log `converted`):
- 0x00576DF1 `Rva00576DF1Ctor.cpp` (owner `Rva00576C4BDtor.cpp`, Impl ctor) 9caa4cbd11.
- 0x0006047C `Rva0006047CSeq.cpp` (owner `MilesAudioManager.cpp`) dd45d8c862; its two
  `g_Va00BBAB74/78` address globals are gone (`hatch_counters.py --update` not run).
- 0x004C121B `BfmeConv892_Rva004C121B.cpp` (owner `SymbioticStructuresBodySlots.cpp`) 93ba3a07a8;
  its stale `reverse/header_queue.tsv` GameLogic key is retired on 2026-10-27 through the
  vanished-source exception. Current history identifies the deletion as `67f241b840`;
  its sole row is tombstoned, and the surviving owner already includes the canonical
  GameLogic header. Evidence: `reverse/attempt_support/header-debt-004c121b-20261027/readme.md`.
- 0x000AF1C2, 0x005243FA, 0x00569450 (2360ac3cf8) and 0x005AE78A (476ee27be8): StlSweepR3
  `uninitialized_fill_n` units (stable_sort over a 1-byte record, `#pragma optimize`); their
  `__uninitialized_fill_n` pins, named only by those units, were dropped.
- 0x00331578 `Rva00331578` copy in `ThingTemplate.cpp` (owner `RadiusDecalTemplateAssign.cpp`, typed
  layout agrees with rowed assign 0x00330CDD and ctor 0x00330E5D) b84b538a13; ThingTemplate.cpp 20/20.
- 0x00502645 `StlSweepR3Rva00502645.cpp` (owner `StlportIntMapInsertFamily.cpp`) eab974b6f3 and
  0x004F715B `StlSweepR3Rva004F715B.cpp` (owner `stlport_pop_heap_rva004f7e61.cpp`) 3e5be5935c; the
  pins only they named were dropped.
- 0x0020F0B8 `StlSweepW5Rva0020F0B8.cpp` (owner `ParticleSystemDebugDisplay.cpp`, pair<AsciiString, int>
  ctor; ICF aliases in `Rva002214A6Dtor.cpp`, `ParticleSystemManagerRva001FCF11.cpp`) c1775868b0; its
  element copy-ctor pin dropped.
- 0x00594976 `UDPNonBlocking.cpp` and 0x00594B2E `UDPBroadcast.cpp` (owner `udp.cpp`, ZH
  SetBlocking/AllowBroadcasts). 0x00594A06 `UDPErrorMap.cpp` was retracted after its two callers
  (`Transport.cpp`, `Rva0059517FSend.cpp`) were respelled to `UDP::GetStatus`; `udp.cpp` now rows
  the ZH body itself (commit "Row UDP::GetStatus at 0x00594A06"), dropping its `/alternatename`
  and the 0x00594A06 pin. link_check 2026-10-27: udp.cpp 1,000 B, Transport.cpp 2,730 B,
  Rva0059517FSend.cpp 325 B, all LINKS.
Remaining / next check:
- 0x0057621A `Rva0057621ACtor.cpp` (4 rows): owner `Rva00575F38Dtor.cpp` rows the Impl ctor and
  funclets $L1049..$L1055, but `__ehhandler` 0x0079B403 and funclets 0x0079B3ED/0x0079B3F8 are rowed
  only in the address-named unit; rehome them (tu_map has no approved unit for them) before retiring.
  Tried 2026-10-26 (reverted): the owner object emits `__ehhandler$??0Impl@...` (row exact at
  0x0079B403) and `$L1057` (exact at 0x0079B3F8), but `$L1056` at 0x0079B3ED jumps to
  `??1Rva005CD7DA@@QAE@XZ`, the owner's inline +0x30 record dtor, which has no row; retail jumps to the
  39B body at 0x005CD7DA. That body has three spellings (`?rva005CD7DA@Rva005CD7DA` in
  `Rva005CD7DAMethod.cpp`, gen-alias `??1Wrap2000576C4B` in `Rva00576C4BDtor.cpp`, pin
  `??1Rva005CD7BDHolder`); it is most likely `??1Rva005CD7BD` (ctor 0x005CD7BD sits just before).
  Naming decision first, then respell the users and rehome all three EH rows together.
- 0x00217607 `GameFont.cpp` `Rva004738A0::set` (BFME 1 donor, unused in the unit): the STLport pair
  ctor in `Rva005C6CCC.cpp` links; ready to retire, but GameFont.cpp was edited on master (6db0d6d013).
- Now both copies link (other agents' LINK-035 repairs on master), so these are no longer over-claims
  but a which-name decision: 0x0052BBD7 (10c7278d38), 0x00587752 (282446c955), 0x005F9813 (16e13794ee),
  0x004F7D7F (392f9f6fe0).
- Naming decisions (the non-linking copy carries the better name): 0x005481F9
  `ObjectOrderQueue::setPatrolStartOrder` in `ObjectOrderQueue.cpp` vs linking `Rva00548117::rva005481F9`
  (`Rva005481F9.cpp`); 0x0048C7BF address-named `Rva0048C7BF` copy in `FlammableUpdate.cpp` vs linking
  `FlammableUpdate::rva0048C7BF` (`FlammableUpdateRva0048C7BF.cpp`) is ready to retire, but
  FlammableUpdate.cpp was just consolidated on master (f41e95506b).
- Not over-claims (genuine ICF folds of distinct functions; add a fold note, do not retire):
  0x001F81BF (ten default vector-holder ctors), 0x00313840 and 0x003140A4 (7B getters).
- StlSweepR3 copies that now also link (LINK-035 repairs) duplicate placeholder rows:
  0x00577EB2 (`RvaVectorDtorFamily.cpp`), 0x0022DCDA (`Rva0022DCDADtor.cpp`); also unlinked
  0x000B0298, 0x001DE3E3. Decide which row keeps
  the address (the STL spelling may be the better name; respell callers) before dropping one.
  Follow-up 2026-10-30 (base `150043baed`): retire the 0x001FDEBC sweep copy;
  its one-byte element and two helper pins are used only by that unit. The
  existing `Rva000427195::operator=` retains the full 31-byte range and binds
  the actual clear/copy owners; the native element identity remains unknown.
  All 194 provider rows and 32 EH graphs verify. Three ordinary previews
  retain LINKS. No linking or unique-byte gain is claimed.
  The outgoing batch audit is inconclusive: its index predates the current
  base and `Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt.
  Carry that affected consumer into the next scheduled census; full current
  consumer closure remains unverified.
  [Evidence and consumer audit](../../reverse/attempt_support/hashtable-1fdebc-overclaim-20261030-codexb.md).
- Multi-row units holding a second copy: DozerAIUpdate.cpp (0x00488C48, 0x0048AEC6, 0x00489DE3,
  0x00489E2E; DozerAIUpdate.cpp was edited on master in the last 6 hours, and tu_map approves it as
  0x00488C48's home), WOLBuddyOverlay.cpp (0x002B70B3), R5VectorDtorEHFramedPolymorphic.cpp (0x002D0F65), ProductionPrerequisiteAssign.cpp
  (0x00564CD4, 0x00565668, emitted COMDATs; its real blockers are op= copies).
Clearance: the surviving owners link in preview (link_check against index d1f046749a); the retired
units held 0 census-linked bytes, so no headline change is claimed.
Census confirmation: not claimed.

**Generated unwind duplicate cleanup (2026-10-26, inspected `39e752ed5b`):**
Retired `uw_gen_009.cpp`'s four 14-byte copies at 0x007A7724/32/40/4E.
The existing AssetManagerImplCtor.cpp rows from `f943117658` retain each exact
range; the current constructor and its full EH graph verify EXACT, and all
12 surviving rows pass. The strict-current parent preview remains LINKS
against index `5ce093a71a`. Tombstones and evidence are in
`reverse/attempt_support/uw009-parent-repoints-20261026.md`; LINK-095 records
the broader generated-harness cleanup and remaining blockers. No census gain
is claimed.

**Assigned retired-unit recheck (2026-10-26, inspected `2a45addda1806342ac5c52757f63be902dcd428e`):** `StlSweepR3Rva004F715B.cpp` is absent and has no current row; its retirement is recorded in `reverse/deleted_rows.csv`. The surviving `stlport_pop_heap_rva004f7e61.cpp` remains byte-exact and LINKS in the paired current-provider preview. The two hashtable over-claims at 0x001DE3E3 and 0x001FDEBC remain; their bounded emission cleanup is recorded under LINK-066 and does not settle ownership. Evidence: `build/c136-r3sweep/before-retired-004f715b.log`, `native-evidence-03.log`, `after-expanded-cohort.log` and `final-assigned-build.log`. No new retirement or census gain is claimed; the next check is the normal ownership/naming decision for the surviving duplicates.

**GUI-package recheck (2026-10-26, inspected `2a45addda1806342ac5c52757f63be902dcd428e`):** `Rva00576DF1Ctor.cpp` is absent; current history records its retirement as `febea697c2a`. The surviving `Rva00576C4BDtor.cpp` remains LINKS and passes all 25 byte rows. The two remaining constructor views now bind their 0x005CD7DA cleanup directly to that owner's existing `Wrap2000576C4B` destructor, clearing that record subset as detailed in LINK-085. The duplicate planning constructor and its three unique EH rows remain untouched. Approved ownership and coherent class naming are still prerequisites for retiring that duplicate; no row move or retirement was attempted here. Raw receipts: `build/c136-gui-w2/expanded-before.log`, `expanded-after.log`, `final-provider-build.log` and `build/link-report.md`. Census confirmation remains pending.
