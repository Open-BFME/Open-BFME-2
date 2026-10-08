// ??0LivingWorldBuildPlot@@QAE@HPAVLivingWorldRegion@@ABVCoord2D@@@Z
// partial score=0.91 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// WorldBuilder 0x01311550 names LivingWorldBuildPlot::CreateIcon and
// 0x014D96C0 names its icon constructor. Retail 0x004FC185..0x004FC207
// proves the lookup, 0x3C allocation, position reference at +0x28, owning
// holder at +0x24, and slot +0x20 receiving (structure != 0, true).
// The remaining class fields and virtual-slot identities are unrecovered.
#include "ascii_string.h"
#include "string_base.h"
// Retail omits the abstract Snapshot constructor vptr store.
class __declspec(novtable) Snapshot;
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include <stdlib.h>
#include "../../../../../Libraries/Include/Lib/Coord2D.h"

class Object;
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
class Rva00213148
{
public:
    void *rva00213148(const AsciiString *key);
};
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
class Rva000AD6F4
{
public:
    void clear();
};
class Rva00575674
{
public:
    Rva00575674() : m_icon(0) {}
    ~Rva00575674() { ((Rva000AD6F4 *)this)->clear(); }
    void rva00575674(Object *object);
    LivingWorldBuildPlotIcon *get() const { return m_icon; }
    bool isBound() const { return m_icon != 0; }
private:
    LivingWorldBuildPlotIcon *m_icon;
};
// Retail constructs this non-polymorphic list before the secondary
// polymorphic base. MSVC places the latter at +4 and this list at +8.
class Rva00330757Member
{
public:
    Rva00330757Member();
    ~Rva00330757Member() { if (m_begin) free(m_begin); }
private:
    void *m_begin, *m_end, *m_capacity;
    int m_index;
};
class LivingWorldPhaseObserver
{
public:
    LivingWorldPhaseObserver() {}
    ~LivingWorldPhaseObserver() {}
    virtual void slot00(int, int) {}
    virtual void slot04(int, int) {}
};
class LivingWorldBuildPlot : public Snapshot, public Rva00330757Member,
                            public LivingWorldPhaseObserver
{
public:
    LivingWorldBuildPlot(int id, LivingWorldRegion *region, const Coord2D &position);
    virtual ~LivingWorldBuildPlot();
    virtual void loadPostProcess();
    virtual void crc(Xfer *xfer);
    virtual void xfer(Xfer *xfer);
    virtual void slot00(int, int);
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

void LivingWorldBuildPlot::CreateIcon(const AsciiString &iconName)
{
    if (((const StringBase<char> *)&iconName)->isEmpty())
        return;
    LivingWorldBuildPlotIconTemplate *templ = (LivingWorldBuildPlotIconTemplate *)
        ((Rva00213148 *)TheLivingWorldManager)->rva00213148(&iconName);
    if (templ)
    {
        m_icon.rva00575674((Object *)new LivingWorldBuildPlotIcon(templ, this, m_position));
        m_icon.get()->slot20(m_building.isBound(), true);
    }
}

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
class Rva002B315BBumpCounter
{
public:
    int bump();
};
class LivingWorldBuilding
{
public:
    LivingWorldBuilding(LivingWorldRegion *region, const Coord2D &position,
                       const Rva003F1BD3TemplateView *templ, int id);
private:
    char m_unrecovered[0x54];
};
class Rva004E0705
{
public:
    bool rva004E0A58();
};
class Rva004FC320Listener
{
public:
    virtual void notify(void *arg);
};
class Rva004FC320List
{
public:
    void forEach(void (Rva004FC320Listener::*notify)(void *), void *arg);
private:
    char m_storage[0x10];
};
struct TreeHintRef00217D4C;
class Rva001FF3A9
{
public:
    void rva001FF3A9(const TreeHintRef00217D4C &arg);
};
class Rva003F1C56Plot
{
public:
    void rva004FC33E(const Rva003F1BD3TemplateView *templ);
private:
    char m_unknown00[8];
    Rva004FC320List m_listeners;
    int m_unknown18;
    LivingWorldRegion *m_region;
    Rva00575674 m_building;
    Rva00575674 m_icon;
    Coord2D m_position;
    int m_buildFrames;
    bool m_hidden;
};

void Rva003F1C56Plot::rva004FC33E(const Rva003F1BD3TemplateView *templ)
{
    if (m_building.isBound())
        return;
    m_building.rva00575674((Object *)new LivingWorldBuilding(m_region, m_position,
        templ, ((Rva002B315BBumpCounter *)TheLivingWorldLogic)->bump()));
    bool pending = ((Rva004E0705 *)m_building.get())->rva004E0A58();
    m_buildFrames = templ->m_buildFrames;
    m_hidden = true;
    if (m_icon.get())
        m_icon.get()->slot24(pending, true);
    m_listeners.forEach((void (Rva004FC320Listener::*)(void *))
        &Rva001FF3A9::rva001FF3A9, this);
}

class Rva004E0B60
{
public:
    void rva004E0CB6();
};

// WorldBuilder 0x01311A50; native 0x004FC3DC..0x004FC470 RET4.
void LivingWorldBuildPlot::ConstructBuildingImmediately(const Rva003F1BD3TemplateView *templ)
{
    if (m_building.isBound())
        return;
    m_building.rva00575674((Object *)new LivingWorldBuilding(m_region, m_position,
        templ, ((Rva002B315BBumpCounter *)TheLivingWorldLogic)->bump()));
    ((Rva004E0B60 *)m_building.get())->rva004E0CB6();
    m_buildFrames = 0;
    m_hidden = false;
    if (m_icon.get())
        m_icon.get()->slot24(false, true);
    ((Rva004FC320List *)((char *)this + 8))->forEach(
        (void (Rva004FC320Listener::*)(void *))&Rva001FF3A9::rva001FF3A9, this);
}

// WorldBuilder 0x013111B0 establishes the constructor and phase-observer
// relationship. Retail 0x004FC807..0x004FC8B3 establishes all offsets,
// initialization order, owner lookup and the secondary-base registration.
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
class Rva002BA8F1Logic
{
public:
    Rva002E2903Player *find(int id, unsigned int *index);
};
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
        (Rva002BA8F1Listener *)(LivingWorldPhaseObserver *)this);
}
