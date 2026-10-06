// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ScriptActions::doNamedCustomColor, retail 0x003BB596 (33B): Zero Hour's
// body - the unit by name (BFME2 resolves it from its parameter through the
// rowed getUnitNamed) gets the rowed Object::setCustomIndicatorColor, Zero
// Hour's only script caller of that setter.
class Object
{
public:
	void setCustomIndicatorColor(int color);
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
	void doNamedCustomColor(Parameter *unitParam, int color);
};

void ScriptActions::doNamedCustomColor(Parameter *unitParam, int color)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitParam);
	if (!obj)
		return;
	obj->setCustomIndicatorColor(color);
}
