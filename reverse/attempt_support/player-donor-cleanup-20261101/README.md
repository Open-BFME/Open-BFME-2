# Player donor-body cleanup

The served Player.cpp owns 12 matched functions (112 bytes, all relocation-free)
and the native TheTeamFactory global at VA E028BC (RVA A028BC). It has 73 known address
references and stays in place. Player is canonical; no replacement private
class, header or ABI is introduced. Existing header-accessor and ScienceType
copy emissions must remain available throughout this pass.

## Science-points donor body

The unrowed addSciencePurchasePoints body introduces two unresolved invented
helper names. It has no runtime/data incoming relocation in the original object
and no outside incoming edge in published index86db074988. The old ILT comment
is a donor assertion, not BFME2 target evidence. Removing this unverified body
and that comment preserves all 12 native functions and the owned global.

The original-source control has 410 external code definitions, the corrected
object 409. The only removed definition is addSciencePurchasePoints; every
retained complete body and symbolic relocation is identical, and nothing is
added. Normal/frozen verification passes. The unit still does not link: its
other donor methods, two wrong-selected copies and additional STL imports
remain. This is cleanup, with no authored-byte or census gain claimed.

## Wrong selected upgrade-query copy

The unrowed pointer-overload hasUpgradeComplete body is removed separately.
Its code has no runtime/data incoming edge in this object or outside incoming
edge in the published index. The census certifies this copy as non-retail; the
current preview no longer selects it. The existing native provider and pins
are untouched. All 12 functions and the global still verify, and all 408
retained complete code definitions/relocations are identical to the preceding
409-definition control. Only the wrong copy disappears; nothing is added.

The owning hatch counter retires one of this source's two same-label
present-unmatched entries. It also synchronizes an already removed alias from
upstream ffdd9456a9 in FakePathfindPortalBehaviourDtor.cpp; that extra shrink is
upstream work, not credit for this pass. No baseline key is hand-added.

The code-identity hook reports existing shadow divergences in other retained
helpers. Whole-object controls show they are unchanged, and their register is
not edited. The remaining science-vector copy and donor imports still block
the unit; no complete link clearance is claimed.

The first two-removal batch passes strict preparation of all 12 function rows
and the one owned data row. Source paths, six admitted aliases and the canonical
class header are unchanged. Its strict receipt and output are retained.

## Relation-map donor CRC

The obsolete unrowed PlayerRelationMap::crc body is removed independently.
The native four-slot BFDD90 table has the deleting destructor, loadPostProcess,
name getter and xfer providers; no CRC slot is present. The old empty CRC also
has no incoming runtime/data edge locally or outside incoming edge in the
published index. The rowed loadPostProcess is retained.

All 12 functions and the global still verify. Only the CRC definition is lost:
407 complete code definitions/relocations remain identical to the preceding
408-definition control. The owning counter retires its one placeholder hatch.
The preview has no new unresolved CRC and retains the remaining blockers.

## Player donor CRC

The unrowed Player::crc body is removed in its own commit. The canonical
native primary contract has loadPostProcess, GetSnapshotName and xfer, without
a CRC slot; the imported CRC has no runtime/data incoming edge in the object
or outside incoming edge in the published index. All 12 functions and the
global still verify. Only this definition disappears, leaving all 406 complete
code definitions/relocations identical to the preceding 407-definition control.
Its one present-unmatched hatch retires through the owning counter.

## Unverified Player transfer body

The imported, unrowed Player::xfer body is removed separately. This does not
claim retail has no transfer method: the native primary contract still has
xfer, and its source recovery remains open. This donor body has no incoming
runtime/data reference or outside incoming edge in the published index.

All 12 function rows and the owned data row pass normal/frozen/strict checks.
The object goes from 406 to 349 external code definitions: the donor transfer
and 56 incidental helpers disappear; every retained complete body and symbolic
relocation is identical, and nothing is added. Its single placeholder hatch
retires through the owning counter. The six existing aliases and canonical
class header remain untouched.

After all five removals, the preview still reports 28 unresolved names, one
losing science-vector copy and one wrong-selected copy, so the unit remains
unlinked. The bitset losing copy and the two invented science-points names
are gone. No census, authored-byte or full consumer clearance is claimed.

The preceding two-removal publication's broad audit is INCONCLUSIVE: the index
predates base33056a795c and affected AIBuildable.cpp has no current strict
receipt. Carry that wider scope into the next scheduled census.

## Static STL profile trial: not applied

Three private profiles add static-library mode, then malloc, then the usual
no-exception/CRT-import definitions. All three preserve the 12 matched code
rows and remove the eight STL DLL-import blockers, but their new-variant audits
introduce 13, 13 and 12 additional helper variants respectively. The profiles
also leave 20 unresolved non-STL names; none establishes a clean provider set.
No compiler flag, Code body, header, row, pin or register is changed by this
trial. The remaining donor users need reconciliation before such a profile
can be considered. Complete scoped verdicts are retained.

## Isolated donor delegate: buildBySupplies

The unrowed donor is removed after the saved reference audit finds only a debug incoming edge and no outside-index caller. All 12 function rows and the owned global still verify. The sole removed definition is this method; all 348 retained complete code definitions/relocations are identical to the preceding 349-definition control. Its one placeholder hatch retires through the owning counter. The removed donor text is evidence only, not a target-body or original-name claim.

## Isolated donor delegate: buildSpecificBuildingNearestTeam

The unrowed donor is removed after the saved reference audit finds only a debug incoming edge and no outside-index caller. All 12 function rows and the owned global still verify. The sole removed definition is this method; all 347 retained complete code definitions/relocations are identical to the preceding 348-definition control. Its one placeholder hatch retires through the owning counter. The removed donor text is evidence only, not a target-body or original-name claim.

This first delegate pair passes strict verification of all 12 functions and
the owned global. It retires two placeholder hatches and reduces the current
preview's unresolved names from 28 to 26; one vector losing/wrong-selected
copy still blocks the unit. No census gain is claimed. The preceding snapshot
batch's wider audit remains inconclusive on the older index and an AIBuildable
receipt; it is carried into the next census, without claiming full clearance.

## Isolated donor delegate: calcClosestConstructionZoneLocation

The unrowed donor is removed after the saved reference audit finds only a debug incoming edge and no outside-index caller. All 12 function rows and the owned global still verify. The sole removed definition is this method; all 346 retained complete code definitions/relocations are identical to the preceding 347-definition control. Its one placeholder hatch retires through the owning counter. The removed donor text is evidence only, not a target-body or original-name claim.

## Isolated donor delegate: isSupplySourceSafe

The unrowed donor is removed after the saved reference audit finds only a debug incoming edge and no outside-index caller. All 12 function rows and the owned global still verify. The sole removed definition is this method; all 345 retained complete code definitions/relocations are identical to the preceding 346-definition control. Its one placeholder hatch retires through the owning counter. The removed donor text is evidence only, not a target-body or original-name claim.

## Isolated donor delegate: removeObjectFromHotkeySquad

The unrowed donor is removed after the saved reference audit finds only a debug incoming edge and no outside-index caller. All 12 function rows and the owned global still verify. The sole removed definition is this method; all 344 retained complete code definitions/relocations are identical to the preceding 345-definition control. Its one placeholder hatch retires through the owning counter. The removed donor text is evidence only, not a target-body or original-name claim.

The final three-delegate batch passes strict verification of all 12 functions
and the global. It retires three further placeholder hatches and reduces the
preview from 26 unresolved names to 23, with the same vector losing/wrong-selected
copy still present. The preceding publication's broader AIBuildable consumer
audit remains inconclusive; this scoped check does not clear it or change the
census. The current AGENTS revision is unchanged (877b481530).

## Asset-transfer donor retirement: blocked, not applied

Removing transferAssetsFromThat alone preserves 11 of 12 code rows but loses
the seven-byte getDefaultTeam emission. The Object getters survive without
extra keepers. Three static member-address keepers restore the rows but add
four data bytes, sixteen BSS bytes and two initializer routines. A single
const getter keeper still adds four data bytes. A type-only/template-argument
trial adds no useful solution: only 11 rows match. No trial is applied.

The existing getter row/contract must be reconciled before retiring that donor
without trading coverage or adding runtime storage. The earlier Player
contract investigation also distinguishes its +160 getter from +2EC caller
views; matching bytes do not resolve that naming/layout question. All native
rows, source flags and runtime data remain unchanged by this investigation.

## Unrowed resetSciences and incidental vector assignment closure

The isolated unverified resetSciences donor is removed, preserving all 12 native
function rows and the owned global. The saved graph has no local or outside
runtime/data incoming reference to it. Its vector assignment was the sole local
user of the losing/wrong-selected _M_allocate_and_copy specialization. The
complete-object proof removes 18 definitions (the donor and 17 incidental
helpers), adds none, and preserves all 326 retained definitions and symbolic
relocations against the 344-definition HEAD control. The existing copy row,
explicit erase anchor, getter anchors, aliases and global stay in place. One
present-unmatched count retires through hatch_counters --update. This removal
does not assert retail lacks a reset method and does not claim a census gain.

Strict preparation verifies all 12 Player functions and its global, plus all
11 rows in current ThingFactory and ProductionPrerequisite. Player's preview
loses the science-vector COMDAT/wrong-selected blockers and retains 23 unresolved
names. The outside vector-assignment caller still uses ThingFactory's alternate
provider; that unit retains its existing wrong helper and other obstacles.
All three units remain unlinked in this bounded preview (0 -> 0). The removed
helper chain is therefore not globally unreferenced. The broader earlier
AIBuildable/old-index batch-audit scope remains inconclusive for the next census.
