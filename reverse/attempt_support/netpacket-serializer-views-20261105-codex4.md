# NetPacket serializer receiver reconciliation

Inspected revision: c1a5a2b848. Date: 2026-11-05. Seat: codex4.

The current GameNetwork consolidation packet lists the frame serializer
0x0058C80F (213 bytes) and serializer 0x0058CD6A (185 bytes) as whole-file
candidates for NetPacket.cpp. The committed map is stale; the ordinary merger
rebuilds routing in memory and approves their current C-bracket placements.
No map is regenerated or committed. Packet alternatives name only NetPacket.cpp.
The initial dry run accepts no remaining donor: both serializers conflict with
the canonical wrapper fields; the separate Unicode serializer fails bytes.

Target evidence already collected in netwrapper-header-debt-20261104.md links
type 3 dispatch and reader 0x0058DCEB to the canonical frame layout. The other
serializer's dword +0x1C, word +0x20, buffer +0x24 and length +0x28 agree with
reader 0x0058E20D and the existing NetHeroCommandMsg view in NetPacket.cpp.
The latter class grouping remains a structural inference, not new donor-name
proof. No ledger function or public symbol is renamed.

FillBufferWithFrameCommand now includes NetFrameCommandMsg.h and reads its
existing three payload fields. Rva0058CD6AWrite uses the TU's inherited
NetHeroCommandMsg view. Both use the seed's base-typed NetCommandRef layout
and explicit derived-message casts. They include the canonical wrapper header
instead of retaining a conflicting private definition.

Verification:

- Normal ./build.sh: 2/2 complete rows exact (398 bytes); string, float and
  import reference checks pass. Baseline build of all three donors: 3/3 exact.
- Each final object has exactly its original one external COMDAT; the census
  byte/relocation digest and all external symbol name/value/defined/type/storage
  records equal the saved baseline. No provider, undefined name or alias changes.
- find_declared_unmatched.py and class_gate.py pass both edited files.
- data_check.py --converged: 11 addresses, no second names or unjudged rows.
- link_check.py at published index c95fcfcfcd (2026-11-05 05:17) reports both
  LINKS, 398 -> 398 bytes. This is a preview, not a new census measurement.
- header_adopt_lane.py accept --class NetWrapperCommandMsg passes both and
  retires exactly their two header-queue rows through the owning lane.
- The post-reconciliation ordinary merge dry run accepts NetPacket.cpp and
  both edited donors. The remaining Rva005910B4Write.cpp trial has an additional
  composition declaration-order error; its earlier byte mismatch remains
  unresolved. It is unchanged. No merge is included in this prerequisite commit.

No production path changes occur in this commit. Code/data identity and hatch
registers retain their owners; only the owning header queue loses its two
passing rows. Scratch receipts are build/netpacket-codex4*, including original
objects and both dry-run logs. SOURCE FILES and census figures are unchanged.
