// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva003977F6@CastleBehavior@@QAE_NPAVObjectTypes@@@Z, retail 0x003977F6,
// 309 bytes (thiscall, ret 4). Target evidence: the only caller,
// ScriptConditions 0x003E51D9 (jump-table case 147,
// OBJECT_OF_TYPE_OR_LIST_INSIDE_REFD_BASE), reaches it on the module
// findModule 0x0028B6D6 returns for the rowed CastleBehavior name key
// 0x003955DA, passing a parsed ObjectTypes. The body walks the members the
// rowed ctor 0x003983D4 lays out: the +0x8C set (begin at header+8, value
// at node+0x10, rowed _M_increment 0x00024250), the +0x5C and +0x68
// vectors, the +0x38 id and the +0x50 vector, resolving each id with the
// rowed GameLogic::findObjectByID 0x00049DC5 and testing its template with
// the rowed ObjectTypes set test 0x00376A84. Element types follow the
// ctor's vector<ObjectID> spelling; no donor names the method, so it keeps
// an address name.
#include <vector>
#include <set>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "../../../Common/GameLogicObjectLookupView.h"

class ThingTemplate;

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
private:
	void *m_vtbl;
	const ThingTemplate *m_template; // +0x04
};

extern GameLogic *TheGameLogic;

// ObjectTypes::isInSet(const ThingTemplate *) is rowed under its address name.
class Rva00376A62
{
public:
	Bool rva00376A84(const void *thingTemplate);
};

class ObjectTypes
{
public:
	Bool isInSet(const ThingTemplate *thingTemplate)
	{
		return ((Rva00376A62 *)this)->rva00376A84(thingTemplate);
	}
};

class CastleBehavior
{
public:
	Bool rva003977F6(ObjectTypes *types);
private:
	unsigned char m_pad00[0x38];
	ObjectID m_38; // +0x38
	unsigned char m_pad3C[0x50 - 0x3C];
	_STL::vector<ObjectID> m_50; // +0x50
	_STL::vector<ObjectID> m_5C; // +0x5C
	_STL::vector<ObjectID> m_68; // +0x68
	unsigned char m_pad74[0x8C - 0x74];
	_STL::set<ObjectID> m_8C; // +0x8C
};

Bool CastleBehavior::rva003977F6(ObjectTypes *types)
{
	for (_STL::set<ObjectID>::const_iterator it = m_8C.begin(); it != m_8C.end(); ++it) {
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj && types->isInSet(obj->getTemplate()))
			return true;
	}
	UnsignedInt i;
	for (i = 0; i < m_5C.size(); ++i) {
		Object *obj = TheGameLogic->findObjectByID(m_5C[i]);
		if (obj && types->isInSet(obj->getTemplate()))
			return true;
	}
	for (i = 0; i < m_68.size(); ++i) {
		Object *obj = TheGameLogic->findObjectByID(m_68[i]);
		if (obj && types->isInSet(obj->getTemplate()))
			return true;
	}
	{
		Object *obj = TheGameLogic->findObjectByID(m_38);
		if (obj && types->isInSet(obj->getTemplate()))
			return true;
	}
	for (i = 0; i < m_50.size(); ++i) {
		Object *obj = TheGameLogic->findObjectByID(m_50[i]);
		if (obj && types->isInSet(obj->getTemplate()))
			return true;
	}
	return false;
}
