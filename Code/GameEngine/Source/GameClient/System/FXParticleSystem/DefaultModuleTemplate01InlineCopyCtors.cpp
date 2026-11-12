// cl: /DNDEBUG /MD /GX- /Ob2

// Default-module template 01 (DefaultAlpha) copy constructors.
// Inner 0x003AEA42 (97B): shared base 0x003AEEB3 plus generated DefaultAlpha
// key block copy (128B rep movsd, as in rowed 0x003A616F) with dual vtable
// sets. Outer 0x003AEA15 (45B): concrete wrapper re-vtables the inner.

#include "../../../../Include/GameClient/Rva003AEEB3.h"

// Existing compiler table installed by the rowed alpha-info copy constructor.
extern "C" const void *const __identifier("??_7DefaultAlphaModuleInfo@FXParticleSystem@@6B@")[];

namespace FXParticleSystem
{

struct FXCoord3D
{
	float x;
	float y;
	float z;
};

struct FXKeyframe
{
	FXCoord3D m_value;
	unsigned int m_frame;
};

struct AlphaKeys
{
	FXKeyframe m_keys[8];
};

}

// The rowed smart-base constructor installs this existing class table.
extern "C" const void *const __identifier("??_7Rva0055B5BF@@6BDefaultModuleHeadBase@@@")[];
extern "C" const void *const __identifier("??_7Rva0055B5BF@@6BRva003AEEB3Slot14@@@")[1];
extern "C" const void *const __identifier("??_7Rva0055B5BF@@6BRva003AEEB3Slot18@@@")[1];
// Rva003AEA42_v0b: retail table 0x00C1D5D4 (5 slots). Own the complete initialized table
// instead of its one-byte first-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a matched row at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GRva005FEA50Base@FXParticleSystem@@UAEPAXI@Z")();
void __identifier("??1Elem4@@QAE@XZ")();
int __cdecl _purecall(void);
void __identifier("?DoXfer@Rva003ABC6E@@UAEXAAVXfer@@@Z")();
void __identifier("?get@Rva004F5FA3LeaGetter@@QBEPAXXZ")();
extern const void *const Rva003AEA42_v0b[5] = {
	(const void *)&__identifier("??_GRva005FEA50Base@FXParticleSystem@@UAEPAXI@Z"), //  0 0x003AEFF6
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  1 0x000B3FD0
	(const void *)&_purecall, //  2 0x0003B810
	(const void *)&__identifier("?DoXfer@Rva003ABC6E@@UAEXAAVXfer@@@Z"), //  3 0x0055B30F
	(const void *)&__identifier("?get@Rva004F5FA3LeaGetter@@QBEPAXXZ")  //  4 0x004F5FA3
};
}
// Folded 0x0081C780 (one __purecall slot): distinct clean COMDATs keep +0x14/+0x18 stores separate without asserting class identity.
extern "C" const void *const __identifier("??_7Rva003F498ACallback@@6B@")[1];
extern "C" const void *const __identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@")[1];
// Rva003AEA42_vsub: retail table 0x00C1D5C4 (4 slots). Own the complete initialized table
// instead of its one-byte first-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a matched row at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_ERva005FEA50Base@FXParticleSystem@@WBM@AEPAXI@Z")();
void __identifier("??1Elem4@@QAE@XZ")();
void __identifier("?Rva003ABC9FGet@@YAHXZ")();
void __identifier("?rva0055B30F@Rva0055B30F@@WBM@AEXPAVXfer@@@Z")();
extern const void *const Rva003AEA42_vsub[4] = {
	(const void *)&__identifier("??_ERva005FEA50Base@FXParticleSystem@@WBM@AEPAXI@Z"), //  0 0x003A588E
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?Rva003ABC9FGet@@YAHXZ"), //  2 0x003ABC9F
	(const void *)&__identifier("?rva0055B30F@Rva0055B30F@@WBM@AEXPAVXfer@@@Z")  //  3 0x003ABCA5
};
}

class Rva003AEA42
{
public:
	__declspec(noinline) Rva003AEA42(const Rva003AEA42 &other);

private:
	void *m_v0;
	char m_pad04[16];
	void *m_v14;
	void *m_v18;
	char m_info[4];
};

// ??0Rva003AEA42@@QAE@ABV0@@Z
Rva003AEA42::Rva003AEA42(const Rva003AEA42 &that)
{
	const void *src = &that;
	((Rva003AEEB3 *)this)->Rva003AEEB3::Rva003AEEB3(*(const Rva003AEEB3 *)src);
	const void *sub_src = src ? (const char *)src + 0x1C : 0;
	void *sub = (char *)this + 0x1C;
	*(void **)this = (void *)__identifier("??_7Rva0055B5BF@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7Rva0055B5BF@@6BRva003AEEB3Slot14@@@");
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7Rva0055B5BF@@6BRva003AEEB3Slot18@@@");
	*(void **)sub = (void *)__identifier("??_7DefaultAlphaModuleInfo@FXParticleSystem@@6B@");
	*(FXParticleSystem::AlphaKeys *)((char *)sub + 4) =
		*(const FXParticleSystem::AlphaKeys *)((const char *)sub_src + 4);
	*(void **)this = (void *)Rva003AEA42_v0b;
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7Rva003F498ACallback@@6B@");
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@");
	*(void **)((char *)this + 0x1C) = (void *)Rva003AEA42_vsub;
}

// Inner 0x003AEA42 only; outer 0x003AEA15 raced (sibling Rva003AEA15CopyCtor.cpp
// won 8c789e53b with the same Rva owner for the middle). Dropped our outer dup.
