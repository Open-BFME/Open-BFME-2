# Window video: retire stale unmatched markers

Inspected upstream `9e1ca7f93f`; BFME 1 reference `f633d0e97a`.
The default link queue served the whole 518-line `window_video_manager.cpp`.
Its prior link attempts and the later
[native map repair](window-video-map-link-20261024.md) were read. The older
node-size/ownership concern was already repaired by `ee4c0517ff`; it is not
reopened here.

## Verified cleanup

Fifteen `present-unmatched` comments were stale: each function already has
one matched ledger row in this source. Only those comments were removed;
no function body, signature, flag, include, layout, pin or ledger row changed.

| Function | RVA | Bytes |
| --- | --- | ---: |
| WindowVideo::WindowVideo | 0x0053F0D0 | 62 |
| WindowVideo::~WindowVideo | 0x0053F10E | 87 |
| WindowVideo::init | 0x0053F165 | 107 |
| WindowVideo::setWindowState | 0x0053F06C | 83 |
| WindowVideoManager::WindowVideoManager | 0x0053F85C | 137 |
| WindowVideoManager::~WindowVideoManager | 0x0053F45C | 136 |
| WindowVideoManager::update | 0x0053F53C | 257 |
| WindowVideoManager::playMovie | 0x0053F63D | 228 |
| WindowVideoManager::pauseMovie | 0x0053F2B9 | 36 |
| WindowVideoManager::resumeMovie | 0x0053F301 | 48 |
| WindowVideoManager::stopMovie | 0x0053F331 | 36 |
| WindowVideoManager::stopAllMovies | 0x0053F721 | 64 |
| WindowVideoManager::pauseAllMovies | 0x0053F761 | 64 |
| WindowVideoManager::resumeAllMovies | 0x0053F7A1 | 64 |
| WindowVideoManager::getWinState | 0x0053F355 | 35 |

The frozen-file checker passes before and after; afterward it no longer needs
the fifteen exemptions. Normal before/after builds preserve **38 rows / 2,155
bytes**; all **seven EH graphs are EXACT**. `hatch_counters.py --update`
generated the register changes; only its fifteen removals for this claimed
source were retained. Its unrelated whole-tree housekeeping was reverted.
`--staged` accepts exactly **15 fewer present_unmatched occurrences**
(register total 4,361 -> 4,346), with no other hatch change.

## Linking and identity limits

Against index `f995f30157` (2026-10-25 21:36 UTC), the ordinary before/after
preview is unchanged: 0 -> 0, solely blocked by the selected `__lower_bound`
copy. Two unreferenced codegen diagnostics are explicitly not blockers.

Passing the current INI and `stlport_lower_bound_uint.cpp` providers with
the window source clears that historical selected-copy blocker: window video
previews LINKS for its **2,116 authored nonpadding bytes**, and the lower-bound
provider for 108 bytes. The three-source command still exits 1 because INI
retains its separate historical duplicates/selection findings. This confirms
existing repair `0c7ebc35a7`; it is not new linking credit for comment removal.
The [INI current-evidence handoff](ini-current-ledger-prerequisites-20261026.md)
records why no complete current-ledger verdict is claimed.

The owning identity-retirement tool refuses and retires **no keys**. Four
reported failures look up obsolete EH labels literally, although the normal
byte/EH gates resolve them from their verified parents:

| RVA | Old label | Verified current label |
| --- | --- | --- |
| 0x00797CA6 | $L12283 | $L11158 |
| 0x00797CC3 | $L12213 | $L11688 |
| 0x00797C8C | $L9318 | $L9533 |
| 0x00797CBB | $L11082 | $L11686 |

That narrow verifier discrepancy extends LINK-015. The refusal also reports
five other findings; those are not declared false rejects or cleared by this
pass. All four existing identity-register keys remain. Reconcile EH resolution
in a separate tooling change and then assess the remaining current bindings.
No tool, pin or compiler label was changed to bypass the refusal.

The credited result is fifteen retired hatch occurrences. No new matched
bytes, census update, complete-image link or runtime result is claimed.
