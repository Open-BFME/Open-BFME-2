// cl: /Ireference/shims/bfme2_ascii /EHs
// stlport
//
// ?addObjectToCache@ScriptEngine@@QAEXPAVObject@@ABVAsciiString@@@Z @0x0020A5FF 374B.
// ScriptEngine name-to-object map at +0x1A120. Evidence: pin name, callers in
// ScriptActions (0x003C3525 0x003C473B), rowed callees StringBase copy 0x365F0
// compare 0x69D6 isEmpty 0x1E2F set 0x366F0 releaseBuffer 0x36410 format
// 0x38150 push_back 0x20A227 AppendDebugMessage 0x205263, globals
// AsciiString::TheEmptyString g_Rva0107301CEmptyString g_Va009FE16C, string
// "Reassigning dead object's name '%s' to object (%d) of type '%s'\n" (ZH donor
// ScriptEngine.cpp:6386), Object+0x88 name Object+0x74 id Object+0x4 template.
#include "ascii_string.h"
#include <vector>

class Object;
struct ObjectTemplate
{
	char m_pad[0x64];
	AsciiString m_name64;
};

class Object
{
public:
	ObjectTemplate *getTemplate() { return m_tmpl04; }
	int getID() { return m_id74; }

private:
	char m_pad0[4];
	ObjectTemplate *m_tmpl04; // +0x04
	char m_pad08[0x6C]; // +0x08..+0x73
	int m_id74; // +0x74
	char m_pad78[0x10]; // +0x78..+0x87
public:
	AsciiString m_name88; // +0x88
};

struct Rva0020A227Element
{
	AsciiString key;
	Object *obj;
	Rva0020A227Element() : obj(0) {}
};

extern class ScriptEngine *TheScriptEngine;

class ScriptEngine
{
public:
	void addObjectToCache(Object *pNewObject, const AsciiString &name);
	void AppendDebugMessage(const AsciiString &strToAdd, bool mustAdd);

private:
	char m_pad[0x1A120];
	_STL::vector<Rva0020A227Element> m_vec1A120;
};

void ScriptEngine::addObjectToCache(Object *pNewObject, const AsciiString &name)
{
	if (pNewObject == 0)
		return;
	AsciiString objName(pNewObject->m_name88);
	bool flag = false;
	if (((StringBase<char> *)&objName)->compare(*(StringBase<char> *)&AsciiString::TheEmptyString) == 0) {
		if (((StringBase<char> *)&name)->isEmpty())
			return;
		((StringBase<char> *)&objName)->set(*(StringBase<char> *)&name);
		flag = true;
	}
	for (Rva0020A227Element *it = m_vec1A120.begin(); it != m_vec1A120.end(); ++it) {
		if (((StringBase<char> *)&it->key)->compare(*(StringBase<char> *)&objName) == 0) {
			Object *cur = it->obj;
			if (cur == 0) {
				AsciiString newNameForDead;
				newNameForDead.format("Reassigning dead object's name '%s' to object (%d) of type '%s'\n", objName.str(), pNewObject->getID(), pNewObject->getTemplate()->m_name64.str());
				TheScriptEngine->AppendDebugMessage(newNameForDead, false);
				it->obj = pNewObject;
				return;
			}
			if (cur == pNewObject || !flag)
				return;
			it->obj = pNewObject;
			return;
		}
		if (pNewObject == it->obj) {
			((StringBase<char> *)&it->key)->set(*(StringBase<char> *)&objName);
			return;
		}
	}
	Rva0020A227Element tmp;
	((StringBase<char> *)&tmp.key)->set(*(const StringBase<char> *)&objName);
	tmp.obj = pNewObject;
	m_vec1A120.push_back(tmp);
}
