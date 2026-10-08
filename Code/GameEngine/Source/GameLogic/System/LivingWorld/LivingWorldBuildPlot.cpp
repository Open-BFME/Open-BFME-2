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
private:
    char m_unrecovered[0x38];
};
class Rva00575674
{
public:
    void rva00575674(Object *object);
    LivingWorldBuildPlotIcon *get() const { return m_icon; }
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
