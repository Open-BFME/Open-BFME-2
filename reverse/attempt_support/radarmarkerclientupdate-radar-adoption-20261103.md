# RadarMarkerClientUpdate: Radar adoption prerequisite

Follow-up to [view reconciliation](radarmarkerclientupdate-consolidation-20261103.md),
at d5895eb54c. No merge or nonmatching source remains from these trials.

`tu_skeleton.py --merge` accepted the seed and updater: 11 rows, one donor
removed. The merged source passed 11/11 byte checks, frozen-file checks,
and local link prediction (178 -> 316 authored bytes). However,
`tu_ownership.py --staged` correctly refused B1: moving the updater would
introduce its private canonical Radar declaration into the destination.
The merge and its ledger, TU-map and header-queue repoints were reverted.

Radar's canonical header declares slot 12 as
`Rva0004E4C9 &vslot12(Rva0004E4C9 &, const char *)`.
The updater's existing view calls the same physical slot with a smart-pointer
return by value. The target calls `[vtable+0x30]`, marks the temporary live
afterward, and pushes returned EAX into the smart-pointer assignment.
These are target calling-convention facts, not proof of the factory's original
C++ signature or the opaque return type's identity.

Trials using the shared Radar declaration:

- An explicit local output object and `vslot12` call compile, but move the
  EH state before the call and emit LEA of the output instead of using returned
  EAX. `./build.sh` rejects the body and parent-bound funclet.
- A free function pointer with `__thiscall` is rejected by the retail compiler
  (C4234).
- Reinterpreting `&Radar::vslot12` as a member pointer returning the updater's
  smart-pointer view compiles, but emits a thunk call and different register
  allocation. The body and parent-bound funclet do not match.

Next step: reconcile the factory's canonical return interface with its callers
before retrying Radar adoption and the two-source merge. Do not transfer the
private Radar view or bypass ownership. The separate DrawableModule getter and
Rva00362EC7 vtable prerequisites still apply to the destructor donor.

The published getter/updater reconciliation remains exact. No aliases, pins,
hatches, shared headers or baselines were changed by these trials.
