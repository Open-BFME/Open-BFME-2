// ?rva002B466E@Rva002B466E@@QAE_NXZ
// partial score=0.97 date=2026-10-10
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

// ?rva002B466E@Rva002B466E@@QAE_NXZ, retail 0x002B466E, 173 bytes.
// Sibling of the check above (same table walk and records): a record whose key is missing from
// the pointer array may still pass when the pair table at +0x10..+0x14 holds the key and the
// owner's counter (+0x0C owner, +0x7C) is below the pair's limit. Evidence: target bytes.
struct Rva002B466EOwner
{
	char m_pad[0x7C];
	int m_count7C;
};

struct Rva002B466EPair
{
	CreateAHeroData *m_key;
	int m_limit;
};

class Rva002B466E
{
public:
	bool rva002B466E();
private:
	char m_pad0[4];
	Rva003F468D *m_table4;
	char m_pad8[4];
	Rva002B466EOwner *m_owner0C;
	Rva002B466EPair *m_pairs10;
	Rva002B466EPair *m_pairsEnd14;
	char m_pad18[4];
	CreateAHeroData **m_first1C;
	CreateAHeroData **m_last20;
};

bool Rva002B466E::rva002B466E()
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
				{
					Rva002B466EPair *end = m_pairsEnd14;
					Rva002B466EPair *pair = m_pairs10;
					for (;;)
					{
						if (pair == end)
							return false;
						if (pair->m_key == key)
							break;
						++pair;
					}
					if (m_owner0C->m_count7C >= pair->m_limit)
						return false;
				}
			}
		}
	}
	return true;
}
