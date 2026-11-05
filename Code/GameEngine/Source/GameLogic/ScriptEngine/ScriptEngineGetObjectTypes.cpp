// cl: /O1 /G7 /D_STLP_USE_STATIC_LIB /D_CRTIMP= /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
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
#include <vector>
// _M_insert_overflow inlines max(size(), n) as retail's copy does; this TU emits no max copy of its own.
namespace _STL { template <> __declspec(dllimport) __forceinline const unsigned int &max<unsigned int>(const unsigned int &__a, const unsigned int &__b) { return __a < __b ? __b : __a; } }


#include "../../../Include/GameLogic/ObjectTypesClass.h"

#include "../../../Include/GameLogic/ScriptEngine.h"

ObjectTypes *ScriptEngine::getObjectTypes(const AsciiString &objectTypeList)
{
	for (ObjectTypes **it = m_allObjectTypeLists.begin(); it != m_allObjectTypeLists.end(); ++it) {
		if (*it == 0)
			continue;
		void *nameField = ((Rva005C4AD1LeaField *)*it)->get();
		if (((const StringBase<char> *)nameField)->compare((const StringBase<char> &)objectTypeList) == 0)
			return *it;
	}
	return 0;
}

// Native358286..358317 RET12; ScriptEngine getObjectTypes/list ownership
// and the named ObjectTypes constructor establish the operation independently
// of WB's enclosing PerfTimer inline name. ZH doObjectTypeListMaintenance at
// donor9e3be919b10a supplies semantics; target uses global new and vector1A4C8.
void ScriptEngine::doObjectTypeListMaintenance(const AsciiString &list,const AsciiString &type,bool add) {
 ObjectTypes *current = getObjectTypes(list);
 if(!current) {
  ObjectTypes *newVec = new ObjectTypes(list);
  m_allObjectTypeLists.push_back(newVec);
  current = newVec;
 }
 if(add) current->addObjectType(type);
 else current->remove(type);
 if(current->getListSize()==0) removeObjectTypes(current);
}
