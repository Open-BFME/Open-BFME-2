# ObjectCreationUpgrade native bases prerequisite

Private proof only, 2026-11-03. Candidate replaces the standalone ten-placeholder-virtual ObjectCreationUpgrade class with canonical UpgradeMux then canonical UpdateModule bases. Their native eight-byte plus0x20-byte layouts place the existing status and flag fields at+0x28/+0x2C. It includes UpgradeMux.h, UpdateModule.h and BehaviorModule.h at the old class position, after the unit's existing Player/Module/Snapshot declarations; no first-Snapshot naming context is reordered. A preexisting later UpgradeMux include is harmless under its guard.

The two owned method identities remain unchanged: rva004B463C and static rva004B3FF5. The existing slot9 call v09(0) becomes inherited setUpgradeExecuted(false), preserving native virtual dispatch/ret4. The old duplicate data pointer becomes (UpgradeData0C*)m_moduleData, and the old object pointer becomes inherited m_object. No copy of the canonical bases, pointer alias field, guessed extra member or new named body is introduced. A protected virtual xfer(Xfer*) declaration is added without a body to support later donor reconciliation.

Sanctioned tu_skeleton.Verifier passes ALL19 matched source rows for both control and candidate, with zero missing RVAs and no verifier errors. All29 external code/data definitions compare exactly including ordinary symbolic relocation contexts: no additions, removals or changed definitions. In particular this prerequisite emits no new vtable or constructor/destructor provider. The complete ordinary external union is preserved; this does not verify full local/.sxdata state, final library/COMDAT selection, the complete leaf class or ownership of its retail vtables. rva004B463C remains neutral rather than being renamed or made a new canonical override.

Current source passes find_declared_unmatched.py. Candidate retains the seed's existing m_status28/m_flag2C names; the separate Xfer donor currently uses m_status/m_flag. Before a later supported merge, reconcile those donor field references using the lane's class-view tool or a separately verified prerequisite. This probe itself does not merge or split any source, claim a source-file reduction, retire header debt or establish a census gain.

Root may apply the candidate only while the control hash still matches current source, then run ordinary byte/data/EH/identity/strict/link checks before a normal commit. candidate.cpp, control.cpp, proof.json and objects are scratch evidence. No tracked edit, claim, network or shared build-cache mutation was performed by this helper.

Tracked application: current source matched the private control SHA256 before
applying this exact candidate. Normal nineteen-row/data/EH verification and
strict reusable receipts pass; bounded link preview preserves680 own linked
bytes. The complete29 external code/data definitions remain identical in the
private control comparison. No emitted vtable or changedprovider identity
is claimed. Subsequent Xfer composition still needs supported class-view
reconciliation of its status/flag members before a fresh approved TU merge.
