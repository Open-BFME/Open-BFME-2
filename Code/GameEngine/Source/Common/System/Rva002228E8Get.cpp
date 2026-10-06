// cl: /Ireference/shims/bfme2_ascii /EHsc

// ?Rva002228E8Get@@YA?AVAsciiString@@M@Z, retail 0x002228E8, 95 bytes.
// Free AsciiString(float) via "%g": stack temp format through rowed
// AsciiString::format 0x00038150 then RVO copy through pinned StringBase<char>
// copy 0x000365F0 and temp teardown through rowed releaseBuffer 0x00036410.
// Sibling of rowed ?Rva0022288EGet@@YA?AVAsciiString@@I@Z @0x0022288E ("%u");
// callers at 0x00216447 0x00216532 0x002D4480 prove the hidden-return RVO shape.
#include "ascii_string.h"


AsciiString Rva002228E8Get(float val)
{
	AsciiString tmp;
	tmp.format("%g", val);
	return tmp;
}
