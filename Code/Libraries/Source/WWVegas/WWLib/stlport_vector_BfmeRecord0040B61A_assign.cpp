// cl: /EHsc /Ireference/shims/bfme2_ascii
// stlport
// ??4?$vector@UBfmeRecord0040B61A@@...@QAEAAV01@ABV01@@Z, retail 0x0040B61A, 186 bytes.
// Evidence: same bytes as vector<GeometryRecord>::operator= except two calls:
// the destroy reads the rowed Rva0040B52EDestroy at 0x0040B52E, which frees a
// narrow string at +0 of a 16-byte element, and the uninitialized copy reads
// 0x0040B2FD. Its other calls read the neighbouring 0x0040B323, 0x0040B350
// and the rowed destroy-and-free 0x0040B5DE. The element name is generated;
// the string at +0 and the 16-byte stride come from those bodies. The
// AsciiString member and the int fields are placeholders: the string's exact
// type and the remaining fields are not established. The flags follow
// GeometryRecordVector.cpp; /MD with the STLport static-lib defines adds a
// distance argument retail does not pass.
#include <vector>

#include "ascii_string.h"

struct BfmeRecord0040B61A
{
	AsciiString m_str;
	int m_04;
	int m_08;
	int m_0C;
};

template _STL::vector<BfmeRecord0040B61A, _STL::allocator<BfmeRecord0040B61A> > &
	_STL::vector<BfmeRecord0040B61A, _STL::allocator<BfmeRecord0040B61A> >::operator=(
		const _STL::vector<BfmeRecord0040B61A, _STL::allocator<BfmeRecord0040B61A> > &);
