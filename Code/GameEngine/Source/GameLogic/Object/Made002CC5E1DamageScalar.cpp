// cl: /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// The DamageNugget "DamageScalar" field (BFME2 FieldParse table at 0x00864264,
// "DamageScalar" -> 0x00508862, offset 0x168) and the vector growth path it
// reaches. The nugget keeps the address-derived name its ctor 0x00507C2D
// carries; its implicit destructor (0x00508684) and ??_G (0x00508668) come
// out of that ctor's TU, Made002CC5E1Ctor.cpp, where the vtable is emitted.
//
// Target evidence:
//   0x00508862  parser: builds an 8-byte entry on the stack (filter ctor
//               0x003623E5 at +0, dtor 0x00360D26), stores
//               INI::dup_002EE10(getNextToken(0)) at +4, parses the filter
//               through 0x00361CA5(ini, instance, &entry.filter, 0), then
//               push_back(entry) on the store.
//   0x0050882B  that push_back: _Construct 0x0060C9D9 (two-dword copy) or
//               _M_insert_overflow 0x005085B6.
//   0x005085B6  the overflow path: raw (bytes, hint) allocator 0x00523D6C,
//               copy 0x004C3121, fill 0x00507958, out-of-line _M_clear
//               0x00507C0F whose destroy loop reaches 0x00495C43 -> 0x00360D26.
// Inferred: the entry is { filter, Real scalar }, which is what the field name
// and the percent scanner say; the filter keeps the opaque Rva003623E5Filter
// name its other pins use.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	float dup_002EE10(const char *token);
};

class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
	~Rva003623E5Filter();

private:
	int m_index;
};

struct Made002CC5E1DamageScalar
{
	Rva003623E5Filter filter;
	float scalar;
};

void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);

typedef _STL::vector<Made002CC5E1DamageScalar, _STL::allocator<Made002CC5E1DamageScalar> > Made002CC5E1DamageScalarVec;

class Made002CC5E1
{
public:
	static void parseDamageScalar(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseDamageScalar@Made002CC5E1@@SAXPAVINI@@PAX1PBX@Z
void Made002CC5E1::parseDamageScalar(INI *ini, void *instance, void *store, const void * /*userData*/)
{
	Made002CC5E1DamageScalar entry;
	entry.scalar = ini->dup_002EE10(ini->getNextToken());
	iniParseObjectFilter(ini, instance, &entry.filter, 0);
	((Made002CC5E1DamageScalarVec *)store)->push_back(entry);
}
