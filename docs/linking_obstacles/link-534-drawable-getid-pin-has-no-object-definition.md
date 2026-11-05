### LINK-534: Drawable::getID pin has no object definition
Status: Open. Updated: 2026-11-05; inspected revision: `2af8c01e56`.
Evidence / affected units: twelve real-link blocker sources reference `?getID@Drawable@@QBE?AW4DrawableID@@XZ`; the pin maps to the matched opaque getter at `0x0055A88B`, but no object defines that spelling.
Completed: AnimationSoundClientBehavior.cpp now calls the existing matched getter; 31/31 function checks and one data row pass, with external definitions preserved.
Remaining / next check: repair the other eleven consumers or reconcile the provider's existing opaque-name consumers; confirm this unit's missing-name error disappears in the next real link.
Clearance: pending real-link verification; ordinary preview remains LINKS for 2,316 bytes and previously accepted the pin.
Census confirmation: not claimed.
[Repair evidence](../../reverse/attempt_support/animation-sound-drawable-id-link-20261105-codex.md).
