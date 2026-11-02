# Flood-member component names and repair of older misleading labels

Model GPT-6. Source:
`Code/GameEngine/Source/Common/INI/INIAllocListParsers.cpp`.
The existing rows are the 74-byte member constructor at `0x0048DC07`,
125-byte `parseFloodMember` at `0x0048E022`, and 75-byte ArmyMember parser
at `0x0041F524`. None is new coverage.

## Six existing approvals applied

Normal `name_lane.py apply` recomputes the independent support, claims the
class/file and applies six still-valid agreements as one verified batch:

| Original field | Inferred name |
| --- | --- |
| m_14 | m_controlPointOffsetTwoY |
| m_18 | m_controlPointOffsetTwoZ |
| m_20 | m_controlPointOffsetThreeY |
| m_24 | m_controlPointOffsetThreeZ |
| m_2C | m_controlPointOffsetFourY |
| m_30 | m_controlPointOffsetFourZ |

The original independent voters and agreement IDs remain in the tool-written
registers; this pass adds no votes or reviewer identities. All six names are
inferred, not claims of original EA spellings. Source commit before rebase:
`ab5fd0b6e1ad697540356d88c1c528ef84e85751`.

## Exact partial reversion of an old unrecorded naming error

Commit `fca96242746249ad6d8e47128c94ecc6148423e4` correctly named two
ArmyMember percentages, but also replaced the same old offset identifiers in
the unrelated Flood record. Its `m_percentageOfArmyPhase2` and
`m_percentageOfArmyPhase3` at +0x08/+0x0C therefore became misleading.
There are no canonical or inferred basis records for these Flood-field names.

Only those two erroneous Flood-record substitutions are reversed to their
historical `m_08` and `m_0C` placeholders. The ArmyMember percentage fields
remain correct. This introduces no new inferred spelling. The float groups
are reformatted in the order already used by the native field table.

Target evidence is read directly from the retail PE at RVA `0x0084C850`:
seven 16-byte FieldParse records, including the zero terminator. They name
ControlPointOffsetOne/Two/Three/Four at offsets 0x04/0x10/0x1C/0x28 and all
point to the existing 81-byte `INI::parseCoord3D` at `0x0002F507`.
That source writes X, Y and Z in order. MemberSpeed at +0x34 names
`INI::parseReal` at `0x0002EFC0`. Thus the first triplet is coordinates,
while the six newly applied component names agree with the later triplets.

The 112-byte Flood table is inspected for semantics only; it is not newly
admitted as data ownership. The current consolidation report marks the TU map
stale, so its FloodUpdate assignment is not permission to move or row it.
No TU move, data row, pin, hatch or class-layout change is made.

## Verification

- Normal application: 3/3 existing functions and one existing data row pass.
- After the two-label restoration: normal and strict 3/3, same data row pass.
- Frozen-file checks pass before and after both changes.
- Bounded index984a4cdc4d preview retains LINKS274->274 bytes.
- Header/source planning grants no TU ownership; no source path changes.

No new matched bytes, measured linking gain or image-ownership receipt is claimed.

`t=9 model=gpt-6 lane=R budget=30m`

## Post-rebase publication checks

The rebase onto `1291df600d4fba21e9a60ef84de93c18d033f5ea` succeeds and
changes neither this source nor AGENTS.md. Worktree preparation pins the
committed BFME 1 reference `946f3c05a1b1e60448734e874a8f47f8017cfdb9`;
no independent upstream check was performed. CSV checks pass with 99,289 rows.
The refreshed planning report still marks the TU map stale and grants no move.

`rename.py check` reports six renames, zero problems. Header-dependency check
returns 0. Current strict preparation again passes all three functions and
the existing data row. Source tip for the explicit outgoing consumer audit is
`c1f5e4a7023a08164602b191a51af1cea0c66cd7`.

The audit returns 2 INCONCLUSIVE: its index `984a4cdc4d` predates the base,
and affected consumer `Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. That unowned consumer was not rebuilt. The obstacle register carries
this source and its affected consumers into the next scheduled census.

Normal submission records three further independently written proposals for
remaining neutral coordinate members and the Army parser. All validate, but
none newly agrees. Only their hashes are published; no reviewer is launched
and they produce no additional source change. Do not count them as landed names.

Additional receipts: `range-check.log`, `header-check.log`,
`post-rebase-strict.log`, `batch-audit.log` and `pending-submit.log`.
