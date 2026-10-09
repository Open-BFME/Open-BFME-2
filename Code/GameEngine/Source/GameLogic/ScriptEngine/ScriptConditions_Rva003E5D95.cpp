// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva003E5D95@ScriptConditions@@IAEEPAVParameter@@PAUCond003E5D95@@@Z
// @0x003E5D95 56B. Leaf via rowed ScriptEngine::getUnitNamed 0x003588E7
// via g_Va009FE16C; Object+4 inner +0x118 bit27 vs second param +8 int.
class Parameter
{
};

struct Cond003E5D95
{
    char m_pad[8];
    int m_value;
};

class Inner003E5D95
{
public:
    char m_pad[0x118];
    unsigned int m_flags;
};

class Object
{
public:
    char m_pad[4];
    Inner003E5D95 *m_inner;
};

class ScriptEngine
{
public:
    Object *getUnitNamed(Parameter *p);
};

extern class ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	unsigned char rva003E5D95(Parameter *param, Cond003E5D95 *cond);
};

unsigned char ScriptConditions::rva003E5D95(Parameter *param, Cond003E5D95 *cond)
{
    Object *obj = TheScriptEngine->getUnitNamed(param);
    if (!obj)
        return 0;
    unsigned int flags = obj->m_inner->m_flags;
    unsigned char flag = (unsigned char)((flags >> 27) & 1);
    unsigned char expected = (unsigned char)(cond->m_value != 0);
    return flag == expected;
}
