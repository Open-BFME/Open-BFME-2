# GloriousChargeUpdate canonical list member, 2026-11-10

GloriousChargeUpdate.cpp now includes the canonical Rva0029FB3BMember
instead of a private class copy. Its four-byte ObjectID list at +0x88 is
constructed in the member initializer and destroyed by C++ member teardown.
The destructor body only resets the list; the separate PoolMember view,
manual destructor call and constructor's stack-address context cast are gone.
Two TU-local inline adapters retain the existing ObjectID iterator view.

Target facts: the constructor at RVA 0x004AD680 is 116 bytes and the
destructor at 0x004AD58C is 60 bytes. Both still match native, including
their callee addresses and table stores. The canonical member's reset and
destructor retain the native reset/free sequence. The existing empty
allocator-reference temporary reproduces the constructor argument without
introducing a zero store. RousingSpeechUpdate.cpp and ArrowStorm's constructor
provide the existing project recipe; this is not a claim about an external
donor's BFME 2 source path or original allocator type name.

Private before/after verification matches all 22 rows. Of 112 retained
COMDAT bodies, only the constructor/destructor digests change, reflecting
their new canonical callee spellings; their native bytes remain exact.
The private begin/end accessor copies disappear. The three-byte empty
allocator constructor is identical to six copies in index 5b5011469d
(digest 03ca90960a9c), so it introduces no new body variant for that symbol.

Normal verification: build.sh 22/22 bodies, two strings; eh_verify four
EH-bearing rows EXACT; find_declared_unmatched passes. The source's own
link_check verdict is **LINKS, 1,196 -> 1,196 bytes** against the 19:12
index at 5b5011469d. The owning header lane accepts the canonical member
and retires three queue rows, 5,641 -> 5,638; this source has no header
queue entries left. No flags, pins, aliases, extents, source paths or
function/data rows change.

The consolidation LinkGuard is not clean against that old index: both
the current baseline object and this candidate report exactly the same
already-published removal of `_vtbl_00C552A4`. That owner transfer landed
in 555ef46b43; cached consumer references still name the old array. No
additional guard loss appears. This is an index limitation, not evidence
that the whole link is verified. Carry forward the previous publication's
broader audit gap: six baseline objects lacked current receipts, first
ParticleSys.cpp, index 5b5011469d versus outgoing base 7cff6c1005. The
next census/image must judge those cases and actual table selection.

The primary GetSnapshotName identity and complete derived-table recovery
remain separate work. This change retires member/header debt; it makes no
new game-run or bridge-count claim.
