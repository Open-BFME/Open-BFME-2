// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
class AsciiString;
// Retail Version stores minimum/current bytes and has an inline constructor;
// that constructor form also reproduces the independent stack homes in DoXfer.
struct FarmVersion
{
    FarmVersion(unsigned char min, unsigned char cur) : minimum(min), current(cur) {}
    unsigned char minimum, current;
};
class Xfer{public:virtual~Xfer();virtual bool IsLoading() const;
virtual bool IsStoring() const;
virtual bool IsCRC() const;
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual Xfer &xferVersion(FarmVersion *);
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
virtual Xfer &xferCoord3D(struct Coord3D *);
virtual void slot25();
virtual void slot26();
virtual Xfer& xferAsciiString(AsciiString*);
virtual void slot28();
virtual void slot29();
virtual Xfer &xferUnsignedInt(unsigned int *);
virtual Xfer& xferInt(int*);
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual Xfer &xferBool(bool *);
};
class Player;
// PlayerList's matched mask/index consumers independently establish index at +0x54.
struct FarmPlayerIndexView
{
    unsigned char unknown[0x54];
    int index;
};
class PlayerList { public: Player *getNthPlayer(int index); };
extern PlayerList *ThePlayerList;
// Existing owned transfer at 0x00573F9F. Only its declaration is needed:
// the retail caller passes the same primary object and its owning player.
class Rva00573F03 { public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void Rva00573F9F(Xfer *, void *);
};
// WB 0x01538EF0 names AIFarm::DoXfer (AIFarm.cpp lines 94..107).
// Retail 0x0059702D..0x005970C9 is slot 12 of vtable RVA 0x00870B38.
// WB names the owning-player field at +0x68 and asserts the incoming owner is null.
// The remaining transferred fields retain offset names until their identities are proved.
class AIFarm
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();

    virtual void DoXfer(Xfer *xfer, Player *owner);
private:
    unsigned char unknown04[0x60];
    bool value64;
    unsigned char pad65[3];
    Player *m_owningPlayer;
    int value6c;
    unsigned int value70;
};
void AIFarm::DoXfer(Xfer *xfer, Player *owner)
{
    FarmVersion version(1,1);
    xfer->xferVersion(&version);
    xfer->xferBool(&value64);
    int index=-1;
    if (xfer->IsStoring() && m_owningPlayer)
        index=reinterpret_cast<const FarmPlayerIndexView *>(m_owningPlayer)->index;
    xfer->xferInt(&index);
    if (xfer->IsLoading() && index!=-1)
        m_owningPlayer=ThePlayerList->getNthPlayer(index);
    xfer->xferInt(&value6c);
    xfer->xferUnsignedInt(&value70);
    reinterpret_cast<Rva00573F03 *>(this)->Rva00573F03::Rva00573F9F(xfer,m_owningPlayer);
}
