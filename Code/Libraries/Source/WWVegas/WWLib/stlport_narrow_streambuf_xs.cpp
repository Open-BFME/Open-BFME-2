// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport46

// Open-BFME5: _STL::basic_streambuf<char> xsgetn @ 0x00840050 (166B)
// and xsputn @ 0x00840150 (172B). FILE*-specialized streambuf.

#include "../../../../GameEngine/Source/Common/StdioStreambufBaseView.h"
#include <cstring>

namespace _STL
{

template <class T>
static inline const T &(min)(const T &a, const T &b)
{
	return a < b ? a : b;
}

int basic_streambuf<char, char_traits<char> >::xsgetn(char_type *s, int n)
{
	int result = 0;
	const int eofv = -1;

	while (result < n)
	{
		BfmeFileBuf *get = _M_get;
		int cnt = get->_cnt;
		if (cnt > 0)
		{
			size_t chunk = (min)((size_t)(n - result), (size_t)cnt);
			if (chunk != 0)
				memcpy(s, get->_ptr, chunk);
			result += (int)chunk;
			s += chunk;
			get = _M_get;
			get->_ptr += chunk;
			get->_cnt -= (int)chunk;
		}
		else
		{
			int_type c = uflow();
			if (c == eofv)
				break;
			*s = (char_type)c;
			++result;
			++s;
		}
	}
	return result;
}

} // namespace _STL
