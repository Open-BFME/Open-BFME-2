# GeneralAllocator snapshot Microsoft-header cleanup, 2026-10-29

Base: `addc18930ae4caf5e401b752b66ebc74fe01f7da`.
Source: `Code/GameEngine/Source/Common/System/Rva00034D10Snapshot.cpp`.

Replace the copied EnterCriticalSection/LeaveCriticalSection declarations with
the Platform SDK's windows.h and the local placement-new definition with new.
The two lock calls now cast the existing opaque pointer to CRITICAL_SECTION*.
The Microsoft-header auditor reports the source clean; its refresh API removes
the queue row containing three local definitions. No source path, ledger,
pin, alias or shared-header change occurs.

The original Windows prototypes promised throw(). Plain SDK declarations add
eight instruction bytes to the lock destructor's EH state handling. /EHsc
retains the original nonthrowing C API contract and restores exact code.
Including new also makes placement construction emit failure cleanup unless
Snapshot's constructor is known not to throw. The existing rowed constructor
at 0x00031570 in memory_pool.cpp only calls memset and initializes fields.
A TU-local __declspec(nothrow) declaration states this measured contract;
no provider definition changes. This is a source-level exception contract,
not a new call target or a substitute implementation.

Validation:

- The supported build verifies both rows, including the 865-byte parent at
  0x00034D10, and both named imports. Frozen-file checking passes.
- The parent's EH graph is EXACT (one checked, none inexact).
- Before/after objects retain all four external COMDAT name/digest/size
  triples, all 12 external symbol name/defined/value records, and zero weak
  externals. The placement-new COMDAT remains identical under the real header.
- Strict current link preparation passes. Ordinary preview retains LINKS,
  874 -> 874 authored bytes, against index 85f6b7f40c (2026-10-29 15:08 UTC).
  This is not a census measurement.
- The staged-tree batch audit exits 2: the index predates the base and the
  affected Common/0CreateAHeroManager21FE49.cpp consumer lacks a current
  receipt. Carry the snapshot and consumer into the next scheduled census;
  broader closure remains unverified.

Scratch evidence: build/snapshot-msheaders-codexb4/{before.cpp,before.obj,
new-nothrow-build.log,eh-final.json,facts-final.json,batch-audit-final.log}.
All failed variants were replaced by the independently verified final source.
No linked-byte or source-file reduction is claimed.

## Preserved targets handoff during preparation recovery

The shared targets document was claimed by another worker at recovery. Its
upstream content is retained; the original handoff is preserved here:

GeneralAllocator snapshot Microsoft-header cleanup (2026-10-29, base
`addc18930a`): replace three copied definitions with windows.h/new, preserving
2/2 rows, both imports, the EH graph and all four COMDAT fingerprints. The
source leaves the header queue. Strict preparation passes and preview retains
LINKS for 874 authored bytes. The older-index batch audit lacks a current
Common/0CreateAHeroManager21FE49.cpp receipt; carry the snapshot and consumer
into the next scheduled census. No census gain is claimed.
[Evidence and exception-contract proof](snapshot-msheaders-20261029-codexb4.md).
