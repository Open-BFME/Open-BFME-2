# HeaderTemplate Microsoft-header cleanup

The served ms-header task replaces the local C declaration of strlen with
<string.h>. The TU retains its existing CRT and intrinsic settings. Private
control/trial compilation preserves all 20 native rows and all 43 complete
external code definitions and symbolic relocations: no additions, removals or
changes. This includes each emitted caller, so no direct/imported callee
substitution is hidden by the declaration change. Normal and strict checks
pass all 20 rows; all five exception graphs are EXACT. The 86db074988 preview
preserves the unit's 706 linked bytes. This is a scoped preview, not a census.

The owning ms_header_audit scan finds zero local Microsoft declarations and
refreshes only this named file's queue entry. No gate, whitelist, pin, alias,
class declaration, ledger row or source path is changed. Original target
identity and native coverage remain the existing ledger's.
