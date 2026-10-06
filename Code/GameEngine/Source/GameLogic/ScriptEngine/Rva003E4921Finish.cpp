// ?rva003E4921@ScriptConditions@@QAE_NPAVParameter@@@Z
// cl: /EHsc
// ?rva003E4921@ScriptConditions@@QAE_NPAVParameter@@@Z
// @0x003E4921 151B gate condition via rowed getUnitNamed 0x003588E7 plus
// rowed nameToKey 0x00148E1A plus rowed findModule 0x0028B6D6.
// Evidence: vslot slot 17 of 0x00835B38; caller none; static
// GateOpenAndCloseBehavior key; donor BFME1 ScriptActionsGates.
// Each failing condition returns immediately so the false arm owns the
// fallthrough and the true arm becomes the forward jmp target, which is the
// polarity retail emits (jne over xor al,al to mov al,1).
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
extern ScriptEngine *TheScriptEngine;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Module
{
public:
	virtual void moduleSlot();
};

class Object
{
	friend class ScriptConditions;
protected:
	Module *findModule(NameKeyType key) const;
};

class GateOpenAndCloseBehaviorView
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual bool stateIsOne() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual bool isReady() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	int m_pad40[15];
	int m_state40;
};

class ScriptConditions
{
public:
	bool rva003E4921(Parameter *param);
};

bool ScriptConditions::rva003E4921(Parameter *param)
{
	Object *object = TheScriptEngine->getUnitNamed(param);
	if (!object)
		return false;
	static NameKeyType gateKey = TheNameKeyGenerator->nameToKey("GateOpenAndCloseBehavior");
	Module *module = object->findModule(gateKey);
	GateOpenAndCloseBehaviorView *gate = module ? (GateOpenAndCloseBehaviorView *)((char *)module - 4) : 0;
	if (gate == 0)
		return false;
	if (!gate->isReady())
		return false;
	bool result = gate->m_state40 <= 0 || gate->stateIsOne();
	return result;
}