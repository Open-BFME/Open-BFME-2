// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// Third batch of STLport _Construct<T> placement-copy helpers, same-shape
// siblings of the rowed _Construct<AsciiString> at 0x0002C485 (45 bytes; see
// stlport_construct_asciistring.cpp). Each body is the null-guarded
// placement-new copy over a single element: the copy delegates out-of-line
// to T's own rowed copy ctor, and __EH_prolog resolves via its matched row.
// Unlike the opaque-struct batches, these T's come from the real STLport
// headers (<vector>, and _STL::pair over a minimal AsciiString declaration):
// the headers declare but do not define the copy ctors, so the calls stay
// out-of-line and resolve through their rows.

#include <memory>
#include <vector>
#include <list>

class AsciiString
{
public:
	AsciiString(const AsciiString &other);

private:
	char m_pad[4];
};

struct NoCaseTreeValue4
{
	char m_body[4];
};

struct Coord3D
{
	int m_pad;
};

enum ScienceType
{
	SCIENCE_INVALID = -1
};

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> ConstructProbePair;
typedef _STL::vector<unsigned int> ConstructProbeVec;
typedef _STL::pair<const int, _STL::vector<unsigned int> > ConstructProbePairIV;
typedef _STL::vector<ScienceType> ConstructProbeSciVec;
typedef _STL::list<Coord3D> ConstructProbeCoordList;
typedef _STL::pair<const AsciiString, char> ConstructProbePairC;

template void _STL::_Construct<ConstructProbeVec, ConstructProbeVec>(ConstructProbeVec *, const ConstructProbeVec &);
template void _STL::_Construct<ConstructProbePair, ConstructProbePair>(ConstructProbePair *, const ConstructProbePair &);
template void _STL::_Construct<ConstructProbePairIV, ConstructProbePairIV>(ConstructProbePairIV *, const ConstructProbePairIV &);
template void _STL::_Construct<ConstructProbeSciVec, ConstructProbeSciVec>(ConstructProbeSciVec *, const ConstructProbeSciVec &);
template void _STL::_Construct<ConstructProbeCoordList, ConstructProbeCoordList>(ConstructProbeCoordList *, const ConstructProbeCoordList &);
template void _STL::_Construct<ConstructProbePairC, ConstructProbePairC>(ConstructProbePairC *, const ConstructProbePairC &);
