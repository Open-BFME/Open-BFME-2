# Script-slot deque cohort on STLport 4.6

Control revision: c16862543a. Model: GPT-6. Scope claims cover all four
sources below. This is header/ABI cleanup of existing matched code, not
recovery of the original slot element identity.

| Unit | Rows | Summed row extents |
| --- | ---: | ---: |
| Common/BfmeOwnerZKRelink.cpp | 20 | 1,271 |
| ScriptEngine/ScriptListSubrecordRemove.cpp | 18 | 1,051 |
| ScriptEngine/ScriptListTakeGroups.cpp | 5 | 417 |
| GameClient/MapObject_fastAssignAllUniqueIDs.cpp | 5 | 430 |

The extent sum is 3,169 bytes in both versions. These sums include repeated
ICF ranges and 0xCC bytes; link_check merges ranges and excludes 0xCC when
reporting its separate per-source preview figures.

The only C++ edits change each unit's `// stlport` selector to
`// stlport46`. Existing flags, private ABI views and source paths remain.
The default picker served the first unit; the other three are the complete
source cohort using BfmeScriptSlotAddress. Migrating the provider alone
would strand their old const-allocator calls. The prior 17/20 trial in
re_attempts.log identified this ABI boundary.

## Target and library evidence

Target facts: retail RVA 00068E15 is a complete 28-byte allocator. It tests
count zero, multiplies a nonzero count by four, calls the existing GameMemory
static byte allocator at 000307F0 with hint zero, and returns with RET 8.
The object's sole REL32 is at offset 15 and names
`?allocate@?$allocator@D@_STL@@SAPADIPBX@Z`.
The existing integer const allocator in AptTimeLineStats.cpp has exactly
the same complete body and relocation. The native deque map initializer at
0030D96F (156 bytes) and reallocator at 003B57E5 (250 bytes) call 00068E15
at relocation offsets 58 and 133 respectively.

Library fact: vendor/stlport-4.6/stlport/stl/_alloc.h:354 declares allocate
without the 4.5.3 const qualifier. The emitted pointer-slot specialization
therefore changes QBE to QAE. Its new complete body and relocation equal
both the old provider and the existing integer ICF peer. add_match admits
this QAE body with that existing ICF owner and the defining source as
fold-proof. The obsolete QBE ledger row is retired, with a deleted_rows
receipt so a union merge cannot restore it. No unique byte is gained or
lost and no pin or hatch is added. The migration does not establish an
original class, element name or BFME source path from a donor.

`rename.py function --dry-run` does not express this signature change: it
compares the unchanged identifier `allocate` and refuses "new name is old
name". No tool was changed or bypassed. Retiring the obsolete instantiation
and admitting the real complete 4.6 instantiation uses the normal row gate.
Every other identity and notes token is retained, gaining only
`migrated=stlport-4.6` through add_match --replace-existing. Folded rows
supply an existing same-range ICF peer.

## Object scope and verification

Control builds pass 48/48 rows. Supported isolated header trials for the
three companion units pass all their 28 rows under both versions; no trial
knob is needed. The migrated joint build also passes 48/48 rows, two literals
and one empty-string reference. Renumbered EH labels are resolved through
their verified parent graphs rather than hand-pinned.

The read-only control comparison normalizes allocator allocate/deallocate
constness, and TU-local relocation labels as link_census does. All retained
external COMDAT bodies, relocation offsets/types and external referents
are equal. External COMDAT counts change 64 -> 58, 77 -> 71, 62 -> 56,
and 76 -> 70 in the table order. Each unit omits the same six old unrowed
helper copies: two __stl_alloc_rebind specializations and two _STLP_alloc_proxy
allocate/deallocate pairs. No common COMDAT changes and no new COMDAT is
introduced after the documented signature normalization. External binding
sets differ exactly by those omissions. This is not a claim that whole
objects or every symbol name are identical.

The saved index's per-object touch sets identify only the four scoped
sources as owners/direct consumers of those omitted helpers. A source search
also finds the slot view only in these four units. These are bounded facts
about the inspected sources and older index, not full current-consumer proof.
`object-comparison.json` records the control/current object hashes and delta.
`verify.py` independently checks the complete native allocator, its existing
integer peer and the two current native caller edges in each of the four
objects, without compiling or writing a cache. Its peer check also needs a
normal ./build.sh of AptTimeLineStats.cpp; that unchanged object was already
available for this control.

No scoped code-identity, data, header-queue or Microsoft-header debt key is
retired. The map-object source's existing present-unmatched register count
is unchanged. No source moves, TU approval changes or baseline edits occur.

## Final checks

All four frozen-source checks report every defined function already matched.
check_csv passes with 99,009 function rows, 9,415 symbols and 2,235 data rows.
Strict --prepare-current byte-verifies 48/48 rows and produces reusable
receipts for exactly the four explicit providers. It verifies two literals
and one empty-string reference, with no skipped literal checks. EH verification
reports all five graphs EXACT, zero baseline entries and no missing objects.
All 48 current rows carry the migration token; a narrow ledger comparison
confirms 47 unchanged identities and exactly the QBE-to-QAE replacement.
The native proof and 255-copy comparison are rerun after preparation.

The final ordinary joint preview against index 85f6b7f40c (2026-10-29 15:08)
retains 4/4 LINKS and 3,085 -> 3,085 per-source bytes. The control and final
preview figures are equal. This is a prediction, not a new census result.
Census confirmation and unverified affected consumers remain with the next
scheduled measurement; no census gain is claimed.


The staged-tree outgoing batch audit returns INCONCLUSIVE (exit 2): index
85f6b7f40c predates the control/outgoing base and eleven affected source
objects lack current receipts, first ScriptEngine/Rva003B573ERva003B7F46.cpp.
The complete missing-source list and audit output are in audit.txt. This does
not establish full consumer closure or absence of losses. Carry the changed
provider, its removed const signature, omitted helper copies and affected
consumer scope into the next scheduled census.

## Commit-hook dependency check and remaining identity conflict

The normal commit hook expands the affected scope to 19 units and verifies
673/673 functions, seven data rows and all 112 EH rows EXACT. It also verifies
40 literals, two empty-string references, 83 floating-point literals and
110 named imports. Converged-data checks find no second name or unjudged row.

The commit hook reports a shadow binding conflict for
`?deallocateEntry@Rva003B573E@@QAEXH@Z` at 003B66D8. Its complete 131-byte
body and all relocations equal the pre-migration control. The REL32 at
offset 104 names `??1AsciiString@@QAE@XZ`; retail targets 00036410,
which agrees with the existing pin, while the destructor's function row
names 0048BA39. Neither identity was edited by this migration. The native
call and unchanged object digest are recorded in ascii-string-binding.json.
Reconcile the native StringBase/AsciiString destructor owners and fold
identity before retiring this conflict; no identity key or baseline is
changed here.

After the hook and rebase onto a5c01ba2ba, the c9fe2831a1 batch audit is
rerun once. It remains INCONCLUSIVE on the older index and the same eleven
missing ScriptEngine consumer receipts. audit.txt retains both outputs.
The rebase changes none of these four source files or their headers; the
read-only native allocator/caller proof passes again after the rebase.
