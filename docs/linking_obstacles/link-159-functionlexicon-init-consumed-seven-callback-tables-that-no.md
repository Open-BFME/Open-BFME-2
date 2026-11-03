### LINK-159: FunctionLexicon init consumed seven callback tables that no object defined (2026-10-30, seat halilkkaya-lk8)

Status: repaired; census confirmation pending.
`Rva002D22CAInit.cpp` (FunctionLexicon init, 0x002D2457, 135 B) registers seven
native .data tables (0x009BC890/998/9C0/AC8/BAC/BC4/BDC) that the data ledger
lists as "unowned", so its census blockers were seven unresolved
`?g_009BCxxx@@3PADA` names. The earlier verdict (re_attempts.log 0x002D2457)
stopped at the Messenger.apt factory 0x005114C6, rowed as a virtual member:
taking `&Class::member` emits a vcall thunk. Binding the row's decorated symbol
through `__identifier` (as the ConstIntGettersAddr FieldParse tables do) is a
plain code pointer, so the table needs no alias or raw address. Fix: the TU
defines all seven tables from retail's words, 65 `{key 0, name, callback}`
records plus null records, each callback the ledger row at its native address
(IMECandidateWindowInput's 0x000910FB is the ICF-shared trivial body whose owner
row is `GameFileClass::Create`; ControlBarInput's 0x000D43D0 has its own row).
The element type is now a 12-byte `TableEntry`, so the spellings become
`?g_009BCxxx@@3PAUTableEntry@@A`; seven new data rows byte-verify. Verified:
`./build.sh` 1/1 row and 7 data rows; scoped DIR32 over the init and
FunctionLexicon.cpp OK; `link_check` 401 -> 536 B (init 0 -> 135,
FunctionLexicon.cpp unchanged). Follow-up for consolidation: the tables' proposed
home is FunctionLexicon.cpp (tu_map), with the init.
