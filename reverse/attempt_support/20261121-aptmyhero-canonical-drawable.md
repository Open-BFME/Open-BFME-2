# AptMyHero008 Drawable: seed-only candidate, full family blocked

Source basis: **874f5012c9df8d970a85919421e15a27f4460dab**, Root-authorized clean
LF tree after normal Matrix3D adoption. Exactly one actual Source-adoption
variant was compiled, in private outputs with BFME_OBJSTORE=off and unchanged
native per-file profiles. Root alone performs production changes and normal
admission. **Do not apply the combined two-file patch.** The Unresolved half adds
an unproved startup initializer and remains blocked. A seed-only candidate is
provided separately, retiring at most one header row; this is zero completed
whole-TU tasks and no new byte coverage.

## Source proposal and target identity

Replace the seed's partial264-byte Drawable declaration with the existing real
GameClient/Drawable.h. In its sole drawable iteration use the existing
getObject()/getNextDrawable() API. No header, guard, macro, optimization,
exception specification, Matrix3D/Vector3 source, row map or baseline is changed.
The already present DrawableFramesPerFlash.h include stays intact.

The old observer declaration used Object* at0xFC and Drawable* at0x104. The
canonical class has those same fields and real inline getters, while representing
the actual1136-byte object, Thing+0/Snapshot+96. This TU owns only pointers:
no Drawable sizeof, complete allocation, by-value copy, object lifetime or vtable
definition. Actual new sections confirm no Drawable vtable is introduced.
`drawable-retail-facts.json` independently contains original PE bytes, nine real
row identities and both15+4-slot tables; `HEADER-PRECHECK.md` explains the family.
The standalone canonical Header CodeView proof is retained separately and is not
misrepresented as a whole-Source debug compilation.

## Strict rows and whole-COFF result

`drawable-adoption-probe.json` contains both normal controls and the one variant:

| Source | Normal control | Candidate | Retained existing row bytes |
|---|---:|---:|---:|
| AptMyHero.cpp |43/43|43/43|4044|
| AptMyHero_Unresolved.cpp |16/16|16/16|1174|

All candidate rows are byte exact, unmasked, with zero unresolved relocations.
Every one of the previous58+13 public strong-code bodies also keeps its complete
bytes and named relocations, beyond merely checking the59 row extents.

The whole footprint **is larger, not identical**:

| Source | Public strong code | Public/weak externals | Physical sections |
|---|---:|---:|---:|
| Seed |58→60|143→145|142→146|
| Unresolved |13→13|70→71|38→42|

`drawable-coff-audit.json` preserves the exact previous runtime/data graph:
142/142 seed nodes and38/38 Unresolved nodes, with zero lost original external or
weak-DEFAULT records, changed local-target edges or changed COMDAT selections/
associations. The four added nodes per source are fully recorded with raw data,
symbol identities and all relocations:

- Seed: getObject7B code +16B DebugF, getNextDrawable7B code +16B DebugF.
- Unresolved:16B .text$yc initializer,4B .CRT$XCU,4B BSS constant,16B DebugF;
  new external BfmeClientFramesPerSecond. This source had no corresponding
  initializer before. Matching old rows alone does not justify adding it.

Some local EH $L/$T numbers and COFF .sxdata symbol-table indices change when
canonical declarations add compiler tokens. The first deliberately lexical
control is preserved in `drawable-coff-strict-label-control.json`. The final
graph proof does not discard their targets: every actual old/new label binds to
the same matched section+offset+type, all local relocation edges are checked,
and every .sxdata DWORD is decoded to an actual same handler role/section/offset.
Its changed raw bytes and both decoded handler lists are explicitly retained.
No code byte or image-address operand is masked by this private audit, and no
production verifier was changed.

## New getter COMDATs and existing heterogeneity

| Existing canonical method | ABI/COFF symbol | Actual new bytes | Selection |
|---|---|---|---|
| Object* getObject() |`?getObject@Drawable@@QAEPAVObject@@XZ`|`8b81fc000000c3`|2 ANY|
| Drawable* getNextDrawable() const |`?getNextDrawable@Drawable@@QBEPAV1@XZ`|`8b8104010000c3`|2 ANY|

Both are real nonvirtual thiscall pointer-return methods, with no explicit
arguments or relocations, reading exactly the two independently proved fields.
All38 existing getObject and7 existing getNextDrawable owners have current
normal compiler/source/header receipts; the audit records every source/object
hash, exact public COFF type role and selection. Their code agrees in37/38 and
6/7 cases. The two pre-existing foreign-layout cases are explicitly **not**
claimed equal or repaired:

- InGameUI.cpp getObject reads+0x88 (`8b8188000000c3`).
- GameClient.cpp getNextDrawable reads+0x90 (`8b8190000000c3`).

Both use the existing ZH Drawable include context, whereas genuine current BFME2
canonical consumers use+0xFC/+0x104. Examples with independently current real
canonical-header dependencies are InGameUI_areSelectedObjectsControllable.cpp
for getObject and InGameUISelectAllAcrossMap.cpp for getNextDrawable. The native
GameClientDrawableTOC.cpp prefix also independently provides the exact+0x104
getter. No claim about repairing the two unrelated existing families follows.

## Native ProviderGuard and publication limits

`seed-native-provider-check-55dd-historical.json` is the completed historical
native check bound to the55dd index inventory. It has no findings, a complete
native reference walk, unchanged kept getter copies under both retail/path
orders, and proves both getter names unreferenced under that inventory.
It does **not** establish the current874f index. The same read-only normal
ProviderGuard check was repeated exactly once after Root's completed index
refresh. **`seed-native-provider-check.json` now names874f5012c9,
2026-11-21 01:32, clean_tree=True.** Its full index SHA-256 is identical before
and after the check. The current result again has zero findings and a complete
native reference walk: both getter names are unreferenced, and even their actual
kept copies remain exactly unchanged under both retail/path orders. The old
snapshot is retained as history only. The final manifest additionally reconfirms
all45 getter-owner observations' source/object hashes, normal compile currency,
and unchanged owner inventories against this current index.

No fallback compilation is used by this check: before/after are the already
compiled explicit private seed objects. No source move, full link, census/index
mutation, smoke run or game runtime is started. Even a clean provider prediction
does not replace Root's native header accept/build, link preview or real link.

## Minimal handoff

- `seed-only-CANDIDATE.patch` and `AptMyHero.drawable.cpp.txt`: sole candidate
  for Root's normal source-only adoption. Source/hash/LF binding is recorded in
  `drawable-final-inputs.json` after the current-index check.
- `AptMyHero_Unresolved.drawable.cpp.txt` and the combined patch preserve the
  blocked tested counterpart only; do not land them standalone.
- Native row receipt, full COFF audit, original retail facts and provider receipt
  above are independent proofs with their stated boundaries.

Existing _$E4/key005B0A53/A06458 shadow debt predates all this work and is left
untouched. ImageCollection remains the separate12/16/C2375 prerequisite in
`../aptmyhero008-image/HANDOFF-BLOCKED.md`. The whole native consolidation item
is still open until its actual all-donor pass conditions hold.
