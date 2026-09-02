// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 locale::operator!=, 18 bytes: it forwards to the equality at
// 0x0000BB10 and inverts the answer with the compiler's usual neg/sbb/inc.

namespace _STL
{

class _Locale_impl;

class locale
{
public:
	bool operator==(const locale &that) const;
	bool operator!=(const locale &that) const;

private:
	_Locale_impl *_M_impl;
};

bool locale::operator!=(const locale &that) const
{
	return !(*this == that);
}

}
