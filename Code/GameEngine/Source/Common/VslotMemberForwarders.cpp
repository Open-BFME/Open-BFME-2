// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// Vtable-slot forwarders with no ledger owner: each moves `this` to a member
// object (add ecx, N), a member pointer (mov ecx, [ecx+N]) or a global
// (mov ecx, [VA]) and tail-jumps to one method, passing the caller's stack
// arguments through (the callee's ret N gives their count). Every class,
// method and callee here is address-named: the bytes prove only the hop and
// the argument count. Callee names already in the ledger are reused through
// their own pins when present; otherwise each callee is pinned by address.

typedef int Int;

// LINK: views of the rowed owners these forwarders reach (respelled from the address-named targets).
template <class T> class StringBase { public: void set(const T *); };
class W3DHordeModelDrawModuleData { public: int rva00079167(); int rva00079186(int); };
class DataChunkInput; struct DataChunkInfo;
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h"
#include "../../../Libraries/Source/WWVegas/WW3D2/Render2DClass.h"
class TextureFilterClass { public: void Apply(unsigned int); };
namespace _STL { template <class T> class allocator; template <class T, class A> class _List_base { public: void clear(); }; }
struct BfmeVectorRecord001B4A39;
class Rva002034E9Host { public: bool rva002034E9(); };
class Rva0020F58E { public: int length() const; };
class Rva00210E7C { public: void rva00210E9D(); };
class AsciiStringPlusString { public: int length() const; };
#include "../../Include/GameClient/Rva002226E5TextPlusString.h"
class Rva002D2DF6 { public: void rva002D2DF6(); };
class Xfer;
class AptPalantir { public: void xfer(Xfer *); };
namespace FXParticleSystem { class WindModuleInfo { public: virtual void DoXfer(Xfer &); }; }
class BfmeTargetCN;
class BfmeOwnCO { public: char bfmeGuardedCO(BfmeTargetCN *, void *); };
namespace OldPolygonTriggerDataChunkParserBase { class Impl { public: bool parsePolygonTriggersChunkImpl(DataChunkInput &, const DataChunkInfo *); bool parseWaterAreasChunkImpl(DataChunkInput &, const DataChunkInfo *); }; }
class Rva0032AFD4 { public: void rva0032AFD4(char *, int, int); };
class RadiusDecal { public: void clear(); };
class Rva00330E2DFrameOpacity { public: void rva00330E2D(unsigned int); };
class Rva00358E6A { public: void rva00358F7C(); };
class CreateAHeroData;
class ConnectionManager { public: bool areAllQueuesEmpty(); void sendHero(CreateAHeroData *, int, unsigned short, unsigned char); };
class UnicodeString;
class Rva004D0E93 { public: void rva004D0E93(int, int, const UnicodeString &); };
namespace FXParticleSystem { class DefaultColorModuleInfo { public: void tintAllColors(int); }; }

class Rva00330E2DTarget
{
public:
	void rva00330E2D(Int firstValue);
};

class Rva000B318DForwarder
{
public:
	void rva000B318D(Int firstValue);
private:
	char m_lead[0x1D0];
	Rva00330E2DTarget m_member;
};

// vtable 0x00BCBC40#24
void Rva000B318DForwarder::rva000B318D(Int firstValue)
{
	((Rva00330E2DFrameOpacity *)&m_member)->rva00330E2D(firstValue);
}

class Rva00330DBATarget
{
public:
	void rva00330DBA();
};

class Rva000B3266Forwarder
{
public:
	void rva000B3266();
private:
	char m_lead[0x1D0];
	Rva00330DBATarget m_member;
};

// vtable 0x00BCBC40#28
void Rva000B3266Forwarder::rva000B3266()
{
	((RadiusDecal *)&m_member)->clear();
}

class Rva000055F5Target
{
public:
	void rva000055F5(Int firstValue);
};

class Rva000B5FB3Forwarder
{
public:
	void rva000B5FB3(Int firstValue);
private:
	char m_lead[0x260];
	Rva000055F5Target m_member;
};

// vtable 0x00BCBC40#53
void Rva000B5FB3Forwarder::rva000B5FB3(Int firstValue)
{
	((StringBase<char> *)&m_member)->set((const char *)firstValue);
}

class Rva0013132DTarget
{
public:
	void rva0013132D();
};

class Rva00131CD3Forwarder
{
public:
	void rva00131CD3();
private:
	char m_lead[0x14];
	Rva0013132DTarget *m_member;
};

// vtable 0x00BD25D8#2
void Rva00131CD3Forwarder::rva00131CD3()
{
	m_member->rva0013132D();
}

class Rva0013EA30Target
{
public:
	void rva0013EA30(Int firstValue);
};

class Rva00131CEAForwarder
{
public:
	void rva00131CEA(Int firstValue);
private:
	char m_lead[0x1C];
	Rva0013EA30Target m_member;
};

// vtable 0x00BD25D8#16
void Rva00131CEAForwarder::rva00131CEA(Int firstValue)
{
	((TextureFilterClass *)&m_member)->Apply(firstValue);
}

class Rva0055B863Target
{
public:
	void rva0055B863(Int firstValue);
};

class Rva003ABCE6Forwarder
{
public:
	void rva003ABCE6(Int firstValue);
private:
	char m_lead[0x1C];
	Rva0055B863Target m_member;
};

// vtable 0x00C1C53C#4
void Rva003ABCE6Forwarder::rva003ABCE6(Int firstValue)
{
	((FXParticleSystem::DefaultColorModuleInfo *)&m_member)->tintAllColors(firstValue);
}

class Rva0023DAA5Target
{
public:
	void rva0023DAA5();
};

class Rva002C5265Forwarder
{
public:
	void rva002C5265();
private:
	char m_lead[0x30];
	Rva0023DAA5Target m_member;
};

// vtable 0x00BC7C90#45
void Rva002C5265Forwarder::rva002C5265()
{
	((_STL::_List_base<int, _STL::allocator<int> > *)&m_member)->clear();
}

class Rva002D2DF6Target
{
public:
	void rva002D2DF6();
};

class Rva002D35C7Forwarder
{
public:
	void rva002D35C7();
private:
	char m_lead[0x10];
	Rva002D2DF6Target *m_member;
};

// vtable 0x00C02AA8#9
void Rva002D35C7Forwarder::rva002D35C7()
{
	((Rva002D2DF6 *)m_member)->rva002D2DF6();
}

class Rva002D6460Target
{
public:
	void rva002D6460(Int firstValue);
};

class Rva002D65EEForwarder
{
public:
	void rva002D65EE(Int firstValue);
private:
	char m_lead[0x4];
	Rva002D6460Target *m_member;
};

// vtable 0x00C02A84#7
void Rva002D65EEForwarder::rva002D65EE(Int firstValue)
{
	((AptPalantir *)m_member)->xfer((Xfer *)firstValue);
}

class Rva003295B4Target
{
public:
	void rva003295B4(Int firstValue, Int secondValue);
};

class Rva0032965BForwarder
{
public:
	void rva0032965B(Int firstValue, Int secondValue);
private:
	char m_lead[0x4];
	Rva003295B4Target *m_member;
};

// vtable 0x00C0D8C4#1
void Rva0032965BForwarder::rva0032965B(Int firstValue, Int secondValue)
{
	((OldPolygonTriggerDataChunkParserBase::Impl *)m_member)->parseWaterAreasChunkImpl(*(DataChunkInput *)firstValue, (const DataChunkInfo *)secondValue);
}

class Rva00119F00Target
{
public:
	void rva00119F00();
};

class Rva000448B9Forwarder
{
public:
	void rva000448B9();
private:
	char m_lead[0x168];
	Rva00119F00Target *m_member;
};

// vtable 0x00BC3C80#53
void Rva000448B9Forwarder::rva000448B9()
{
	((Render2DClass *)m_member)->Reset();
}

class Rva00079167Target
{
public:
	void rva00079167();
};

class Rva000791DDForwarder
{
public:
	void rva000791DD();
private:
	char m_lead[0x4];
	Rva00079167Target *m_member;
};

// vtable 0x00BC68F0#66
void Rva000791DDForwarder::rva000791DD()
{
	((W3DHordeModelDrawModuleData *)m_member)->rva00079167();
}

class Rva00079186Target
{
public:
	void rva00079186(Int firstValue);
};

class Rva000791E5Forwarder
{
public:
	void rva000791E5(Int firstValue);
private:
	char m_lead[0x4];
	Rva00079186Target *m_member;
};

// vtable 0x00BC68F0#67
void Rva000791E5Forwarder::rva000791E5(Int firstValue)
{
	((W3DHordeModelDrawModuleData *)m_member)->rva00079186(firstValue);
}


// The global at VA 0x00DFE1C8.
class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;

class Rva0009AD42Forwarder
{
public:
	void rva0009AD42();
private:
};

// vtable 0x00BC89C8#12
void Rva0009AD42Forwarder::rva0009AD42()
{
	((Rva00210E7C *)TheLivingWorldManager)->rva00210E9D();
}

class Rva000B0DA8Target
{
public:
	void ParseHeightMapData(Int firstValue, Int secondValue);
};

class Rva000B1974Forwarder
{
public:
	void rva000B1974(Int firstValue, Int secondValue);
private:
	char m_lead[0xC];
	Rva000B0DA8Target *m_member;
};

// vtable 0x00BC95B8#1
void Rva000B1974Forwarder::rva000B1974(Int firstValue, Int secondValue)
{
	((WorldHeightMap *)m_member)->ParseHeightMapData(*(DataChunkInput *)firstValue, (DataChunkInfo *)secondValue);
}

class Rva001B4C7ATarget
{
public:
	void rva001B4C7A();
};

class Rva001B4CD0Forwarder
{
public:
	void rva001B4CD0();
private:
	char m_lead[0xC];
	Rva001B4C7ATarget m_member;
};

// vtable 0x00BD7678#1
void Rva001B4CD0Forwarder::rva001B4CD0()
{
	((_STL::_List_base<BfmeVectorRecord001B4A39, _STL::allocator<BfmeVectorRecord001B4A39> > *)&m_member)->clear();
}

class Rva00222D47Target
{
public:
	void rva00222D47(Int firstValue, Int secondValue, Int thirdValue);
};

// Slot 1 of Rva00222A19's table 0x00BE6D5C (constructor in RvaSmallVtableCtors.cpp).
class Rva00222A19
{
public:
	virtual int rva00222A2B();
	virtual void rva00222D3F(Int firstValue, Int secondValue, Int thirdValue);
	virtual Int rva00222D26(char *buf);
private:
	void *m_member;
};

// vtable 0x00BE6D5C#1
void Rva00222A19::rva00222D3F(Int firstValue, Int secondValue, Int thirdValue)
{
	((Rva00222D47Target *)m_member)->rva00222D47(firstValue, secondValue, thirdValue);
}

class Rva0022C9D2Forwarder
{
public:
	void rva0022C9D2();
private:
	char m_lead[0x10];
	Rva0023DAA5Target m_member;
};

// vtable 0x00BE74F0#9
void Rva0022C9D2Forwarder::rva0022C9D2()
{
	((_STL::_List_base<int, _STL::allocator<int> > *)&m_member)->clear();
}

class Rva004CF3B9Target
{
public:
	void rva004CF3B9();
};

class Rva0025DC30Forwarder
{
public:
	void rva0025DC30();
private:
	char m_lead[0xC];
	Rva004CF3B9Target *m_member;
};

// vtable 0x00BF6040#31
void Rva0025DC30Forwarder::rva0025DC30()
{
	((ConnectionManager *)m_member)->areAllQueuesEmpty();
}

class Rva004D01D5Target
{
public:
	void rva004D01D5(Int firstValue, Int secondValue, Int thirdValue, Int fourthValue);
};

class Rva0025DC56Forwarder
{
public:
	void rva0025DC56(Int firstValue, Int secondValue, Int thirdValue, Int fourthValue);
private:
	char m_lead[0xC];
	Rva004D01D5Target *m_member;
};

// vtable 0x00BF6040#34
void Rva0025DC56Forwarder::rva0025DC56(Int firstValue, Int secondValue, Int thirdValue, Int fourthValue)
{
	((ConnectionManager *)m_member)->sendHero((CreateAHeroData *)firstValue, secondValue, (unsigned short)thirdValue, (unsigned char)fourthValue);
}

class Rva004D0E93Target
{
public:
	void rva004D0E93(Int firstValue, Int secondValue, Int thirdValue);
};

class Rva0025DEDDForwarder
{
public:
	void rva0025DEDD(Int firstValue, Int secondValue, Int thirdValue);
private:
	char m_lead[0xC];
	Rva004D0E93Target *m_member;
};

// vtable 0x00BF6040#66
void Rva0025DEDDForwarder::rva0025DEDD(Int firstValue, Int secondValue, Int thirdValue)
{
	((Rva004D0E93 *)m_member)->rva004D0E93(firstValue, secondValue, *(const UnicodeString *)thirdValue);
}


// The global at VA 0x00DFE78C.
extern class GameLogic *TheGameLogic;

class Rva002A9F53Forwarder
{
public:
	void rva002A9F53();
private:
};

// vtable 0x00BFDF18#5
void Rva002A9F53Forwarder::rva002A9F53()
{
	(*(Rva002034E9Host **)&TheGameLogic)->rva002034E9();
}

class Rva002AC2CFTarget
{
public:
	void rva002AC2CF(Int firstValue, Int secondValue, Int thirdValue);
};

// The three slots of Rva002AAD9C's table 0x00BFDC6C (constructor in
// RvaSmallVtableCtors.cpp), each reaching the payload it stores at +4.
class Rva002AAD9C
{
public:
	virtual void rva002AADAE();
	virtual void rva002AC2C7(Int firstValue, Int secondValue, Int thirdValue);
	virtual void rva002AC2BF(Int firstValue);
private:
	void *m_member;
};

// vtable 0x00BFDC6C#0
void Rva002AAD9C::rva002AADAE()
{
	((Rva002226E5TextPlusString *)m_member)->length();
}

// vtable 0x00BFDC6C#2
void Rva002AAD9C::rva002AC2BF(Int firstValue)
{
	((Rva002226E5TextPlusString *)m_member)->write((char *)firstValue);
}

// vtable 0x00BFDC6C#1
void Rva002AAD9C::rva002AC2C7(Int firstValue, Int secondValue, Int thirdValue)
{
	((Rva002AC2CFTarget *)m_member)->rva002AC2CF(firstValue, secondValue, thirdValue);
}

class Rva003003C5Target
{
public:
	void rva003003C5(Int firstValue, Int secondValue);
};

class Rva00300481Forwarder
{
public:
	void rva00300481(Int firstValue, Int secondValue);
private:
	char m_lead[0xC];
	Rva003003C5Target *m_member;
};

// vtable 0x00C07484#1
void Rva00300481Forwarder::rva00300481(Int firstValue, Int secondValue)
{
	((BfmeOwnCO *)m_member)->bfmeGuardedCO((BfmeTargetCN *)firstValue, (void *)secondValue);
}

class Rva003294D6Target
{
public:
	void rva003294D6(Int firstValue, Int secondValue);
};

class Rva00329653Forwarder
{
public:
	void rva00329653(Int firstValue, Int secondValue);
private:
	char m_lead[0x4];
	Rva003294D6Target *m_member;
};

// vtable 0x00C0D8C4#0
void Rva00329653Forwarder::rva00329653(Int firstValue, Int secondValue)
{
	((OldPolygonTriggerDataChunkParserBase::Impl *)m_member)->parsePolygonTriggersChunkImpl(*(DataChunkInput *)firstValue, (const DataChunkInfo *)secondValue);
}

class Rva002198C8Target
{
public:
	void rva002198C8();
};

class Rva0032AF9CForwarder
{
public:
	void rva0032AF9C();
private:
	char m_lead[0x4];
	Rva002198C8Target *m_member;
};

// vtable 0x00C0D938#0
void Rva0032AF9CForwarder::rva0032AF9C()
{
	((AsciiStringPlusString *)m_member)->length();
}

class Rva0032AFD4Target
{
public:
	void rva0032AFD4(Int firstValue, Int secondValue, Int thirdValue);
};

class Rva0032AFCCForwarder
{
public:
	void rva0032AFCC(Int firstValue, Int secondValue, Int thirdValue);
private:
	char m_lead[0x4];
	Rva0032AFD4Target *m_member;
};

// vtable 0x00C0D938#1
void Rva0032AFCCForwarder::rva0032AFCC(Int firstValue, Int secondValue, Int thirdValue)
{
	((Rva0032AFD4 *)m_member)->rva0032AFD4((char *)firstValue, secondValue, thirdValue);
}

class Rva0033082FTarget
{
public:
	unsigned char rva0033082F(Int firstValue, Int secondValue);
};

class Rva003308EEForwarder
{
public:
	void rva003308EE(Int firstValue, Int secondValue);
private:
	char m_lead[0xC];
	Rva0033082FTarget *m_member;
};

// vtable 0x00C0DB58#1
void Rva003308EEForwarder::rva003308EE(Int firstValue, Int secondValue)
{
	m_member->rva0033082F(firstValue, secondValue);
}

class Rva00358F7CTarget
{
public:
	void rva00358F7C();
};

class Rva003592FAForwarder
{
public:
	void rva003592FA();
private:
	char m_lead[0xC];
	Rva00358F7CTarget m_member;
};

// vtable 0x00C15398#9
void Rva003592FAForwarder::rva003592FA()
{
	((Rva00358E6A *)&m_member)->rva00358F7C();
}

class Rva00392092Target
{
public:
	void rva00392092();
};

class Rva003922B7Forwarder
{
public:
	void rva003922B7();
private:
	char m_lead[0x10];
	Rva00392092Target m_member;
};

// vtable 0x00C1A088#1
void Rva003922B7Forwarder::rva003922B7()
{
	m_member.rva00392092();
}

class Rva003A547ETarget
{
public:
	void rva003A547E(Int firstValue);
};

class Rva003A5896Forwarder
{
public:
	// virtual: also reached through the this-0x1C thunk 0x003A589E.
	virtual void rva003A5896(Int firstValue);
private:
	char m_lead[0x1C - 4];
	Rva003A547ETarget m_member;
};

// vtable 0x00C1B5A8#3
void Rva003A5896Forwarder::rva003A5896(Int firstValue)
{
	((FXParticleSystem::WindModuleInfo *)&m_member)->FXParticleSystem::WindModuleInfo::DoXfer(*(Xfer *)firstValue);
}

class Rva004DFC20
{
public:
	void clear();
};

class Rva003ED1B6Forwarder
{
public:
	void rva003ED1B6();
private:
	char m_lead[0xC];
	Rva004DFC20 m_member;
};

// vtable 0x00C36100#9
void Rva003ED1B6Forwarder::rva003ED1B6()
{
	m_member.clear();
}

class Rva003FD05ETarget
{
public:
	void rva003FD05E(Int firstValue, Int secondValue, Int thirdValue);
};

// Two slots of Rva003FC428's table 0x00C37C20 (constructor in
// RvaSmallVtableCtors.cpp; slot 2 is in Rva003FD02EWrite.cpp), each reaching
// the payload it stores at +4.
class Rva003FC428
{
public:
	virtual void rva003FCE30();
	virtual void rva003FD056(Int firstValue, Int secondValue, Int thirdValue);
	virtual int rva003FD02E(char *dst);
private:
	void *m_member;
};

// vtable 0x00C37C20#0
void Rva003FC428::rva003FCE30()
{
	((Rva0020F58E *)m_member)->length();
}

// vtable 0x00C37C20#1
void Rva003FC428::rva003FD056(Int firstValue, Int secondValue, Int thirdValue)
{
	((Rva003FD05ETarget *)m_member)->rva003FD05E(firstValue, secondValue, thirdValue);
}
