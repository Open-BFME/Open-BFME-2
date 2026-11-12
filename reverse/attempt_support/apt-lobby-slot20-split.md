# AptLanLobby slot 20 and split refusal at c02a707f61

The constructor and destructor of Rva004444D2 install table RVA 0083E020.
Its 23 words and the panel owner's callback declarations identify a bounded
test. Extend the existing installer view using the slot order in
AptMpGameSetupRva00440BDF.cpp, with the slot 19 GameSlot parameter from
MpGameSetupSlots.cpp. Slot 20 returns Rva004444EBBase*. This experiment
does not establish a prototype for an uncalled pure slot.

With the unit's normal compiler flags, the probe table had 92 bytes and
23 relocations. Slots 1–12, 14–19 and 21 named purecall. Default true
for slot 13 (GameSlot*, const UnicodeString&) emitted B0 01 C2 08 00;
slot 22 () emitted B0 01 C3. Both had zero relocations. Slot 0 used
the compiler's deleting destructor. Slot 20 named
?rva004444EB@Rva004444D2@@UAEPAVRva004444EBBase@@XZ. Its 30-byte
allocation body also compiled in AptLanLobby.cpp with operand relocations
at +3 (operator new) and +22 (Rva004444EBObject vtable).

## Split before changing the member identity

The approved TU for 004444EB is AptLanLobby.cpp. Keep the old method name
for this trial. Prepare the destination by replacing its 004444EB skeleton
comment with the Rva0007DF07.h include and the factory classes and body
from VslotSmallBodiesR.cpp (spell its Int member as int).
Run tu_skeleton.py --split for that donor and TU with --prepared and
--dry-run. It identifies the correct single factory, but reports four
lost riders at two RVAs and refuses the split.

Two independently compiled objects give a regression case. Compile the
donor minus just the 004444EB method body, and compile the factory at
its destination. Inspect the decorated names separately:

| Folded RVA | Destination emits | Residual emits |
|---|---|---|
| 004E84A4 | ??1Rva004444EBObject@@UAE@XZ | ??1Rva0059F35EObject@@UAE@XZ |
| 005FAA31 | ??_GRva004444EBObject@@UAEPAXI@Z | ??_GRva0059F35EObject@@UAEPAXI@Z |

Each 7-byte destructor references the Rva0007DF07 table at +2. Each
28-byte deleting destructor calls its own destructor at +4 and operator
delete at +17. The residual lacks both 004444EBObject members. The
destination lacks both 0059F35EObject members. The split's lost/rider
selection groups these rows by target_rva. A regression test should keep
the second factory's decorated rows in the residual and independently
prove the first factory's rows at the destination, refusing loss of either
name. Baseline build: 78/78; baseline link preview: 5,331 bytes.
The table remains bridged pending verified source and a real link.
