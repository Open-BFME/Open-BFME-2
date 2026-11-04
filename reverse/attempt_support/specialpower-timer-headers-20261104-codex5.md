# Special-power timer header adoption, 2026-11-04

Inspected source revision: `2974791b3ec4f752bb409ee10d1c57f4be6a79b1`.
Published census/index: `a62ac1c10b`, 2026-11-04 07:28. These are scoped
source and preview results, not a new census or real-link measurement.

## Repaired scope

- `Code/GameEngine/Source/Common/Rva0049355ERatio.cpp`, RVA `0x0049355E`, 194 B.
- `Code/GameEngine/Source/Common/Rva00493AB7Ready.cpp`, RVA `0x00493AB7`, 103 B.

Target facts: both bodies call the const override walker at `0x00288609`
and read byte `+0x59` of its result. The existing canonical `SpecialPower.h`
documents the target parse table's SharedSyncedTimer field at that offset.
The previous private declarations placed it on Overridable, rather than
SpecialPowerTemplate. Both files now directly include the two canonical
headers and read `SpecialPowerTemplate::m_sharedSyncedTimer`. The Ratio
holder's pointer is const; Ready explicitly qualifies the walker receiver as
const. This preserves the target overload instead of binding the mutable
walker at `0x001E35DF`. No shared header was changed.

Verification:

- Normal `./build.sh` on both original sources and final sources: 2/2 exact;
  seven compiler float references verified, no string/import references.
- `find_declared_unmatched.py` before and after: all defined bodies matched.
- Original/final COFF graphs: identical external definitions and all sections,
  relocations, COMDAT policies and weak bindings except `.drectve`. Its size
  grows from 44 to 600 bytes because the existing ascii_string.h adds its seven
  established AsciiString/StringBase aliases. No alias was written or removed.
- `header_adopt_lane.py accept --class Overridable` on both sources: PASS,
  two queue rows retired by the owning tool.
- `header_adopt_lane.py accept --class SpecialPowerTemplate` on both sources:
  PASS, two queue rows retired by the owning tool; final source variant rechecked.
- Ordinary `link_check.py` on the two final sources: LINKS, 194 -> 194 B and
  103 -> 103 B; total 297 -> 297 B against the index above.

No source paths, ledger ownership, pins, compiler flags, data identities or
shared declarations changed. Four header-debt rows are retired; class-wide
adoption and source consolidation remain outside this repair's scope.

## Rejected preliminary trials

The default picker twice served Xfer's four-unit batch. Existing attempts
already document unresolved load/save class identity and deleting-dtor names;
no prerequisite had changed. The class claim was released without edits.

The supported unused-class discovery checked 12,959 GameEngine sources and
offered only Rva00628770Impl in BfmeWideResultForward.cpp. The apply tool's
compile correctly refused C2027: that declaration is used through m_impl in
PartitionRangeQueryCallView.h. The tool restored and byte-verified the original
and released its claim. No source edit survives. Include-aware candidate
discovery is the next useful check; this is not a gate false reject.

Two automatic Overridable swaps were also restored:

- AttackPriorityInfo_setPriority.cpp: the field-rename scanner refuses
  vendor/stlport/config/stl_dec_vms.h:50 as a trigraph/continued-line-comment
  include input, before a source trial. Recorded as a false reject, without
  modifying or bypassing that check.
- SpecialPowerStoreFind.cpp: the 114-byte findSpecialPowerTemplatePrivate row
  fails after private inline recursive override walkers become canonical
  out-of-line declarations. A future adoption must preserve the visible-body
  codegen required by both lookup rows; no frozen-header change was attempted.

These failed probes retire no debt and claim no linking gain.
