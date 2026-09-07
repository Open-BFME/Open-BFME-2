# BFME2 device reset reconstruction

`DX8Wrapper::Reset_Device(bool)` begins at RVA `0x122600` and occupies 1,111
bytes, ending in `ret` at `0x122A56`. Nine `CC` bytes separate it from
`Set_Swap_Interval` at `0x122A60`. The previous 475-byte catalog extent stopped
inside its control flow. The source reproduces the complete body, including
failure reporting, both resource-enumeration phases, and normal cleanup.

The Zero Hour reference's reset routine omitted BFME2's resource registry and
effect handling. The reconstructed function uses ordinary C++ owning references
and a D3D9 device declaration. D3D9 `Reset` occupies virtual slot `0x40` and
consumes the independently corrected 56-byte presentation structure. The method
order follows [Wine's D3D9 declaration](https://github.com/wine-mirror/wine/blob/master/include/d3d9.h).

## Callee contracts

Names beginning `Bfme` or `bfme` express recovered behavior. They do not claim
that the original source used those spellings. Only the caller is newly counted;
these declarations do not count their external callees as reconstructed bodies.

| RVA / bytes | Independent evidence |
| --- | --- |
| `61F110` / 21 | Nullable registry at VA `E09C0C`; forwards a type tag to `621480`, whose 69-byte body locks the registry, starts iteration, and stores the filter. |
| `61F310` / 175 | Produces a four-byte owning reference. Its 224-byte iterator at `6214D0` advances the registry and compares virtual type tag slot `34` with the saved filter. |
| `131D99`, `15142A` / 50 each | Typed assignment checks `TEX` (`544558`) or `FXSH` (`46585348`). Successful conversion calls the already verified 40-byte `RefCountPtr<TextureClass>::operator=` at `424D0`; a wrong tag calls the 19-byte nullable clear operation at `4D75B`. |
| `61ED10` / 36 | Already established `TextureBaseClass::Release_Ref`. Decrements WORD `+4`; zero plus the disposal flag causes virtual dispatch at slot `20`. The holders assert no legacy texture payload layout. |
| `132CAD` / 44 | Checks the resource, backend `+14`, backend COM pointer `+8`, and default pool `+50`. Releases the COM pointer through slot `8` and clears it. |
| `132CD9` / 54 | Recreates a missing default-pool texture using seven saved fields. The 199-byte backend method at `1310E3` stores those creation arguments and calls the texture creation helper at `120720` under the device lock. |
| `151553`, `151575` / 34 each | Guard resource, backend `+14`, and effect pointer `+4`; invoke effect slots `114` and `118`. These are `ID3DXEffect::OnLostDevice` and `OnResetDevice` in [Wine's effect declaration](https://github.com/wine-mirror/wine/blob/master/include/d3dx9effect.h). |
| `69E440` / 1 | Both renderer phases call the same empty, folded body. The renderer global is established by device-dependent initialization. No exclusive helper identity or separate body is claimed. |
| `12A400` / 67 | `Debug_Statistics::Begin_Statistics`: clears eleven counters, calls established `Record_Texture_Begin` at `129DE0`, then tail-calls `DX8Wrapper::Begin_Statistics` at `11D140`. |
| `133283` / 151 | Locks the device and the queue, invokes `IUnknown::Release` on every queued pointer, erases the full vector range, and unlocks. All cleanup and the final return were inspected. |
| `62B16A` / entry | HRESULT-to-symbolic-name switch. Cases include `8004D00B` → `XACT_E_NOISORETAIN` and `800706B9` → `RPC_S_OUT_OF_RESOURCES`; shared epilogue at `636F86` ends in `ret 4`, confirming stdcall. Exact SDK function spelling is unasserted. |
| `38790` / 33 | Established `Debug::SkipNext(bool)` captures its return address and forwards the address and flag to virtual slot `5C`. The Debug virtual prefix is independently used by `profile_alloc_memory.cpp`. |
| `13A840` / 150 | Dynamic vertex-buffer shutdown releases fifteen format buffers and the sorting buffer, resetting their usage, sizes, and offsets. |
| `11FD10` / 226 | Render-state invalidation writes sentinel `12345678`, releases cached engine buffers and material, and clears sixteen owning texture handles. |
| `122510` / 232 | Default states use `RasterCaps::FOGRANGE` then the reference's fog, material, color, and bump-matrix settings. |

The reset body clears shader-constant arrays, tests cooperative level, resets
the device, and counts attempts. Failure builds the three exact NUL-terminated
messages; the fiftieth failure executes the established Debug crash sequence.
Success optionally recreates the typed resources and resets the cached state.
The `SkipNext` static overload is declared after its virtual overload because
VC7.1 groups overloaded methods at their first declaration; this preserves the
independently known `0x60` virtual slot.

## Exception and relocation verification

The complete emitted exception graph was recursively compared with the image,
resolving every code edge and data relocation:

- Handler VA `B65208`, 10 bytes, calls a complete six-byte import thunk whose
  PE import is independently `msvcr71.dll!__CxxFrameHandler`.
- Function-info record VA `D09520`, 28 bytes; unwind map VA `D094D8`, 72 bytes.
- Nine unwind actions at VAs `B651C0`, `B651C8`, `B651D0`, `B651D8`, `B651E0`,
  `B651E8`, `B651F0`, `B651F8`, `B65200`, eight bytes each.
- Nullable reference destructors fold to the same complete 12-byte body at
  VA `57098D`, which calls the established WORD-reference release operation.
- String destruction uses the complete five-byte tail-call at VA `465F5B`.

The final ordinary source was checked for all 1,111 code bytes, every REL32
callee, all 16 emitted EH nodes, three NUL-terminated string references, and
consistent global DIR32 references. No float literal is present. No relocation
exception or pin-consistency baseline was added.
