// cl: /DNDEBUG /MD /EHs-c- /Oy- /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native frame-pointer prologue/epilogue establish /Oy- for this body.
// Access views follow the verified Rva005EA33D unit without asserting
// that its original owning class is also the owner of this method.
#include <map>

struct Rva005EAEAFMap
{
	_STL::map<int, int> values;
	char unknown[0x34 - sizeof(_STL::map<int, int>)];
};

struct Rva005EAEAFMaps
{
	Rva005EAEAFMap *begin;
};

class Rva005FB846
{
public:
	void rva005FB846();
};

struct Rva005EAEAFElem
{
	char m_pad00[4];
	int m_mapIndex;
	float m_a;
	float m_b;
	char m_pad10[4];
	int m_val14;
	char m_pad18[0x20 - 0x18];
	void *m_ptr;
};

struct Rva005EAEAFVec
{
	Rva005EAEAFElem *m_begin;
	Rva005EAEAFElem *m_end;
	Rva005EAEAFElem *m_allocEnd;
};

struct Rva005EAEAFData
{
	char m_pad00[0x10];
	Rva005EAEAFMaps *m_maps;
	char m_pad14[4];
	float m_divisor;
	Rva005EAEAFVec m_ranges[2];
	char m_pad34[8];
	int m_key;
};

class Rva005EAEAF
{
public:
	void rva005EAEAF(int side, int index);
	void rva005EA441();
private:
	char m_pad00[4];
	Rva005EAEAFData *m_data;
	int m_remaining;
};

// Native 0x005EAEAF, 106 bytes, RET 8. Shares the +4 data pointer, +1C
// two ranges and 0x24-byte elements with the existing bodies. The target
// tests element +C against zero, conditionally shows elimination via the
// existing +20 panel pointer, then decrements +8 and dispatches completion.
// Map index +4, map stride 0x34 and data key +3C are native facts; original
// owner/type identities beyond these access views remain unresolved.
void Rva005EAEAF::rva005EAEAF(int side, int index)
{
	Rva005EAEAFElem *element = m_data->m_ranges[side].m_begin + index;
	if (0.0f >= element->m_b)
	{
		if (m_data->m_maps)
		{
			side = m_data->m_key;
			Rva005EAEAFMap *map = m_data->m_maps->begin + element->m_mapIndex;
			if (map->values.lower_bound(side) != map->values.end())
				goto completed;
		}
		((Rva005FB846 *)((char *)element->m_ptr + 8))->rva005FB846();
	}
completed:
	if (--m_remaining <= 0)
		rva005EA441();
}
