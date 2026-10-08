// cl: /MD /Oy-
// Ghidra FUN_00814ea1, 00414EA1..00414F27 RET4. The version pair is
// transferred through slot 28, the +1C vector through the 280-byte cdecl
// helper 00414C92, and +2C and the player index through slot 7C.
// ThePlayerList and getPlayerFromMask are established providers. The owner
// and the +1C element identity remain address-derived.
struct Rva00414EA1Version { unsigned char version, current; };
class Xfer
{
public:
    virtual ~Xfer();
    virtual bool isLoading();
    virtual bool isSaving();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void xferVersion(Rva00414EA1Version *version);
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void xferInt(int *value);
};
class Player
{
public:
    char unknown00[0x54];
    int index;
};
class PlayerList { public: Player *getPlayerFromMask(int mask); };
extern PlayerList *ThePlayerList;
struct Rva00414EA1Vector { void *begin, *end, *capacity; };
Xfer *Rva00414C92(Xfer *xfer, Rva00414EA1Vector *values);
// DoXfer is a virtual: slot 3 of vtable 0x00C3A09C, which the ctors 0x004147CF
// and 0x004148C0 store at +0; WorldBuilder's twin is slot 3 of the table its
// twin ctors install.
class ScoredKillEvaAnnouncer
{
public:
    virtual void DoXfer(Xfer *xfer);
private:
    char unknown04[0x18];
    Rva00414EA1Vector values;
    Player *player;
    int value;
};
void ScoredKillEvaAnnouncer::DoXfer(Xfer *xfer)
{
    Rva00414EA1Version version = {1, 1};
    xfer->xferVersion(&version);
    Rva00414C92(xfer, &values);
    xfer->xferInt(&value);
    int playerIndex = player ? player->index : -1;
    xfer->xferInt(&playerIndex);
    if (xfer->isLoading())
    {
        if (playerIndex == -1)
            player = 0;
        else
            player = ThePlayerList->getPlayerFromMask(1 << playerIndex);
    }
}
