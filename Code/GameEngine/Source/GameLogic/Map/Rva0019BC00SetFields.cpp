// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameLogic/Map/Rva0019BC00SetFields.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// Rva0019BC00Owner::apply 0x0032D223 (86B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// class-gate: allow AsciiString the donor's own view; the placed bodies are byte-exact under it
class AsciiString
{
public:
	int m_data;
};

class AsciiStringField
{
public:
	void set(AsciiString *value);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Dict.h
class Dict
{
public:
	AsciiString *setAsciiString(AsciiString value);
};

class StaticNameKey;
extern const StaticNameKey TheKey_teamOwner;
extern const StaticNameKey TheKey_teamName;

// The bracketing calls are the rowed TeamsInfoRec::bfmePrepareRelease and
// TeamsInfoRec::addToIndex.
class TeamsInfoRec
{
public:
	void bfmePrepareRelease(int index);
	void addToIndex(int index);
};

class Rva0019BC00Owner
{
public:
	void apply(int index, AsciiString a, AsciiString b);
	void prepare(int index);
	void finish(int index);

private:
	char m_head[0xC];
	char *m_data;
};

void Rva0019BC00Owner::apply(int index, AsciiString a, AsciiString b)
{
	((TeamsInfoRec *)this)->bfmePrepareRelease(index);
	AsciiStringField *field = (AsciiStringField *)(m_data + (index << 4) + 0xC);
	field->set(((Dict *)&TheKey_teamOwner)->setAsciiString(a));
	field->set(((Dict *)&TheKey_teamName)->setAsciiString(b));
	((TeamsInfoRec *)this)->addToIndex(index);
}
