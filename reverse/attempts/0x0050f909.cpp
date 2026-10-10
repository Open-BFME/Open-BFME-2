// ??0Rva0050F909@@QAE@HABVAsciiString@@HH@Z
// partial score=0.9300901688984591 date=2026-10-10
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

struct FunctorBinding
{
	FunctorBinding(FunctorMethod method, FunctorTarget *target) : m_target(target), m_method(method) {}

	FunctorTarget *m_target;
	unsigned int m_pad;
	FunctorMethod m_method;
};

class FunctorWrapperHead
{
public:
	void *m_vtbl;
	int m_refCount; // +0x04
};

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

class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

private:
	unsigned char m_names[12]; // an STLport vector<AsciiString>
};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);

private:
	unsigned char m_names[12]; // an STLport vector<AsciiString>
};

// The 0x58-byte callback registry (as in BfmeAptGameWindowDestructor.cpp),
// constructed by the pinned 0x002D2C34.
class Rva002D2C34
{
public:
	void rva002D2C34();
};

class __declspec(novtable) Rva005248D0
{
public:
	__forceinline Rva005248D0() { ((Rva002D2C34 *)this)->rva002D2C34(); }
	virtual ~Rva005248D0();

	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10

private:
	unsigned char m_pad01C[0x58 - 0x1C];
};


class Rva0050FAEC:public Rva005248D0 {public:Rva0050FAEC(int level,const AsciiString&name);virtual ~Rva0050FAEC(){}void color(int,char*,bool);protected:int m_color;};
#pragma pointers_to_members(full_generality, multiple_inheritance)
Rva0050FAEC::Rva0050FAEC(int level,const AsciiString&name):m_color(0){AsciiString key;key.format("_level%u.%s_color",level,name.str());FunctorMethod method=reinterpret_cast<FunctorMethod>(&Rva0050FAEC::color);m_externHandlers.AddExternHandler(key,0,AptRef<AptExternHandler>(MakeBinding(method,reinterpret_cast<FunctorTarget*>(this))));}

#include "unicode_string.h"
class GameSlot {public:bool isAI()const;UnicodeString getApparentPlayerTemplateDisplayName()const;int getApparentColor()const;char pad[0x1C];int team;char pad2[0x30-0x20];UnicodeString playerName;};
class GameInfo {public:const GameSlot*getConstSlot(int)const;};extern GameInfo*TheGameInfo;
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
virtual bool isDefeated(void*);};extern UnknownE03138*g_00E03138;
class NetworkInterface {public:
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
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual bool connected(int);};extern NetworkInterface*TheNetwork;
class GameTextInterface {public:
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
virtual UnicodeString fetch(const char*,bool*exists=0);virtual UnicodeString fetch(const AsciiString&,bool*exists=0);};extern GameTextInterface*TheGameText;
class MultiplayerColorDefinition {public:char pad[0x10];int color;};class MultiplayerSettings {public:MultiplayerColorDefinition*getColor(int);};extern MultiplayerSettings*TheMultiplayerSettings;
struct Rva0050F909State {char pad[0x33A];bool flag;__declspec(noinline) bool state()const{return flag;}};
void Rva0050EE72Set(int,const AsciiString&,int,const UnicodeString&);
class Rva0050F909:public Rva0050FAEC {public:Rva0050F909(int,const AsciiString&,int,int);virtual~Rva0050F909(){}};
Rva0050F909::Rva0050F909(int level,const AsciiString&path,int slotIndex,int stateWord):Rva0050FAEC(level,path){
 const GameSlot*slot=TheGameInfo->getConstSlot(slotIndex);bool alive=!g_00E03138->isDefeated((void*)stateWord);bool observer=((Rva0050F909State*)stateWord)->state();
 Rva0050EE72Set(level,path,0,slot->playerName);Rva0050EE72Set(level,path,1,slot->getApparentPlayerTemplateDisplayName());
 AsciiString text;text.format("Team:%d",slot->team+1);if(slot->isAI()&&slot->team==-1)text="Team:AI";
 Rva0050EE72Set(level,path,2,TheGameText->fetch(text,0));text.clear();
 if(slot->isAI())goto Active;
 if(!TheNetwork)goto Active;
 if(!TheNetwork->connected(slotIndex))goto Gone;
Active:
 if(alive)text="GUI:PlayerAlive";else if(observer)text="GUI:PlayerObserver";else text="GUI:PlayerDead";
 goto Status;
Gone:
 if(observer)text="GUI:PlayerObserverGone";else text="GUI:PlayerGone";
Status:;
 Rva0050EE72Set(level,path,3,TheGameText->fetch(text,0));m_color=TheMultiplayerSettings->getColor(slot->getApparentColor())->color;
}
