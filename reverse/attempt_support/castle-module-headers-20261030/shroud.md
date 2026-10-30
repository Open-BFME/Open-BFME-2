# Shroud canonical Module adoption

The private Module view mixed the canonical eight-byte base with castle-specific
storage at `+18`. Include the existing canonical base and retain that observed
storage in an address-named partial view. Exposing the inherited ModuleData
pointer changes access permission only; it does not alter storage.

Native `278B10` calls Object::findModule and `278B1D` reads the returned
module's `+18` as an ObjectID. A separate lookup at `278B39` reads ModuleData
at `+4`, then the event at data `+4C`. Those results need not have one concrete
derived class: only the first uses the castle field, and only the canonical
base is read from the second. The view preserves these accesses without
claiming a recovered concrete class, full layout or original inheritance.

Private before/after verification passes all five rows and their EH graph.
All 17 external code definitions and symbolic relocation destinations are
identical; no body or provider is added or removed. Original preview retains
LINKS/891 authored bytes against `ccafe54d1d`. Literal build.sh, frozen and
strict preparation pass across this unit and the separately checked castle
helper: nine rows, three literals and one empty string. The owning header
acceptance tool accepts this source and retires its one Module queue row.
[Private and actual-object proof](shroud-proof.json).

No shared header, ledger row, pin, alias, hatch, source path or other debt
register changes. Existing ModuleData, Object and merge prerequisites remain
separate. Full consumer selection/loss checks and scheduled census confirmation
remain pending; no new linked-byte gain is claimed.

The normal shadow data check reports a pre-existing wrong-name finding for
the compiler's local guard at RVA `009FEC4C`. Original and changed private
objects define the identical guard name, storage and data. The data ledger
still records the former GlobalFlagClearers owner; this adoption changes
neither that ownership record nor its debt and claims no retirement of it.
Enforced converged-data checks pass. The evidence records the unchanged guard
explicitly, rather than treating the shadow finding as new data progress.

Ready-batch audit: INCONCLUSIVE because `ccafe54d1d` predates outgoing base
`6d6ae2f4d5` and affected CreateAHeroManager lacks a current receipt. Carry
both adoptions and their affected consumers into the next scheduled census;
no complete consumer selection/loss clearance is claimed.
