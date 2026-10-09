// cl: /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva004194D6@Rva004194D6@@QAEXXZ, retail 0x004194D6, 52 bytes.
// State gate at +0x38 with 8-float threshold check at +0x14 against global at 0x00BBAEAC; sets 1 or 0.
// Evidence: callers 0x00419510 0x00419577 share +0x38 state; prev stlport next ConstIntGetters; float loop with comiss ja matches SSE shape.
// The data ledger identifies the shared read-only operand as float +0.0.

#include <map>

class Rva004194D6
{
public:
	void rva004194D6();
	bool rva0041950A();
	float rva00419561(int key, float numerator, float denominator, int index);
private:
	char m_pad0[4];
	_STL::map<int, float> m_curve;
	int m_10;
	float m_floats[8];
	char m_34;
	char m_pad35[3];
	int m_38;
};

void Rva004194D6::rva004194D6()
{
	if (m_38 != 2)
		return;
	if (m_10 >= 100) {
		m_38 = 0;
		return;
	}
	for (int i = 0; i < 8; i++) {
		if (m_floats[i] > 0.0f) {
			m_38 = 1;
			return;
		}
	}
	m_38 = 0;
}

bool Rva004194D6::rva0041950A()
{
	if (m_38 == 2)
		rva004194D6();
	return m_38;
}

// ?rva00419561@Rva004194D6@@QAEMHMMH@Z @0x00419561
// Curve lookup: the int-keyed tree at +4 holds a float per key; the result is
// the floor entry's value plus 1.0 scaled by the table float (itself rescaled
// by numerator/denominator when the +0x34 flag is set), or the table float
// below the first key. Out-of-range index and state 0 return the shared +0.0.
float Rva004194D6::rva00419561(int key, float numerator, float denominator, int index)
{
	if (index < 0 || (unsigned)index >= 8)
		return 0.0f;
	if (m_38 == 2)
		rva004194D6();
	if (m_38 == 0)
		return 0.0f;
	float base = m_floats[index];
	if (m_34)
		base = (numerator / denominator) * base;
	_STL::map<int, float>::iterator it = m_curve.lower_bound(key);
	if (it == m_curve.end() || it->first > key)
	{
		if (it == m_curve.begin())
			return base;
		--it;
	}
	return (it->second + 1.0) * base;
}

// Retail table neighbour "LevelBonus": INI field parser for the +4 curve, one
// "Level <int> Bonus <real>" pair per call. A repeated level is an INI error.
class INI
{
public:
	const char *getNextSubToken(const char *expected);
	int scanInt(const char *token);
	float dup_002EE10(const char *token);
};

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();
};

typedef _STL::pair<const int, int> IntIntValue;
typedef _STL::_Rb_tree<int, IntIntValue, _STL::_Select1st<IntIntValue>, _STL::less<int>,
	_STL::allocator<IntIntValue> > MapIntIntTree;

// ?Rva004195ECParse@@YAXPAVINI@@PAX1PBX@Z @0x004195EC
// The insert is the shared <int,int> tree body: the entry is built as a float
// pair and handed over as the same-layout int pair.
void Rva004195ECParse(INI *ini, void *, void *levels, const void *)
{
	const int level = ini->scanInt(ini->getNextSubToken("Level"));
	const char *token = ini->getNextSubToken("Bonus");
	_STL::pair<const int, float> value(level, ini->dup_002EE10(token));
	_STL::pair<MapIntIntTree::iterator, bool> inserted = ((MapIntIntTree *)levels)->insert_unique(*(IntIntValue *)&value);
	if (!inserted.second)
		throw INIException(1, "Duplicate LevelBonus entries for level %d", level);
}
