// cl: /Ob2 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Target00149A90..149BA8: compare eligibility of model/material views, optional
// light environments, the by-value vector getter and virtual float64. Layout
// offsets and receiver ABI are from retail; names remain neutral. The old
// bank's stdcall light predicate and pointer-output getter were incorrect.
// Correct providers are Rva0013F8D0 comparison and vector-return149280.
// Real reference Vector3 (BF1@874e38488) supplies copy/equality semantics.
// A positive outer eligibility guard retains native early EDI save and sinks
// the pre-ESI false epilogue after the comparison body. All280B exact.
#include "vector3.h"
class Rva00149280Class { public: Vector3 rva00149280() const; };
class Rva00149A90Sub
{
public:
	char m_pad0[0xB8];
	int m_B8;
	char m_padBC[0x108 - 0xBC];
	int m_108;
};

class Rva00149A90Node
{
public:
	char m_pad0[0x94];
	Rva00149A90Sub *m_94;
};

class Rva0013F8D0 { public: bool rva0013F8D0(const Rva0013F8D0 &that) const; };

class Rva00149A90Obj
{
public:
	virtual void rva00149A90V00();
	virtual void rva00149A90V01();
	virtual void rva00149A90V02();
	virtual void rva00149A90V03();
	virtual void rva00149A90V04();
	virtual void rva00149A90V05();
	virtual void rva00149A90V06();
	virtual void rva00149A90V07();
	virtual void rva00149A90V08();
	virtual void rva00149A90V09();
	virtual void rva00149A90V10();
	virtual void rva00149A90V11();
	virtual void rva00149A90V12();
	virtual void rva00149A90V13();
	virtual void rva00149A90V14();
	virtual void rva00149A90V15();
	virtual void rva00149A90V16();
	virtual void rva00149A90V17();
	virtual void rva00149A90V18();
	virtual void rva00149A90V19();
	virtual void rva00149A90V20();
	virtual void rva00149A90V21();
	virtual void rva00149A90V22();
	virtual void rva00149A90V23();
	virtual void rva00149A90V24();
	virtual float rva00149A90Float();
	bool rva00149A90(Rva00149A90Obj *other);

private:
	char m_padVptr[0xC4 - 4];
	Rva00149A90Node *m_C4;
	Rva0013F8D0 *m_C8;
};

// ?rva00149A90@Rva00149A90Obj@@QAE_NPAV1@@Z @0x00149A90
bool Rva00149A90Obj::rva00149A90(Rva00149A90Obj *other)
{
	if (m_C4 && (m_C4->m_94->m_B8 || m_C4->m_94->m_108) && other->m_C4 && (other->m_C4->m_94->m_B8 || other->m_C4->m_94->m_108)) {
	if ((m_C8 == 0) != (other->m_C8 == 0))
		return false;
	if (m_C8 != 0 && !m_C8->rva0013F8D0(*other->m_C8))
		return false;
	if (((const Rva00149280Class *)this)->rva00149280() != ((const Rva00149280Class *)other)->rva00149280())
		return false;
	float fThis = rva00149A90Float();
	float fOther = other->rva00149A90Float();
	if (fThis != fOther)
		return false;
	return true;
	}
	return false;
}
