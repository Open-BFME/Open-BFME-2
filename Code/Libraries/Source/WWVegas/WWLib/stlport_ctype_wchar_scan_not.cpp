// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 src/ctype.cpp: ctype<wchar_t>::do_scan_is/do_scan_not.

#include <algorithm>
#include <functional>
#include <stl/_ctype.h>

_STLP_BEGIN_NAMESPACE

#ifndef _STLP_NO_WCHAR_T

struct _Ctype_w_is_mask : public unary_function<wchar_t, bool>
{
	ctype_base::mask M;
	const ctype_base::mask *table;

	_Ctype_w_is_mask(ctype_base::mask m, const ctype_base::mask *t)
		: M(m), table(t) {}

	bool operator()(wchar_t c) const
	{
		return c >= 0 && size_t(c) < ctype<char>::table_size && (table[c] & M);
	}
};

const wchar_t *ctype<wchar_t>::do_scan_is(ctype_base::mask m,
	const wchar_t *low, const wchar_t *high) const
{
	return find_if(low, high,
		_Ctype_w_is_mask(m, ctype<char>::classic_table()));
}

const wchar_t *ctype<wchar_t>::do_scan_not(ctype_base::mask m,
	const wchar_t *low, const wchar_t *high) const
{
	return find_if(low, high,
		not1(_Ctype_w_is_mask(m, ctype<char>::classic_table())));
}

#endif

_STLP_END_NAMESPACE

// STLport's named table members, using its declared 257-mask/256-byte spans.
// Four matched BFME2 references place the mask base at VA 0x00BBBDD8;
// classic_table() skips its leading zero. Two references each place the case
// maps at VA 0x00BBC1E0 and 0x00BBC2E0. All 1540 initialized bytes match retail.
_STLP_BEGIN_NAMESPACE
const unsigned char ctype<char>::_S_upper[256] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
    64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
    96, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 123, 124, 125, 126, 127,
    128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
    144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
    160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
    176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
    192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
    208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
    224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
    240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255
};

const unsigned char ctype<char>::_S_lower[256] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
    64, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 91, 92, 93, 94, 95,
    96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
    128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
    144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
    160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
    176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
    192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
    208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
    224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
    240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255
};

const ctype<char>::mask ctype<char>::_S_classic_table[257] = {
    (ctype_base::mask)0x000, (ctype_base::mask)0x020, (ctype_base::mask)0x020, (ctype_base::mask)0x020,
    (ctype_base::mask)0x020, (ctype_base::mask)0x020, (ctype_base::mask)0x020, (ctype_base::mask)0x020,
    (ctype_base::mask)0x020, (ctype_base::mask)0x020, (ctype_base::mask)0x028, (ctype_base::mask)0x028,
    (ctype_base::mask)0x028, (ctype_base::mask)0x028, (ctype_base::mask)0x028, (ctype_base::mask)0x020,
    (ctype_base::mask)0x020, (ctype_base::mask)0x020, (ctype_base::mask)0x020, (ctype_base::mask)0x020,
    (ctype_base::mask)0x020, (ctype_base::mask)0x020, (ctype_base::mask)0x020, (ctype_base::mask)0x020,
    (ctype_base::mask)0x020, (ctype_base::mask)0x020, (ctype_base::mask)0x020, (ctype_base::mask)0x020,
    (ctype_base::mask)0x020, (ctype_base::mask)0x020, (ctype_base::mask)0x020, (ctype_base::mask)0x020,
    (ctype_base::mask)0x020, (ctype_base::mask)0x048, (ctype_base::mask)0x050, (ctype_base::mask)0x050,
    (ctype_base::mask)0x050, (ctype_base::mask)0x050, (ctype_base::mask)0x050, (ctype_base::mask)0x050,
    (ctype_base::mask)0x050, (ctype_base::mask)0x050, (ctype_base::mask)0x050, (ctype_base::mask)0x050,
    (ctype_base::mask)0x050, (ctype_base::mask)0x050, (ctype_base::mask)0x050, (ctype_base::mask)0x050,
    (ctype_base::mask)0x050, (ctype_base::mask)0x0C4, (ctype_base::mask)0x0C4, (ctype_base::mask)0x0C4,
    (ctype_base::mask)0x0C4, (ctype_base::mask)0x0C4, (ctype_base::mask)0x0C4, (ctype_base::mask)0x0C4,
    (ctype_base::mask)0x0C4, (ctype_base::mask)0x0C4, (ctype_base::mask)0x0C4, (ctype_base::mask)0x050,
    (ctype_base::mask)0x050, (ctype_base::mask)0x050, (ctype_base::mask)0x050, (ctype_base::mask)0x050,
    (ctype_base::mask)0x050, (ctype_base::mask)0x050, (ctype_base::mask)0x1C1, (ctype_base::mask)0x1C1,
    (ctype_base::mask)0x1C1, (ctype_base::mask)0x1C1, (ctype_base::mask)0x1C1, (ctype_base::mask)0x1C1,
    (ctype_base::mask)0x141, (ctype_base::mask)0x141, (ctype_base::mask)0x141, (ctype_base::mask)0x141,
    (ctype_base::mask)0x141, (ctype_base::mask)0x141, (ctype_base::mask)0x141, (ctype_base::mask)0x141,
    (ctype_base::mask)0x141, (ctype_base::mask)0x141, (ctype_base::mask)0x141, (ctype_base::mask)0x141,
    (ctype_base::mask)0x141, (ctype_base::mask)0x141, (ctype_base::mask)0x141, (ctype_base::mask)0x141,
    (ctype_base::mask)0x141, (ctype_base::mask)0x141, (ctype_base::mask)0x141, (ctype_base::mask)0x141,
    (ctype_base::mask)0x050, (ctype_base::mask)0x050, (ctype_base::mask)0x050, (ctype_base::mask)0x050,
    (ctype_base::mask)0x050, (ctype_base::mask)0x050, (ctype_base::mask)0x1C2, (ctype_base::mask)0x1C2,
    (ctype_base::mask)0x1C2, (ctype_base::mask)0x1C2, (ctype_base::mask)0x1C2, (ctype_base::mask)0x1C2,
    (ctype_base::mask)0x142, (ctype_base::mask)0x142, (ctype_base::mask)0x142, (ctype_base::mask)0x142,
    (ctype_base::mask)0x142, (ctype_base::mask)0x142, (ctype_base::mask)0x142, (ctype_base::mask)0x142,
    (ctype_base::mask)0x142, (ctype_base::mask)0x142, (ctype_base::mask)0x142, (ctype_base::mask)0x142,
    (ctype_base::mask)0x142, (ctype_base::mask)0x142, (ctype_base::mask)0x142, (ctype_base::mask)0x142,
    (ctype_base::mask)0x142, (ctype_base::mask)0x142, (ctype_base::mask)0x142, (ctype_base::mask)0x142,
    (ctype_base::mask)0x050, (ctype_base::mask)0x050, (ctype_base::mask)0x050, (ctype_base::mask)0x050,
    (ctype_base::mask)0x020, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000, (ctype_base::mask)0x000,
    (ctype_base::mask)0x000
};

_STLP_END_NAMESPACE
