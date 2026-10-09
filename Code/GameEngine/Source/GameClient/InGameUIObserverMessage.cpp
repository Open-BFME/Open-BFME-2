// cl: /O1 /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ShowStuckAsObserverInStrategicRTSGameMessage, retail 0x0029DF1A, 171B.
// WorldBuilder 0x00DC5210 supplies the name, InGameUI.cpp lines 9047-9051,
// Generic lookup and notification purpose. Retail proves GameText slot 0x3C,
// the null-preserving UI +0x10 interface adjustment and the existing record
// getter, destructor and three-argument Open forwarder. The record keeps its
// established address name; its fields and the full UI layout are not claimed.
#include "ascii_string.h"
#include "unicode_string.h"

class Rva002217EA
{
public:
    ~Rva002217EA();
    void rva0010670B(const class Image *image);
private:
    unsigned char m_data[0x14];
};

class InGameNotificationType
{
public:
    Rva002217EA rva00221ABB() const;
};
InGameNotificationType *FindInGameNotificationType(const AsciiString &name);

class GameTextInterface
{
public:
#define TEXT_SLOT(n) virtual void slot##n();
    TEXT_SLOT(0) TEXT_SLOT(1) TEXT_SLOT(2) TEXT_SLOT(3) TEXT_SLOT(4)
    TEXT_SLOT(5) TEXT_SLOT(6) TEXT_SLOT(7) TEXT_SLOT(8) TEXT_SLOT(9)
    TEXT_SLOT(10) TEXT_SLOT(11) TEXT_SLOT(12) TEXT_SLOT(13)
#undef TEXT_SLOT
    virtual UnicodeString fetchAscii(const AsciiString &label, bool *exists = 0);
    virtual UnicodeString fetch(const char *label, bool *exists = 0);
};
extern GameTextInterface *TheGameText;

class InGameNotificationBox
{
public:
    void rva005CC208(const UnicodeString &text, const Rva002217EA &data, int timeoutMS);
};
class Rva005CB260;
class CreateAHeroHero;
class Object;
class InGameNotificationBoxMovieClip {
public: void rva004E6F30(const UnicodeString &, const Rva002217EA &, int, bool, int);
};
class InGameUI
{
public:
    void notifyHeroEarnedAward(CreateAHeroHero *, int);
    void rva0029F954(Object *obj, const char *typeName, const int *label, float seconds);
    Rva005CB260 *rva000CF155()
    {
        return this ? reinterpret_cast<Rva005CB260 *>(m_notificationInterface) : 0;
    }
private:
    unsigned char m_primary[0x10];
    unsigned char m_notificationInterface[4];
    unsigned char pad14[0x9cc-0x14];
    InGameNotificationBoxMovieClip *awardMovie;
    unsigned char pad9d0[0x9e8-0x9d0];
    AsciiString awardLabel;
    float awardSeconds;
};
extern InGameUI *TheInGameUI;

void ShowStuckAsObserverInStrategicRTSGameMessage()
{
    InGameNotificationType *type = FindInGameNotificationType(AsciiString("Generic"));
    if (!type)
        return;
    UnicodeString text = TheGameText->fetch("GUI:StuckAsObserverInStrategicRTSGameMessage");
    InGameNotificationBox *box = (InGameNotificationBox *)TheInGameUI->rva000CF155();
    box->rva005CC208(text, type->rva00221ABB(), 0);
}

// Target evidence for notifyHeroEarnedAward: WB0x00DC4B30 names the owner,
// method and InGameUI.cpp:8930/8936/8948; native 0x0029DCA9..0x0029DE76
// is the whole 461-byte RET8 body. Existing helper ABIs are retained under
// their established names. Target reads the hero UnicodeString at +8,
// award ASCII label/image at +0x10/+0x18, UI movie pointer +0x9CC,
// format label +0x9E8 and seconds +0x9EC. The +0x1A104 ScriptEngine word
// is a gate; its original field name is unproved. No compatible BFME1/ZH
// definition of this BFME2 hero-award method exists in the current donor.
// The unique 233-byte movie Open callee at 0x004E6F30 has RET20 and a byte
// fourth argument; WB checks its signed fifth location argument against 0..2.
// Its address-derived spelling preserves uncertainty about the location enum.
#include "../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;
struct AwardScriptEngineView { char pad[0x1a104]; int suppressed; };
class Player { public: bool isLocalPlayer() const; };
// The KindOf bit set at +0x108; notifyOfHeroSpawnEvent tests bit 90 (0x5A).
class ThingTemplate
{
public:
 bool isKindOf90() const { return (m_kindOf[90 >> 3] & (1 << (90 & 7))) != 0; }
private:
 unsigned char m_pad000[0x108];
 unsigned char m_kindOf[0x20];
};
class Object
{
public:
 Player *getControllingPlayer() const;
 void *getDisplayName();
 ThingTemplate *getTemplate() const { return m_template; }
private:
 void *m_vtable;
 ThingTemplate *m_template;
};
class Rva004076EE { public: Object *rva004076EE(); };
struct HeroAwardNameView { char pad[8]; UnicodeString name; };
struct BfmePod40;
class Rva0040AAD5 { public: BfmePod40 *rva0040AAD5(int); };
extern Rva0040AAD5 *g_00E02F74;
struct HeroAwardRecordView { char pad[0x10]; AsciiString label; unsigned word14; AsciiString image; };
class Image;
class ImageCollection { public: const Image *findImageByName(const AsciiString &); };
extern ImageCollection *TheMappedImageCollection;
void InGameUI::notifyHeroEarnedAward(CreateAHeroHero *hero, int key)
{
 if (!TheGameLogic->rva0042219() || ((AwardScriptEngineView *)TheScriptEngine)->suppressed >= 0) return;
 Object *object=((Rva004076EE *)hero)->rva004076EE();
 if (!object || !object->getControllingPlayer()->isLocalPlayer()) return;
 HeroAwardRecordView *award=(HeroAwardRecordView *)g_00E02F74->rva0040AAD5(key);
 if (!award || award->label.isEmpty()) return;
 InGameNotificationType *type=FindInGameNotificationType(AsciiString("HeroEarnedAward"));
 if (!type) return;
 bool exists;
 UnicodeString format=TheGameText->fetchAscii(awardLabel,&exists);
 if (!exists) return;
 UnicodeString label=TheGameText->fetchAscii(award->label);
 UnicodeString text;
 text.format(format.str(),((HeroAwardNameView *)hero)->name.str(),label.str());
 const Image *image=TheMappedImageCollection->findImageByName(award->image);
 Rva002217EA data=type->rva00221ABB();
 data.rva0010670B(image);
 InGameNotificationBoxMovieClip *movie=awardMovie;
 movie->rva004E6F30(text,data,(int)(awardSeconds*1000.0f),0,0);
}

// Target evidence for 0x0029F954 (350 bytes ret 0x10): WB 0x00DC46B0 names
// it InGameUI::notifyOfHeroSpawnEvent (InGameUI.cpp asserts 8874..8897);
// the pinned placeholder spelling is the one its matched hero-event callers
// 0x002A123F/0x002A1261/0x002A1283 use. Their third argument is the address
// of an InGameUI AsciiString message label (+0x9D0/+0x9D8/+0x9E0) that
// retail passes straight to GameText slot 0x38 (the AsciiString fetch); the
// fourth is its duration in seconds, converted on the x87 like
// notifyHeroEarnedAward (this unit's no-SSE codegen). Only a hero (template
// KindOf bit 90) of the local player notifies: the fetched label formatted
// with the object's display name goes to the +0x9CC notification movie with
// the type's record carrying getButtonImage of the template and object.
const Image *getButtonImage(ThingTemplate *tmpl, Object *obj);
void InGameUI::rva0029F954(Object *obj, const char *typeName, const int *label, float seconds)
{
 if (!obj->getTemplate()->isKindOf90() || !obj->getControllingPlayer()->isLocalPlayer())
  return;
 InGameNotificationType *type = FindInGameNotificationType(AsciiString(typeName));
 if (!type)
  return;
 bool exists;
 UnicodeString format = TheGameText->fetchAscii(*(const AsciiString *)label, &exists);
 if (!exists)
  return;
 ThingTemplate *tmpl = obj->getTemplate();
 UnicodeString text;
 text.format(format.str(), ((UnicodeString *)obj->getDisplayName())->str());
 Rva002217EA data = type->rva00221ABB();
 data.rva0010670B(getButtonImage(tmpl, obj));
 InGameNotificationBoxMovieClip *movie = awardMovie;
 movie->rva004E6F30(text, data, (int)(seconds * 1000.0f), 0, 0);
}
