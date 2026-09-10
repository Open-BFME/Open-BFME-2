// ?Check_Depth_Stencil_Support@DX8Caps@@AAEXW4WW3DFormat@@ABU_D3DCAPS8@@@Z
// partial score=0.945 date=2026-09-09
// cl: (compiled as part of Code/Libraries/Source/WWVegas/WW3D2/dx8caps.cpp --
// this body is ALREADY IN THE TREE at dx8caps.cpp:959 behind a
// present-unmatched marker; this stash exists for the analysis, not the source)
//
// THE SIZE IN reverse/reloc_names.csv IS WRONG. It records 122 bytes. Retail's
// cc padding starts at 0x0012B3A0 + 146, and our emitted COMDAT is also 146:
// the last 24 bytes are the switch JUMP TABLE, which belongs to the body. A row
// claiming 122 would stop in the middle of the table. Claim 146.
//
//   tail at +146:  cc cc cc cc cc cc cc cc cc cc cc cc cc cc 8b 44
//
// WHAT IS LEFT: exactly 8 bytes, and all 8 are one register-allocation choice.
// Retail keeps the caps members in ecx and the vtable in edx; we do the
// opposite, and the setge/store that follows inherits it (dl vs al).
//
//   off  71   8b 0b  mov ecx,[ebx]        <- ours 8b 13  mov edx,[ebx]
//   off  79   8b 10  mov edx,[eax]        <- ours 8b 08  mov ecx,[eax]
//   off  86   51     push ecx             <- ours 52     push edx
//   off  88   8b 4b 04                    <- ours 8b 53 04
//   off  90   51     push ecx             <- ours 52     push edx
//   off  93   ff 52 28  call [edx+0x28]   <- ours ff 51 28
//   off  99   0f 9d c2  setge dl          <- ours 0f 9d c0  setge al
//   off 101   88 94 3e  mov [esi+edi+..],dl <- ours 88 84 3e  ..,al
//
// Everything else already agrees, INCLUDING the jump table's own DIR32 entries
// and the `cmp eax,0Dh` range guard that proves the switch spans 70..83 (the
// D3D9-only D3DFMT_D32F_LOCKABLE and D3DFMT_D24FS8 sit past the loop bound of
// 81 but inside the switch). The instruction sequence, the scheduling, the
// `lea ecx,[ecx]` alignment padding at +0x2d and the loop shape are identical.
//
// SO THIS IS THE ALLOCATOR WALL, not a source defect. The load ORDER already
// matches retail exactly -- caps member first, then Direct3D at this+0x2D8,
// then the vtable -- so reordering the source cannot be the lever; MSVC simply
// names the two scratch registers the other way round.
//
// REASONED-OUT, so do not spend time on it: hoisting `retail->direct3D` into a
// local does NOT help, in either position. Retail's load order is caps member,
// then Direct3D at this+0x2D8, then the vtable. Our source already produces
// exactly that order. A local declared ahead of the loop, or ahead of the
// call, would load Direct3D FIRST and reorder the two loads -- trading eight
// bytes of register naming for a real instruction-order divergence.
//
// NOT YET TRIED (do this before assuming it is unreachable):
//   - /Oa, ALONE (it must not be combined -- /Ow, /Oa /Ot, /Oa /Og, /Oa /Ob2
//     and /Oa /Ox all revert to the un-optimised allocation). It moved
//     time_get::do_get_time from 2 to 3 callee-saved registers. Caution:
//     dx8caps.cpp carries many matched rows and shares its `// cl:` line with
//     all of them, so `Functions: FAIL n/m` is the regression check.
//
// ALREADY REFUTED here: nothing. No flag sweep has been run against this body.
// Do not record one as refuted without measuring it.

// The body as it stands in dx8caps.cpp:959.
void DX8Caps::Check_Depth_Stencil_Support(WW3DFormat display_format, const D3DCAPS8& caps)
{
	BFME_DX8Caps_DepthStencilFields *retail = (BFME_DX8Caps_DepthStencilFields *)this;
	if (display_format==WW3D_FORMAT_UNKNOWN)
	{
		for (unsigned i=0;i<118;++i)
		{
			retail->supportDepthStencilFormat[i]=false;
		}
		return;
	}

	for (unsigned i=70;i<81;++i)
	{
		switch (i)
		{
		case 70: case 71: case 73: case 75: case 77: case 79: case 80:
		case 82: case 83:
			retail->supportDepthStencilFormat[i]=SUCCEEDED(
				retail->direct3D->CheckDeviceFormat(
					caps.AdapterOrdinal,
					caps.DeviceType,
					(D3DFORMAT)display_format,
					D3DUSAGE_DEPTHSTENCIL,
					D3DRTYPE_SURFACE,
					(D3DFORMAT)i));
			break;
		default:
			break;
		}
	}
}
