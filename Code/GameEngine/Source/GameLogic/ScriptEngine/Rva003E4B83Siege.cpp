// cl: /O1 /EHsc
// ?Rva003E4B83Get free @ 0x003E4B83 119B leaf from 0x003EBD81. Evidence:
// 1x Parameter ret 4; rowed getUnitNamed plus static SiegeDeploySpecialPower
// key via rowed nameToKey plus rowed findModule plus rowed bool getter
// ?get@Rva004C5772CmpBoolField@@QBE_NXZ; EH_prolog with static init.
class AsciiString;
enum NameKeyType
{
    NAMEKEY_INVALID = 0
};

class Parameter;
class Object;
class Module;

class ScriptEngine
{
public:
    Object *getUnitNamed(Parameter *parameter);
};
extern ScriptEngine *g_Va009FE16C;

class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Rva004C5772CmpBoolField
{
public:
    bool get() const;
};

class Module
{
public:
    virtual void moduleSlot();
};

class Object
{
    friend bool __stdcall Rva003E4B83Get(Parameter *);
protected:
    Module *findModule(NameKeyType key) const;
};

bool __stdcall Rva003E4B83Get(Parameter *pUnitParm)
{
    Object *obj = g_Va009FE16C->getUnitNamed(pUnitParm);
    if (obj == 0)
        return false;
    static NameKeyType siegeKey = TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
    Module *mod = obj->findModule(siegeKey);
    if (mod != 0)
        return ((Rva004C5772CmpBoolField *)mod)->get();
    return false;
}
