# Assisted module-name getter split prerequisite

The supported split carves486E76/6 and preserves48 residual rows but macro
composition removes the destination class declaration and fails at its sizeof
check. Nothing was moved. Reconcile the donor into explicit normal C++:
canonical UpdateModule-derived0x20 AssistedTargetingUpdate declaration plus
out-of-line protected GetSnapshotName returning its existing string. Other
48 getter bodies remain untouched. No rows/paths/pins/aliases change here.

Normal49/49,49 literals and frozen check pass. All49 original code/provider
properties and relocations remain equal, and normal/private code/properties
agree. This prepares the source for the supported split; no row moves by hand.

Publication audit carried from424d4d55df: INCONCLUSIVE index4d5e6a2f0f,
base9d04d5d0ac0fe0e83a9aae58bbe00fcd3ff0a8b6, one missing current receipt
(AssistedTargetingUpdate.cpp). Scoped13/13,3EXACT EH and63table checks passed;
current outside-consumer/image/census confirmation remains necessary.
