# SpecialPowerModule tables 0x0085E080 (+0x10 interface) / 0x0084E868 (primary)

Landed: 56956c9dca's parent bfcbafae6b -- SpecialPowerModuleCtor.cpp and
SpecialPowerModuleDtor_Unresolved.cpp adopt the canonical
`SpecialPowerModuleClass.h` (inline `getSpecialPowerModuleData`, protected inline
virtual `getSpecialPowerTemplate`, row 0x493236). Primary mismatches fell from
slots 2,3,12,13 to 2,3; interface mismatches are now 0,3,4,8,16,17,19-24.

Blocked: every remaining slot is a rowed body under a placeholder name; moving it
onto the class with its interface name needs a name_lane approval
(`rename.py function --to-class SpecialPowerModule --new ... --approval-base REV`).
First blind votes cast in 56956c9dca (session spm-slots2) for table 0x00C5E080:
slot 0 isModuleForPower, 4 getReadyFrame, 8 setReadyFrame, 16 getInitiateSound.
They need a second, different worker's blind vote. Editing
SpecialPowerModuleClass.h voids those vote fingerprints: carry header changes in
the rename commit itself.

## Slot evidence (target facts)

| table | slot | RVA | body |
|---|---|---|---|
| primary | 2 | 0x493DA4 | snapshot-name getter, rowed free `?Rva00493DA4Get@@YAHXZ` (ConstIntGetters4.cpp) |
| primary | 3 | 0x493009 | xfer, rowed `?xfer@Rva00493009@@MAEXPAVXfer@@@Z` (placeholder class Rva00493009.h) |
| +0x10 | 3 | 0x251C08 | `m_pausedCount > 0` |
| +0x10 | 4 | 0x493AB7 | getReadyFrame: template + object + disabled mask (BitFlags<11>) + TheGameLogic->getFrame() |
| +0x10 | 8 | 0x10670B | ICF fold with DisplayString::setFont (needs fold-proof) |
| +0x10 | 16 | 0x493218 | getInitiateSound |
| +0x10 | 17,19 | 0x251C2C | shared body |
| +0x10 | 20 | 0x30F2C7 | ICF fold |
| +0x10 | 21 | 0x4932D5 | |
| +0x10 | 22 | 0x49329E | pause toggle: `if (!rva00493251()) { if (!m_30) { m_30=1; pauseCountdown(1);} } else if (m_30) { m_30=0; pauseCountdown(0);} ` |
| +0x10 | 23,24 | 0x4BF893 | shared body |

Interface placeholder names slot03, slot17, slot19-slot24 in
SpecialPowerModule.h also need votes before they can be respelled.

ElvenWoodSpecialPower 0x0085CE28 derives from this class and stays bridged
until these slots land.
