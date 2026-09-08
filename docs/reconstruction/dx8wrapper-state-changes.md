# BFME2 render-state application

`DX8Wrapper::Apply_Render_State_Changes` is the complete 746-byte function at
RVA `0x11D930`. Its final return is `0x11DC19`, followed by six alignment bytes.
The 737-byte catalog entry omitted the final alternate-mask branch and return.
The identity is independently corroborated by the unique direct call to the
retail `ShaderClass::Apply` body at `0x137590`, the dirty-bit tests, and every
state-binding operation. The claim covers the complete function.

The reconciled behavior differs from the older source in three substantial ways:

* The boolean at VA `0xDEDA20` skips shader, texture, material, light, and transform
  application. Stream/index updates still run. The function retains mask
  `0xCC3FF` in that mode and the two matrix-identity bits (`0xC0000`) otherwise.
  The variable has a recovered behavioral name; its original spelling and all
  callers that set this mode remain unclaimed.
* Texture state holds 16 four-byte owning references. A texture-binding helper
  handles null and live references, rather than this caller directly applying a
  raw texture pointer.
* D3D9 stream binding includes offset zero, and index binding has one argument.
  Vertex buffers store an explicit declaration-mode flag. FVF binding occurs
  when that flag is false; testing whether the FVF value itself is nonzero is
  incorrect for this image.

The source uses narrowly recovered field views. No meaning is assigned to
unexamined buffer prefixes or the two unused offset fields. All accesses agree
with these retail offsets from the render-state base VA `0xDEE5D8`:

| Field | Offset |
| --- | --- |
| Shader / material | `0x000` / `0x004` |
| 16 texture holders | `0x008` |
| Four 104-byte lights | `0x048` |
| Four light-enable bytes | `0x1E8` |
| World / view matrices | `0x1EC` / `0x22C` |
| Two vertex-buffer types / index type | `0x26C` / `0x274` |
| Two vertex-buffer pointers / index buffer | `0x280` / `0x288` |

The vertex-buffer view uses format pointer `+0x14`, declaration-mode byte
`+0x18`, and D3D9 buffer pointer `+0x1C`. Index buffers use native pointer `+0x14`.
The format view reads FVF at `+0` and stride at `+0xC`. This stride is independently
confirmed by the format constructor at RVA `0x181260`: it stores the FVF at zero
and stores the vertex-size calculation at `+0xC`, then adjusts that same field
for optional vertex extensions. The legacy format header's `+4` stride is not
used. The first prototype matched 745 of 746 bytes; this single corrected field
produced complete equality.

Direct callees were audited separately before pinning:

* `ShaderClass::Apply`, RVA `0x137590`: the independently reconstructed 2,838-byte
  shader-state routine. This caller supplies the shader at the state base and
  invokes it under dirty bit `0x8000`. The callee remains a separate unmatched
  body, with no completion credit from this pin.
* `VertexMaterialClass::Apply`, RVA `0x13D570`: the complete 1,084-byte body through
  return `0x13D9AB` sets material from `this+8`, configures lighting/color sources,
  applies eight mapper/UV pairs, then handles the ATI `0x5144` / `0x5157..0x515A`
  texture-transform workaround. The older source establishes the material and
  mapper identity; the full appended vendor path was independently decoded.
* Recovered texture-holder apply role, RVA `0x132AF8`: the complete 139-byte body
  through `ret 4` at `0x132B80` loads the held pointer from offset zero. Null
  references release the old cached native texture and call D3D9 `SetTexture`;
  live references test/prepare the texture through virtual slots `0x28/0x2C`,
  dispatch its backend at pointer `+0x14`, and finish through virtual slot `0x40`.
  This establishes the owning-holder ABI without claiming original symbol names.
* `VertexMaterialClass::Apply_Null`, RVA `0x13D180`: the existing verified
  128-byte body. Its exact ledger binding is reused.

All 11 global bases were independently checked: state mask `0xDEC4F4`, skip mode
`0xDEDA20`, state object `0xDEE5D8`, caps `0xDEDA7C`, device `0xDEDA34`, light-enable
cache `0xDED5F0`, call counter `0xDEDA98`, and matrix/vertex/index/light counters
`0xDEDA4C/54/58/5C`. The proven 740-byte caps layout supplies its `+0x2B0` limit.
The ordinary D3D9 interface follows
[Wine's SDK declarations](https://github.com/wine-mirror/wine/blob/master/include/d3d9.h),
with `SetTransform`, `SetLight`, `LightEnable`, `SetFVF`, `SetStreamSource`, and
`SetIndices` at vtable byte offsets `0xB0/CC/D4/164/190/1A0`.

There are no exception tables, embedded switch tables, string literals, compiler
float literals, or direct imports in this body. All 41 previously held functions
in the translation unit stayed exact before this addition.
