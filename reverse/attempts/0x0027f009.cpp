// ?addWaypointLink@TerrainLogic@@IAEXHH@Z
// partial score=0.6 date=2026-09-22
// cl: /O1 /DNDEBUG /MD /EHsc
// ?parseWaypointData@TerrainLogic@@IAE_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z,
// retail 0x0027FFF3, 60 bytes. Dedicated TU.
//
// Battle for Middle-earth 2 keeps the Zero Hour skeleton verbatim:
// three readInt calls plus addWaypointLink per link; the end-of-chunk
// assert vanishes in NDEBUG so retail is a frameless loop plus true.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;

struct DataChunkInfo;

class DataChunkReader
{
public:
	virtual void read(void *buffer, Int size);
};

class DataChunkInput
{
public:
	Int readInt();
	void consume(Int bytes);

private:
	DataChunkReader *m_reader;
};

class Waypoint
{
public:
	char m_pad00[4];
	int m_id;
	char m_pad08[0x14];
	Waypoint *m_next;
	Waypoint *m_links[8];
	Waypoint *m_linkSource;
	char m_pad44[8];
	Int m_numLinks;
	char m_pad50[0x0C];
	Bool m_biDirectional;

	// Direct members at retail offsets: id +4 next +0x1C links +0x20
	// source +0x40 count +0x4C bidirectional +0x5C. getLink/addLink stay
	// out-of-line via pins; the rest fold to direct reads.
	UnsignedInt getID(void) const { return (UnsignedInt)m_id; }
	Waypoint *getNext(void) const { return m_next; }
	Int getNumLinks(void) const { return m_numLinks; }
	Waypoint *getLink(Int ndx) const;
	void addLink(Waypoint *other);
	Bool getBiDirectional(void) const { return m_biDirectional; }
};

class __declspec(novtable) TerrainLogic
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual Waypoint *getFirstWaypoint(void) = 0;

protected:
	bool parseWaypointData(DataChunkInput &file, DataChunkInfo *info, void *userData);
	void addWaypointLink(Int id1, Int id2);
};

// ?parseWaypointData@TerrainLogic@@IAE_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
bool TerrainLogic::parseWaypointData(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	Int numWaypointLinks = file.readInt();
	Int i;
	for (i = 0; i < numWaypointLinks; i++) {
		Int waypoint1 = file.readInt();
		Int waypoint2 = file.readInt();
		addWaypointLink(waypoint1, waypoint2);
	}
	return true;
}

// ?readInt@DataChunkInput@@QAEHXZ @0x00306E78
Int DataChunkInput::readInt()
{
	Int value;
	m_reader->read(&value, 4);
	consume(4);
	return value;
}

// ?addWaypointLink@TerrainLogic@@IAEXHH@Z @0x0027F009
void TerrainLogic::addWaypointLink(Int id1, Int id2)
{
	Waypoint *pWay1 = 0;
	Waypoint *pWay2 = 0;
	Waypoint *pWay;
	for (pWay = getFirstWaypoint(); pWay; pWay = pWay->getNext()) {
		if (pWay->getID() == (UnsignedInt)id1) {
			pWay1 = pWay;
		}
		if (pWay->getID() == (UnsignedInt)id2) {
			pWay2 = pWay;
		}
	}
	if (pWay1 && pWay2 && (pWay1 != pWay2)) {
		Int i;
		for (i = 0; i < pWay1->getNumLinks(); i++) {
			if (pWay1->getLink(i) == pWay2) {
				return;
			}
		}
		pWay1->addLink(pWay2);
		if (pWay1->getBiDirectional()) {
			for (i = 0; i < pWay2->getNumLinks(); i++) {
				if (pWay2->getLink(i) == pWay1) {
					return;
				}
			}
			pWay2->addLink(pWay1);
		}
	}
}
