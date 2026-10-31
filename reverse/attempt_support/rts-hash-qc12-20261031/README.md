# Shared rts::hash primary, qc-12
Base8C5FD5E859; queue5208. MoveToFormationGroupOrder had a private primary
template implementing identity cast to size_t. MoveToGroupOrderCtor already
included RtsHashView.h, whose primary was empty; MoveToGroupOrder includes
that same header and supplies an explicit NameKeyType specialization.
Move the existing identity operator unchanged in type/signature/semantics to
the shared primary and replace the formation donor's entire private primary
with the shared include. Preserve the explicit NameKey specialization intact.
Register the shared primary's existing namespace/type spelling; no original
retail template spelling is newly recovered. It remains a documented donor lead.

This is an empty-state, nonpolymorphic functor before/after. No field, base,
virtual slot, lifetime or copy behavior changes. All three actual users are
listed above; rg confirmed no other include consumers. 30/30 owned native rows
pass before and after. Both served donors pass header acceptance, with one new
adoption and the other already shared. Frozen checks pass source/header.
All128 complete externally defined CODE functions across the three objects
retain the same symbol sets, full bytes and relocation triples: zero added,
removed or changed definitions (50+46+32). This includes the NameKey-specific
user; no hashing fallback or newly emitted helper is substituted. The proof
filters true code sections and function symbols, never treating static data as
function evidence. No virtual slots exist for this functor.

No rows, pins, aliases, hatches, source paths or tool code change. Header hooks
must verify the full three-source dependent scope. Link-check acceptance is a
prediction against the published census, not new LINKED credit. Shared obstacle
register is held elsewhere; this README is the proposed cleared-scope entry.
The remaining MoveTo group-order/GroupOrder layout and virtual-provider debt
is separate; no unrelated class view or table was promoted here.
