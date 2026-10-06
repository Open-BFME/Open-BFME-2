// cl: /MD
// stlport
// STLport 4.5.3 ios_base::_M_copy_state and _Stl_copy_array (src/ios.cpp).
// Ported from Open-BFME-1 5cae4bdff game/Libraries/Source/STLport/IosBaseCopyState.cpp
// (BFME1 0x0083F3F0, 432 B); bfme1_sweep places the same masked body at BFME2
// 0x0001C300, where symbols.csv already pins this name. The donor's stand-in
// class for the ios_base locale member is written here as _STL::locale: BFME2's
// ledger already holds its inequality test (??9locale, 0x0000BC40) and assignment
// (??4locale, 0x00007160), the two call targets this body reads, so no new pin
// or address-named type is needed. The two members copied with the locale are
// STLport's cached ctype and numpunct facet pointers.

#include <algorithm>
#include <cstdlib>

namespace _STL
{
class locale
{
	void *_M_impl;

public:
	bool operator!=(const locale &L) const;
	locale &operator=(const locale &L);
};
}

struct U2Elem8
{
	int m_a;
	int m_b;
};

extern void *Rva0083F3B0Duplicate(const U2Elem8 *src, int count);

extern void *g_global;						// BFME1 0x013592F0
extern void (__cdecl *g_call)(void *, void *);		// BFME1 0x013593C8

namespace _STL
{

// malloc N elements and copy the source array into them; null on failure.
template <class PODType>
PODType *_Stl_copy_array(const PODType *array, size_t N)
{
	PODType *result = (PODType *)malloc(N * sizeof(PODType));
	if (result)
		copy(array, array + N, result);
	return result;
}

class ios_base
{
public:
	virtual void handle();

protected:
	void _M_copy_state(const ios_base &x);
	void _M_setstate_nothrow(int state) { _M_iostate |= state; }
	void _M_check_exception_mask()
	{
		if (_M_iostate & _M_exception_mask)
			g_call((void *)"ios failure", (char *)g_global + 0x40);
	}

public:
	int _M_fmtflags;					// +0x04
	int _M_iostate;						// +0x08
	int _M_openmode;					// +0x0C
	int _M_seekdir;						// +0x10
	int _M_exception_mask;					// +0x14
	int _M_precision;					// +0x18
	int _M_width;						// +0x1C
	locale _M_locale;					// +0x20
	U2Elem8 *_M_callbacks;					// +0x24
	unsigned int _M_num_callbacks;				// +0x28
	unsigned int _M_callback_index;			// +0x2C
	int *_M_iarray;						// +0x30
	unsigned int _M_iarray_size;				// +0x34
	void **_M_parray;					// +0x38
	unsigned int _M_parray_size;				// +0x3C
	const void *_M_cached_ctype;				// +0x40
	const void *_M_cached_numpunct;			// +0x44
	char m_pad2[0x54 - 0x48];
};

void ios_base::_M_copy_state(const ios_base &x)
{
	_M_fmtflags = x._M_fmtflags;
	_M_openmode = x._M_openmode;
	_M_seekdir = x._M_seekdir;
	_M_precision = x._M_precision;
	_M_width = x._M_width;

	if (_M_locale != x._M_locale)
	{
		_M_locale = x._M_locale;
		_M_cached_ctype = x._M_cached_ctype;
		_M_cached_numpunct = x._M_cached_numpunct;
	}

	if (x._M_callbacks)
	{
		U2Elem8 *tmp = (U2Elem8 *)Rva0083F3B0Duplicate(x._M_callbacks, x._M_callback_index);
		if (tmp)
		{
			free(_M_callbacks);
			_M_callbacks = tmp;
			_M_num_callbacks = _M_callback_index = x._M_callback_index;
		}
		else
		{
			_M_setstate_nothrow(1);
			_M_check_exception_mask();
		}
	}

	if (x._M_iarray)
	{
		int *tmp = _Stl_copy_array(x._M_iarray, x._M_iarray_size);
		if (tmp)
		{
			free(_M_iarray);
			_M_iarray = tmp;
			_M_iarray_size = x._M_iarray_size;
		}
		else
		{
			_M_setstate_nothrow(1);
			_M_check_exception_mask();
		}
	}

	if (x._M_parray)
	{
		void **tmp = _Stl_copy_array(x._M_parray, x._M_parray_size);
		if (tmp)
		{
			free(_M_parray);
			_M_parray = tmp;
			_M_parray_size = x._M_parray_size;
		}
		else
		{
			_M_setstate_nothrow(1);
			_M_check_exception_mask();
		}
	}
}

}
