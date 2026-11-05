### LINK-040: the 172-byte `CarryoverUnit` vector is spelled as five element types
**Supported-fold boundary (2026-11-02, GPT-6, base `3799c53a99b`):**
The source/RVA scope was claimed and its frozen check passes. Normal
`class --fold Rva001EBEABElement --into CarryoverUnit --dry-run` refuses
before edits: zero constructor/destructor rows carry the placeholder class,
so its own-vftable-store proof has no input. The constructor/destructor pins
are call-binding leads, not that required proof. The opaque source's
nonvirtual destructor also needs reconciliation with CarryoverUnit's virtual
destructor, along with the helper twins already described below. No alias,
pin, checker change or source trial was added; no new link or census claim.
Do not repeat this fold without new element/ABI evidence or a supported proof
path. [Exact boundary and next prerequisites](../../reverse/attempt_support/carryover-fold-boundary-20261102/readme.md).

Status: Open. Updated: 2026-10-26; inspected revision: 10621f1b34.
Evidence / affected units: `StlSweepW4Rva001EBEAB.cpp` (`vector<Rva001EBEABElement>::_M_fill_insert`,
0x001EBEAB, 307 B with funclets) fails on unresolved element ctor/dtor/`operator=` and a non-retail
`_M_insert_overflow<Rva001EBEABElement>`. Retail 0x001EBEAB calls (target facts): 0x001EB79E
`??0CarryoverUnit@@QAE@ABV0@@Z`, 0x0037DEE4 `??1CarryoverUnit@@UAE@XZ`, 0x001EB84E
`fill<BfmeAssignRecord172>`, 0x001EB831 `__copy_backward_ptrs<Rva001EB831Element>`, 0x001EBA30 and
0x001EBAB4 (`BfmePod172` helpers) and 0x001EBD3B `vector<BfmePod172>::_M_insert_overflow`. So one
native element (the virtual-dtor `CarryoverUnit`, 0xAC bytes) is rowed as `CarryoverUnit`,
`BfmeAssignRecord172` (incl. `operator=` 0x001EB20E, vector dtor/erase/reserve/clear),
`BfmePod172`, `Rva001EB831Element`, `Rva001EB86EElement` and `Rva001EBEABElement`.
`re_attempts.log` 0x001EC9BD already notes the BfmeAssignRecord172 / Rva001EBEABElement split.
Completed: none (no edit; diagnosis only).
Remaining / next check: one `vector<CarryoverUnit>` family rename across the rows above and their
units (about 20 rows, 12 files, incl. `LinearCampaignCarryoverInsert.cpp`, `Rva001EC9BDResize.cpp`,
`StlportVectorClearForwarders.cpp`), with a shared `CarryoverUnit` view; check each renamed body
still byte-matches and that the POD-named helpers really are the same instantiation, not ICF folds.
Clearance: pending.
Census confirmation: not claimed.

Sibling family, same cause (K10, 2026-10-26, inspected revision 7790bd44c7): the 52-byte
`BfmeAssignRecord52` vector. `StlSweepW4Rva002BC47D.cpp` (`vector<Rva002BC47DElement>::_M_fill_insert`
0x002BC47D plus `Rva002BC8C9Vector::resize`, 382 B) fails on unresolved `Rva002BC47DElement`
copy ctor/dtor/`operator=` and a non-retail `_M_insert_overflow<Rva002BC47DElement>`. Retail
0x002BC47D calls (target facts): 0x002B90D6 copy ctor (rowed `??0Rva002B91EDElement@@QAE@ABU0@@Z`,
pinned again as `??0Rva002BC47DElement@@QAE@ABU0@@Z`), 0x002BADB2 / 0x002BADD8 / 0x002BBC7A
(`uninitialized_copy` / `uninitialized_fill_n` / `_M_insert_overflow` over `Rva002BBC7ARecord`,
`VectorOverflowRva002BBC7A.cpp`), 0x002B913D / 0x002B915A (`__copy_backward_ptrs` / `fill` over
`BfmeAssignRecord52`) and 0x002B707E `??1BfmeAssignRecord52@@QAE@XZ`. One element is spelled
`BfmeAssignRecord52`, `Rva002BC47DElement`, `Rva002BBC7ARecord`, `Rva002B91EDElement` (and
`Rva002B91BBElement` op= ICF row). `tools/rename.py class --name Rva002BC47DElement --new
BfmeAssignRecord52 --dry-run` refuses: BfmeAssignRecord52 is itself a placeholder, so the family
needs a real element name (or a sanctioned merge path) first. No edit made.

**Assigned-family confirmation (2026-10-26, inspected `58598f540fd3c84610304b3659ed382a4c05acca`):** both `StlSweepW4Rva001EBEAB.cpp` and `StlSweepW4Rva002BC47D.cpp` remain U3/L1/S1 with current native providers against index `d1f046749a`. Their retail calls still reach the CarryoverUnit and split 52-byte-record owners documented above. No source change or repeat of the failed forwarder/overflow-suppression trials was made. `build/c136-w4sweep/native-evidence.log`, `provider-rows.json` and the paired ordinary-preview logs retain the native references and row homes; all their rows pass `final-all-assigned-build.log`. Next check remains coherent element/row reconciliation, including the real `CarryoverUnit` name where independently supported, rather than adding more same-address placeholder names. Clearance and census confirmation remain pending.

**52-byte scope recheck (2026-10-30, codex4, base `53cb08f077`):** the
current-object preview against `12b9e7a7c0` still reports U3/C1/S1 for
StlSweepW4Rva002BC47D.cpp (382 authored bytes, six ledger rows). The frozen-file
check is clean. The split element/helper names and real-name prerequisite above
remain current; no source edit, forwarder retry, new pin or census gain is
claimed. The claim was released. Carry this provider family into the next census
after coherent element reconciliation; a placeholder-to-placeholder respell
still supplies no identity evidence.

**Scope check (2026-10-28, seat halilkkaya-lk3, inspected `91fe563172`, index `73061d9452`):**
StlSweepW4Rva001EBEAB.cpp and StlSweepW4Rva002BC47D.cpp are still unlinked in the census (U3/C1/S1
each). The `vector<CarryoverUnit>` respell was not attempted: one of its source homes,
`stlport_pod_vector_bodies.cpp` (the `BfmePod172` push_back, allocate, `__uninitialized_copy`,
`__uninitialized_fill_n` and `uninitialized_fill_n` rows), is file-claimed by another seat. The plan
needs one more fact than the entry above lists: the generic `_M_fill_insert` instantiation calls the
non-const `__uninitialized_copy<CarryoverUnit *, CarryoverUnit *>`, while 0x001EBA30 is rowed as the
const-first instantiation that `_M_allocate_and_copy<const T *>` uses, so the respell must give the folded body both names
(fold-proof, not a hand pin). The same shape now applies to the 104-byte `vector<ArmySummary>` family
(LINK-002, 0x003F53DA), whose element is established by the real-named `swap<ArmySummary>` row.

**Header-selection prerequisite (2026-10-30, codex5, base `31de1b9659`):**
LinearCampaignManager.cpp already selected the 4.6 environment through merged
donor markers but explicitly searched BFME 1's older STLport headers first.
Removing that include, and using the repository's 4.5.3 headers for
Rva001EBCD8Erase.cpp, gives both providers strict reusable receipts. All
33 rows, one data row, three strings and five parent EH graphs remain exact;
all 70 external provider fingerprints and reference sets are unchanged.
Ordinary preview reports both LINKS (1,753 authored bytes); no census gain is
claimed. This resolves the two providers' include-inventory obstacle, including
the seed receipt limitation recorded by later outgoing audits. It does not
resolve consumer selection or LINK-040's element identity. The initial merge
probe accepted no donors; incompatible private views/STL helper declarations
and four merged byte failures remain. Refresh the supported probe after this
repair. The staged audit remains INCONCLUSIVE on the older index and missing
current Common/0CreateAHeroManager21FE49.cpp receipt; carry the two providers
and their consumers into the next scheduled census.
[Evidence and remaining prerequisites](../../reverse/attempt_support/linear-campaign-header-selection-20261030-codex5.md).

**Erase declaration prerequisite (2026-11-03, codex):** the 0x001EBDFA provider now uses real STLport headers with an explicit instantiation; 51/51 bytes and its ordinary link preview remain exact/clean. Removing the seed's three erase suppressions preserved its 47 rows but selected a non-retail erase body; that trial was reverted and the restored seed links again. Reconcile erase codegen in the seed environment before removing the suppressions; element identity remains open. [Seed boundary](../../reverse/attempt_support/linear-campaign-erase-seed-boundary-20261103-codex.md). [Evidence](../../reverse/attempt_support/linear-campaign-erase-header-20261103-codex.md).

**Destructor merge prerequisite (2026-11-05, codex):** removed three unused 4.5.3 specialization declarations from Rva001EC349Dtor that conflict with the seed's 4.6 allocator signature; all six destructor/EH rows and the complete external symbol set remain unchanged. Next: rerun the supported merge; element identity remains open. [Verification](../../reverse/attempt_support/linear-campaign-unused-declarations-20261105-codex.md).
