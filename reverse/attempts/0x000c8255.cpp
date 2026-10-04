// ?push_back@?$vector@UBfmeVectorRecord000C0BEC@@V?$allocator@UBfmeVectorRecord000C0BEC@@@_STL@@@_STL@@QAEXABUBfmeVectorRecord000C0BEC@@@Z
// partial score=0.98 date=2026-10-04
// cl: /G7 /O1 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc/stl
// stlport
// BANK STATUS: native bodies C8492/202, C8255/55 and C781E/183 all have
// exact instruction shapes under these flags. Only provisional scratch binding
// checks were performed; normal strict byte/import/link gates remain to run.
// Current blocker: /G7 emits max<uint>17 with MOV edx,[eax] before loading
// argument b into ECX, unlike rowed native13740. Existing max declaration or
// extern template introduces an external call and changes overflow183->189;
// /G6 fixes max but changes owner/growth register allocation and LEA tails.
// Do not pin max incorrectly or suppress this known wrong COMDAT to land.
// Required additional rowed helper bindings, each proven by target callsites:
// ??1BfmeVectorRecord000C0BEC@@QAE@XZ ->BEDF0/53, canonical existing
// ??1Rva000BEDF0Record@@QAE@XZ. Native memberwise cleanup independently proves
// AsciiString0/vector<AsciiString>4; owner news20 and rowed copyC0BEC confirm
// the same record extent. Add linker alternatename plus consistency-checked pin.
// ?_M_clear@?$vector@UBfmeVectorRecord000C0BEC@@V?$allocator@UBfmeVectorRecord000C0BEC@@@_STL@@@_STL@@IAEXXZ
// ->C695D/30, existing corresponding Rva000BEDF0Record vector method.
// Native growth callC78B7 goes there; rowed native clear destroys20-byte records
// via C37E6/dtorBEDF0 then frees backing storage. Add alias + checked typedpin.
// ?allocate@?$allocator@UBfmeVectorRecord000C0BEC@@@_STL@@QBEPAUBfmeVectorRecord000C0BEC@@IPBX@Z
// ->395960/28, already-rowed allocator<BfmeStringRecord002CF4C6>.
// This TU's allocator is fully exact including char-allocator call307F0;
// count*20/native growthC784D establishes its allocation ABI, not an
// application-record identity. Checked typed pin needed for strict relocation.
// The three new rows should bind in dependency order growth183, push55,
// owner202; no unresolved native endpoint should be given an invented pin.
// BFME1 donor 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24 whole
// game/GameEngine/Source/Common/Containers/Rva007701C0Vector.cpp compiled first.
// Target C8492/202 scans20-byte records through owner+7C (donor+78), calls
// CRT _strcmpi through IAT BBA518, ctorBDD48, set366F0, pushC8255,
// dtorBEDF0 and delete2FD60. Original application owner identity unknown.
// CopyC0BEC proves text0/names4/word10; scalar meaning/signedness unknown.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#undef _CRTIMP
#define _CRTIMP
#define _STLP_NO_EXCEPTIONS 1
#include <cstddef>
#include "_alloc.h"
#include <vector>
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int& max<unsigned int>(const unsigned int& a,const unsigned int& b) {return a<b?b:a;}
}
#pragma optimize("", on)
#include "ascii_string.h"
struct BfmeVectorRecord000C0BEC {
    AsciiString text;
    _STL::vector<AsciiString> names;
    unsigned int word10;
    BfmeVectorRecord000C0BEC();
    BfmeVectorRecord000C0BEC(const BfmeVectorRecord000C0BEC &);
    ~BfmeVectorRecord000C0BEC();
    BfmeVectorRecord000C0BEC &operator=(const BfmeVectorRecord000C0BEC &);
};
typedef char RecordExtent000C8492[sizeof(BfmeVectorRecord000C0BEC)==20?1:-1];
namespace _STL {
template <> void _Construct<BfmeVectorRecord000C0BEC,BfmeVectorRecord000C0BEC>(BfmeVectorRecord000C0BEC *, const BfmeVectorRecord000C0BEC &);
template <> void vector<BfmeVectorRecord000C0BEC>::_M_clear();
}
class Rva000C8492RecordOwner
{
public:
	BfmeVectorRecord000C0BEC *findOrCreateRecord(const AsciiString &name);

private:
	unsigned char m_prefix[0x7C];
	_STL::vector<BfmeVectorRecord000C0BEC> m_info;
};

// ?findOrCreateRecord@Rva000C8492RecordOwner@@QAEPAUBfmeVectorRecord000C0BEC@@ABVAsciiString@@@Z
BfmeVectorRecord000C0BEC *Rva000C8492RecordOwner::findOrCreateRecord(const AsciiString &name)
{
	BfmeVectorRecord000C0BEC *it = m_info.begin();
	int (__cdecl *compare)(const char *, const char *) = _strcmpi;
	for (; it != m_info.end(); ++it)
	{
		if (compare(it->text.str(), name.str()) == 0)
			return it;
	}

	create_record:
	BfmeVectorRecord000C0BEC *record = new BfmeVectorRecord000C0BEC;
	record->text = name;
	m_info.push_back(*record);
	delete record;

	return &m_info[m_info.size() - 1];
}


template void _STL::vector<BfmeVectorRecord000C0BEC>::push_back(const BfmeVectorRecord000C0BEC &);
template void _STL::vector<BfmeVectorRecord000C0BEC>::_M_insert_overflow(BfmeVectorRecord000C0BEC *,const BfmeVectorRecord000C0BEC &,const _STL::__false_type &,unsigned int,bool);
