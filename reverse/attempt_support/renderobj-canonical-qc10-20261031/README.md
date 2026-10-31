# RenderObjClass canonical header, qc-10, 2026-10-31

Target: game.dat SHA256 f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640, image base 0x400000.

## Target facts

The matched default constructor at RVA 13BF00 (262 bytes), copy constructor at 13B430 (427 bytes), destructor at 13BE20 (79 bytes), and assignment at 13B5F0 (217 bytes) establish the existing 0xC4 layout. The primary table is VA BD2F68, the secondary table BD2F60; destruction adjusts this by eight for MultiListObjectClass. compiled-layout.json retains the compiled base/field/slot offsets. retail-slots.tsv reads the primary table directly from the PE and matches only explicitly RenderObjClass-named ledger owners. Blank owner cells include folded targets and are not assigned another class's name.

The table has slots 0..128. Existing typed declarations are preserved from the BFME2-adjusted header, including inherited Delete_This at 0, destructor at 1, transform validation/set at 20/21, child count/getter at 28/30 and material info at 85. The contract's disputed slots 87,112,114,116,120,121,123,127,128 have explicit target owners in the table (see TSV). Slot122 returns false, slot124 and126 share a ret8 worker, slot125 uses ret4. This establishes ABI widths only for folded leaves, not semantic identities. Existing declaration names for these leaves are donor or prior-recovery facts. Slots129+ from oversized private views are outside this base table and are not added.

The automatic contract instead proposed sizeof4 from 108 opaque-vptr views and a base inferred as Rva000657D9. That majority is not used: complete matched constructor/copy/destructor evidence takes precedence. No missing slot is invented to satisfy those views.

## Header and donors

The pre-existing BFME2-adjusted reference/shims/bfme2renderobj/rendobj.h definition is moved byte-for-byte to the official Code/Libraries/Source/WWVegas/WW3D2/rendobj.h destination. Its old path becomes a compatibility include, retaining one definition and the existing optimization directives. BFME1/ZH declaration names and signatures are donor facts, not proof of original BFME2 source text. No new virtual slot or field is introduced.

W3DLightDrawDoDrawModule adopts the shared RenderObj, math and vector types. An explicit volatile amplitude read retains retail's load-then-multiply operand order after shared WWMath::Sin; it emits the original 467 bytes. The private math helper and its inline assembler are removed.

ResetAllTextureMappers adopts the same header. Its slot5 mesh-view call uses the existing neutral _bfme_ro_v3 declaration with an explicit pointer cast; its slot28 child count uses Get_Num_Sub_Objects and its release uses the real inherited Release_Ref. Its 165 bytes remain matched. No new alias or pin is added.

## Verification

Boat only: build.sh passes both donors; header_adopt_lane accept passes both with link prediction; the constructor/copy/destructor/assignment units retain all35 matched rows. header_adopt_lane gate-cost finds210 dependent ledger sources and zero red chunks. Normal commit-hook results are recorded in the bundle handoff. Existing private views are recorded with the header lane queue writer; no unverified adoption is claimed.
