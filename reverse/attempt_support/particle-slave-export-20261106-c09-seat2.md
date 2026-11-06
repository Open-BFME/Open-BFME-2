> Superseded during recovery publication rebase: current master repairs this exact exported return and its destructor-fold prerequisite. See [upstream repair and its verification scope](create-slave-system-export-20261106-noro.md). The interrupted proposal and recovery inspection below describe their earlier revisions; do not apply the archived draft again.

> Recovery review at `8bb483ac9115`: this interrupted proposal was not byte-verified by its worker. The constructor, destructor and slave-provider sources are unchanged since `f15737ff46b` (`git diff --quiet f15737ff46b HEAD -- <three sources>` exits 0). The existing attempt at 0x001F9CF3 already documents the exact handle-destructor identity boundary. No repeated compiler trial or source change is claimed. All original claims are released.

# Particle slave return identity: chat 09 seat 2

Inspected base: f15737ff46b. Picker: `next_work.py --claim --shard 25/30`.
Target: 0x001F9CF3, 165 bytes, ParticleSystemTemplateCreateSlave.cpp.

Target facts: reverse/exports.csv:1553 (ordinal 1552) gives the exact
`FXParticleSystem::ParticleSystemTemplate::createSlaveSystem(bool) const`
name and `TrackingPtr<FXParticleSystem::ParticleSystem>` return type.
The current owner uses the neutral `rva001F9CF3` with a 12-byte handle.
The constructor calls it once; the destructor has an unused declaration.
Current frozen-source checks passed for all three sources before edits.

Prior attempt: re_attempts.log records the same export/return repair passing
1/1 but blocked by a peer claim on 0x002115C5. That prerequisite is now claimed
by this worker with the provider and both caller scopes. Existing owner
`?rva002115C5@Rva002115C5@@QAEXXZ` has the 11-byte guarded unlink body.

Donor facts: Zero Hour's particle semantics explain the lookup/factory branch,
but do not establish BFME2's template return name. No new donor-name claim.
Structural inference: retain the existing three-word intrusive representation
and copy/assignment/unlink operations while using the exported template type.
The manager factory's existing handle converts through the proven base assignment.

This is a return-signature respell beyond rename.py's function-identifier
operation; docs/naming.md permits a hand canonical rename at that unsupported
boundary. It is not a virtual decoration change. The old row is tombstoned,
all three existing declarations are updated, and retail ABI evidence retained.

Verification: pending. No real-link or runtime improvement measured.

## Recovery disposition

Do not apply this draft directly: the constructor cleanup would require the exported TrackingPtr destructor at 0x002115C5, whose body already has multiple registered owners and existing BfmeParticleSystemHandle bindings. Resolve the shared handle identity and move its consumers through supported tools before removing an owner; no second body or hand alias is justified. Keep the current byte-matched sources and the unverified proposal in recovery evidence.
