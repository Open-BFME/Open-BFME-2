// cl: /O1 /EHsc /MD /arch:SSE /G7 /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// BFME1 OnlineLoginRegister.cpp34f59164 supplies registration-tool behavior.
// BFME2 WB150B150 names OnBttnRegisterFESL and AptOnlineLogin.cpp.
// Native56E849..56E998 owns the guard, removes donor's eight UI toggles,
// uses ShellExecuteW and verifies the fetch slot at3C.
#include "ascii_string.h"
#include "unicode_string.h"
// stlport
// Native string cleanup calls the existing STL allocator free, not CRT free.
#include <stdlib.h>
namespace _STL { void __cdecl free(void *block); }
#define free _STL::free
#include <map>
#include <list>
#include <string>
#undef free
extern template _STL::_List_base<AsciiString,_STL::allocator<AsciiString> >::~_List_base();
bool operator<(const UnicodeString &,const UnicodeString &);
namespace _STL { template<> struct less<UnicodeString> {
    bool operator()(const UnicodeString &a,const UnicodeString &b)const { return a<b; }
}; }
typedef _STL::pair<const UnicodeString,int> CountryPair;
typedef _STL::map<UnicodeString,int> CountryLocaleMap;
typedef _STL::_Rb_tree<UnicodeString,CountryPair,_STL::_Select1st<CountryPair>,_STL::less<UnicodeString>,_STL::allocator<CountryPair> > CountryTree;
// Use the reconciled /EHs provider's native 56-byte destructor. This /EHsc
// callback unit must not emit a different definition of that same member.
extern template CountryTree::~_Rb_tree();
extern template CountryLocaleMap::map();
extern template CountryTree::iterator CountryTree::insert_unique(CountryTree::iterator,const CountryPair &);
extern template _STL::pair<CountryTree::iterator,bool> CountryTree::insert_unique(const CountryPair &);
extern "C" __declspec(dllimport) void *__stdcall ShellExecuteW(void *,const unsigned short *,const unsigned short *,const unsigned short *,const unsigned short *,int);
bool GetStringFromRegistry(AsciiString,AsciiString,AsciiString &);
void GSMessageBoxOk(UnicodeString,UnicodeString,void (*)());
void bfmeMinimizeCurrentThreadWindow();
class BfmeObjELB;
extern BfmeObjELB *g_bfmeObjELB;
class GameTextInterface {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14();
    virtual UnicodeString fetch(const char *,bool *exists=0);
};
extern GameTextInterface *TheGameText;
class UserPreferences { public: virtual ~UserPreferences();
    virtual bool load(const AsciiString &); virtual bool load(const UnicodeString &);
    virtual bool write(); };
class GameSpyMiscPreferences: public UserPreferences {
public: GameSpyMiscPreferences(); virtual ~GameSpyMiscPreferences();
    int rva00559782();
    unsigned char rest[0x10];
};
class Rva00222A8BTarget { public:
    int invoke(void *,const char *,int,const char *,void *,void *,void *,void *);
};
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva0056DCBF { public: void rva0056DCBF(bool); };
struct AptOnlineLoginOwner { unsigned char pad[0x274]; void *movie; };
class GameWindow;
// The country callback reads only this ledger-owned first word.
extern int g_00DB9198;
AsciiString GetRegistryLanguage();
int GadgetListBoxAddEntryText(GameWindow *,UnicodeString,int,int,int,bool);
void Rva00325388Send(GameWindow *,int,int,int);
void GadgetListBoxSetSelected(GameWindow *,int);
void GadgetCheckBoxSetChecked(GameWindow *,bool);
void GadgetTextEntrySetText(GameWindow *,UnicodeString);
class GameSpyLoginPreferences: public UserPreferences { public:
    virtual bool write();
    void deleteNick(const AsciiString &,const AsciiString &);
    void rva005CA53E(const AsciiString &);
    void rva005CACDE(AsciiString,AsciiString,AsciiString,AsciiString);
    AsciiString rva005C9FC4();
    _STL::list<AsciiString> rva005CA07D();
    AsciiString getPasswordForEmail(AsciiString);
    const _STL::list<AsciiString> &rva005CA201(const AsciiString &);
};
void GadgetComboBoxReset(GameWindow *);
void GadgetComboBoxSetIsEditable(GameWindow *,bool);
int GadgetComboBoxAddEntry(GameWindow *,UnicodeString,int);
void GadgetComboBoxSetSelectedPos(GameWindow *,int,bool);
void GadgetComboBoxSetText(GameWindow *,UnicodeString);
static bool g_cachedLoginPopulationBusy;
struct SkirmishFindNode { unsigned char pad[0x14]; AsciiString value; };
class SkirmishFindMap { public:
    SkirmishFindNode *find(const AsciiString &) const throw();
    SkirmishFindNode *end() const { return head; }
    SkirmishFindNode *head; unsigned char remainder[8];
};

class GameSpyConfigInterface { public:
    virtual ~GameSpyConfigInterface();
    virtual _STL::list<AsciiString> getPingServers()=0;
    virtual int getNumPingRepetitions()=0;
    virtual int getPingTimeoutInMs()=0;
};
extern GameSpyConfigInterface *TheGameSpyConfig;
class PingRequest { public: _STL::string hostname;int repetitions,timeout; };
class PingerInterface { public:
    virtual ~PingerInterface();
    virtual void startThreads()=0;
    virtual void endThreads()=0;
    virtual bool areThreadsRunning()=0;
    virtual void addRequest(const PingRequest &)=0;
    virtual void slot14();virtual void slot18();virtual void slot1C();
    virtual bool arePingsInProgress();virtual void slot24();virtual void slot28();
    virtual AsciiString getPingString(int);
};
extern PingerInterface *ThePinger;
struct LoginPingStringData { int refs;unsigned short length,capacity;char text[1]; };


extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
extern "C" unsigned char *__cdecl _mbscpy(unsigned char *,const unsigned char *);
class Rva0056EBA1 { public: UnicodeString rva0056EB15(); };
class Rva0056EA91 { public: UnicodeString rva0056EA91(); };
class Rva0056EBD0 { public: UnicodeString rva0056EBD0(); };
// Donor request fields retained only where retail accesses them. Native
// proves this request's prefix and 0x2B8 stack extent; remaining bytes opaque.
struct LoginSubmitRequest {
 int type;
 char nickname[31],email[51],password[31];bool hasFirewall;
 unsigned char opaque[0x200];char registryKey[65];unsigned char tail;
};
class GameSpyBuddyMessageQueueInterface { public:
 virtual void slot00();virtual void slot04();virtual void slot08();
 virtual void slot0C();virtual void slot10();virtual void slot14();
 virtual void addRequest(const LoginSubmitRequest &);
};
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;

typedef _STL::map<AsciiString,AsciiString> LoginPreferenceMap;
extern template AsciiString &LoginPreferenceMap::operator[](const AsciiString &);
class OptionPreferences { public:
    OptionPreferences();virtual ~OptionPreferences();
    LoginPreferenceMap settings;AsciiString filename;
};
class PSPlayerAllStats { public:
    PSPlayerAllStats(const PSPlayerAllStats &);~PSPlayerAllStats();
    void setID(int);
    // 0x548 native extent independently corroborated by the recovered
    // PersistentStorageThread provider. No fields reconstructed here.
    unsigned opaque[0x548/4];
};
PSPlayerAllStats rva00556DFF();
void Rva003B3371Call(int);
bool GadgetCheckBoxIsChecked(GameWindow *);
class AptOnlineShell { public:void LoadChildScreen(const char *); };
class FirewallHelperClass { public:
    virtual ~FirewallHelperClass();
    bool behaviorDetectionUpdate();void writeFirewallBehavior();
    void flagNeedToRefresh(bool);
};
// Existing owning unit models the native slot0 allocation-release result.
struct Rva00A063B0Obj { virtual void *Unknown00(int); };
extern Rva00A063B0Obj *g_a063b0;

class GameSpyInfoInterface { public:
 virtual void slot00();
 virtual void slot04();
 virtual void clearGroupRoomList();
 virtual void slot0C();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1C();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
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
 virtual void slot78();
 virtual int getLocalProfileID();
 virtual void slot80();

 virtual void setLocalEmail(AsciiString);
 virtual void slot88();
 virtual void setLocalPassword(AsciiString);
 virtual void setLocalBaseName(AsciiString);
 virtual void slot94();virtual void setCachedLocalPlayerStats(PSPlayerAllStats);
 virtual void slot9C();
 virtual void slotA0();
 virtual void slotA4();
 virtual void slotA8();
 virtual void slotAC();
 virtual void slotB0();
 virtual void slotB4();
 virtual void slotB8();
 virtual void slotBC();
 virtual void slotC0();
 virtual void slotC4();
 virtual void slotC8();
 virtual void slotCC();
 virtual void slotD0();
 virtual void slotD4();
 virtual void slotD8();
 virtual void slotDC();
 virtual void slotE0();
 virtual void slotE4();
 virtual void slotE8();
 virtual void slotEC();
 virtual void slotF0();
 virtual void slotF4();
 virtual void slotF8();
 virtual void slotFC();
 virtual void slot100();
 virtual void slot104();
 virtual void slot108();
 virtual void slot10C();
 virtual void slot110();
 virtual void slot114();
 virtual void setPingString(const AsciiString &);
};
extern GameSpyInfoInterface *TheGameSpyInfo;

class AptOnlineLogin {
public:
    void OnBttnRegisterFESL(const char *);
    void OnAccountDeleted(bool);
    void rva00572632(const char *);
    void rva00572768(const char *);
    void rva00571B75();
    void rva00570C64();
    void rva00570D36();
    void rva00571129();
    void rva0057179D(bool);
    void rva005700A0();
    void rva005709D1(AsciiString &,AsciiString &);
    bool rva005706D4();
    bool rva0056EC54(const UnicodeString &,bool);
    void rva0056FEA8();
private:
    unsigned char pad00[0x58]; AptOnlineLoginOwner *owner;
    unsigned char pad5c[8]; SkirmishFindMap loginPreferences;
    unsigned char pad70[0xA4-0x70];
    GameWindow *email;
    GameWindow *nickname;
    GameWindow *password;
    GameWindow *remember;
    unsigned char padB4[4]; GameWindow *m_countryList;
    unsigned char padBC[8]; bool loggedIn; bool needsRefresh;
    unsigned char padC6[2]; unsigned long loginStartTime;
    unsigned char padCC[4]; bool closeLocale;
    unsigned char padD1[3]; int locale;
    AsciiString m_deleteNickname;
};
void AptOnlineLogin::OnBttnRegisterFESL(const char *)
{
    if(g_bfmeObjELB) {
        AsciiString path("");
        if(GetStringFromRegistry("","InstallPath",path) && !path.isEmpty()) {
            path.concat("\\SUPPORT\\EREG.EXE");
            int result=(int)ShellExecuteW(0,L"open",UnicodeString(path).str(),L"",0,5);
            if(result<=31)
                GSMessageBoxOk(TheGameText->fetch("GUI:GSErrorTitle"),TheGameText->fetch("GUI:EREGError"),0);
            else
                bfmeMinimizeCurrentThreadWindow();
        } else {
            GSMessageBoxOk(TheGameText->fetch("GUI:GSErrorTitle"),TheGameText->fetch("GUI:EREGError"),0);
        }
    }
}

// Native 56EC54..56ECAE verifies password AC and checkbox B0. The
// purpose follows BFME1 34f59164 OnlineLoginSetText.cpp. Native retains
// the checkbox pointer across text.isEmpty() rather than loading it again.
bool AptOnlineLogin::rva0056EC54(const UnicodeString &text,bool updateEnabled)
{
    bool textWasSet=false;
    if(password) {
        GameWindow *dependent=remember;
        if(dependent && updateEnabled)
            GadgetCheckBoxSetChecked(dependent,!text.isEmpty());
        GadgetTextEntrySetText(password,text);
        textWasSet=true;
    }
    return textWasSet;
}

// Registered as AptOnline::Login::Login in native 572885. BFME1 donor
// 34f59164 OnlineLoginLogin.cpp supplies purpose and control flow;
// native 572632..572766 verifies fields 58/D0/D4 and all callees.
// The target callback's method name remains address-derived.
void AptOnlineLogin::rva00572632(const char *)
{
    if(g_bfmeObjELB) {
        { void *movie=owner->movie;
          ((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(movie,"CallChild",1,"DisableButtonDeleteNickname",0,0,0,0); }
        { void *movie=owner->movie;
          ((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(movie,"CallChild",1,"DisableButtonCreate",0,0,0,0); }
        { void *movie=owner->movie;
          ((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(movie,"CallChild",1,"DisableButtonLogin",0,0,0,0); }
        { void *movie=owner->movie;
          ((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(movie,"CallChild",1,"DisableButtonServiceTerms",0,0,0,0); }
        GameSpyMiscPreferences preferences;
        if(preferences.rva00559782()>=1 && preferences.rva00559782()<=0x25) {
            locale=preferences.rva00559782();
            ((AptOnlineLogin *)g_bfmeObjELB)->rva0057179D(false);
            return;
        }
        closeLocale=false;
        void *movie=owner->movie;
        ((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(movie,"CallChild",1,"DoOpenLocale",0,0,0,0);
        ((Rva0056DCBF *)this)->rva0056DCBF(false);
    }
}

// Native 56FEA8..5700A0: country list B8; localized Unicode keys and
// locale values 1..37. BFME1 34f59164 OnlineLoginPopulateCountryList.cpp
// supplies purpose; target verifies node fields, ordering and selection.
void AptOnlineLogin::rva0056FEA8()
{
	AsciiString label;
	label.format( "WOL:Locale%2.2d", 1 );
	int row = GadgetListBoxAddEntryText( m_countryList,
		TheGameText->fetch( label.str() ), g_00DB9198, -1, -1, true );
	Rva00325388Send( m_countryList, 1, row, 0 );

	CountryLocaleMap locales;
	for( int i = 2; i <= 0x25; ++i )
	{
		AsciiString localeLabel;
		localeLabel.format( "WOL:Locale%2.2d", i );
		locales[ TheGameText->fetch( localeLabel.str() ) ] = (int)i;
	}

	UnicodeString language;
	language.translate( GetRegistryLanguage() );
	if( language.getLength() == 0 || language.compareNoCase( (const unsigned short *)L"english" ) == 0 )
		language = (const unsigned short *)L"United States";

	int selectedRow = 0;
	for( CountryLocaleMap::iterator it = locales.begin(); it != locales.end(); ++it )
	{
		row = GadgetListBoxAddEntryText( m_countryList, it->first,
			g_00DB9198, -1, -1, true );
		Rva00325388Send( m_countryList, it->second, row, 0 );
		if( language.compareNoCase( it->first ) == 0 )
			selectedRow = row;
	}

	GadgetListBoxSetSelected( m_countryList, selectedRow );
}

// BFME1 34f59164 OnlineLoginRva005536F0 supplies this sibling state flow.
// Native 572768..572871 verifies the true tail argument and D0 byte;
// no callback registration or original method spelling is asserted.
void AptOnlineLogin::rva00572768(const char *)
{
    if(g_bfmeObjELB) {
        { void *movie=owner->movie;
          ((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(movie,"CallChild",1,"DisableButtonCreate",0,0,0,0); }
        { void *movie=owner->movie;
          ((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(movie,"CallChild",1,"DisableButtonLogin",0,0,0,0); }
        { void *movie=owner->movie;
          ((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(movie,"CallChild",1,"DisableButtonServiceTerms",0,0,0,0); }
        GameSpyMiscPreferences preferences;
        if(preferences.rva00559782()>=1 && preferences.rva00559782()<=0x25) {
            ((AptOnlineLogin *)g_bfmeObjELB)->rva0057179D(true);
            return;
        }
        closeLocale=true;
        void *movie=owner->movie;
        ((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(movie,"CallChild",1,"DoOpenLocale",0,0,0,0);
        ((Rva0056DCBF *)this)->rva0056DCBF(false);
    }
}


// BFME1 34f59164 BfmeAptScreenOnlineLoginRefreshState.cpp supplies purpose.
// Native 571B75..571C60 uses the added login-preferences last-email getter
// at this+60 instead of the donor's map/registry fallback. Base map+64;
// lastName node value+14; cached-login helper receives two AsciiString refs.
void AptOnlineLogin::rva00571B75()
{
    if(!password || !email || !nickname || !remember) return;
    GadgetTextEntrySetText(password,UnicodeString::TheEmptyString);
    AsciiString lastEmail=((GameSpyLoginPreferences *)((char *)this+0x60))->rva005C9FC4();
    AsciiString lastName;
    SkirmishFindNode *it=loginPreferences.find(AsciiString("lastName"));
    if(it!=loginPreferences.end()) {
        const AsciiString *nameValue=&it->value;
        lastName=*nameValue;
    }
    rva005709D1(lastEmail,lastName);
    needsRefresh=false;
}

// BFME1 34f59164 OnlineLoginPopulateCachedLogins0054FF80 supplies behavior.
// Native 5709D1..570C64 proves prefs60, controlsA4/A8/AC, two refs/RET8.
// BFME2 uses a borrowed nickname list and its shared out-of-line cleanup.
void AptOnlineLogin::rva005709D1(AsciiString &lastEmail,AsciiString &lastName)
{
    if(g_cachedLoginPopulationBusy) return;
    g_cachedLoginPopulationBusy=true;
    GadgetComboBoxReset(email);
    GadgetComboBoxSetIsEditable(email,true);
    GadgetComboBoxReset(nickname);
    GadgetComboBoxSetIsEditable(nickname,true);
    GadgetTextEntrySetText(password,UnicodeString::TheEmptyString);
    GameSpyLoginPreferences *preferences=(GameSpyLoginPreferences *)((char *)this+0x60);
    _STL::list<AsciiString> cachedEmails=preferences->rva005CA07D();
    int selectedPosition=-1;
    for(_STL::list<AsciiString>::iterator it=cachedEmails.begin();it!=cachedEmails.end();++it) {
        UnicodeString translated;
        translated.translate(*it);
        int position=GadgetComboBoxAddEntry(email,translated,g_00DB9198);
        if(((const StringBase<char> *)&*it)->compare(*(const StringBase<char> *)&lastEmail)==0)
            selectedPosition=position;
    }
    if(selectedPosition>=0) {
        GadgetComboBoxSetSelectedPos(email,selectedPosition,false);
        if(lastEmail.isEmpty()) GadgetComboBoxSetText(email,UnicodeString::TheEmptyString);
        UnicodeString passwordText;
        passwordText.translate(preferences->getPasswordForEmail(lastEmail));
        rva0056EC54(passwordText,true);
    } else {
        UnicodeString translated;
        translated.translate(lastEmail);
        GadgetComboBoxSetText(email,translated);
    }
    _STL::list<AsciiString> cachedNames=preferences->rva005CA201(lastEmail);
    selectedPosition=-1;
    for(_STL::list<AsciiString>::iterator it=cachedNames.begin();it!=cachedNames.end();++it) {
        UnicodeString translated;
        translated.translate(*it);
        int position=GadgetComboBoxAddEntry(nickname,translated,g_00DB9198);
        if(((const StringBase<char> *)&*it)->compare(*(const StringBase<char> *)&lastName)==0 || selectedPosition<0)
            selectedPosition=position;
    }
    if(selectedPosition>=0) GadgetComboBoxSetSelectedPos(nickname,selectedPosition,false);
    g_cachedLoginPopulationBusy=false;
    rva005706D4();
}

// ZH WOLLoginMenu.cpp startPings supplies the semantic source. BFME1
// 34f59164 PingThread.h retains the 20-byte request and virtual interfaces.
// Native570C64..570D36 independently proves config slots4/C/8 and pinger10.
// Original target method spelling is unknown.
void AptOnlineLogin::rva00570C64()
{
    _STL::list<AsciiString> servers=TheGameSpyConfig->getPingServers();
    int timeout=TheGameSpyConfig->getPingTimeoutInMs();
    int repetitions=TheGameSpyConfig->getNumPingRepetitions();
    for(_STL::list<AsciiString>::iterator it=servers.begin();it!=servers.end();++it) {
        AsciiString server=*it;
        PingRequest request;
        const LoginPingStringData *data=*(const LoginPingStringData *const *)&server;
        request.hostname=data?data->text:"";
        request.repetitions=repetitions;
        request.timeout=timeout;
        ThePinger->addRequest(request);
    }
}

// WB150F770 names OnAccountDeleted and m_deleteNickname at D8.
// Native571593..571657 proves prefs60 and its write slot0C; the
// trimmed-email getter and cached-login refresh use their ledger owners.
void AptOnlineLogin::OnAccountDeleted(bool success)
{
    if (m_deleteNickname.isEmpty()) return;
    if (success) {
        AsciiString emailText;
        emailText.translate(((Rva0056EBA1 *)this)->rva0056EB15());
        GameSpyLoginPreferences *preferences=(GameSpyLoginPreferences *)((char *)this+0x60);
        preferences->deleteNick(emailText,m_deleteNickname);
        preferences->write();
        AsciiString emptyName(AsciiString::TheEmptyString);
        rva005709D1(emailText,emptyName);
    }
    m_deleteNickname=AsciiString::TheEmptyString;
}
// BFME1 34f59164 OnlineLoginSubmit00551620.cpp supplies login-request behavior.
// Native570D36..571129 independently proves all target offsets and slots;
// BFME2 removes the donor's UI disables and nickname persistence here.
// Original method spelling and the untouched request fields remain unknown.
void AptOnlineLogin::rva00570D36() {
 AsciiString login,password,email;
 email.translate(((Rva0056EBA1 *)this)->rva0056EB15());
 login.translate(((Rva0056EA91 *)this)->rva0056EA91());
 password.translate(((Rva0056EBD0 *)this)->rva0056EBD0());
 if(!email.isEmpty() && !login.isEmpty() && !password.isEmpty()) {
  loginStartTime=timeGetTime();
  LoginSubmitRequest req;
  req.type=4;
  _mbscpy((unsigned char *)req.nickname,(const unsigned char *)((const StringBase<char> *)&login)->str());
  _mbscpy((unsigned char *)req.email,(const unsigned char *)((const StringBase<char> *)&email)->str());
  _mbscpy((unsigned char *)req.password,(const unsigned char *)((const StringBase<char> *)&password)->str());
  req.hasFirewall=true;
  AsciiString registryValue;
  GetStringFromRegistry("\\ergc","",registryValue);
  _mbscpy((unsigned char *)req.registryKey,(const unsigned char *)((const StringBase<char> *)&registryValue)->str());
  TheGameSpyInfo->setLocalBaseName(login);
  TheGameSpyInfo->setLocalEmail(email);
  TheGameSpyInfo->setLocalPassword(password);
  TheGameSpyBuddyMessageQueue->addRequest(req);
  ((Rva0056DCBF *)this)->rva0056DCBF(false);
  rva00570C64();
 } else {
  if(email.isEmpty() && login.isEmpty() && password.isEmpty()) GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoAll"),0);
  else if(email.isEmpty() && login.isEmpty()) GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoEmailNickname"),0);
  else if(email.isEmpty() && password.isEmpty()) GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoEmailPassword"),0);
  else if(login.isEmpty() && password.isEmpty()) GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoNicknamePassword"),0);
  else if(email.isEmpty()) GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoEmail"),0);
  else if(password.isEmpty()) GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoPassword"),0);
  else if(login.isEmpty()) GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoNickname"),0);
  else GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoAll"),0);
 }
}
// BFME1 34f59164 OnlineLoginSubmit00551620.cpp primary semantic donor.
// Native571129..571593 owns this separate request path: disables three
// controls, stores nickname at D8 and sets the byte at request+2B7.
// The sibling570D36 differs; its exactness is not evidence for this body.
void AptOnlineLogin::rva00571129() {
 AsciiString login,password,email;
 email.translate(((Rva0056EBA1 *)this)->rva0056EB15());
 login.translate(((Rva0056EA91 *)this)->rva0056EA91());
 password.translate(((Rva0056EBD0 *)this)->rva0056EBD0());

 { void *movie=owner->movie;
   ((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(movie,"CallChild",1,"DisableButtonDeleteNickname",0,0,0,0); }
 { void *movie=owner->movie;
   ((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(movie,"CallChild",1,"DisableButtonLogin",0,0,0,0); }
 { void *movie=owner->movie;
   ((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(movie,"CallChild",1,"DisableButtonServiceTerms",0,0,0,0); }
 if(!email.isEmpty() && !login.isEmpty() && !password.isEmpty()) {
  m_deleteNickname=login;
  loginStartTime=timeGetTime();
  LoginSubmitRequest req;
  req.type=0;
  req.tail=1;
  _mbscpy((unsigned char *)req.nickname,(const unsigned char *)((const StringBase<char> *)&login)->str());
  _mbscpy((unsigned char *)req.email,(const unsigned char *)((const StringBase<char> *)&email)->str());
  _mbscpy((unsigned char *)req.password,(const unsigned char *)((const StringBase<char> *)&password)->str());
  req.hasFirewall=true;
  AsciiString registryValue;
  GetStringFromRegistry("\\ergc","",registryValue);
  _mbscpy((unsigned char *)req.registryKey,(const unsigned char *)((const StringBase<char> *)&registryValue)->str());
  TheGameSpyInfo->setLocalBaseName(login);
  TheGameSpyInfo->setLocalEmail(email);
  TheGameSpyInfo->setLocalPassword(password);
  TheGameSpyBuddyMessageQueue->addRequest(req);
  ((Rva0056DCBF *)this)->rva0056DCBF(false);
  rva00570C64();
 } else {
  if(email.isEmpty() && login.isEmpty() && password.isEmpty()) GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoAll"),0);
  else if(email.isEmpty() && login.isEmpty()) GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoEmailNickname"),0);
  else if(email.isEmpty() && password.isEmpty()) GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoEmailPassword"),0);
  else if(login.isEmpty() && password.isEmpty()) GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoNicknamePassword"),0);
  else if(email.isEmpty()) GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoEmail"),0);
  else if(password.isEmpty()) GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoPassword"),0);
  else if(login.isEmpty()) GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoNickname"),0);
  else GSMessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:GSNoLoginInfoAll"),0);
 }
}
void b_00042a50();
// Native57179D references this callback at56DCB2. Complete five-byte jump
// ends at independent56DCB7. Preserve the distinct callable entry point.
void Rva0056DCB2() { b_00042a50(); }

// Native57179D registers571657; call44BA2A then singleton-gated tail to571129.
// All21B terminate at57166C independentEHbody. Original callback name unknown.
void Rva00571657() { b_00042a50(); if(g_bfmeObjELB) ((AptOnlineLogin *)g_bfmeObjELB)->rva00571129(); }

void MessageBoxOkCancel(UnicodeString,UnicodeString,void (*)(),void (*)());

// BFME1 34f59164 OnlineLoginRva00552C40 supplies this boolean login path.
// Native57179D..571B75 independently verifies byte argument, delete-dialog
// callback entries, request layout and UI calls. Original spelling unknown.
void AptOnlineLogin::rva0057179D(bool argument) {
 if(argument) {
  MessageBoxOkCancel(UnicodeString(L""),TheGameText->fetch("GUI:SureDeleteNickname"),Rva00571657,Rva0056DCB2);
  return;
 }
 AsciiString login,password;
 AsciiString email(((Rva0056EBA1 *)this)->rva0056EB15());
 login.translate(((Rva0056EA91 *)this)->rva0056EA91());
 password.translate(((Rva0056EBD0 *)this)->rva0056EBD0());
 if(!email.isEmpty() && !login.isEmpty() && !password.isEmpty()) {
  loginStartTime=timeGetTime();
  LoginSubmitRequest req;
  req.type=0;
  _mbscpy((unsigned char *)req.nickname,(const unsigned char *)((const StringBase<char> *)&login)->str());
  _mbscpy((unsigned char *)req.email,(const unsigned char *)((const StringBase<char> *)&email)->str());
  _mbscpy((unsigned char *)req.password,(const unsigned char *)((const StringBase<char> *)&password)->str());
  req.hasFirewall=true;
  AsciiString registryValue;
  GetStringFromRegistry("\\ergc","",registryValue);
  _mbscpy((unsigned char *)req.registryKey,(const unsigned char *)((const StringBase<char> *)&registryValue)->str());
  TheGameSpyInfo->setLocalBaseName(login);
  TheGameSpyInfo->setLocalEmail(email);
  TheGameSpyInfo->setLocalPassword(password);
  req.tail=false;
  TheGameSpyBuddyMessageQueue->addRequest(req);
  ((Rva0056DCBF *)this)->rva0056DCBF(false);
  { void *movie=owner->movie; ((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(movie,"CallChild",1,"DisableButtonLogin",0,0,0,0); }
  { void *movie=owner->movie; ((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(movie,"CallChild",1,"DisableButtonDeleteNickname",0,0,0,0); }
  rva00570C64();
 } else {
  const char *message;
  if(email.isEmpty() && login.isEmpty() && password.isEmpty()) message="GUI:GSNoLoginInfoAll";
  else if(email.isEmpty() && login.isEmpty()) message="GUI:GSNoLoginInfoEmailNickname";
  else if(email.isEmpty() && password.isEmpty()) message="GUI:GSNoLoginInfoEmailPassword";
  else if(login.isEmpty() && password.isEmpty()) message="GUI:GSNoLoginInfoNicknamePassword";
  else if(email.isEmpty()) message="GUI:GSNoLoginInfoEmail";
  else if(password.isEmpty()) message="GUI:GSNoLoginInfoPassword";
  else if(login.isEmpty()) message="GUI:GSNoLoginInfoNickname";
  else message="GUI:GSNoLoginInfoAll";
  GSMessageBoxOk(TheGameText->fetch("GUI:GSErrorTitle"),TheGameText->fetch(message),0);
 }
}

// BFME1 34f59164 OnlineLoginCheckLogin.cpp semantic donor. Native700A0
// adds the firewall completion phase and uses PSPlayerAllStats (0x548).
// Complete native evidence supplies offsets and virtual slots independently.
void AptOnlineLogin::rva005700A0()
{
    if(g_a063b0) {
        if(!((FirewallHelperClass *)g_a063b0)->behaviorDetectionUpdate()) return;
        ((FirewallHelperClass *)g_a063b0)->writeFirewallBehavior();
        ((FirewallHelperClass *)g_a063b0)->flagNeedToRefresh(false);
        void *allocation=g_a063b0?g_a063b0->Unknown00(0):0;
        operator delete(allocation);
        g_a063b0=0;
    }
    if(loggedIn && ThePinger && !ThePinger->arePingsInProgress()) {
        OptionPreferences preferences;
        preferences.settings["HasGotOnline"]="yes";
        ((UserPreferences *)&preferences)->UserPreferences::write();
        AsciiString ping=ThePinger->getPingString(TheGameSpyConfig->getPingTimeoutInMs());
        TheGameSpyInfo->setPingString(ping);
        loggedIn=false;loginStartTime=0;
        TheGameSpyInfo->clearGroupRoomList();
        Rva003B3371Call(0x12);
        PSPlayerAllStats stats=rva00556DFF();
        stats.setID(TheGameSpyInfo->getLocalProfileID());
        TheGameSpyInfo->setCachedLocalPlayerStats(stats);
        AsciiString email;
        email.translate(((Rva0056EBA1 *)this)->rva0056EB15());
        AsciiString login,password;
        login.translate(((Rva0056EA91 *)this)->rva0056EA91());
        if(remember && GadgetCheckBoxIsChecked(remember))
            password.translate(((Rva0056EBD0 *)this)->rva0056EBD0());
        else password.clear();
        (*(LoginPreferenceMap *)&loginPreferences)["lastName"]=login;
        GameSpyLoginPreferences *preferences2=(GameSpyLoginPreferences *)((char *)this+0x60);
        preferences2->rva005CA53E(email);
        (*(LoginPreferenceMap *)&loginPreferences)["useProfiles"]="yes";
        AsciiString date("01/01/1970");
        preferences2->rva005CACDE(email,login,password,date);
        preferences2->write();
        ((AptOnlineShell *)owner)->LoadChildScreen("OnlineHome");
    }
}
