// cl: /DNDEBUG /MD
//
// ?deleteListResources@Radar@@IAEXXZ, retail 0x002D75E5, 130 bytes.
// Dedicated TU (sibling of Radar_reset.cpp: the Radar file-unit keeps one
// body per TU).
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/Common/System/Radar.cpp,
// b1 0x00106A90): tear both object lists down, then walk every game object
// (the NDEBUG assertion loop survives with an empty body because
// getFirstObject is a call the compiler will not walk away from).
//
// BFME2 divergences from the donor, all retail-measured:
// - The lists hang at +0x14 (object list) and +0x18 (local list), not
//   +0x10/+0x14; the node links are unchanged (object at +0x04, next at
//   +0x08); Object carries next at +0x8C (b1 +0x88) and the radar
//   back-pointer at +0x260 (b1 +0x20C).
// - The free path is not the donor's plain `delete`: retail calls the
//   node's slot-0 virtual with a zero word and frees whatever it returns,
//   guarding a null head into operator delete(0):
//     push 0 / call [vft] / push eax / call ??3, with a test-and-branch
//   around the virtual. A `virtual void *deleteInstance(int)` plus an
//   explicit null-guarded operator delete reproduces it exactly; the plain
//   `delete` the donor spells compiles to the single-call push-1
//   scalar-deleting shape instead (b1 keeps that shape to this day).
//   The name is the donor's; the word parameter and the returned block are
//   what the codegen proves (a pool release handing its block back to be
//   freed reads the same way).
// - Every helper (friend_getNext, friend_getObject, friend_setRadarData,
//   getNextObject) is inline in retail; only operator delete and
//   getFirstObject are out-of-line calls, both already rowed.

class GameLogic;

extern GameLogic *TheGameLogic;

class Object;

class RadarObject
{
public:
	virtual void *deleteInstance(int pool);
	Object *friend_getObject() { return m_object; }
	RadarObject *friend_getNext() { return m_next; }

	Object *m_object; // +0x04
	RadarObject *m_next; // +0x08
};

class Object
{
public:
	Object *getNextObject() { return m_next; }
	void friend_setRadarData(RadarObject *data) { m_radarData = data; }

	char m_pad[0x8C];
	Object *m_next; // +0x8C
	char m_pad2[0x260 - 0x90];
	RadarObject *m_radarData; // +0x260
};

class GameLogic
{
public:
	Object *getFirstObject();
};

class Radar
{
public:
	virtual void vslot0();
protected:
	void deleteListResources();
private:
	// Single vptr here (the retail MI second base shifts nothing this body
	// reads); the pad keeps the retail list offsets.
	char m_pad[0x10];
	RadarObject *m_objectList; // +0x14
	RadarObject *m_localObjectList; // +0x18
};

// ?deleteListResources@Radar@@IAEXXZ
void Radar::deleteListResources()
{
	RadarObject *nextObject;

	// delete entries from the local object list
	while (m_localObjectList)
	{
		// get next object
		nextObject = m_localObjectList->friend_getNext();

		// remove radar data from object
		m_localObjectList->friend_getObject()->friend_setRadarData(0);

		// delete the head of the list
		::operator delete(m_localObjectList ? m_localObjectList->deleteInstance(0) : 0);

		// set head of the list to the next object
		m_localObjectList = nextObject;
	}

	// delete entries from the regular object list
	while (m_objectList)
	{
		// get next object
		nextObject = m_objectList->friend_getNext();

		// remove radar data from object
		m_objectList->friend_getObject()->friend_setRadarData(0);

		// delete the head of the list
		::operator delete(m_objectList ? m_objectList->deleteInstance(0) : 0);

		// set head of the list to the next object
		m_objectList = nextObject;
	}

	Object *obj;
	for (obj = TheGameLogic->getFirstObject(); obj; obj = obj->getNextObject())
	{
	}
}
