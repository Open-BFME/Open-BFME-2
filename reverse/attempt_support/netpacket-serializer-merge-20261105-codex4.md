# NetPacket serializer consolidation

Date: 2026-11-05. Seat: codex4. Prerequisite: b6d91beea5, already handed
to the fleet publisher. Scope: absorb FillBufferWithFrameCommand.cpp and
Rva0058CD6AWrite.cpp into Code/GameEngine/Source/GameNetwork/NetPacket.cpp.

The refreshed GameNetwork name_lane consolidation packet names only NetPacket
as the alternative for both whole-file donors. The ordinary tu_skeleton merge
rebuilds current routing in memory, approves their C-bracket placements, and
accepts those two donors plus the existing seed (203 approved rows in its
composition plan). The final ledger contains all 212 existing seed/donor code
rows, including the helper/funclet rows outside that plan count. The committed
TU map changes only the two source columns; no map regeneration is committed.
SOURCE FILES falls by two, with no new match or census claim.

Verification:

- Normal ./build.sh of the original seed passes 210/210; the final merged TU
  passes 212/212, including string, float and import reference checks.
- eh_verify.py reports 67/67 EXACT. find_declared_unmatched.py and class_gate.py
  pass. check_csv.py passes all three ledgers.
- A fresh pre-merge seed object plus the independently verified donor objects
  has the same 260 external COMDATs as the final object: identical byte/relocation
  digests, sizes, section flags and selection rules. No external definition is
  lost or added. No undefined name is introduced; the two serializer references
  become internally satisfied. Weak bindings are identical. The first comparison
  used an older cached seed object; rebuilding the original seed through the
  normal build corrected that baseline before accepting the comparison.
- data_check.py --converged passes all 11 covered data addresses with no second
  names or unjudged rows. Neither absorbed file nor the seed has a code-identity
  or data-check register key to transfer. The three existing seed alternatename
  hatches are retained, with identical weak bindings; no alias is removed.
- The header queue has no surviving row for the donors (the prerequisite used
  header_adopt_lane accept for both). The destination's MS-header queue row is
  refreshed without changing its debt. The merge rekeys functions, TU-map source
  columns and name_basis.source; there is no debt retirement in this commit.
- link_check.py at census index c95fcfcfcd (2026-11-05 05:17) reports LINKS for
  the final TU (33,923 own bytes) and unchanged Unicode donor (188). This is a
  prediction, not a census update or proof of a real executable link.

Tooling compatibility audit: the outgoing prerequisite since c1a5a2b848 has no
path changes; this merge has exactly the two absorptions listed above. The
fetched origin also has three unrelated incoming commits; these are outside
this batch. Combined old-basename/path searches in tools, hooks, workflows,
Code and doxygen find no active path consumer requiring edits. Active ledger
owners and name_basis.source resolve to NetPacket. Remaining old paths in
name_basis's historical rename columns, source provenance, attempt evidence,
the recorded link_status census and class-contract witness snapshots are
intentional historical records. The wrapper contract's outlier sources describe
the pre-adoption private layouts, not current providers; repointing those
witnesses would misrepresent their evidence. No generated report is promoted
to a new measurement. The publisher's normal outgoing batch audit remains
required, and the next scheduled census must confirm current provider selection.

Remaining work: the ordinary merger rejects Rva005910B4Write.cpp because its
composed declaration precedes NetHeroCommandMsg. Its earlier Unicode/EH byte
mismatch is also unresolved; that donor is unchanged. Mixed donors and the
existing list-copy identity obstacle remain outside this two-file batch.
Scratch logs and COFF comparison: build/netpacket-codex4*.
