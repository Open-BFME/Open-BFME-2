// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /Oi-
// Target 0x0051569F/155 is a MainMenu field callback, not GameState code.
// The target constructor 0x00516211/2802 binds this exact member address at
// 0x00516A17, 0x00516A6F and 0x00516AC4 to MainMenuLevel (id 0),
// MainMenuContinueCampaign (id 1), and BlinkBattleSchoolOff (id 3).
// Adjacent AptMainMenu diagnostics establish the subsystem; neither they nor
// exact bytes establish the callback's original method/class spelling.
//
// BFME1 revision 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/GameClient/GUI/AptMainMenuConstructor.cpp, carries
// the same three labels and selector ids, but only declares bfmeProvide.
// That donor supplies registration context, not a recovered callback body.
//
// This nonvirtual, address-qualified view describes only the observed prefix.
// Native constructor initialization and this callback independently establish
// the byte at +0x281 and the four-byte string storage at +0x2A4; their wider
// containing class, bases, vtable and lifetime are deliberately unspecified.
// Only call on the native callback receiver; no construction/ownership is
// defined here. Target setting=true writes only id 0, while setting=false
// first clears the destination and supplies the three observed values.
//
// Existing target providers establish StringBase<char>::set at 0x55F5,
// wide text construction at 0x37E30, and the address-qualified save-existence
// method at 0x2DCCFB (by-value UnicodeString, with callee-owned destruction).
// TheGameState retains the existing global's decorated type; its cast claims
// only the helper ABI already proven by the native call. The copying call is
// the real msvcr71 _mbscpy import trampoline at 0x629176/BBA6D0, not an
// inference that the target used the ordinary strcpy implementation.
#include "ascii_string.h"
#include "unicode_string.h"
// The gen-import row uses a generic void() placeholder spelling. The PE
// import proves the msvcr71 _mbscpy identity; VC7/include/mbstring.h gives
// its actual cdecl signature below. No CRT symbol is overridden here.
void ji_00629176();
typedef unsigned char *(__cdecl *Rva00629176CopyABI)(unsigned char *, const unsigned char *);
class GameState;
extern GameState *TheGameState;
class Rva002DCCFB { public: bool rva002DCCFB(UnicodeString filename); };
class Rva0051569FMainMenuFields {
public:
    void access(int field, char *buffer, bool setting);
private:
    unsigned char opaque000[0x281];
    unsigned char flag281;
    unsigned char opaque282[0x22];
    AsciiString level2A4;
};
void Rva0051569FMainMenuFields::access(int field, char *buffer, bool setting)
{
    if (!setting)
        buffer[0] = 0;
    switch (field) {
    case 0:
        if (setting)
            ((StringBase<char> *)&level2A4)->set(buffer);
        else
            ((Rva00629176CopyABI)&ji_00629176)((unsigned char *)buffer, (const unsigned char *)level2A4.str());
        break;
    case 1:
        if (!setting)
            ((Rva00629176CopyABI)&ji_00629176)(
                (unsigned char *)buffer,
                (const unsigned char *)(((Rva002DCCFB *)TheGameState)->rva002DCCFB(
                    UnicodeString(L"00000000.sav")) ? "1" : "0"));
        break;
    case 3:
        if (!setting)
            ((Rva00629176CopyABI)&ji_00629176)((unsigned char *)buffer, (const unsigned char *)(flag281 ? "0" : "1"));
        break;
    }
}
