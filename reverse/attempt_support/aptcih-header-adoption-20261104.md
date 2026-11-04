# AptCIH consumer header adoption

Inspected base `2974791b3e` on 2026-11-04. Four source units now include
the registered class headers instead of their private class declarations:

| Source under Code/Libraries/Source/Apt/ | Accepted header-debt rows | Code rows | Preview linked bytes |
| --- | --- | --- | --- |
| AptAnimationPoolData__tickNewInsts.cpp | AptCIH | 1 | 237 -> 237 |
| AptDisplayList.cpp | AptCIH, AptValue, AptNativeHash | 8 | 1,324 -> 1,324 |
| AptDisplayListRegisterInst.cpp | AptCIH, Rva006E34D0 | 1 | 492 -> 492 |
| AptInput.cpp | AptCIH, AptValue, BfmeAptValue006DCD20 | 19 | 4,952 -> 4,952 |

Target ABI facts: the canonical AptValue table and existing headers place
AddRef/Release at slots 0/1 and the neutral `vslot13` at slot 13. The removed
private declarations used those same slots under local helper names.
AptCIH's payload access remains at +0x4C through the canonical `field4C`.
The pool constructor evidence in Rva006E34D0.h proves the eight-byte set
storage at +8, +0x20 and +0x28. The existing list API uses typed views of
those members. AptNativeHash's existing nested Entry definition remains
local, outside the now-included canonical outer class declaration.

Validation: `./build.sh` over all four final sources passes 29/29 rows,
59 string literals, and both AptInput funclet pins despite compiler label
renumbering. Frozen-file checks pass. `header_adopt_lane.py accept` passed
each of the nine class/source pairs and removed their header-queue rows.
Ordinary `link_check.py` previews all four as LINKS, 7,005 -> 7,005 bytes,
against the 2026-11-04 07:28 census index at `a62ac1c10b`. This preserves
the preview; it is not a new census measurement or a claimed linking gain.
No shared header, function ledger, pin, alias or source path changed.

Remaining prerequisite: adopting AptCIH in AptMiscObjects.cpp after replacing
its slot-0 helper with AddRef fails C2011: AptValue is defined both in
AptValue.h and the already-included AptObject/AptScriptFunction.h. The latter
still declares its own root and names slots 12/13 differently. The complete
AptMiscObjects trial was restored, retaining all its queue rows. Reconcile
that shared root header and its consumers before retrying this unit; this
is the same root-header prerequisite tracked by LINK-197.
