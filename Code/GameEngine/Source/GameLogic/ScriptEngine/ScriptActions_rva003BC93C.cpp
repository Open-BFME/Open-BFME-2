// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// Two single-unit script actions on the unit's +0x264 object (the unit
// resolved from its parameter by the rowed getUnitNamed); its two methods
// are pinned from these calls, identities unknown.
//   0x003BD306 (37B): hands the int argument to 0x0039B28F (no null check).
//   0x003BC93C (51B): when the +0x264 object exists, hands it the int
//                     argument as a float with true to 0x0039B3D1.
class Rva003BD306Target
{
public:
    void rva0039B28F(int value);
    void rva0039B3D1(float value, bool flag);
};

class Object
{
public:
    Rva003BD306Target *m_264Get() const { return m_264; }
private:
    unsigned char m_pad[0x264];
    Rva003BD306Target *m_264; // +0x264
};

class Parameter;

class ScriptEngine
{
public:
    Object *getUnitNamed(Parameter *unitParam);
};
extern ScriptEngine *g_Va009FE16C;

class ScriptActions
{
protected:
    void rva003BC93C(Parameter *pUnit, int value);
    void rva003BD306(Parameter *pUnit, int value);
};

void ScriptActions::rva003BC93C(Parameter *pUnit, int value)
{
    Object *obj = g_Va009FE16C->getUnitNamed(pUnit);
    if (!obj)
        return;
    Rva003BD306Target *target = obj->m_264Get();
    if (!target)
        return;
    target->rva0039B3D1((float)value, true);
}

void ScriptActions::rva003BD306(Parameter *pUnit, int value)
{
    Object *obj = g_Va009FE16C->getUnitNamed(pUnit);
    if (!obj)
        return;
    obj->m_264Get()->rva0039B28F(value);
}
