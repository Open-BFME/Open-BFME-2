// AptPlayer: canonical BFME2 layout. Target facts (code addresses are RVAs; tables are VAs): constructor 0x00224E10 calls SubsystemInterface 0x001B4E63 at 0x00224E23 and stores 0x00BE6E80 at 0x00224E30; destructor 0x00224A90 restores that table at 0x00224AA1 and calls parent 0x001B4E74 at 0x00224B6B. The parent's 0x00BD77A0 has fourteen slots, matching this table's inherited prefix; BFME_SUBSYSTEM_SLOTS supplies them. Derived constructor 0x000628EB calls AptPlayer then stores 0x00BC57E0, and derived destructor 0x000628FD stores that derived table before jumping to AptPlayer's destructor. These tables belong to successive class lifetimes. Factory 0x00041E75 allocates 0x32C bytes before calling 0x000628EB; AptPlayer writes through +0x329 at 0x00224F27. With the parent's four-byte alignment, its extent is 0x32C, and the derived class adds no storage.
// Target facts: table 0x00BE6E80 has 21 slots before string data at 0x00BE6ED4: 0=0x00224F50 (deleting destructor calling 0x00224A90), 1=0x00224296, 2=0x001B5384, 3/8=0x000B3FD0, 4/11=0x005CB9FF, 5=0x0047A699, 6=0x000D43D0, 7/13=0x0047A69C, 9=0x00222471, 10=0x002251E5, 12=0x0022244D, 14=0x0022274A, 15-19=__purecall 0x0003B810, 20=AddLevel 0x00224710. Derived table 0x00BC57E0 supplies 15/16=0x00062972/0x00062977 (tail jumps returning static addresses through 0x000A8F58/0x000A8F5E), 17=0x0006297C (four float-pair pointers, RET 16), 18=0x00062A1C (one word, RET 4), 19=0x00062A29 (forwards one word to bool callee 0x000A8F64, RET 4). Slot 19 therefore takes bool; the no-argument private declaration contradicts retail. Call 0x0056C798 dispatches slot 15 and reads floats at result+0/+4 through 0x0056C7AB; neutral v15 uses its caller's opaque ScalePair pointer view, whose original type name remains unproved. Unknown slot names remain neutral. Constructor and destructor are out-of-line ledger bodies.
// Target facts: constructor 0x00224E10 constructs 0x14-byte containers at +0x0C/+0x20/+0x34/+0x48/+0x5C/+0x70/+0x90/+0xA4/+0xB8 through 0x00224C76, a 0x0C-byte container at +0x84 through 0x000D3A71, fourteen 0x28-byte records at +0xCC through 0x00224C95, and a three-pointer vector at +0x2FC through 0x00211E58. Record constructor 0x00224C95 and destructor 0x00224252 prove strings +0/+4, words +8/+0x0C, container +0x10 and flag byte +0x24. PopFocus 0x00222A33 proves byte +0x308. Constructor stores time +0x30C, bytes +0x310/+0x311/+0x312/+0x328/+0x329 and words +0x314/+0x318/+0x31C/+0x320/+0x324. Container types and field names remain unproved. Ledger rows name LoadLevel 0x00222E29, ShowLevel 0x002224FE, UnloadLevel 0x00222481, HideLevel 0x0022277D, RemoveLevel 0x00224B7D, PeekGameWindow 0x0022252D, GetLevelIndex 0x00222547, OnCommand 0x00223D4C, OnCustomRender 0x00223D8D, GetExtern 0x00223E4B, SetExtern 0x00223DD7, FindRenderImage 0x00223AC4, WinCreate 0x00223263, PopFocus 0x00222A33, HandleOverButtons 0x00224F6C, AddCommandMap 0x002243E3, AddExternHandler 0x0022445D, AddCustomRender 0x0022464C, AddTimer 0x002246B9, AddOverButtonHandler 0x002244D2/0x00224584 and RemoveOverButtonHandler 0x0022453E/0x002245FF; their declarations preserve those out-of-line calls.
#ifndef BFME2_APTPLAYERCLASS_H
#define BFME2_APTPLAYERCLASS_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../subsystem/SubsystemInterface.h"

class AptFocusTarget;
class AptCommandMap;
class AptExternHandler;
class AptCustomRender;
class AptOverButtonHandler;
class AptTimer;
class GameWindow;
class Image;
struct AptLayoutInfoView;
struct ScalePair;
template <class T> class AptRef;

class AptPlayer : public SubsystemInterface
{
public:
    AptPlayer();
    virtual ~AptPlayer();
    virtual void init();
    virtual void reset();
    virtual void update();
    virtual void vslot12();
    virtual void vslot14();
    virtual ScalePair *v15() = 0;
    virtual void *vslot16() = 0;
    virtual void vslot17(const float *, const float *, float *, float *) = 0;
    virtual void vslot18(int) = 0;
    virtual void slot19(bool) = 0;
    virtual int AddLevel(AsciiString directory, AsciiString file, bool show, int parameter);

    bool LoadLevel(unsigned int index);
    bool ShowLevel(int index);
    bool UnloadLevel(int index);
    bool HideLevel(int index);
    bool RemoveLevel(int index);
    void *PeekGameWindow(int index);
    static int GetLevelIndex(GameWindow *window);
    void OnCommand(const char *name, int value);
    void OnCustomRender(const char *name, int a, int b, int c, int d);
    void GetExtern(const char *name, char *out);
    void SetExtern(const char *name, int value);
    const Image *FindRenderImage(const char *name, const char *parameters);
    GameWindow *WinCreate(const AsciiString *name, AptLayoutInfoView *layout);
    void PopFocus(AptFocusTarget *target);
    void HandleOverButtons();
    void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);
    void AddExternHandler(const AsciiString &name, int context, AptRef<AptExternHandler> handler);
    void AddCustomRender(const AsciiString &name, AptRef<AptCustomRender> render);
    void AddOverButtonHandler(const AsciiString &name, AptRef<AptOverButtonHandler> handler);
    void AddOverButtonHandler(unsigned int level, const AsciiString &name, AptRef<AptOverButtonHandler> handler);
    void AddTimer(const AsciiString &name, AptRef<AptTimer> timer);
    void RemoveOverButtonHandler(const AsciiString &name);
    void RemoveOverButtonHandler(int level, const AsciiString &name);

    struct Record
    {
        AsciiString field00;
        AsciiString field04;
        unsigned int field08;
        int field0C;
        unsigned char field10[0x14];
        unsigned char field24;
        unsigned char field25[3];
    };

    unsigned char field00C[0x14];
    unsigned char field020[0x14];
    unsigned char field034[0x14];
    unsigned char field048[0x14];
    unsigned char field05C[0x14];
    unsigned char field070[0x14];
    unsigned char field084[0x0C];
    unsigned char field090[0x14];
    unsigned char field0A4[0x14];
    unsigned char field0B8[0x14];
    Record field0CC[14];
    void *field2FC;
    void *field300;
    void *field304;
    bool field308;
    unsigned int field30C;
    bool field310;
    bool field311;
    bool field312;
    unsigned int field314;
    unsigned int field318;
    unsigned int field31C;
    unsigned int field320;
    int field324;
    bool field328;
    bool field329;
};

#endif
