# BFME2 sorting-buffer draw conversion

The recovered role `bfmeDrawSortingPrimitive` matches the complete 539-byte
routine at RVA `0x11D710`. The final return at `0x11D92A` is followed by five
alignment bytes before render-state application. All code and all five nodes
of its C++ exception metadata are independently verified.

This is the fallback invoked by the recovered six-argument draw routine when
both vertex and index buffers use sorting storage. Its five arguments are
32-bit unsigned values. The entry explicitly rejects polygon counts and vertex
counts above 65535 before passing counts to the 16-bit access constructors.

The ordinary C++ reconstruction preserves both temporary buffer lifetimes:

1. Allocate dynamic vertex access using format-table index 5 and extra argument
   zero. Lock it under the device mutex, copy the selected 44-byte sorting
   vertices, unlock, then bind the native D3D9 stream and nonzero FVF.
2. Compute the index count for list, strip, or fan input. Allocate and lock a
   dynamic index buffer, copy and rebase 16-bit indices, then unlock and bind it.
3. Submit the retail triangle-list draw, update the same statistics, and destroy
   index access before vertex access. The 16-bit index loop counter is preserved.

The older source's `IndexBufferExceptionFunc` try/catch sequence is absent from
this image and is not retained. D3D9 stream offset, separate base-vertex argument,
FVF binding, and one-argument index binding replace the legacy device ABI.
Explicit native-buffer locals preserve the retail evaluation of buffer handles
before the COM call. No assembly, emitted bytes, custom calling convention, or
unverified padding is used.

The dynamic vertex-access layout is independently established by its 83-byte
constructor at `0x13B040` and already verified 80-byte destructor at `0x13A780`:

| Field | Offset |
| --- | --- |
| Format pointer / buffer type | `0x00` / `0x04` |
| Format-table index / extra argument | `0x08` / `0x0C` |
| 16-bit vertex count / vertex offset | `0x10` / `0x12` |
| Vertex-buffer pointer | `0x14` |

The constructor indexes 96-byte format records at VA `0xDF2AA0`. The destructor's
24-byte view was already held under `BoxDynamicVBAccessClass`; this patch reuses
its actual ABI and grants no duplicate body credit. Dynamic index access keeps
the already verified 12-byte layout, constructor `0x139240` (55 bytes), and
destructor `0x138BE0` (72 bytes).

Both write-lock objects have an owner pointer at zero, data pointer at four, and
an empty but nontrivial device-lock member at eight, making them 12 bytes.
This is established by actual unwind actions, not inferred from stack size:

| Lock | EH unwind map | Unwind action |
| --- | --- | --- |
| Dynamic vertex | VA `0xD0A254` | VA `0xB65D10` |
| Dynamic index | VA `0xD0A190` | VA `0xB65C50` |

Both actions load the saved object, add eight to `this`, and tail-call the
five-byte guard destructor at VA `0x442F8C`. That destructor jumps to the device
mutex release at VA `0x520F50`. Constructors acquire the same mutex through
`0x11F520`; normal destruction releases it after native-buffer work. The member
contract agrees with the preexisting `BFMEDX8DeviceLock` reconstruction in
`reference/shims/indexbuffercount/dx8indexbuffer.h`.

The vertex write-lock constructor/destructor are the complete 247/108-byte
routines at `0x13AA00/0x13AB00`. Index write-lock constructor/destructor are
218/120 bytes at `0x138CA0/0x138D80`. Their native buffer access, device lock,
reference-count operation, return ABI, and member cleanup were independently
decoded before introducing the narrow view pins. No callee body is counted as
completed by those pins.

The caller's complete exception graph consists of its handler at VA `0xB64F60`,
28-byte function information at `0xD0925C`, 16-byte unwind map at `0xD0924C`, and
two eight-byte destructor actions at `0xB64F50/0xB64F58`. Their real constructor
and destructor targets were resolved before comparison. The final runtime thunk
independently imports `msvcr71.dll!__CxxFrameHandler`.

All six global bases agree with the independently established state and device:
render state `0xDEE5D8`, device `0xDEDA34`, API-call counter `0xDEDA98`, vertex
counter `0xDEDA54`, index counter `0xDEDA58`, and draw counter `0xDEDA6C`. The
`fs:[0]` exception-chain relocation is separately checked as zero. There are no
string or float literals in this body. All 43 previously verified functions in
the translation unit remain exact.
