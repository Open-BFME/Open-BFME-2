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

extern "C" char Rva003AF184_v0a;
extern "C" char Rva003AF184_v14a;
extern "C" char Rva003AF184_vsub;
extern "C" char Rva003AF184_v0b;
extern "C" char Rva003AF184_v14b;

extern "C" char Rva003AF22E_v0a;
extern "C" char Rva003AF22E_v14a;
extern "C" char Rva003AF22E_vsub;
extern "C" char Rva003AF22E_v0b;
extern "C" char Rva003AF22E_v14b;

extern "C" char Rva003AF34F_v0a;
extern "C" char Rva003AF34F_v14a;
extern "C" char Rva003AF34F_vsub;
extern "C" char Rva003AF34F_v0b;
extern "C" char Rva003AF34F_v14b;

extern "C" char Rva003AF3F9_v0a;
extern "C" char Rva003AF3F9_v14a;
extern "C" char Rva003AF3F9_vsub;
extern "C" char Rva003AF3F9_v0b;
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
	*(void **)this = &Rva003AF22E_v0a;
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
	*(void **)this = &Rva003AF34F_v0a;
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
	*(void **)this = &Rva003AF3F9_v0a;
	*(void **)((char *)this + 0x14) = &Rva003AF3F9_v14a;
	sub->CylindricalEmissionVelocityInfo::CylindricalEmissionVelocityInfo(
		*(const FXParticleSystem::CylindricalEmissionVelocityInfo *)sub_src);
	*(void **)sub = &Rva003AF3F9_vsub;
	*(void **)this = &Rva003AF3F9_v0b;
	*(void **)((char *)this + 0x14) = &Rva003AF3F9_v14b;
}
