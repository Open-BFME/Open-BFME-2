// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva00317C34@Rva00317C34@@QAEXVAsciiString@@@Z @0x00317C34 52B: AsciiString setter at +4 via operator= 0x000366F0 then param release via 0x00036410 with EH prolog. Evidence: retail lea ebp+8 plus add ecx 4 plus pin-only operator= plus rowed releaseBuffer plus EH_prolog with scope 0x00B7A71F; caller 0x003181D7; same 52B shape as 0x004D65F9 and 0x002AAE81.
#include "ascii_string.h"
class Rva00317C34
{
public:
	void rva00317C34(AsciiString s);
private:
	char m_pad00[4];
	AsciiString m_str04;
};
void Rva00317C34::rva00317C34(AsciiString s)
{
	AsciiString &slot = m_str04;
	slot = s;
}
