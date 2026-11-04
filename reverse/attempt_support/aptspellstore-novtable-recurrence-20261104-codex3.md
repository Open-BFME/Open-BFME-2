# AptSpellStore forwarding-destructor regression recurrence

Inspected source: `8740450b929d4c4ac1a3f705a77603ff7d0f8a1c` on upstream
master; worker `yasinschroeder-codex3`, model GPT-6.1.

That commit removes `novtable` on the assumption that only the rowed
constructor/destructor owner matters. This consumer defines a force-inline
forwarding destructor, however: the rowed AptSpellStore constructor's EH
cleanup instantiates it. It therefore has observable object emission even
without a separate destructor ledger row. Its generated vtable references
`?v00@Rva0043D16F@@UAE_NW4ScienceType@@@Z` and
`?v04@Rva0043D16F@@UAEHXZ`, neither supplied by the native provider. The
out-of-line constructor still owns its vptr store. Restore the annotation on
this forwarding view and explain the EH dependency in the adjacent comment.
No names, ledger rows, aliases, class registrations or data change.

Verification against census index `2f0cb97f52` (2026-11-04 16:16):

- Before: link preview 1,137 -> 0 bytes, exactly the two unresolved names above.
- After: `./build.sh` passes 16/16, nine string literals and all ten funclet
  mappings; `eh_verify.py` reports EXACT 1, zero not exact.
- After: link preview 1/1 LINKS, 1,137 -> 1,137 bytes.
- `find_declared_unmatched.py`: all definitions already matched.
- `header_adopt_lane.py accept --class AptPlayer` passes again. Its queue row
  was previously retired through this tool; the regression had invalidated
  that outgoing acceptance and blocked publication. No queue row is edited.
- `git diff --check` passes.

Logs: ignored `build/aptspellstore-publication-{build,link,link-after,accept}.log`.
This is regression repair supported by byte/EH and current-object preview,
not a new census result. The original LINK-219 history remains applicable;
real-link confirmation and class-view consolidation are still pending.
