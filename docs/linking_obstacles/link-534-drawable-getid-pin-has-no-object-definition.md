### LINK-534: Drawable::getID pin has no object definition
Status: Cleared at the provider, pending real-link confirmation. Updated: 2026-11-05; inspected revision: `418876d965`.
Evidence / affected units: twelve real-link blocker sources reference `?getID@Drawable@@QBE?AW4DrawableID@@XZ`; the pin maps to the matched opaque getter at `0x0055A88B`, but no object defines that spelling.
Completed: AnimationSoundClientBehavior.cpp and eight more consumer units call the existing matched getter; the new batch preserves 304/304 matched rows and all 1,938 external definitions.
Remaining / next check: all twelve consumers now call the matched getter; confirm they disappear from the next real-link missing-name errors.
Clearance: pending real-link verification; the new eight-unit preview remains LINKS for the same 30,284 bytes and previously accepted the pin.
Census confirmation: not claimed.
[Repair evidence](../../reverse/attempt_support/animation-sound-drawable-id-link-20261105-codex.md).
[Eight-consumer repair evidence](../../reverse/attempt_support/drawable-id-consumers-20261105-codex/report.md).
2026-11-05: InGameUISelectDrawable.cpp and ObjectDoXfer.cpp now call the matched getter; 18/18 rows and all 60 external definitions are preserved, with both previews still LINKS for 4,023 bytes; [selection/snapshot repair evidence](../../reverse/attempt_support/drawable-id-selection-xfer-20261105-codex/report.md).

2026-11-05 (claude-opus-5-5): the provider half is done. `85b46a09f3` defines
`?getID@Drawable@@QBE?AW4DrawableID@@XZ` in Drawable.cpp as the 0x0055A88B ICF twin
(row matched; Drawable.cpp 150/150; its object carries the 7-byte `mov eax,[ecx+0x100]; ret`)
and retires the pin. So the remaining consumer, GameClient.cpp
(`GameClient::allocDrawableID` 0x002FDB5D, served from the real-link errors), needs no
change: `link_check` LINKS (5 -> 5 bytes). Scope: every consumer that spells the name now
has a definer. Clearance needs the next real link (`real-link.yml`) to stop listing it.
2026-11-05: independently of `85b46a09f3`, GameClient.cpp also calls the matched getter (2/2 rows, 622 external definitions kept, preview LINKS); next check: the next real link lists none of them; [GameClient repair evidence](../../reverse/attempt_support/drawable-id-gameclient-20261105-claude/report.md).

2026-11-05: `85b46a09f3` supplies the named getter in Drawable.cpp; AnimationSoundClientBehavior now uses it directly, removing its address-named workaround. Current animation/provider/health-bar objects all preview LINKS; provider absence is cleared locally, awaiting the next real link for all historical callers. [Named-provider verification and stale-index duplicate diagnosis](../../reverse/attempt_support/animation-sound-named-id-20261105-codexb4.md).
