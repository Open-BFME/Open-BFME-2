// cl: /O1 /G7 /Oy- /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva002B471B@Rva002B471B@@QAE_NXZ, retail 0x002B471B, 132 bytes.
// Walks every record of every entry of the table at +4 (entry count from the 0x1C-byte
// entry array at table +0x18..+0x1C, record count through the rowed 0x003F4DAE, record
// through the rowed 0x003F468D) and, for each record whose word at +0x44 is clear, looks the
// pointer at record +0x14 up in the pointer array at +0x1C..+0x20 with the rowed STLport
// find 0x0020E873; a miss fails the check. Evidence: target bytes and the rowed callees (the
// rowed record accessor is declared to return int, but retail dereferences it, so the result
// is cast); names are neutral views.
#include <vector>
#include <algorithm>

class CreateAHeroData;

struct Rva002B471BRecord
{
	char m_pad[0x14];
	CreateAHeroData *m_key14;
	char m_pad18[0x44 - 0x18];
	int m_flag44;
};

struct Rva002B471BEntry
{
	char m_pad[0x1C];
};

class Rva003F468D
{
public:
	int rva003F468D(int a, int b);
	int rva003F4DAE(int a);
	char m_pad[0x18];
	_STL::vector<Rva002B471BEntry> m_entries18;
};

class Rva002B471B
{
public:
	bool rva002B471B();
private:
	char m_pad0[4];
	Rva003F468D *m_table4;
	char m_pad8[0x1C - 8];
	CreateAHeroData **m_first1C;
	CreateAHeroData **m_last20;
};

bool Rva002B471B::rva002B471B()
{
	int entries = (int)m_table4->m_entries18.size();
	for (int i = 0; i < entries; ++i)
	{
		int records = m_table4->rva003F4DAE(i);
		for (int j = 0; j < records; ++j)
		{
			Rva002B471BRecord *record = (Rva002B471BRecord *)m_table4->rva003F468D(i, j);
			if (record->m_flag44 == 0)
			{
				CreateAHeroData *key = record->m_key14;
				if (_STL::find(m_first1C, m_last20, key) == m_last20)
					return false;
			}
		}
	}
	return true;
}
