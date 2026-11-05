// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /O1 /DNDEBUG /MD /D_CRTIMP= /EHsc
// Split from LivingWorldBuildPlot.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// WorldBuilder 0x01311550 names LivingWorldBuildPlot::CreateIcon and
// 0x014D96C0 names its icon constructor. Retail 0x004FC185..0x004FC207
// proves the lookup, 0x3C allocation, position reference at +0x28, owning
// holder at +0x24, and slot +0x20 receiving (structure != 0, true).
// The remaining class fields and virtual-slot identities are unrecovered.
#include "ascii_string.h"
#include "string_base.h"
#include <stdlib.h>
#include "Lib/Coord2D.h"

#define BFME_SNAPSHOT_CONSTRUCTOR_ONLY
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

#include "../../../../Include/Common/Rva00330757Member.h"

#include "../../../../Include/Common/RegionTurnObserverView.h"
class Object;
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
class LivingWorldBuildPlot;
class LivingWorldBuildPlotIconTemplate;
class LivingWorldRegion;
struct Rva003F1BD3TemplateView;
class LivingWorldBuildPlotIcon
{
public:
    LivingWorldBuildPlotIcon(LivingWorldBuildPlotIconTemplate *templ,
                            LivingWorldBuildPlot *plot, const Coord2D &position);
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20(bool occupied, bool immediate);
    virtual void slot24(bool pending, bool immediate);
private:
    char m_unrecovered[0x38];
};
#include "../../../../Include/Common/Rva00575674.h"
class LivingWorldBuildPlot : public Snapshot, public Rva00330757Member,
                            public RegionTurnObserverView
{
public:
    LivingWorldBuildPlot(int id, LivingWorldRegion *region, const Coord2D &position);
    virtual ~LivingWorldBuildPlot();
    virtual void loadPostProcess() = 0;
    virtual void crc(Xfer *xfer) = 0;
    virtual void xfer(Xfer *xfer) = 0;
    virtual void BeginTurn(int, int);
    void CreateIcon(const AsciiString &iconName);
    void ConstructBuildingImmediately(const Rva003F1BD3TemplateView *templ);
private:
    int m_id;
    LivingWorldRegion *m_region;
    Rva00575674 m_building;
    Rva00575674 m_icon;
    Coord2D m_position;
    int m_buildFrames;
    bool m_hidden;
    bool m_unrecovered35;
};


// The existing callee pin names ConstructBuilding by its address-derived
// receiver. Keep that provider spelling; WorldBuilder 0x013118C0 supplies
// the source identity while retail alone supplies the fields below.
struct Rva003F1BD3TemplateView
{
    char m_unknown[0x28];
    int m_buildFrames;
};
class LivingWorldRegion;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct TreeHintRef00217D4C;
class LivingWorldRegion
{
public:
    char m_unrecovered[0x13C];
    int m_owner;
};
struct Rva004FC807PlayerTemplate
{
    char m_unrecovered[0x28];
    AsciiString m_iconName;
};
class Rva002E2903Player
{
public:
    char m_unrecovered[0x40];
    Rva004FC807PlayerTemplate *m_template;
};
#include "../../../../Include/GameLogic/Rva002BA8F1Logic.h"
struct Rva002BA8F1Listener;
class Rva005A0B4CList
{
public:
    void append(Rva002BA8F1Listener *listener);
};

LivingWorldBuildPlot::LivingWorldBuildPlot(int id, LivingWorldRegion *region,
                                         const Coord2D &position)
    : m_id(id), m_region(region), m_position(position), m_buildFrames(0),
      m_hidden(false), m_unrecovered35(false)
{
    int owner = m_region->m_owner;
    Rva002E2903Player *player = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(
        owner, 0);
    if (player)
        CreateIcon(player->m_template->m_iconName);
    ((Rva005A0B4CList *)((char *)TheLivingWorldLogic + 0x1C))->append(
        (Rva002BA8F1Listener *)(RegionTurnObserverView *)this);
}
