// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?doNamedEnableCameraFading@ScriptActions@@IAEXPAVParameter@@PAX@Z @ 0x003BBD02 (55B).
// Free-function wrapper: looks up Object via TheScriptEngine getUnitNamed
// Parameter row 0x003588E7 then double getDrawable Thing row 0x005508E2
// null-guarded then Drawable walk rva00273686 row 0x00273686 with void arg.
// Layout from callers plus sibling doNamedEnableStealth; ret 8 stdcall with
// Parameter plus void. Global g_Va009FE16C used by 14 TUs.
class Parameter;
class Drawable {
public:
    void rva00273686(void *arg);
};
class Thing {
public:
    Drawable *getDrawable() const;
};
class Object : public Thing {
};
class ScriptEngine {
public:
    Object *getUnitNamed(Parameter *p);
};
extern class ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doNamedEnableCameraFading(Parameter *p, void *arg);
};

void ScriptActions::doNamedEnableCameraFading(Parameter *p, void *arg)
{
    Object *obj = TheScriptEngine->getUnitNamed(p);
    if (!obj)
        return;
    if (!obj->getDrawable())
        return;
    obj->getDrawable()->rva00273686(arg);
}
