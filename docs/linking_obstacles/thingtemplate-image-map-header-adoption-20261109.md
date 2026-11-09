### ThingTemplate image and locomotor consumers need shared storage views

Status: three consumer adoptions verified; wider class recovery open. Updated:
2026-11-09; inspected revision: 592396ae2c.

ThingTemplateButtonImage.cpp, ThingTemplateLocomotorMapStore.cpp and
GameLogic/Thing/Rva0033BA46Finish.cpp adopt the unchanged canonical header.
Existing image-pointer words and the twelve-byte locomotor map are accessed
through explicit views. Normal verification preserves three rows/305 ledger
bytes and all three string references; current-input previews against index
138c18d3c9 preserve 303/303 linked bytes. Owning acceptance retires three header
queue rows, leaving 75 ThingTemplate consumers locally.

[Target facts, checks and remaining prerequisites](../../reverse/attempt_support/thingtemplate-image-map-header-adoption-20261109.md).
Opaque member spelling, other private consumers and their lifetime/accessor
constraints remain separate. The prior broad audit's GapBodiesGE26.cpp receipt
gap is carried forward. Census/image confirmation is pending; this is source
cleanup, with no new global linking coverage or game-runtime claim.
