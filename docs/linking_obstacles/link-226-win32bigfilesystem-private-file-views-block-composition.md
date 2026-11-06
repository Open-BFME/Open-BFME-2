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
