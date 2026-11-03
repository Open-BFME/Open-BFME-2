// Bases of the Apt shell screens (AptSaveLoad and its siblings); _bfme_AptGameWindow is not registered yet.
// The base ctor calls BfmeAptScreenBase (0x00313847) at +0 and Rva005248D0 (0x002D2C34) at +0x218; its 0x005126C6/0x005126CD/0x005126D4 stores place 4/4/1-byte fields at +0x270/+0x274/+0x278. Factory 0x002D1E55 pushes 0x27C at 0x002D1E60 before calling that ctor. Dtor 0x005126F5 destroys AsciiString +0x270 through 0x00036410, Rva005248D0 +0x218 through 0x005248D0, then GameWindow through 0x00314A0C. The 0x274/0x279 base extents in partial views omit storage or tail padding; retail bounds the base to 0x27C. GameWindow and Rva005248D0 come from their existing definitions in the registered Bfme2GameWindow.h and AptMpGameSetup.h headers; the immediate Apt window base has no registered header.
// Rva005248D0's ctor 0x002D2C34 and dtor 0x005248D0 bound its secondary span to 0x58. The ctor calls six holder constructors on +4/+0x10/+0x1C/+0x34/+0x40/+0x4C before storing its vptr at 0x002D2C8C; the dtor destroys those bases in reverse order. The corresponding extents are 12/12/24/12/12/12, with the 24-byte constructor at 0x00524415; the other constructors fold to 0x001F81BF. Dtor targets are 0x0052413E/0x005241B0/0x00524436/0x00524265/0x005242D7/0x00524349. AptSaveLoad's ctor 0x00436347 passes the +4 base (object +0x21C) to the rowed AptCommandMapAdder::AddCommandMap at 0x0052458E. Holder storage names are unproven. The immediate and secondary base constructors/destructors, and AptSaveLoad's virtual destructor, remain out-of-line declarations.
#ifndef BFME2_GAMECLIENT_BFMEAPTGAMEWINDOW_H
#define BFME2_GAMECLIENT_BFMEAPTGAMEWINDOW_H

#include "Bfme2GameWindow.h"
#include "AptMpGameSetup.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class BfmeAptScreenBase : public GameWindow
{
public:
    BfmeAptScreenBase(void *context);
};

class _bfme_AptGameWindow : public BfmeAptScreenBase, public Rva005248D0
{
public:
    _bfme_AptGameWindow(void *context);
    virtual ~_bfme_AptGameWindow();
    virtual WindowMsgHandledType input(unsigned int, unsigned int, unsigned int);
    virtual WindowMsgHandledType bfmeGoEHCb(unsigned int, unsigned int, unsigned int);
    virtual int draw(void *);
    virtual int tooltip(WinInstanceData *, unsigned int);
    virtual int rva0009FD78();
    virtual void *fetchCreateInstance();
    virtual bool vslot11();
    virtual void vslot12();
    virtual void vslot13();
    int rva0051274F(int message, unsigned int data1, unsigned int data2);
private:
    AsciiString field270;
    int field274;
    unsigned char field278;
};

typedef char BfmeAptSaveLoadBaseExtent[(sizeof(_bfme_AptGameWindow) == 0x27C) ? 1 : -1];

#endif
