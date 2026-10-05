// cl: /O2 /Ob1 /DNDEBUG /MD
// Transferred unchanged from Open-BFME-1 5cae4bdff game/GameEngine/Source/GameNetwork/Rva007F7030Request.cpp;
// bfme1_sweep places the same masked body: request at BFME2 0x00663720. Addresses in the donor text are BFME1.
// Retail 007F7030..007F70CD; INT3-delimited thiscall body with two args.
// Callback VA00BF5790 independently decodes as a two-argument cdecl
// forwarder to the one-argument thiscall body 007F5720.
class Rva007E8810Message;
class Rva007F5720GameBrowser
{
public:
    void handleLoginReply(Rva007E8810Message *message);
};
// BFME 2 0x00661F40 (15B): forward the reply to the browser's
// handleLoginReply (0x00661ED0).
extern "C" void Rva007F5790Callback(void *message, void *browser)
{
    ((Rva007F5720GameBrowser *)browser)->handleLoginReply((Rva007E8810Message *)message);
}
class BfmeC994 {
public:
    BfmeC994(char *, int);
    char bytes[0x34];
};
class Gen_007e86c0 { public: void m(); };
class Rva007F7030Sender {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void send(BfmeC994 *, const char *, int, int);
};
class Rva007F7030Notifier {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void send(BfmeC994 *, void (__cdecl *)(void *, void *), void *, int);
};
class Rva007F7030Listener {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void report(int);
};
class Rva007F7030 {
    char pad00[0x10];
    Rva007F7030Sender *sender;
    Rva007F7030Notifier *notifier;
    int field18;
    Rva007F7030Listener *listener;
    char pad20[0x10];
    int state;
    bool flag34;
    char pad35[0x2a7];
    char buffer[0x400];
    int transaction;
public:
    void request(int first, int second);
};
void Rva007F7030::request(int first, int second)
{
    if (state != 3) {
        listener->report(-105);
        return;
    }
    if (flag34 && second == 0) {
        listener->report(-110);
        return;
    }
    state = 4;
    BfmeC994 message(buffer, 0x400);
    sender->send(&message, "", second, first);
    notifier->send(&message, Rva007F5790Callback, this, transaction);
    ((Gen_007e86c0 *)&message)->m();
}
