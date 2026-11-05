# WallUpgradeUpdate health-bar caller adoption, 2026-11-05

Inspected revision: `a4e73d9ed3`. Scope: the health-bar caller in
`Code/GameEngine/Source/GameClient/DrawableHealthBarGate.cpp`, under the
picker's `class:WallUpgradeUpdate` claim.

The caller now includes the canonical WallUpgradeUpdate header. Its virtual
query uses the existing neutral `rva004AB3AE` declaration, whose interface is
at complete-object offset +0x24, instead of the private UpgradeMux spelling
`isUpgradeActive`. The partial primary-storage class and both private views
are removed. This does not establish an UpgradeMux relationship or a new
semantic method name. No header, provider, pin or alias changes.

Verification:

- `./build.sh Code/GameEngine/Source/GameClient/DrawableHealthBarGate.cpp`:
  1/1 matched, including string, float and import checks; RVA 0x0027601B,
  472 bytes.
- `find_declared_unmatched.py` before and after: all defined functions matched.
- `header_adopt_lane.py accept --class WallUpgradeUpdate` on this caller:
  PASS; the owning tool retired its single row from `reverse/header_queue.tsv`.
- Ordinary `link_check.py` on the final caller: LINKS, 472 -> 472 census-linked
  bytes; dependency cache current. Published index: 2026-11-05 05:17,
  `c95fcfcfcd`. This preview is not a new census or runtime measurement.

Remaining cohort: ModuleFactoryInit retains its recorded Module/ModuleData
include-chain prerequisite; GeometryUpgrade retains its private BehaviorModule
base conflict. The constructor unit still needs LINK-441's provider identities
before a canonical hierarchy can preserve its link result. These unchanged
blocked trials were not repeated. Their queue rows remain.

The caller's separate UpgradeMux queue row also remains: its class claim is
held by another worker. The old private view is gone, but acceptance still
requires the canonical include; coordinate that retirement with the owner.
