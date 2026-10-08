// cl: /DNDEBUG /MD /EHsc /Oy-
//
// ?rva00275545@Drawable@@QAEXXZ @0x00275545 (83B):
// Drawable locally-controlled gate: object at +0xFC via isLocallyControlled
// clears TheRva00DFE77C+0xB8 then rva0028C197 tail slot 0xE0 else tail to
// rva00272BE7. Evidence: rowed isLocallyControlled 0x0028B07A and rva0028C197
// 0x0028C197 plus DIR32 global 0x00DFE77C plus chain callee 0x00272BE7.
class ClientFrameSubsystem; extern class GameClient *TheGameClient;

class Object
{
public:
    bool isLocallyControlled() const;
    void *rva0028C197() const;
    char m_pad00[0x74];
    int m_74;
    char m_pad78[0x250 - 0x78];
    struct Slot3CHolder *m_250;
};
class Rva00DFE77CHolder
{
public:
    char m_pad[0xB8];
    int m_b8;
};
#define TheRva00DFE77C (*(Rva00DFE77CHolder **)&TheGameClient)
class SlotE0Holder
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
    virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
    virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
    virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
    virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
    virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
    virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8C();
    virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9C();
    virtual void slotA0(); virtual void slotA4(); virtual void slotA8(); virtual void slotAC();
    virtual void slotB0(); virtual void slotB4(); virtual void slotB8(); virtual void slotBC();
    virtual void slotC0(); virtual void slotC4(); virtual void slotC8(); virtual void slotCC();
    virtual void slotD0(); virtual void slotD4(); virtual void slotD8(); virtual void slotDC();
    virtual void slotE0();
};
class Drawable
{
public:
    void rva00275545();
    void rva00272BE7();
    void rva00272BAB(int a, int b);
    void rva002754E3();
private:
    char m_pad[0xFC];
    Object *m_object;
};
void Drawable::rva00275545()
{
    Object *obj = m_object;
    if (obj == 0)
        return;
    if (!obj->isLocallyControlled())
        return;
    TheRva00DFE77C->m_b8 &= 0;
    void *p = obj->rva0028C197();
    if (p != 0) {
        SlotE0Holder *h = (SlotE0Holder *)p;
        return h->slotE0();
    }
    if (!obj->isLocallyControlled())
        return;
    return rva00272BE7();
}

struct Slot3CHolder
{
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
    virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
};

class SlotE4Holder
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
    virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
    virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
    virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
    virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
    virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
    virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8C();
    virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9C();
    virtual void slotA0(); virtual void slotA4(); virtual void slotA8(); virtual void slotAC();
    virtual void slotB0(); virtual void slotB4(); virtual void slotB8(); virtual void slotBC();
    virtual void slotC0(); virtual void slotC4(); virtual void slotC8(); virtual void slotCC();
    virtual void slotD0(); virtual void slotD4(); virtual void slotD8(); virtual void slotDC();
    virtual void slotE0(); virtual void slotE4();
};

class BfmeSubBIC
{
public:
    int bfmeAskBIC();
};

// ?rva002754E3@Drawable@@QAEXXZ @0x002754E3 98B
// Evidence: unlock lane, Drawable +0xFC Object, TheGameClient +0xB8, slots 0x3C/0xE4, rows rva0028C197/isLocallyControlled/rva00272BAB, pin bfmeAskBIC.
void Drawable::rva002754E3()
{
    Object *obj = m_object;
    if (obj == 0)
        return;
    Rva00DFE77CHolder *holder = TheRva00DFE77C;
    holder->m_b8 = obj->m_74;
    Slot3CHolder *p250 = obj->m_250;
    if (p250 != 0)
        p250->slot3C();
    void *p = obj->rva0028C197();
    if (p != 0)
        return ((SlotE4Holder *)p)->slotE4();
    if (!obj->isLocallyControlled())
        return;
    int bic = ((BfmeSubBIC *)obj)->bfmeAskBIC();
    rva00272BAB(1, bic);
}
