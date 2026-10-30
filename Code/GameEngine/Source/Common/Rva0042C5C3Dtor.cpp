// cl: /O1 /MD /EHsc
// ??1Rva0042C5C3@@UAE@XZ, retail 0x0042C5C3..0x0042C677 (180 bytes, EH):
// the destructor of the 0x3C-byte impl built by ??0Rva0042C5C3 (0x0042C693;
// opaque pin of its scalar deleting destructor). Own tables 0x00C3C6E4,
// 0x00C3C6DC (+4), 0x00C3C6D4 (+8) and 0x00C3C6D0 (+0xC). With
// TheLivingWorldLogic present it takes its +8 and +4 subobjects off the
// logic's lists at +0x1C and +0x4C (rowed erase 0x002B7250), unregisters this
// from its +0x20 owner (rowed 0x0042CAEB), then its parts die as retail's
// unwind map lists them: the +0x38 owned-pointer cell (rowed clear
// 0x0042C1DF), the +0x34 cell (rowed 0x000AD6F4), the base at +0xC (rowed
// 0x00574A8A), the StrategicHUD cell base at +0x14 (rowed 0x0042E00F) and
// the three interface bases whose inline destructors restore 0x00C62A20,
// 0x00BED658 and 0x00BDBA74 (out-of-line copies 0x004EDFFF, 0x00238D97 and
// 0x00429191). Complete-class identity remains unknown; interface roles
// are established by the native tables and registrations below.
class CreateAHeroData;
class Rva0042C1B7Item;
class Rva002D3627Host;
class Rva0042D8D4;
struct Rva002BA8F1Listener;
class Rva005A0B4CList { public: void append(Rva002BA8F1Listener *); };
namespace StrategicHUD { class HUD { public: void Show(); }; }

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *who);
};

class LivingWorldLogic
{
public:
	unsigned char m_pad00[0x1C];
	Rva002B7250 m_list1C;
	unsigned char m_pad1D[0x4C - 0x1D];
	Rva002B7250 m_list4C;
};

extern LivingWorldLogic *TheLivingWorldLogic;

class Rva0042CBB6
{
public:
	void rva0042CAEB(int who);
	void rva002B230F(int impl);
};

class Rva000AD6F4
{
public:
	Rva000AD6F4() : m_ptr(0) {}
	~Rva000AD6F4();

	void *m_ptr;
};

class Rva0057417E { public: ~Rva0057417E(); };
#include <new>

class Rva0042C1DF
{
public:
	Rva0042C1DF() : m_ptr(0) {}
	__declspec(noinline) ~Rva0042C1DF();
	void clear();
private:
	Rva0057417E *m_ptr;
};

// The native normal and exceptional member lifetimes both call the complete
// 26-byte cleanup at42C1DF. Emit that same cleanup as the destructor rather
// than inventing a separate five-byte forwarding entry. The existing reset
// owner proves both calls and their relocation targets; original types remain
// address-derived. Keeping the body out of line preserves the native parent.
Rva0042C1DF::~Rva0042C1DF()
{
	Rva0057417E *ownedObject = m_ptr;
	m_ptr = 0;
	if (ownedObject)
	{
		ownedObject->Rva0057417E::~Rva0057417E();
		::operator delete(ownedObject);
	}
}

class Rva0042DFF5
{
public:
	Rva0042DFF5(const unsigned int &level);
	~Rva0042DFF5();
private:
	void *m_ptr;
};

class Rva00574A8A
{
public:
	Rva00574A8A(unsigned int first, unsigned int second);
	virtual ~Rva00574A8A();
private:
	int m_04;
};

// BFME1 a0e8f345a9b2 MessageStream shim and its ZH GeneralsMD header
// corroborate translator slot order. Native BDBA74 and the114B message
// callback establish this target ABI; the neutral class spelling is retained.
class Rva001DB080
{
public:
 virtual int translateGameMessage(const void *) = 0;
 virtual ~Rva001DB080() {}
};

#include "../../Include/Common/LivingWorldLogicObserver.h"

#include "../../Include/Common/RegionTurnObserverView.h"

struct Rva0042C083Param {int x,y;};
union GameMessageArgumentType {Rva0042C083Param position;int integer;};
class GameMessage {public:const GameMessageArgumentType*getArgument(int)const;char unknown0[0x10];int type;};
class Rva005E6817Mid {public:int fwd(GameMessage*);};
class Rva0042C083 {public:void rva0042C083(const Rva0042C083Param*);};
class RAMFile {public:virtual int write(const void*,int);};
class Mouse {public:
 virtual void m0();virtual void m1();virtual void m2();virtual void m3();virtual void m4();
 virtual void m5();virtual void m6();virtual void m7();virtual void m8();virtual void m9();
 virtual void m10();virtual void m11();virtual void m12();virtual void m13();virtual void m14();
 virtual void m15();virtual void m16();virtual void m17();virtual void m18();virtual void m19(int);
 char unknown4[0x4FA0];int cursor;
};
extern Mouse*TheMouse;
class Rva0042C0DBDelegate {public:
 virtual void slot0();virtual void slot1();virtual int slot2(GameMessage*);virtual int slot3(const Rva0042C083Param*,int);
 __declspec(noinline) int invokeMessage(GameMessage*);__declspec(noinline) int invokePoint(const Rva0042C083Param*,int);
};

class Rva0042C5C3 : public Rva001DB080, public LivingWorldLogicObserver, public RegionTurnObserverView,
	public Rva0042DFF5, public Rva00574A8A
{
public:
	Rva0042C5C3(Rva0042C1B7Item *owner, Rva002D3627Host *holder,
		Rva0042CBB6 *source, Rva0042D8D4 *state);
	virtual ~Rva0042C5C3();
 virtual int translateGameMessage(const void *);
 virtual void event6_0(int);
 virtual void OnTurnEnding(int,int);
 int rva0042C0DB(const Rva0042C083Param *,int);
private:
	int m_18;
	int m_1C;
	Rva0042CBB6 *m_owner;			// +0x20
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	Rva000AD6F4 m_34;
	Rva0042C1DF m_38;
};

// Native42C693..42C76B RET16 and the two rowed wrapper constructors prove
// these four argument words. The destructor above supplies the actual base
// layout and unwind ordering; WB12BB6F0 is a structural constructor guide.
// The +14 cell consumes the first word of state by reference. The +C base
// forwards holder and that cell's address as opaque words through its rowed
// constructor; no additional names or pointee layouts are claimed here.
Rva0042C5C3::Rva0042C5C3(Rva0042C1B7Item *owner, Rva002D3627Host *holder,
	Rva0042CBB6 *source, Rva0042D8D4 *state)
	: Rva0042DFF5(*reinterpret_cast<const unsigned int *>(state)),
	  Rva00574A8A((unsigned int)holder, (unsigned int)static_cast<Rva0042DFF5 *>(this)),
	  m_18((int)owner), m_1C((int)holder), m_owner(source),
	  m_24(0), m_28(0), m_2C(-1), m_30(-1)
{
	reinterpret_cast<StrategicHUD::HUD *>(static_cast<Rva0042DFF5 *>(this))->Show();
	m_owner->rva002B230F((int)this);
	reinterpret_cast<Rva005A0B4CList *>(&TheLivingWorldLogic->m_list4C)->append(
		reinterpret_cast<Rva002BA8F1Listener *>(static_cast<LivingWorldLogicObserver *>(this)));
	reinterpret_cast<Rva005A0B4CList *>(&TheLivingWorldLogic->m_list1C)->append(
		reinterpret_cast<Rva002BA8F1Listener *>(static_cast<RegionTurnObserverView *>(this)));
}

Rva0042C5C3::~Rva0042C5C3()
{
	if (TheLivingWorldLogic)
	{
		TheLivingWorldLogic->m_list1C.rva002B7250((CreateAHeroData *)static_cast<RegionTurnObserverView *>(this));
		TheLivingWorldLogic->m_list4C.rva002B7250((CreateAHeroData *)static_cast<LivingWorldLogicObserver *>(this));
	}
	m_owner->rva0042CAEB((int)this);
}

// Native 0x00787652: complete20B null-preserving adjusted-base lifetime action.
// Whole180B owner and native EH graph prove the receiver adjustment; the
// existing same-object7B destructor restores its witnessed base table.

// Native007876AD: complete11B member38 unwind reaches the same full26B
// owned-pointer destructor as normal teardown. Whole180B parent and its
// complete native EH graph prove this lifetime and receiver adjustment.

// Native 0x00787666: complete20B null-preserving adjusted-base lifetime action.
// Whole180B owner and native EH graph prove the receiver adjustment; the
// existing same-object7B destructor restores its witnessed base table.

int Rva0042C5C3::rva0042C0DB(const Rva0042C083Param*p,int value){
 if(TheMouse){
  int cursor;
  switch(m_24){
   default:
    if(m_34.m_ptr)cursor=((Rva0042C0DBDelegate *)m_34.m_ptr)->invokePoint(p,value);
    else cursor=((RAMFile*)((char*)this+0xC))->RAMFile::write(p,value);
    if(cursor<1||cursor>=0x38)cursor=2;
    break;
   case 3:cursor=2;break;
  }
  if(cursor!=TheMouse->cursor)TheMouse->m19(cursor);
 }
 ((Rva0042C083 *)m_1C)->rva0042C083(p);
 return 0;
}
int Rva0042C5C3::translateGameMessage(const void *raw){
 GameMessage *gameMessage=(GameMessage*)raw;
 if(m_24!=3){
  int result;
  if(m_34.m_ptr)result=((Rva0042C0DBDelegate *)m_34.m_ptr)->invokeMessage(gameMessage);
  else result=((Rva005E6817Mid*)((char*)this+0xC))->fwd(gameMessage);
  if(result==1)return result;
 }
 int type=gameMessage->type;
 if(type!=3)return type==0x6F;
 Rva0042C083Param point=gameMessage->getArgument(0)->position;
 return rva0042C0DB(&point,gameMessage->getArgument(1)->integer);
}

void Rva0042C5C3::event6_0(int){m_2C=0;}
void Rva0042C5C3::OnTurnEnding(int,int value){m_2C=value;}

// Native C3C6E4 is the two-slot translator table. C3C6DC at+4 is the
// two-slot Logic observer; C3C6D4 at+8 is the two-slot turn observer.
// Their scalar callbacks both write complete-object word2C. The names of
// the complete class and this state word remain unknown. These three views
// replace single-slot placeholders; the existing+C provider is retained.
