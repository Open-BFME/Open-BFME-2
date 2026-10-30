// cl: /O1 /DNDEBUG /MD /G7
// BFME 1 donor: Rva002E0E30RecordDispatch.cpp at
// 1399ad37d42ea52a63829e417c46a1ba9ed2cd20. The owning type and method remain
// address-derived. BFME 2 uses the rowed GameLogic::findObjectByID instead of
// the donor's inlined hash lookup, with 12-byte records at receiver +4/+8.
// Native 0x331ED1..0x331F2D is 92 bytes and returns with three stack words.
// Its Lua callback at 0x334860..0x334A38 was inspected in full: ECX is the
// named TheLuaScriptEngine, with opaque event data, Object and two more words.

class Object;
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class LuaScriptEngine
{
public:
    // 0x00334860 is rowed as LuaScriptEngine::DispatchSpyEvent (472B;
    // sibling of DispatchEvent); same (int, ptr, ptr, ptr) shape, so this
    // resolves to the rowed body instead of the unrowed spelling (sole U).
    void DispatchSpyEvent(int event, void *object, void *argument2,
        void *argument3);
};
extern LuaScriptEngine *TheLuaScriptEngine;

struct SpyEventObjectNode
{
    SpyEventObjectNode *next;
    SpyEventObjectNode *previous;
    ObjectID id;
};

struct Rva00331ED1Record
{
    int key;
    void *event;
    SpyEventObjectNode *sentinel;
};

class Rva00331ED1
{
public:
    void rva00331ED1(int key, void *argument2, void *argument3);
private:
    unsigned char prefix[4];
    Rva00331ED1Record *begin;
    Rva00331ED1Record *end;
};

// ?rva00331ED1@Rva00331ED1@@QAEXHPAX0@Z
void Rva00331ED1::rva00331ED1(int key, void *argument2, void *argument3)
{
    for (Rva00331ED1Record *record = begin; record != end; ++record)
    {
        if (record->key != key)
            continue;
        SpyEventObjectNode *node = record->sentinel->next;
        while (node != record->sentinel)
        {
            Object *object = TheGameLogic->findObjectByID(node->id);
            if (object)
                TheLuaScriptEngine->DispatchSpyEvent((int)record->event, object,
                    argument2, argument3);
            node = node->next;
        }
    }
}
