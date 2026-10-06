// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// moneypunct's nine virtuals, slots 1..9 of the four vftables at 0x007BC810,
// 0x007BC83C, 0x007BC868 and 0x007BC894. Almost none of it is distinct code:
// the four vftables between them name thirty-six slots and hold six bodies,
// because the default facet has no locale data to report. decimal_point and
// thousands_sep both return a space, grouping and the three string getters
// all return an empty string, frac_digits returns zero, and only the two
// format getters differ - and only from each other, reading _M_pos_format at
// this+0xC and _M_neg_format at this+0x10.
//
// Those two offsets come from the constructor at 0x00019750, which writes the
// bytes 2,3,0,4 to each: symbol, sign, none, value.
//
// The four string getters are not here. They share one body at 0x00019D30
// which zeroes a basic_string in place and then range-initialises it from a
// static - basic_string's copy constructor, inlined. cl 13.10 declines to
// inline it and emits a call, and that same wall stops numpunct's truename
// and falsename. Ten of these thirty-six slots wait behind it.

#include <locale>

namespace _STL
{

char moneypunct<char, true>::do_decimal_point() const
{
	return ' ';
}

char moneypunct<char, true>::do_thousands_sep() const
{
	return ' ';
}





int moneypunct<char, true>::do_frac_digits() const
{
	return 0;
}

money_base::pattern moneypunct<char, true>::do_pos_format() const
{
	return _M_pos_format;
}

money_base::pattern moneypunct<char, true>::do_neg_format() const
{
	return _M_neg_format;
}

wchar_t moneypunct<wchar_t, true>::do_decimal_point() const
{
	return L' ';
}

wchar_t moneypunct<wchar_t, true>::do_thousands_sep() const
{
	return L' ';
}

// The other three specialisations' copies of the same defaults. Retail keeps
// one body per shape (0x00019730/0x000197F0 the space, 0x0065CE90 the zero,
// 0x0066D820 and 0x00019740 the two format getters), so each is the ICF twin
// of the body above that shares it.
char moneypunct<char, false>::do_decimal_point() const { return ' '; }
char moneypunct<char, false>::do_thousands_sep() const { return ' '; }
int moneypunct<char, false>::do_frac_digits() const { return 0; }
money_base::pattern moneypunct<char, false>::do_pos_format() const { return _M_pos_format; }
money_base::pattern moneypunct<char, false>::do_neg_format() const { return _M_neg_format; }

int moneypunct<wchar_t, true>::do_frac_digits() const { return 0; }
money_base::pattern moneypunct<wchar_t, true>::do_pos_format() const { return _M_pos_format; }
money_base::pattern moneypunct<wchar_t, true>::do_neg_format() const { return _M_neg_format; }

wchar_t moneypunct<wchar_t, false>::do_decimal_point() const { return L' '; }
wchar_t moneypunct<wchar_t, false>::do_thousands_sep() const { return L' '; }
int moneypunct<wchar_t, false>::do_frac_digits() const { return 0; }
money_base::pattern moneypunct<wchar_t, false>::do_pos_format() const { return _M_pos_format; }
money_base::pattern moneypunct<wchar_t, false>::do_neg_format() const { return _M_neg_format; }

}
