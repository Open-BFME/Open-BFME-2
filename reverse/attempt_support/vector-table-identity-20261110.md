# Sentence vector identity at 0x001A3B90

Updated 2026-11-12 against bfadd71c4cc. Scope: render2dsentence.cpp's
explicit SentenceDataStruct vector instantiation and the two retained
four-byte-vector fold owners in agg_def.cpp and collect.cpp.

## Target evidence

Retail table 0x007D6C24 has six slots: 0x001A3B90, 0x00196920,
0x001A3720, 0x00154A30, 0x001964F0 and 0x00154BE0. The 178-byte
Resize at 0x001A3720 allocates four bytes per element: its instruction
at 0x001A373E is `lea eax, [ebp*4]`. The native vector constructor at
0x001A37E0 and AggregateDefClass::Build_Subobject_List supply the
RenderObjClass-pointer context. Character-pointer and RenderObjClass-pointer
deleting-destructor rows both retain the complete 71 bytes at 0x001A3B90.

The donor SentenceDataStruct view is a surface pointer followed by two
16-byte rectangles, hence 36 bytes. Its emitted vector table selected a
715-byte Resize. The folded deleting destructor alone could mask that
different element type; it did not establish ownership of the retail table.
This follows the earlier RendererDataStruct alias retraction in 2dca491cbc,
whose own eight-byte-element table is 0x007D3BC8.

These are target bytes and current source facts. The donor record spelling
is not evidence that retail used that record type at 0x001A3B90.

## Repair

Replace the full SentenceDataStruct vector instantiation with its assignment
member instantiation. This preserves the existing native 61-byte record
assignment at 0x0053FFCE without emitting the unrelated vector lifetime and
table. Expose the nested record type in the TU-scoped donor view so that the
member instantiation is legal; data layout is unchanged.

Retract the false SentenceDataStruct deleting-destructor row and document it
in deleted_rows.csv. The primary fold owner is agg_def.cpp; collect.cpp's
retained character-pointer alias now cites that owner. Every byte of the
withdrawn row remains covered. No source path, pin or hatch is added.

## Verification and limits

- Private comparison: all 28 remaining source rows exact; 109 retained
  COMDATs identical, 14 removed, none added or changed. The removed set is
  the sentence vector lifetime/table machinery and unused comparison/ID
  helpers. The existing record assignment remains emitted.
- Normal three-source build after the 2026-11-12 pull passes: agg_def.cpp
  60 rows, collect.cpp 17, render2dsentence.cpp 28. Frozen-file check passes.
- Current link_check verdicts against census 2026-11-12 17:55 at
  9ca25659d0: all three LINKS. agg_def 4,887 -> 4,887 bytes; collect
  786 -> 786; render2dsentence 1,320 -> 1,249. The 71-byte accounting
  decrease is the retracted alias, not lost physical code coverage.
- The upstream 2026-11-10 metadata repair has already separated the renderer
  and pointer table addresses. This change does not rewrite data_ledger.csv.
  A full generated refresh would require current objects for every input;
  direct native-pointer searches alone do not establish exhaustive bindings
  because COFF addends may be nonzero.

The served table's published real-link pass test remains pending until a
new image measurement selects the repaired inputs. Local byte and link
checks are not evidence that the game runs. The neighboring 0x007D3BC8
renderer bridges and agg_def's 0x008E0BC4 PrototypeClass/BfmeMsg identity
remain separate work (LINK-619).
