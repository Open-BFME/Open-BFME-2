// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD
// stlport
// ?parse@LibraryMapsParser@@QAE_NAAVDataChunkInput@@PAVDataChunkInfo@@@Z @0x0032D742 153B
// Evidence: vslot slot 1 offset 0x4 of vtable 0x00C0D924 for LibraryMapsParser ctor 0x00329F83; donor open-bfme-1 game/GameEngine/Source/GameLogic/Map/LibraryMapsParserParse.cpp; all callees rowed
#include <vector>
#include "ascii_string.h"

class DataChunkInput
{
public:
	int readInt();
	AsciiString rva0030750A();
};

class DataChunkInfo;

struct BfmeE12 { float x, y, z; };

class LibraryMapsParser
{
public:
	bool parse(DataChunkInput &file, DataChunkInfo *info);

private:
	char m_base[0xC];
	_STL::vector<AsciiString> *m_lists;
	int *m_count;
};

bool LibraryMapsParser::parse(DataChunkInput &file, DataChunkInfo *info)
{
	(void)info;
	_STL::vector<AsciiString> values;
	int count = file.readInt();
	if (count > 0)
	{
		values.reserve(count);
		do
		{
			values.push_back(file.rva0030750A());
			--count;
		} while (count > 0);
	}
	((_STL::vector<BfmeE12> *)m_lists)[(*m_count)++].swap((_STL::vector<BfmeE12> &)values);
	return true;
}
