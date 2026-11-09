# ThingTemplate equivalence uses the shared class and string types

Inspected at c21963756a on 2026-11-09. The complete
Common/Thing/ThingTemplateIsEquivalentTo.cpp replaces its private ThingTemplate
and StringBase declarations with the canonical ThingTemplate header. The shared
headers, method row and compiler flags are unchanged.

The +0x64 canonical AsciiString is viewed as the existing four-byte StringBase
comparison receiver. The opaque twelve-byte +0x330/+0x33C members retain their
existing vector<StringBase<char>> element representation through const views.
Small force-inlined helpers name these non-owning views; no string/vector is
constructed, copied or destroyed. The original Rva001E35DFView declaration and
its getFinalOverride identity remain. Explicit prefix views preserve its chain
pointer +4 and native getter rather than changing to the canonical base's getter.

Native layout/accesses and all existing calls are target facts. Donor facts in
the original source commentary remain distinct. This adoption establishes no
new member spelling, full container lifetime or original TU. No source path,
ledger identity, pin, alias declaration, hatch or shared layout changes.

Private direct-view and final helper variants both match the entire row.
Normal build.sh passes the 335-byte ledger row, with no string, float, import
or EH-bearing-row obligations. Frozen checks pass. Current-input link_check
against the newly fetched 5b5011469d index (2026-11-09 19:12, census 9b9d058303
at17:41) reports LINKS 330 -> 330 bytes; the five tail padding bytes are not
counted as linked code. Owning acceptance retires one header-queue row, leaving
74 ThingTemplate consumers in this checkout. The changed source has a strict
reusable receipt.

Provider audit: the private before object and normal final object retain six
COMDAT payloads/sizes identically. No definition is added. The only removed
definition is the old StringBase-returning ThingTemplate::getName spelling.
Both index138c18d3c9 (native read-only review) and fresh index5b5011469d (parent
check) show this file as its sole emitter and sole toucher. Current Code and
explicit ledger/pin searches find no outside binding to it. The canonical
AsciiString-returning getter is a different symbol, not a replacement under
the old name. The kept Rva001E35DFView getter has three indexed providers and
four touching objects; it is not removed or respelled.

Undefined symbols, weak defaults and /INCLUDE directives are unchanged. The
canonical AsciiString header contributes its seven pre-existing /alternatename
directives to this object; every identical alias/target pair already exists in
the fresh index and none of those names is defined/referenced by this object.
No alias declaration or hatch count is added. The first local provider script
assumed directives would be identical; inspection identified these inherited
directives and the final report records them explicitly instead.

Local evidence: build/thingtemplate-header-cohort-20261109/{probe-equivalence.py,
probe-equivalence-views.py,equivalence-views-proof.json,equivalence-private-eh.json,
equivalence-build.log,equivalence-frozen.log,equivalence-link.log,
equivalence-accept.log,equivalence-prepare.log,equivalence-provider-index.json,
prove-equivalence-providers.py,equivalence-provider-diff.json}. Before snapshots
are historical evidence, not scripts to rerun over the baseline.

Other ThingTemplate consumers, typed member recovery and canonical-base getter
reconciliation remain separate. The preceding publication's INCONCLUSIVE
AptFileTransferPopup.cpp receipt gap (index138c18d3c9/base5c6ddfa805) is carried
forward for the next census; this preview does not clear it or establish a
real image/runtime result.
