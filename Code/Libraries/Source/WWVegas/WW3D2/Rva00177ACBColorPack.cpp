// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Reference: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// Rva0090F950PackColor.cpp and Rva0090FBA0ConvertColors.cpp, with ZH
// dx8wrapper.h clamp/pack helpers. Original entry owners remain unknown.
// Native177ACB..177C7B (432B) writes one packed color; native177CA8..177E7B
// (467B) reads 16B colors and advances the destination by the byte stride.
// Both preserve the HasCMOVSupport flag at RVA A08D2C, the complete scalar
// clamp fallback, and the donor's established CMOV/x87 codegen blockers.
// Target col=0, explicit four-component clamps and the donor's field-by-field
// copy constructor reproduce both complete bodies. No callee pins are needed.
// The existing converted sibling at12617C independently supports these
// compiler-machine helpers; ordinary C++ does not reproduce cmovnb or the
// x87 control-word/truncation protocol under VC7.1. The algorithms are C++.
// Types represent only the directly read three/four-float value layouts.

#include "cpudetect.h"

class Rva00177ACBColor3
{
public:
	float X;
	float Y;
	float Z;
};

class Rva00177ACBColor4
{
public:
	float X;
	float Y;
	float Z;
	float W;
	Rva00177ACBColor4(const Rva00177ACBColor4 &other)
		: X(other.X), Y(other.Y), Z(other.Z), W(other.W) {}

	const float &operator[](int index) const { return (&X)[index]; }
	float &operator[](int index) { return (&X)[index]; }
};

// TU-local: the DX8Wrapper::Clamp_Color symbol is owned by DX8WrapperClampColor.cpp
static __forceinline void PackColorClamp(Rva00177ACBColor4 &color)
{
	if (!CPUDetectClass::Has_CMOV_Instruction()) {
		color.X = color.X <= 0.0f ? 0.0f : (color.X > 1.0f ? 1.0f : color.X);
		color.Y = color.Y <= 0.0f ? 0.0f : (color.Y > 1.0f ? 1.0f : color.Y);
		color.Z = color.Z <= 0.0f ? 0.0f : (color.Z > 1.0f ? 1.0f : color.Z);
		color.W = color.W <= 0.0f ? 0.0f : (color.W > 1.0f ? 1.0f : color.W);
		return;
	}

	__asm
	{
		mov esi,dword ptr color
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

static __forceinline unsigned int Rva00177ACBConvertColor(
	const Rva00177ACBColor3 &color, float alpha)
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
		jz rva0090f950_fpu_unchanged
		mov [esp],eax
		fldcw [esp]
rva0090f950_fpu_unchanged:
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
		fistp dword ptr[esp+0]
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
		je rva0090f950_fpu_restored
		fwait
		fldcw [esp+16]
rva0090f950_fpu_restored:
		add esp,20
		mov col,eax
	}
	return col;
}

void rva00177ACBPackColor(unsigned int *out, const Rva00177ACBColor4 *color)
{
	Rva00177ACBColor4 clamped_color = *color;
	PackColorClamp(clamped_color);
	*out = Rva00177ACBConvertColor(
		reinterpret_cast<const Rva00177ACBColor3 &>(clamped_color), clamped_color[3]);
}

static __forceinline unsigned int Rva00177ACBConvertColorClamp(const Rva00177ACBColor4 &color)
{
    Rva00177ACBColor4 clamped_color=color;
    PackColorClamp(clamped_color);
    return Rva00177ACBConvertColor(reinterpret_cast<const Rva00177ACBColor3 &>(clamped_color),clamped_color[3]);
}
void rva00177CA8ConvertColors(unsigned int *out,int stride,const Rva00177ACBColor4 *colors,int count)
{
    for (;count;--count) {
        *out=Rva00177ACBConvertColorClamp(*colors);
        ++colors;
        out=(unsigned int *)((char *)out+stride);
    }
}
