// cl: /O1 /G7 /MD /EHsc
// WB1370CA0 names AIBuilder::DoXfer; native4EC1D9..4EC276 is157B RET4.
// Native (rather than WB's older version) transfers Version1/5, unsigned158
// at v2 and bool154 at v5. It serializes components140/4/B4/E4 unconditionally,
// component38 from v3 and the pointer at12C from v4. Their established rowed
// identities and exact call order are retained; the component38 and pointer
// class identities are unresolved and keep honest address names.
// All layout offsets come from this native caller; no unseen embedded sizes
// or member semantics are inferred. The new economy/wall/string providers
// unlock these calls without speculative callee pins.
#include "../../Common/GameLogicObjectLookupView.h"
class AsciiString;
// Retail Version stores minimum/current bytes and has an inline constructor;
// that constructor form also reproduces the independent stack homes in DoXfer.
struct WallVersion
{
    WallVersion(unsigned char min, unsigned char cur) : minimum(min), current(cur) {}
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
virtual Xfer &xferVersion(WallVersion *);
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


class AIDozerManager {public: void DoXfer(Xfer*);};
class AIBaseBuilder {public: void DoXfer(Xfer*);};
#include "AIEconomyBuilder/AIEconomyBuilderFarmLibrary.h"
class AIWallBuilder {public: void DoXfer(Xfer*);};
class Rva00598DA2 {public: void rva00598DA2(Xfer*);};
class Rva0059761B {public: void rva0059761B(void*);};
class Player
{
public:
    unsigned char prefix00[0x94];
    unsigned int money94;
};
class Rva00596389
{
public:
    void rva005963A1(int amount);
    unsigned char prefix00[0x14];
    unsigned int saved14;
    int limit18;
};
struct AIBuilderSavingsStore
{
    unsigned char prefix00[0x0c];
    Rva00596389 *saver0c;
};
struct Rva002A8AB1Record
{
    unsigned char prefix00[0x160];
    void *data160;
    unsigned char gap164[8];
    int difficulty16c;
};
class Rva002A8F24
{
public:
    void *rva002A8F24(Player *);
    Rva002A8AB1Record *rva002A8AB1(void *);
};
extern GameLogic *TheGameLogic;
extern Rva002A8F24 *g_00DFEEF8;
extern int g_Va00DBA4E4;
class AIBuilder {
public: void DoXfer(Xfer*); void moneySaverUpdate();
private:
    Player *owner00;
    unsigned char gap04[0x7c];
    int savingsLimit80;
    unsigned char gap84[0xa8];
    Rva0059761B *component12c; unsigned char opaque130[0x24]; bool flag154; unsigned char gap155[3]; unsigned int value158;
};
void AIBuilder::DoXfer(Xfer *xfer) {
 WallVersion version(1,5);
 xfer->xferVersion(&version);
 if(version.current>=2) xfer->xferUnsignedInt(&value158);
 if(version.current>=5) xfer->xferBool(&flag154);
 reinterpret_cast<AIDozerManager*>(reinterpret_cast<unsigned char*>(this)+0x140)->DoXfer(xfer);
 reinterpret_cast<AIBaseBuilder*>(reinterpret_cast<unsigned char*>(this)+4)->DoXfer(xfer);
 reinterpret_cast<AIEconomyBuilder*>(reinterpret_cast<unsigned char*>(this)+0xb4)->DoXfer(xfer);
 reinterpret_cast<AIWallBuilder*>(reinterpret_cast<unsigned char*>(this)+0xe4)->DoXfer(xfer);
 if(version.current>=3) reinterpret_cast<Rva00598DA2*>(reinterpret_cast<unsigned char*>(this)+0x38)->rva00598DA2(xfer);
 if(version.current>=4) component12c->rva0059761B(xfer);
}

// WB1371120 establishes the method name and savings-update purpose. Native
// 4EC0C1..4EC166 establishes every accessed offset, unsigned money conversion,
// and the three already-rowed calls. WB's Player money offset differs; +0x94
// here is native evidence. The configuration's extent and identity remain open.
void AIBuilder::moneySaverUpdate()
{
    unsigned int frame = TheGameLogic->getFrame();
    if (value158 <= frame)
    {
        AIBuilderSavingsStore *store = static_cast<AIBuilderSavingsStore *>(g_00DFEEF8->rva002A8F24(owner00));
        Rva00596389 *saver = store->saver0c;
        saver->limit18 = savingsLimit80;
        if (saver->limit18 == -1 || saver->saved14 < static_cast<unsigned int>(saver->limit18))
        {
            Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(owner00);
            double amount = static_cast<float>(owner00->money94) *
                *reinterpret_cast<float *>(static_cast<unsigned char *>(record->data160) + 0xac + record->difficulty16c * 4);
            if (amount > 1.0f)
                saver->rva005963A1(static_cast<int>(amount));
        }
        value158 = frame + g_Va00DBA4E4 * 2;
    }
}
