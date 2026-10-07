// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// DX8Wrapper::Convert_Color_Clamp, retail 0x0012617C (399 B), directly after
// the out-of-line Clamp_Color at 0x0012611E (DX8WrapperClampColor.cpp), the
// same pair and order as BFME 1's 0x0090F3FA / 0x0090F460.
// Donor: reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/
// Rva0090F460ConvertColorClamp.cpp. Target facts: the color arrives by value
// (four floats at [ebp+8], plain ret), the no-CMOV path tests
// CPUDetectClass::HasCMOVSupport (0x00A08D2C) and clamps with SSE compares,
// the CMOV path is Zero Hour's integer clamp, and the conversion is Zero
// Hour's x87 Convert_Color asm inlined with BFME 2's col=0 store (the same
// initializer as dx8wrapper.h's Convert_Color(Vector3,float); retail's
// "and [ebp-4],0"). Both asm blocks are the upstream header's own inline asm:
// cmovnb and the fldcw/fistp sequence are not reachable from C++ under VC7.1.
// Size-optimized like retail (/O1: "and [ebp-4],0" for col=0), so the four
// SSE clamps are written out rather than looped: /O1 keeps a loop rolled.

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class Vector4
{
public:
	float X;
	float Y;
	float Z;
	float W;

	float &operator[](int index) { return (&X)[index]; }
	const float &operator[](int index) const { return (&X)[index]; }
};

class CPUDetectClass
{
public:
	static bool Has_CMOV_Instruction() { return HasCMOVSupport; }

private:
	static bool HasCMOVSupport;
};

class DX8Wrapper
{
public:
	static unsigned int Convert_Color_Clamp(Vector4 color);

private:
	static __forceinline unsigned int Convert_Color(const Vector3 &color, float alpha);
};

// upstream: GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
// ?Convert_Color@DX8Wrapper@@CAIABVVector3@@M@Z present-unmatched
__forceinline unsigned int DX8Wrapper::Convert_Color(const Vector3 &color, float alpha)
{
	const float scale = 255.0;
	unsigned int col = 0;

	__asm
	{
		sub esp,20

		fwait
		fstcw [esp+16]
		mov eax,[esp+16]
		mov edi,eax
		and eax,~(1024|2048)
		or eax,(1024|2048)
		sub edi,eax
		jz skip
		mov [esp],eax
		fldcw [esp]
skip:
		mov esi,dword ptr color
		fld dword ptr[scale]

		fld dword ptr[esi]
		fld dword ptr[esi+4]
		fld dword ptr[esi+8]
		fld dword ptr[alpha]
		fld st(4)
		fmul st(4),st
		fmul st(3),st
		fmul st(2),st
		fmulp st(1),st
		fistp dword ptr[esp]
		fistp dword ptr[esp+4]
		fistp dword ptr[esp+8]
		fistp dword ptr[esp+12]
		mov ecx,[esp]
		mov eax,[esp+4]
		mov edx,[esp+8]
		mov ebx,[esp+12]
		shl ecx,24
		shl ebx,16
		shl edx,8
		or eax,ecx
		or eax,ebx
		or eax,edx
		fstp st(0)
		cmp edi,0
		je not_changed
		fwait
		fldcw [esp+16]
not_changed:
		add esp,20
		mov col,eax
	}

	return col;
}

// ?Convert_Color_Clamp@DX8Wrapper@@SAIVVector4@@@Z
unsigned int DX8Wrapper::Convert_Color_Clamp(Vector4 color)
{
	Vector4 *clamped_color = &color;

	if (!CPUDetectClass::Has_CMOV_Instruction()) {
		clamped_color->X = clamped_color->X <= 0.0f ? 0.0f : (clamped_color->X > 1.0f ? 1.0f : clamped_color->X);
		clamped_color->Y = clamped_color->Y <= 0.0f ? 0.0f : (clamped_color->Y > 1.0f ? 1.0f : clamped_color->Y);
		clamped_color->Z = clamped_color->Z <= 0.0f ? 0.0f : (clamped_color->Z > 1.0f ? 1.0f : clamped_color->Z);
		clamped_color->W = clamped_color->W <= 0.0f ? 0.0f : (clamped_color->W > 1.0f ? 1.0f : clamped_color->W);
	} else {
		__asm
		{
			mov esi,dword ptr clamped_color
			mov edx,0x3f800000

			mov edi,dword ptr[esi]
			mov ebx,edi
			sar edi,31
			not edi
			and edi,ebx
			cmp edi,edx
			cmovnb edi,edx
			mov dword ptr[esi],edi

			mov edi,dword ptr[esi+4]
			mov ebx,edi
			sar edi,31
			not edi
			and edi,ebx
			cmp edi,edx
			cmovnb edi,edx
			mov dword ptr[esi+4],edi

			mov edi,dword ptr[esi+8]
			mov ebx,edi
			sar edi,31
			not edi
			and edi,ebx
			cmp edi,edx
			cmovnb edi,edx
			mov dword ptr[esi+8],edi

			mov edi,dword ptr[esi+12]
			mov ebx,edi
			sar edi,31
			not edi
			and edi,ebx
			cmp edi,edx
			cmovnb edi,edx
			mov dword ptr[esi+12],edi
		}
	}

	const float alpha = (*clamped_color)[3];
	const Vector3 &rgb = reinterpret_cast<const Vector3 &>(*clamped_color);
	return Convert_Color(rgb, alpha);
}
