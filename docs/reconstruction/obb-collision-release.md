# Oriented-box collision release configuration

The tracked collision translation unit omitted NDEBUG. Assertions changed
compiler-local calling conventions, register lifetimes, and control flow in
five substantial routines. Restoring the release configuration reproduces the
retail implementations with the source algorithms unchanged. Both SSE and SSE2
were independently checked; the existing SSE2 choice remains in use.

| Routine | RVA | Executable bytes |
| --- | --- | --- |
| intersect_obb_obb | 7277C0 | 3084 |
| ObbCollisionStruct constructor | 728810 | 309 |
| compute_contact_point | 728E50 | 4667 |
| compute_contact_normal | 72A0D0 | 1185 |
| collide_obb_obb | 72A5C0 | 4059 |

All 17 previously held bodies remain exact. The five complete bodies account
for 13304 code bytes; compiler tables and trailing alignment are not counted.
The contact-point contribution has 4667 code bytes, one NOP for table alignment,
15 four-byte switch entries, and then eight CC alignment bytes. Every table
entry was checked against the same COFF section's actual label offset. All
float literal payloads and direct callees were independently verified, including
the existing 276-byte OBBox Compute_Point implementation. The full family was
checked together before any new rows were added, including the inner functions
called by the outer collision dispatcher.

The broad drift scanner's suggested 728ECB location lay inside the contact-point
body. The actual entry 728E50 was established from the image boundary, complete
source matching, and the caller. No locator suggestion was accepted as a pin.
