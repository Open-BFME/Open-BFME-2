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
// Rva003AEF9B_vsub: retail table 0x00C1D758 (4 slots). Own the complete initialized table
// instead of its one-byte first-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a matched row at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_ERva005FEA50Base@FXParticleSystem@@WBM@AEPAXI@Z")();
void __identifier("??1Elem4@@QAE@XZ")();
void __identifier("?name@Rva003ABE7FNamed@@QBEPBDXZ")();
void __identifier("?rva00562233@Rva00562233@@WBM@AEXPAVXfer@@@Z")();
extern const void *const Rva003AEF9B_vsub[4] = {
	(const void *)&__identifier("??_ERva005FEA50Base@FXParticleSystem@@WBM@AEPAXI@Z"), //  0 0x003A588E
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?name@Rva003ABE7FNamed@@QBEPBDXZ"), //  2 0x003ABE7F
	(const void *)&__identifier("?rva00562233@Rva00562233@@WBM@AEXPAVXfer@@@Z")  //  3 0x003ABE85
};
}
// Rva003AEF9B_v0b: retail table 0x00C1D728 (12 slots). Own the complete initialized table
// instead of its one-byte first-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a matched row at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GRva005FEA50Base@FXParticleSystem@@UAEPAXI@Z")();
void __identifier("??1Elem4@@QAE@XZ")();
int __cdecl _purecall(void);
void __identifier("?rva00562233@Rva00562233@@UAEXPAVXfer@@@Z")();
void __identifier("?get@Rva003EE704LeaField@@QBEPAXXZ")();
void __identifier("?get@Rva0030BBA5LeaField@@QBEPAXXZ")();
void __identifier("?get@Rva00308156LeaGetter@@QBEPAXXZ")();
void __identifier("?get@Rva003ABE71LeaGetter@@QBEPAXXZ")();
void __identifier("?get@Rva003ABE78LeaGetter@@QBEPAXXZ")();
extern const void *const Rva003AEF9B_v0b[12] = {
	(const void *)&__identifier("??_GRva005FEA50Base@FXParticleSystem@@UAEPAXI@Z"), //  0 0x003AEFF6
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  1 0x000B3FD0
	(const void *)&_purecall, //  2 0x0003B810
	(const void *)&__identifier("?rva00562233@Rva00562233@@UAEXPAVXfer@@@Z"), //  3 0x00562233
	(const void *)&__identifier("?get@Rva003EE704LeaField@@QBEPAXXZ"), //  4 0x003EE704
	(const void *)&__identifier("?get@Rva0030BBA5LeaField@@QBEPAXXZ"), //  5 0x0030BBA5
	(const void *)&__identifier("?get@Rva00308156LeaGetter@@QBEPAXXZ"), //  6 0x00308156
	(const void *)&__identifier("?get@Rva003ABE71LeaGetter@@QBEPAXXZ"), //  7 0x003ABE71
	(const void *)&__identifier("?get@Rva003ABE78LeaGetter@@QBEPAXXZ"), //  8 0x003ABE78
	(const void *)&__identifier("?get@Rva00308156LeaGetter@@QBEPAXXZ"), //  9 0x00308156
	(const void *)&__identifier("?get@Rva003ABE71LeaGetter@@QBEPAXXZ"), // 10 0x003ABE71
	(const void *)&__identifier("?get@Rva003ABE78LeaGetter@@QBEPAXXZ")  // 11 0x003ABE78
};
}
// Folded 0x0081C780 (one __purecall slot): distinct clean COMDATs keep +0x14/+0x18 stores separate without asserting class identity.
extern "C" const void *const __identifier("??_7Rva003F498ACallback@@6B@")[1];
extern "C" const void *const __identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@")[1];

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
	*(void **)sub = (void *)Rva003AEF9B_vsub;
	*(void **)this = (void *)Rva003AEF9B_v0b;
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7Rva003F498ACallback@@6B@");
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@");
}

// Native constructor operands bind this complete compiler table.
extern "C" const void *const __identifier("??_7Rva005FEA50Base@FXParticleSystem@@6BDefaultModuleHeadBase@@@")[4];
extern "C" const void *const __identifier("??_7Rva005FEA50Base@FXParticleSystem@@6BRva003AEEB3Slot14@@@")[1];
extern "C" const void *const __identifier("??_7Rva005FEA50Base@FXParticleSystem@@6BRva003AEEB3Slot18@@@")[1];
// Native constructor operands bind this complete compiler table.
extern "C" const void *const __identifier("??_7Rva005FEA50Base@FXParticleSystem@@6B@")[4];

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
	*(void **)sub = (void *)__identifier("??_7Rva005FEA50Base@FXParticleSystem@@6B@");
	*(void **)this = (void *)__identifier("??_7Rva005FEA50Base@FXParticleSystem@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7Rva005FEA50Base@FXParticleSystem@@6BRva003AEEB3Slot14@@@");
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7Rva005FEA50Base@FXParticleSystem@@6BRva003AEEB3Slot18@@@");
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
