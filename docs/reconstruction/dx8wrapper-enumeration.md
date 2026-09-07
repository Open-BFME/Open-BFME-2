# BFME2 graphics adapter enumeration

`DX8Wrapper::Enumerate_Devices()` occupies RVA `0x124890` through its return
at `0x124FD2`: 1,859 code bytes. A one-byte alignment instruction and a five-entry
switch table at VA `0x524FD4` make the complete emitted section 1,880 bytes.
The following device-selection routine starts at RVA `0x124FF0`.

The reference performs one D3D8 mode enumeration. BFME2 first rejects devices
below pixel shader 1.1, then enumerates five D3D9 formats separately: R5G6B5,
X1R5G5B5, R8G8B8, A8R8G8B8, and X8R8G8B8. Each mode passes the established
capability filter before insertion into the resolution list. Only adapters
with a nonempty list are added to the three device tables.

## Data layout and source reconciliation

The local `BfmeEnumerationDesc` view retains the reference's nine `StringClass`
fields at `0x00`–`0x20`. The actual 304-byte D3D9 caps start at `0x24`; the
1,100-byte adapter identifier starts at `0x154`; the 24-byte resolution vector
starts at `0x5A0`. The total is 1,464 bytes. This replaces the older shim's
unexplained padding with the fields that the executable actually copies.

`BfmeEnumerationCaps` uses the 740-byte DX8Caps layout already proven by the
complete capability computation and both constructors. Its three strings at
`0x2D4`, `0x2DC`, and `0x2E0` produce the same normal and exceptional cleanup.
Its constructor calls the existing verified caps-copy constructor at `0x12C780`.
The display-format filter at `0x12B330` uses the first two dimension fields;
its format argument is unused, so the retail call passes the D3D format directly.
The recovered view names do not claim original source spellings.

The last code difference was an eight-byte EH-state update before destruction
of the temporary format vector. Restoring `__declspec(nothrow)` on the ordinary
array-deallocation declaration removes exactly that update. The language's
[deallocation contract](https://eel.is/c++draft/basic.stc.dynamic.deallocation)
is non-throwing; the older GameMemory declaration omitted that annotation.
The established retail array-delete wrapper at RVA `0x2FD80` is 21 bytes: it
null-checks the pointer and calls the configured deallocator with array tag 2.
The annotation leaves all 35 previously matched routines in this TU exact.

## Independent verification

The 1,859-byte body, alignment, and all five switch destinations were compared
with the executable. The version-format string `%d.%d.%d.%d` was checked through
its terminating NUL, and its direct IAT reference was independently resolved to
`msvcr71.dll!sprintf`. Nine global DIR32 bindings were checked consistently.

The six direct external call contracts are independently established:

| RVA / bytes | Evidence |
| --- | --- |
| `1221B0` / 417 | Descriptor construction matches the complete emitted body, with nine strings and the resolution-vector vtable. |
| `122360` / 225 | Descriptor destruction matches its complete emitted body and exception graph. |
| `12C780` / 265 | Previously verified DX8Caps caps-copy constructor; the view preserves all argument widths and layout. |
| `12B330` / 36 | Previously verified dimension filter; no format-field dependency. |
| `121550` / 158 | Resolution insertion matches all bytes: scans width, height and depth, then adds only a new triple. |
| `122450` / 188 | Descriptor assignment matches all bytes: copies nine strings, 76 caps DWORDs, 275 adapter DWORDs, and the resolution vector. |

A recursive audit compared 84 emitted code/data nodes covering the caller's
EH graph, its typed descriptors, the format/resolution vector vtables and their
emitted functions. COFF weak aliases from vector-deleting to scalar-deleting
destructors were resolved using their actual auxiliary symbol records. Every
EH runtime edge independently resolves to the named PE import
`msvcr71.dll!__CxxFrameHandler`. Switch labels were checked against their exact
positions inside the verified parent body.

The descriptor assignment's deeper `VectorClass<ResolutionDescClass>::operator=`
at RVA `0x120FE0` was independently decoded as a complete 215-byte vector copy:
self-assignment guard, clear, 16-byte element allocation and construction, then
copying all four fields. Its different constructor inlining is not claimed as
an additional byte-matched body. No relocation exception or pin-consistency
baseline was added.
