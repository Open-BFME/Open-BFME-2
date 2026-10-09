// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// BF1 f989 Rva00351040ScriptAssetList and Rva0033CA50CollectScriptAssets
// provide the action/team-asset traversal. Target3B3836 proves action heads
// 34/38, parameter8/C/string10 and target TeamPrototype template12C with
// unit names14/stride18/countAC/transport100. These layout facts are native,
// not copied from BF1. Target helper33CF34 still has only its neutral binding.
#include "ascii_string.h"
class AssetList;
struct AssetLoadMode;
class ThingTemplate;
class Rva0020AA00Target { public: void notify(int assets, int context); };
class ThingFactory
{
public:
    const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;
struct Rva003B3836Unit
{
    char unknown[16];
    AsciiString name;
    char trailing[4];
};
struct Rva003B3836TemplateInfo
{
    char unknown[4];
    Rva003B3836Unit units[7];
    int count;
    char beforeTransport[0x100 - 0xB0];
    AsciiString transport;
};
class TeamPrototype
{
public:
    Rva003B3836TemplateInfo *getTemplateInfo() { return &m_template; }
private:
    char beforeTemplate[0x12C];
    Rva003B3836TemplateInfo m_template;
};
class ScriptEngine
{
public:
    TeamPrototype *rva003570D1(AsciiString name);
};
extern ScriptEngine *TheScriptEngine;
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
private:
    char beforeString[16];
    AsciiString m_string;
};
class ScriptAction
{
private:
    void *vtable;
public:
    int type;
    Parameter *getParameter(int index) const
    {
        if (index >= 0 && index < count)
            return parameters[index];
        return 0;
    }
    ScriptAction *getNext() const { return next; }
private:
    int count;
    Parameter *parameters[12];
    ScriptAction *next;
};
class Script
{
public:
    void rva003B3836(AssetList *assets, AssetLoadMode *mode);
private:
    char beforeActions[0x34];
    ScriptAction *actions[2];
};
static __forceinline void CollectScriptAsset(const ThingTemplate *thing, AssetList *assets, AssetLoadMode *mode)
{
    if (thing)
        ((Rva0020AA00Target *)thing)->notify((int)assets, (int)mode);
}
void Script::rva003B3836(AssetList *assets, AssetLoadMode *mode)
{
    ScriptAction **slot = &actions[0];
    int remaining = 2;
    do
    {
        ScriptAction *action = *slot;
        while (action)
        {
            switch (action->type)
            {
            case 0x22:
            {
                TeamPrototype *team = TheScriptEngine->rva003570D1(action->getParameter(0)->getString());
                Rva003B3836TemplateInfo *info = team ? team->getTemplateInfo() : 0;
                if (info)
                {
                    if (!info->transport.isEmpty())
                        CollectScriptAsset(TheThingFactory->findTemplate(info->transport), assets, mode);
                    Rva003B3836Unit *unit = &info->units[0];
                    for (int index = 0; index < info->count; ++index, ++unit)
                        CollectScriptAsset(TheThingFactory->findTemplate(unit->name), assets, mode);
                }
                break;
            }
            case 0x28:
            case 0x139:
                CollectScriptAsset(TheThingFactory->findTemplate(action->getParameter(1)->getString()), assets, mode);
                break;
            case 0x17:
            case 0x29:
                CollectScriptAsset(TheThingFactory->findTemplate(action->getParameter(0)->getString()), assets, mode);
                break;
            }
            action = action->getNext();
        }
        ++slot;
    } while (--remaining);
}
