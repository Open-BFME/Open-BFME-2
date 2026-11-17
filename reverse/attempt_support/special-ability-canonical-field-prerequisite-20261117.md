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
