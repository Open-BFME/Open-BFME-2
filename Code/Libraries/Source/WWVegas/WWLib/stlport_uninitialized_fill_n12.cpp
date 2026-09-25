// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Second STLport __uninitialized_fill_n<T> batch (37 bytes): stride-12
// siblings of the rowed fill_n at 0x000BBB83. Same recipe as
// stlport_uninitialized_fill_n.cpp: each body null-guards the count, then
// constructs each element out-of-line through T's own rowed _Construct
// (declared-only specialization below), striding by sizeof(T) = 12. The
// bodies ride the vector fill constructor, instantiated per T below. Game
// types are modeled as 12-byte payloads with the struct/class-ness of their
// rowed copy ctors; strings and vectors come from the real headers. Siblings
// calling a _Construct dupe rather than its true address land as gen-alias
// rows.

#include <memory>
#include <vector>
#include <string>

class RvaSmartPtr12
{
public:
	RvaSmartPtr12();
	RvaSmartPtr12(const RvaSmartPtr12 &other);

private:
	unsigned int m_body[3];
};

struct BfmeStringRecord0022074B
{
public:
	BfmeStringRecord0022074B();
	BfmeStringRecord0022074B(const BfmeStringRecord0022074B &other);
	unsigned int m_body[3];
};

enum ScienceType
{
	SCIENCE_INVALID = -1
};

struct BfmeStringRecord00395E75
{
public:
	BfmeStringRecord00395E75();
	BfmeStringRecord00395E75(const BfmeStringRecord00395E75 &other);
	unsigned int m_body[3];
};

struct BfmeStringRecord00466E64
{
public:
	BfmeStringRecord00466E64();
	BfmeStringRecord00466E64(const BfmeStringRecord00466E64 &other);
	unsigned int m_body[3];
};

struct BfmeStringRecord005F93E3
{
public:
	BfmeStringRecord005F93E3();
	BfmeStringRecord005F93E3(const BfmeStringRecord005F93E3 &other);
	unsigned int m_body[3];
};

struct BfmePod88
{
	char m_body[88];
};

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > FillStdString;
typedef _STL::vector<ScienceType> FillSciVec;
typedef _STL::vector<unsigned int> FillUIntVec;
typedef _STL::vector<BfmePod88> FillPodVec;

namespace _STL {
template<> void _Construct<RvaSmartPtr12, RvaSmartPtr12>(RvaSmartPtr12 *, const RvaSmartPtr12 &);
template<> void _Construct<FillStdString, FillStdString>(FillStdString *, const FillStdString &);
template<> void _Construct<BfmeStringRecord0022074B, BfmeStringRecord0022074B>(BfmeStringRecord0022074B *, const BfmeStringRecord0022074B &);
template<> void _Construct<FillSciVec, FillSciVec>(FillSciVec *, const FillSciVec &);
template<> void _Construct<BfmeStringRecord00395E75, BfmeStringRecord00395E75>(BfmeStringRecord00395E75 *, const BfmeStringRecord00395E75 &);
template<> void _Construct<FillUIntVec, FillUIntVec>(FillUIntVec *, const FillUIntVec &);
template<> void _Construct<BfmeStringRecord00466E64, BfmeStringRecord00466E64>(BfmeStringRecord00466E64 *, const BfmeStringRecord00466E64 &);
template<> void _Construct<FillPodVec, FillPodVec>(FillPodVec *, const FillPodVec &);
template<> void _Construct<BfmeStringRecord005F93E3, BfmeStringRecord005F93E3>(BfmeStringRecord005F93E3 *, const BfmeStringRecord005F93E3 &);
}

template _STL::vector<RvaSmartPtr12, _STL::allocator<RvaSmartPtr12> >::vector(unsigned int, const RvaSmartPtr12 &, const _STL::allocator<RvaSmartPtr12> &);
template _STL::vector<FillStdString, _STL::allocator<FillStdString> >::vector(unsigned int, const FillStdString &, const _STL::allocator<FillStdString> &);
template _STL::vector<BfmeStringRecord0022074B, _STL::allocator<BfmeStringRecord0022074B> >::vector(unsigned int, const BfmeStringRecord0022074B &, const _STL::allocator<BfmeStringRecord0022074B> &);
template _STL::vector<FillSciVec, _STL::allocator<FillSciVec> >::vector(unsigned int, const FillSciVec &, const _STL::allocator<FillSciVec> &);
template _STL::vector<BfmeStringRecord00395E75, _STL::allocator<BfmeStringRecord00395E75> >::vector(unsigned int, const BfmeStringRecord00395E75 &, const _STL::allocator<BfmeStringRecord00395E75> &);
template _STL::vector<FillUIntVec, _STL::allocator<FillUIntVec> >::vector(unsigned int, const FillUIntVec &, const _STL::allocator<FillUIntVec> &);
template _STL::vector<BfmeStringRecord00466E64, _STL::allocator<BfmeStringRecord00466E64> >::vector(unsigned int, const BfmeStringRecord00466E64 &, const _STL::allocator<BfmeStringRecord00466E64> &);
template _STL::vector<FillPodVec, _STL::allocator<FillPodVec> >::vector(unsigned int, const FillPodVec &, const _STL::allocator<FillPodVec> &);
template _STL::vector<BfmeStringRecord005F93E3, _STL::allocator<BfmeStringRecord005F93E3> >::vector(unsigned int, const BfmeStringRecord005F93E3 &, const _STL::allocator<BfmeStringRecord005F93E3> &);
