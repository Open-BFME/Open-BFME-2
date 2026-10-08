// cl: /O1 /EHsc /MD /arch:SSE /G7 /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// BFME1 OnlineLoginRegister.cpp34f59164 supplies registration-tool behavior.
// BFME2 WB150B150 names OnBttnRegisterFESL and AptOnlineLogin.cpp.
// Native56E849..56E998 owns the guard, removes donor's eight UI toggles,
// uses ShellExecuteW and verifies the fetch slot at3C.
#include "ascii_string.h"
#include "unicode_string.h"
// stlport
#include <map>
#include <list>
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
class BfmeObjELB { public: void bfmeTailELB(bool); };
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
class UserPreferences { public: virtual ~UserPreferences(); virtual bool write(); };
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
class GameSpyLoginPreferences { public:
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
class AptOnlineLogin {
public:
    void OnBttnRegisterFESL(const char *);
    void rva00572632(const char *);
    void rva00572768(const char *);
    void rva00571B75();
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
    unsigned char padBC[9]; bool needsRefresh;
    unsigned char padC6[10]; bool closeLocale;
    unsigned char padD1[3]; int locale;
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
            g_bfmeObjELB->bfmeTailELB(false);
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
            g_bfmeObjELB->bfmeTailELB(true);
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
