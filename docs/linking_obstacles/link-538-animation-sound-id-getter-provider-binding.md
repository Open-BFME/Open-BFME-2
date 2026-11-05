### LINK-538: Animation sound calls a pinned Drawable ID getter without a compiled provider

Status: Cleared for the animation-sound unit's bounded preview. Updated: 2026-11-05; inspected revision: `5a1f7a409f`.
Evidence / repair: [Native getter binding and checks](../../reverse/attempt_support/animation-sound-id-provider-20261105-codexb.md). `updateAnimationSounds` now calls the existing rowed `0x0055A88B` getter; all 31 code rows, the data row and five EH graphs remain exact. Current-object preview changes from the sole unresolved `Drawable::getID` reference to LINKS for 2,316 authored bytes against index `112a456a2c`.
Remaining / next check: confirm removal of this unit's missing-name error in the next real link; other consumers of the pinned spelling and full consumer selection remain open.
Census confirmation: pending; no headline or runtime gain claimed.

2026-11-05: [InGameUI follow-up](../../reverse/attempt_support/ingameui-id-provider-20261105-codexb.md) binds selection, mouseover hints and UI save/load to the same rowed getter; 39 rows and four EH graphs pass, and all three current-object previews LINKS (4,465 authored bytes). Cleared for those bounded previews; next real-link confirmation and other consumers remain pending.

2026-11-05: [Audio-loop and faction-bib follow-up](../../reverse/attempt_support/behavior-bib-id-provider-20261105-codexb.md) binds two more consumers to the rowed getter; nine rows and three EH graphs pass, and both current-object previews LINKS (1,795 authored bytes). Cleared for these bounded previews; next real-link confirmation and other consumers remain pending.

2026-11-05: Removed a duplicate getter class definition introduced by `306f6f33e7` after the earlier binding repair; [regression evidence](../../reverse/attempt_support/animation-sound-duplicate-getter-20261105-codexb.md). The unit compiles again, all 31 functions and the data row pass, five EH graphs are EXACT, strict preparation passes and its preview LINKS for 2,316 bytes at index `112a456a2c`; real-link confirmation remains pending.
