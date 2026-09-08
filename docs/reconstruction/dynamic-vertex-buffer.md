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
