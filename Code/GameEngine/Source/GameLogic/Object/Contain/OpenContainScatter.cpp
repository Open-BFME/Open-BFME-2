// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /ICode/Libraries/Include /ICode/GameEngine/Source/Common
// Native 00464B96..00464D02 scatter algorithm, with source assertions at
// OpenContain.cpp lines 992/1006. The whole reference home and WB 011952F0
// were read; WB's folded BitFlags export is not this routine's identity.
// Preserve the target under an address name. ZH/BFME1 provides the scatter
// purpose, while the native secondary slot44 maskbit61, owner8, position38,
// orientation44, radiusB8, AI258 and command interface +20 supply the ABI.
// Snapshot orientation before the relative-angle call; establish the position
// pointer before the second random call. These lifetimes reproduce native.
// The native source-path literal is retained exactly for the random calls.
#include "Lib/Coord3D.h"
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
extern float GetGameLogicRandomValueReal(float, float, char *, int);
extern float Cos(float);
extern float Sin(float);
enum CommandSourceType { CMD_FROM_AI = 2 };
class AICommandInterface { public: void aiMoveToPosition(const Coord3D *, CommandSourceType); };
class AIUpdateInterface { public: void ignoreObstacle(const Object *); };
class Thing { public: void setPosition(const Coord3D *); };
class Object : public Thing {
public:
    float GetRelativeAngle(const Coord3D *) const;
    int rva0028B511() const;
    void rva0023D3AF(void *);
};
template <int N> class Rva00464B96Slots : public Rva00464B96Slots<N - 1> {
public: virtual void gap(char (*)[N]);
};
template <> class Rva00464B96Slots<0> {};
struct Rva00464B96Mask { unsigned words[4]; bool test(int i) const { return (words[i/32] >> (i%32)) & 1; } };
class Rva00464B96Status : public Rva00464B96Slots<44> {
public: virtual Rva00464B96Mask status(int);
};
class TerrainLogic : public Rva00464B96Slots<7> {
public: virtual float height(float, float, int, int, int);
};
extern TerrainLogic *TheTerrainLogic;
struct Rva00464B96Object {
    char unknown00[0x38];
    Coord3D position38;
    float orientation44;
    char unknown48[0xB8 - 0x48];
    float radiusB8;
    char unknownBC[0x258 - 0xBC];
    AIUpdateInterface *ai258;
};
struct Rva00464B96Logic { char unknown00[0x40]; void *word40; };
class Rva00464B96 {
public:
    void rva00464B96(Object *);
    void *vptr;
    void *data4;
    Object *owner8;
    char unknown0C[0x20 - 0xC];
    Rva00464B96Status status20;
};
void Rva00464B96::rva00464B96(Object *rider)
{
    Object *container = owner8;
    Rva00464B96Object *containerView = reinterpret_cast<Rva00464B96Object *>(container);
    char *file = "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\OpenContain.cpp";
    float angle = GetGameLogicRandomValueReal(0.0f, 6.2831855f, file, 992);
    if (!status20.status(0).test(61)) {
        float orientation = containerView->orientation44;
        angle = orientation + container->GetRelativeAngle(&reinterpret_cast<Rva00464B96Object *>(rider)->position38);
    }
    float radius = containerView->radiusB8;
    const Coord3D *position = &containerView->position38;
    float distance = GetGameLogicRandomValueReal(radius, radius * 1.5f, file, 1006);
    Coord3D target;
    target.x = distance * Cos(angle) + position->x;
    target.y = distance * Sin(angle) + position->y;
    target.z = TheTerrainLogic->height(target.x, target.y, container->rva0028B511(), 0, 1);
    AIUpdateInterface *ai = reinterpret_cast<Rva00464B96Object *>(rider)->ai258;
    if (ai) {
        if (status20.status(0).test(61)) {
            rider->setPosition(position);
            rider->rva0023D3AF(reinterpret_cast<Rva00464B96Logic *>(TheGameLogic)->word40);
            rider->setPosition(position);
        }
        ai->ignoreObstacle(container);
        reinterpret_cast<AICommandInterface *>(reinterpret_cast<char *>(ai) + 0x20)->aiMoveToPosition(&target, CMD_FROM_AI);
    } else rider->setPosition(&target);
}
