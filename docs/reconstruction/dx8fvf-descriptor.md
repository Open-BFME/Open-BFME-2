# BFME2 extended FVF descriptor

`BfmeFVFDescriptor::Initialize(unsigned,unsigned,bool,unsigned)` reconstructs the
complete 488-byte body at RVA `0x181260`. Its `ret 16` ends at `0x181447`, followed
by eight alignment bytes. `BfmeFVFDescriptor` names a recovered layout; it does
not assert that the original BFME2 source used this spelling.

The Generals FVF implementation supplies the position, blend, normal, color and
texture-coordinate layout algorithm. BFME2 adds a basis flag, an extension count,
extra offsets, and a known-format index. Those additions move the vertex stride
from the old layout's `+4` to `+0xC` and produce a 96-byte descriptor. Dynamic
vertex-buffer reset loops call this initializer at `0x13A821` and `0x13A891`, advance
the descriptor pointer by `0x60`, and operate on the array at VA `0xDF2AA0`.
The distinct constructor at `0x181550` calls this method and then returns `this`;
the initializer itself returns no pointer. Treating it as a constructor produced
two extra bytes and would have asserted the wrong ABI.

The additional-basis flag adds two three-float fields. The count controls an
aligned byte region and further float fields; the names here describe recovered
roles without assigning unproved skinning or tangent semantics. Each of eight
texture slots uses its two-bit FVF encoding and is bounded by the encoded texture
count. A signed integer scan of the fifteen known formats reproduces the retail
compiler's unrolled loop and countdown. No assembler or forced register bindings
are used.

The original bundled DX8.1 SDK, at
`reference/open-bfme-1/build/toolchains/dx81/include/d3d8types.h:577`, defines the
five blend-position constants as `6,8,0xA,0xC,0xE`. The legacy shared shim had
incorrect values for the last four. This recovered body uses an explicit SDK
`XYZB4=0xC`, independently of that shared-header repair.

The only direct callee is the complete six-byte thunk at RVA `0x62AFBC`, whose
`FF 25` operand names IAT VA `0xBBA9E4`. Independent PE import parsing identifies
`d3dx9_27.dll!D3DXGetFVFVertexSize`. Its prototype remains compatible with the
included D3DX8 declaration; the actual imported DLL and export determine identity.
The entire fifteen-DWORD table at VA `0xBD52D4` is verified against emitted object
data, including all 60 bytes. Its first thirteen entries agree with the retained
named FVF enum values; the final two are transformed-position/diffuse formats
with three and four texture sets. Checking only a relocated table base would not
have established those values.

Validation checks the unrestricted object body length, complete relocated code,
all table data, the independently named import, the constructor and both reset
callers, and the previously held `FVFInfoClass::Get_FVF_Name` body. There are no
exception tables, string literals, or floating-point constants in this body.
The reproducible development audit is `build/astra_fvf/audit_initialize.py` in the
worker scratch; ordinary add-match and pre-commit byte gates validate the tracked
source.

The separately claimed four-argument constructor is the complete 36-byte body at
RVA `0x181550`, ending with `ret 16` and twelve alignment bytes. Its sole call
resolves to the verified initializer. Keeping that initializer explicitly out of
line reproduces the ordinary wrapper and its `this` return without altering the
initializer or the retained FVF name formatter.
