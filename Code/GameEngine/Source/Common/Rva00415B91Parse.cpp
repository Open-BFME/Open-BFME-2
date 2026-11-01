// cl: /O1 /G7 /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception /D_STLP_USE_STATIC_LIB
// stlport
//
// Rva00415B91Parse, retail 0x00415B91 (197 B). INI block callback of the CrowdResponse threshold list
// (WorldBuilder twin 0x00C65800, "CrowdResponse: Multiple Thresholds with minimum units %d"): reads the
// minimum-unit count, parses one threshold record with the rowed Rva0041573F::rva00415218, copies the
// record next to the count into the owner container (store) through the rowed insert 0x00415A55 and
// refuses a count that is already present. Evidence: target bytes, WorldBuilder twin and the rowed
// callees (default ctor 0x00415688, copy ctor 0x0041573F, dtor 0x004156BC). Names stay address-derived.
#include "Common/INIException.h"

#include "../../Include/Common/INI/INI.h"

class Rva0041573F
{
public:
	Rva0041573F(const Rva0041573F &src);
	~Rva0041573F();
	void rva00415218(INI *ini);
private:
	char m_data[0x1CC];
};

class Rva00415688 : public Rva0041573F
{
public:
	Rva00415688();
};

class Rva0041579E;

struct Rva00415A55Result
{
	__forceinline Rva00415A55Result(void *node, bool inserted) : m_node(node), m_inserted(inserted) {}
	void *m_node;
	bool m_inserted;
};

struct Rva0041580E
{
	Rva00415A55Result rva00415A55(const Rva0041579E &value);
};

struct Rva00415B91Entry
{
	__forceinline Rva00415B91Entry(int key, const Rva0041573F &value) : m_key(key), m_value(value) {}
	int m_key;
	Rva0041573F m_value;
};

static __forceinline const Rva0041579E &asEntry(const Rva00415B91Entry &entry)
{
	return *(const Rva0041579E *)&entry;
}

void Rva00415B91Parse(INI *ini, void *instance, void *store, const void *userData)
{
	int minUnits = ini->scanInt(ini->getNextToken(0));
	Rva00415688 record;
	record.rva00415218(ini);
	bool inserted;
	{
		Rva00415A55Result result = ((Rva0041580E *)store)->rva00415A55(asEntry(Rva00415B91Entry(minUnits, record)));
		inserted = result.m_inserted;
	}
	if (!inserted)
		throw INIException(3, "CrowdResponse: Multiple Thresholds with minimum units %d", minUnits);
}
