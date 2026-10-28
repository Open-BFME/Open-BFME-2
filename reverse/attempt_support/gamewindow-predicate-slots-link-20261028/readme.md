# Native GameWindow predicates: slots6,8,9

Target facts: the table at VA C0BBCC selected by the existing GameWindow
constructor3145F0/destructor314A0C names RVA313913 (16B),31393A (16B),
and8FF78 (12B) in slots6,8,9. The first two compare input callback+1E0
against the existing LeftHUDInput/GadgetPushButtonInput code owners; the
third checks tooltip callback+1EC for null. The emitted bodies are unchanged.

The three false standalone getter owners are withdrawn and tombstoned;
normal add_match individually readmits them as virtual const bool members
of GameWindow. Existing vslot6/vslot8/vslot9 placeholders are retained:
this is target class/slot ownership recovery, not original method-name proof.
The enum/input callback view is a structural ABI choice. Both implementation
sources remain at their existing paths; the current TU map approves no move.
Eight direct gadget table consumers bind the corrected members. All11-slot
GameWindow views touched here agree; both emitted tables remain44B.

Validation: before and after normal builds pass184/184 rows across13
sources and16 native data rows. All13 frozen-definition checks pass. Both
44B emitted table copies now bind slots6,8,9 to the rowed symbols instead
of purecall; the proof JSON independently reads their COFF relocations.
No old getter identity remains in Code/. Ordinary before/after previews
are13/13 LINKS against index73061d9452, retaining4697 authored per-source
bytes. The printed historical4448->4697 delta predates this repair. This
is zero new unique matched bytes and no measured census-linked-byte gain.
No new pin, hatch, source path, compiler override or alias is introduced.

Remaining: slot10 still incorrectly emits purecall while retail uses the
3B shared constant provider0050B5C6, which has many unrelated consumers.
It needs its own ownership/fold analysis and gated consumer repair; no
identity is claimed here. Slot7 is genuinely pure. The old input helper
remains separately rowed because two gadget constructors still consume it.
Full batch closure remains unverified because the census index lacks
consumer metadata; carry the provider/consumer cohort to the next normal
census. No extra full link cycle or smoke was started.

Reference freshness: official BFME1 master was fetched on2026-10-28 and
is392a18ed4b80122bf4c9d71dc27c81a2d149ce9b. Verified build inputs remain
E744. The earlier freshness upgrade is blocked by recorded full-control
DIR32/identity failures; no success stamp is written and no new donor facts
are imported. Narrow current-input verification above is independent.

Model GPT-6; t=7 per body (one homogeneous three-body batch);
lane=R; budget=30m. Normal source commit and publication gates follow.
