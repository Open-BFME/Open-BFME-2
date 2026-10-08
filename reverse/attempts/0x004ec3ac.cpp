// ?onUnitCreated@AIBuilder@@QAEXPAVObject@@0_N@Z
// partial score=0.85 date=2026-10-08
// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
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
#include "ascii_string.h"
#include <list>
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
enum ObjectStatusTypes;
class ThingTemplate
{
public:
    unsigned char prefix00[0x64];
    AsciiString name64;
    unsigned char gap68[0xad];
    unsigned char kindOf115;
};
class Object
{
public:
    bool testStatus(ObjectStatusTypes) const;
    void *vtable00;
    ThingTemplate *template04;
    unsigned char gap08[0x6c];
    unsigned int id74;
};
class AIBuilderOrder
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07(int state) = 0;
    unsigned int opaque04;
    unsigned int objectID08;
    AsciiString name0c;
    int state10;
};
class AIBuilder {
public: void DoXfer(Xfer*); void moneySaverUpdate();
    void onUnitCreated(Object *, Object *, bool);
private:
    Player *owner00;
    unsigned char gap04[0x7c];
    int savingsLimit80;
    unsigned char gap84[0xa8];
    Rva0059761B *component12c;
    unsigned char opaque130[0xc];
    _STL::list<AIBuilderOrder *> orders13c;
    unsigned char opaque140[0x14];
    bool flag154; unsigned char gap155[3]; unsigned int value158;
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

// WB1370420 names onUnitCreated and supplies the list/production-order lead.
// Native4EC3AC..4EC430 proves the +13C sentinel, node +8 payload, payload
// +8 ID/+C name/+10 state, template flag +115 and virtual slot +1C. Payload
// class identity and the other virtual slots remain unresolved.
// ?onUnitCreated@AIBuilder@@QAEXPAVObject@@0_N@Z present-unmatched
void AIBuilder::onUnitCreated(Object *object, Object *created, bool horde)
{
    if (object)
    {
        for (_STL::list<AIBuilderOrder *>::iterator it = orders13c.begin(); it != orders13c.end(); ++it)
        {
            AIBuilderOrder *order = *it;
            if ((horde || !(created->template04->kindOf115 & 0x20)) &&
                order->state10 == 1 && order->objectID08 == object->id74 &&
                !created->testStatus(static_cast<ObjectStatusTypes>(0x57)) &&
                order->name0c.compare(created->template04->name64) == 0)
            {
                order->slot07(2);
                break;
            }
        }
    }
}
