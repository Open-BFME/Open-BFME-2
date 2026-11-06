### LINK-229: Win32BIGFileSystem private file views block composition
Status: Open. Updated: 2026-11-04; inspected revision: e472447e0b.
Completed: adopted canonical File and RAMFile in the approved Win32BIGFileSystem.cpp; 33/33 rows match, two header-queue rows retired, preview preserves 2,011 linked bytes.
Remaining / next check: reconcile the archive-parser nested map and missing rva006045A2 declaration, opaque destructor inheritance/method views, and constructor STL declarations separately. Directory-list donor merged; 38/38 rows match and the link guard passes.
Evidence: [repair checks and post-adoption merge trial](../../reverse/attempt_support/win32bigfilesystem-canonical-files-20261104.md).
Census confirmation: awaiting; no linking headline gain claimed.

Directory-list consolidation removes one source file, preserves all rows and clarifies three local names. [Checks and compatibility audit](../../reverse/attempt_support/win32bigfilesystem-directory-merge-20261104.md).

2026-11-06 P8 experiment: the boot receipt
`2026-11-06T155837Z-boot_smoke-5f14318d61dc` reaches a virtual init call
past the one-slot Win32BIGFileSystem table, into XferMD5CRC's deleting destructor.
The retail table at 0x87A94C has ten slots and two kept ledger names. The Link
lane's generated bridge now emits a separately counted full SELECT_ANY copy for
each defined or referenced ledger name at that same unique retail address.
Conflicting retail-address assignments or slot sequences refuse the group.
Strong/common definitions, target-provider checks and displaced-slot evidence
remain enforced. No source recovery or runtime pass is claimed by this bridge.
Diagnostic topic proof and independent review are required before master landing.

P8's candidate `5be80f76ec` reached P9 instead:
`2026-11-06T165013Z-boot_smoke-297dfd3f4ffe` reports a null virtual call
from SubsystemInterfaceList::initSubsystem. Its SubsystemLegend spelling was
absent from the stale data ledger at retail table RVA 0x7D7678. The current
matched ctor/dtor rows use SubsystemLegend; the index still names Rva0022E0E5.

The follow-up derives current compiler vftable names from matched code rows:
whole-row bytes must agree outside recognized relocation fields; a complete,
zero-addend external DIR32 operand supplies the retail address. Only an
already indexed vtable address and its existing bounded retail slot run can
generate a copy. Conflicting name addresses refuse, and rejected row evidence
and bindings to unindexed addresses stay visible in JSON. No pin/name heuristic
or missing extent is guessed, and no persistent data-ledger row changes.
The normal regeneration command is `python3 tools/data_ledger.py`; the ledger's
active owner was LeonardBuhl@DESKTOP-TCMKKT2/10d48df1 when checked. This lane
leaves that scope alone. Branch CI and a new queue receipt must prove past P9.
