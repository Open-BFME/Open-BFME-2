# LookupTablePostEffect: one false-pure slot, body held

Base Rva001164B6 native table RVA 007CFB24 slots 0/2/3/4 all contain retail
__purecall at RVA 0003B810. Leave those four slots pure. Its slot 1 is the
real deleting destructor at RVA 001164B6.

Derived LookupTablePostEffect table RVA 007CFAC8 slot 2 contains RVA
00111DB6, a matched 332-byte function currently rowed as
`?rva00111DB6@Rva00111DB6@@QAEXXZ` in
Rva00111DB6PostFXLookupTable.cpp. Both constructor and destructor objects
instead emit __purecall at slot 2. Slots 0/3/4 already reference concrete
LookupTablePostEffect methods; the deleting slot is concrete too.

Skipped: Rva00111DB6PostFXLookupTable.cpp is held by StarkillerHDX@fleet,
first through RefCountClass and then a direct file claim. The final live
file/RVA dry runs still refuse it. The LookupTablePostEffect scope itself
is available, but repairing only its declaration cannot define the rowed
body under its actual virtual owner. No partial source or ledger rename
was attempted. After release, reconcile that placeholder's owner and apply
the evidence-gated virtual respell, keeping all constructor/destructor
copies and body references together. The TSV records all ten base/derived
slots and their native/current targets.

The complete eight-unit class/reference cohort remains 8/8 LINKS,
2,350 -> 2,350 B against the index. It includes both table emitters, the
seed, factory, base provider and three other base/reference users. No
source changed, and agreeing false-pure tables still need repair.

Current object table emitters:

- Code/GameEngineDevice/Source/W3DDevice/GameClient/LookupTablePostEffectCtor.cpp; SHA256 6a04d0c87eaa7d05417e87befe00b86d574db94e43b048f706f90f2241fe09fa.
- Code/GameEngineDevice/Source/W3DDevice/GameClient/LookupTablePostEffectDtor.cpp; SHA256 5976a0667deaf940cf62c276f69ac08d8e0538598a5ef89926f534facbba8081.

[Slot inventory](lookup.tsv).

Base: `42ba5fba3d67de6fd90e938e491169eea70fd6d2`. Seat: `halilkkaya-codex` in wt_d.
Retail table addresses and targets in the TSV are RVAs; add 00400000 for VAs.
Targets were read as little-endian DWORDs from the retail image through
build.exe_image/rva_to_file_offset. Only those exact addresses were streamed
from functions.csv; the complete function ledger was not materialized.

The TSV inventories each selected slot. Up to three representative matched
names and three source paths are listed independently (not paired);
matched_row_count records the full count. A rowed address alone does not
prove the current declaration's signature, owner, receiver adjustment or
complete vftable contract. Concrete slots are inventoried without that claim.

The initial foreground ./build.sh passed all 99,276 rows and 2,253 data
rows, FULL GATE OK. This handoff changes no Code, row, pin or header.
The link previews below use index 86db074988, 2026-11-01 14:31; they are
scoped predictions, not census or runtime proof.
