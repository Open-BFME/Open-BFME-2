# Geometry bounding-shape canonical-header attempt, 2026-11-05

Inspected revision: `d51d8d64d1`. Source: `Code/GameEngine/Source/Common/System/GeometryInfoRva006BD9C0.cpp`; existing matched row `0x006BD9C0`, 567 bytes (the source's 560-byte comment is stale).

The original normal build passes 1/1 bodies and six compiler float literals. A trial removes the private GeometryInfo class and duplicate GeometryType enum, includes the canonical Geometry header, and accesses the existing STLport shape-vector type through a const reference at canonical `field2c`. It produces 554 bytes, with different register allocation from the prologue and different vector-pointer reload behavior around GeometryShape assignment. Casting through `(const char *)this + 0x2c` instead of `field2c` leaves that mismatch. See [the unlanded trial patch](canonical-vector.patch).

The source is restored. Header debt, compiler flags, pins, aliases, data and ledger rows remain unchanged; no nonmatching body remains under Code. Next step: reconcile the canonical opaque-vector view's access/alias behavior with the original embedded STLport vector before owner acceptance. No TU merge or link/census gain is claimed.
