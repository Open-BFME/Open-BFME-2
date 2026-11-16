// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
#include "ascii_string.h"
// Native0050F85D..0050F909 RET8; target color callback0050E7EB reads58.
// WorldBuilder AptPlayerTribute.cpp binds the same _level%u.%s_color query.
// Existing row destructor0050FAEC and C65518 one-entry vtable prove this
// neutral class identity; adjacent C6551C is a separate page vtable.
// Registry58 comes from existing target callback views; constructor calls
// existing002D2C34 and the16B multiple-inheritance binding holder0057BC63.
// Original constructor/class spelling unknown; no donor-layout fact claimed.
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

#include "../../../../../Include/GameClient/FunctorBinding.h"

#include "../../../../../Include/Common/FunctorWrapperHead.h"

class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);
	Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_refCount;
	}

	FunctorWrapperHead *m_ptr;
};

__forceinline FunctorBinding MakeBinding(FunctorMethod method, FunctorTarget *target)
{
	FunctorBinding binding(method, target);
	return binding;
}

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

template <class T> class AptRef : public Rva0057BC63FunctorHolder
{
public:
	AptRef(const FunctorBinding &binding) : Rva0057BC63FunctorHolder(binding) {}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
};

class AptCommandMap;
class AptExternHandler;

#include "../../../../../../Libraries/Source/Apt/AptCommandMapAdder.h"

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);

private:
	unsigned char m_names[12]; // an STLport vector<AsciiString>
};

// The 0x58-byte callback registry (as in BfmeAptGameWindowDestructor.cpp),
// constructed by the rowed 0x002D2C34.
class __declspec(novtable) Rva005248D0
{
public:
	Rva005248D0();
	virtual ~Rva005248D0();

	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10

private:
	unsigned char m_pad01C[0x58 - 0x1C];
};


class Rva0050FAEC:public Rva005248D0 {public:Rva0050FAEC(int level,const AsciiString&name);virtual ~Rva0050FAEC();void color(int,char*,bool);protected:int m_color;};
#pragma pointers_to_members(full_generality, multiple_inheritance)
Rva0050FAEC::Rva0050FAEC(int level,const AsciiString&name):m_color(0){AsciiString key;key.format("_level%u.%s_color",level,name.str());FunctorMethod method=reinterpret_cast<FunctorMethod>(&Rva0050FAEC::color);m_externHandlers.AddExternHandler(key,0,AptRef<AptExternHandler>(MakeBinding(method,reinterpret_cast<FunctorTarget*>(this))));}

#include "unicode_string.h"
#include "../../../../../Include/GameNetwork/GameInfo.h"
extern GameInfo*TheGameInfo;
struct UnknownE03138 {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual bool isDefeated(void*);};class VictoryConditionsInterface; extern VictoryConditionsInterface *TheVictoryConditions;
#include "../../../../../Include/GameClient/GameText.h"
#include "../../../../../Include/GameNetwork/NetworkInterfaceClass.h"
extern NetworkInterface*TheNetwork;
extern GameTextInterface*TheGameText;
#include "../../../../../Include/GameNetwork/MultiplayerColorDefinition.h"
#include "../../../../../Include/GameNetwork/MultiplayerSettingsClass.h"
extern MultiplayerSettings*TheMultiplayerSettings;
#include "../../../../../Include/Common/Player.h"
void Rva0050EE72Set(int,const AsciiString&,int,const UnicodeString&);
class Rva0050F909:public Rva0050FAEC {public:Rva0050F909(int,const AsciiString&,int,int);virtual~Rva0050F909(){}};
Rva0050F909::Rva0050F909(int level,const AsciiString&path,int slotIndex,int stateWord):Rva0050FAEC(level,path){
 const GameSlot*slot=TheGameInfo->getConstSlot(slotIndex);bool alive=!((UnknownE03138 *)TheVictoryConditions)->isDefeated((void*)stateWord);bool observer=((const Player*)stateWord)->isPlayerObserver();
 Rva0050EE72Set(level,path,0,slot->m_name);Rva0050EE72Set(level,path,1,slot->getApparentPlayerTemplateDisplayName());
 AsciiString text;text.format("Team:%d",slot->m_teamNumber+1);if(slot->isAI()&&slot->m_teamNumber==-1)text="Team:AI";
 Rva0050EE72Set(level,path,2,TheGameText->fetch(text,0));text.clear();
 bool ok;
 if(slot->isAI())ok=true;else if(!TheNetwork)ok=true;else ok=TheNetwork->slot51(slotIndex);
 if(ok){
  if(alive)text="GUI:PlayerAlive";else if(observer)text="GUI:PlayerObserver";else text="GUI:PlayerDead";
 }else{
  if(observer)text="GUI:PlayerObserverGone";else text="GUI:PlayerGone";
 }
 Rva0050EE72Set(level,path,3,TheGameText->fetch(text,0));m_color=TheMultiplayerSettings->getColor(slot->getApparentColor())->m_color;
}
