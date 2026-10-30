# Module interface storage adoption, 2026-10-30

`Rva004AC7C9FindModuleObject.cpp` adopts canonical Module.h while retaining
the existing secondary interface at module+0C. A partial Module-derived view
reserves four bytes after the canonical eight-byte base and contains the
existing interface member. No original derived/interface name is inferred.

The complete native 32-byte helper at 4AC5F5 reads Object's module array at
+244, adjusts the module receiver by +0C at 4AC5FE, and calls interface slot
+7C at 4AC603. The slot declaration and its result handling are unchanged.
This is the same helper used by the partition query and environment update
in this whole source; its compiler-selected internal EAX argument must remain
unchanged. No public calling-convention replacement or new getter is added.

Private original/corrected probes verify every one of the eight ledger rows
and the parent's EH graph against retail. All eight external code definitions
and symbolic relocations are identical. `proof.json` records the complete
native helper, the probe checks and the actual strict-current comparison.
The actual source also passes the normal build, frozen-file check, header
acceptance and bounded link prediction before publication.
The bounded prediction conserves 410 linked bytes. The two local unwind
labels are compiler-renumbered; the verified parent EH graph still places
them at 78E360/78E368, without editing ledger or pin spellings.

Retire this source's one Module header key only through the owning acceptance
tool. No shared header, ledger identity, pin, hatch, data owner, source path
or build flag changes. The previous failed bare header swap lost the private
`m_interface` member; the separately evidenced storage view closes that
prerequisite. Existing placeholder identities and other private views remain.
This is a debt retirement; no census gain or complete-image audit is claimed.
Broader audit findings retain the old-index/missing-consumer qualification.
