// cl: /O1 /MD /EHsc /DNDEBUG
// WorldHeightMap::ParseWorldDictDataChunk, retail 0x000ABD9A..0x000ABE0A
// (112 bytes, EH). The chunk parser parse (0x000AF238, WB-named) registers
// for "WorldInfo"; the pinned public-static spelling is kept.
// Zero Hour's body (WorldHeightMap.cpp in this tree carries the verbatim
// port, compiled at that unit's other optimization level): read the chunk's
// Dict into the world dict (VA 0x00E00944), and when it has the weather key
// (StaticNameKey at VA 0x00DBDEB4) store it in TheWritableGlobalData, here at
// +0x138. Callees are the rowed DataChunkInput::readDict 0x00307833,
// Dict::operator= 0x003133E1, StaticNameKey::key 0x00148F5E, Dict::getInt
// 0x003131CA and Dict::releaseData 0x0031339C.
typedef int Int;
typedef bool Bool;

enum NameKeyType { NAMEKEY_INVALID = 0 };

class StaticNameKey
{
public:
	NameKeyType key() const;
	// public so the retail static initialiser below is plain data
	mutable NameKeyType m_key;
	const char *m_name;
};

class Dict
{
public:
	~Dict() { releaseData(); }
	Dict &operator=(const Dict &src);
	Int getInt(Int key, Bool *exists) const;
private:
	void releaseData();
	void *m_data;
};

class AsciiString;
struct DataChunkInfo;
class UserParser;
class ChunkInputStream;
class DataChunkInput
{
public:
	typedef bool (*Parser)(DataChunkInput &file, DataChunkInfo *info, void *userData);
	Dict readDict();
	float readReal();
	unsigned char readByte();
	AsciiString readAsciiString();
	UserParser *registerParser(const AsciiString &label, const AsciiString &parentLabel, Parser parser, void *userData);
	bool parse(void *userData);
	DataChunkInput(ChunkInputStream *stream);
	~DataChunkInput();
	int readInt();
	void readArrayOfBytes(char *, int);
private:
	unsigned char m_data[0x28]; // +0x00
};


class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct GlobalDataWeatherView
{
	unsigned char m_pad[0x138];
	Int m_weather;										// +0x138
};

extern Dict g_Va00E00944;								// the world dict
StaticNameKey TheKey_weather = { NAMEKEY_INVALID, "weather" };	// VA 0x00DBDEB4, retail .data {0, "weather"}

class WorldHeightMap
{
public:
	static Bool ParseWorldDictDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);
};

Bool WorldHeightMap::ParseWorldDictDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	Dict d = file.readDict();
	g_Va00E00944 = d;
	Bool exists;
	Int theWeather = g_Va00E00944.getInt(TheKey_weather.key(), &exists);
	if (exists)
		((GlobalDataWeatherView *)TheWritableGlobalData)->m_weather = theWeather;
	return true;
}
