// Target facts (code addresses are RVAs; table addresses are VAs):
// AptSaveLoad ctor 0x00436259 calls _bfme_AptGameWindow (0x0051268C) at 0x00436271, then stores 0x00C3CDC8 at +0 and 0x00C3CDC4 at +0x218 (0x00436278/0x0043627E). Its dtor 0x00435DE7 stores the same pair at 0x00435DFC/0x00435E02. The secondary table contains the -0x218 deleting-dtor thunk 0x004360A8 to 0x00436197. The class is polymorphic.
// The primary table has 14 code entries through 0x00C3CDFC: slots 0/1/2/3/4/5/6/7/8/9/10/11/12/13 target 0x00436197/0x00434132/0x00435BB3/0x000A12F8/0x00444680/0x00437053/0x00313913/0x00436846/0x0031393A/0x0008FF78/0x0050B5C6/0x0050B5C6/0x000B3FD0/0x000B3FD0. Slot 7 returns the screen factory pointer 0x006D20D3. The base table 0x00C659E8 has the same 14-entry prefix shape; its secondary table is 0x00C659E4. GameWindow's registered table 0x00C0BBCC has 11 entries and ends at the independently stored next table 0x00C0BBF8.
// AptSaveLoad's factory pushes 0x2B0 at 0x002D20DE and calls its ctor at 0x002D20FA. Ctor stores at 0x00436288..0x004362EB establish dwords +0x27C/+0x280/+0x288/+0x28C/+0x290/+0x294/+0x298/+0x2A0/+0x2A8 and bytes +0x284/+0x29C/+0x29D/+0x2A4. It calls the list-base ctor 0x00434916 on +0x2AC at 0x004362F1; field2AC preserves that four-byte representation without asserting an element layout. The selected-item getter 0x00433F7F proves GameWindow pointers +0x288/+0x28C; callback InitGadgets (0x00435172) proves +0x290. Load (0x004348CA) treats +0x280 as a pointer. Ctor 0x0043630E and dtor 0x00435E8F write s_instance at VA 0x00E032E0.
// Externs 0x00433DFE tests byte +0x298 at 0x00433EE4/0x00433EFA/0x00433F10/0x00433F26/0x00433F3C; field298Byte exposes that low byte of the ctor's dword at the same address.
// AptSaveLoad method spellings and signatures below follow matched ledger rows: 0x00433D71/0x00433D96/0x00433DB1/0x00433DE0/0x00433DF1/0x00433DFE/0x00433F7F/0x00433FDD/0x00433FF3/0x004340AC/0x00434160/0x00434220/0x00434318/0x00434432/0x0043448C/0x004348CA/0x00434A2F/0x00434AAE/0x00434B8A/0x00435107/0x00435172/0x00435224/0x004354F3/0x0043566A/0x004357CF/0x00435819/0x00435BB3/0x0043684C/0x00436FF6/0x00437053. Their nonvirtual ledger spellings remain separate from inherited virtual declarations; the table targets above do not prove original override names.
#ifndef BFME2_GAMECLIENT_APTSAVELOAD_H
#define BFME2_GAMECLIENT_APTSAVELOAD_H

#include "BfmeAptGameWindow.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class GameSpyGameSlot;
struct AptSaveLoadPending;

class AptSaveLoad : public _bfme_AptGameWindow
{
public:
    AptSaveLoad(void *context);
    virtual ~AptSaveLoad();
    virtual WindowMsgHandledType input(unsigned int, unsigned int, unsigned int);
    virtual WindowMsgHandledType bfmeGoEHCb(unsigned int, unsigned int, unsigned int);
    virtual int rva0009FD78();
    virtual void *fetchCreateInstance();

    static AptSaveLoad *s_instance;
    static void OpenScreen(int, int, bool);
    static GameSpyGameSlot *GetOpponentSlotData();
    static void AddFriendConfirmationHandler(int);
    static bool PromptAddFriend();
    void rva00433D71(int);
    void rva00433D96();
    void OnClosed(const char *);
    void Cancel(const char *);
    void rva00433DF1(const char *);
    void Externs(int, char *, bool);
    int rva00433F7F();
    void rva00433FDD();
    void rva004340AC();
    void MultiplayerSaveGameDenied(int);
    void Delete(const char *);
    void rva00434432();
    void rva0043448C();
    void Load(const char *);
    void rva00434A2F();
    void SetDefaultFileName();
    void rva00434B8A();
    void InitGadgets(const char *, void *, GameWindow *);
    void rva00435224();
    void OnButtonSave(const char *);
    void ConfirmationOk(const char *);
    void rva00435819();
    int rva00435BB3(int, GameWindow *, int);
    void rva0043684C();
    void rva00436FF6();
    int rva00437053();

private:
    int field27C;
    AptSaveLoadPending *field280;
    unsigned char field284;
    GameWindow *field288;
    GameWindow *field28C;
    GameWindow *field290;
    int field294;
    union
    {
        int field298;
        unsigned char field298Byte;
    };
    bool field29C;
    bool field29D;
    int field2A0;
    bool field2A4;
    int field2A8;
    unsigned int field2AC;
};

typedef char BfmeAptSaveLoadExtent[(sizeof(AptSaveLoad) == 0x2B0) ? 1 : -1];

#endif
