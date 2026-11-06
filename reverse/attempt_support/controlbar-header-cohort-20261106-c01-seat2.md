> Recovery publication: historical stopped-fleet investigation, not a new reproduction. Original claims were released. No source change or debt retirement is claimed.

# ControlBar header cohort: supported reconciliation boundary

Date: 2026-11-06. Worker: `codex-fleet-20261106-c01-seat2`; shard `1/30`.
Inspected tree: `64ff2f11655`. Model: gpt-6.

## Scope and verification

The default picker `python3 tools/next_work.py --claim --shard 1/30` served
canonical ControlBar adoption in the first 25 distinct sources of its queue.
The class, frozen header and cohort were claimed before the trial. Every
source passed `tools/find_declared_unmatched.py` before planning the trial.
`tools/check_csv.py` passed: 99,515 function rows, 9,320 symbol rows, 2,272 data rows.
The pinned BFME1 reference was prepared through `tools/worktree_setup.py`;
no official-upstream refresh was performed.

The supported command, run once and polled to completion, was:

```text
python3 /Users/mehmet/Projects/Open-BFME-2/build/fleet/20261106-pass3/verification_slot.py \
  python3 tools/header_adopt_lane.py adopt --class ControlBar \
  --header Code/GameEngine/Include/GameClient/ControlBar.h --apply --jobs 1 <the 25 sources below>
```

The wrapper passed the 25 explicit paths from the table through a Python
subprocess argument list. Environment used the shared VM wrappers, the
project virtualenv, `BFME_VM_WINEPREFIX=/home/bfme/.wine-pdb`, `BUILD_POOL=1`,
`BFME_CLAIM_NS=refs/claims/` and the worker identity above. The two-slot
scheduler was held throughout the tool's own layout trials and byte-gate
bisection. It returned exit 1 after approximately 128 minutes; no duplicate
verification or compiler runtime was started.

Result: **0/25 adopted**. Eighteen consumers stop in field reconciliation;
seven reach byte/data/include checks and fail. These are supported refusals,
not demonstrated false rejects. The header, sources, ledger and header queue
are unchanged. `git status --short` immediately after return was empty,
confirming the tool restored all temporary trials. No reconstruction is
banked as a partial, because no new body was written.

## Returned diagnostics

The tool abbreviates some compiler messages; the table distinguishes those
limits rather than inferring a complete hidden diagnostic.

| Source | Returned refusal |
|---|---|
| `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` | C2011: SubsystemInterface redefinition in the canonical header's parent include (tool output truncates the class spelling). |
| `Code/GameEngine/Source/Common/CreateAHeroManager.cpp` | C2011: SubsystemInterface redefinition in the canonical header's parent include (tool output truncates the class spelling). |
| `Code/GameEngine/Source/Common/GapJmpThunksSeat8.cpp` | C2953: StringBase template class has already been defined, reference/shims/bfme2_ascii/string_base.h:174. |
| `Code/GameEngine/Source/Common/Rva005399D0Check.cpp` | ControlBar::m_6C (+0x6C, 4 bytes) has no canonical field of that offset and size. |
| `Code/GameEngine/Source/Common/Rva005DA6F3Ctor.cpp` | C2039: rva0031D5F8 is not a member of canonical ControlBar (trial source line 111). |
| `Code/GameEngine/Source/Common/System/BuildAssistant.cpp` | Data rows: FAIL 1 of 1. |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp` | ControlBar::m_videoManager (+0xC, 4 bytes) has no canonical field of that offset and size. |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarCommand.cpp` | ControlBar::queueParent (+0x50, 4 bytes) has no canonical field of that offset and size. |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarCommandProcessing.cpp` | ControlBar::selectedDrawable (+0x6C, 4 bytes) has no canonical field of that offset and size. |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarConstructor.cpp` | ControlBar::m_videoManager (+0xC, 4 bytes) has no canonical field of that offset and size. |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarInitSpecialPowerShortcut.cpp` | ControlBar::m_videoManager (+0xC, 4 bytes) has no canonical field of that offset and size. |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarMultiSelect.cpp` | ControlBar::m_slice_pad (+0x0, 108 bytes) has no canonical field of that offset and size. |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarOCLTimer.cpp` | ControlBar::m_contextOCLTimerParent (+0x64, 4 bytes) has no canonical field of that offset and size. |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarReloadNotice.cpp` | ControlBar::m_videoManager (+0xC, 4 bytes) has no canonical field of that offset and size. |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarRva0031D230.cpp` | ControlBar::m_videoManager (+0xC, 4 bytes) has no canonical field of that offset and size. |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarSwitchContext.cpp` | ControlBar::m_videoManager (+0xC, 4 bytes) has no canonical field of that offset and size. |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarUpdateConstruction.cpp` | ControlBar::m_6c (+0x6C, 4 bytes) has no canonical field of that offset and size. |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarUpdateConstruction_Rva0053E4B1.cpp` | ControlBar::m_6c (+0x6C, 4 bytes) has no canonical field of that offset and size. |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarUpdateVirtual.cpp` | ControlBar::m_videoManager (+0xC, 4 bytes) has no canonical field of that offset and size. |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_populateSpecialPowerShortcut.cpp` | ControlBar::m_videoManager (+0xC, 4 bytes) has no canonical field of that offset and size. |
| `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/ControlBarVisibility.cpp` | ControlBar::m_controlBarAnimateWindowManager (+0x10, 4 bytes) has no canonical field of that offset and size. |
| `Code/GameEngine/Source/GameClient/GUI/InGame/Tactical/BannerUI.cpp` | TheBannerUI data check reports this unit does not compile; adoption tool truncates the underlying compiler diagnostic. Full compiler cause not established by this returned diagnostic. |
| `Code/GameEngine/Source/GameClient/GUI/Rva0050DE39Observer.cpp` | ControlBar::m_00 (+0x0, 528 bytes) has no canonical field of that offset and size. |
| `Code/GameEngine/Source/GameClient/GUI/TransitionStyleSlotsBfme2.cpp` | ControlBar::m_unreconstructed_000 (+0x0, 620 bytes) has no canonical field of that offset and size. |
| `Code/GameEngine/Source/GameClient/InGameUIDtor.cpp` | C1189 at ControlBar.h:99: include-order requirement: Include ControlBar.h before the short SubsystemInterface definition. |

## Small caller hypothesis and prerequisite

Target facts: `Common/Rva005DA6F3Ctor.cpp` calls
`TheControlBar->rva0031D5F8(name)` via its private inherited declaration.
`functions.csv` rows retail 0x0031D5F8 (38 bytes) as
`?rva0031D5F8@Rva0031D5F8@@QAEPAXPBVAsciiString@@@Z`, currently in
`GUI/ControlBar/ControlBar.cpp`. That body searches the receiver's +0x30
command-set table and returns a node's +8 value or zero.

The frozen header declares `findCommandSet(const AsciiString&)`; the existing
`symbols.csv` binding maps that decorated name to the same RVA. This supports
a byte-compatible caller hypothesis, but does not establish a real linked
provider. The coordinator checked its published index at `47fd56b879`
(2026-11-06 05:39 UTC): no strong, COMDAT, common or alternatename entry for
`?findCommandSet@ControlBar@@QAEPBVCommandSet@@ABVAsciiString@@@Z`.
Current source still defines only the placeholder row above. Consequently no
caller substitution was retained or trialed: replacing a bound call with a
newly unresolved canonical name would not satisfy the header adoption pass
test. Reconcile the existing owner's identity and its callers through the
supported naming path first; do not add another body, alias or pin.

## Next useful work and limits

Establish evidence-backed canonical fields for the named spans, respecting
retail layout and the shared base contract. Reconcile conflicting
SubsystemInterface/StringBase include worlds and the required ControlBar
include order in their consumers. Inspect the BuildAssistant data-row failure
and recover BannerUI's full compiler diagnostic before choosing a repair.
Then retry only consumers whose prerequisite changed and use the owning
`header_adopt_lane.py accept` path to retire passing debt. No queue line was
edited merely to influence selection.

No link preview, link batch audit, real link, image, menu, skirmish, save/load
or retail CRC result is established by this attempt. The recurring
0CreateAHeroManager21FE49 affected-consumer receipt gap remains open.

## Blocked-claim release receipt

Only the class-scope claim existed as an owning claim; its footprint covered the
header/cohort. All requested scope keys and the release result are retained here:

```text
Owner: codex-fleet-20261106-c01-seat2
Namespace: refs/claims/
Requested keys:
class:ControlBar
file:Code/GameEngine/Include/GameClient/ControlBar.h
file:Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp
file:Code/GameEngine/Source/Common/CreateAHeroManager.cpp
file:Code/GameEngine/Source/Common/GapJmpThunksSeat8.cpp
file:Code/GameEngine/Source/Common/Rva005399D0Check.cpp
file:Code/GameEngine/Source/Common/Rva005DA6F3Ctor.cpp
file:Code/GameEngine/Source/Common/System/BuildAssistant.cpp
file:Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp
file:Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarCommand.cpp
file:Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarCommandProcessing.cpp
file:Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarConstructor.cpp
file:Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarInitSpecialPowerShortcut.cpp
file:Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarMultiSelect.cpp
file:Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarOCLTimer.cpp
file:Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarReloadNotice.cpp
file:Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarRva0031D230.cpp
file:Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarSwitchContext.cpp
file:Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarUpdateConstruction.cpp
file:Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarUpdateConstruction_Rva0053E4B1.cpp
file:Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarUpdateVirtual.cpp
file:Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_populateSpecialPowerShortcut.cpp
file:Code/GameEngine/Source/GameClient/GUI/GUICallbacks/ControlBarVisibility.cpp
file:Code/GameEngine/Source/GameClient/GUI/InGame/Tactical/BannerUI.cpp
file:Code/GameEngine/Source/GameClient/GUI/Rva0050DE39Observer.cpp
file:Code/GameEngine/Source/GameClient/GUI/TransitionStyleSlotsBfme2.cpp
file:Code/GameEngine/Source/GameClient/InGameUIDtor.cpp

released 1: class:ControlBar

Exit: 0

Post-release claims.py list exit: 0
No claims listed for codex-fleet-20261106-c01-seat2.
```
