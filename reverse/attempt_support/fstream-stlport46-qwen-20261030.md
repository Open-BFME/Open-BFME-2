# Two-argument fstream constructor STLport 4.6 migration

Base: 8ca3c9be51 (2026-10-30). The owning STLport queue serves
Code/Libraries/Source/STLport/FstreamDefaultProtectionNameCtors.cpp, five
existing rows totaling 528 bytes. BFME 1 reference freshness remains within
72 hours; its tracked 7a8a034afa7dd3530d9a99dc48cfec711626256c checkout is
preserved. No reference revision, shared-header content or // cl: compiler
flag is changed.

## Prior blocker and repair

The earlier marker-only move is recorded as C2244 at 0001FA40 in the attempt
log. It retained two 4.5.3-only proxy allocation specializations. That unchanged
failed trial is not repeated. The actual 4.6 header inherits allocate/deallocate
in this compiler mode; the existing ostringstream migration and subsequent
particle-writer migration demonstrate the supported removal of those obsolete
declarations. Select stlport46 and remove only those two proxy declarations.
All other suppression declarations and the // cl: line are preserved.

The source comments now distinguish the BFME 1 donor RVAs 0084C6F0/0084CEA0
from BFME 2 targets 0001FA40/000201F0. The existing three-argument counterparts
are at BFME 2 0001FC40/000203F0. No name or identity is inferred from equal
bytes; the existing recorded constructor identities and boundaries are kept.
The two-argument constructors still supply default protection 0x80 and retain
their hidden virtual-base flag and RET 0xC behavior.

All five rows are updated by add_match --replace-existing, preserving their
historical notes and adding migrated=stlport-4.6. No row, pin, source path,
RVA, extent or ownership is added. The owning queue no longer serves the file.

## Verification and limits

- Original control and migrated whole-file build pass 5/5 rows. Both parent
  EH graphs remain EXACT. Declared-unmatched, strict current preparation,
  CSV and whitespace checks pass.
- External code definitions fall 140 -> 134. Every retained code body and
  its relocation records are identical; no definition or undefined reference
  is added. The six removed code helpers are __default_constructed and its
  __true_type auxiliary for char, unsigned short and int.
- External definitions total 704 -> 160: the other 538 removals are old
  header-emitted constants (ios/locale/numeric_limits families). Retained
  code and the complete undefined-name set are identical. This inventory is
  not a current full-image proof that every outside consumer has a provider.
  Carry the six removed helpers and constant providers into the scheduled
  consumer/census audit; no registered data/identity-debt retirement is claimed.
- Ordinary file preview retains LINKS, 528 -> 528 authored bytes, against
  ccafe54d1d (2026-10-30 15:43). No new linked or recovered coverage is claimed.
  Broader consumer selection/loss verification and census confirmation remain
  open; a bounded preview is not a complete engine link or runtime test.

Qwen2.5-Coder-7B Q4_K_M was used only to inventory a small supplied diff.
It correctly identified the marker change, removed member names and lack of
whole-image proof, but falsely stated that compiler flags changed. A direct
before/after // cl: comparison proves them identical; that sentence was
rejected. The host established the header adaptation and verified the source.
The helper supplied no original-name evidence and wrote no game code. It ran
on four low-priority CPU threads and was stopped after the request.

Raw control/source/object inventories, all five verified sole-writer updates,
EH/strict/preview checks and the flags comparison are under
build/continuation-qwen-20261030-201608/. Requests and verbatim helper replies
are under W:/OpenBFME/diagnostics/continuation-qwen-20261030-201608/.
