# Assisted feedback donor native views

Replace the donor's flat private Player/Object/AssistedTargetingUpdate views
with canonical Player, draft native Object and canonical UpdateModule-derived
0x20 AssistedTargetingUpdate. Access the existing protected m_object and real
Player::m_defaultTeam fields: retail219B at486F35 reads +8 and Player+2EC.
No fields, methods, allocations or runtime behavior are invented.

Normal build3/3 and one literal pass, parent EXACT EH retained, normal/private
code and properties equal. All three previous code definitions/relocations and
their properties are unchanged; no provider added/removed. Local helper getter
variants also matched but emitted two extra getter COMDATs; use direct real
fields instead. header_adopt_lane accept Player passes and retires one queue
row. Two-source preview preserves both files: feedback228 ->228, seed235 ->367.

Known inventory difference: the expanded native header environment renumbers
the compiler-owned internal key guard from $S1 to $S3 at the same verified
addressA038B8. data_check reports this wrong-name in shadow. It is not a new
semantic data object, pin or guessed alias. Keep the protected data ledger as
its owning tool's inventory; do not hand-edit or baseline the finding. Its next
owner regeneration should reconcile the compiler local label. Native function,
EH graph, static key, guard storage and all code/provider facts remain exact.

The prior lifetime split remains blocked by selected implementation/private-
weak COMDAT context, despite2/2 carved rows and57 preserved residual rows.
That failed split wrote nothing; constructor merge landed separately. The
complete destructor claim and mixed-source scope are released for other work.

Publication audit carried from83c586e5fb: INCONCLUSIVE indexc4354285e7,
base3b1f72628ff56035f0e132848d11c71b34aee679, one missing current receipt
(AssistedTargetingUpdate.cpp). Current scoped bytes/EH/data checks passed;
future current-consumer/image measurement remains necessary. No actual image
or runtime claim is made.

## Remaining registered factory view reconciled

The first supported merge passed byte/link verification, but its commit hook
correctly refused the donor's private ThingFactory in the destination. Revert
that pending move and replace the donor's factory declaration with the existing
canonical ThingFactory.h in a separate prerequisite commit. Its newObject
signature is unchanged. Normal3/3, literal, frozen check, EXACT EH and independent
canonical factory acceptance pass; normal/private code/provider properties
agree. No check is changed or bypassed. Retry the merge only after this repair.
