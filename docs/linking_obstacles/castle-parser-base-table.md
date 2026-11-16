### Castle-map parser consumer emits an incorrect base table

Status: local trial superseded by upstream b902765169 during rebase. The
current source keeps upstream's ordinary base with one pure parser slot and
its derived override. Fresh full-link/runtime results remain pending.

Retail table 007C9574 contains deleting destructor 000AD930 and __purecall
0003B810. The consumer in SidesListParseCastleTemplateMaps.cpp emitted a
different base table referencing two undefined slot spellings. Making both
slots pure is not a faithful reconstruction of this native table.

The earlier local trial used the existing native base-table provider. novtable
suppresses its local table/deleting helper; its inline destructor explicitly
restores the existing table before unregistering the token, preserving all
retail parent and cleanup bytes. No alias, pin, replacement function or data
definition is added. This retains the footprint view's existing derived slots;
it is not a claim that the full parser hierarchy is reconstructed.

Historical trial build: 9/9 rows, one EXACT EH graph. Provider-inclusive link preview
with BfmeDataChunkParserBinding.cpp and Rva003B241AForwarder.cpp: 3/3 clean,
69 -> 516 own bytes against stale census 0534e78db3. COFF comparison removes
only the local base table and deleting helper, adds no external definition,
and leaves every retained external definition's raw section bytes unchanged.

Evidence: [handoff](../../reverse/attempt_support/castle-parser-base-table.md).
