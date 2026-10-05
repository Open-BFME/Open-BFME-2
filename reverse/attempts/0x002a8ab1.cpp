// ?rva002A8AB1@Rva002A8F24@@QAEPAURva002A8AB1Record@@PAX@Z
// partial score=0.93 date=2026-10-05
// cl: /O1 /MD
// ?rva002A8AB1@Rva002A8F24@@QAEPAURva002A8AB1Record@@PAX@Z 0x002A8AB1 51B
// Scan the pointer range at +0x914/+0x918 and return the first non-null find
// through rowed 0x004E95D4, else null. Null key returns null.
struct Rva002A8AB1Record
{
	char m_pad[0x160];
};

class Rva004E9600
{
public:
	void *rva004E95D4(void *p);
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *key);
};

// ?rva002A8AB1@Rva002A8F24@@QAEPAURva002A8AB1Record@@PAX@Z present-unmatched
Rva002A8AB1Record *Rva002A8F24::rva002A8AB1(void *key)
{
	Rva002A8AB1Record *result = 0;
	if (key != 0)
	{
		Rva004E9600 **cur;
		cur = *(Rva004E9600 ***)((char *)this + 0x914);
		for (; cur != *(Rva004E9600 ***)((char *)this + 0x918); ++cur)
		{
			result = (Rva002A8AB1Record *)(*cur)->rva004E95D4(key);
			if (result != 0)
				break;
		}
	}
	return result;
}
