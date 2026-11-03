### LINK-075: legacy Zero Hour `GameWindowManager` bodies kept `GameWindowManager.cpp` from linking
Status: Repair landed / awaiting verification. Updated: 2026-10-26; inspected revision:
`9f685c7696` (index 2026-10-26 19:02 at `5ce093a71a`).
Evidence / affected units: `Code/GameEngine/Source/GameClient/GUI/GameWindowManager.cpp`
owns two rows, `PassSelectedButtonsToParentSystem` (0x002C0978) and
`PassMessagesToParentSystem` (0x002C09DF). It also carried 23 verbatim Zero Hour
member bodies (ctor, dtor, the `gogoGadget*` builders, `winCreate`, `initTestGUI`, ...)
under `present-unmatched` markers. They emitted the class vtable and referenced
`GameWinDefault*`, `winDrawImage`, `winFillRect`, `winOpenRect`, `winDrawLine`,
`winFontHeight`, `winFormatText`, `winIsDigit/Ascii/AlNum`, `winCreateFromScript`,
`GameWindow::winSetOwner` and `GameWindow::winGetTooltipFunc`. None of these resolves
under a real name today, and the unit selected the wrong `registerTabList`. The
retail `W3DGameWindowManager` vtable 0x007C7C90 has no `winIsDigit/Ascii/AlNum`
slots (target fact). Slots 66-69 are the placeholders `Rva00314AE0`, `Rva00314B28`,
`Rva00314B75` and `Rva00314BC9` (`GameWindowRva00314AE0.cpp`); by Zero Hour
`GameWindowGlobal.cpp` shape they are probably `winDrawImage`, `winFillRect`,
`winOpenRect` and `winDrawLine`. Slot 73 (`Rva00314C93`, `VslotSmallBodiesB.cpp`)
is probably `winFormatText` (structural inference, a naming lead).
Completed: deleted the unmatched bodies, their markers and `testGrab`. Rowed owners got
pointer comments (`winCreate` in `GameWindowManager_dumpWindow.cpp`, and
`gogoGadgetListBox`/`ComboBox`/`TextEntry` in their own units). Also dropped the
`??_H` anchor block: the unit still emits `??_H@YGXPAXIHP6EPAX0@Z@Z`, byte-identical
to retail 0x00001423 (34 bytes compared). 25 hatches retired (23 `present_unmatched`,
2 `pragma_optimize`). Both rows pass `./build.sh`, and `find_declared_unmatched.py`
is clean. Preview: LINKS, LINKED 0 -> 151.
Consolidation prerequisite (2026-10-28, inspected `f5979062a5`): the initial
21-donor/70-row merge trial accepted no combination. Reconciled the lone-window
donor's duplicate GGM_CLOSE and its slot-58 send view with the seed; its 51-byte
body, COMDAT relocation identities and external symbols are preserved. The seed
and donor pass 7/7 rows and both preview LINKS. Full evidence and remaining
class/enum/STL blockers: `reverse/attempt_support/gamewindowmanager-consolidation-20261028-codexb.md`.
The retry exposed a second blocker: the shared header's lone-window field is
+0x28, while target code uses +0x2C. Extended the identical TU-local send view
with the native field and routed the donor's field accesses through it. Both
objects retain all COMDAT bytes, relocation identities and external symbols;
a scratch composed-pair probe passes 7/7 rows and LinkGuard with no findings.
The subsequent full merge accepted that pair: winSetLoneWindow now lives in the
approved GameWindowManager.cpp, removing one source file. All 70 scope rows
still byte-match across 20 files. The merged object's 546 COMDATs and external
dependencies equal the old pair's union, LinkGuard passes, and the 370-byte TU
previews LINKS. The other 19 clean donors retain declaration or byte blockers;
the handoff records them. Census confirmation remains pending.
The outgoing batch audit is INCONCLUSIVE: index 14dc3d2467 predates the base
a6874d8a6a and lacks per-object consumer names. Carry selected-provider and
unchanged-consumer verification into the next ordinary census; the passing
pair guard and byte/relocation comparison do not establish batch-wide closure.
Remaining / next check: rename the four vtable-slot placeholders above once their
bodies are checked against Zero Hour.
Clearance: pending.
Census confirmation: awaiting the next census.

Current follow-up (2026-11-03): a fresh baseline dry merge rejects all20
clean donors (119 approved TU rows). No source move is applied. Four consumers
already include the canonical GameWindowManager header; current-main normal
13-row verification and owning acceptance retire their four stale manager
queue keys. Other window/DisplayString/transition/list identity debts remain.
The text-entry anchor cleanup is a separate prepared change.
[Current scope, exact refusals and acceptance receipts](../../reverse/attempt_support/gamewindowmanager-current-pass-20261103/README.md).

The text-entry cleanup now passes current-main three-row verification and the
unmodified replacement LinkGuard: its exact function/EH body remains, the
artificial four-byte anchor disappears, and the function becomes an ordinary
NODUPLICATES definition. All four surviving providers retain bytes/relocations;
this explicit selection change is included in the outgoing consumer audit.
No image-ownership receipt or census improvement is inferred.
[Anchor removal, COFF properties and scope](../../reverse/attempt_support/gadget-textentry-anchor-20261103/README.md).
