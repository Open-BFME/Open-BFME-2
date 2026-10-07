// cl: /DNDEBUG /MD
#include "../../../Common/RTS/XYDistanceCallView.h"
//
// findClosestOrphan, retail 0x0045F39B (93 bytes): Zero Hour's SpawnBehavior
// iteration callback, placed between SpawnBehavior::loadPostProcess and
// shouldTryToSpawn and passed with an OrphanData record to the player's
// object iterator (0x002AB08B) at 0x0045F547. BFME 2 changes three things:
// the callback returns 1 (the iterator's continue flag), it also skips
// objects of KindOf 0x220, and the distance is the squared 2D distance from
// the object to the source's position (0x002615E3) rather than the
// partition manager's. Target facts: the record is matchTemplate +0,
// source +4, closest +8, closestDistSq +0xC; the producer ID is the dword
// at Object +0x78; the template at +4 is tested with the rowed
// ThingTemplate::isEquivalentTo (0x0033BB04). ZH declares it static; it is
// external here so the unit emits it. Retail compares with fcompi, which
// MSVC 7.1 emits only under /arch:SSE.
enum ObjectID
{
	INVALID_ID = 0
};
enum KindOfType
{
	KINDOF_220 = 0x220
};
struct Coord3D
{
	float x, y, z;
};
class ThingTemplate
{
public:
	bool isEquivalentTo(const ThingTemplate *other) const;
};
class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getProducerID() const { return m_producerID; }
	bool isKindOf(KindOfType kindOf) const;
private:
	unsigned char m_pad00[4];
	const ThingTemplate *m_template;	// +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_pos;				// +0x38
	unsigned char m_pad44[0x78 - 0x44];
	ObjectID m_producerID;			// +0x78
};
class OrphanData
{
public:
	const ThingTemplate *m_matchTemplate;	// +0x00
	Object *m_source;			// +0x04
	Object *m_closest;			// +0x08
	float m_closestDistSq;			// +0x0C
};

int findClosestOrphan(Object *obj, void *userData)
{
	OrphanData *orphanData = (OrphanData *)userData;
	if (obj->getTemplate()->isEquivalentTo(orphanData->m_matchTemplate) && obj->getProducerID() == INVALID_ID && !obj->isKindOf(KINDOF_220)) {
		float distSq = reinterpret_cast<Rva000CBA20 *>(obj)->distSq(reinterpret_cast<const Rva000CBA20Point *>(orphanData->m_source->getPosition()));
		if (orphanData->m_closestDistSq > distSq) {
			orphanData->m_closest = obj;
			orphanData->m_closestDistSq = distSq;
		}
	}
	return 1;
}
