# Preserve the actual attack-move state destructor owner

Actual integrated source2023f0eeb0 real link fails with LNK2005 for
??1AIAttackMoveToState@@UAE@XZ. The byte-verified79B owner is already in
AIStates.cpp at00345CAB, and its normal28B deleting destructor at00349FF5.
The separate constructor TU's incomplete class declares no destructor, so
newly completed virtual roles cause it to emit a second implicit definition.
The original vtable and the already-owned member establish the actual class
destructor; this is not a new inferred method or forwarding implementation.

Declare that existing virtual destructor in the constructor's own class view.
The normal two-source byte/relocation/constant/import gate passes, the current
constructor object no longer defines the second destructor, and the real
AIStates source remains byte-identical. No body, field, flag, pin, alias,
weak-name policy, baseline or linker override is changed. The larger private
class-view reconciliation remains separate debt. No new body/coverage credit.
The other two unresolved symbols and the final real-link pass remain open.
