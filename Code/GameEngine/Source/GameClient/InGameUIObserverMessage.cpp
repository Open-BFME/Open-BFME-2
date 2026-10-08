// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
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
    TEXT_SLOT(10) TEXT_SLOT(11) TEXT_SLOT(12) TEXT_SLOT(13) TEXT_SLOT(14)
#undef TEXT_SLOT
    virtual UnicodeString fetch(const char *label, bool *exists = 0);
};
extern GameTextInterface *TheGameText;

class InGameNotificationBox
{
public:
    void rva005CC208(const UnicodeString &text, const Rva002217EA &data, int timeoutMS);
};
class Rva005CB260;
class InGameUI
{
public:
    Rva005CB260 *rva000CF155()
    {
        return this ? reinterpret_cast<Rva005CB260 *>(m_notificationInterface) : 0;
    }
private:
    unsigned char m_primary[0x10];
    unsigned char m_notificationInterface[4];
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
