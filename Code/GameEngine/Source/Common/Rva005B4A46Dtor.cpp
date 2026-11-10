// stlport
// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Native 005B4A46..005B4AD9 (147B): CahAppearance cleanup. Both literals
// identify its Apt resources; the application class name remains unresolved.
// The final vptr is the rowed Rva005B253F base's table (VA C72B74).
// Lead: Rva005B2575Dtor.cpp's string/screen cleanup and inline base teardown.
// Retail constructor 005B4F6F and registered callback addresses identify
// the appearance subsystem; neutral class ownership remains unchanged.
// Target accesses prove owner hero+27C, registries+21C/+228, selections
// +414/+418, and this view's window+8/active+C/IME+D. WB names are leads.
// Reference StringBase supplies the inline empty test and nonallocating
// compare semantics; every admitted hot body and EH map is verified.
#include "ascii_string.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "unicode_string.h"
// The reference isEmpty body is header-defined; compare performs only bounded C-runtime comparison.
// Link-suppressed (dllimport, no COMDAT) so this TU emits no copy competing
// with the rowed body in string_base_inline.cpp (0x00035740).
template<> __declspec(dllimport) __forceinline bool StringBase<unsigned short>::isEmpty()const{return m_data==0||m_data->length==0;}
template<> int StringBase<unsigned short>::compare(const StringBase<unsigned short>&)const throw();
class Rva00406F12 {public:bool rva00406F12(int);};
class Rva00406F27 {public:bool rva00406F27(int);};
class Rva00406F3C {public:bool rva00406F3C(int);};
class AppearanceHeroView {public:virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();virtual void refresh(bool);virtual void refresh14();char unknown04[0x2C-4];unsigned m_hairColor,m_skinColor,m_paintColor;};
#include "../../Include/GameClient/AptMyHero.h"
class CreateAHeroHero {public:bool SetDefaultColors();};
class Rva005B4BDB {public:void rva005B4C3C();void rva005B4BDB();void rva005B4AD9(int);};
class Rva005B5C02Box {public:void Run();};
class GameWindow;

UnicodeString GadgetTextEntryGetText(GameWindow*);
void GadgetTextEntrySetText(GameWindow*,UnicodeString);
class LanguageFilter {public:void filterLine(UnicodeString&);};extern LanguageFilter*TheLanguageFilter;
class CreateAHeroData;
struct AppearanceHeroNameView {char unknown00[8];UnicodeString name;};
#include "../../Include/Common/Rva0040A3F9.h"
#include "../../Include/GameLogic/CreateAHeroManager.h"
extern CreateAHeroManager*TheCreateAHeroManager;
class GameWindowManager;extern GameWindowManager*TheWindowManager;
class Rva005B4F20WindowManagerView {public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot0A();
 virtual void slot0B();
 virtual void slot0C();
 virtual void slot0D();
 virtual void slot0E();
 virtual void slot0F();
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
 virtual void slot1A();
 virtual void slot1B();
 virtual void slot1C();
 virtual void slot1D();
 virtual void slot1E();
 virtual void slot1F();
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
 virtual void slot2A();
 virtual void slot2B();
 virtual void slot2C();
 virtual void slot2D();
 virtual void slot2E();
 virtual void slot2F();
 virtual GameWindow*focusedWindow();
};


#include "../../../Libraries/Source/Apt/AptCommandTarget.h"
typedef void(AptCommandTarget::*FunctorMethod)(const char*);
#include "../../Include/Common/DelegateDesc.h"
static __forceinline DelegateDesc MakeBinding(FunctorMethod method,AptCommandTarget*target){DelegateDesc d(method,target);return d;}
class Rva00579E47 {public:Rva00579E47(const DelegateDesc&);void*ptr;};
struct TargetRef00217D4C;void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
template<class T> class AptRef:public Rva00579E47 {public:AptRef(const DelegateDesc&d):Rva00579E47(d){}~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);}};
class AptCommandMap;class AptExternHandler;class AptScreenInitGadgets;
#include "../../../Libraries/Source/Apt/AptCommandMapAdder.h"
class AptExternHandlerAdder {public:void AddExternHandler(const AsciiString&,int,AptRef<AptExternHandler>);char storage[12];};
struct AppearanceOwner {char unknown00[0x21C];AptCommandMapAdder maps;AptExternHandlerAdder externs;char unknown234[0x414-0x234];Rva005B5C02Box *current414,*selected418;};
void _bfme_setAptScreenRef(const AsciiString&,AptRef<AptScreenInitGadgets>);
#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
extern BfmeAptWindowManager *g_bfmeAptWindowManager;


void _bfme_closeAptScreen(const AsciiString &name);
#include "../../Include/Common/Rva00223A94.h"
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

#include "../../Include/GameClient/IMEManagerClass.h"
extern IMEManager *TheIMEManager;

class Rva005B253F
{
public:
	Rva005B253F(void*p):m_04(p){}
	virtual ~Rva005B253F() {}
protected:
	void *m_04;
};

// WorldBuilder: AptCreateAHero::Appearance (WB VA 0x0157AE60 for ExternFunc,
// callgraph lead score 4); the command-map strings in the constructor below
// spell the same scope.
#include "../../Include/Common/AptCreateAHero.h"
class AptCreateAHero::Appearance : public Rva005B253F
{
public:
	Appearance(AppearanceOwner*);
 void AutoChangeBttn(const char*);
 void OnComplete(const char*);
 void OnPaintColor(const char*);
 void OnSkinColor(const char*);
 void OnHairColor(const char*);
 void IncreaseAttribute(const char*);
 void DecreaseAttribute(const char*);
 void NextAppearance(const char*);
 void PrevAppearance(const char*);
 void InitGadgets(const char*,unsigned,GameWindow*);
 void ExternFunc(int,char*,bool);

	virtual ~Appearance();
private:
	void *m_window08;
	char m_pad0C;
	bool m_imeActive;
};

AptCreateAHero::Appearance::~Appearance()
{
	_bfme_closeAptScreen(AsciiString("CahAppearance::InitGadgets"));
	{
		AsciiString name("CahAppearance::Portrait");
		reinterpret_cast<Rva00223A94 *>(g_bfmeAptWindowManager)->rva00223A94(&name);
	}
	if (m_imeActive)
		TheIMEManager->enable();
}

AptCreateAHero::Appearance::Appearance(AppearanceOwner*owner):Rva005B253F(owner),m_window08(0),m_pad0C(true),m_imeActive(false){
 {AsciiString name("AptCreateAHero::Appearance::AutoChangeBttn");owner->maps.AddCommandMap(name,MakeBinding(reinterpret_cast<FunctorMethod>(&AptCreateAHero::Appearance::AutoChangeBttn),(AptCommandTarget*)this));}
 {AsciiString name("AptCreateAHero::Appearance::OnComplete");owner->maps.AddCommandMap(name,MakeBinding(reinterpret_cast<FunctorMethod>(&AptCreateAHero::Appearance::OnComplete),(AptCommandTarget*)this));}
 {AsciiString name("AptCreateAHero::Appearance::NamePrompt");owner->maps.AddCommandMap(name,MakeBinding(reinterpret_cast<FunctorMethod>(&Rva005B4BDB::rva005B4AD9),(AptCommandTarget*)this));}
 {AsciiString name("AptCreateAHero::Appearance::OnPaintColor");owner->maps.AddCommandMap(name,MakeBinding(reinterpret_cast<FunctorMethod>(&AptCreateAHero::Appearance::OnPaintColor),(AptCommandTarget*)this));}
 {AsciiString name("AptCreateAHero::Appearance::OnSkinColor");owner->maps.AddCommandMap(name,MakeBinding(reinterpret_cast<FunctorMethod>(&AptCreateAHero::Appearance::OnSkinColor),(AptCommandTarget*)this));}
 {AsciiString name("AptCreateAHero::Appearance::OnHairColor");owner->maps.AddCommandMap(name,MakeBinding(reinterpret_cast<FunctorMethod>(&AptCreateAHero::Appearance::OnHairColor),(AptCommandTarget*)this));}
 {AsciiString name("AptCreateAHero::Appearance::IncreaseAttribute");owner->maps.AddCommandMap(name,MakeBinding(reinterpret_cast<FunctorMethod>(&AptCreateAHero::Appearance::IncreaseAttribute),(AptCommandTarget*)this));}
 {AsciiString name("AptCreateAHero::Appearance::DecreaseAttribute");owner->maps.AddCommandMap(name,MakeBinding(reinterpret_cast<FunctorMethod>(&AptCreateAHero::Appearance::DecreaseAttribute),(AptCommandTarget*)this));}
 {AsciiString name("AptCreateAHero::Appearance::NextAppearance");owner->maps.AddCommandMap(name,MakeBinding(reinterpret_cast<FunctorMethod>(&AptCreateAHero::Appearance::NextAppearance),(AptCommandTarget*)this));}
 {AsciiString name("AptCreateAHero::Appearance::PrevAppearance");owner->maps.AddCommandMap(name,MakeBinding(reinterpret_cast<FunctorMethod>(&AptCreateAHero::Appearance::PrevAppearance),(AptCommandTarget*)this));}
 {AsciiString name("CahAppearance::InitGadgets");_bfme_setAptScreenRef(name,MakeBinding(reinterpret_cast<FunctorMethod>(&AptCreateAHero::Appearance::InitGadgets),(AptCommandTarget*)this));}
 {AsciiString fallback(" ");AsciiString name("APT:HeroTypeDescription");g_bfmeAptWindowManager->rva00225375(name,fallback,false);}
 {AsciiString name("CahAppearance::ShowNamePrompt");owner->externs.AddExternHandler(name,0,MakeBinding(reinterpret_cast<FunctorMethod>(&AptCreateAHero::Appearance::ExternFunc),(AptCommandTarget*)this));}
 {AsciiString name("CahAppearance::HeroNameSet");owner->externs.AddExternHandler(name,1,MakeBinding(reinterpret_cast<FunctorMethod>(&AptCreateAHero::Appearance::ExternFunc),(AptCommandTarget*)this));}
 {AsciiString name("CahAppearance::PaintColor");owner->externs.AddExternHandler(name,4,MakeBinding(reinterpret_cast<FunctorMethod>(&AptCreateAHero::Appearance::ExternFunc),(AptCommandTarget*)this));}
 {AsciiString name("CahAppearance::SkinColor");owner->externs.AddExternHandler(name,3,MakeBinding(reinterpret_cast<FunctorMethod>(&AptCreateAHero::Appearance::ExternFunc),(AptCommandTarget*)this));}
 {AsciiString name("CahAppearance::HairColor");owner->externs.AddExternHandler(name,2,MakeBinding(reinterpret_cast<FunctorMethod>(&AptCreateAHero::Appearance::ExternFunc),(AptCommandTarget*)this));}
}

void AptCreateAHero::Appearance::OnHairColor(const char*path){AppearanceHeroView*hero=reinterpret_cast<AppearanceHeroView*>(static_cast<char*>(m_04)+0x27C);reinterpret_cast<Rva00406F12*>(hero)->rva00406F12(atoi(path));hero->refresh(false);}

void AptCreateAHero::Appearance::OnSkinColor(const char*path){AppearanceHeroView*hero=reinterpret_cast<AppearanceHeroView*>(static_cast<char*>(m_04)+0x27C);reinterpret_cast<Rva00406F27*>(hero)->rva00406F27(atoi(path));hero->refresh(false);}

void AptCreateAHero::Appearance::OnPaintColor(const char*path){AppearanceHeroView*hero=reinterpret_cast<AppearanceHeroView*>(static_cast<char*>(m_04)+0x27C);reinterpret_cast<Rva00406F3C*>(hero)->rva00406F3C(atoi(path));hero->refresh(false);}

void AptCreateAHero::Appearance::IncreaseAttribute(const char*path){int value=atoi(path);reinterpret_cast<AptMyHero*>(static_cast<char*>(m_04)+0x27C)->AdjustBling(0,value,1);}

void AptCreateAHero::Appearance::DecreaseAttribute(const char*path){int value=atoi(path);reinterpret_cast<AptMyHero*>(static_cast<char*>(m_04)+0x27C)->AdjustBling(0,value,-1);}

void AptCreateAHero::Appearance::NextAppearance(const char*path){int value=atoi(path);reinterpret_cast<AptMyHero*>(static_cast<char*>(m_04)+0x27C)->AdjustBling(1,value,1);}

void AptCreateAHero::Appearance::PrevAppearance(const char*path){int value=atoi(path);reinterpret_cast<AptMyHero*>(static_cast<char*>(m_04)+0x27C)->AdjustBling(1,value,-1);}

void AptCreateAHero::Appearance::AutoChangeBttn(const char*path) {
 if(strcmp(path,"AppearanceDefault")==0) {
  AptMyHero *hero=reinterpret_cast<AptMyHero*>(static_cast<char*>(m_04)+0x27C);
  hero->rva005B0FCD(1);reinterpret_cast<CreateAHeroHero*>(hero)->SetDefaultColors();reinterpret_cast<AppearanceHeroView*>(hero)->refresh14();
 } else if(strcmp(path,"AppearanceRandom")==0) reinterpret_cast<AptMyHero*>(static_cast<char*>(m_04)+0x27C)->rva005B0923(1);
 else if(strcmp(path,"AttribReset")==0) reinterpret_cast<AptMyHero*>(static_cast<char*>(m_04)+0x27C)->rva005B097F(0);
 else if(strcmp(path,"AttribRecommend")==0) reinterpret_cast<AptMyHero*>(static_cast<char*>(m_04)+0x27C)->rva005B0FCD(0);
}
void AptCreateAHero::Appearance::InitGadgets(const char*name,unsigned,GameWindow*window) {
 if(window&&strcmp(name,"CreateAHero::HeroName")==0){m_window08=window;reinterpret_cast<Rva005B4BDB*>(this)->rva005B4C3C();}
}
void AptCreateAHero::Appearance::OnComplete(const char*) {
 AppearanceOwner *owner=static_cast<AppearanceOwner*>(m_04);Rva005B5C02Box *selected=owner->selected418;
 if(owner->current414==selected){reinterpret_cast<Rva005B4BDB*>(this)->rva005B4BDB();selected->Run();}
}

void AptCreateAHero::Appearance::ExternFunc(int property,char*buffer,bool writing) {
 AppearanceHeroView*hero=reinterpret_cast<AppearanceHeroView*>(static_cast<char*>(m_04)+0x27C);
 bool result;
 switch(property){
 case 1:if(!writing){result=false;if(m_window08){UnicodeString name=GadgetTextEntryGetText(static_cast<GameWindow*>(m_window08));TheLanguageFilter->filterLine(name);name.trim();if(name.compare(GadgetTextEntryGetText(static_cast<GameWindow*>(m_window08)))!=0)GadgetTextEntrySetText(static_cast<GameWindow*>(m_window08),name);if(!name.isEmpty()){result=true;Rva0040A3F9*list=TheCreateAHeroManager->rva0021F797();int count=list->size();for(int i=0;i<=count;++i){CreateAHeroData*item=list->rva0040A32F(i);if(item&&name.compareNoCase(reinterpret_cast<AppearanceHeroNameView*>(item)->name)==0){result=false;break;}}}}strcpy(buffer,result?"1":"0");}break;
 case 0:if(!writing){result=m_window08&&GadgetTextEntryGetText(static_cast<GameWindow*>(m_window08)).compare(UnicodeString::TheEmptyString)==0&&m_window08!=reinterpret_cast<Rva005B4F20WindowManagerView*>(TheWindowManager)->focusedWindow();strcpy(buffer,result?"1":"0");}break;
 case 2:if(!writing)sprintf(buffer,"%u",hero->m_hairColor);break;
 case 3:if(!writing)sprintf(buffer,"%u",hero->m_skinColor);break;
 case 4:if(!writing)sprintf(buffer,"%u",hero->m_paintColor);break;
 }
}
