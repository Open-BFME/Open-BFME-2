### ThingTemplate common member consumers need canonical storage views

Status: four consumer adoptions verified; remaining consumers open. Updated:
2026-11-09; inspected revision: 3aaf490c96.

ModuleInfoGetNthData.cpp, ThingTemplateFuelFactorProvider.cpp,
ThingTemplateFloatMapStore.cpp and
ThingTemplateGetCurrentLivingWorldAutoResolveWeapon.cpp replace their private
ThingTemplate bodies with the unchanged shared header and explicit views of
its existing member storage. All eight native bodies and both string references
pass. Four current-input previews preserve 656/656 linked bytes against index
138c18d3c9. Owning header acceptance retires four queue rows; 78 remain locally.

ConstIntGetters9.cpp and Rva0033A8FCBuildFieldParse.cpp still need an evidence-led
resolution of their private static field-table access (canonical substitution
fails C2248). Other cohort refusals need geometry/kind-mask/container views or
constructor lifetime reconciliation. No failed source or new access mechanism
is retained. LINK-582's W3D consumers remain separate.

[Target facts, verification scope and remaining prerequisites](../../reverse/attempt_support/thingtemplate-common-member-header-adoption-20261109.md).
Census/image confirmation is pending; no new linking coverage or game progress
is claimed. The prior broad audit's unchanged AIBuildable.cpp receipt gap is
carried forward, not cleared by these four current sources.
