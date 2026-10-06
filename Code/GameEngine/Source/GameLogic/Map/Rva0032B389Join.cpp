// cl: /Ireference/shims/bfme2_ascii
//
// ?Rva0032B389Join@@YA?AVAsciiString@@ABV1@0@Z @ 0x0032B389 (98B).
// Free path-join: tmp(a) + '/' + concat(b), return tmp by value via hidden
// pointer (sret). Evidence: calls pin StringBase copy 0x000365F0 twice, row AsciiString
// append-char 0x000065FA, row StringBase concat 0x00006987, row
// releaseBuffer 0x00036410; 12 callers in 0x00209xxx/0x0020Cxxx/0x0032E02B.
#include "ascii_string.h"


AsciiString Rva0032B389Join(const AsciiString &a, const AsciiString &b)
{
	AsciiString tmp(a);
	tmp += '/';
	((StringBase<char> *)&tmp)->concat(*(const StringBase<char> *)&b);
	return tmp;
}
