# Rva0055F197 whole-file bridge preflight — blocked, no trial

Inspected against Root's reported fb05fff834 (17de7e integrated). This is a read-only PE/source/scoped-ledger assessment, not a current global index, new CodeView measurement or native pass. EVIDENCE.json contains the actual retail bytes, decoded instructions, exact table words, selected current rows and stable inspected-source hashes.0CPP/PP,0production/claim/Git/cache writes,0task/coverage/runtime credit.

The served source currently owns five rows: constructor55F197/129B, its799A8B/10B handler and799A83/8B unwind, primary deleting body3AEFF6/28B and secondary adjustor3A588E/8B;183B total retained coverage. The task requires the next published real link to stop bridging BOTH tables, preserving these rows. A local source/layout edit alone cannot satisfy that pass.

## Primary table RVA0081D654 — nine actual entries

| Slot | Target RVA | Observed ABI / existing owner |
|---|---|---|
|0|003AEFF6|Deleting destructor: thiscall(unsigned), returns original receiver, ret4; already rowed for Rva0055F197, calls22B cleanup3ABC0B.|
|1|000B3FD0|Bare RET. Current inherited DefaultModuleHeadBase::slot01 is an abstract void/noarg placeholder; a RET alone supplies no original method role/name/return proof. Do not invent a slot stub.|
|2|0003B810|Real __purecall; clone-like inherited Rva003AEEB3::vslot02 remains abstract.|
|3|0055EF39|thiscall(Xfer argument), ret4; calls Version1 then DefaultPhysicsModuleInfo::DoXfer at this+1C. Both pointer carrier Rva0055EF39::xfer and reference-form Rva003ABD20::DoXfer are already rowed.|
|4|00094A9C|fld [ecx+2C];ret, float in ST0. Opaque const getter in Disp8FloatFieldGetters.cpp.|
|5|004F5FA3|lea eax,[ecx+20];ret. Disp8LeaFieldGetters.cpp's void* carrier AND real SceneClass::Get_Fog_Color returning const Vector3& share this RVA. This is a concrete unrelated-owner ICF boundary, not permission for a global class rename.|
|6|003ABD6B|Reads floats+34/+38 into the hidden output pointer at[esp+4], returns that pointer in EAX, ret4. VtableSlotBodiesR3F.cpp uses existing8B Rva00SlotFloat2. Original value-type identity/constness is not established by these instructions.|
|7|0045310D|mov al,[ecx+3C];ret. Opaque unsigned-char const getter in Disp8ByteFieldGetters.cpp; machine body alone also permits bool/byte enum.|
|8|003ABD51|mov al,[ecx+3D];ret; same carrier/ABI limitation as slot7.|

The actual Rva0055BF21 base table0081D638 is exactly four entries:3AEF18,purecall,purecall,purecall. Expanding this shared generated base to nine slots would put the five physics-specific getters in unrelated siblings. The missing slots belong to the derived physics family, not a demonstrated error in that base's four-slot extent.

## Secondary table RVA0081D678 — actual Snapshot surface

Entries are3A588E,B3FD0,3ABD55,3ABD63. The first subtracts1C and tails3AEFF6. Slot2 returns the complete native literal "DefaultModule<CAT_PHYSICS>" at VA00C1C59C; current owners include free int carrier Rva003ABD55Get and real Rva003ABD20::GetSnapshotName. Slot3 subtracts1C and tails0055EF39; both its pointer carrier and Rva003ABD20's reference-form adjustor already exist. The exported canonical DefaultPhysicsModuleInfo table0081BCB0 is also four slots, but its name getter003A612D and transfer0055EECB are DIFFERENT entries. Merely inheriting that canonical header does not produce the required derived Snapshot table.

## Physical layout and source argument

The constructor and template copy003AEBC9 independently construct the info at+1C and stamp both served tables. Canonical DefaultPhysicsModuleInfo is36B/0x24 with Snapshot4B, coordinate+4, float+10, three-word GameClientRandomVariable+14 and bytes+20/+21. Its placement yields whole-object fields+20,+2C,+30,+3C/+3D and a28+36=64/0x40 physical layout model, not a new whole-class sizeof/CodeView measurement. This accounts for all fields currently represented by the served source's fake4B info plus seven private ints/two bytes. A correct canonical-info recovery must REMOVE that duplicate derived payload; replacing only the private info declaration is insufficient.

Important correction: Rva003ABD20Ctor.cpp AND Rva003ABD20Dtor.cpp already combine canonical36B info with those seven ints/two bytes. Under their stated28B common base and4B alignment the declaration arithmetic is28+36+28+2+2padding=96/0x60. The earlier0x5C estimate was an arithmetic error.0x60 is an explicit declaration-model calculation, NOT a new compiler/CodeView observation; existing49B/5B bodies need not use sizeof, so their byte match does not settle complete-class layout.

The129B constructor copies x+0C→this+20 (12B), x+18→this+2C (4B), x+1C→this+30 (12B), and bytes x+28/+29→this+3C/+3D. Thus x is not directly a DefaultPhysicsModuleInfo pointer. Existing DefaultModuleTemplate<3> in DefaultModuleTemplate.h has an independently documented info base at+8 and whole size0x2C, physically fitting this source pattern. That is a useful already-owned type lead; the constructor's int parameter has NOT been independently tied to that whole source-class identity here. No cast/type substitution is authorized by matching offsets alone.

## Concrete prerequisites and supported route

1. Reconcile and normally verify the64B physical Rva0055F197 model across its ctor, both Rva003ABD20 views, destructor-only novtable views and DefaultModuleTemplateCopyCtors consumer. Keep the established14/18 pure construction-stage symbols distinct. The Nov9 package removed aliases, not these class/slot debts; the Oct22 sibling package proves Snapshot/lifetime prefixes, not all nine physics methods.
2. Establish the five primary getter API/type/owner roles plus primary slot1's actual contract. Preserve shared generic and SceneClass owners. Use normal naming/identity/ICF ownership APIs only after target/ABI/name evidence and all affected claims; no raw vtable array, pin/alias or unknown-slot implementation.
3. Converge the already-rowed Snapshot-name and28B/8B Xfer family onto the correct existing owner contracts while retaining all old rows/provider consumers. rename.py function --to-class/--virtual has strict shared-body and ABI checks; its guarded Snapshot getter support does not waive them. add_match.py --icf-owner is an owning whole-byte fold path only with the complete independently proved class/member and provider evidence, not a new unique-body credit or naming shortcut. Generated base headers, if ever changed, require the contract/normal header owner route; no handwritten edits.
4. Only after those prerequisites: Root reserves the entire affected source/class/header/RVA cohort, runs ordinary whole-source/whole-consumer/layout/EH/data/provider gates, and obtains the next published real-link bridge result. Neither a fresh CPP trial nor a full repaired private patch is justified by this preflight alone.

Whole-family current Rva0055F197 spellings occur in exactly the served ctor, Rva003ABD20Ctor.cpp, Rva003ABD20Dtor.cpp, Rva003ABC0BDtor.cpp and DefaultModuleTemplateCopyCtors.cpp among inspected Code files. No additional target is selected, no old scheduling experiments are repeated, and no BFME1 work was performed.
