# Constructor memset blocker status, 2026-11-05

Inspected source revision: `5480792e2e21669a6107feefa61e069ddca6e057`.
The default link picker served `Rva0051C0E7Ctor.cpp`, still listed in
`reverse/exit_link_blockers.tsv` under `?ji_006291ae@@YAPAXPAXHI@Z`.
History shows that `ce7565b2ca` already repaired that source: its `memset`
declaration precedes includes with `throw()`, preserving the constructor's
EH shape while calling the named CRT thunk. This pass made no source edit.

Current-source verification in this session:

- `find_declared_unmatched.py`: all defined functions already matched.
- `./build.sh Code/Libraries/Source/WWVegas/WWLib/Rva0051C0E7Ctor.cpp`:
  **7/7 rows exact**, including EH funclets/handlers.
- `link_check.py --fetch-index` retained the published census index from
  **2026-11-05 05:17**, revision `c95fcfcfcd`.
- Current-object `link_check.py`: **LINKS, 326 -> 326 bytes**.

LINK-509's claim that this constructor's legacy reference remains is stale.
Both its documented accessor repair and the constructor repair now await the
next scheduled real link's blocker refresh. This preview changes no census
figure and does not establish real-link clearance. No alias, pin or debt
register changed in this status update.
