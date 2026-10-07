// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Native0006F0BB..0006F1A6, cdecl(bool, Vector3 const&, float, float).
// Semantic/source lead: the already byte-verified SceneClass_Render.cpp fog
// wrapper, derived from BFME1 6583b3c1ff and the ZH dx8wrapper.h Set_Fog API.
// The original standalone identity is not established; keep an RVA name.
// Target facts independently establish the four fog globals, ShaderDirty,
// render states36/37, and x87 AARRGGBB colour conversion with alpha0.
// The original donor x87 helper is required for its saved rounding-control
// word and four FISTP conversions; ordinary MSVC7.1 /arch:SSE casts do not
// express that codegen machinery. No naked body or machine-byte emission.
class Vector3 { public: float X,Y,Z; };
class ShaderClass { public: static bool ShaderDirty; static void Invalidate() {ShaderDirty=true;} };
class DX8Wrapper {
public:
 static bool FogEnable;
 static unsigned FogColor;
 static void Set_DX8_Render_State(unsigned long state,unsigned value);
 static unsigned Convert_Color(const Vector3 &color,float alpha);
};
extern float g_Va00DEDA28;
extern float g_Va00DEDA2C;

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

void rva0006F0BB(bool enable, const Vector3 &color, float start, float end)
{
	DX8Wrapper::FogEnable = enable;
	DX8Wrapper::FogColor = DX8Wrapper::Convert_Color(color, 0.0f);
	g_Va00DEDA28 = start;
	g_Va00DEDA2C = end;
	ShaderClass::Invalidate();
	DX8Wrapper::Set_DX8_Render_State(36, *(unsigned *)(&start));
	DX8Wrapper::Set_DX8_Render_State(37, *(unsigned *)(&end));
}

