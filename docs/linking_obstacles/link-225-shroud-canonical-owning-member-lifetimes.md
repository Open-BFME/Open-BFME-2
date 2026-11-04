### LINK-225: Shroud canonical view lacks owning-member lifetimes

Status: Blocked for the owning constructor; six caller views repaired locally.
Updated:2026-11-04; inspected revision `821be0eb4735c240b9da490d9084fd537b6e4813`.

Completed: six W3DShroud header keys are retired with46 existing code/EH
rows and all173 external code instances/data/relocations retained. The
native header's88-byte footprint and the selected accessed projections are
proved separately; the old partial source views are not complete-size proof.
The counted getter keeps its copy/Add_Ref/Release_Ref bodies and the cell getter
keeps its two-byte low-nibble view. No shared header or allocator is changed.

Remaining: W3DShroud.cpp's owning texture, counted holder and custom tree need
supported canonical lifetime before its constructor/EH can adopt the header.
That source's W3DShroud key stays open. This does not reopen LINK-095's already
verified holder-cleanup repoint: it concerns adopting the full owning class.

[Member-lifetime prerequisite](../../reverse/attempt_support/shroud-owning-member-prerequisite-20261104-1105.md).
[Scoped batch proof](../../reverse/attempt_support/shroud-batch-20261104-1105.md).
Census confirmation and full-image linking: not claimed.


#### Batch1105 affected-consumer audit

The native audit result is INCONCLUSIVE; affected consumer closure is not fully verified. No full-image or runtime proof follows from unchanged object contents. See [combined audit](../../reverse/attempt_support/header-cleanup-audit-20261104-1105.md).
