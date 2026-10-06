// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
// ?Rva003C0E87Do@@YGXABVAsciiString@@H@Z @0x003C0E87 130B: lookup unit by value
// then SupplyWarehouseDockUpdate module int dispatch via cached NameKey.
// Evidence: rowed lookupUnitByValue 0x358752 via g_Va009FE16C, nameToKey PBD
// 0x148E1A via TheNameKeyGenerator, findModule 0x28B6D6, StringBase copy
// 0x365F0, rowed 0x004A7F78 int member, globals g_Va009FE16C plus statics,
// SupplyWarehouseDockUpdate literal at 0xBF507C; caller sibling 0x003C3175
// ret 0x8 stdcall.
#include "ascii_string.h"

enum NameKeyType { NK_NONE = 0 };

class Object;
class Rva004A7D55
{
public:
    void rva004A7F78(int v);
};
class Module
{
public:
    char m_pad00[0x20];
    unsigned char m_20;
};

class Object
{
protected:
    Module *findModule(NameKeyType key) const;
    friend void __stdcall Rva003C0E87Do(const AsciiString &, int);
};

class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Rva00358752Opaque
{
public:
    Object *lookupUnitByValue(AsciiString name);
};
extern Rva00358752Opaque *g_Va009FE16C;

void __stdcall Rva003C0E87Do(const AsciiString &name, int count)
{
    Object *obj = g_Va009FE16C->lookupUnitByValue((AsciiString &)name);
    if (obj == 0)
        return;
    static NameKeyType supplyKey = TheNameKeyGenerator->nameToKey("SupplyWarehouseDockUpdate");
    Module *module = obj->findModule(supplyKey);
    if (module == 0)
        return;
    ((Rva004A7D55 *)module)->rva004A7F78(count);
}
