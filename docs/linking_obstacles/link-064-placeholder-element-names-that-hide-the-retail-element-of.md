### LINK-064: placeholder element names that hide the retail element of three STL families

**2026-11-01 bounded vector-overflow follow-up, base `64b496da64`, index
`12902e9e1b`:** The 49B copy constructor and 50B copy-backward twin are already
admitted. `StlSweepW4Rva00584405.cpp` still rejects its selected overflow COMDAT
and call (280 authored bytes); native 189B provider `0x0058431D` remains under
the old int/Arg5 spelling in `HordeMeleeSwarm.cpp`. A private actual member
specialization emits with an explicit instantiation. Best standalone resolved
score is 0.8929676511954994: empty temporary tags still force twelve local
bytes versus native eight and occupy different stack addresses. Existing
`Rva00030830FreeAllocation` fixes the free-call target without a new pin.
Production files and rows are unchanged; no clearance or census gain.
See `reverse/attempt_support/vector-overflow-owner-link-20261101/readme.md`
and its `candidate.cpp.txt` before retrying (blocked handoff: this RVA is already real-rowed). Do not reproduce the
already-LINKS 73B sibling as a new gain; preserve the real provider until exact.

**Status: Open. Updated: 2026-10-30; inspected revision: dd8a90d22f (earlier: d0d3b5054d, index d1f046749a).**

- **Evidence / scope:** retail call chains name the element of three families
  differently from their rows. Read with `tools/retail_body.py` callers/disasm.
  - **`vector<ProductionPrerequisite::PrereqUnitRec>`**
    (`ProductionPrerequisiteRecVectorInsertOverflow.cpp`, 183 B): the overflow
    0x004F5165 and push_back 0x004F5243 call `_Construct` 0x002CF99D. That body
    calls copy ctor 0x002CF5B1, whose only caller is 0x002CF99D. Both are rowed
    as `BfmeStringRecord002CF5B1` in `StringRecordCopyBFME2.cpp`. The helpers
    0x004F5097 and 0x004F50BD are also rowed under that name, so it is the real
    PrereqUnitRec: two words, then an AsciiString. The ZH view conflates this
    element with another 12-byte record. `ProductionPrerequisite.cpp` rows
    `__uninitialized_copy`/`__uninitialized_fill_n<PrereqUnitRec>` at
    0x004EE1E2/0x004EE20B. Those bodies call 0x004EE1A9, a word-field copy
    rowed as `PerTurnStats` in `V3PolyCopyCtors.cpp`. The symbols.csv pin
    `??0PrereqUnitRec@ProductionPrerequisite@@QAE@ABU01@@Z -> 0x004EE1A9`
    carries the same conflation. That ZH-flagged TU also emits an EH-enabled
    `_M_insert_overflow` (267 B) and an 18 B `_Construct`. It is first in link
    order, so its wrong copies are selected.
  - **`map<int, AsciiString>` in `Rva00566695Assign.cpp`** (179 B): the node
    that clone_node 0x005041D8 allocates through 0x005041B6 is 0x2C bytes
    (`push 0x2c`). That holds a 0x1C value, not `pair<const int, AsciiString>`
    (0x8). The rowed `_Construct` 0x00500CFE calls pair copy 0x00500839, rowed
    `pair<const int, Rva0050055D>` in `StlSweepW4Rva00500839.cpp`. That calls
    0x0050055D, a two-tree copy. The symbols.csv pin
    `??0?$pair@$$CBHVAsciiString@@@_STL@@QAE@ABU01@@Z -> 0x00500839` and the
    whole `map<int, AsciiString>` row family behind 0x00566695 are therefore a
    placeholder value type. It is shared with the genuine ignore-list
    `map<int, AsciiString>` (`UserPreferencesDeferredIgnores.cpp`, `PeerDefs.cpp`,
    `WOLBuddyOverlay.cpp`).
  - **`vector<Rva00584405Element>`** (`StlSweepW4Rva00584405.cpp`, 225 B):
    retail overflow 0x0058431D and copy worker 0x00583B11 construct through
    0x00583A72. 0x00583A1E is an assignment (`mov eax, ecx ... ret 4`, rowed
    `Rva002337F0::set`), not the copy ctor its pin claims. The 28 B element is
    four dwords, a byte at +0x10, then dwords at +0x14/+0x18. Its family is
    split across `Rva002337F0`, `BfmeStringRecord00111ACF` and
    `Rva00584405Element` rows.
- **Completed:** diagnosis only. No source or row was changed.
- **Remaining / next check:** each repair is a family rename, not a unit-local
  change. Retype the rows and callers together under one element and drop the
  wrong pins. Keep the genuine `map<int, AsciiString>` ignore family separate.
  For PrereqUnitRec, first rename the 0x004EE1E2/0x004EE20B rows and their
  0x004EE1A9 element away from `PrereqUnitRec`. Then the 0x002CF5B1 family can
  take the real name, and `ProductionPrerequisite.cpp` can stop emitting its
  overflow and `_Construct`. Related: the `vector<BfmePod32>` copy 0x0052C823
  (`Rva0056616BCopyDeferred.cpp`, 517 B) reaches 0x0052C27E, rowed
  `__uninitialized_copy<Rva003A6F70*>`, so its element is `Rva003A6F70`
  (LINK-002). Its provider file `stlport_pod_noexc_deferred_copies.cpp` was
  being repaired by another worker (98e2e4d836, Pod28 sibling) and was left
  alone.
- **Clearance:** none.
- **Census confirmation:** not applicable.

**2026-10-27 package c140 follow-up, inspected `a0b82f68445de8ab0254437ef7e97332ce48cfb0`, ordinary-preview index `bf3dd31211` (2026-10-27 00:39):** The current-provider cohort confirms the deferred ignore-family prerequisite. `getIgnores` at 0x003B224D has its tree-copy REL32 at body offset 174 targeting native 0x003B1EBB, while its decorated `_Rb_tree<int,pair<const int,AsciiString> >` constructor currently owns 0x0052D25D. The former is already rowed under `_Rb_tree<Rva003B1EBBElement>` in `StlSweepW4Rva003B1EBB.cpp`; 0x00383BAC is rowed as the int/int `_M_insert_00383BAC` and 0x00383EB2 as `Rva00383A28` destruction in `Rva0046A93EDtor.cpp`. These current owners preview LINKS, but the ignore unit retains L3/S2. The two pair-destructor digests remain split between WOLBuddyOverlay/PeerDefs and the deferred ignore/assign units. No consumer was rebound to a placeholder and no row or pin was changed. Next: reconcile those existing tree/value identities and the folded pair destructor before retrying suppression. No clearance or census gain is claimed.

**2026-10-27 codex pair-destructor follow-up, inspected `6f3fa807a0`, index
`73061d9452` (14:34):** Native pair cleanup 0x0077FA71 and its exact parent
graph prove the eight-byte destructor fold at 0x0029D7C2. Both proposed rows
pass unmasked byte verification, but admitting the destructor identity alone
regresses the currently linking `PeerDefs.cpp` (7,181 bytes). Its copy and
WOLBuddyOverlay's jump to the AsciiString destructor thunk; the ignore and
assign copies jump directly to releaseBuffer. Plain specialized destructor
declarations do not suppress MSVC's implicit copies. All source and ledger
trials were reverted; restored builds pass 164/164 and the paired four-provider
preview preserves the original linking status. Reconcile the destructor's
four providers before repointing the cleanup. The copy/insertion and two
distinct placeholder-value families remain open. No clearance or census gain.
Evidence: `reverse/attempt_support/ignore-pair-destructor-20261027-codex.md`.

**2026-10-27 vector follow-up, inspected `48ba8143a5`, preview index `bf3dd31211`:**
The default queue served `StlSweepW4Rva00584405.cpp` again. Its current object
still has the unresolved copy constructor and wrong selected overflow described
above (U1/C1/S1). No source trial repeated the documented `/Ob0` forwarder
failure. Reconcile the three existing element identities and the assignment
mis-pinned as a copy constructor before retrying. No source or row changed;
[scoped handoff](../../reverse/attempt_support/watchdog-donor-cleanup-20261027.md).

**2026-10-30 claudec3 ProductionPrerequisite.cpp follow-up, inspected `dd8a90d22f`, census 2026-10-29 15:08 at `85f6b7f40c`:**
`link_check` still reports `RTS/ProductionPrerequisite.cpp` (429 own bytes) as
not linking: unresolved `AsciiString::freeBytes`/`set` and
`__imp_` `__new_alloc::allocate`/`deallocate`, plus selected non-retail
`_Construct`, copy ctor and `_M_insert_overflow<PrereqUnitRec>`. The unresolved
symbols come from the `zh_ascii_outofline` shim and the ZH `PreRTS.h` chain.
A trial that only swapped the shim to `bfme2_ascii` still byte-matched 6/6 rows,
but it did not link and the `set` reference got worse, because `PreRTS.h` still
pulls in ZH's AsciiString. The trial was reverted and the restored build passes.
`reverse/tu_map.csv` already approves the 0x004EE1A9 PerTurnStats family
(0x004EE1A9, 0x004EE1D0, 0x004EE1E2, 0x004EE20B, 0x004EE233, 0x004EE6D0,
0x004EE9B1, 0x004EE9E9) into `Common/LivingWorldScoreKeeper.cpp`. Its rows still
use three placeholder element spellings across five files: `PrereqUnitRec` in
`ProductionPrerequisite.cpp` and `Rva004EE233AllocateCopy.cpp`,
`Elem003AF8C0`/`PrereqRec` casts in `Rva004EE6D0Insert.cpp`, and `PerTurnStats`
in `V3PolyCopyCtors.cpp`/`StlportConstructCopySiblings.cpp`. Three of those
files link today (953 bytes).
Next: give that family real `vector<LivingWorldScoreKeeper::PerTurnStats>`
instantiations in the approved TU, preview them with the three linking files,
then rewrite `ProductionPrerequisite.cpp` against a BFME 2 TU-local view like
the linked `ProductionPrerequisiteIsSatisfied_...cpp` and
`Thing/ProductionPrerequisiteAddUnitPrereq.cpp`. Do not use the ZH `PreRTS.h`.
No source or row changed. No clearance is claimed.
