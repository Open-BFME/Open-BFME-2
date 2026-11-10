// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -GX -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?doSetWarehouseValue@ScriptActions@@QAEXABVAsciiString@@H@Z @0x003C0E87 130B: lookup unit by value
// then SupplyWarehouseDockUpdate module int dispatch via cached NameKey.
// Evidence: rowed lookupUnitByValue 0x358752 via TheScriptEngine (0x9FE16C), nameToKey PBD
// 0x148E1A via TheNameKeyGenerator, findModule 0x28B6D6, StringBase copy
// 0x365F0, rowed 0x004A7F78 int member, globals TheScriptEngine plus statics,
// SupplyWarehouseDockUpdate literal at 0xBF507C; caller sibling 0x003C3175
// ret 0x8 stdcall.
#include "ascii_string.h"

enum NameKeyType { NK_NONE = 0 };

class Object;
class SupplyWarehouseDockUpdate
{
public:
    void rva004A7F78(int v);
};
#include "../../../Include/Common/Module.h"

class Object
{
protected:
    Module *findModule(NameKeyType key) const;
    friend void ScriptActions::doSetWarehouseValue(const AsciiString &, int);
};

#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../Include/GameLogic/Rva00358752Opaque.h"
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

void ScriptActions::doSetWarehouseValue(const AsciiString &name, int count)
{
    Object *obj = ((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue((AsciiString &)name);
    if (obj == 0)
        return;
    static NameKeyType supplyKey = TheNameKeyGenerator->nameToKey("SupplyWarehouseDockUpdate");
    Module *module = obj->findModule(supplyKey);
    if (module == 0)
        return;
    ((SupplyWarehouseDockUpdate *)module)->rva004A7F78(count);
}
