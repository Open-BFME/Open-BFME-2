# PeerThread nine-slot ownership repair blocked by private data admission

Observed at BFME2 62227dccbdfa0c0a9fb7e4167e59600eea672489 with the verified
BFME1 checkout f98983a7d3bb405f1a4ba94bb6a2a168062a819d.

## Target facts

Retail DC0768 contains nine key pointers (b_locale through b_rank2v2).
Retail DC078C contains nine pointers to E025E0 + 20*i for i=0..8; the next
owned datum is s_lastExtendedInfoID at DC07B0, whose initial value is -1.
The complete E025E0..E02694 buffer extent holds 180 loader-zero bytes and
ends at the independently owned localIP global at E02694.

Room body 38AF29..38B1BB formats slots 0..6 and dispatches seven entries.
Thread_Function 38EDD7 has the two _snprintf destination pushes at 38F78E
and 38F79E: E0266C and E02680, which are array indices 7 and 8.
Its existing 388D61 call dispatches two entries using DC0784=keys+28 and
DC07A8=values+28. These are slices of the same nine-entry tables, rather
than independent integer globals. The receiver value at +54 remains an
opaque pointer; the donor spelling DualIndexedDispatchThunk does not
establish an original target owner.

The current source already declares nine buffers and keys but initializes
only six value pointers and writes indices 0/1 in Thread_Function. The
source-local offsets make the same s_valueBuffers name bind to incompatible
bases E025E0 and E0266C in the full gate.

## Reference repair reviewed first

BFME1 commit 9562b49dc1536757cd793d3cd7e68d43eccf2d1f (Define the two retail
slot arrays) was reviewed with its full patch and verification evidence.
Its native selectors, loader zeros and next datum establish two eight-slot
arrays in a different subsystem. Its data_rows/sizeof/pointer-relocation
verification is an applicable ownership recipe; its names, addresses,
count and subsystem are not BFME2 PeerThread identity evidence.

## Exact bounded trial

PeerThread.cpp.txt and proposed.patch preserve the complete trial. It keeps
private access and the existing nine-slot declaration, fills all nine value
pointers, changes the core writes to indices 7/8, and places the existing
60-byte table-slice dispatcher with the real table owner through friend
access. No new header, pin, alias, pragma, flag override or baseline is used.
The old dispatcher source and ledger row were not removed/repointed; this
trial was never admitted.

Normal explain_mismatch confirmed the complete Thread_Function 4914 bytes
and dispatch 60 bytes exactly. A diagnostic build with the refused proposed
data rows removed verified all 80/80 existing owner/room rows, 118 literals,
26 empty-string references and 27 imports. This is code-byte evidence only;
removing the proposal was not used to commit the repair or claim closure.

## Admission blocker and remaining debt

Normal build with the proposed 180-byte buffer and 36-byte value-table data
rows stops before code verification: both private-static COFF access-digit-0
names cannot be named from their TU by tools/data_rows.py::_cpp_data_access,
which intentionally admits only digits 1/2/3. This records the precise
false-reject/data-admission gap. No public/protected access widening or
verifier change was attempted. The Code and data_rows changes were restored.

The saved census reports the main owner with substantial inherited STL,
selected-provider, duplicate and unresolved debt, the room home linked, and
the old dispatcher with two unresolved invented interior globals. No current
link improvement is claimed; a future admitted repair must verify current
provider/consumer closure and tool-generated scoped data metadata.

The prior full native baseline was 73440/73440 bodies green, with inherited
DIR32 inconsistencies for this buffer and ShaderClass::_PresetAlphaShader
(DB6234 versus DB44B8). This proposal resolves only the demonstrated buffer
binding; ShaderPreset debt remains distinct. No full-gate success is claimed.

Evidence only: +0 recovered C++ bytes and no admitted data ownership.
Model gpt-6.1-sol; bounded trial t=12 minutes.
