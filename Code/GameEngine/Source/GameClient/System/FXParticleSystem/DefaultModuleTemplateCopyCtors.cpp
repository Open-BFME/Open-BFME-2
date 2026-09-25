// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// Default module template copy constructors (retail 0x003AEB0A cluster).
// Each per-module template copy constructs the shared base at 0x003AEEB3,
// copies its info member through a null-preserving sub pointer at +0x1C
// (the Cylindrical-assignment idiom from FXParticleSystemModules.cpp),
// and installs its own vftables. All vftable dwords are DIR32 sites the
// gate takes from the target; both calls resolve through the ledger.

class Rva003AEEB3
{
public:
	Rva003AEEB3(const Rva003AEEB3 &other);
};

namespace FXParticleSystem
{

class DefaultColorModuleInfo
{
public:
	DefaultColorModuleInfo(const DefaultColorModuleInfo &other);
};

}

extern "C" char Rva003AEB0A_v0a;
extern "C" char Rva003AEB0A_v14a;
extern "C" char Rva003AEB0A_v18a;
extern "C" char Rva003AEB0A_vsub;
extern "C" char Rva003AEB0A_v0b;
extern "C" char Rva003AEB0A_v14b;
extern "C" char Rva003AEB0A_v18b;

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
	*(void **)this = &Rva003AEB0A_v0a;
	*(void **)((char *)this + 0x14) = &Rva003AEB0A_v14a;
	*(void **)((char *)this + 0x18) = &Rva003AEB0A_v18a;
	sub->DefaultColorModuleInfo::DefaultColorModuleInfo(
		*(const FXParticleSystem::DefaultColorModuleInfo *)sub_src);
	*(void **)sub = &Rva003AEB0A_vsub;
	*(void **)this = &Rva003AEB0A_v0b;
	*(void **)((char *)this + 0x14) = &Rva003AEB0A_v14b;
	*(void **)((char *)this + 0x18) = &Rva003AEB0A_v18b;
}
