// cl: /DNDEBUG /MD /GX- /Ob2

// Default module template copy constructors (retail 0x003AEB0A cluster).
// Each per-module template copy constructs the shared base at 0x003AEEB3,
// copies its info member through a null-preserving sub pointer at +0x1C
// (the Cylindrical-assignment idiom from FXParticleSystemModules.cpp),
// and installs its own vftables. All vftable dwords are DIR32 sites the
// gate takes from the target; both calls resolve through the ledger.

#include "../../../../Include/GameClient/Rva003AEEB3.h"

#include "../../../../Include/GameClient/WindModuleInfo.h"
#include "../../../../Include/GameClient/RenderObjectUpdateModuleInfo.h"
#include "../../../../Include/GameClient/DefaultPhysicsModuleInfo.h"
namespace FXParticleSystem
{

class DefaultColorModuleInfo
{
public:
	DefaultColorModuleInfo(const DefaultColorModuleInfo &other);
};


class DefaultUpdateModuleInfo
{
public:
	DefaultUpdateModuleInfo(const DefaultUpdateModuleInfo &other);
};



}

// Pure secondary tables below are bound by native constructor operands.
// Keep construction stages and +0x14/+0x18 symbols distinct even where retail
// folded their one-purecall data. Wind/RenderObject byte owners remain below.

extern "C" char __identifier("??_7Rva0055BF21@@6BDefaultModuleHeadBase@@@");
extern "C" const void *const __identifier("??_7Rva0055BF21@@6BRva003AEEB3Slot14@@@")[1];
extern "C" const void *const __identifier("??_7Rva0055BF21@@6BRva003AEEB3Slot18@@@")[1];
// VA 0xc1d628: the compiler table the owning class's unit emits there.
extern "C" char __identifier("??_7Rva0055BF4B@@6B@");
// VA 0xc1d60c: the compiler table the owning class's unit emits there.
extern "C" char __identifier("??_7Rva0055BF4B@@6BDefaultModuleHeadBase@@@");
extern "C" const void *const __identifier("??_7Rva0055BF4B@@6BRva003AEEB3Slot14@@@")[1];
extern "C" const void *const __identifier("??_7Rva0055BF4B@@6BRva003AEEB3Slot18@@@")[1];

extern "C" char __identifier("??_7Rva0055BF21@@6BDefaultModuleHeadBase@@@");
extern "C" const void *const __identifier("??_7Rva0055BF21@@6BRva003AEEB3Slot14@@@")[1];
extern "C" const void *const __identifier("??_7Rva0055BF21@@6BRva003AEEB3Slot18@@@")[1];
// VA 0xc1d678: the compiler table the owning class's unit emits there.
extern "C" char __identifier("??_7Rva0055F197@@6B@");
// VA 0xc1d654: the compiler table the owning class's unit emits there.
extern "C" char __identifier("??_7Rva0055F197@@6BDefaultModuleHeadBase@@@");
extern "C" const void *const __identifier("??_7Rva0055F197@@6BRva003AEEB3Slot14@@@")[1];
extern "C" const void *const __identifier("??_7Rva0055F197@@6BRva003AEEB3Slot18@@@")[1];

extern "C" char __identifier("??_7Rva0055F98A@@6BDefaultModuleHeadBase@@@");
extern "C" const void *const __identifier("??_7Rva0055F98A@@6BRva003AEEB3Slot14@@@")[1];
extern "C" const void *const __identifier("??_7Rva0055F98A@@6BRva003AEEB3Slot18@@@")[1];
// VA 0xc1d6b8: the compiler table the owning class's unit emits there.
extern "C" char __identifier("??_7Rva0055F9B4@@6B@");
// VA 0xc1d688: the compiler table the owning class's unit emits there.
extern "C" char __identifier("??_7Rva0055F9B4@@6BDefaultModuleHeadBase@@@");
extern "C" const void *const __identifier("??_7Rva0055F9B4@@6BRva003AEEB3Slot14@@@")[1];
extern "C" const void *const __identifier("??_7Rva0055F9B4@@6BRva003AEEB3Slot18@@@")[1];

extern "C" char __identifier("??_7Rva0055F98A@@6BDefaultModuleHeadBase@@@");
extern "C" const void *const __identifier("??_7Rva0055F98A@@6BRva003AEEB3Slot14@@@")[1];
extern "C" const void *const __identifier("??_7Rva0055F98A@@6BRva003AEEB3Slot18@@@")[1];
// Rva003AEF9B_vsub: matched references place it at VA 0xc1d758 (retail .rdata value -114).
extern "C" char Rva003AEF9B_vsub = -114;
// Rva003AEF9B_v0b: matched references place it at VA 0xc1d728 (retail .rdata value -10).
extern "C" char Rva003AEF9B_v0b = -10;
extern "C" char Rva003AEF9B_v14b;
extern "C" char Rva003AEF9B_v18b;

class Rva003AEB0A
{
public:
	__declspec(noinline) Rva003AEB0A(const Rva003AEB0A &other);

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04: smart member + int, owned by the base copy
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	char m_info[4]; // +0x1C: info head, owned by the sub copy
};

// ??0Rva003AEB0A@@QAE@ABV0@@Z
Rva003AEB0A::Rva003AEB0A(const Rva003AEB0A &that)
{
	const void *src = &that;
	((Rva003AEEB3 *)this)->Rva003AEEB3::Rva003AEEB3(*(const Rva003AEEB3 *)src);
	const void *sub_src = src ? (const char *)src + 0x1C : 0;
	FXParticleSystem::DefaultColorModuleInfo *sub =
		(FXParticleSystem::DefaultColorModuleInfo *)((char *)this + 0x1C);
	*(void **)this = &__identifier("??_7Rva0055BF21@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7Rva0055BF21@@6BRva003AEEB3Slot14@@@");
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7Rva0055BF21@@6BRva003AEEB3Slot18@@@");
	sub->DefaultColorModuleInfo::DefaultColorModuleInfo(
		*(const FXParticleSystem::DefaultColorModuleInfo *)sub_src);
	*(void **)sub = &__identifier("??_7Rva0055BF4B@@6B@");
	*(void **)this = &__identifier("??_7Rva0055BF4B@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7Rva0055BF4B@@6BRva003AEEB3Slot14@@@");
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7Rva0055BF4B@@6BRva003AEEB3Slot18@@@");
}

class Rva003AEBC9
{
public:
	__declspec(noinline) Rva003AEBC9(const Rva003AEBC9 &other);

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04: smart member + int, owned by the base copy
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	char m_info[4]; // +0x1C: info head, owned by the sub copy
};

// ??0Rva003AEBC9@@QAE@ABV0@@Z
Rva003AEBC9::Rva003AEBC9(const Rva003AEBC9 &that)
{
	const void *src = &that;
	((Rva003AEEB3 *)this)->Rva003AEEB3::Rva003AEEB3(*(const Rva003AEEB3 *)src);
	const void *sub_src = src ? (const char *)src + 0x1C : 0;
	FXParticleSystem::DefaultPhysicsModuleInfo *sub =
		(FXParticleSystem::DefaultPhysicsModuleInfo *)((char *)this + 0x1C);
	*(void **)this = &__identifier("??_7Rva0055BF21@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7Rva0055BF21@@6BRva003AEEB3Slot14@@@");
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7Rva0055BF21@@6BRva003AEEB3Slot18@@@");
	sub->DefaultPhysicsModuleInfo::DefaultPhysicsModuleInfo(
		*(const FXParticleSystem::DefaultPhysicsModuleInfo *)sub_src);
	*(void **)sub = &__identifier("??_7Rva0055F197@@6B@");
	*(void **)this = &__identifier("??_7Rva0055F197@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7Rva0055F197@@6BRva003AEEB3Slot14@@@");
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7Rva0055F197@@6BRva003AEEB3Slot18@@@");
}

class Rva003AEC8B
{
public:
	__declspec(noinline) Rva003AEC8B(const Rva003AEC8B &other);

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04: smart member + int, owned by the base copy
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	char m_info[4]; // +0x1C: info head, owned by the sub copy
};

// ??0Rva003AEC8B@@QAE@ABV0@@Z
Rva003AEC8B::Rva003AEC8B(const Rva003AEC8B &that)
{
	const void *src = &that;
	((Rva003AEEB3 *)this)->Rva003AEEB3::Rva003AEEB3(*(const Rva003AEEB3 *)src);
	const void *sub_src = src ? (const char *)src + 0x1C : 0;
	FXParticleSystem::DefaultUpdateModuleInfo *sub =
		(FXParticleSystem::DefaultUpdateModuleInfo *)((char *)this + 0x1C);
	*(void **)this = &__identifier("??_7Rva0055F98A@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7Rva0055F98A@@6BRva003AEEB3Slot14@@@");
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7Rva0055F98A@@6BRva003AEEB3Slot18@@@");
	sub->DefaultUpdateModuleInfo::DefaultUpdateModuleInfo(
		*(const FXParticleSystem::DefaultUpdateModuleInfo *)sub_src);
	*(void **)sub = &__identifier("??_7Rva0055F9B4@@6B@");
	*(void **)this = &__identifier("??_7Rva0055F9B4@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7Rva0055F9B4@@6BRva003AEEB3Slot14@@@");
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7Rva0055F9B4@@6BRva003AEEB3Slot18@@@");
}

class Rva003AEF9B
{
public:
	__declspec(noinline) Rva003AEF9B(const Rva003AEF9B &other);

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04: smart member + int, owned by the base copy
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	char m_info[4]; // +0x1C: info head, owned by the sub copy
};

// ??0Rva003AEF9B@@QAE@ABV0@@Z
Rva003AEF9B::Rva003AEF9B(const Rva003AEF9B &that)
{
	const void *src = &that;
	((Rva003AEEB3 *)this)->Rva003AEEB3::Rva003AEEB3(*(const Rva003AEEB3 *)src);
	const void *sub_src = src ? (const char *)src + 0x1C : 0;
	FXParticleSystem::RenderObjectUpdateModuleInfo *sub =
		(FXParticleSystem::RenderObjectUpdateModuleInfo *)((char *)this + 0x1C);
	*(void **)this = &__identifier("??_7Rva0055F98A@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7Rva0055F98A@@6BRva003AEEB3Slot14@@@");
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7Rva0055F98A@@6BRva003AEEB3Slot18@@@");
	sub->RenderObjectUpdateModuleInfo::RenderObjectUpdateModuleInfo(
		*(const FXParticleSystem::RenderObjectUpdateModuleInfo *)sub_src);
	*(void **)sub = &Rva003AEF9B_vsub;
	*(void **)this = &Rva003AEF9B_v0b;
	*(void **)((char *)this + 0x14) = &Rva003AEF9B_v14b;
	*(void **)((char *)this + 0x18) = &Rva003AEF9B_v18b;
}

// Rva003AED6B_v0: matched references place it at VA 0xc1b5a8 (retail .rdata value -10).
extern "C" char Rva003AED6B_v0 = -10;
extern "C" const void *const __identifier("??_7Rva005FEA50Base@FXParticleSystem@@6BRva003AEEB3Slot14@@@")[1];
extern "C" const void *const __identifier("??_7Rva005FEA50Base@FXParticleSystem@@6BRva003AEEB3Slot18@@@")[1];
// Rva003AED6B_vsub: matched references place it at VA 0xc1b598 (retail .rdata value -114).
extern "C" char Rva003AED6B_vsub = -114;

class Rva003AED6B
{
public:
	__declspec(noinline) Rva003AED6B(const Rva003AED6B &other);

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04: smart member + int, owned by the base copy
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	char m_info[4]; // +0x1C: info head, owned by the sub copy
};

// ??0Rva003AED6B@@QAE@ABV0@@Z
Rva003AED6B::Rva003AED6B(const Rva003AED6B &that)
{
	const void *src = &that;
	((Rva003AEEB3 *)this)->Rva003AEEB3::Rva003AEEB3(*(const Rva003AEEB3 *)src);
	const void *sub_src = src ? (const char *)src + 0x1C : 0;
	FXParticleSystem::WindModuleInfo *sub =
		(FXParticleSystem::WindModuleInfo *)((char *)this + 0x1C);
	sub->WindModuleInfo::WindModuleInfo(
		*(const FXParticleSystem::WindModuleInfo *)sub_src);
	*(void **)sub = &Rva003AED6B_vsub;
	*(void **)this = &Rva003AED6B_v0;
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7Rva005FEA50Base@FXParticleSystem@@6BRva003AEEB3Slot14@@@");
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7Rva005FEA50Base@FXParticleSystem@@6BRva003AEEB3Slot18@@@");
}
// _Rva003AEF9B_v14b: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_Rva003AEF9B_v14b=?vftable_0112B89C@@3HA")
// _Rva003AEF9B_v18b: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_Rva003AEF9B_v18b=?vftable_0112B89C@@3HA")

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
