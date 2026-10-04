// cl: /G7 /O1 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc/stl
// stlport
// Whole clean BFME1 donor1281192f682ce6f29b8f06b7daea4b5e8fdfbb24:
// game/GameEngine/Source/Common/Containers/Rva007701C0Vector.cpp.
// Native C8492/202 allocates20-byte records and scans its vector at+7C;
// donor owner vector offset was+78. Rowed copyC0BEC and dtorBEDF0 prove
// text+0, vector<AsciiString>+4 and scalar+10; original application owner,
// field meanings and scalar signedness remain unknown.
// Native growthC781E and pushC8255 independently establish the STL operations.
// A TU-local member specialization below uses the same STLport4.5.3 algorithm,
// spelling its maximum reference selection as a pointer choice. This preserves
// every native body byte while avoiding an unused non-retail max COMDAT.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#undef _CRTIMP
#define _CRTIMP
#define _STLP_NO_EXCEPTIONS 1
#include <cstddef>
#include "_alloc.h"
#include <vector>

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
/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

// Source: pristine STLport4.5.3 stl/_vector.h overflow algorithm.
// Only its inlined maximum reference selection is expressed directly here.
namespace _STL {
template<> void vector<BfmeVectorRecord000C0BEC>::_M_insert_overflow(
    BfmeVectorRecord000C0BEC *__position, const BfmeVectorRecord000C0BEC &__x,
    const __false_type &, unsigned int __fill_len, bool __atend)
{
    const size_type __old_size = size();
    const size_type *__larger = __old_size < __fill_len ? &__fill_len : &__old_size;
    const size_type __len = __old_size + *__larger;
    
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    _STLP_TRY {
      __new_finish = __uninitialized_copy(this->_M_start, __position, __new_start, __false_type());
      // handle insertion
      if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
      } else
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
      if (!__atend)
        // copy remainder
        __new_finish = __uninitialized_copy(__position, this->_M_finish, __new_finish, __false_type());
    }
    _STLP_UNWIND((_Destroy(__new_start,__new_finish), 
                  this->_M_end_of_storage.deallocate(__new_start,__len)));
    _M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
  }

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
// ?findOrCreateRecord@Rva000C8492RecordOwner@@QAEPAUBfmeVectorRecord000C0BEC@@ABVAsciiString@@@Z present-unmatched
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


// ?push_back@?$vector@UBfmeVectorRecord000C0BEC@@V?$allocator@UBfmeVectorRecord000C0BEC@@@_STL@@@_STL@@QAEXABUBfmeVectorRecord000C0BEC@@@Z present-unmatched
template void _STL::vector<BfmeVectorRecord000C0BEC>::push_back(const BfmeVectorRecord000C0BEC &);

// Native ownerC852B and growthC78B7 name the rowed teardown providers.
// These bindings share the observed nonvirtual record/vector ABI; original
// application types are not inferred from the alternate C++ symbol spellings.
#pragma comment(linker, "/alternatename:??1BfmeVectorRecord000C0BEC@@QAE@XZ=??1Rva000BEDF0Record@@QAE@XZ")
#pragma comment(linker, "/alternatename:?_M_clear@?$vector@UBfmeVectorRecord000C0BEC@@V?$allocator@UBfmeVectorRecord000C0BEC@@@_STL@@@_STL@@IAEXXZ=?_M_clear@?$vector@URva000BEDF0Record@@V?$allocator@URva000BEDF0Record@@@_STL@@@_STL@@IAEXXZ")
