# SpecialAbilityUpdate canonical-field prerequisite

This is a source preparation for the official SpecialAbilityUpdateDtor.cpp merge, not a class fold, placement repair or resolved-symbol claim. Work was isolated from the parent full gate at base13d2e8e275 with BFME_OBJSTORE=off and BUILD_POOL32.

## Preserved descriptive-name evidence

The main source's existing private SpecialAbilityUpdate view used the following field names. The canonical header already names the same offsets/types differently. Only that class's declaration and unqualified member references were reconciled (22 identifier occurrences):

| Existing private name | Canonical name | Offset | Type |
|---|---|---|---|
| m_prepSoundLoop | m_34 | 0x34 | AudioHandle, typedef unsigned int |
| m_packSoundHandle | m_38 | 0x38 | AudioHandle, typedef unsigned int |
| m_previousTarget | m_50 | 0x50 | Coord3D |
| m_approachFrames | m_78 | 0x78 | unsigned int |
| m_7c | m_7C | 0x7C | bool |
| m_approached | m_83 | 0x83 | bool |

These prior descriptive names are retained here as existing-source evidence, not newly accepted semantic names. A later canonical naming pass should evaluate their original uses. The separate SpecialAbilityUpdateModuleData::m_prepSoundLoop at +0x10 and specialAbilityUpdateModuleData->m_prepSoundLoop access are unchanged. No global identifier replacement, type/layout change, new private class, header edit, alias or compiler flag was introduced.

## Measured checks

Official before/after whole-source builds pass35/35 functions, five literals plus one empty string and13 float references. Seven EH graphs are EXACT, with no missing objects or mismatches. Complete external COFF provider comparison has zero additions, removals or changes, and compile_is_current confirms the after object belongs to the changed source. No link behavior changed from this prerequisite alone.

The official bounded merge selected the main unit's34 approved/eligible rows and the Dtor donor's six rows; the whole-source byte gate also checks a further existing source row. The original composed-source trial rejected16 compiler diagnostics over the six names above; its first diagnostic was C2065 m_prepSoundLoop. After this prerequisite the retry reaches LinkGuard, which refuses because the otherwise census-linked Dtor donor would be absorbed into an object still referencing unresolved ??1Rva0044EF5E@@UAE@XZ. No merge was applied. The old constructor-class identity and its consumer cohort still require a coherent official fold; no wrapper or alias is a solution.

Fresh TU evidence approves SpecialAbilityUpdate.cpp for ctor0x0044EF5E and deleting destructor0x004522F0. The canonical destructor donor is an eligible whole-file donor, but the class fold currently refuses the two deleting-destructor ledger spellings at4522F0. Existing frozen duplicate-definition keys and all prepared consumers also remain separate prerequisites. No row was retracted or moved by this change.

Ignored evidence: build/decal-diagnostic/special-ability-fold-preflight/ contains both dry-run logs, full compiler diagnostics, prerequisite before/proposed source and before COFF, field-map.json, prerequisite-provider-proof.json, prerequisite-eh.json and build logs. The copied census index is the old0534e78db3/2026-11-16 index; previews are not fresh real links. Two official blocked attempt records distinguish the original compile failure from the subsequent unresolved-symbol refusal.

## Separate reviewed redundant-G row retraction

The placeholder ??_GRva0044EF5E@@UAEPAXI@Z row at 0x004522F0/28B was retracted in a separate transaction, with an OLD-name tombstone. The existing ??_GSpecialAbilityUpdate@@UAEPAXI@Z row remains at exactly that address and length in SpecialAbilityUpdateDtor.cpp. Its native bytes and both resolved relocations match: +4 calls the real canonical destructor at0x00451F45, +17 calls operator delete at0x0002FD60. The earlier whole-object inventory found the OLD G/E reference only in the main source's own object. This transaction does not delete that emitted body or any reference; the subsequent all-consumer fold must eliminate the old class spelling coherently.

Verification after retraction passes40/40 functions across main and donor (41 before removal of the redundant claim), all literal/float/import checks, and8EXACT EH graphs. Both source files and both complete COFF files are byte-identical to their saved pre-retraction counterparts. External provider additions/removals/changes are all empty; both receipts remain current. Thus no unique address coverage, provider or incoming edge changed. The sole flag-vote set remains O1/SSE/G7,6553->6525 voting bytes. The source text, flags, pins and duplicate-definition baseline were not changed.

This deliberately retains existing displaced canonical ownership temporarily; it does not move a row or claim placement repaired. AGENTS.md's approved-TU rule governs moves; tools/tu_ownership.py A2 checks source changes and A3 new rows. docs/naming.md requires real-row retraction to have its own reviewable commit. Later consolidation must still place the canonical family in its approved SpecialAbilityUpdate.cpp TU. The OLD tombstone does not block the NEW destination name. Frozen duplicate-definition keys and the prepared consumer cohort remain independent prerequisites, not retired by this record.

Evidence: build/decal-diagnostic/special-ability-fold-preflight/retraction/ contains exact before source/object/ledger snapshots, the retired record, after-build.log, proof.json and eh.json. No source merge, class fold, publication or lease release occurred.
