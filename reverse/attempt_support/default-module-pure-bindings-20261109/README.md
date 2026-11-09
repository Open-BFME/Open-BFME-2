# Default-module copy stages: retire sixteen linker aliases

Root recovery seat, 2026-11-09, inspected base 0dabbd0a8a. The served file
DefaultModuleTemplateCopyCtors.cpp contains five matched copy constructors
(435 bytes), eighteen pure-table linker aliases, and four registered
one-byte table owners. The whole file and Wind producer were read; frozen
checks pass. This repair retires sixteen actual aliases while retaining the
four owners and two final RenderObject aliases whose class recovery is open.

Target facts: each source producer below has zero-addend DIR32 operands to
VA 00C1C780. Its distinct +14/+18 compiler tables are four-byte SELECT_ANY
COMDATs, each with one relocated pointer to native __purecall (0003B810).
The twelve operands independently verify the addresses of all replacements.

| Producer constructor | Slot14 operand | Slot18 operand |
| --- | --- | --- |
| 0055BF21 | 0055BF3A | 0055BF41 |
| 0055BF4B | 0055BF87 | 0055BF8E |
| 0055F98A | 0055F9A3 | 0055F9AA |
| 0055F197 | 0055F1D3 | 0055F1DA |
| 0055F9B4 | 0055F9F6 | 0055F9FD |
| 003A5856 | 003A5877 | 003A587E |

Source facts: separate constructor stages use the existing Rva0055BF21,
Rva0055BF4B, Rva0055F98A, Rva0055F197, Rva0055F9B4 and namespaced Wind-base
compiler symbols. The native fold does not merge their source spellings:
adjacent +14/+18 stores and base/final stages retain distinct symbols, so
the compiler preserves retail's stores. No borrowed final RenderObject class
identity is asserted. Placeholder class names remain unverified names.

The private trial passes all five copies. Normal six-source verification
passes 25/25 code rows, 21 data rows and three exact EH graphs. Every retained byte, relocation
position, flag and COMDAT policy is identical after the exact sixteen-name
mapping. All data and external definitions agree, and five producer objects
are wholly unchanged. The only linker directive differences are the sixteen
removed aliases. Their sixteen hatch allowances are deleted; every other
register byte is preserved. No pin, identity row, shared header, class
declaration or source path is added or moved.

The downloaded index lists no outside consumer of a retired name, and none
remain in current Code text (`reference-scope.json`). The six-source preview
conserves LINKS 1,364 bytes at c885072a48 (2026-11-08 19:18). This scoped
prediction does not replace the broader outgoing audit or a current image.

The full data-index regeneration changes twelve existing metadata rows,
including C1C780's alias list. It preserves all 34,433 addresses, every
extent/section and all 2,354 explicit verified owners. The other accumulated
metadata changes are not independent data verification or recovery credit;
`index-audit.json` records the complete differences.

## Wind owners: precise remaining prerequisite

Both current Rva005FEA50Base compiler tables are already sixteen bytes,
but their last slots differ from retail. Native primary 81B5A8 ends at
003A5896; the compiler copy has __purecall. Native Snapshot 81B598 ends at
003A589E; the compiler copy inherits WindModuleInfo::DoXfer (003A547E).
The other Snapshot slots and both widths are correct.

Native 003A5896 is an eight-byte this-plus-1C tail-call to the exported
WindModuleInfo::DoXfer(Xfer&); 003A589E is its eight-byte this-minus-1C
adjustor. A proper own DoXfer(Xfer&) override is the concrete repair
hypothesis. Current rows are under Rva003A5896Forwarder with an int parameter
in VslotMemberForwarders.cpp and GapForwardersSeat8.cpp. The supported
to-class route rejects the namespace and int-to-reference change; the
read-only helper diagnostics are recorded in `proof.json`. A separately
reviewed identity transition and normal byte/provider checks are needed.
Do not add an alias or retract/re-add those rows to avoid that boundary.

Transferring either one-byte owner now would conceal a wrong last slot, so
both explicit rows remain unchanged. The RenderObject pair at C1D728/C1D758
also remains: its producer uses composition/raw stores and emits no direct
replacement table; native widths are 48/16 bytes. Its two final-stage pure
aliases stay with that class-recovery pass. These blockers are not a source
regression, and no full table, bridge-retirement, image or runtime clearance
is claimed here.

Published as 362b6b1740 on attempt two (37.5 seconds; rebase 5.8,
hook/push 31.7), after the first lost race at 47.1 seconds. Normal push
checks pass. Post-publication object proof passes again, comparing the
hatch register to the published commit's actual parent so unrelated
upstream retirements are not attributed to this change. All eight claims
are released.

The broader outgoing audit remains INCONCLUSIVE: index c885072a48 versus
base 7c6a144ce2699e6667c8de330e4a56923fac44f3; unchanged
ConcreteModuleTemplateCopyCtors.cpp lacks a current receipt. Carry that
consumer into the next census/image rather than claiming global link
closure. Wind's two method addresses also have no approved TU in the map
inspected for this pass; any future row rehome needs actual TU approval,
in addition to the namespace/signature identity transition.
