// cl: /DNDEBUG /MD /EHsc /Oy-
//
// ?rva00272BE7@Drawable@@QAEXXZ @0x00272BE7 (55B):
// Drawable dual null-terminated walk: draw modules at +0x14C via slot 0x70
// then client items at +0x154 via slot 0x48. Evidence: same +0x14C module walk
// and slot 0x70 as Drawable_getCurrentClientBonePositions plus slot 0x48 as in
// Drawable_rva00278689; neighbours Drawable 0x002727C8 and 0x00274176 share flags;
// callers 0x00265200 0x00275313 0x00469F23 plus jmp tail 0x00275590.
#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
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
void Drawable::rva00272BE7()
{
    for (DrawModule **p = ((DrawModule **)m_modules[0]); *p; ++p)
        (*p)->slot70();
    for (ClientItem **q = ((ClientItem **)m_modules[2]); q && *q; ++q)
        (*q)->slot48();
}
// @0x0027272B (34B): module scan returning first nonzero slotD0 value else 0.
// Caller 0x004087F7.
int Drawable::rva0027272B()
{
    for (DrawModule **p = ((DrawModule **)m_modules[0]); *p; ++p)
    {
        int v = (*p)->slotD0();
        if (v != 0)
            return v;
    }
    return 0;
}
