// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Transferred unchanged from Open-BFME-1 5cae4bdff game/GameEngine/Source/GameNetwork/Rva007F7360EntryRequest.cpp;
// bfme1_sweep places the same masked body: requestEntry at BFME2 0x00663A50. Addresses in the donor text are BFME1.
// FESL game-browser LID/GID entry request at retail 0x007F7360 (vtable slot
// 0x00D2B85C). Its reply goes through the 0x007F7350 adapter to
// BfmeThingZI::Rva007F72D0, which clears the entry's active word. Same
// request shape as the region count request at 0x007F7A00.

struct Rva007F72D0Obj;

class BfmeC994
{
public:
    BfmeC994(char *buffer, int size);
    char m_unknown[0x34];
};
class Gen_007e86c0
{
public:
    void m();
};
class Rva007F7360Sender
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14();
    virtual void send(BfmeC994 *message, int lid, int gid);
};
class Rva007F7360Notifier
{
public:
    virtual void v0();
    virtual void v1();
    virtual void send(BfmeC994 *message,
        void (*callback)(int, Rva007F72D0Obj *),
        Rva007F72D0Obj *owner, int transaction);
};
void Rva007F7350Thunk(int messageAddress, Rva007F72D0Obj *opaqueObject);
class Rva007E8810Message;

class BfmeThingZI
{
public:
    void requestEntry(int lid, int gid);
    void Rva007F72D0(Rva007E8810Message *message);

    char m_pad00[0x10];
    Rva007F7360Sender *m_sender;
    Rva007F7360Notifier *m_notifier;
    char m_pad18[0x2c4];
    char m_messageBuffer[0x400];
    int m_transaction;
};

void BfmeThingZI::requestEntry(int lid, int gid)
{
    BfmeC994 message(m_messageBuffer, 0x400);
    m_sender->send(&message, lid, gid);
    m_notifier->send(&message, Rva007F7350Thunk, (Rva007F72D0Obj *)this,
        m_transaction);
    ((Gen_007e86c0 *)&message)->m();
}

// BFME 2 0x00663A40 (15B; BFME 1 0x007F7350): the reply adapter handed to the
// notifier above, forwarding the reply to the owner's Rva007F72D0 (0x006639C0).
void Rva007F7350Thunk(int messageAddress, Rva007F72D0Obj *opaqueObject)
{
    ((BfmeThingZI *)opaqueObject)->Rva007F72D0((Rva007E8810Message *)messageAddress);
}
