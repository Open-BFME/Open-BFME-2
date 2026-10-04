// ?Rva00417FF0Parse@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.93 date=2026-10-04
// cl: /G7 /O1 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?Rva00417FF0Parse@@YAXPAVINI@@PAX1PBX@Z @0x00417FF0 112B.
// Chain lane: parses BonusForLevel record via INI::initFromINI with table
// g_00C3A658 into Rva00417AB8 24B local, inserts pair<int,BfmePod24> into
// map at store arg via rowed insert_unique 0x00417D57, throws INIException
// on duplicate MinLevel. Evidence: caller init 0x00417AB8 (rowed), table VA
// 0x0083A658, dup string, TI1 INIException, _CxxThrowException pin.
#include <map>

struct FieldParse;
extern const FieldParse g_00C3A658[];

class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
};

class Rva00417AB8
{
public:
	Rva00417AB8 *rva00417AB8();
};

struct BfmePod24
{
	int a[6];
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
};

// ?Rva00417FF0Parse@@YAXPAVINI@@PAX1PBX@Z present-unmatched
void __cdecl Rva00417FF0Parse(INI *ini, void *, void *store, const void *)
{
	BfmePod24 tmp;
	((Rva00417AB8 *)&tmp)->rva00417AB8();
	ini->initFromINI(&tmp, g_00C3A658);
	_STL::pair<_STL::_Rb_tree<int, _STL::pair<const int, BfmePod24>, _STL::_Select1st<_STL::pair<const int, BfmePod24> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod24> > >::iterator, bool> res =
		((_STL::map<int, BfmePod24> *)store)->insert(_STL::pair<const int, BfmePod24>(tmp.a[0], tmp));
	if (!res.second)
		throw INIException(1, "Two BonusForLevel entries with duplicate MinLevel of %d", tmp.a[0]);
}
