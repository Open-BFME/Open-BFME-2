// Target facts (code addresses are RVAs; table addresses are VAs): ctor 0x005142B0 calls _bfme_AptGameWindow at 0x005142C8, then stores 0x00C65D20 at +0 (0x005142D9) and 0x00C65D1C at +0x218 (0x005142DF). Dtor 0x00513BAB restores those same tables at 0x00513BBE/0x00513BC4. The secondary table contains the -0x218 deleting-dtor thunk 0x00513CD4 to 0x00513DB4, whose call at 0x00513DB7 reaches the destructor. This class is polymorphic. The base's different pair 0x00C659E8/0x00C659E4 belongs to _bfme_AptGameWindow: its ctor 0x0051268C and dtor 0x005126F5 store that pair before the derived ctor replaces it or after derived teardown.
// The primary table has fourteen entries, slots 0..13 targeting 0x00513DB4/0x00513888/0x005138B8/0x000A12F8/0x00444680/0x005138E8/0x00313913/0x0051482F/0x0031393A/0x0008FF78/0x0050B5C6/0x00513838/0x00513988/0x000B3FD0. Override declarations preserve the existing base header's slot names; they do not assert original names for the address-named targets. Factory 0x002D1F03 pushes 0x438 at 0x002D1F0E and calls the ctor at 0x002D1F2A. The ctor constructs AptMyHero at +0x27C (0x005142E9), initializes dwords +0x40C..+0x428, bytes +0x42C..+0x433 and dword +0x434; the destructor destroys AptMyHero at 0x00513CB6. field27C preserves its 0x190-byte span without inventing its internal layout.
// The disputed +0x228 storage belongs to the base's second twelve-byte holder: Rva005248D0's ctor 0x002D2C34 constructs it at secondary +0x10, while AptMyHero's ctor 0x005B12C5 calls AddExternHandler on screen +0x228. Base ctor 0x0051268C writes dword -1 at +0x274 (0x005126CD); both disputed offsets remain in the included base. Method declarations follow ledger rows 0x005139B0/0x00513A47/0x00513A51/0x00513A64/0x00513A6D/0x00513AA8/0x00513ABB/0x00513ACE/0x00513AE1/0x00513AF4/0x00513CDF/0x00514070. Ctor 0x005143A7 and dtor 0x00513CA6 write s_instance at VA 0x00E048D4; Rva00513866 reads it at 0x00513866. Nested type declarations retain the ledger scopes Class, Powers, Appearance and Manager.
#ifndef BFME2_COMMON_APTCREATEAHERO_H
#define BFME2_COMMON_APTCREATEAHERO_H

#include "../GameClient/BfmeAptGameWindow.h"

class Coord2D;
class Rva005B6B93;
class Rva005B2575;

class AptCreateAHero : public _bfme_AptGameWindow
{
public:
    class Class;
    class Powers;
    class Appearance;
    class Manager;

    AptCreateAHero(void *context);
    virtual ~AptCreateAHero();
    virtual WindowMsgHandledType input(unsigned int, unsigned int, unsigned int);
    virtual WindowMsgHandledType bfmeGoEHCb(unsigned int, unsigned int, unsigned int);
    virtual int rva0009FD78();
    virtual void *fetchCreateInstance();
    virtual bool vslot11();
    virtual void vslot12();

    void OnShowScreen(const char *screen);
    void PrepareToTakePicture(const char *unused);
    void OnTakePicture(const char *unused);
    void RenderPictureGuard(const void *, const void *, void *, void *);
    void CreateAHeroDemo(int query, char *result, bool skip);
    void RotateLeft(const char *pressed);
    void RotateRight(const char *pressed);
    void ZoomIn(const char *pressed);
    void ZoomOut(const char *pressed);
    void rva00513AF4(const char *value);
    void DrawMapComponent(const Coord2D *, const Coord2D *, void *, void *);
    static void OpenScreen(int mode);

private:
    unsigned int field27C[0x190 / 4];
    int field40C;
    void *field410;
    void *field414;
    Rva005B6B93 *field418;
    Class *field41C;
    Appearance *field420;
    Powers *field424;
    Rva005B2575 *field428;
    bool field42C;
    bool field42D;
    bool field42E;
    bool field42F;
    bool field430;
    bool field431;
    bool field432;
    bool field433;
    int field434;

    friend void Rva00513866();
    static AptCreateAHero *s_instance;
};

typedef char BfmeAptCreateAHeroExtent[(sizeof(AptCreateAHero) == 0x438) ? 1 : -1];

#endif
