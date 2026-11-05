// Target facts (code addresses are RVAs; table addresses are VAs): ctor 0x0051215B calls _bfme_AptGameWindow at 0x00512173 and stores the pair 0x00C659A0/0x00C65998; dtor 0x005125ED restores it. Its primary table shares the AptMessengerOnline prefix through slot 13 and has its own slots 14/15/16; unknown override names remain placeholders.
// The ctor builds twelve-byte containers at +0x280/+0x28C, writes dwords +0x27C/+0x298 and bytes +0x29C/+0x29D, and the dtor destroys those containers at 0x00512624..0x00512643, bounding the four-byte-aligned span to 0x2A0. GetSelectedPlayers 0x00511C19 loads a chat-tab pointer through the +0x280 container and calls ChatWindowsInGame::rva005AFEF7.
// Declarations follow rows 0x005AEF16/0x005AEF32/0x005AE886/0x005AE90F/0x005AE990/0x005AEA3E/0x005AEBD3; lifetime methods remain out of line.
#ifndef BFME2_GAMECLIENT_APTMESSENGER_H
#define BFME2_GAMECLIENT_APTMESSENGER_H

#include "BfmeAptGameWindow.h"

class ChatWindowsInGame;

class AptMessenger : public _bfme_AptGameWindow
{
public:
    AptMessenger(void *context);
    virtual ~AptMessenger();
    virtual WindowMsgHandledType input(unsigned int, unsigned int, unsigned int);
    virtual WindowMsgHandledType bfmeGoEHCb(unsigned int, unsigned int, unsigned int);
    virtual int rva0009FD78();
    virtual void vslot12();
    virtual void vslot13();
    virtual void vslot14();
    virtual bool vslot15();
    virtual void *CreateChatWindow(int selector) = 0;

    // The open messenger (VA 0x00E046B8, set by the ctor) and its opener 0x005116C2.
    static AptMessenger *s_instance;
    static void OpenScreen();

    void OnBttn_0(const char *argument);
    void OnBttn_1(const char *argument);
    void GetSelectedPlayers(int listIndex, int profiles, int names);
    void rva005AE886();
    void rva005AE90F();
    void rva005AE990();
    void rva005AEA3E();
    void rva005AEBD3();

protected:
    int field27C;
    ChatWindowsInGame **field280;
    ChatWindowsInGame **field284;
    ChatWindowsInGame **field288;
    unsigned int field28C[3];
    int field298;
    bool field29C;
    bool field29D;
};

typedef char Bfme2AptMessengerExtent[(sizeof(AptMessenger) == 0x2A0) ? 1 : -1];

#endif
