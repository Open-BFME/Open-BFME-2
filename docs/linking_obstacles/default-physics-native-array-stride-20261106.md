### DefaultPhysics deleting-destructor identity and array stride
Status: Repair prepared / awaiting automated verification. Updated2026-11-06.

The named DefaultPhysics vector destructor was placed at3A69B4 with a32-byte private donor view, but its exported constructors and tableC1BCB0 require native3A77A7/75B with stride36. Cylinder/Line owns the distinct32-byte69B4 operation. Only complete destructor49B47C folds.

The existing source now uses the canonical header and its SAME named row is deliberately corrected by supported replacement to77A7; the old name/address is tombstoned. Source path unchanged, no TU approval invented. Provider/private equality and707/707 rows plus the data row across all six actual consumer sources pass. Header debt stays open: owning acceptance requires broader canonical adoption; no baseline or check is changed to conceal that refusal.

Next: publish through normal hooks, verify final consumer/table closure in the next real image, and retire the now-unused opaque77A7 replica only with its retained-row/provider checks. No current crash/CRC/runtime result is established. [Native evidence and scope](../../reverse/attempt_support/default-physics-native-stride-20261106/README.md).
