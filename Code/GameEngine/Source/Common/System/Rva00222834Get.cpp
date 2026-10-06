// cl: /Ireference/shims/bfme2_ascii /EHsc

// ?Rva00222834Get@@YA?AVAsciiString@@H@Z, retail 0x00222834, 90 bytes.
// Free AsciiString(int) via "%d": stack temp format through rowed
// AsciiString::format 0x00038150 then RVO copy through pinned StringBase<char>
// copy 0x000365F0 and temp teardown through rowed releaseBuffer 0x00036410.
// Byte-identical twin of rowed ?intAsStr@@YA?AVAsciiString@@H@Z @0x003B18F4;
// callers 0x002D4404 0x002D44AE 0x002D4545 0x0043F1B8 0x00511C50 prove the
// hidden-return RVO shape. Honest free-function name.
#include "ascii_string.h"


AsciiString Rva00222834Get(int val)
{
	AsciiString tmp;
	tmp.format("%d", val);
	return tmp;
}
