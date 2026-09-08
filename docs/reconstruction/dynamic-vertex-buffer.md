# BFME2 dynamic vertex-buffer allocation

`BfmeDynamicVBAccess::AllocateNative` reconstructs the complete 384-byte body at
RVA `0x13AEC0`, through the return immediately before the independently decoded
access constructor at `0x13B040`. The recovered type names describe the established
roles and ABI, without asserting original source spellings.

The reference `DynamicVBAccessClass::Allocate_DX8_Dynamic_Buffer` provides the
allocation and reference-ownership algorithm. BFME2 selects one of fifteen pools
using the access object's format index at `+8`, rather than one fixed pool.
The access constructor selects the same index from the 96-byte descriptor array.
The extra argument at `+0xC` controls the native buffer's declaration flag at
`+0x18`. This source preserves the actual pool growth threshold of 5000 vertices,
16-bit pool sizes and offsets, ring-buffer wrap condition, optional NPatch usage,
and add-reference-before-release ordering.

The native vertex-buffer contract is independently decoded through the complete
106-byte constructor at `0x13AC00`. It calls the base constructor at `0x139350`,
stores its own vtable at VA `0xBD2F50`, clears the native buffer member at `+0x1C`,
and calls native creation at `0x1397B0`. The base constructor sets the DWORD
reference count at `+4`, type at `+8`, 16-bit vertex count at `+0xC`, engine count
at `+0x10`, FVF pointer at `+0x14`, and declaration flag at `+0x18`. It allocates
96 bytes for the FVF descriptor and calls its separately verified constructor at
`0x181550`. The native-creation body invokes Device9 CreateVertexBuffer at COM
slot `0x68`. These facts independently establish the four-argument constructor
pin and the 28-byte base / 32-byte native allocation size.

Reference ownership uses the actual nonvirtual increment/decrement and virtual
slot-zero deletion contract from the reference `RefCountClass`. The new source
uses an ordinary base class for that contract. No native resource destructor is
invented or counted as completed by the constructor pin.

All six global roles are independently checked:

| Role | Retail VA |
| --- | --- |
| Fifteen in-use flags | `0xDF29F0` |
| Native buffer pointers | `0xDF2A04` |
| 16-bit offsets / capacities | `0xDF2A44` / `0xDF2A64` |
| Current caps pointer | `0xDEDA7C` |
| Fifteen known FVF values | `0xBD2F04` |

The complete 60-byte FVF table is checked and agrees with the separately verified
descriptor table at `0xBD52D4`. The caps view contains the actual grouped 304-byte
D3D9 aggregate, preceded by display width and height. The NPatch flag at `0x13B`
is independently established by the verified DX8Caps compute/constructor family.
No guessed trailing padding or legacy four-byte stride is used.

The full exception graph is also checked, including all instruction and data
bytes after resolving actual targets: handler VA `0xB65D3B` (10 bytes), function
information `0xD0A2F4` (28), unwind map `0xD0A2EC` (8), and allocation cleanup
`0xB65D30` (11). Cleanup calls the already verified scalar operator delete.
The terminal runtime thunk independently imports `msvcr71.dll!__CxxFrameHandler`.
The `fs:[0]` chain base is separately verified as zero. There are no string or
floating-point literals. Ordinary add-match and pre-commit gates validate the
tracked body; the independent scratch audit is `build/astra_fvf/audit_native.py`.

The sorting allocator is the complete 275-byte body at `0x13A8E0`, including both
return paths and followed by thirteen alignment bytes. It grows one CPU sorting
pool, preserves 16-bit offset/capacity behavior, and uses the same ownership
sequence. Its four globals are the in-use flag at `0xDF2A88`, buffer pointer at
`0xDF2A8C`, capacity at `0xDF2A90`, and offset at `0xDF2A94`.

Restoring the reference's translation-unit-local `static` linkage is necessary:
external declarations produced 287 bytes with extra reloads across reference
updates. The original internal linkage gives the compiler the same information
about aliases, reproducing the full 275-byte body without artificial temporaries
or register controls. The native allocator remains unchanged.

The sorting constructor pin is independently supported by the complete 112-byte
body at `0x139660`. It calls the same base with type 1 and FVF `0x252`, installs
its distinct vtable at `0xBD2F48`, allocates `44 * vertexCount` bytes through the
already verified array allocator, and stores the result at `+0x1C`. The destructor
begins immediately after its `ret 4`. The sorting allocator's four exception
nodes resolve to the same independently audited allocation-cleanup graph as the
native allocator. No constructor or destructor receives duplicate body credit.

Native creation at `0x1397B0` is the complete 271-byte body, ending in `ret 4`
followed by one alignment byte. It acquires the real device mutex through the
ordinary `BFMEDX8DeviceLock` lifetime, translates dynamic/NPatch/software usage
bits, and calls Device9 CreateVertexBuffer twice at most. The second attempt
follows mesh-cache invalidation and managed-resource eviction. The reference's
old texture-age invalidation is absent in this image, while Device9 adds the
null shared-handle argument. Both explicit TnL fallback checks remain present.

Restoring the original inline FVF_Info/Get_FVF/Get_FVF_Size and device-accessor
source structure is necessary to reproduce the retail evaluation order and stack
spills. Replacing those ordinary accessors with raw field/global expressions
produced 251 bytes; explicit locals alone produced 260. The reference accessor
structure emits all 271 bytes exactly, including both native calls and cleanup.

The separate 19-byte eviction helper at `0x11E610` calls the exact Device9
EvictManagedResources slot 5 and increments the independently established API
counter at `0xDEDA98`. Its thirteen following alignment bytes and full device
reference at `0xDEDA34` are checked. The helper closes the creation retry's actual
callee dependency and is explicitly out of line.

The complete creation exception graph comprises its handler `0xB65CF8` (10),
function information `0xD0A2D0` (28), unwind map `0xD0A2C8` (8), unwind action
`0xB65CF0` (8), and guard destructor `0x442F8C` (5). All bytes and targets are
independently checked. The guard destructor reaches the already established
mutex release at `0x120F50`; the runtime thunk names msvcr71's C++ handler.
The SDK-ordered Device9 prefix is included with its Wine source attribution,
through the exact CreateVertexBuffer slot 26. No placeholder slots are used.

The dynamic write-lock constructor and destructor now match their full 247- and
108-byte bodies at `0x13AA00` and `0x13AB00`. The lock holds its owner pointer at
zero, initialized data pointer at four, and actual nontrivial mutex guard member
at eight. Its 12-byte size is asserted. Native access selects DISCARD for offset
zero and NOOVERWRITE otherwise, includes NOSYSLOCK, and multiplies the 16-bit
count/offset by the independently proven FVF stride at `+0xC`. Sorting access
advances a typed 44-byte vertex pointer. Unlock precedes guard destruction.

The original inline native-buffer accessor is necessary to preserve the caller's
separate buffer evaluations; a direct field expression compiled the constructor
three bytes short. Restoring the ordinary accessor matches all 247 bytes, while
the destructor and the four previously claimed allocation/create bodies remain
exact. The SDK-ordered VertexBuffer9 interface uses the actual Lock/Unlock slots
`0x2C/0x30`, including the Device9 `void **` data parameter, and is based on
[Wine's primary d3d9.h declaration](https://github.com/wine-mirror/wine/blob/master/include/d3d9.h).

Both lock bodies independently reproduce the entire same exception graph:
handler `0xB65D1B` (10 bytes), function information `0xD0A25C` (28), unwind map
`0xD0A254` (8), member cleanup `0xB65D10` (11), and guard destructor `0x442F8C` (5).
The member cleanup explicitly adds eight to the saved object before destruction.
This confirms the guard's member offset independently of stack allocation.
All actual mutex/assert/log callees are checked, with no new pins or duplicate
claims for the folded no-op assertion target. Constructor alignment is nine
bytes and destructor alignment is four. No literals or external data globals
are used beyond the separately checked FS exception chain.
