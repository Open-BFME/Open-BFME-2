# Rva8D0D80Result header adoption

The APT interpreter calls the frame publisher at 0x006FBED0 through its
current function. Including the full receiver declaration in place of the
old one-method class changed register allocation in _createObject, first at
offset 980 of 2496 bytes. A forward declaration in the declaration section
and the shared include with the register handlers preserve all 101 rows.
The header adoption tool accepted this consumer.

Three queued implementation views still require receiver evidence:

- Rva006FBED0Cluster.cpp reads a run pointer at +0x28 and a 16-bit count at
  +0x2C. AptScriptFunction.h independently declares creator scope and frame
  stack reserve at those offsets. The routine publishes a frame stack.
- VslotSmallBodiesQ.cpp obtains the protected static spFrameStack through
  AptScriptFunctionBase. The header substitution fails with C2065. The
  AptScriptFunction.cpp TU skeleton identifies the 15-byte 0x00709A00 as
  CreatingNestedFunction, slot 24. Establish its method identity together
  with the 0x006FBED0 call before removing the existing inheritance.
- Rva8D0D80ResultAdd.cpp instead treats its receiver as an object with a
  table at +8. The related find-or-add at 0x006FBBA0 is already rowed on
  Rva006FBC90Owner. Rva006FBE60Cluster selects the published frame or the
  scope at +0x28 as receiver of that find-or-add. Verify the caller of the
  0x006FBB90 tail jump and its owner before adding table fields to the
  shared declaration.

The layout probe rejects both field-reading units with the current opaque
header. Their queue entries and the inheritance-dependent entry remain.
