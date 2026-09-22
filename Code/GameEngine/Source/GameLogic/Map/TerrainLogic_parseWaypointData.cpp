// cl: /O1 /DNDEBUG /MD /EHsc
// ?parseWaypointData@TerrainLogic@@IAE_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z,
// retail 0x0027FFF3, 60 bytes. Dedicated TU.
//
// Battle for Middle-earth 2 keeps the Zero Hour skeleton verbatim:
// three readInt calls plus addWaypointLink per link; the end-of-chunk
// assert vanishes in NDEBUG so retail is a frameless loop plus true.

typedef int Int;

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

class __declspec(novtable) TerrainLogic
{
public:
	virtual void slot00() = 0;

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
