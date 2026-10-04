// cl: /O1 /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
//
// ??_E?$StringBase@G@@AAEPAXI@Z,
// retail 0x002331F0 (75 bytes). Vector deleting destructor for wide StringBase.
// Element size 4 (single pointer), cookie at [esi-4], calls rowed ??_M helper
// with ??1 (which shares 0x005B804E with clear), then ??_V/??3.
// Evidence: Ghidra vector_deleting_destructor; push 4 + push clear VA;
// scalar path calls clear/??1; callers 0x002332E7/0x00233319/0x00233677;
// same 75B shape as ??_ERva002E5791 precedent.
void operator delete[](void *p);

typedef unsigned short wchar_t;

template <typename T>
class StringBase
{
public:
	void clear();
	friend void StringBaseWideDeleteArray(StringBase<wchar_t> *array);

private:
	~StringBase();
	T *m_data;
};

// ?StringBaseWideDeleteArray@@YAXPAV?$StringBase@G@@@Z present-unmatched
void StringBaseWideDeleteArray(StringBase<wchar_t> *array)
{
	delete[] array;
}
