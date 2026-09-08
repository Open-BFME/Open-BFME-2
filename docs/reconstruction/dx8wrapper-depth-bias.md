# BFME2 projection depth-bias reconstruction

The recovered role `bfmeSetProjectionDepthBias(float)` matches the complete
380-byte routine at RVA `0x11F1C0`. Its final return is at `0x11F33B`, followed
by four alignment bytes before the next function. The original source spelling
is not established; the legacy BFME1 `Set_DX8_ZBias(int)` declaration is not used
as a type or identity claim.

The argument is independently a float: the entry loads it with `movss`, compares
it directly with the cached float, and performs floating-point multiplication
without integer conversion. A zero-only caller would not establish that type.
The function returns if the bias is unchanged, caches the new bias, copies the
16-float projection, and adjusts element `[3][2]` when the near and far distances
differ:

```cpp
applied[3][2] -= (far * near / (far - near)) * (bias * 0.000625f);
```

The compiled equality tests preserve the retail unordered/NaN behavior. The
constant is independently verified as `0A D7 23 3A` at VA `0xBD0D20`, the exact
single-precision representation of `0.000625f`. No integer bias conversion or
hardware Z-bias capability test occurs in this body.

The global roles are established by all their loads and stores in the complete
routine, rather than inferred from names or copied relocation words:

| Role | Retail VA |
| --- | --- |
| Cached float bias | `0xDEDA74` |
| Near distance | `0xDEC4F0` |
| Far distance | `0xDED9F8` |
| Source projection, 16 floats | `0xDEDC30` |
| Applied projection, 16 floats | `0xDEDBF0` |
| D3D9 device pointer | `0xDEDA34` |
| Direct3D call counter | `0xDEDA98` |

The routine calls `IDirect3DDevice9::SetTransform(PROJECTION, &applied)` at
vtable byte offset `0xB0`. Its ordinary typed interface extends the already
verified 17-method reset interface in SDK order through `SetTransform`.
The declarations retain provenance from
[Wine's D3D9 interface](https://github.com/wine-mirror/wine/blob/master/include/d3d9.h).
There are no direct callee pins, exception tables, string literals, or import
aliases in this body. All seven global contracts and the compiler float literal
were independently checked, and all 40 existing bodies in this translation unit
remained exact before adding this claim.
