// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport46

// Open-BFME5: _STL::basic_streambuf<char>::_M_snextc_aux @ 0x008402D0 (94B)
// FILE*-specialized streambuf (STLport 4.5.3): _M_get at +4.

#include "../../../../GameEngine/Source/Common/StdioStreambufBaseView.h"

namespace _STL
{

int basic_streambuf<char, char_traits<char> >::_M_snextc_aux()
{
	const int_type eofv = -1;
	if (_FILE_I_avail(_M_get) == 0)
	{
		int_type c = uflow();
		if (c == eofv)
			return c;
		return sgetc();
	}
	else
	{
		setg(eback(), egptr(), egptr());
		return underflow();
	}
}

} // namespace _STL
