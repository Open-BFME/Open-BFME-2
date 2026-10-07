// cl: /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Semantic/source lead: ZH dx8wrapper.h Set_Ambient and Convert_Color at
// BFME1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f; reused x87 helper from
// verified BFME2 SceneClass_Render.cpp (donor BFME1 6583b3c1ff).
// The saved x87 rounding-control word and four FISTP conversions require
// the original donor inline assembler; the wrapper and vector copy are C++.
class Vector3 {
public:
    float X,Y,Z;
    Vector3 &operator=(const Vector3 &other) {
        X=other.X; Y=other.Y; Z=other.Z;
        return *this;
    }
};
class DX8Wrapper {
public:
    static void Set_DX8_Render_State(unsigned long state,unsigned value);
    static unsigned Convert_Color(const Vector3 &color,float alpha);
    static void Set_Ambient(const Vector3 &color);
};

__forceinline unsigned DX8Wrapper::Convert_Color(const Vector3 &color, float alpha)
{
	const float scale = 255.0;
	unsigned int col = 0;
	__asm
	{
		sub	esp,20
		fwait
		fstcw		[esp+16]
		mov		eax,[esp+16]
		mov		edi,eax
		and		eax,~(1024|2048)
		or			eax,(1024|2048)
		sub		edi,eax
		jz			skip
		mov		[esp],eax
		fldcw		[esp]
skip:
		mov	esi,dword ptr color
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
		mov	ecx,[esp]
		mov	eax,[esp+4]
		mov	edx,[esp+8]
		mov	ebx,[esp+12]
		shl	ecx,24
		shl	ebx,16
		shl	edx,8
		or		eax,ecx
		or		eax,ebx
		or		eax,edx
		fstp	st(0)
		cmp	edi,0
		je		not_changed
		fwait
		fldcw	[esp+16];
not_changed:
		add	esp,20
		mov	col,eax
	}
	return col;
}

// Native00117F50..00118033, cdecl RET0: copy three float colour components
// to VA00DEDC70, pack with alpha0, then set D3DRS_AMBIENT (139) through the
// independently matched wrapper at 0006615F. This complete target behaviour
// supports the ZH dx8wrapper.h Set_Ambient identity and ABI. The ambient
// vector's original data symbol is not pinned; retain its measured address.
extern Vector3 g_Va00DEDC70;

void DX8Wrapper::Set_Ambient(const Vector3 &color)
{
    g_Va00DEDC70 = color;
    Set_DX8_Render_State(139, Convert_Color(color, 0.0f));
}
