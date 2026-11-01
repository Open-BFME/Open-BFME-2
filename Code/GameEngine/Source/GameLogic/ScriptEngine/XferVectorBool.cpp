// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// ?Rva0060C253Xfer@@YAPAVXfer@@PAV1@PAV?$vector@_NV?$allocator@_N@_STL@@@_STL@@@Z @0x0060C253 283B free vector<bool> Xfer helper version {1,1} via slot 0x28 size via slot 0x2C/0x78 isSaving via slot 0x08 saving walks bits via slot 0x90 loading checks empty via FormatText 0x0060C36E plus Throw 0x00629094 then reserve 0x0060C1C0 plus rowed push_back.
// Evidence: chain lane every callee rowed or pinned; skeleton mirrors landed XferListInt 0x00206861; caller 0x004EF0C3.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// Keep STLport's deallocation inlined without emitting a competing helper.
// The external helper has no retail address and differs across allocator TUs.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _Bvector_base<allocator<bool> >::_M_deallocate()
{
    if (_M_start._M_p)
        _M_end_of_storage.deallocate(_M_start._M_p,
            _M_end_of_storage._M_data - _M_start._M_p);
}
}

// bfme link decl-only begin
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> copy<_Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *> >(_Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *>); }
namespace _STL { template <> unsigned int * _Bvector_base<allocator<bool> >::_M_bit_alloc(unsigned int); }
namespace _STL { template <> void vector<bool, allocator<bool> >::reserve(unsigned int); }
// Use the rowed insertion provider rather than emitting its unused helpers.
namespace _STL { template <> void vector<bool, allocator<bool> >::_M_insert_aux(_Bit_iterator, bool); }
// bfme link decl-only end
// Preserve this unit's rowed iterator body after suppressing unused insert helpers.
template _STL::_Bit_iterator _STL::_Bit_iter<_STL::_Bit_reference, _STL::_Bit_reference *>::operator++(int);

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

#include "../../Common/System/XferVectorTypes.h"
#include "../../../Include/Common/BfmeXfer.h"

#include "../../../Include/Common/XferException.h"


typedef _STL::vector<bool> VectorBool;

struct XferHead
{
	XferVersion version;
	UnsignedInt count;
};

Xfer *Rva0060C253Xfer(Xfer *xfer, VectorBool *vec)
{
	XferHead head;
	head.version.m_version = 1;
	head.version.m_currentVersion = 1;
	xfer->operator==(reinterpret_cast<Xfer::Version &>(head.version));

	head.count = vec->size();
	xfer->operator==("std::vector").operator==(head.count);

	if (xfer->IsStoring())
	{
		VectorBool::iterator last = vec->end();
		VectorBool::iterator first = vec->begin();
		for (; first != last; ++first)
		{
			Bool b = *first;
			xfer->operator==(b);
		}
	}
	else
	{
		if (!vec->empty())
		{
			throw XferException(4, "Vector must be empty on load");
		}

		vec->reserve(head.count);
		Bool value;
		while (head.count != 0)
		{
			--head.count;
			xfer->operator==(value);
			vec->push_back(value);
		}
	}
	return xfer;
}
