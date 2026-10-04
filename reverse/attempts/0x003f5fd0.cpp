// ??4?$vector@URva003F610FElement@@V?$allocator@URva003F610FElement@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z
// partial score=0.95 date=2026-10-04
// cl: /G7 /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector growth paths and their fill/copy helpers for BFME2
// element types whose other STL helpers are already matched, dedicated TU.
// Each element is reduced to its footprint (size read from the owning TU's
// definition) with an out-of-line copy ctor and dtor: these bodies only
// move elements through _Construct, which is declared as an explicit
// specialization so the copies call the element's matched _Construct row.
//
// Target evidence per body: it is the unowned retail caller of that element's
// matched _Construct / __uninitialized_fill_n rows, byte-identical with
// relocations masked; the remaining callees are rows or pins to matched
// bodies they reproduce. /G7 emits retail's imul element scaling (the
// AnimSet sibling's IMUL recipe), bfmealloc keeps allocate a two-argument
// call and _STLP_NO_EXCEPTIONS drops the EH frame retail does not have.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// 32-byte element; layout owner stlport_bfmeassignrecord32_destroy.cpp.
struct BfmeAssignRecord32 { char m_pad[32]; public: BfmeAssignRecord32(const BfmeAssignRecord32 &); ~BfmeAssignRecord32(); };
// 8-byte element; layout owner StlportVectorDtorChains.cpp.
class Rva002390CB { char m_pad[8]; public: Rva002390CB(const Rva002390CB &); ~Rva002390CB(); };
// 20-byte element; layout owner Rva003371B1Copy.cpp.
class Rva003371B1 { char m_pad[20]; public: Rva003371B1(const Rva003371B1 &); ~Rva003371B1(); };
// 20-byte element; layout owner stlport_vector_stringrecord_5ed5f3_allocate_copy.cpp.
struct BfmeStringRecord005ED5F3 { char m_pad[20]; public: BfmeStringRecord005ED5F3(const BfmeStringRecord005ED5F3 &); ~BfmeStringRecord005ED5F3(); };
// 36-byte element; layout owner stlport_vector_rva0007bb16_destroy.cpp.
struct Rva0007BB16Record { char m_pad[36]; public: Rva0007BB16Record(const Rva0007BB16Record &); ~Rva0007BB16Record(); };
// 36-byte element; layout owner StringContainerRecordCopyBFME2.cpp.
struct BfmeRecord001ECAF9 { char m_pad[36]; public: BfmeRecord001ECAF9(const BfmeRecord001ECAF9 &); ~BfmeRecord001ECAF9(); };
// 36-byte element; layout owner StringVectorRecordCopyBFME2.cpp.
struct BfmeVectorRecord002AF478 { char m_pad[36]; public: BfmeVectorRecord002AF478(const BfmeVectorRecord002AF478 &); ~BfmeVectorRecord002AF478(); };
// 16-byte element; layout owner StringRecordCopyBFME2.cpp.
struct BfmeStringRecord0040360E { char m_pad[16]; public: BfmeStringRecord0040360E(const BfmeStringRecord0040360E &); ~BfmeStringRecord0040360E(); };
// 24-byte element; layout owner StringRecordCopyBFME2.cpp.
struct BfmeStringRecord00404BF3 { char m_pad[24]; public: BfmeStringRecord00404BF3(const BfmeStringRecord00404BF3 &); ~BfmeStringRecord00404BF3(); };

// 24-byte element; layout owner NarrowStringRecord00427F75Helpers.cpp.
struct BfmeNarrowRecord00427F75 { char m_pad[24]; public: BfmeNarrowRecord00427F75(const BfmeNarrowRecord00427F75 &); ~BfmeNarrowRecord00427F75(); };
// 128-byte element; layout owner stlport_pod_vector_bodies.cpp.
struct BfmePod128 { char m_pad[128]; public: BfmePod128(const BfmePod128 &); ~BfmePod128(); };
// 216-byte element; layout owner stlport_pod_vector_bodies.cpp.
struct BfmePod216 { char m_pad[216]; public: BfmePod216(const BfmePod216 &); ~BfmePod216(); };
// 248-byte element; layout owner stlport_pod_vector_bodies.cpp.
struct BfmePod248 { char m_pad[248]; public: BfmePod248(const BfmePod248 &); ~BfmePod248(); };
// 252-byte element; layout owner stlport_pod_vector_bodies.cpp.
struct BfmePod252 { char m_pad[252]; public: BfmePod252(const BfmePod252 &); ~BfmePod252(); };
// 20-byte element; layout owner stlport_vector_stringrecord_00204a30_allocate_copy.cpp.
struct BfmeStringRecord00204A30 { char m_pad[20]; public: BfmeStringRecord00204A30(const BfmeStringRecord00204A30 &); ~BfmeStringRecord00204A30(); };
// 20-byte element; layout owner stlport_vector_stringrecord_2cf4c6_allocate_copy.cpp.
struct BfmeStringRecord002CF4C6 { char m_pad[20]; public: BfmeStringRecord002CF4C6(const BfmeStringRecord002CF4C6 &); ~BfmeStringRecord002CF4C6(); };
// 20-byte element; layout owner stlport_vector_stringrecord_3b3f78_allocate_copy.cpp.
struct BfmeStringRecord003B3F78 { char m_pad[20]; public: BfmeStringRecord003B3F78(const BfmeStringRecord003B3F78 &); ~BfmeStringRecord003B3F78(); };
// 24-byte element; layout owner stlport_vector_rva000bb491_allocate_copy.cpp.
class Rva000BB491 { char m_pad[24]; public: Rva000BB491(const Rva000BB491 &); ~Rva000BB491(); };
// 24-byte element; layout owner stlport_vector_rva000bb4ac_allocate_copy.cpp.
class Rva000BB4AC { char m_pad[24]; public: Rva000BB4AC(const Rva000BB4AC &); ~Rva000BB4AC(); };
// 48-byte element; layout owner StlportVectorInsertOverflowRva003F610F.cpp.
struct Rva003F610FElement { char m_pad[48]; public: Rva003F610FElement(const Rva003F610FElement &); Rva003F610FElement &operator=(const Rva003F610FElement &); ~Rva003F610FElement(); };
// 12-byte element; layout owner Rva004F6352UninitializedCopy.cpp.
struct Rva004F6352 { char m_pad[12]; public: Rva004F6352(const Rva004F6352 &); ~Rva004F6352(); };
// 80-byte element; layout owner StlportVectorOverflowRva00520211.cpp.
struct Rva00520211Element { char m_pad[80]; public: Rva00520211Element(const Rva00520211Element &); ~Rva00520211Element(); };
// 84-byte element; layout owner stlport_construct_rva585B16.cpp.
class Rva00585B16 { char m_pad[84]; public: Rva00585B16(const Rva00585B16 &); ~Rva00585B16(); };

// 8-byte element; layout owner stlport_vector_rva00151dab_clear.cpp.
class Rva00151DAB { char m_pad[8]; public: Rva00151DAB(const Rva00151DAB &); ~Rva00151DAB(); };
// 76-byte element; layout owner Rva00153729Dtor.cpp.
struct Rva00153729 { char m_pad[76]; public: Rva00153729(const Rva00153729 &); ~Rva00153729(); };
// 8-byte element; layout owner StlportVectorDtorChains.cpp.
class BfmeStringTailRecord156 { char m_pad[8]; public: BfmeStringTailRecord156(const BfmeStringTailRecord156 &); ~BfmeStringTailRecord156(); };
namespace _STL
{
template <> void _Construct<BfmeAssignRecord32, BfmeAssignRecord32>(BfmeAssignRecord32 *, const BfmeAssignRecord32 &);
template <> void _Construct<Rva002390CB, Rva002390CB>(Rva002390CB *, const Rva002390CB &);
template <> void _Construct<Rva003371B1, Rva003371B1>(Rva003371B1 *, const Rva003371B1 &);
template <> void _Construct<BfmeStringRecord005ED5F3, BfmeStringRecord005ED5F3>(BfmeStringRecord005ED5F3 *, const BfmeStringRecord005ED5F3 &);
template <> void _Construct<Rva0007BB16Record, Rva0007BB16Record>(Rva0007BB16Record *, const Rva0007BB16Record &);
template <> void _Construct<BfmeRecord001ECAF9, BfmeRecord001ECAF9>(BfmeRecord001ECAF9 *, const BfmeRecord001ECAF9 &);
template <> void _Construct<BfmeVectorRecord002AF478, BfmeVectorRecord002AF478>(BfmeVectorRecord002AF478 *, const BfmeVectorRecord002AF478 &);
template <> void _Construct<BfmeStringRecord0040360E, BfmeStringRecord0040360E>(BfmeStringRecord0040360E *, const BfmeStringRecord0040360E &);
template <> void _Construct<BfmeStringRecord00404BF3, BfmeStringRecord00404BF3>(BfmeStringRecord00404BF3 *, const BfmeStringRecord00404BF3 &);
template <> void _Construct<BfmeNarrowRecord00427F75, BfmeNarrowRecord00427F75>(BfmeNarrowRecord00427F75 *, const BfmeNarrowRecord00427F75 &);
template <> void _Construct<BfmePod128, BfmePod128>(BfmePod128 *, const BfmePod128 &);
template <> void _Construct<BfmePod216, BfmePod216>(BfmePod216 *, const BfmePod216 &);
template <> void _Construct<BfmePod248, BfmePod248>(BfmePod248 *, const BfmePod248 &);
template <> void _Construct<BfmePod252, BfmePod252>(BfmePod252 *, const BfmePod252 &);
template <> void _Construct<BfmeStringRecord00204A30, BfmeStringRecord00204A30>(BfmeStringRecord00204A30 *, const BfmeStringRecord00204A30 &);
template <> void _Construct<BfmeStringRecord002CF4C6, BfmeStringRecord002CF4C6>(BfmeStringRecord002CF4C6 *, const BfmeStringRecord002CF4C6 &);
template <> void _Construct<BfmeStringRecord003B3F78, BfmeStringRecord003B3F78>(BfmeStringRecord003B3F78 *, const BfmeStringRecord003B3F78 &);
template <> void _Construct<Rva000BB491, Rva000BB491>(Rva000BB491 *, const Rva000BB491 &);
template <> void _Construct<Rva000BB4AC, Rva000BB4AC>(Rva000BB4AC *, const Rva000BB4AC &);
template <> void _Construct<Rva003F610FElement, Rva003F610FElement>(Rva003F610FElement *, const Rva003F610FElement &);
template <> void _Construct<Rva004F6352, Rva004F6352>(Rva004F6352 *, const Rva004F6352 &);
template <> void _Construct<Rva00520211Element, Rva00520211Element>(Rva00520211Element *, const Rva00520211Element &);
template <> void _Construct<Rva00585B16, Rva00585B16>(Rva00585B16 *, const Rva00585B16 &);
template <> void _Construct<Rva00151DAB, Rva00151DAB>(Rva00151DAB *, const Rva00151DAB &);
template <> void _Construct<Rva00153729, Rva00153729>(Rva00153729 *, const Rva00153729 &);
template <> void _Construct<BfmeStringTailRecord156, BfmeStringTailRecord156>(BfmeStringTailRecord156 *, const BfmeStringTailRecord156 &);
}

// Retail 0x0015239D.
template void _STL::vector<Rva0007BB16Record>::reserve(unsigned int);
// Retail 0x00173FE9.
template void _STL::vector<BfmeAssignRecord32>::_M_insert_overflow(
    BfmeAssignRecord32 *, const BfmeAssignRecord32 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x001ECD5F.
template BfmeRecord001ECAF9 *_STL::__uninitialized_fill_n<BfmeRecord001ECAF9 *, unsigned int, BfmeRecord001ECAF9>(
    BfmeRecord001ECAF9 *, unsigned int, const BfmeRecord001ECAF9 &, const _STL::__false_type &);
// Retail 0x001ECD84.
template BfmeRecord001ECAF9 *_STL::__uninitialized_copy<BfmeRecord001ECAF9 *, BfmeRecord001ECAF9 *>(
    BfmeRecord001ECAF9 *, BfmeRecord001ECAF9 *, BfmeRecord001ECAF9 *, const _STL::__false_type &);
// Retail 0x001ED13A.
template void _STL::vector<BfmeRecord001ECAF9>::_M_insert_overflow(
    BfmeRecord001ECAF9 *, const BfmeRecord001ECAF9 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x002AF67A.
template BfmeVectorRecord002AF478 *_STL::__uninitialized_copy<BfmeVectorRecord002AF478 *, BfmeVectorRecord002AF478 *>(
    BfmeVectorRecord002AF478 *, BfmeVectorRecord002AF478 *, BfmeVectorRecord002AF478 *, const _STL::__false_type &);
// Retail 0x002AF6A0.
template BfmeVectorRecord002AF478 *_STL::__uninitialized_fill_n<BfmeVectorRecord002AF478 *, unsigned int, BfmeVectorRecord002AF478>(
    BfmeVectorRecord002AF478 *, unsigned int, const BfmeVectorRecord002AF478 &, const _STL::__false_type &);
// Retail 0x002B1418.
template void _STL::vector<BfmeVectorRecord002AF478>::_M_insert_overflow(
    BfmeVectorRecord002AF478 *, const BfmeVectorRecord002AF478 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x002B0F1E.
template void _STL::vector<BfmeVectorRecord002AF478>::_M_clear();
// Retail 0x002B0EDF.
template _STL::vector<BfmeVectorRecord002AF478>::~vector();
// Retail 0x00337B57.
template void _STL::vector<Rva003371B1>::_M_insert_overflow(
    Rva003371B1 *, const Rva003371B1 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x00339EB3.
template void _STL::vector<Rva002390CB>::_M_insert_overflow(
    Rva002390CB *, const Rva002390CB &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x00403666.
template BfmeStringRecord0040360E *_STL::__uninitialized_copy<BfmeStringRecord0040360E *, BfmeStringRecord0040360E *>(
    BfmeStringRecord0040360E *, BfmeStringRecord0040360E *, BfmeStringRecord0040360E *, const _STL::__false_type &);
// Retail 0x0040368C.
template BfmeStringRecord0040360E *_STL::__uninitialized_fill_n<BfmeStringRecord0040360E *, unsigned int, BfmeStringRecord0040360E>(
    BfmeStringRecord0040360E *, unsigned int, const BfmeStringRecord0040360E &, const _STL::__false_type &);
// Retail 0x00404C8D.
template BfmeStringRecord00404BF3 *_STL::__uninitialized_copy<BfmeStringRecord00404BF3 *, BfmeStringRecord00404BF3 *>(
    BfmeStringRecord00404BF3 *, BfmeStringRecord00404BF3 *, BfmeStringRecord00404BF3 *, const _STL::__false_type &);
// Retail 0x00404CB3.
template BfmeStringRecord00404BF3 *_STL::__uninitialized_fill_n<BfmeStringRecord00404BF3 *, unsigned int, BfmeStringRecord00404BF3>(
    BfmeStringRecord00404BF3 *, unsigned int, const BfmeStringRecord00404BF3 &, const _STL::__false_type &);
// Retail 0x0040542A.
template void _STL::vector<BfmeStringRecord00404BF3>::_M_insert_overflow(
    BfmeStringRecord00404BF3 *, const BfmeStringRecord00404BF3 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x004055BB.
template void _STL::vector<BfmeStringRecord00404BF3>::push_back(const BfmeStringRecord00404BF3 &);
// Retail 0x005EDABD.
template void _STL::vector<BfmeStringRecord005ED5F3>::_M_insert_overflow(
    BfmeStringRecord005ED5F3 *, const BfmeStringRecord005ED5F3 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x000C34ED.
template void _STL::vector<Rva000BB491>::_M_insert_overflow(
    Rva000BB491 *, const Rva000BB491 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x000C35A4.
template void _STL::vector<Rva000BB4AC>::_M_insert_overflow(
    Rva000BB4AC *, const Rva000BB4AC &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x000C866D.
template void _STL::vector<BfmePod252>::_M_insert_overflow(
    BfmePod252 *, const BfmePod252 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x000C8D04.
template void _STL::vector<BfmePod248>::_M_insert_overflow(
    BfmePod248 *, const BfmePod248 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x00209952.
template void _STL::vector<BfmeStringRecord00204A30>::_M_insert_overflow(
    BfmeStringRecord00204A30 *, const BfmeStringRecord00204A30 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x0021F95B.
template void _STL::vector<BfmePod216>::_M_insert_overflow(
    BfmePod216 *, const BfmePod216 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x0032C3ED.
template void _STL::vector<BfmePod128>::_M_insert_overflow(
    BfmePod128 *, const BfmePod128 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x0033D08B.
template void _STL::vector<BfmeStringRecord002CF4C6>::_M_insert_overflow(
    BfmeStringRecord002CF4C6 *, const BfmeStringRecord002CF4C6 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x003B725C.
template void _STL::vector<BfmeStringRecord003B3F78>::_M_insert_overflow(
    BfmeStringRecord003B3F78 *, const BfmeStringRecord003B3F78 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x003F5F15.
template void _STL::vector<Rva003F610FElement>::reserve(unsigned int);
// Retail 0x003F5FD0.
template _STL::vector<Rva003F610FElement> &_STL::vector<Rva003F610FElement>::operator=(const _STL::vector<Rva003F610FElement> &);
// Retail 0x0042843E.
template void _STL::vector<BfmeNarrowRecord00427F75>::_M_insert_overflow(
    BfmeNarrowRecord00427F75 *, const BfmeNarrowRecord00427F75 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x004282EF.
template void _STL::vector<BfmeNarrowRecord00427F75>::_M_clear();
// Retail 0x004F8F61.
template void _STL::vector<Rva004F6352>::_M_insert_overflow(
    Rva004F6352 *, const Rva004F6352 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x0052019D.
template void _STL::vector<Rva00520211Element>::reserve(unsigned int);
// Retail 0x00586C56.
template void _STL::vector<Rva00585B16>::_M_insert_overflow(
    Rva00585B16 *, const Rva00585B16 &, const _STL::__false_type &, unsigned int, bool);

// The next four growth paths call _Construct rows that are not landed: each
// _Construct address is read from the REL32 sites of these byte-identical
// bodies and pinned; its retail body is the element's null-guarded
// placement copy (EH frame for Rva0007BB16Record and Rva00153729, throw()
// tail call for Rva00151DAB and BfmeStringTailRecord156). Each overflow also
// emits the element's __uninitialized_copy and __uninitialized_fill_n.
// Retail 0x0007D8FE.
template void _STL::vector<Rva0007BB16Record>::_M_insert_overflow(
    Rva0007BB16Record *, const Rva0007BB16Record &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x001521B3.
template void _STL::vector<Rva00151DAB>::_M_insert_overflow(
    Rva00151DAB *, const Rva00151DAB &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x00153C5F.
template void _STL::vector<Rva00153729>::_M_insert_overflow(
    Rva00153729 *, const Rva00153729 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x001D9FAC.
template void _STL::vector<BfmeStringTailRecord156>::_M_insert_overflow(
    BfmeStringTailRecord156 *, const BfmeStringTailRecord156 &, const _STL::__false_type &, unsigned int, bool);
// push_back over the growth paths above: retail 0x0007D9EC, 0x00152265 and 0x001DA655.
template void _STL::vector<Rva0007BB16Record>::push_back(const Rva0007BB16Record &);
template void _STL::vector<Rva00151DAB>::push_back(const Rva00151DAB &);
template void _STL::vector<BfmeStringTailRecord156>::push_back(const BfmeStringTailRecord156 &);
// Retail 0x00428678.
template void _STL::vector<BfmeNarrowRecord00427F75>::push_back(const BfmeNarrowRecord00427F75 &);
// Retail 0x0010E604: copy ctor; its get_allocator, _Vector_base(n) and const
// __uninitialized_copy callees are ICF aliases pinned at the rowed bodies.
template _STL::vector<Rva0007BB16Record>::vector(const _STL::vector<Rva0007BB16Record> &);
