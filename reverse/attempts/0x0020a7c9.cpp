// ?rva0020A7C9@ScriptEngine@@QAEXXZ
// partial score=0.98 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /EHs
// stlport
//
// ?rva0020A7C9@ScriptEngine@@QAEXXZ @0x0020A7C9 144B.
// ScriptEngine method clearing the +0x1A120 vector then rebuilding one
// 8-byte entry per world object whose +0x88 name is non-empty. Evidence:
// +0x1A120 is ScriptEngine::m_vector1A120 in ScriptEngine_dtor.cpp; walk is
// GameLogic::getFirstObject plus Object+0x8C next like getObjectCount;
// callees rowed erase push_back StringBase set isEmpty releaseBuffer.
#include "ascii_string.h"
#include <vector>

struct FXBoneInfo
{
	AsciiString m_boneName;
	const void *m_template;
};

class Object
{
public:
	Object *getNextObject() { return m_next; }

private:
	char m_pad[0x88];
public:
	AsciiString m_name88;
	Object *m_next;
};

class GameLogic
{
public:
	Object *getFirstObject();
};
extern GameLogic *TheGameLogic;

struct Rva0020A227Element
{
	AsciiString key;
	Object *obj;
	Rva0020A227Element() : obj(0) {}
};

class ScriptEngine
{
public:
	void rva0020A7C9();

private:
	char m_pad[0x1A120];
	_STL::vector<Rva0020A227Element> m_vec;
};

void ScriptEngine::rva0020A7C9()
{
	_STL::vector<FXBoneInfo> &fv = (_STL::vector<FXBoneInfo> &)m_vec;
	fv.erase(fv.begin(), fv.end());
	GameLogic *g = TheGameLogic;
	if (g == 0)
		return;
	Object *obj = g->getFirstObject();
	if (obj == 0)
		return;
	for (; obj != 0; obj = obj->getNextObject()) {
		if (((StringBase<char> *)&obj->m_name88)->isEmpty())
			continue;
		Rva0020A227Element tmp;
		tmp.key.set(obj->m_name88);
		tmp.obj = obj;
		m_vec.push_back(tmp);
	}
}
