// cl: /O1 /EHsc /MD /arch:SSE /G7 /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// BFME1 OnlineLoginRegister.cpp34f59164 supplies registration-tool behavior.
// BFME2 WB150B150 names OnBttnRegisterFESL and AptOnlineLogin.cpp.
// Native56E849..56E998 owns the guard, removes donor's eight UI toggles,
// uses ShellExecuteW and verifies the fetch slot at3C.
#include "ascii_string.h"
#include "unicode_string.h"
// stlport
#include <map>
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
class AptOnlineLogin {
public:
    void OnBttnRegisterFESL(const char *);
    void rva00572632(const char *);
    bool rva0056EC54(const UnicodeString &,bool);
    void rva0056FEA8();
private:
    unsigned char pad00[0x58]; AptOnlineLoginOwner *owner;
    unsigned char pad5c[0xA4-0x5C];
    GameWindow *email;
    GameWindow *nickname;
    GameWindow *password;
    GameWindow *remember;
    unsigned char padB4[4]; GameWindow *m_countryList;
    unsigned char padBC[0xD0-0xBC]; bool closeLocale;
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
