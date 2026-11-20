# Particle manager lifetime and table evidence

The real-link 388 image at `5f94f950f4f5` still uses bridges for the
derived particle manager's 20-slot primary table at `0x007C4C70`
and four-slot Snapshot table at `0x007C4C5C`. Both source COMDATs
have only the deleting-destructor slot. The abstract parent at
`0x007E18C8` / `0x007E18B8` is also bridged.

## Parent and slots

`ParticleSys.h` already documents the complete base layout.
The parent constructor and destructor remain rowed as
`Rva001F9D98`. The class-fold dry run refuses to fold that type into
`ParticleSystemManager` because the data ledger names the parent
tables for `Rva001F9D98` and the named virtual at `0x001F9F66` occupies
slot 19 of both the base table and the derived table. The latter is
an inherited slot. A supported owner reconciliation must account for
both installing lifetimes and the inheritance evidence before the
slot providers can move to the shared class.

The derived Snapshot table starts with the verified -0xC deleting
thunk `0x0004CE2E`. Slots 1–3 use the same bodies as the parent:
the one-byte empty hook `0x000B3FD0`, the six-byte name getter
`0x0004CE28`, and the transfer routine `0x001F9105`. The getter and
transfer currently have placeholder owner and member spellings.
The transfer enters with the Snapshot subobject directly. Its
field offsets +0x3C/+0x40/+0x4C are +0x48/+0x4C/+0x58 from the complete
manager, and it subtracts 0xC for calls that take the complete
manager. A forwarding thunk would introduce a new entry shape.

The derived primary table shares 15 slots with the parent. Slot 0
uses its own deleting destructor. Slots 14/16/17/18 replace the
parent's pure calls with `0x0008BB81`, `0x0004CF9A`, `0x0004D47D`,
and `0x0004CB16`. The existing render rows use placeholder class
`Rva0004CA4C`, and `0x0004D47D` has a second matched copy.
`Rva0004CA4C` is a distinct 0x3C-byte object whose constructor and
destructor install `0x007C4C20`. Its 14 code slots are followed by
the value 6 at `0x007C4C58`. The older description of slots 36–37
of that object crosses both table boundaries. Move the two render
methods by their individual rows once the derived owner is
established. A whole-class fold would mix two allocations and
two unrelated tables.

The derived factory at `0x00041DFB` allocates 0xC4 bytes.
The grouped deleting-destructor units B03 and B09 also still
emit tag-constructor tables for the old class views. Check live
consumers before removing those copies in a lifetime transaction.
No runtime result is inferred from the existing real-link image.

## Verified lifetime changes

The two vectors at +0xAC now use the same `RvaSmartPtr12` specialization
as the render passes. The derived factory's 0xC4 allocation and the
base constructor's 0xA8 extent also place the ready flag in the
derived object at +0xA8. The build verifies all 11 rows and both
unwind graphs. The flag move preserves every COMDAT digest and
reference in the scratch comparison.

The five newly registered names are existing STLport folds. Their
actual emitted sizes are 11, 29, 18, 13 and 30 bytes. The first
four link in order from the default constructor callback to the
allocator proxy. The 30-byte destructor calls the shared nonthrowing
range destroy at `0x0004CD64` and `free` at `0x00030830`.
These replace the two alternate-name callbacks. The scoped preview
counts 206 to 307 bytes in this unit, entirely through already owned
folds. The two linked tables still need the owner and slot work above.
