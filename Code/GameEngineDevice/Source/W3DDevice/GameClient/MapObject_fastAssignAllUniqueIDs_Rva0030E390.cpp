// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?fastAssignAllUniqueIDs@MapObject@@SAXXZ
// Retail 0x0030E390..0x0030E51F (399 bytes).
//
// MapObject::fastAssignAllUniqueIDs: stacks every map object of the list
// (BfmeTheMapObjectListHolder, retail [0x00E00940]) and pops them from the
// back, giving each a uniqueID property (TheKey_uniqueID 0x00DBDDB4) made of
// its path-free template name (else its waypoint name, else its
// GenericAIObjectName, else its object name) formatted "%s %d" with a running
// index, or plain "%s" for waypoints and generic AI objects.
//
// Target evidence: WB twin 0x00A7E7A0 by call graph; the "%s %d" / "%s"
// literals; rowed or pinned callees getThingTemplate (0x0030D833, called
// twice), getWaypointName (0x0030D748), getGenericAIObjectName (0x0030D808),
// AsciiString::format, StaticNameKey::key (0x00148F5E), Dict::setAsciiString
// (0x0031375A) and the five deque bodies named below; layouts as in
// MapObject_verifyValidUniqueIDMethodThunk_Rva0030E0AA.cpp.
// Donor: GeneralsMD WorldHeightMap.cpp MapObject::fastAssignAllUniqueIDs (the
// present-unmatched copy in this tree's WorldHeightMap.cpp) and Open-BFME-1
// MapObjectFastAssignUniqueIDs.cpp. BFME 2 adds the generic-AI-object branch
// and format choice (flag 0x20, name inferred from its key string, as in
// verifyValidUniqueID).
#include <stl/_algobase.h>
// Keep the shared out-of-line max provider (the ScriptListTakeGroups precedent).
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{ return a < b ? b : a; }
}
// Neutral storage for the stacked MapObject pointer, not the original element
// type (Zero Hour stacks MapObject*): retail calls the folded four-byte POD
// deque bodies whose ledger names use this aggregate (ctor 0x00605464,
// push_back 0x00423BD8, back 0x003B5603, _M_pop_back_aux 0x003B3F2F, base dtor
// 0x0054FAAC). STLport needs the POD traits stated explicitly.
struct BfmeScriptSlotAddress { unsigned int address; };
typedef char ScriptSlotAddressWidth[sizeof(BfmeScriptSlotAddress) == 4 ? 1 : -1];
namespace _STL {
template<> struct __type_traits<BfmeScriptSlotAddress> : __type_traits_aux<1> {};
}
#include <stack>
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class StaticNameKey
{
public:
	NameKeyType key() const;
};

extern const StaticNameKey TheKey_uniqueID;		// retail 0x00DBDDB4

class Dict
{
public:
	void setAsciiString(int key, const AsciiString &value);
private:
	void *m_data;
};

class ThingTemplateHead
{
	char m_pad00[0x64];
};

class ThingTemplateName
{
public:
	const AsciiString &getName() const { return m_nameString; }
private:
	AsciiString m_nameString;
};

class ThingTemplate : public ThingTemplateHead, public ThingTemplateName
{
};

class MapObject;

class MapObjectListHolder
{
public:
	MapObject *m_head;
};

extern MapObjectListHolder *BfmeTheMapObjectListHolder;	// retail [0x00E00940]

class MapObject
{
public:
	enum
	{
		MO_WAYPOINT = 0x04,
		MO_GENERIC_AI_OBJECT = 0x20
	};

	MapObject *getNext() { return m_next; }
	Dict *getProperties() { return &m_properties; }
	const AsciiString &getName() const { return m_objectName; }
	Bool isWaypoint() const { return (m_runtimeFlags & MO_WAYPOINT) != 0; }
	Bool isGenericAIObject() const { return (m_runtimeFlags & MO_GENERIC_AI_OBJECT) != 0; }

	const ThingTemplate *getThingTemplate() const;		// 0x0030D833
	AsciiString getWaypointName();				// 0x0030D748
	AsciiString getGenericAIObjectName();			// 0x0030D808

	static MapObject *getFirstMapObject() { return BfmeTheMapObjectListHolder->m_head; }
	static void fastAssignAllUniqueIDs();

private:
	void *m_vtable;
	MapObject *m_next;
	char m_pad08[0x14 - 0x08];
	AsciiString m_objectName;
	void *m_thingTemplate;
	char m_pad1C[0x24 - 0x1C];
	Dict m_properties;
	char m_pad28[0x44 - 0x28];
	Int m_runtimeFlags;
};

void MapObject::fastAssignAllUniqueIDs()
{
	MapObject *pMapObj = getFirstMapObject();

	std::stack<BfmeScriptSlotAddress> objStack;
	Int actualNumObjects = 0;

	while (pMapObj) {
		++actualNumObjects;
		objStack.push(*reinterpret_cast<BfmeScriptSlotAddress *>(&pMapObj));
		pMapObj = pMapObj->getNext();
	}

	Int indexOfThisObject = 0;
	while (actualNumObjects) {
		MapObject *obj = reinterpret_cast<MapObject *>(objStack.top().address);

		const char *thingName;
		if (obj->getThingTemplate()) {
			thingName = obj->getThingTemplate()->getName().str();
		} else if (obj->isWaypoint()) {
			thingName = obj->getWaypointName().str();
		} else if (obj->isGenericAIObject()) {
			thingName = obj->getGenericAIObjectName().str();
		} else {
			thingName = obj->getName().str();
		}
		const char *pName = thingName;

		while (*thingName) {
			if ((*thingName) == '/') {
				pName = thingName + 1;
			}
			++thingName;
		}

		AsciiString newID;
		if (obj->isWaypoint() || obj->isGenericAIObject()) {
			newID.format("%s", pName);
		} else {
			newID.format("%s %d", pName, indexOfThisObject);
		}

		obj->getProperties()->setAsciiString(TheKey_uniqueID.key(), newID);
		objStack.pop();

		++indexOfThisObject;
		--actualNumObjects;
	}
}
