# DeployStyleAIUpdate consumer header adoption, 2026-11-05

Inspected revision: `eb87c49e6a7212e4ab03948a5d9257600ccf8a14`. Picker: class-header adoption,
`class:DeployStyleAIUpdate`, five queued source files. Initial declared-unmatched
check passed for the whole cohort. No source paths, ledger rows, shared headers,
pins or aliases changed.

## Target evidence and implementation

The existing canonical header documents the target constructor/destructor stores,
0x4D8 allocation, member offsets and inherited slot 111 (RVA 0x00262D8F).
This pass uses those existing target contracts; it makes no new donor identity
or field-role claim.

- `DeployStyleAIUpdateXfer.cpp` now includes the canonical class and uses its
  existing fields. The 12-byte triple at +0x4C4 passes through a `Coord3DBase`
  reference, retaining the original Xfer overload and field order. Private
  DeployStyleAIUpdate and Rva0026AFDAMember definitions were removed.
- `ToggleDeploySpecialAbilityUpdateSlot24.cpp` uses the canonical class and
  inherited `rva00262D8F()` virtual, replacing the private `v111()` spelling.
- `ToggleDeploySpecialAbilityUpdateSlots23And24.cpp` removes its private
  DeployStyleAIUpdate/AICommandInterface and slot-padding views. The same
  inherited virtual and `aiIdle()` replace the private slot/member expressions;
  the compiler still adjusts to the +0x20 AICommandInterface subobject.

## Verification and register retirement

- `./build.sh` on all three final sources: **6/6 function rows byte-match**;
  string, float and import checks pass. The existing $L2845 funclet row is
  verified through the parent's EH data at compiler label $L3360, RVA 0x0078E60A.
- `find_declared_unmatched.py` on all three final sources: all defined functions
  already matched.
- `header_adopt_lane.py accept --class DeployStyleAIUpdate` passes all three
  consumers; exactly three queue rows retire through the owning tool.
- The same tool's `accept --class AIUpdateInterface` passes Xfer and retires
  its queue row; `accept --class AICommandInterface` passes the combined Toggle
  unit and retires its queue row. Total: **five header-debt rows retired**.
- `link_check.py --fetch-index` kept the local published index, census
  2026-11-05 05:17 at `c95fcfcfcd`. Final current-object previews: Xfer LINKS,
  304 -> 304 bytes; Slot24 LINKS, 183 -> 183; Slots23And24 LINKS, 316 -> 316.
  Combined preview: **803 -> 803 linked bytes**. These overlapping source
  claims are reported as the tool prints them, not a unique-address gain.
  No real-link or census headline change is claimed.
- `check_csv.py` and `git diff --check` pass.
- No touched-source keys found in the searched data-check, code-identity,
  MS-header, gate or hatch debt registers. Only header debt is retired.

## Remaining scope

The supported initial adoption trial restored two rejected files unchanged:

- `ModuleFactoryInit.cpp`: the shared base Module definition conflicts with its
  existing private Module class (C2011). Factory-wide reconciliation remains.
- `DeployStyleAIUpdate.cpp`: separate four-byte +0x4C4 field and canonical
  12-byte array prevent automatic field mapping. Its constructor composition
  also retains the earlier member-destructor/codegen prerequisite in LINK-277.

The Xfer header prerequisite in LINK-277 is now repaired. Next: reconcile the
seed's layout and constructor/destructor composition, then retry the supported
TU merge dry-run. No merge was attempted or claimed in this header pass.
