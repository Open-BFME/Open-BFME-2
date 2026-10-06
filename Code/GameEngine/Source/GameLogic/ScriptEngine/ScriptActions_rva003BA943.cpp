// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ScriptActions::rva003BA943, retail 0x003BA943 (44B): the unit resolved
// from its parameter by the rowed getUnitNamed hands the flag to its
// drawable (pinned Object::getDrawable 0x005508E2) through the Drawable
// method 0x002785FB (stores the flag at +0x448; pinned from this call).
class Drawable
{
public:
    void rva002785FB(bool flag);
};

class Object
{
public:
    Drawable *getDrawable() const;
};

class Parameter;

class ScriptEngine
{
public:
    Object *getUnitNamed(Parameter *unitParam);
};
extern class ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
    void rva003BA943(Parameter *pUnit, bool flag);
};

void ScriptActions::rva003BA943(Parameter *pUnit, bool flag)
{
    Object *obj = TheScriptEngine->getUnitNamed(pUnit);
    if (!obj)
        return;
    Drawable *draw = obj->getDrawable();
    if (!draw)
        return;
    draw->rva002785FB(flag);
}
