# Castle helper canonical Module adoption

The private Module view includes member-specific storage at `+14`. Include
the existing canonical eight-byte base and keep the observed bytes in an
address-named partial derived view with the appropriate gap.

Native `398056` calls Object::findModule; `398064` tests four bytes at the
returned module's `+14`, and `398069` passes the same module pointer as ECX
to the existing checkValid provider. The view preserves these offsets and ABI
without pointer adjustment. The test proves storage, not its original type or
name. No complete derived class or original inheritance is inferred, and this
layout is not transferred to the differently returned upgrade-module view.

Private before/after verification passes all four rows and their EH graph.
All four external code definitions and symbolic relocations are identical,
with no new body/provider. Original preview retains LINKS/377 authored bytes
against `ccafe54d1d`. Literal build.sh, frozen and strict preparation pass
across the changed pair: nine rows, three literals and one empty string.
[Private and actual-object proof](pending-proof.json).

No shared header, ledger row, pin, alias, hatch or source path changes.
The owning header-acceptance verdict and outgoing audit are recorded with the
accepted source change. Full consumer selection/loss and scheduled census
confirmation remain separate; no new linked-byte gain is claimed.

The owning `header_adopt_lane.py accept --class Module` test passes and
retires this source's one queue row. The final changed-pair preview retains
2/2 LINKS and 1,268 authored bytes (891 + 377), with both owned EH graphs
EXACT. This is the second independently banked source adoption.

Ready-batch audit: INCONCLUSIVE on older `ccafe54d1d` versus outgoing base
`6d6ae2f4d5` and the missing current CreateAHeroManager consumer receipt.
Carry both adopted sources and affected consumers into the next scheduled
census; no full-image selection/loss clearance is inferred.
