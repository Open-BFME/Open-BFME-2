# Four ThingTemplate consumers adopt the shared layout

Inspected at 3aaf490c96 on 2026-11-09. This is a source/header cleanup,
not a new byte match or a real-image result.

The bounded first 25 queued consumers all refuse automatic substitution.
Four of their private views are reconciled manually to the existing canonical
ThingTemplate.h, without changing that header, its 0x640-byte layout or any
method/ledger identity:

- ModuleInfoGetNthData.cpp: four existing scanners view the twelve bytes at
  +0x2E4 as the already shared ModuleInfo. The reference introduces no member
  construction or destruction; repeated getNthData calls are retained.
- ThingTemplateFuelFactorProvider.cpp: the callback uses the same ModuleInfo
  view at +0x2E4, retaining its search, validation and exception storage.
- ThingTemplateFloatMapStore.cpp: the rowed store views the existing twelve
  bytes at +0x3A0 as its existing map<int,float>; allocator specializations and
  all declaration-only bindings are preserved.
- ThingTemplateGetCurrentLivingWorldAutoResolveWeapon.cpp: begin/end remain
  pointer words +0x3F8/+0x3FC in the canonical twelve-byte storage. Two direct
  expressions preserve native loads. A local pointer to the descriptor emitted
  an extra LEA and was immediately reverted; no failed source remains.

Target facts are the retained native bodies, addresses, field accesses and
existing declarations. No donor is used. These consumer views do not establish
the original container spellings, complete member lifetimes or original TU.
No source path, code/data row, pin, alias, compiler flag or hatch is added.

Private verification passes all eight existing rows. Normal build.sh passes
8/8 native bodies and both string references, with no float/import obligations.
The private EH check finds no EH-bearing row or missing object. Frozen-file
checks pass before and after. Current-input link_check against index 138c18d3c9
(2026-11-09 16:08) reports all four LINKS: 369+29+197+61 = 656 -> 656 bytes.
The final source form passes owning header acceptance; the tool retires four
queue rows, leaving 78 ThingTemplate consumers in this checkout. Strict reusable
receipts are prepared for the four changed sources before publication.

Other consumers remain queued. In particular, ConstIntGetters9.cpp and
Rva0033A8FCBuildFieldParse.cpp access the private static field table through
their old private class's friendship. Direct canonical substitution gives C2248;
no new friendship, surrogate field-table symbol or access bypass was added.
The remaining automatic refusals include typed geometry, kind-mask and opaque
container boundaries, ambiguous receiver names and constructor lifetimes.
Resolve these from their own native uses rather than changing the shared layout
to make a textual swap pass. The existing W3D name-accessor and container
identity blockers in LINK-582 remain separate.

Local evidence: build/thingtemplate-header-cohort-20261109/{adopt-dry.log,
probe-members.py,member-private-proof.json,member-private-eh.json,
build-members.log,link-final.log,accept-final.log,prepare-final.log}.
The before/candidate texts are historical snapshots; do not rerun scripts
which would overwrite those baselines. A future census and maintained real
image must confirm the broader selection/runtime outcome. The preceding
publication's unchanged AIBuildable.cpp receipt gap at index138c18d3c9/base
77690d50fb remains unverified; this four-source preview does not clear it.
