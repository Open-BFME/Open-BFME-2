# FX alpha/color transfer identities

Inspected base: `aa587049989ea57f19840b5032ead2bb76a4a825`.

Target evidence: retail exports 1161 and 1162 name
`?DoXfer@DefaultAlphaModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z`
at 0x0055B266 (54 bytes) and
`?DoXfer@DefaultColorModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z`
at 0x0055B8CD (70 bytes). The existing native table evidence places them
in slot 3 of the info tables at VA 0x0081BA60/0x0081BA90 and their
module-wrapper tables. No donor source is used for these identities.

The former rows named address-based classes and took Xfer pointers.
`rename.py function` cannot express the reference signature change; this
uses the manual canonical rename path in docs/naming.md. Both old names
are tombstoned, and both verdicts are recorded through re_log.py. No pin
uses either old name. The three caller sources found by the scoped text
search are updated: Rva0055B30FXfer, Rva0055B951 and
ModuleCtorChainsA_Rva003ABAF3_Rva003ABB93. Their qualified calls retain
the original native call targets. The two constructor views now declare
the exported slot 3, and FXParticleSystem.cpp's alpha/color infos use the
already-included canonical Snapshot base. Transfer-only views remain
partial; this change does not recover either complete application class.

Verification: build.log records all 403 rows across eight sources and two
data checks passing; eh.log records both constructor EH graphs EXACT.
The existing generated funclet rows are validated against their parent
EH graphs after compiler label renumbering. All changed sources pass
find_declared_unmatched.py; FXParticleSystem.cpp keeps its five preexisting
unclaimed-definition notes. check_csv.py and git diff --check pass.
link.log is an ordinary eight-source preview against the published
2026-11-04 16:16 index at 2f0cb97f52: all eight LINKS, preserving 6,385
census-linked bytes. This is no new census, runtime or linked-byte gain.

Snapshot header acceptance still refuses FXParticleSystem.cpp because
its private namespace base remains for six macro-declared info classes:
DefaultDraw, StreakDraw, QuadDraw, ButterflyDraw, RenderObjectDraw and
LifeEvent. Next: reconcile their real native callback slots/providers
before removing that base and rerunning the owning acceptance command.
MoneyVectorPushBack no longer has a Snapshot use after the prior record
identity correction; its header queue row still needs a supported
retirement path. No header queue row is removed by this change.

The staged name_dependents scan (dependents.log) checks 18,344 cached
units and finds zero remaining references to either withdrawn symbol.
