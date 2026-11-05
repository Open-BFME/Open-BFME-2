### LINK-534: Drawable::getID pin has no object definition
Status: Open. Updated: 2026-11-05; inspected revision: `7d786ca949`.
Evidence / affected units: twelve real-link blocker sources reference `?getID@Drawable@@QBE?AW4DrawableID@@XZ`; the pin maps to the matched opaque getter at `0x0055A88B`, but no object defines that spelling.
Completed: AnimationSoundClientBehavior.cpp and eight more consumer units call the existing matched getter; the new batch preserves 304/304 matched rows and all 1,938 external definitions.
Remaining / next check: GameClient.cpp, InGameUISelectDrawable.cpp and ObjectDoXfer.cpp were peer-held; repair their calls or reconcile the provider, then confirm the repaired consumers disappear from the next real-link missing-name errors.
Clearance: pending real-link verification; the new eight-unit preview remains LINKS for the same 30,284 bytes and previously accepted the pin.
Census confirmation: not claimed.
[Repair evidence](../../reverse/attempt_support/animation-sound-drawable-id-link-20261105-codex.md).
[Eight-consumer repair evidence](../../reverse/attempt_support/drawable-id-consumers-20261105-codex/report.md).
