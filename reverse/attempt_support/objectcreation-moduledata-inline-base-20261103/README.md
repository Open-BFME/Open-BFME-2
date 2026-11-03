# Canonical ModuleData base with ordinary TU-local empty destructor

Private prerequisite hypothesis,2026-11-03. Source control SHA256:10ff749d4787143b8430c599f1ed85bb4cbb047df549aaf864378507fabd4e46. Candidate includes existing canonical Common/ModuleData.h immediately before the leaf declaration, defines `inline ModuleData::~ModuleData() {}`, derives ObjectCreationUpgradeModuleData from canonical ModuleData, and shrinks only the preceding opaque storage to0x120-sizeof(ModuleData). The existing tail fields, real AsciiString members, leaf destructor, novtable annotation and first-Snapshot naming context remain intact. The inherited Snapshot destructor runs automatically; no legacy reinterpret_cast, explicit base teardown or double-destruction pattern is copied. The storage comment is corrected from+4 to+8 to describe the actual canonical base; this final comment-only correction follows the private code proof.

Sanctioned private Verifier passes ALL23 source rows for control and candidate. All FOUR actual parent EH graphs are EXACT in both. The original46 ordinary external code/data definitions and symbolic relocation contexts compare identically. The ONLY addition is ??1ModuleData@@UAE@XZ: a seven-byte `C7 01 <Snapshot-vtable DIR32> C3` definition. Its body matches native RVA0x0049B47C exactly after its one normal DIR32 operand is accounted for; the relocation at+2 names ??_7Snapshot@@6B@, the same native Snapshot teardown the original leaf used inline.

provider-proof.json inspects the complete symbol sets, including nonexternal symbols, undefined references, weak externals and directives. No ModuleData or leaf vtable, ModuleData deleting helper or new slot-provider body is emitted. Undefined symbol sets are unchanged, and weak/directive sets are identical. The new seven-byte ModuleData destructor's bytes and ordinary relocation also compare identically to the existing cached Rva004ABFD9Dtor.cpp owner object. That cached owner's source sidecar does NOT match current source, so this is explicitly a historical cached-provider comparison, not a current strict receipt. Independent native7B proof and root's subsequent normal/strict/link verification remain required evidence; no global selected-provider claim is made here.

The existing ledger already owns the same ModuleData destructor name at0x0049B47C/7B from Common/Rva004ABFD9Dtor.cpp, gen-alias with fold-proof=Code/GameEngine/Source/Common/System/Snapshot.cpp. No new row, second name, pin, hatch or alias is introduced. Frozen-source analysis calls the owning find_defined_functions parser and mangle_method routine, then applies the tool's current global declared/matched-prefix rules to the actual candidate text. It reports no unmatched source definitions and no new markers, with all23 own rows retained; the new inline body matches that existing global destructor row. Root should still run the actual path-based frozen-file gate after tracked application.

This solves the earlier out-of-line-base-call codegen blocker in a PRIVATE trial. It does not recover the constructor's unmodeled filter-member lifetime or31-slot child table, and does not retire/repoint the separate g_00C577C8 data owner. No shared header, tracked source, ledger, claim, network, check or shared match-cache mutation occurred. Root must apply only against the captured control hash and retain normal23-row/strict/EH/data/link/identity checks. No sourcefile or census gain is claimed by this prerequisite alone.

Tracked completion: exact control hash checked before applying. The actual
path-based frozen-file gate passes; normal23/23, owning ModuleData acceptance
and strict receipts pass. The existing three-row Rva004ABFD9Dtor.cpp owner was
rebuilt through build.sh, replacing the earlier stale-provider evidence with
current normal verification. Its exact7B ModuleData destructor equals the new
inline definition, including the Snapshot relocation. All46 prior ordinary
definitions remain unchanged, with only that already-owned body added. Paired
bounded previews retain1505+100 own bytes and LINKS. No queue record was
retired by this adoption, and no new row/alias/pin/table is introduced.

This clears the prior direct-base-call shape blocker for the current typed
leaf. The constructor's mask-member lifetime,31-slot data owner and the other
four donor prerequisites remain open; no sourcefile or measured census gain
is claimed by this prerequisite alone. Final image selection still belongs
to the scheduled census; retain the established guard data-name follow-up.
