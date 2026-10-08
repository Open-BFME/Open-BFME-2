// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// WorldBuilder 0x01311550 names LivingWorldBuildPlot::CreateIcon and
// 0x014D96C0 names its icon constructor. Retail 0x004FC185..0x004FC207
// proves the lookup, 0x3C allocation, position reference at +0x28, owning
// holder at +0x24, and slot +0x20 receiving (structure != 0, true).
// The remaining class fields and virtual-slot identities are unrecovered.
#include "ascii_string.h"
#include "string_base.h"
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
class Rva00575674
{
public:
    void rva00575674(Object *object);
    LivingWorldBuildPlotIcon *get() const { return m_icon; }
    bool isBound() const { return m_icon != 0; }
private:
    LivingWorldBuildPlotIcon *m_icon;
};
class LivingWorldBuildPlot
{
public:
    void CreateIcon(const AsciiString &iconName);
private:
    char m_unrecovered[0x20];
    void *m_structure;
    Rva00575674 m_icon;
    Coord2D m_position;
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
        m_icon.get()->slot20(m_structure != 0, true);
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
