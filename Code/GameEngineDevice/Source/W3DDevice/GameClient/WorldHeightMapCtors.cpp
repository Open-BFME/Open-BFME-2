// cl: /O1 /MD /EHsc
// stlport
// WorldHeightMap's default constructor and its two stream constructors (WorldBuilder names the class's
// parse 0x000AF238, WorldHeightMap.cpp; the ctor pin of
// W3DTerrainLogic::loadMap names 0x000B0C38):
//   0x000B098A (323 bytes)         WorldHeightMap() (no caller in retail;
//                                   ends in the rowed static alpha-tile
//                                   setup 0x000AC6F9, as Zero Hour's does)
//   0x000B0ACD (363 bytes, ret 4)  WorldHeightMap(ChunkInputStream *)
//   0x000B0C38 (368 bytes, ret 16) WorldHeightMap(ChunkInputStream *, int, int, int)
// Both share retail's handler 0x00761418 (identical unwind tables).
//
// Target facts: over RefCountClass (count 1) with own table 0x00BC967C,
// twelve empty vectors (+0x14 +0x28 +0x38 ... +0x8C, +0x80B0 +0x80BC) through
// the folded _Vector_base constructor 0x00211E58, two 512-entry arrays of
// 0x28-byte records (+0x80CC, +0xD0D0; rowed constructor 0x000AF215 and
// destructor 0x004D9A3C), a cleared texture reference at +0x120D0 and a
// two-entry texture reference array at +0x120D8 (rowed RefCountPtr ctor
// 0x00326BE6 and dtor 0x0017098D); then the rowed reset 0x000B08F7, and the
// stream is wrapped in a DataChunkInput and handed to parse (0x000AF238,
// pinned) with the three ints, or zeros. The destructor is the rowed
// 0x000B0028 (Rva00B0028Dtor.cpp, same member layout). The vector element
// types are carriers whose base constructor the ledger owns: the bytes prove
// only empty three-pointer headers.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

#include "../../../../Libraries/Include/Lib/BfmeE16.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline _Vector_base<BfmeE16,allocator<BfmeE16> >::~_Vector_base() { if (this->_M_start != 0) this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start); } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline _Vector_base<int,allocator<int> >::~_Vector_base() { if (this->_M_start != 0) this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start); } }
// bfme link decl-only begin
namespace _STL { template <> vector<int, allocator<int> >::~vector(); }
// bfme link decl-only end
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

class RefCountClass
{
public:
	void Release_Ref() { if (--m_refs == 0) Delete_This(); }
	RefCountClass() : m_refs(1) {}
	virtual void Delete_This();
protected:
	virtual ~RefCountClass() {}
private:
	int m_refs; // +0x04
};

class TileData;

class TextureClass;

template <class T> class RefCountPtr
{
public:
	RefCountPtr() : m_ptr(0) {}
	~RefCountPtr();
private:
	T *m_ptr;
};

// The 0x28-byte record of the two 512-entry arrays (rowed ctor 0x000AF215,
// dtor 0x004D9A3C).
struct Rva000AF215
{
	Rva000AF215();
	~Rva000AF215();
	unsigned char m_data[0x28];
};

class ChunkInputStream;

class Dict;
class AsciiString;
struct DataChunkInfo;
class UserParser;
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

class Rva000B08F7
{
public:
	void rva000B08F7();										// 0x000B08F7
};

void Rva000AC6F9SetupAlphaTiles();							// 0x000AC6F9

enum { NUM_SOURCE_TILES = 0x1000 };

class WorldHeightMap : public RefCountClass
{
public:
	WorldHeightMap();
	WorldHeightMap(ChunkInputStream *strm);
	WorldHeightMap(ChunkInputStream *strm, int polygonOwner, int b, int c);
	virtual ~WorldHeightMap();

	void parse(DataChunkInput &file, void *polygonOwner, void *owner10, void *owner14);	// 0x000AF238 (WorldHeightMapParse.cpp)

private:
	int m_08;
	int m_0C;
	int m_10;
	_STL::vector<int> m_14;
	int m_20;
	unsigned char *m_data;									// +0x24
	_STL::vector<int> m_28;
	int m_34;
	_STL::vector<int> m_38;
	_STL::vector<int> m_44;
	_STL::vector<int> m_50;
	_STL::vector<int> m_5C;
	_STL::vector<int> m_68;
	_STL::vector<int> m_74;
	_STL::vector<int> m_80;
	_STL::vector<int> m_8C;
	short *m_tileNdxes;										// +0x98
	short *m_blendTileNdxes;								// +0x9C
	short *m_extraBlendTileNdxes;							// +0xA0
	short *m_cliffInfoNdxes;								// +0xA4
	int m_A8;
	int m_AC;
	TileData *m_sourceTiles[NUM_SOURCE_TILES];				// +0xB0
	TileData *m_edgeTiles[NUM_SOURCE_TILES];				// +0x40B0
	_STL::vector<BfmeE16> m_80B0;
	_STL::vector<int> m_80BC;
	int m_80C8;
	Rva000AF215 m_80CC[0x200];
	int m_D0CC;
	Rva000AF215 m_D0D0[0x200];
	RefCountPtr<TextureClass> m_120D0;
	int m_120D4;
	RefCountPtr<TextureClass> m_120D8[2];
	int m_120E0[4];
};

WorldHeightMap::WorldHeightMap()
{
	((Rva000B08F7 *)this)->rva000B08F7();
	Rva000AC6F9SetupAlphaTiles();
}

WorldHeightMap::WorldHeightMap(ChunkInputStream *strm)
{
	((Rva000B08F7 *)this)->rva000B08F7();
	DataChunkInput file(strm);
	parse(file, 0, 0, 0);
}

WorldHeightMap::WorldHeightMap(ChunkInputStream *strm, int polygonOwner, int b, int c)
{
	((Rva000B08F7 *)this)->rva000B08F7();
	DataChunkInput file(strm);
	parse(file, (void *)polygonOwner, (void *)b, (void *)c);
}
