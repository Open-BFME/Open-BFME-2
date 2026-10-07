// ?Set_Ambient@DX8Wrapper@@SAXABVVector3@@@Z
// partial score=1.0 date=2026-10-07
// cl: /O2 /G7 /arch:SSE /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// Set_Ambient: native 0x00117F50..0x00118033, RET, 227B.
// BFME1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f dx8wrapper.h inline:
// Ambient_Color=color; Set_DX8_Render_State(D3DRS_AMBIENT,Convert_Color(color,0)).
// Target establishes Ambient_Color VA DEDC70 and setter call 6615F.
// Exact under O2/SSE/G7; inlined x87 helper reused from verified colour unit.
// Pending linking: kept state-setter definition and snapshot-name providers
// differ from retail; no new row or pin is asserted.
#include "always.h"
#include "vector3.h"

class DX8Wrapper {
public:
    static unsigned Convert_Color(const Vector3&, float);
    static void Set_Ambient(const Vector3&);
    static void Set_DX8_Render_State(unsigned long,unsigned);
private:
    static Vector3 Ambient_Color;
};

// Adapted from reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/
// dx8wrapper.h. Clean C++ casts and SSE intrinsic variants failed matching,
// so retain this donor x87 sequence. Input is expected clamped to [0,1]; the
// control word selects truncation for RGBA*255, packs AARRGGBB, then restores
// the caller's rounding mode. The target-derived col=0 initialization remains.
WWINLINE unsigned int DX8Wrapper::Convert_Color(const Vector3& color,float alpha)
{
	const float scale = 255.0;
	unsigned int col = 0;

	__asm
	{
		sub	esp,20					// a, r, g, b and saved FPU control word
		fwait
		fstcw		[esp+16]				// save caller control word
		mov		eax,[esp+16]
		mov		edi,eax
		and		eax,~(1024|2048)	// clear rounding-control bits
		or			eax,(1024|2048)	// select truncation
		sub		edi,eax
		jz			skip
		mov		[esp],eax
		fldcw		[esp]
skip:
		mov	 esi,dword ptr color
		fld	dword ptr[scale]
		fld	dword ptr[esi]
		fld	dword ptr[esi+4]
		fld	dword ptr[esi+8]
		fld	dword ptr[alpha]
		fld	st(4)
		fmul	st(4),st
		fmul	st(3),st
		fmul	st(2),st
		fmulp	st(1),st
		fistp	dword ptr[esp+0]
		fistp	dword ptr[esp+4]
		fistp	dword ptr[esp+8]
		fistp	dword ptr[esp+12]
		mov		ecx,[esp]
		mov		eax,[esp+4]
		mov		edx,[esp+8]
		mov		ebx,[esp+12]
		shl		ecx,24
		shl		ebx,16
		shl		edx,8
		or			eax,ecx
		or			eax,ebx
		or			eax,edx
		fstp	st(0)
		cmp		edi,0
		je			not_changed
		fwait
		fldcw	[esp+16]				// restore caller control word
not_changed:
		add		esp,20
		mov		col,eax
	}
	return col;
}


void DX8Wrapper::Set_Ambient(const Vector3 &color)
{
    Ambient_Color=color;
    Set_DX8_Render_State(139,Convert_Color(color,0.0f));
}
