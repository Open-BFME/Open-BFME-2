// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// Particle module template copy constructors (retail 0x003AF184 cluster).
// Each template copy constructs the particle module-info base at 0x003AF50D,
// copies its emission-info member through a null-preserving sub pointer at
// +0x18 (the Cylindrical-assignment idiom from FXParticleSystemModules.cpp),
// and installs its own vftables. All vftable dwords are DIR32 sites the
// gate takes from the target; both calls resolve through the ledger.

class Rva003AF50D
{
public:
	Rva003AF50D(const Rva003AF50D &other);
};

namespace FXParticleSystem
{

class OrthoEmissionVelocityInfo
{
public:
	OrthoEmissionVelocityInfo(const OrthoEmissionVelocityInfo &other);
};

class SphericalEmissionVelocityInfo
{
public:
	SphericalEmissionVelocityInfo(const SphericalEmissionVelocityInfo &other);
};

class CylindricalEmissionVelocityInfo
{
public:
	CylindricalEmissionVelocityInfo(const CylindricalEmissionVelocityInfo &other);
};

}

// Rva003AF184_v0a: matched references place it at VA 0xc1c84c (retail .rdata value 60).
extern "C" char Rva003AF184_v0a = 60;
extern "C" char Rva003AF184_v14a;
// Rva003AF184_vsub: matched references place it at VA 0xc1c874 (retail .rdata value -17).
extern "C" char Rva003AF184_vsub = -17;
// Rva003AF184_v0b: matched references place it at VA 0xc1c860 (retail .rdata value -43).
extern "C" char Rva003AF184_v0b = -43;
extern "C" char Rva003AF184_v14b;

extern "C" char Rva003AF22E_v14a;
// Rva003AF22E_vsub: matched references place it at VA 0xc1c898 (retail .rdata value -17).
extern "C" char Rva003AF22E_vsub = -17;
// Rva003AF22E_v0b: matched references place it at VA 0xc1c884 (retail .rdata value -43).
extern "C" char Rva003AF22E_v0b = -43;
extern "C" char Rva003AF22E_v14b;

extern "C" char Rva003AF34F_v14a;
// Rva003AF34F_vsub: matched references place it at VA 0xc1c8cc (retail .rdata value -17).
extern "C" char Rva003AF34F_vsub = -17;
// Rva003AF34F_v0b: matched references place it at VA 0xc1c8b8 (retail .rdata value -43).
extern "C" char Rva003AF34F_v0b = -43;
extern "C" char Rva003AF34F_v14b;

extern "C" char Rva003AF3F9_v14a;
// Rva003AF3F9_v0b: matched references place it at VA 0xc1c8dc (retail .rdata value -43).
extern "C" char Rva003AF3F9_v0b = -43;
extern "C" char Rva003AF3F9_v14b;

class Rva003AF184
{
public:
	__declspec(noinline) Rva003AF184(const Rva003AF184 &other);

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04: smart member + int, owned by the base copy
	void *m_v14; // +0x14
	char m_info[4]; // +0x18: info head, owned by the sub copy
};

// ??0Rva003AF184@@QAE@ABV0@@Z
Rva003AF184::Rva003AF184(const Rva003AF184 &that)
{
	const void *src = &that;
	((Rva003AF50D *)this)->Rva003AF50D::Rva003AF50D(*(const Rva003AF50D *)src);
	const void *sub_src = src ? (const char *)src + 0x18 : 0;
	FXParticleSystem::OrthoEmissionVelocityInfo *sub =
		(FXParticleSystem::OrthoEmissionVelocityInfo *)((char *)this + 0x18);
	*(void **)this = &Rva003AF184_v0a;
	*(void **)((char *)this + 0x14) = &Rva003AF184_v14a;
	sub->OrthoEmissionVelocityInfo::OrthoEmissionVelocityInfo(
		*(const FXParticleSystem::OrthoEmissionVelocityInfo *)sub_src);
	*(void **)sub = &Rva003AF184_vsub;
	*(void **)this = &Rva003AF184_v0b;
	*(void **)((char *)this + 0x14) = &Rva003AF184_v14b;
}

class Rva003AF22E
{
public:
	__declspec(noinline) Rva003AF22E(const Rva003AF22E &other);

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04: smart member + int, owned by the base copy
	void *m_v14; // +0x14
	char m_info[4]; // +0x18: info head, owned by the sub copy
};

// ??0Rva003AF22E@@QAE@ABV0@@Z
Rva003AF22E::Rva003AF22E(const Rva003AF22E &that)
{
	const void *src = &that;
	((Rva003AF50D *)this)->Rva003AF50D::Rva003AF50D(*(const Rva003AF50D *)src);
	const void *sub_src = src ? (const char *)src + 0x18 : 0;
	FXParticleSystem::SphericalEmissionVelocityInfo *sub =
		(FXParticleSystem::SphericalEmissionVelocityInfo *)((char *)this + 0x18);
	*(void **)this = &Rva003AF184_v0a;
	*(void **)((char *)this + 0x14) = &Rva003AF22E_v14a;
	sub->SphericalEmissionVelocityInfo::SphericalEmissionVelocityInfo(
		*(const FXParticleSystem::SphericalEmissionVelocityInfo *)sub_src);
	*(void **)sub = &Rva003AF22E_vsub;
	*(void **)this = &Rva003AF22E_v0b;
	*(void **)((char *)this + 0x14) = &Rva003AF22E_v14b;
}

class Rva003AF34F
{
public:
	__declspec(noinline) Rva003AF34F(const Rva003AF34F &other);

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04: smart member + int, owned by the base copy
	void *m_v14; // +0x14
	char m_info[4]; // +0x18: info head, owned by the sub copy
};

// ??0Rva003AF34F@@QAE@ABV0@@Z
Rva003AF34F::Rva003AF34F(const Rva003AF34F &that)
{
	const void *src = &that;
	((Rva003AF50D *)this)->Rva003AF50D::Rva003AF50D(*(const Rva003AF50D *)src);
	const void *sub_src = src ? (const char *)src + 0x18 : 0;
	FXParticleSystem::CylindricalEmissionVelocityInfo *sub =
		(FXParticleSystem::CylindricalEmissionVelocityInfo *)((char *)this + 0x18);
	*(void **)this = &Rva003AF184_v0a;
	*(void **)((char *)this + 0x14) = &Rva003AF34F_v14a;
	sub->CylindricalEmissionVelocityInfo::CylindricalEmissionVelocityInfo(
		*(const FXParticleSystem::CylindricalEmissionVelocityInfo *)sub_src);
	*(void **)sub = &Rva003AF34F_vsub;
	*(void **)this = &Rva003AF34F_v0b;
	*(void **)((char *)this + 0x14) = &Rva003AF34F_v14b;
}

class Rva003AF3F9
{
public:
	__declspec(noinline) Rva003AF3F9(const Rva003AF3F9 &other);

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04: smart member + int, owned by the base copy
	void *m_v14; // +0x14
	char m_info[4]; // +0x18: info head, owned by the sub copy
};

// ??0Rva003AF3F9@@QAE@ABV0@@Z
Rva003AF3F9::Rva003AF3F9(const Rva003AF3F9 &that)
{
	const void *src = &that;
	((Rva003AF50D *)this)->Rva003AF50D::Rva003AF50D(*(const Rva003AF50D *)src);
	const void *sub_src = src ? (const char *)src + 0x18 : 0;
	FXParticleSystem::CylindricalEmissionVelocityInfo *sub =
		(FXParticleSystem::CylindricalEmissionVelocityInfo *)((char *)this + 0x18);
	*(void **)this = &Rva003AF184_v0a;
	*(void **)((char *)this + 0x14) = &Rva003AF3F9_v14a;
	sub->CylindricalEmissionVelocityInfo::CylindricalEmissionVelocityInfo(
		*(const FXParticleSystem::CylindricalEmissionVelocityInfo *)sub_src);
	*(void **)sub = &Rva003AF34F_vsub;
	*(void **)this = &Rva003AF3F9_v0b;
	*(void **)((char *)this + 0x14) = &Rva003AF3F9_v14b;
}

// Rva003AF15E_v0: matched references place it at VA 0xc1cf88 (retail .rdata value 87).
extern "C" char Rva003AF15E_v0 = 87;
// Rva003AF15E_v14: matched references place it at VA 0xc1bff8 (retail .rdata value -106).
extern "C" char Rva003AF15E_v14 = -106;
// Rva003AF15E_v18: matched references place it at VA 0xc1cf78 (retail .rdata value 67).
extern "C" char Rva003AF15E_v18 = 67;

class Rva003AF15E : public Rva003AF184
{
public:
	__declspec(noinline) Rva003AF15E(const Rva003AF15E &other);
};

Rva003AF15E::Rva003AF15E(const Rva003AF15E &that)
	: Rva003AF184(that)
{
	*(void **)this = &Rva003AF15E_v0;
	*(void **)((char *)this + 0x14) = &Rva003AF15E_v14;
	*(void **)((char *)this + 0x18) = &Rva003AF15E_v18;
}

// Rva003AF208_v0: matched references place it at VA 0xc1cf9c (retail .rdata value 87).
extern "C" char Rva003AF208_v0 = 87;
// Rva003AF208_v14: matched references place it at VA 0xc1c01c (retail .rdata value -59).
extern "C" char Rva003AF208_v14 = -59;
// Rva003AF208_v18: matched references place it at VA 0xc1c8a8 (retail .rdata value 67).
extern "C" char Rva003AF208_v18 = 67;

class Rva003AF208 : public Rva003AF22E
{
public:
	__declspec(noinline) Rva003AF208(const Rva003AF208 &other);
};

Rva003AF208::Rva003AF208(const Rva003AF208 &that)
	: Rva003AF22E(that)
{
	*(void **)this = &Rva003AF208_v0;
	*(void **)((char *)this + 0x14) = &Rva003AF208_v14;
	*(void **)((char *)this + 0x18) = &Rva003AF208_v18;
}

// Rva003AF2CC_v0: matched references place it at VA 0xc1cae8 (retail .rdata value 87).
extern "C" char Rva003AF2CC_v0 = 87;
extern "C" char Rva003AF2CC_v14;

class Rva003AF2CC : public Rva003AF22E
{
public:
	__declspec(noinline) Rva003AF2CC(const Rva003AF2CC &other);
};

Rva003AF2CC::Rva003AF2CC(const Rva003AF2CC &that)
	: Rva003AF22E(that)
{
	*(void **)this = &Rva003AF2CC_v0;
	*(void **)((char *)this + 0x14) = &Rva003AF2CC_v14;
	*(void **)((char *)this + 0x18) = &Rva003AF208_v18;
}

// g_00C1CFD4: matched references place it at VA 0xc1cfd4 (retail .rdata value 87).
extern "C" char g_00C1CFD4 = 87;
// g_00C1C054: matched references place it at VA 0xc1c054 (retail .rdata value 35).
extern "C" char g_00C1C054 = 35;
// g_00C1CFC4: matched references place it at VA 0xc1cfc4 (retail .rdata value 67).
extern "C" char g_00C1CFC4 = 67;

class Rva003AF329 : public Rva003AF34F
{
public:
	__declspec(noinline) Rva003AF329(const Rva003AF329 &other);
};

Rva003AF329::Rva003AF329(const Rva003AF329 &that)
	: Rva003AF34F(that)
{
	*(void **)this = &g_00C1CFD4;
	*(void **)((char *)this + 0x14) = &g_00C1C054;
	*(void **)((char *)this + 0x18) = &g_00C1CFC4;
}

// g_00C1CFF8: matched references place it at VA 0xc1cff8 (retail .rdata value 87).
extern "C" char g_00C1CFF8 = 87;
// g_00C1C078: matched references place it at VA 0xc1c078 (retail .rdata value 82).
extern "C" char g_00C1C078 = 82;
// g_00C1CFE8: matched references place it at VA 0xc1cfe8 (retail .rdata value 67).
extern "C" char g_00C1CFE8 = 67;

class Rva003AF3D3 : public Rva003AF3F9
{
public:
	__declspec(noinline) Rva003AF3D3(const Rva003AF3D3 &other);
};

Rva003AF3D3::Rva003AF3D3(const Rva003AF3D3 &that)
	: Rva003AF3F9(that)
{
	*(void **)this = &g_00C1CFF8;
	*(void **)((char *)this + 0x14) = &g_00C1C078;
	*(void **)((char *)this + 0x18) = &g_00C1CFE8;
}
// _Rva003AF34F_v14b: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_Rva003AF34F_v14b=?vftable_0112B89C@@3HA")
// _Rva003AF2CC_v14: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_Rva003AF2CC_v14=?vftable_0112B89C@@3HA")
// _Rva003AF34F_v14a: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_Rva003AF34F_v14a=?vftable_0112B89C@@3HA")
// _Rva003AF22E_v14a: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_Rva003AF22E_v14a=?vftable_0112B89C@@3HA")
// _Rva003AF184_v14a: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_Rva003AF184_v14a=?vftable_0112B89C@@3HA")
// _Rva003AF184_v14b: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_Rva003AF184_v14b=?vftable_0112B89C@@3HA")
// _Rva003AF3F9_v14a: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_Rva003AF3F9_v14a=?vftable_0112B89C@@3HA")
// _Rva003AF22E_v14b: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_Rva003AF22E_v14b=?vftable_0112B89C@@3HA")
// _Rva003AF3F9_v14b: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_Rva003AF3F9_v14b=?vftable_0112B89C@@3HA")
