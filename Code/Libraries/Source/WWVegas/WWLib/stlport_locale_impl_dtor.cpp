// cl: /O2 /Ob0 /DNDEBUG /MD

// Open-BFME5: _STL::_Locale_impl::~_Locale_impl(), retail 0x00408D60,
// 21 bytes. Retail RTTI at 0x00CF3FB4 names _Locale_impl, and its vtable at
// 0x00BBBBB0 points to the scalar-deleting destructor at 0x0040B710. That
// thunk calls this body before optionally deleting the object.
//
// The destructor restores the _Locale_impl vtable, then releases the optional
// allocation at offset 0x0C through the game's C free wrapper at 0x00430830.

extern "C" void __cdecl free(void *);

namespace _STL
{

class _Locale_impl
{
public:
	virtual ~_Locale_impl();

private:
	void *_M_facets;
	unsigned int _M_size;
	void *_M_names;
};

_Locale_impl::~_Locale_impl()
{
	if (_M_names != 0)
		free(_M_names);
}

}
