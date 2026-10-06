// cl: /MD /EHsc /DNDEBUG
//
// ??0Rva003623E5Member@@QAE@XZ at 0x003623E5 (82 bytes).
// The ctor resets its 4-byte handle to -1, builds a 0x94-byte default record
// with the rowed 0x360F55 ctor, registers/deduplicates it through 0x361790,
// stores the returned pool index, then destroys the local through 0x360FDB.
// The 0x361790 helper's identity is unknown; its pointer argument and integer
// return are established by this call site and the callee's table scan.

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);

private:
	unsigned char m_bytes[28];
};

class Rva00360F55
{
public:
	Rva00360F55();
	~Rva00360F55();

	unsigned char m_vectors[0x48];
	BfmeFixedStorage0004543D m_first;
	BfmeFixedStorage0004543D m_second;
	int m_value80;
	int m_value84;
	unsigned char m_flag88;
	unsigned char m_pad89[3];
	int m_value8C;
	int m_value90;
};

void Rva00360CB0Release(int *indexHolder);
int __cdecl Rva00361790(Rva00360F55 *record);

extern const BfmeFixedStorage0004543D g_defaultStorage009FEFA4;

class Rva00045411BitSet
{
public:
	unsigned char m_bytes[28];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D first,
	                      BfmeFixedStorage0004543D second);
	void rva00362192(Rva00045411BitSet first, BfmeFixedStorage0004543D second);

private:
	unsigned int m_record;
};

Rva003623E5Member::Rva003623E5Member()
	: m_record(-1)
{
	Rva00360F55 defaultRecord;
	m_record = Rva00361790(&defaultRecord);
}

class Rva00360D26Member
{
public:
	Rva00360D26Member();

private:
	unsigned int m_record;
};

// The 4-byte filter handle's constructor folds with the address-derived member
// constructor above. Its 0x94-byte default record is a temporary, not its size.
Rva00360D26Member::Rva00360D26Member()
	: m_record(-1)
{
	Rva00360F55 defaultRecord;
	m_record = Rva00361790(&defaultRecord);
}

// 0x362087 (153B): release the previous pool index, then register a rebuilt
// 0x94-byte record. Target merges the two 28-byte inputs at +0x48/+0x64 and
// sets +0x88 when any dword in the first input is nonzero; these field labels
// describe offsets only, not recovered domain names.
void Rva003623E5Member::initFromStorages(
	BfmeFixedStorage0004543D first,
	BfmeFixedStorage0004543D second)
{
	Rva00360CB0Release((int *)&m_record);
	Rva00360F55 record;
	record.m_flag88 = 0;
	record.m_value80 = 1;
	for (unsigned int offset = 0; offset < 28; offset += 4)
	{
		*(unsigned int *)((unsigned char *)&record.m_first + offset) |=
			*(unsigned int *)((unsigned char *)&first + offset);
	}
	for (unsigned int offset = 0; offset < 28; offset += 4)
	{
		*(unsigned int *)((unsigned char *)&record.m_second + offset) |=
			*(unsigned int *)((unsigned char *)&second + offset);
	}
	for (unsigned int index = 0; index < 7; ++index)
	{
		if (((unsigned int *)&first)[index] != 0)
		{
			record.m_flag88 = 1;
			break;
		}
	}
	m_record = Rva00361790(&record);
}

void Rva003623E5Member::rva00362192(Rva00045411BitSet first, BfmeFixedStorage0004543D second)
{
	Rva00360CB0Release((int *)&m_record);
	Rva00360F55 record;
	record.m_flag88 = 0;
	record.m_value80 = 2;
	for (unsigned int offset = 0; offset < 28; offset += 4)
	{
		*(unsigned int *)((unsigned char *)&record.m_first + offset) |=
			*(unsigned int *)((unsigned char *)&first + offset);
	}
	for (unsigned int offset = 0; offset < 28; offset += 4)
	{
		*(unsigned int *)((unsigned char *)&record.m_second + offset) |=
			*(unsigned int *)((unsigned char *)&second + offset);
	}
	for (unsigned int index = 0; index < 7; ++index)
	{
		if (((unsigned int *)&first)[index] != 0)
		{
			record.m_flag88 = 1;
			m_record = Rva00361790(&record);
			return;
		}
	}
	initFromStorages(g_defaultStorage009FEFA4, g_defaultStorage009FEFA4);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0Rva003623E5Filter@@QAE@XZ=??0Rva003623E5Member@@QAE@XZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?construct@Rva003623E5Member@@QAEXXZ=??0Rva003623E5Member@@QAE@XZ")

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_defaultStorage009FEFA4@@3VBfmeFixedStorage0004543D@@B=?g_00DFEFA4StoragePrototype@@3PAEA")
