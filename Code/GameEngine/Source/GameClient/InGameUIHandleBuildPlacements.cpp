// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_OPERATOR_NEW_DEFINED_ /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /ICode/GameEngine/Include /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// InGameUI::handleBuildPlacements, native 0x002A21E1..0x002A3255 (4212 bytes).
// WorldBuilder 0x00DAD2E0 retains the placement, port-preview, castle-preview
// and resource-feedback control flow. Native instructions establish the layouts,
// call targets, 0x194 frame and seven-state exception graph used here.
// Matrix3D helpers use the pinned BFME 1 reference cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
// The 67-byte static lookup below is retained by its real placement caller;
// MSVC supplies retail's EAX argument convention without assembly or a shim.

#include "ascii_string.h"
#include "unicode_string.h"
#include "Coord3D.h"
#include "Coord2D.h"
#include <vector>
#include <math.h>
#include "matrix3d.h"
void __cdecl Rva00030830GameFree(void*);
namespace _STL
{
template <> __forceinline void allocator<Coord3D>::deallocate(Coord3D* p, size_t) const
{
    if (p)
        Rva00030830GameFree(p);
}
}
#include "ICoord2D.h"
#include "../Common/PlacementPositionValue.h"
#include "RGBColor.h"
static const RGBColor illegalBuildColor = { 1, 0, 0 };
struct RGBAColorInt
{
    int v[4];
};
class Mouse
{
public:
    enum MouseCursor
    {
        CURSOR_BUILD = 5,
        CURSOR_INVALID = 12
    };
    void setMouseText(UnicodeString, const RGBAColorInt*, const RGBAColorInt*);
    char unknown[0x4f0c];
    ICoord2D pos;
};
extern Mouse* TheMouse;
class TerrainResourceBehaviorModuleData;
class ModuleData
{
public:
    virtual void slot0();
    virtual void slot4();
    virtual void slot8();
    virtual void slotC();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual const TerrainResourceBehaviorModuleData* resourceData() const;
    char unknown04[0x30 - 4];
    float placementRadius;
};
class TerrainResourceBehaviorModuleData
{
public:
    char unknown00[12];
    int maxIncome;
};
class ModuleInfo
{
public:
    const void *first, *last, *cap;
    __declspec(noinline) const ModuleData* getNthData(int) const;
    int count() const { return ((const char*)last - (const char*)first) / 20; }
};
class ThingTemplate
{
public:
    const ModuleData* rva0033B3D7() const;
    const ModuleData* rva0033B427(int) const;
    bool isEquivalentTo(const ThingTemplate*) const;
    char unknown00[0x108];
    unsigned char kinds[28];
    char unknown124[0x2e4 - 0x124];
    ModuleInfo modules;
    __forceinline bool hasKind(int i) const { return (kinds[i / 8] & (1 << (i % 8))) != 0; }
};
// ?rva0029B9E5@@YAPBVTerrainResourceBehaviorModuleData@@PBVThingTemplate@@@Z
// Native 0x0029B9E5 scans the module vector at +0x2E4 and queries slot +0x60.
static const TerrainResourceBehaviorModuleData* rva0029B9E5(const ThingTemplate* type)
{
    const ModuleInfo& modules = type->modules;
    int count = modules.count();
    for (int i = 0; i < count; ++i)
    {
        const ModuleData* data = modules.getNthData(i);
        if (data)
        {
            const TerrainResourceBehaviorModuleData* result = data->resourceData();
            if (result)
                return result;
        }
    }
    return 0;
}
class Thing
{
public:
    __forceinline const ThingTemplate* getTemplate() const { return type; }
    void setOrientation(float);
    void setPositionZ(float);
    void* vtable;
    const ThingTemplate* type;
    char unknown08[0x38 - 8];
    Coord3D position;
};
class ModelConditionFlags;
class Rva0028F59A
{
public:
    Rva0028F59A(int, int);
    unsigned int words[19];
};
class Rva002707FA
{
public:
    void rva002707FA(unsigned char);
};
class Drawable : public Thing
{
public:
    void setPosition(const Coord3D*);
    const Coord3D* getPosition() const;
    void setDrawableHidden(bool);
    void rva002791E7(const ModelConditionFlags&, unsigned, unsigned);
    void colorTint(const RGBColor*);
    char unknown44[0xb0 - 0x44];
    float opacity;
};
class Player
{
public:
    __forceinline int getPlayerIndex() const { return index; }
    void rva002AF614(void*);
    char unknown00[0x54];
    int index;
    char unknown58[0x280 - 0x58];
    int color;
};
class Object : public Thing
{
public:
    Player* getControllingPlayer() const;
};
class Rva00293330
{
public:
    void* rva00293330(unsigned);
};

class Cb00359D42;
class TerrainResourceManager
{
public:
    void enumerateRegisteredClaimants(int, Cb00359D42*);
};

#include "../Common/GameLogicObjectLookupView.h"

extern GameLogic* TheGameLogic;
class PlayerList
{
public:
    int getPlayersWithRelationship(int, unsigned, bool);
    char unknown00[0x10];
    Player* local;
};
extern PlayerList* ThePlayerList;
class ResourceEntryCollector
{
public:
    void rva004E551E();
    void addEntry(const Coord3D*, float, int);
};
class Rva004E54B8
{
public:
    void rva004E54B8();
};
struct BfmeUiResourceEntryState
{
    unsigned unknown00;
    void* head;
};
extern BfmeUiResourceEntryState BfmeUiResourceEntryCollectorState;
#include "../Common/Bfme/PlaceTerrainResourceClaimantFeedbackView.h"
class Rva004E63DB
{
public:
    void rva004E63DB();
};
class Rva004E668E;
class Rva0029B5FD
{
public:
    void reset(Rva004E668E*);
    PlaceTerrainResourceClaimantFeedback* ptr;
};
class View
{
public:
    virtual void slot0();
    virtual void slot4();
    virtual void slot8();
    virtual void slotC();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6C();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual void slot7C();
    virtual void slot80();
    virtual void slot84();
    virtual void slot88();
    virtual void slot8C();
    virtual void slot90();
    virtual void slot94();
    virtual void slot98();
    virtual void slot9C();
    virtual void slotA0();
    virtual void slotA4();
    virtual void slotA8();
    virtual void slotAC();
    virtual void slotB0();
    virtual void slotB4();
    virtual void slotB8();
    virtual void slotBC();
    virtual void slotC0();
    virtual void slotC4();
    virtual void slotC8();
    virtual void slotCC();
    virtual void slotD0();
    virtual void slotD4();
    virtual void slotD8();
    virtual void slotDC();
    virtual void slotE0();
    virtual void slotE4();
    virtual void slotE8();
    virtual void slotEC();
    virtual void slotF0();
    virtual void slotF4();
    virtual void slotF8();
    virtual void slotFC();
    virtual void slot100();
    virtual void slot104();
    virtual void slot108();
    virtual void slot10C();
    virtual void slot110();
    virtual void slot114();
    virtual void slot118();
    virtual void slot11C();
    virtual void slot120();
    virtual void slot124();
    virtual void slot128();
    virtual void slot12C();
    virtual void slot130();
    virtual void slot134();
    virtual void slot138();
    virtual void slot13C();
    virtual void slot140();
    virtual void slot144();
    virtual void slot148();
    virtual void slot14C();
    virtual void slot150();
    virtual void slot154();
    virtual void slot158();
    virtual void slot15C();
    virtual void slot160();
    virtual void slot164();
    virtual void screenToTerrain(const ICoord2D*, Coord3D*, bool = false);
};
extern View* TheTacticalView;
class GlobalData
{
public:
    char unknown00[0xa94];
    int maxLineBuildObjects;
};
extern GlobalData* TheWritableGlobalData;
class GameClient
{
public:
    virtual void slot0();
    virtual void slot4();
    virtual void slot8();
    virtual void slotC();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6C();
    virtual void slot70();
    virtual void destroyDrawable(Drawable*);
    virtual void slot78();
    virtual unsigned getFrame();
};
extern GameClient* TheGameClient;
class ThingFactory
{
public:
    void* newDrawable(void*, int, int);
    const ThingTemplate* findTemplate(const AsciiString&);
};
extern ThingFactory* TheThingFactory;
class SpecialPowerModule
{
public:
    virtual void slot0();
    virtual void slot4();
    virtual void slot8();
    virtual void slotC();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual bool getRadius(float*);
};
class Rva004D9A3C
{
public:
    Coord3D pos;
    float angle;
    char unknown10[12];
};
class Rva0039205C
{
public:
    Rva0039205C()
    {
        count = 0;
        array = 0;
        flagC = false;
        flagD = false;
        status = -1;
        cost = 0;
        unknown14 = 0;
    }
    ~Rva0039205C();
    void* rva00392CC5(unsigned);
    Rva004D9A3C* rva00392CF9(unsigned);
    float rva00392D1D(unsigned);
    int rva00392D71(int);
    unsigned count;
    int cost;
    Rva004D9A3C* array;
    bool flagC, flagD;
    int status;
    void* unknown14;
};
class BuildAssistant
{
public:
    virtual void slot0();
    virtual void slot4();
    virtual void slot8();
    virtual void slotC();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual int isLocationLegalToBuild(
        const Coord3D*, const ThingTemplate*, float, int, Object*, Object*);
    virtual void slot44();
    virtual void slot48();
    virtual void slot4c();
    virtual bool getBuildPortData(Rva0039205C*, Object*, const Coord3D*, const Coord3D*, unsigned);
    virtual void slot54();
    virtual void slot58();
    virtual bool isBuildPort(const ThingTemplate*, Object*);
    bool getPortTransform(const Coord3D*, const ThingTemplate*, float, float*, Coord3D*);
};
extern BuildAssistant* TheBuildAssistant;
class Rva0029A94F
{
public:
    void rva0029A94F();
};
class TerrainType
{
public:
    AsciiString getTexture() const;
};
class BuildListInfo
{
    friend class InGameUI;

public:
    const Coord3D* getLocation() const { return &location; }
    float getAngle() const { return angle; }
    BuildListInfo();
    AsciiString buildingName, templateName;
    Coord3D location;
    Coord2D rally;
    float angle;
    char tail[0x80 - 0x24];

protected:
    virtual ~BuildListInfo();
};
class Rva00396A5C
{
public:
    int rva00396A5C(Player*);
};
class SidesList
{
public:
    bool rva0032BD25(int, int, BuildListInfo*);
};
extern SidesList* TheSidesList;
class TerrainLogic
{
public:
    virtual void slot0();
    virtual void slot4();
    virtual void slot8();
    virtual void slotC();
    virtual void slot10();
    virtual void slot14();
    virtual float getGroundHeight(float, float, void*);
};
extern TerrainLogic* TheTerrainLogic;
class G00DFF080Obj
{
public:
    virtual void slot0();
    virtual void slot4();
    virtual void slot8();
    virtual void slotC();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void addFactionBibDrawable(Drawable*, bool, float);
    virtual void removeFactionBibDrawable(Drawable*);
    virtual void removeAllBibs();
};
extern G00DFF080Obj* TheTerrainVisual;
class GhostObjectManager
{
public:
    __forceinline int getLocalPlayerIndex() const { return playerIndex; }
    void* vtable;
    int playerIndex;
};
extern GhostObjectManager* TheGhostObjectManager;
bool Rva0030596CIntersects(void*, PlaceCoord, float);
float normalizeAngle(float);
struct CommandButton
{
    char unknown00[0x1c];
    unsigned command;
};
struct PlaceIcon
{
    Drawable* drawable;
    float angle;
};
class InGameUI
{
public:
    virtual void slot0();
    virtual void slot4();
    virtual void slot8();
    virtual void slotC();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6C();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual void slot7C();
    virtual void slot80();
    virtual void slot84();
    virtual void slot88();
    virtual void slot8C();
    virtual void slot90();
    virtual void slot94();
    virtual void slot98();
    virtual void slot9C();
    virtual void slotA0();
    virtual void slotA4();
    virtual void slotA8();
    virtual void slotAC();
    virtual void slotB0();
    virtual void slotB4();
    virtual void slotB8();
    virtual void slotBC();
    virtual CommandButton* getPendingCommand();
    virtual void slotC4();
    virtual void slotC8();
    virtual void slotCC();
    virtual void slotD0();
    virtual void slotD4();
    virtual void slotD8();
    virtual void slotDC();
    virtual void slotE0();
    virtual ObjectID getPendingPlaceSourceObjectID();
    virtual void slotE8();
    virtual void slotEC();
    virtual bool isPlacementAnchored();
    virtual void getPlacementPoints(ICoord2D*, ICoord2D*);
    virtual void slotF8();
    virtual bool canPlacePort();
    virtual void setCanPlacePort(bool);

protected:
    void handleBuildPlacements();

public:
    char unknown04[0x53c - 4];
    const ThingTemplate* pendingType;
    void* unknown540;
    PlaceIcon* icons;
    char unknown548[0x554 - 0x548];
    bool useFeedbackPoint;
    char unknown555[3];
    ICoord2D feedbackPoint;
    char unknown560[0x574 - 0x560];
    FeedbackParams resourcePoint;
    Rva0029B5FD feedback;
    char unknown58c[0x9c8 - 0x58c];
    int feedbackState;

protected:
    void setMouseCursor(Mouse::MouseCursor);
};
// ?handleBuildPlacements@InGameUI@@IAEXXZ
void InGameUI::handleBuildPlacements()
{
    TheMouse->setMouseText(UnicodeString::TheEmptyString, 0, 0);
    Object* builder = TheGameLogic->findObjectByID(getPendingPlaceSourceObjectID());
    if (!builder || (!builder->getTemplate()->hasKind(14) && !builder->getTemplate()->hasKind(156)))
        return;
    if (!pendingType)
        return;
    bool isPort = TheBuildAssistant->isBuildPort(pendingType, builder);
    const ModuleData* castle = pendingType->rva0033B3D7();
    ICoord2D loc;
    PlaceCoord world;
    float angle = icons[0].angle;
    if (isPlacementAnchored())
    {
        ICoord2D start, end;
        getPlacementPoints(&start, &end);
        loc = start;
        if (start.x != end.x || start.y != end.y)
        {
            PlaceCoord worldStart, worldEnd;
            TheTacticalView->screenToTerrain(&start, &worldStart);
            TheTacticalView->screenToTerrain(&end, &worldEnd);
            Coord2D v;
            v.x = worldEnd.x - worldStart.x;
            v.y = worldEnd.y - worldStart.y;
            angle = v.toAngle();
        }
    }
    else
    {
        const ICoord2D* mousePos = &TheMouse->pos;
        loc = *mousePos;
        if (feedbackState == 2)
        {
            feedbackState = 0;
            TerrainResourceManager* manager = TheGameLogic->getTerrainResourceManager();
            const TerrainResourceBehaviorModuleData* data = rva0029B9E5(pendingType);
            if (data && data->maxIncome > 0 && manager)
            {
                feedback.reset((Rva004E668E*)new PlaceTerrainResourceClaimantFeedback(
                    &resourcePoint, icons[0].drawable, data));
                ((ResourceEntryCollector*)&BfmeUiResourceEntryCollectorState)->rva004E551E();
                int mask = 0;
                if (ThePlayerList && ThePlayerList->local)
                    mask = ThePlayerList->getPlayersWithRelationship(
                        ThePlayerList->local->getPlayerIndex(), 3, false);
                manager->enumerateRegisteredClaimants(
                    mask, (Cb00359D42*)&BfmeUiResourceEntryCollectorState);
                ((Rva004E54B8*)&BfmeUiResourceEntryCollectorState)->rva004E54B8();
            }
        }
        if (isPort)
        {
            if (!canPlacePort())
            {
                setCanPlacePort(true);
                ((Rva0029A94F*)this)->rva0029A94F();
            }
            else
            {
                unsigned int last = TheWritableGlobalData->maxLineBuildObjects - 1;
                if (feedbackState == 1)
                {
                    feedbackState = 0;
                    SpecialPowerModule* module
                        = (SpecialPowerModule*)((Rva00293330*)builder)
                              ->rva00293330(
                                  getPendingCommand() ? getPendingCommand()->command : 0xfffffe);
                    if (module)
                    {
                        _STL::vector<Coord3D> positions;
                        float radius = 0;
                        if (module->getRadius(&radius))
                        {
                            Player* player = builder->getControllingPlayer();
                            if (player)
                            {
                                int color = player->color;
                                player->rva002AF614(&positions);
                                ((ResourceEntryCollector*)&BfmeUiResourceEntryCollectorState)
                                    ->rva004E551E();
                                for (_STL::vector<Coord3D>::iterator it = positions.begin();
                                    it != positions.end(); ++it)
                                    ((ResourceEntryCollector*)&BfmeUiResourceEntryCollectorState)
                                        ->addEntry(&*it, radius, color);
                                ((Rva004E54B8*)&BfmeUiResourceEntryCollectorState)->rva004E54B8();
                            }
                        }
                    }
                }
                PlaceCoord builderPos(builder->position), mouseWorld;
                TheTacticalView->screenToTerrain(&loc, &mouseWorld);
                unsigned command = 0xfffffe;
                CommandButton* button = getPendingCommand();
                if (button)
                    command = button->command;
                Rva0039205C info;
                bool portResult = TheBuildAssistant->getBuildPortData(
                    &info, builder, &builderPos, &mouseWorld, command);
                if (!portResult)
                {
                    for (int i = 0; i < TheWritableGlobalData->maxLineBuildObjects; ++i)
                    {
                        if (!icons[i].drawable)
                        {
                            if (icons[last].drawable)
                            {
                                ((Rva002707FA*)icons[last].drawable)->rva002707FA(0);
                                icons[last].drawable->setDrawableHidden(true);
                            }
                            break;
                        }
                        ((Rva002707FA*)icons[i].drawable)->rva002707FA(0);
                        icons[i].drawable->setDrawableHidden(true);
                    }
                    return;
                }
                UnicodeString text;
                text.format((const unsigned short*)L"%d", info.cost);
                RGBAColorInt color = { { 32, 255, 128, 255 } }, shadow = { { 0, 0, 0, 255 } };
                TheMouse->setMouseText(text, &color, &shadow);
                RGBColor tint = illegalBuildColor;
                switch (info.status)
                {
                case 0:
                    setMouseCursor(Mouse::CURSOR_BUILD);
                    break;
                case 10:
                    setMouseCursor(Mouse::CURSOR_BUILD);
                    tint.green = tint.red = tint.blue = 0.5f;
                    if (TheGameClient->getFrame() & 4)
                        tint.green = 1.3f;
                    break;
                case 9:
                    setMouseCursor(Mouse::CURSOR_INVALID);
                    tint.red = 0;
                    if (TheGameClient->getFrame() & 4)
                        tint.blue = 1.7f;
                    break;
                case 7:
                    setMouseCursor(Mouse::CURSOR_INVALID);
                    tint.red = 0;
                    if (TheGameClient->getFrame() & 4)
                        tint.green = 1.0f;
                    break;
                default:
                    setMouseCursor(Mouse::CURSOR_INVALID);
                    if (TheGameClient->getFrame() & 4)
                        tint.green = 0.8f;
                    break;
                }
                int count
                    = (unsigned)(TheWritableGlobalData->maxLineBuildObjects - 1) < info.count - 1
                    ? (TheWritableGlobalData->maxLineBuildObjects - 1)
                    : info.count - 1;
                if (info.status == 10)
                    ++count;
                for (int i = 0; i < count; ++i)
                {
                    if (icons[i].drawable
                        && !icons[i].drawable->getTemplate()->isEquivalentTo(
                            (const ThingTemplate*)info.rva00392CC5(i)))
                    {
                        TheGameClient->destroyDrawable(icons[i].drawable);
                        icons[i].drawable = 0;
                    }
                    if (!icons[i].drawable)
                    {
                        const ThingTemplate* type = (const ThingTemplate*)info.rva00392CC5(i);
                        if (type)
                            icons[i].drawable
                                = (Drawable*)TheThingFactory->newDrawable((void*)type, 8, -1);
                        if (!icons[i].drawable)
                            continue;
                    }
                    icons[i].drawable->setPosition((const Coord3D*)info.rva00392CF9(i));
                    icons[i].drawable->opacity = 0.45f;
                    icons[i].drawable->setOrientation(info.rva00392D1D(i));
                    icons[i].angle = info.rva00392D1D(i);
                    ((Rva002707FA*)icons[i].drawable)->rva002707FA(1);
                    icons[i].drawable->setDrawableHidden(false);
                    icons[i].drawable->rva002791E7(
                        (const ModelConditionFlags&)Rva0028F59A(0, 108), 1, 0);
                    if (info.status == 10)
                        icons[i].drawable->colorTint(&tint);
                    else if (info.rva00392D71(i))
                        icons[i].drawable->colorTint(&tint);
                    else if (info.status != 0)
                        icons[i].drawable->colorTint(&illegalBuildColor);
                    else
                        icons[i].drawable->colorTint(0);
                }
                if (icons[last].drawable
                    && !icons[last].drawable->getTemplate()->isEquivalentTo(
                        (const ThingTemplate*)info.rva00392CC5(count)))
                {
                    TheGameClient->destroyDrawable(icons[last].drawable);
                    icons[last].drawable = 0;
                }
                if (!icons[last].drawable)
                {
                    const ThingTemplate* type = (const ThingTemplate*)info.rva00392CC5(count);
                    if (type)
                        icons[last].drawable
                            = (Drawable*)TheThingFactory->newDrawable((void*)type, 8, -1);
                }
                if (icons[last].drawable)
                {
                    icons[last].drawable->setPosition((const Coord3D*)info.rva00392CF9(count));
                    icons[last].drawable->opacity = 0.45f;
                    icons[last].drawable->setOrientation(info.rva00392D1D(count));
                    icons[last].drawable->setDrawableHidden(false);
                    ((Rva002707FA*)icons[last].drawable)->rva002707FA(1);
                    icons[last].angle = info.rva00392D1D(count);
                    if (info.rva00392D71(count))
                        icons[last].drawable->colorTint(&tint);
                    else if (info.status != 0)
                        icons[last].drawable->colorTint(&illegalBuildColor);
                    else
                        icons[last].drawable->colorTint(0);
                }
                for (int i = ((count - 1 >= 0) ? count - 1 : 0) + 1;
                    i < TheWritableGlobalData->maxLineBuildObjects - 1; ++i)
                {
                    if (!icons[i].drawable)
                    {
                        const ThingTemplate* type = (const ThingTemplate*)info.rva00392CC5(i);
                        if (type)
                            icons[i].drawable
                                = (Drawable*)TheThingFactory->newDrawable((void*)type, 8, -1);
                    }
                    if (icons[i].drawable)
                    {
                        ((Rva002707FA*)icons[i].drawable)->rva002707FA(0);
                        icons[i].drawable->setDrawableHidden(true);
                        icons[i].drawable->setPositionZ(-5000.0f);
                    }
                }
            }
        }
    }
    TheTacticalView->screenToTerrain(&loc, &world);
    float displayAngle = angle;
    if (castle)
    {
        int i = 0;
        BuildListInfo info;
        int side = ((Rva00396A5C*)castle)->rva00396A5C(builder->getControllingPlayer());
        while (TheSidesList->rva0032BD25(side, i++, &info))
        {
            const ThingTemplate* type
                = TheThingFactory->findTemplate(((TerrainType*)&info)->getTexture());
            if (!type)
                continue;
            if (icons[i].drawable && !icons[i].drawable->getTemplate()->isEquivalentTo(type))
            {
                TheGameClient->destroyDrawable(icons[i].drawable);
                icons[i].drawable = 0;
            }
            if (!icons[i].drawable)
                icons[i].drawable = (Drawable*)TheThingFactory->newDrawable((void*)type, 8, -1);
            if (!icons[i].drawable)
                continue;
            Matrix3D matrix(true);
            Vector3 center(world.x, world.y, world.z);
            matrix.In_Place_Pre_Rotate_Z(angle);
            matrix.Set_Translation(center);
            Vector3 v(info.getLocation()->x, info.getLocation()->y, info.getLocation()->z);
            Matrix3D::Transform_Vector(matrix, v, &v);
            PlaceCoord pos;
            pos.x = v.X;
            pos.y = v.Y;
            pos.z = v.Z;
            pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y, 0);
            float buildingAngle = angle;
            buildingAngle += info.getAngle();
            buildingAngle = normalizeAngle(displayAngle);
            icons[i].drawable->setPosition(&pos);
            // Preserve this distinct pointer read after setPosition. MSVC 7.1 otherwise
            // commutes the address operands at native 0x002A2DD2. This qualifier belongs
            // to this access; the Drawable pointer field itself is not declared volatile.
            ((Drawable* volatile&)icons[i].drawable)->opacity = 0.45f;
            icons[i].drawable->setOrientation(displayAngle);
            icons[i].angle = buildingAngle;
            ((Rva002707FA*)icons[i].drawable)->rva002707FA(1);
            icons[i].drawable->setDrawableHidden(false);
            icons[i].drawable->rva002791E7((const ModelConditionFlags&)Rva0028F59A(0, 108), 1, 0);
        }
        for (; i < TheWritableGlobalData->maxLineBuildObjects; ++i)
            if (icons[i].drawable)
            {
                TheGameClient->destroyDrawable(icons[i].drawable);
                icons[i].drawable = 0;
            }
    }
    if (pendingType->hasKind(188))
    {
        float newAngle = 0;
        PlaceCoord newWorld;
        newWorld.z = newWorld.y = newWorld.x = 0;
        if (TheBuildAssistant->getPortTransform(&world, pendingType, angle, &newAngle, &newWorld))
        {
            displayAngle = newAngle;
            world = newWorld;
        }
    }
    if (isPort)
        return;
    if (!icons[0].drawable)
        return;
    icons[0].angle = angle;
    icons[0].drawable->setPosition(&world);
    icons[0].drawable->setOrientation(displayAngle);
    if (feedbackState == 1)
    {
        feedbackState = 0;
        const ModuleData* data = pendingType->rva0033B427(0);
        if (data)
        {
            _STL::vector<Coord3D> positions;
            float radius = data->placementRadius;
            Player* player = builder->getControllingPlayer();
            if (player)
            {
                int color = player->color;
                player->rva002AF614(&positions);
                ((ResourceEntryCollector*)&BfmeUiResourceEntryCollectorState)->rva004E551E();
                for (_STL::vector<Coord3D>::iterator it = positions.begin(); it != positions.end();
                    ++it)
                    ((ResourceEntryCollector*)&BfmeUiResourceEntryCollectorState)
                        ->addEntry(&*it, radius, color);
                ((Rva004E54B8*)&BfmeUiResourceEntryCollectorState)->rva004E54B8();
            }
        }
    }
    if (feedback.ptr)
    {
        feedback.ptr->rva004E6693(useFeedbackPoint ? &feedbackPoint : 0);
        ((Rva004E63DB*)feedback.ptr)->rva004E63DB();
    }
    if (TheGameClient->getFrame() & 1)
    {
        TheTerrainVisual->removeAllBibs();
        bool anyIllegal = false;
        for (int i = 0; i < TheWritableGlobalData->maxLineBuildObjects; ++i)
        {
            if (!icons[i].drawable)
                continue;
            int code = 0;
            if (castle)
            {
                const ThingTemplate* type = icons[i].drawable->getTemplate();
                if (type && type->hasKind(120))
                {
                    code = TheBuildAssistant->isLocationLegalToBuild(
                        icons[i].drawable->getPosition(), icons[i].drawable->getTemplate(),
                        icons[i].angle, 0x48f, builder, 0);
                    if (code != 0)
                        anyIllegal = true;
                }
            }
            else
                code = TheBuildAssistant->isLocationLegalToBuild(icons[i].drawable->getPosition(),
                    icons[i].drawable->getTemplate(), icons[i].angle, 0x48f, builder, 0);
            if (TheGhostObjectManager->getLocalPlayerIndex()
                    == builder->getControllingPlayer()->getPlayerIndex()
                && Rva0030596CIntersects((void*)icons[i].drawable->getTemplate(),
                    *icons[i].drawable->getPosition(), icons[i].angle))
                code = 8;
            if (code != 0)
            {
                if (code == 9)
                {
                    RGBColor tint = { 0, 0, 0.5f };
                    if (TheGameClient->getFrame() & 4)
                        tint.blue = 1.7f;
                    icons[i].drawable->colorTint(&tint);
                }
                else
                    icons[i].drawable->colorTint(&illegalBuildColor);
            }
            else if (anyIllegal)
                icons[i].drawable->colorTint(&illegalBuildColor);
            else
                icons[i].drawable->colorTint(0);
            if (code != 0)
                TheTerrainVisual->addFactionBibDrawable(icons[i].drawable, code != 0 && code != 9, 0);
            else
                TheTerrainVisual->removeFactionBibDrawable(icons[i].drawable);
        }
    }
}
