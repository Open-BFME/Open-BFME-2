// cl: /DNDEBUG /MD /GX- /Ob2

// Particle module template copy constructors (retail 0x003AF184 cluster).
// Each template copy constructs the particle module-info base at 0x003AF50D,
// copies its emission-info member through a null-preserving sub pointer at
// +0x18 (the Cylindrical-assignment idiom from FXParticleSystemModules.cpp),
// and installs compiler tables already emitted by the module constructor units.
// Native constructor operands establish their addresses, not original class names.
// Keep distinct table symbols across construction stages even when retail folds
// their storage: coalescing the names changes the compiler-visible stores.

class Rva003AF50D
{
public:
	Rva003AF50D(const Rva003AF50D &other);
};

#include "../../../../Include/GameClient/OrthoEmissionVelocityInfo.h"
#include "../../../../Include/GameClient/SphericalEmissionVelocityInfo.h"
namespace FXParticleSystem
{

class CylindricalEmissionVelocityInfo
{
public:
	CylindricalEmissionVelocityInfo(const CylindricalEmissionVelocityInfo &other);
};

}

extern "C" const void *const __identifier("??_7?$DefaultParticleModule@$03@FXParticleSystem@@6BDefaultModuleHeadBase@@@")[];
extern "C" const void *const __identifier("??_7?$DefaultParticleModule@$03@FXParticleSystem@@6BRva003AA228Slice@1@@")[];
extern "C" const void *const __identifier("??_7OrthoEmissionVelocityModule@FXParticleSystem@@6B@")[];
extern "C" const void *const __identifier("??_7OrthoEmissionVelocityModule@FXParticleSystem@@6BDefaultModuleHeadBase@@@")[];
extern "C" const void *const __identifier("??_7OrthoEmissionVelocityModule@FXParticleSystem@@6BRva003AA228Slice@1@@")[];

extern "C" const void *const __identifier("??_7SphericalEmissionVelocityModule@FXParticleSystem@@6B@")[];
extern "C" const void *const __identifier("??_7SphericalEmissionVelocityModule@FXParticleSystem@@6BDefaultModuleHeadBase@@@")[];
extern "C" const void *const __identifier("??_7SphericalEmissionVelocityModule@FXParticleSystem@@6BRva003AA228Slice@1@@")[];

extern "C" const void *const __identifier("??_7CylindricalEmissionVelocityModule@FXParticleSystem@@6B@")[];
extern "C" const void *const __identifier("??_7CylindricalEmissionVelocityModule@FXParticleSystem@@6BDefaultModuleHeadBase@@@")[];
extern "C" const void *const __identifier("??_7CylindricalEmissionVelocityModule@FXParticleSystem@@6BRva003AA228Slice@1@@")[];

extern "C" const void *const __identifier("??_7Rva003AC297Module@FXParticleSystem@@6BDefaultModuleHeadBase@@@")[];
extern "C" const void *const __identifier("??_7Rva003AC297Module@FXParticleSystem@@6BRva003AA228Slice@1@@")[];

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
	*(void **)this = (void *)__identifier("??_7?$DefaultParticleModule@$03@FXParticleSystem@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7?$DefaultParticleModule@$03@FXParticleSystem@@6BRva003AA228Slice@1@@");
	sub->OrthoEmissionVelocityInfo::OrthoEmissionVelocityInfo(
		*(const FXParticleSystem::OrthoEmissionVelocityInfo *)sub_src);
	*(void **)sub = (void *)__identifier("??_7OrthoEmissionVelocityModule@FXParticleSystem@@6B@");
	*(void **)this = (void *)__identifier("??_7OrthoEmissionVelocityModule@FXParticleSystem@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7OrthoEmissionVelocityModule@FXParticleSystem@@6BRva003AA228Slice@1@@");
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
	*(void **)this = (void *)__identifier("??_7?$DefaultParticleModule@$03@FXParticleSystem@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7?$DefaultParticleModule@$03@FXParticleSystem@@6BRva003AA228Slice@1@@");
	sub->SphericalEmissionVelocityInfo::SphericalEmissionVelocityInfo(
		*(const FXParticleSystem::SphericalEmissionVelocityInfo *)sub_src);
	*(void **)sub = (void *)__identifier("??_7SphericalEmissionVelocityModule@FXParticleSystem@@6B@");
	*(void **)this = (void *)__identifier("??_7SphericalEmissionVelocityModule@FXParticleSystem@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7SphericalEmissionVelocityModule@FXParticleSystem@@6BRva003AA228Slice@1@@");
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
	*(void **)this = (void *)__identifier("??_7?$DefaultParticleModule@$03@FXParticleSystem@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7?$DefaultParticleModule@$03@FXParticleSystem@@6BRva003AA228Slice@1@@");
	sub->CylindricalEmissionVelocityInfo::CylindricalEmissionVelocityInfo(
		*(const FXParticleSystem::CylindricalEmissionVelocityInfo *)sub_src);
	*(void **)sub = (void *)__identifier("??_7CylindricalEmissionVelocityModule@FXParticleSystem@@6B@");
	*(void **)this = (void *)__identifier("??_7CylindricalEmissionVelocityModule@FXParticleSystem@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7CylindricalEmissionVelocityModule@FXParticleSystem@@6BRva003AA228Slice@1@@");
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
	*(void **)this = (void *)__identifier("??_7?$DefaultParticleModule@$03@FXParticleSystem@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7?$DefaultParticleModule@$03@FXParticleSystem@@6BRva003AA228Slice@1@@");
	sub->CylindricalEmissionVelocityInfo::CylindricalEmissionVelocityInfo(
		*(const FXParticleSystem::CylindricalEmissionVelocityInfo *)sub_src);
	*(void **)sub = (void *)__identifier("??_7CylindricalEmissionVelocityModule@FXParticleSystem@@6B@");
	*(void **)this = (void *)__identifier("??_7Rva003AC297Module@FXParticleSystem@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7Rva003AC297Module@FXParticleSystem@@6BRva003AA228Slice@1@@");
}

extern "C" const void *const __identifier("??_7Rva003AD16CModule@@6BDefaultModuleHeadBase@@@")[];
extern "C" const void *const __identifier("??_7Rva003AD16CModule@@6BRva003AA228Slice@FXParticleSystem@@@")[];
extern "C" const void *const __identifier("??_7Rva003ACB79@@6B@")[];

class Rva003AF15E : public Rva003AF184
{
public:
	__declspec(noinline) Rva003AF15E(const Rva003AF15E &other);
};

Rva003AF15E::Rva003AF15E(const Rva003AF15E &that)
	: Rva003AF184(that)
{
	*(void **)this = (void *)__identifier("??_7Rva003AD16CModule@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7Rva003AD16CModule@@6BRva003AA228Slice@FXParticleSystem@@@");
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7Rva003ACB79@@6B@");
}

extern "C" const void *const __identifier("??_7Rva003AD19BModule@@6BDefaultModuleHeadBase@@@")[];
extern "C" const void *const __identifier("??_7Rva003AD19BModule@@6BRva003AA228Slice@FXParticleSystem@@@")[];
extern "C" const void *const __identifier("??_7Rva003ACBA3@@6B@")[];

class Rva003AF208 : public Rva003AF22E
{
public:
	__declspec(noinline) Rva003AF208(const Rva003AF208 &other);
};

Rva003AF208::Rva003AF208(const Rva003AF208 &that)
	: Rva003AF22E(that)
{
	*(void **)this = (void *)__identifier("??_7Rva003AD19BModule@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7Rva003AD19BModule@@6BRva003AA228Slice@FXParticleSystem@@@");
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7Rva003ACBA3@@6B@");
}

extern "C" const void *const __identifier("??_7Rva003ACBA3@@6BDefaultModuleHeadBase@@@")[];
extern "C" const void *const __identifier("??_7Rva003ACBCD@@6BRva003AA228Slice@FXParticleSystem@@@")[];

class Rva003AF2CC : public Rva003AF22E
{
public:
	__declspec(noinline) Rva003AF2CC(const Rva003AF2CC &other);
};

Rva003AF2CC::Rva003AF2CC(const Rva003AF2CC &that)
	: Rva003AF22E(that)
{
	*(void **)this = (void *)__identifier("??_7Rva003ACBA3@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7Rva003ACBCD@@6BRva003AA228Slice@FXParticleSystem@@@");
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7Rva003ACBA3@@6B@");
}

extern "C" const void *const __identifier("??_7Rva003AD1F9Module@@6BDefaultModuleHeadBase@@@")[];
extern "C" const void *const __identifier("??_7Rva003AD1F9Module@@6BRva003AA228Slice@FXParticleSystem@@@")[];
extern "C" const void *const __identifier("??_7Rva003ACBF7@@6B@")[];

class Rva003AF329 : public Rva003AF34F
{
public:
	__declspec(noinline) Rva003AF329(const Rva003AF329 &other);
};

Rva003AF329::Rva003AF329(const Rva003AF329 &that)
	: Rva003AF34F(that)
{
	*(void **)this = (void *)__identifier("??_7Rva003AD1F9Module@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7Rva003AD1F9Module@@6BRva003AA228Slice@FXParticleSystem@@@");
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7Rva003ACBF7@@6B@");
}

extern "C" const void *const __identifier("??_7Rva003AD228Module@@6BDefaultModuleHeadBase@@@")[];
extern "C" const void *const __identifier("??_7Rva003AD228Module@@6BRva003AA228Slice@FXParticleSystem@@@")[];
extern "C" const void *const __identifier("??_7Rva003ACC21@@6B@")[];

class Rva003AF3D3 : public Rva003AF3F9
{
public:
	__declspec(noinline) Rva003AF3D3(const Rva003AF3D3 &other);
};

Rva003AF3D3::Rva003AF3D3(const Rva003AF3D3 &that)
	: Rva003AF3F9(that)
{
	*(void **)this = (void *)__identifier("??_7Rva003AD228Module@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7Rva003AD228Module@@6BRva003AA228Slice@FXParticleSystem@@@");
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7Rva003ACC21@@6B@");
}
