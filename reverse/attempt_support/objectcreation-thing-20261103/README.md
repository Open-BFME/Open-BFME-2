# ObjectCreationUpgrade update adopts canonical Thing

The private truncated Thing view is removed from ObjectCreationUpgradeUpdate.cpp.
The canonical header establishes the full0x60-byte base. Keeping Object's next
field at native+0x74 requires its existing padding extent to use sizeof(Thing);
the legacy padding label is retained. All other Object field offsets remain.

The existing TU-scoped twelve-float OCUMatrix3D view still controls the proven
floating-point evaluation order. An explicit view cast at the matrix operation
accepts the canonical Matrix3D return type without changing the operation or
introducing a new type view. The original /G6 SSE compiler profile is unchanged.

All three existing rows, including the complete753-byte update and its EH
records, remain exact in the private comparison and normal verification.
Every retained external code/data definition is identical. The old private
getTransformMatrix return-type spelling disappears; the canonical getter and
compiler array-construction helper appear. That external-definition inventory
does not independently prove whole-image provider selection.

The owning header_adopt_lane accept --class Thing passes its structural, byte
and previously-linking-unit guard, retiring exactly one header-queue entry.
Remaining Object/ObjectCreationUpgrade/ModuleData reconciliation and source
consolidation are separate. No source path, row identity, pin or unique native
coverage changes. No census, full-TU or runtime clearance is claimed.
