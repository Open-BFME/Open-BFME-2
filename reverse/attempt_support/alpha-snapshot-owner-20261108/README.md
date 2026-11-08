# Alpha Snapshot table owner repair, 2026-11-08

The existing data row at VA C1CDBC owned one byte named
_Rva003AEA15_v1c. That explicit owner overrode the already recovered
compiler table's extent, making the bridge refuse it as unbounded.
The existing Rva003ABC6E Snapshot COMDAT is a complete 16-byte table:
native targets [3ABCAD, B3FD0, 3ABC9F, 3ABCA5]. Native constructor stores
at 3ABC6E and 3ACEFC independently bind it at +1C; the verified 20-byte
primary datum beginning C1CDCC independently bounds the end.

The owner row now names that existing compiler table and emitter in
ModuleCtorChainsA_Rva003ABAF3_Rva003ABB93.cpp, with extent 16. The copy
constructor removes all three byte definitions and refers to existing
g_00C1CDCC/g_00C1C504 arrays and the Snapshot table. Its +18 reference
also uses the current CategoryModuleInfo compiler qualifier, replacing
the stale SecondaryModuleBase spelling at the same native C1C900.
The exact 3ACEFC constructor operand proves that replacement. No new
global definition, pin, alias, flag, function row or source path is added.

Normal whole-file verification passes all 37 code rows and 16 data rows
across the copy, emitter and array-owner files. Normal data_rows --verify
independently passes the two emitter data rows, including every byte and
all four relocations of the new owner. Frozen/new-variant checks pass;
there are no EH rows in this cohort. The 45-byte copy body, relocation
positions, flags and policies agree after only the four proved referent
normalizations. Exactly three definitions disappear; none is added.
The emitter's complete COMDAT/data facts remain unchanged.

Bounded replay changes one strong-definition and one unbounded-row
refusal to zero, with the compiler's own table already correct and no
bridge for this table. The picker lists all candidate names in a row:
CategoryTemplate5 is a separate offset-32 binding to C1C780; Snapshot
is offset39 at C1CDBC. No address ambiguity was demonstrated.
Current three-source preview is LINKS/1,177 bytes against c885072a48
(2026-11-08 19:18). The unchanged units' 740/393 bytes were fixed before
this pass; that older-census delta is not credited here. The copy's
pre-existing stale qualifier is now resolved and its 44 unique bytes link.

The companion index regeneration is the full output of data_ledger.py,
not a hand edit or selected-row patch. It refreshes 312 existing records
and adds one observed address, removes none, and preserves all 2,354
verified owners. Only this table changes extent. Other metadata reflects
accumulated matched-object changes and is not independent global-data
verification. The raw index must carry extent16: the bridge does not
use data_ledger.load's in-memory owner reconciliation.

Primary/factory tables still use existing raw-array providers. No
original enclosing class name, complete layout, fresh image, census or
runtime clearance is claimed. Next published real link must confirm
this table leaves both refused and bridged queues.
