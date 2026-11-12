// cl: /G7 /O1 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /I.
// stlport
// Dedicated TU: AIBuilder.cpp already carries the matched 0x4EC1D9 DoXfer and
// 0x4EC0C1 moneySaverUpdate rows, so this file keeps only the class views and
// the new 0x4EC3AC onUnitCreated body (its two siblings stay declarations).
// R1/S2 equal-arm carrier on compare()'s template-name argument moves the
// receiver/argument order to retail's: (kindOf115 ? name64 : name64).
// unlock these calls without speculative callee pins.
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "ascii_string.h"
#include <list>

// Compare the typed nodes locally; the shared base wrapper is not called by retail.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits> &a,
                              const _List_iterator<T, RightTraits> &b)
{ return a._M_node != b._M_node; }
}

class AsciiString;
// Retail Version stores minimum/current bytes and has an inline constructor;
// that constructor form also reproduces the independent stack homes in DoXfer.
class Snapshot;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../Include/Common/BfmeXfer.h"


#include "Code/GameEngine/Source/GameLogic/SkirmishAI/AIEconomyBuilder/AIEconomyBuilderFarmLibrary.h"
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
#include "../../../Include/Common/Rva002A8AB1Record.h"
#include "../../../Include/GameLogic/Rva002A8F24.h"
extern GameLogic *TheGameLogic;
extern Rva002A8F24 *TheSkirmishAIManager;
enum ObjectStatusTypes;
#include "../../../Include/Common/ThingTemplate.h"
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


// WB1370420 names onUnitCreated and supplies the list/production-order lead.
// Native4EC3AC..4EC430 proves the +13C sentinel, node +8 payload, payload
// +8 ID/+C name/+10 state, template flag +115 and virtual slot +1C. Payload
// class identity and the other virtual slots remain unresolved.
void AIBuilder::onUnitCreated(Object *object, Object *created, bool horde)
{
    if (object)
    {
        for (_STL::list<AIBuilderOrder *>::iterator it = orders13c.begin(); it != orders13c.end(); ++it)
        {
            AIBuilderOrder *order = *it;
            if ((horde || !(created->template04->m_kindof[3] & 0x2000U)) &&
                order->state10 == 1 && order->objectID08 == object->id74 &&
                !created->testStatus(static_cast<ObjectStatusTypes>(0x57)) &&
                order->name0c.compare( ((created->template04->m_kindof[3] >> 8 & 0xFF) ? created->template04->m_nameString : created->template04->m_nameString)) == 0)
            {
                order->slot07(2);
                break;
            }
        }
    }
}
