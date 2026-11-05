# W3DShadow consolidation prerequisite (2026-11-05)

Inspected revision: `5edd7860d9`. Scope: `W3DShadow.cpp`,
`AudioEventRTSAssign.cpp` and `W3DShadowManagerAddShadow.cpp`.

The supported planner surveyed the Shadow directory. Its committed map is
stale; `tu_skeleton.py` rebuilt current approvals in memory. The initial
merge dry run accepted no donor: both hit the seed's private StringBase
template when their shared ASCII header was included.

Target fact: the second guarded dispatch in the complete 61-byte
`Rva0009A2CDRun` calls the folded empty body at RVA `0x000B3FD0` with the
shadow-manager pointer as receiver. The StringBase spelling did not establish
the receiver's type or the original method name. Replace that private template
and its friend exception with the existing opaque `Rva000B3FD0` member
declaration. Its out-of-line owner is already rowed in `EmptyFoldTwins.cpp`;
no new name, pin, alias or code row was added. No donor name is asserted.

Verification of the prerequisite:

- `./build.sh .../Shadow/W3DShadow.cpp`: all 17 rows match; four unwind labels
  verified through the existing parent EH data; literal/import checks pass.
- `find_declared_unmatched.py` before/after: all definitions matched.
- `class_gate.py`: pass. `hatch_counters.py --update`: class exceptions 31 -> 30.
- `link_check.py`: LINKS, 1,237 -> 1,237 authored bytes against the
  2026-11-05 05:17 census index at `c95fcfcfcd`. This is a preview, not a census.
- A fresh supported merge dry run accepts the seed plus the assignment donor.
  The addShadow donor still fails declaration ordering (`Shadow::ShadowTypeInfo`)
  and requires reconciliation of its manager views and canonical headers.

The existing GlobalData and W3DShadowManager header-queue debts remain owned
by their sources. No protected debt is retired except the removed class hatch.

## Applied composition and path-consumer audit

After the prerequisite commit, the supported merger absorbed only
`Code/GameEngine/Source/Common/System/AudioEventRTSAssign.cpp` into
`Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadow.cpp`.
It repointed the assignment's function-ledger and existing TU-map source cells;
the map was not regenerated on disk. One source file is removed. The other
donor and all three mixed sources remain intact.

Final verification: 18/18 rows byte-match, including the moved 93-byte
assignment; parent EH labels remain verified. Declaration, ledger, class,
TU-ownership and case checks pass. The merger's census link guard passed with
the absorbed donor removed. The ordinary destination preview LINKS with 1,330
authored bytes against the same index; the additional 93 bytes already linked
in the donor, so this is no new linked-byte or census gain.

The audit covers this session's prerequisite and its one path move. Combined
searches for both donor basenames across tools, hooks, workflows, sources,
build.sh, doxygen inputs and path-keyed registers found no active consumer of
the absorbed path needing another update. Remaining old-path text is source
provenance and this historical evidence. No include names the absorbed file.
No alternatename pragma was removed. Existing data definitions and manager
provider declarations are retained; the assignment uses the same canonical
ASCII string header and passes the merger's combined COMDAT/link check.

Neither donor has code/data-identity or Microsoft-header debt to transfer.
The merger refreshed the destination's Microsoft-header scan and retained
the existing GlobalData header-queue row. The unmerged addShadow source keeps
its W3DShadowManager header-queue row. No debt retirement is inferred from the
deleted source, and no protected-register change accompanies the merge.

Next prerequisite for addShadow remains the nested Shadow type declaration
ordering and reconciliation with the canonical manager header and GlobalData
view. No partial body or additional path move is left in Code.
