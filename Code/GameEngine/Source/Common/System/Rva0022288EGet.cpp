// cl: /Ireference/shims/bfme2_ascii /EHsc

// ?Rva0022288EGet@@YA?AVAsciiString@@I@Z, retail 0x0022288E, 90 bytes.
// Free AsciiString(unsigned) via "%u": stack temp format through rowed
// AsciiString::format 0x00038150 then RVO copy through pinned StringBase<char>
// copy 0x000365F0 and temp teardown through rowed releaseBuffer 0x00036410.
// Byte-identical twin of rowed ?Rva00222834Get@@YA?AVAsciiString@@H@Z @0x00222834
// which twins ?intAsStr@@YA?AVAsciiString@@H@Z @0x003B18F4 except "%d";
// callers 0x002162E3 0x00216346 0x002163C6 0x002164AC 0x00216547 0x00741100 prove the
// hidden-return RVO shape. Honest free-function name.
#include "ascii_string.h"


AsciiString Rva0022288EGet(unsigned int val)
{
	AsciiString tmp;
	tmp.format("%u", val);
	return tmp;
}
