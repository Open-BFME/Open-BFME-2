# Preserve the native ModuleInfo copied-flag provider

Inspected at a3623130cb on 2026-11-09, following the ThingTemplate adoption
in 3a769cd922. ThingTemplateSetCopiedFromDefault.cpp now includes the canonical
ModuleInfoClass.h instead of defining its own ModuleInfo/Nugget. The actual
setCopiedFromDefault(bool) body remains an inline out-of-class definition.

Target facts: ModuleInfo is12B, Nugget stride20B and copiedFromDefault is the
byte+0x10. The canonical second flag is+0x11; dropping the old unused third
flag at+0x12 does not change stride. The loop's count comparison stays unsigned
through an explicit cast of canonical getCount(). No ModuleInfo/Nugget object
is constructed, copied or destroyed by this pointer-only loop. Existing record
iterators, ThingTemplate methods and AsciiString lifetimes remain unchanged.
No shared header, source path, ledger identity/extent, pin, alias declaration,
hatch or compiler flag changes. Existing donor commentary stays separate; this
adoption imports no donor or original-TU claim.

The first private candidate matches all three rows and its one EH graph.
Normal build.sh passes3/3 with no string/float/import obligations; frozen checks
pass before/after. Current-input link_check against index5b5011469d (2026-11-09
19:12, census9b9d058303 at17:41) preserves LINKS306/306 bytes. Owning ModuleInfo
acceptance retires the file's one header-queue row, leaving28 ModuleInfo units
locally. No header queue key remains for this file. Its strict receipt is current.

Provider preservation is explicit: ten retained COMDAT payloads/sizes are
identical, including the native67B setter (digestf1117d56610d). The setter's
select-any policy remains2 before/after, so this does not turn an existing
inline provider into a conflicting strong definition. Undefined references,
weak defaults, aliases and /INCLUDE directives are unchanged.

The sole definition substitution is the incidental12B unsigned size() getter
for the canonical signed getCount() spelling. The old name has one indexed
emitter/toucher, this file, and no explicit outside Code/ledger binding. The
new getter's identical12B payload (digestd2b57ba9852a) matches all six existing
canonical copies in the fresh index. The native setter preserves unsigned
comparison semantics independently of the new getter's signed return type.
These observations establish this consumer/provider scope, not global recovery
of all28 remaining ModuleInfo views or any runtime result.

Local evidence is under build/thingtemplate-header-cohort-20261109/:
probe-moduleinfo-provider.py, moduleinfo-private-proof.json,
moduleinfo-private-eh.json, moduleinfo-build.log, moduleinfo-frozen.log,
moduleinfo-link.log, moduleinfo-accept.log, moduleinfo-prepare.log,
prove-moduleinfo-providers.py and moduleinfo-provider-diff.json. Historical
before/candidate snapshots must not be overwritten. A bounded native read-only
review independently checked stride, count signedness, provider users and claims;
the parent performed all edits, compilations, acceptance and publication.

The preceding six-source publication's broader audit remains INCONCLUSIVE for
unchanged AICowerState_onEnter.cpp at index5b5011469d/basebd5a6b9947. Carry this
receipt gap into the next census. A real maintained image and runtime pass are
still required; the scoped preview is not that result.
