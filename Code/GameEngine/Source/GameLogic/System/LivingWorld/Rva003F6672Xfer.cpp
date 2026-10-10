// stlport
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Native 3F6672..3F6727 transfers the leading field and the 48-byte player
// vector at +4, then the ID vector at +10 for version >=2. WB1049ED0
// supplies the transfer guide; its enclosing method name is unknown.
// The existing vector resize/erase and free vector-transfer providers own
// their callees. WB1049300 independently names the 48-byte element's
// LivingWorldBattle::BattlePlayer::DoXfer; native REL32 agrees at3F66EB.
// This aligned version view reproduces retail stack storage; only its first
// two bytes and Xfer slots04/28/7C are established target fields. It does
// not assert the original Xfer::Version class size.
union XferVersion {struct {unsigned char m_minVersion,m_version;}; unsigned int value;};

class Xfer
{
public:
	virtual void slot00();
	virtual bool isLoading();			// +0x04
	virtual void slot08();
	virtual bool isCRC();				// +0x0C
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void xferVersion(XferVersion &version);	// +0x28
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void xferUnsignedInt(unsigned int &value);	// +0x78
	virtual void xferInt(int &value);		// +0x7C
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
	virtual void xferBool(bool &value);		// +0x90
};


struct Rva003F610FElement { char bytes[48]; };
namespace _STL { template<class T> class allocator;template<class T,class A>class vector;
template<>class vector<Rva003F610FElement,allocator<Rva003F610FElement> > {public:Rva003F610FElement*erase(Rva003F610FElement*,Rva003F610FElement*);};
}
class Rva003F664FOwner {public:void rva003F664F(unsigned);};
#include "../../../Common/BfmeIntVecG.h"
class LivingWorldBattle {public:class BattlePlayer {public:void DoXfer(Xfer*);};};
Xfer* Rva003F5A72Xfer(Xfer*,void*);
struct Players48 {Rva003F610FElement*first,*last,*limit;int size(){return last-first;}void clear(){((_STL::vector<Rva003F610FElement,_STL::allocator<Rva003F610FElement> >*)this)->erase(first,last);}};
class Rva003F6672 {public:void rva003F6672(Xfer*);int field00;Players48 players;BfmeIntVecG ids;};
void Rva003F6672::rva003F6672(Xfer *xfer) {
 XferVersion version;version.m_minVersion=1;version.m_version=2;
 xfer->xferVersion(version);xfer->xferInt(field00);
 int count=players.size();xfer->xferInt(count);
 if(xfer->isLoading()) { players.clear();((Rva003F664FOwner*)&players)->rva003F664F(count); }
 for(int i=0;i<count;++i) ((LivingWorldBattle::BattlePlayer*)&players.first[i])->DoXfer(xfer);
 if(version.m_version>=2) Rva003F5A72Xfer(xfer,&ids);
 else ids.clear();
}
