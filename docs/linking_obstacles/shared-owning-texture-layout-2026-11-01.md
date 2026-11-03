## Shared owning texture layout (2026-11-01)

The separate destructor view is now reconciled with the complete LineGroup
layout in a TU-local header. The existing four-byte RefCountPtr reconstruction
owns +0x24; direct Referent access preserves the two remaining donor providers
without adding assignment/refcount semantics or claiming their ABI debt fixed.
All 27 rows and both native EH graphs pass strict checks; all retained complete
code/relocations remain unchanged. Two redundant destructor optimization hatches
retire. The fresh dae306bc9d index's bounded LinkGuard reports no loss for either
unit. Actual absorption remains for the supported merge.

The preceding 6e00b635d8 wider audit was inconclusive against the old86db074988
index (two receipt gaps, first linegrp.cpp). Fresh strict receipts now cover
the two current units, but wider/global clearance awaits census measurement.
Evidence: reverse/attempt_support/linegrp-owning-layout-20261101/.
