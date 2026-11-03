# CDManager donor-list cleanup

Base: c1325ac0b6. Seat: halilkkaya-codex. No source paths or ledger identities move.

The successful real-link workflow 41678189681 measures 96cfeda7ba:
678 unresolved names and two duplicates. Eight of those names are referenced
by Common/System/CDManager.cpp. Its current ledger contains only the two
27-byte ICF-folded getters, getPath and getDiskName. The ScriptConditions
destructor formerly attributed to CDManager was already corrected in
74490b2a87; this cleanup does not retract any row.

Remove the fourteen unrowed Zero Hour CDDrive/CDManager definitions and the
unused GameLogic include. Keep both getters and TheCDManager, which the
current FileSystem unit references. The disappeared list/manager bodies have
no outside references in the published index (984a4cdc4d, November 2 08:35)
or in the current Code source reference audit. Thirty-seven external
providers disappear; the five common COMDAT fingerprints are identical,
and no new provider is emitted. The five shared removed inline providers
have other owners; none changes selected owner in the paired index overlay.
The obsolete CDManager tables and their methods have no outside consumer.
These facts do not prove the actual retail CDManager implementation recovered.

Verification:

- Required initial full build: all checks green, 99,420 function rows and
  2,266 data rows; no master repair was required.
- Normal six-source build: 389/389 rows, string/float/import checks pass.
  Scope: CDManager, FileSystem, Libraries/subsystem/SubsystemInterface,
  BFMEConnectionManager_sendGameSpyStatsAuthKey,
  ConnectionManager_processGameSpyStatsAuthKey_Rva004CFE24,
  MilesAudioManagerGetAudioLengthMS. Other-seat paths are read/verified only.
- True base/tip A/B: restore the original source and build it normally, run
  link_check over all six sources, restore the candidate and repeat. Five
  unchanged LINKS sources retain 22,879 bytes; CDManager changes from blocked
  to LINKS, adding its existing 54 bytes. No LINKS-to-blocked transition.
- find_declared_unmatched: clean. Scoped DIR32: 389 rows plus 17 current
  witnesses; 237 symbols, zero new or whitelisted conflicts.
- The following eight artifact names no longer occur as undefined externals
  in CDManager; the artifact attributes none to another source:
  - `??0LList@@QAE@XZ`
  - `??0LListNode@@QAE@XZ`
  - `??1CDManager@@UAE@XZ`
  - `?add@LList@@QAEXPAVLListNode@@@Z`
  - `?getNode@LList@@QAEPAVLListNode@@H@Z`
  - `?next@LListNode@@QAEPAV1@XZ`
  - `?nodeCount@LList@@QAEHXZ`
  - `?remove@LListNode@@QAEXXZ`

No real link was rerun and no census headline gain is claimed. The dated
preview does not establish whole-current-image or runtime closure. Scratch
base/tip objects, source reference inventory and logs: build/seat-link/.
