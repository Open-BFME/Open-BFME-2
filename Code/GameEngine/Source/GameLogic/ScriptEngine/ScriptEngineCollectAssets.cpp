// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// BF1 f989 Rva0033CA50CollectScriptAssets supplies traversal; native205358
// supplies BFME2 side count3C, embedded pool8, receiver chains10/14.
class AssetList;
struct AssetLoadMode;
class Script
{
public:
    void rva003B3836(AssetList *assets, AssetLoadMode *mode);
private:
    char beforeActions[0x34];
    void *actions[2];
};
struct Rva00205358Chain;
class ScriptEngine
{
public:
    void rva00205358(AssetList *assets, AssetLoadMode *mode);
private:
    char beforeChains[0x10];
    Rva00205358Chain **chainsBegin;
    Rva00205358Chain **chainsEnd;
};

class Rva00205358PooledScript
{
public:
    Script *getScript() { return &script; }
private:
    void *head;
    Script script;
};
struct Rva00205358PoolNode
{
    int next;
    char unknown[12];
    Rva00205358PooledScript *value;
};
struct Rva00205358ScriptPool
{
    char beforeNodes[0x38];
    Rva00205358PoolNode *nodes;
    char beforeHead[12];
    int head;
};
class SidesInfo
{
public:
    Rva00205358ScriptPool *getScripts() { return &scripts; }
private:
    char beforeScripts[8];
    Rva00205358ScriptPool scripts;
};
class SidesList
{
public:
    __declspec(noinline) SidesInfo *getSideInfo(int index)
    {
        if (index >= 0 && index < count)
            return (SidesInfo *)(sides + index * 0x60);
        return 0;
    }
    int getNumSides() const { return count; }
private:
    char beforeCount[0x3C];
    int count;
    char sides[0x60];
};
extern SidesList *TheSidesList;
struct Rva00205358Chain
{
    char beforeScript[0x14];
    Script *script;
    char beforeNext[0x10];
    Rva00205358Chain *next;
};
// Target205358 proves the pool and chain offsets; BF1 supplies traversal.
void ScriptEngine::rva00205358(AssetList *assets, AssetLoadMode *mode)
{
    for (int side = 0; side < TheSidesList->getNumSides(); ++side)
    {
        Rva00205358ScriptPool *pool = TheSidesList->getSideInfo(side)->getScripts();
        if (pool == 0)
            continue;
        for (int index = pool->head; index != -1; index = pool->nodes[index].next)
        {
            Script *script = pool->nodes[index].value->getScript();
            if (script)
                script->rva003B3836(assets, mode);
        }
    }
    for (Rva00205358Chain **it = chainsBegin; it != chainsEnd; ++it)
        for (Rva00205358Chain *chain = *it; chain; chain = chain->next)
            if (chain->script)
                chain->script->rva003B3836(assets, mode);
}
