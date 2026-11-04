# AudioLoopUpgrade xfer UpgradeMux adoption, 2026-11-04

Inspected `b3f5048fc9`. The consolidation picker claimed the approved TU and
its four clean donors. The fresh Upgrade subsystem planner reports 22 groups,
148 sources and no missing inputs; its AudioLoopUpgrade entries identify the
private-view prerequisites. No source path or ledger owner moved.

Repaired `AudioLoopUpgradeXfer.cpp`: include the canonical UpgradeMux header,
model the +0x20 subobject as a base, and retain the +0x28 interface using the
existing seed's ALU_Iface4 declaration. The handle remains at +0x2C. Invoke
`UpgradeMux::upgradeMuxXfer` as a qualified base call. Constructor/dtor target
facts in AudioLoopUpgrade.cpp establish these subobjects; this is not a new
original-name claim for the interface. The old view incorrectly instantiated
UpgradeMux as a member, preventing adoption of its abstract canonical class.

Verification:

* `./build.sh .../AudioLoopUpgradeXfer.cpp`: 1/1 functions matched (72 bytes),
  string/float/import verification passes.
* `find_declared_unmatched.py`: all defined functions already matched.
* `header_adopt_lane.py accept --class UpgradeMux .../AudioLoopUpgradeXfer.cpp`:
  PASS; retired exactly its one header-queue row through the owning tool.
* Explicit `link_check.py` preview: LINKS, census-linked 72 -> 72 bytes,
  index census 2026-11-04 02:25 at `5a13f2cd61`. This is a preservation
  prediction, not a new census or an increase in the headline.
* No data/code-identity keys for the changed source; no pins or aliases changed.

The initial TU dry run accepts no donors. Remaining prerequisites are the
seed's canonical UpgradeMux adoption, DieMuxData constructor sequencing,
module-data completion in the implementation donor, and reconciliation of the
other AudioLoopUpgrade partial views. This change removes only the xfer
member-versus-base prerequisite and its UpgradeMux header debt; it does not
claim the TU merge or broader LINK-168 family is cleared.
