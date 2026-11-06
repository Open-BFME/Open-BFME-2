# BoneFX native enum-vector allocation contract

Served debt: BoneFXUpdate::xfer487C75/349 calls ParticleSystemID push_back at
2E01C6, whose selected helper previously used the wrong allocation contract.
This is existing code-identity debt, not missing coverage or a lost body.

Repair the current provider BoneFXUpdateUpdate.cpp with the same malloc/CRT
allocation contract as the verified native enum-vector owner:
/D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc. All six original
provider rows and34 consumer rows remain exact. Native provider EH is EXACT.

The full private comparison against NameKeyListHelpersBFME2.cpp establishes:
push49, overflow179, allocator28, copy31 and fill31 all retain the same bytes,
and relocation offsets/types/targets after mapping only the distinct enum
spellings. Every overflow relocation is checked: allocator at+44, copy+62,
fill+103, copy+133 and free+151. The enums remain different application types;
this is a compiler ICF relation, not a recovered common semantic identity.

That comparison is not admission. The owning pin_admission.fold_proof_problems
then independently passes the whole unmasked179B body and recursively certifies
its allocator/copy/fill at68E15/1DD10D/20E400, producing admission-proof.json.
pin_consistency's precheck reports no existing overflow pin. The supported
pin_admission --add command adds exactly one fold-proof pin at148D00, also
recording its hatch admission. Post-admission pin consistency passes. No pin or
baseline was hand-added, and no gate was changed or bypassed.

This closes the missing proof from the earlier chat05 seat2 trial, whose
configured retry was rejected by automatic approval review before execution.
The current read-only owning proof passed before admission, and the supported
admission now completes normally. There is no request to bypass that earlier
review or the repository's one-identity rule; the documented proven-ICF exception
is what the owning verifier accepts here.

Normal40/40,18 strings plus3 empty refs,4 imports, one data row and the provider
parent EH pass. repair_queue.py retire identity removes the one original key
after its fresh-object scan finds it gone and no new keys. The identity register
is changed only by that owning command. One admitted pin increases hatch debt
by one; it is not authored-byte or runtime progress in its own right.

Two-source preview preserves3459 own bytes against older index7bd55416c6,
not a new census gain. Full outgoing consumer audit and actual image/runtime
confirmation remain separate. No real-link, menu, save/load or CRC claim.

Prior evidence: ../bonefx-particle-vector-allocator-20261106-c05-seat2.md.
