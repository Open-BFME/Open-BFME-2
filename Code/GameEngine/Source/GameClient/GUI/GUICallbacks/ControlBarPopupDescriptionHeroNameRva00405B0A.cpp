// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD
// ?rva00405B0A@@YA_NABVAsciiString@@PBVPlayer@@PBVThingTemplate@@PAVUnicodeString@@@Z
// Retail 0x00405B0A 86 bytes (cdecl helper). WorldBuilder twin 0x01077DB0
// sits in ControlBarPopupDescription.cpp beside OldSchoolHelpBoxContentSource::
// createContent (retail 0x00405E3D its only caller). When the template carries
// KindOf bit 190 (byte +0x11F mask 0x40) it asks TheCreateAHeroManager for the
// player's created hero (rowed GetHeroForPlayer 0x0021B5D6) and formats the
// label's string (TheGameText slot +0x40 fetchPtr by AsciiString) with the
// hero's +8 name through the rowed UnicodeString::format 0x006CB660.
#include "ascii_string.h"
#include "unicode_string.h"

class Player;
class ThingTemplate;

struct Rva00405B0AKindOf
{
    unsigned char m_pad000[0x108];
    unsigned char m_kindOf[0x1C];           // +0x108, bit 190 tested

    __forceinline bool isKindOf(int bit) const { return (m_kindOf[bit >> 3] & (1 << (bit & 7))) != 0; }
};

class CreateAHeroHero
{
public:
    unsigned char m_pad00[8];
    UnicodeString m_name;                   // +0x08
};

class CreateAHeroManager
{
public:
    const CreateAHeroHero *GetHeroForPlayer(const Player *player);
};
extern CreateAHeroManager *TheCreateAHeroManager;

class GameTextInterface
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15();
    virtual UnicodeString *fetchPtr(const AsciiString &label, bool *exists = 0);   // +0x40
};
extern GameTextInterface *TheGameText;

bool rva00405B0A(const AsciiString &label, const Player *player, const ThingTemplate *thing, UnicodeString *out)
{
    const CreateAHeroHero *hero = 0;
    if (reinterpret_cast<const Rva00405B0AKindOf *>(thing)->isKindOf(190))
        hero = TheCreateAHeroManager->GetHeroForPlayer(player);
    if (hero) {
        out->format(TheGameText->fetchPtr(label), hero->m_name.str());
        return true;
    }
    return false;
}
