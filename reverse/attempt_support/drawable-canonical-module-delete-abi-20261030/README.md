# Drawable destructor canonical Module and deleting ABI

Replace the last private Module in the header queue with the canonical header.
Keep its pointers and array traversal. A declaration-only slot0 ABI view
expresses MSVC's scalar deleting destructor: flags0 destroys the object and
returns the allocation pointer for the separate free. This is not an original
Module method name or a complete derived-class reconstruction.

Native 0x00279484 pushes zero, 0x00279485 calls slot0, and 0x00279487/488 pass
the returned EAX to the existing free at 0x0002FD60. The pointer returned by a
deleting destructor must be preserved, including for adjusted subobjects.
The existing 28-byte ObjectModule scalar deleting owner at 0x004A10FD
independently witnesses the flags argument, conditional free and returned
allocation. No hand-authored thunk, implementation, pin or alias is added.

All 12 rows, the complete 633-byte parent, its EXACT EH graph and all 24 code
definitions/relocations pass the private probe. Every non-debug section,
loadable definition, undefined name and relocation is identical. The partial
ABI view has only a virtual declaration; it emits no table or body. The owning
Module acceptance tool retires its key, the last remaining Module queue item.
Normal/strict verification retains all 12 rows; ordinary preview preserves
LINKS/643 authored bytes against ccafe54d1d. This does not claim new native
coverage, whole-image link clearance or census progress.
