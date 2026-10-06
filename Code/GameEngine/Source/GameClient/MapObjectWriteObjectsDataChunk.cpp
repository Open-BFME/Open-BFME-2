// cl: /Ireference/shims/bfme2_ascii
//
// Shared BFME map-object chunk writer, retail 0x0030D526, 196 bytes.
// Dedicated TU (B2 has no MapUtil writer unit). Ported from the BFME1 twin
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/
// MapObjectWriteObjectsDataChunk.cpp): ObjectsList/3 chunk, per-object
// Object/3 chunk with location, angle, flags, name and property dictionary.
// Retail-measured: MapObject layout (next +4, location +8, name +14,
// template +18, angle +1C, flags +20, props +24), filter shouldWrite at
// vtable slot 1. Callee pins: writeInt/writeReal share 0x00306CFF,
// closeDataChunk and openDataChunk resolve via existing rows/pins, writeDict
// is pinned at 0x00307D85 (ZH DataChunk.h identity).

typedef int Int;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

#include "ascii_string.h"

class Dict
{
private:
	unsigned char m_data[1];
};

class MapObject
{
public:
	const Coord3D *getLocation() const { return &m_location; }

	void *m_vftable;
	MapObject *m_nextMapObject;
	Coord3D m_location;
	AsciiString m_objectName;
	void *m_thingTemplate;
	Real m_angle;
	Int m_flags;
	Dict m_properties;
};

class MapObjectWriterFilter
{
public:
	virtual void bfmeFilterDestructorSlot();
	virtual Bool shouldWrite(MapObject *object);
};

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short version);
	void closeDataChunk();
	void writeReal(Real value);
	void writeInt(Int value);
	void writeAsciiString(const AsciiString &value);
	void writeDict(const Dict &value);
};

void bfmeWriteObjectsDataChunk(MapObject *objects, DataChunkOutput *output,
	MapObjectWriterFilter *filter)
{
	output->openDataChunk("ObjectsList", 3);

	for (MapObject *object = objects; object; object = object->m_nextMapObject)
	{
		if (!filter->shouldWrite(object))
			continue;

		output->openDataChunk("Object", 3);
		Coord3D location;
		location.x = object->getLocation()->x;
		location.y = object->getLocation()->y;
		location.z = object->getLocation()->z;
		output->writeReal(location.x);
		output->writeReal(location.y);
		output->writeReal(location.z);
		output->writeReal(object->m_angle);
		output->writeInt(object->m_flags);
		output->writeAsciiString(object->m_objectName);
		output->writeDict(object->m_properties);
		output->closeDataChunk();
	}

	output->closeDataChunk();
}
