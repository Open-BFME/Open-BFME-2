### LINK-106: thread-wrapper calls used the Win32 import thunk's name

Follow-up verification (2026-10-27, `b8156cd386`): the default picker served
Rva000E6B99FreeBuffers.cpp's historical selected-copy blocker. All four
unchanged rows byte-verify. With current BfmeDX8ThreadLock.cpp, both ordinary
previews LINKS (229 and 247 authored bytes) against `bf3dd31211`.
[Scoped evidence](../../reverse/attempt_support/angle-math-headers-20261027-codex.md)
confirms the existing repair; census confirmation remains pending.

Status: Cleared in ordinary-preview scope; census confirmation pending. Updated: 2026-10-27; inspected revision: a0b82f68445de8ab0254437ef7e97332ce48cfb0.

Additional caller confirmation (2026-10-27, `0054abc1930e`):
WaterRenderObjInit.cpp passes all four matched rows and its shader data row.
Paired with the current BfmeDX8ThreadLock.cpp, both ordinary previews LINKS
(297 and 247 authored bytes), clearing the stale-index selected-copy result.
No source change was needed; [scoped checks](../../reverse/attempt_support/ww3d-window-sort-data-20261027-codexb4.md)
confirm the existing repair without a census or headline gain.

Evidence / affected units: Code/Libraries/Source/WWVegas/WW3D2/BfmeDX8ThreadLock.cpp emitted wrong copies of ?BFME_DX8_Thread_Lock@@YAXXZ, ?bfmeRva0011F5B0@@YA_NK@Z and ?bfmeRva0011F600@@YAHXZ. Code/Libraries/Source/WWVegas/WW3D2/BfmeDX8ThreadCheck.cpp emitted the wrong ?Rva0011F500@@YAHXZ copy, and Code/GameEngine/Source/Main/BfmeDfe6e4_rva00225492.cpp emitted the wrong ?rva00225492@BfmeDfe6e4@@QAEXXZ copy. All five native calls target RVA 0x006105D0, already rowed as ThreadClass::_Get_Current_Thread_ID in Code/Libraries/Source/WWVegas/WWLib/thread.cpp. Commit e53f7b13020672350e4244facf694217e855f9af introduced the distinct _GetCurrentThreadId@0 row at RVA 0x00687E0A. Census identity resolution then preferred that row over the old pin at 0x006105D0. Both entries contain FF 25 20 A2 BB 00, but their native entry addresses differ. The inspected preview index identifies itself as bf3dd31211 (2026-10-27 00:39, retail-truth-4).

Completed: the three consumers include the existing reference/shims/bfme2_thread/thread.h and call its ThreadClass::_Get_Current_Thread_ID declaration. Include directories are added only to the existing cl lines. The provider, import thunks, shared headers, pins and ledgers are unchanged. All emitted COMDAT names, bytes and extents remain identical; exactly five REL32 referent names change from _GetCurrentThreadId@0 to ?_Get_Current_Thread_ID@ThreadClass@@SAIXZ. All seven matched rows pass ordinary byte verification. Per-source declaration, EH and shadow data checks pass; the data checks report zero findings. check_csv.py and pin_consistency.py --check pass. Four DX8 code verdicts improve from wrong to unknown because of their separate unplaced data names; the timestamp body is retail. No stronger retail-verdict claim is made for the DX8 bodies.

Clearance: a paired current-object link_check.py call covers 115 previewable sources, comprising every source that spells an affected body or the thread-wrapper name and the Win32 import provider. It changes 16 to 114 LINKS, preserves every previously linking source and adds no blocker to any source. All three assigned sources and all eight named sample callers now LINKS. This subset is cleared in ordinary-preview scope; census confirmation pending. The only remaining failure in this cohort is the unchanged ??_7GameWindow@@6B@ first-copy conflict in Code/GameEngine/Source/GameClient/GUI/GameWindowDtor.cpp. The additional spelling hit W3DSnowResourceView.h is a header rather than a census unit.

2026-10-27 caller confirmation at e1a73387fd: the picker still serves Code/GameEngine/Source/Common/Rva007E3C20Vp6StreamDtor.cpp against the same census. Its current object alone retains the stale-index wrong-selected BFME_DX8_Thread_Lock result; including the current BfmeDX8ThreadLock.cpp provider clears it. After replacing handwritten memcpy declarations with <string.h> in that caller and Rva007E3C20Vp6StreamDtor_~Rva007E3C20Vp6Stream.cpp, the three-source ordinary preview is 3/3 LINKS (1,460 + 375 + 247 authored bytes). Both consumer objects preserve all executable-section bytes and relocation targets; their seven matched rows and both EH parents verify. A scoped ms_header_audit refresh removes the two clean queue entries. This confirms the existing repair and retires header-copy debt; it adds no census or headline gain.

2026-10-27 caller confirmation at 9fef84f164: the picker also serves
Code/GameEngine/Source/Common/Rva001517DEDtor.cpp. Its six matched rows pass
the byte gate, including the two funclets verified through their parent's EH
data after label renumbering. Its sole ordinary-preview blocker is the old
BFME_DX8_Thread_Lock provider. Supplying the current BfmeDX8ThreadLock.cpp
clears both units (192 and 247 authored bytes). No source change was needed;
this is confirmation of the existing repair, with census confirmation pending.

Remaining / next check: no match, pin, rename or shared-header prerequisite remains for the assigned sources. Keep the GameWindow table issue in its separate repair scope. Confirm the repaired wrapper bindings and their caller closure in the next normal maintainer census; no census or headline gain is claimed here.

Census confirmation: pending.

Follow-up verification (2026-10-27, `e1a73387fd`): the default queue served
GameEngineExecuteRva0022D290.cpp's historical selected-copy blocker. With the
current BfmeDfe6e4_rva00225492.cpp provider both preview LINKS (1,395 and 78
authored bytes), and all five execute-unit rows byte-verify. This confirms the
existing repair for this additional caller; census confirmation remains pending.
Checks are recorded in [the scoped evidence](../../reverse/attempt_support/upgradedie-data-index-20261027.md).

Follow-up verification (2026-10-27, `67098f8d8b`): the default queue served
W3DDisplayRva00045213.cpp's historical BFME_DX8_Thread_Lock blocker. Paired with
the current BfmeDX8ThreadLock.cpp provider, both preview LINKS (383 and 247
authored bytes); all three screenshot-unit rows pass byte verification. No
source change was needed. [Scoped checks](../../reverse/attempt_support/gamespy-pinger-shared-data-20261027.md)
extend the existing repair's caller evidence; census confirmation remains pending.

Follow-up shadow verification and debt retirement (2026-10-27, `f732423015`):
the default picker served W3DVolumetricShadow.cpp's historical selected-copy
blocker. Paired with the current BfmeDX8ThreadLock.cpp provider, both preview
LINKS before and after cleanup (348 and 247 authored bytes). All four shadow
rows and its one EH graph remain exact; all 13 emitted COMDAT digests are
unchanged. Two stale manager-destructor unmatched exemptions and their hatch
keys are retired. Existing shadow data findings and LINK-008's strict-receipt
prerequisite remain. [Scoped evidence](../../reverse/attempt_support/shadow-marker-cleanup-20261027-codexb4.md).
This confirms the landed repair for this caller; census confirmation remains
pending, with no new linked-byte gain claimed.

Follow-up verification (2026-10-27, `83f299b390`): the default queue served
W3DUtility.cpp's historical thread-wrapper selected-copy blocker. All five
utility rows byte-verify. Paired with the current BfmeDX8ThreadLock.cpp and
BfmeDX8ThreadCheck.cpp providers, all three preview LINKS (1,502, 247 and 31
authored bytes). [Scoped checks](../../reverse/attempt_support/texture-current-frame-data-20261027.md)
confirm this caller needs no further source repair; census confirmation remains
pending.
Follow-up verification (2026-10-27, `e43a9aad40`): the default link queue (shard
0/10) still serves nine historical BFME_DX8_Thread_Lock callers. Alone, each
current object keeps only the selected-copy finding; paired with the current
BfmeDX8ThreadLock.cpp provider all nine and the provider preview LINKS against
index `bf3dd31211`: W3DDisplayInit.cpp (1,599 B), Rva00111DB6PostFXLookupTable.cpp
(342), WaterRenderObjInit.cpp (297), W3DDisplayResetD3DDevice.cpp (288),
W3DSmudgeManager_ReAcquireResources.cpp (260), W3DDisplayReset.cpp (259),
W3DTaintReAcquire.cpp (183), W3DRadarReset.cpp (177) and Rva00066A9ASubHeadB.cpp
(114). No source change; this extends the landed repair's caller evidence only.
Census confirmation remains pending; no headline gain claimed.

Follow-up verification (2026-10-27, `10d8ab4531`): the default picker served
W3DDisplayCreate_W3DDisplay_createVideoBuffer.cpp's historical selected-copy
blocker. Its four unchanged rows pass byte verification, including both
funclets through their parent EH graph. Paired with current
BfmeDX8ThreadLock.cpp, both ordinary previews report LINKS (258 and 247
authored bytes) against index `bf3dd31211`. No source repair is needed;
this extends the existing repair's caller evidence. Census confirmation remains
pending; no new headline or runtime gain is claimed.

Follow-up verification and header cleanup (2026-10-27, `87d14902cf`): the
default picker served bfmedynamicvertexbuffer.cpp's historical thread-wrapper
selected-copy blocker. With current BfmeDX8ThreadLock.cpp and
BfmeDX8ThreadCheck.cpp, all three ordinary previews report LINKS before and
after cleanup (6,860, 247 and 31 authored bytes). Replacing four handwritten
allocation declarations with `<new>` preserves all 63 executable sections and
90 external symbol records; all 46 rows and 14 EH graphs verify. A scoped
Microsoft-header queue refresh retires this source's entry. Existing storage
identity prerequisites remain in the prior data handoff. [Scoped evidence](../../reverse/attempt_support/dynamic-vertex-buffer-header-20261027-codex.md).
This extends the existing repair's caller evidence; census confirmation remains
pending, with no new linked-byte gain claimed.

Follow-up water declaration repair (2026-10-27, `b3ff5cb28fb`):
the picker serves W3DWaterRva0007F0FB.cpp's historical lock-provider blocker.
Paired with current BfmeDX8ThreadLock.cpp, both preview LINKS before and after
the repair (1,930 and 247 authored bytes). The water source now declares the
release helper with its rowed bool return type, replacing two void-alias
references with direct owner references. All five rows, the EH graph, and every
byte in its 19 executable sections are preserved; shadow data has no findings.
[Scoped evidence](../../reverse/attempt_support/water-release-owner-binding-20261027-bce2/README.md)
records the exact two relocation-name changes. The shared alias remains for
other callers. This is caller binding cleanup; census confirmation of the
earlier provider repair is still pending, and no new linked-byte gain is claimed.

Follow-up verification (2026-10-27, `b8ac4b22c1`): the default picker also
served W3DDisplayRva0004A462.cpp. All seven rows byte-verify; the paired
current BfmeDX8ThreadLock.cpp provider clears its sole stale-index blocker
(2/2 LINKS, 1,432 and 247 authored bytes). The same provider clears
dx8wrapper.cpp (2/2 LINKS, 28,658 and 247 authored bytes). Neither caller
needed a source repair for LINK-106. [The scoped evidence](../../reverse/attempt_support/dx8wrapper-destructor-folds-20261027.md)
also records five independent DX8 identity-key retirements; no census gain
is claimed.

Follow-up verification (2026-10-27, inspected `48ba8143a5`): the default queue
served `WW3D2/Rva00131965TextureLoaders.cpp`'s historical selected-copy blocker.
Together with current `BfmeDX8ThreadLock.cpp`, both preview LINKS (2,458 and
247 authored bytes), and all 18 texture-loader rows pass byte verification.
No source change was needed; census confirmation remains pending.
[Scoped checks](../../reverse/attempt_support/watchdog-donor-cleanup-20261027.md).

Follow-up verification (2026-10-27, `dbce5d0f8e`): the default queue served
Rva00081F03Cleanup.cpp's historical thread-lock selected-copy blocker. All
three rows verify. Paired with the current BfmeDX8ThreadLock.cpp provider,
both preview LINKS (228 and 247 authored bytes). No source repair was needed;
[scoped evidence](../../reverse/attempt_support/banner-poolkey-data-retirement-20261027-codexb4.md)
confirms the existing repair for this caller. Census confirmation remains pending.

The 2026-11-12 Watchdog synchronization-member reconciliation preserved the
three affected units' 915 census-linked bytes. Their TU merge still depends
on the Watchdog base override and the four-slot table at RVA 0x007E6FD8.
[Constructor trial and remaining slot conflicts](../../reverse/attempt_support/watchdog-donor-cleanup-20261027.md#synchronization-members-and-tu-composition-2026-11-12).
