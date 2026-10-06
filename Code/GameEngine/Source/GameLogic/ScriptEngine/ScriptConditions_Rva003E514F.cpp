// ?Rva003E514FCheck@@YG_NPAVParameter@@PAUCondA003E514F@@PAUCondB003E514F@@@Z
// retail 0x003E514F, 138 bytes.
// Evidence: leaf via rowed ScriptEngine::getUnitNamed plus ThePlayerList not needed; g_Va009FE16C ScriptEngine global; Object +0x264 ptr plus +0x24 value; op switch 0..5 to setl/setle/sete/setge/setg/setne.
// flags: region default (reverse/retail_inventory/flag_regions.csv)

class Parameter
{
};

class ObjectInner003E514F
{
public:
	char m_pad[0x24];
	int m_value;
};

class Object
{
public:
	char m_pad[0x264];
	ObjectInner003E514F *m_inner;
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
};

extern class ScriptEngine *TheScriptEngine;

struct CondA003E514F
{
	char m_pad[8];
	int m_op;
};

struct CondB003E514F
{
	char m_pad[8];
	int m_value;
};

bool __stdcall Rva003E514FCheck(Parameter *param, CondA003E514F *a, CondB003E514F *b)
{
	Object *obj = TheScriptEngine->getUnitNamed(param);
	if (!obj)
		return false;

	ObjectInner003E514F *inner = obj->m_inner;
	if (!inner)
		return false;

	int op = a->m_op;
	int count = inner->m_value;
	bool result;

	switch (op)
	{
	case 0:
		result = count < b->m_value;
		break;
	case 1:
		result = count <= b->m_value;
		break;
	case 2:
		result = count == b->m_value;
		break;
	case 3:
		result = count >= b->m_value;
		break;
	case 4:
		result = count > b->m_value;
		break;
	case 5:
		result = count != b->m_value;
		break;
	default:
		result = false;
		break;
	}

	if (result)
		return true;

	return false;
}
