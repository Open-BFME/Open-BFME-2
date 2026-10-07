// ?Rva004195ECParse@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.95 date=2026-10-06
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /O1 /arch:SSE /G7
// stlport
// Retail table neighbor "LevelBonus" and exception text identify this parser.
// Its map<int,int> insertion and INI token order follow the retail body.

#include <map>

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
typedef _STL::_Rb_tree_node<IntIntValue> IntIntNode;
typedef _STL::_Rb_tree_iterator<IntIntValue, _STL::_Nonconst_traits<IntIntValue> > IntIntIterator;
typedef _STL::_Rb_tree<int, IntIntValue, _STL::_Select1st<IntIntValue>, _STL::less<int>,
	_STL::allocator<IntIntValue> > MapIntIntTree;
typedef _STL::pair<IntIntIterator, bool> IntIntInsertResult;

// ?Rva004195ECParse@@YAXPAVINI@@PAX1PBX@Z
void Rva004195ECParse(INI *ini, void *, void *levels, const void *)
{
	const int level = ini->scanInt(ini->getNextSubToken("Level"));
	union BonusValue
	{
		float real;
		int integer;
	} bonus;
	bonus.real = ini->dup_002EE10(ini->getNextSubToken("Bonus"));
	IntIntValue value(level, bonus.integer);
	IntIntInsertResult inserted = ((MapIntIntTree *)levels)->insert_unique(value);
	if (!inserted.second)
		throw INIException(1, "Duplicate LevelBonus entries for level %d", level);
}
