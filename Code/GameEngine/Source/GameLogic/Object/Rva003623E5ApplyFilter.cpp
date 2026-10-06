// cl: /MD /EHsc /DNDEBUG
//
// ?applyFilter@Rva003623E5Filter@@QAEXVBfmeFixedStorage0004543D@@@Z
// RVA 0x00362120 size 114. Target pin evidence: five module-data constructor
// callers pass a 28-byte BfmeFixedStorage value, including the convergent
// caller at 0x4C24AE. The 4-byte filter member layout follows the folded ctor
// at 0x3623E5 and teardown at 0x360D26. Exact target bytes show it releases
// the old handle at this+0, constructs a local 0x94-byte record, sets +0x80=3
// and +0x88=1, ORs the argument into +0x64, registers it via 0x361790, and
// stores the returned index. Record offsets follow the matched
// Rva003623E5Member::initFromStorages sibling at 0x362087; the assignments and
// single-storage merge are directly visible in this target's instructions.

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);

private:
	unsigned char m_bytes[28];
};

class Rva003623E5Filter
{
public:
	void applyFilter(BfmeFixedStorage0004543D storage);

private:
	int m_record;
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

void Rva003623E5Filter::applyFilter(BfmeFixedStorage0004543D storage)
{
	Rva00360CB0Release(&m_record);
	Rva00360F55 record;
	record.m_flag88 = 1;
	record.m_value80 = 3;
	for (unsigned int offset = 0; offset < 28; offset += 4)
	{
		*(unsigned int *)((unsigned char *)&record.m_second + offset) |=
			*(unsigned int *)((unsigned char *)&storage + offset);
	}
	m_record = Rva00361790(&record);
}
