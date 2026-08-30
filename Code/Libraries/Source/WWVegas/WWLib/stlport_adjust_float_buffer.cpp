// cl: /GX- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 __adjust_float_buffer. The printf-produced buffer always
// carries a '.', so the locale's decimal point is patched in afterwards. Retail
// walks the whole range rather than stopping at the first hit.

namespace _STL
{

void __cdecl __adjust_float_buffer(char *first, char *last, char decimalPoint)
{
	if (decimalPoint != '.')
	{
		for (char *position = first; position != last; ++position)
		{
			if (*position == '.')
				*position = decimalPoint;
		}
	}
}

}
