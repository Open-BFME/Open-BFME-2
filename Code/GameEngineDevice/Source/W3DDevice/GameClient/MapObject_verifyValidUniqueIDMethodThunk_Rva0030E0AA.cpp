// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /DNDEBUG
//
// ?verifyValidUniqueID@MapObject@@QAEXXZ
// retail 0x0030E0AA, 420 bytes (Ghidra FUN_0070e0aa boundary).
//
// Target evidence: MapObject::validate (placed at 0x0030E380 in
// WorldHeightMap.cpp) calls verifyValidTeam (0x0030D6C7) then this body,
// the Zero Hour order. The key caches it reads name themselves: 0x00DBDDB4
// "uniqueID", 0x00DBDC64 "waypointName" (0x0030D748 is the getter over it)
// and 0x00DBDC6C "GenericAIObjectName" (0x0030D808). 0x0030D833 is
// getThingTemplate (m_thingTemplate +0x18, tail call into getFinalOverride).
// Retail formats with the literals "%s %d" and "%s".
//
// Donor: GeneralsMD WorldHeightMap.cpp MapObject::verifyValidUniqueID, by way
// of Open-BFME-1 MapObject_verifyValidUniqueIDMethodThunk.cpp (layouts). BFME 2
// adds a second runtime flag (0x20) that the loop skips like a waypoint and
// that names the object through its GenericAIObjectName property; the name
// of that flag and getter are inferred from the key string, not proven.

#include <stdlib.h>
#include "ascii_string.h"

// Retail keeps no EH state for the loop's tempStr across this call, so the
// compiler saw StringBase<char>::reverseFind (row 0x00035930) as nothrow.
template<> const char *StringBase<char>::reverseFind(char c) const throw();

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
	AsciiString getAsciiString(NameKeyType key, Bool *exists = 0) const;
	void setAsciiString(int key, const AsciiString &value);
private:
	void *m_data;
};

// Retail reads the template's name as `add eax,0x64; mov eax,[eax]`, not
// [eax+0x64]: the +0x64 is materialised like a base-class this adjustment.
// This TU-local view reproduces that; it does not claim ThingTemplate's real
// class layout, only that its name string sits at +0x64.
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

	static MapObject *getFirstMapObject();

	void verifyValidUniqueID();

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

class MapObjectListHolder
{
public:
	MapObject *m_head;
};

extern MapObjectListHolder *BfmeTheMapObjectListHolder;	// retail [0x00E00940]

inline MapObject *MapObject::getFirstMapObject()
{
	return BfmeTheMapObjectListHolder->m_head;
}

void MapObject::verifyValidUniqueID()
{
	Bool exists;
	AsciiString uniqueID = getProperties()->getAsciiString(TheKey_uniqueID.key(), &exists);
	MapObject *obj = MapObject::getFirstMapObject();

	// -1 is the sentinel
	int highestIndex = -1;

	while (obj) {
		if (obj == this) {
			obj = obj->getNext();
			continue;
		}

		if (obj->isWaypoint()) {
			obj = obj->getNext();
			continue;
		}

		if (obj->isGenericAIObject()) {
			obj = obj->getNext();
			continue;
		}

		Bool iterateExists;
		AsciiString tempStr = obj->getProperties()->getAsciiString(TheKey_uniqueID.key(), &iterateExists);
		const char *lastSpace = tempStr.reverseFind(' ');

		int testIndex = -1;
		if (lastSpace) {
			testIndex = atoi(lastSpace);
		}

		if (testIndex > highestIndex) {
			highestIndex = testIndex;
		}
		break;
	}

	int indexOfThisObject = highestIndex + 1;

	const char *thingName;
	if (getThingTemplate()) {
		thingName = getThingTemplate()->getName().str();
	} else if (isWaypoint()) {
		thingName = getWaypointName().str();
	} else if (isGenericAIObject()) {
		thingName = getGenericAIObjectName().str();
	} else {
		thingName = getName().str();
	}
	const char *pName = thingName;

	while (*thingName) {
		if ((*thingName) == '/') {
			pName = thingName + 1;
		}
		++thingName;
	}

	AsciiString newID;
	if (isWaypoint() || isGenericAIObject()) {
		newID.format("%s", pName);
	} else {
		newID.format("%s %d", pName, indexOfThisObject);
	}

	getProperties()->setAsciiString(TheKey_uniqueID.key(), newID);
}
