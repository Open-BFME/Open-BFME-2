// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// Default-module template 01 (DefaultAlpha) copy constructors.
// Inner 0x003AEA42 (97B): shared base 0x003AEEB3 plus generated DefaultAlpha
// member copy (128B rep movsd, inlined from rowed 0x003A616F) with dual vtable
// sets. Outer 0x003AEA15 (45B): concrete wrapper re-vtables the inner.

class Rva003AEEB3
{
public:
	Rva003AEEB3(const Rva003AEEB3 &other);
};

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

extern "C" char DefaultAlphaModuleInfo_vtbl;

class DefaultAlphaModuleInfo
{
public:
	__forceinline DefaultAlphaModuleInfo(const DefaultAlphaModuleInfo &that)
	{
		*(void **)this = &DefaultAlphaModuleInfo_vtbl;
		*(struct AlphaKeys *)((char *)this + 4) =
			*(const struct AlphaKeys *)((const char *)&that + 4);
	}
	virtual ~DefaultAlphaModuleInfo();

private:
	FXKeyframe m_keys[8];
};

}

extern "C" char Rva003AEA42_v0a;
extern "C" char Rva003AEA42_v14a;
extern "C" char Rva003AEA42_v18a;
extern "C" char Rva003AEA42_v0b;
extern "C" char Rva003AEA42_v14b;
extern "C" char Rva003AEA42_v18b;
extern "C" char Rva003AEA42_vsub;

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
	FXParticleSystem::DefaultAlphaModuleInfo *sub =
		(FXParticleSystem::DefaultAlphaModuleInfo *)((char *)this + 0x1C);
	*(void **)this = &Rva003AEA42_v0a;
	*(void **)((char *)this + 0x14) = &Rva003AEA42_v14a;
	*(void **)((char *)this + 0x18) = &Rva003AEA42_v18a;
	sub->DefaultAlphaModuleInfo::DefaultAlphaModuleInfo(
		*(const FXParticleSystem::DefaultAlphaModuleInfo *)sub_src);
	*(void **)this = &Rva003AEA42_v0b;
	*(void **)((char *)this + 0x14) = &Rva003AEA42_v14b;
	*(void **)((char *)this + 0x18) = &Rva003AEA42_v18b;
	*(void **)((char *)this + 0x1C) = &Rva003AEA42_vsub;
}

// Inner 0x003AEA42 only; outer 0x003AEA15 raced (sibling Rva003AEA15CopyCtor.cpp
// won 8c789e53b with the same Rva owner for the middle). Dropped our outer dup.
