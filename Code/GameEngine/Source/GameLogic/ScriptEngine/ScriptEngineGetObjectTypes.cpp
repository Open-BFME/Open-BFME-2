// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?getObjectTypes@ScriptEngine@@QAEPAVObjectTypes@@ABVAsciiString@@@Z @0x00357651 60B
// ScriptEngine::getObjectTypes: search m_allObjectTypeLists (+0x1A4C8 vector) by list name.
// Donor: ZH ScriptEngine::getObjectTypes (ScriptEngine.cpp:5860) loop with null skip and
// getListName compare. Target evidence: adjacent ScriptEngine::getQualifiedTriggerAreaByName
// at 0x0035768D, callers 0x00358286 (doObjectTypeListMaintenance push_back to +0x1A4C8) and
// 0x003C449C pass ScriptEngine this, callee 0x005C4AD1 lea+4 is ObjectTypes name field and
// 0x000069D6 is StringBase<char>::compare. Layout +0x1A4C8 from matched removeObjectTypes.

class Rva005C4AD1LeaField
{
public:
	void *get() const;
};

#include "ascii_string.h"


class ObjectTypes;

class ScriptEngine
{
public:
	ObjectTypes *getObjectTypes(const AsciiString &objectTypeList);

private:
	char m_pad[0x1A4C8];
	ObjectTypes **m_begin; // +0x1A4C8
	ObjectTypes **m_end; // +0x1A4CC
};

ObjectTypes *ScriptEngine::getObjectTypes(const AsciiString &objectTypeList)
{
	for (ObjectTypes **it = m_begin; it != m_end; ++it) {
		if (*it == 0)
			continue;
		void *nameField = ((Rva005C4AD1LeaField *)*it)->get();
		if (((const StringBase<char> *)nameField)->compare((const StringBase<char> &)objectTypeList) == 0)
			return *it;
	}
	return 0;
}
