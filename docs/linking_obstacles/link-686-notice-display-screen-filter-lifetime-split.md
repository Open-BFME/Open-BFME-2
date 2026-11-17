### LINK-686: Notice display constructor shares a false destructor identity with a screen-filter global
Status: Blocked. Updated: 2026-11-17; inspected revision: 6f05eee4dbbdde3d67d9259349b2f6d028d472db.
Evidence / affected units: Common/Bfme/Rva004E5A24Ctor.cpp, Common/Bfme/IngameNoticeDisplay.cpp, Common/Rva007B6880Thunks.cpp and W3DDevice/GameClient/ScreenHilightFilter.cpp; [native lifetime proof and supported-tool limits](../../reverse/attempt_support/notice-display-lifetime-split-20261117-root20.md).
Completed: existing 2/2 row baseline; native initializer/exit-thunk pair proves 15B FB86C belongs to the separate 0x2C global constructed at FB8B6. Notice table 8623CC instead destroys the 0x34 object through 105B 4E61C8. No edits or aliases.
Remaining / next check: owning-tool class/signature split preserving coverage and approved placement before class fold and fourteen-slot bridge recovery.
Clearance: pending. Census confirmation: none; source unchanged.
