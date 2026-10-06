// cl: /DNDEBUG /MD /EHsc /Oy-
//
// ?rva00272BE7@Drawable@@QAEXXZ @0x00272BE7 (55B):
// Drawable dual null-terminated walk: draw modules at +0x14C via slot 0x70
// then client items at +0x154 via slot 0x48. Evidence: same +0x14C module walk
// and slot 0x70 as Drawable_getCurrentClientBonePositions plus slot 0x48 as in
// Drawable_rva00278689; neighbours Drawable 0x002727C8 and 0x00274176 share flags;
// callers 0x00265200 0x00275313 0x00469F23 plus jmp tail 0x00275590.
class DrawModule
{
public:
    virtual void slot00() = 0; virtual void slot04() = 0;
    virtual void slot08() = 0; virtual void slot0C() = 0;
    virtual void slot10() = 0; virtual void slot14() = 0;
    virtual void slot18() = 0; virtual void slot1C() = 0;
    virtual void slot20() = 0; virtual void slot24() = 0;
    virtual void slot28() = 0; virtual void slot2C() = 0;
    virtual void slot30() = 0; virtual void slot34() = 0;
    virtual void slot38() = 0; virtual void slot3C() = 0;
    virtual void slot40() = 0; virtual void slot44() = 0;
    virtual void slot48() = 0; virtual void slot4C() = 0;
    virtual void slot50() = 0; virtual void slot54() = 0;
    virtual void slot58() = 0; virtual void slot5C() = 0;
    virtual void slot60() = 0; virtual void slot64() = 0;
    virtual void slot68() = 0; virtual void slot6C() = 0;
    virtual void slot70() = 0; virtual void slot74() = 0;
    virtual void slot78() = 0; virtual void slot7C() = 0;
    virtual void slot80() = 0; virtual void slot84() = 0;
    virtual void slot88() = 0; virtual void slot8C() = 0;
    virtual void slot90() = 0; virtual void slot94() = 0;
    virtual void slot98() = 0; virtual void slot9C() = 0;
    virtual void slotA0() = 0; virtual void slotA4() = 0;
    virtual void slotA8() = 0; virtual void slotAC() = 0;
    virtual void slotB0() = 0; virtual void slotB4() = 0;
    virtual void slotB8() = 0; virtual void slotBC() = 0;
    virtual void slotC0() = 0; virtual void slotC4() = 0;
    virtual void slotC8() = 0; virtual void slotCC() = 0;
    virtual int slotD0() = 0;
};
class ClientItem
{
public:
    virtual void slot00() = 0; virtual void slot04() = 0;
    virtual void slot08() = 0; virtual void slot0C() = 0;
    virtual void slot10() = 0; virtual void slot14() = 0;
    virtual void slot18() = 0; virtual void slot1C() = 0;
    virtual void slot20() = 0; virtual void slot24() = 0;
    virtual void slot28() = 0; virtual void slot2C() = 0;
    virtual void slot30() = 0; virtual void slot34() = 0;
    virtual void slot38() = 0; virtual void slot3C() = 0;
    virtual void slot40() = 0; virtual void slot44() = 0;
    virtual void slot48() = 0;
};
class Drawable
{
public:
    void rva00272BE7();
    int rva0027272B();
private:
    char m_pad[0x14C];
    DrawModule **m_drawModules;
    char m_pad14C[0x154 - 0x150];
    ClientItem **m_client;
};
void Drawable::rva00272BE7()
{
    for (DrawModule **p = m_drawModules; *p; ++p)
        (*p)->slot70();
    for (ClientItem **q = m_client; q && *q; ++q)
        (*q)->slot48();
}
// @0x0027272B (34B): module scan returning first nonzero slotD0 value else 0.
// Caller 0x004087F7.
int Drawable::rva0027272B()
{
    for (DrawModule **p = m_drawModules; *p; ++p)
    {
        int v = (*p)->slotD0();
        if (v != 0)
            return v;
    }
    return 0;
}
