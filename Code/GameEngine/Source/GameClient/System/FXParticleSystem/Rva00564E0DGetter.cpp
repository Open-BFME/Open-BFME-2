// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
// ?rva00564E0D@Rva00564E0D@@QAE?AVAsciiString@@XZ, retail 0x00564E0D, 27 bytes.
// AsciiString at +0xC via rowed StringBase copy 0x000365F0, hidden out-pointer return. Same 27B shape as Rva0056394AGetter and neighbours Image::getName 0x00564DF2 and CDDrive::getDiskName 0x00564E28. Callers in 0x000898B0 0x0009873C 0x00564EC0, no vtable proof so honest Rva name.
#include "ascii_string.h"

struct Pad0C
{
	char m_pad[0x0C];
};

class Rva00564E0D : public Pad0C
{
public:
	AsciiString rva00564E0D();

private:
	AsciiString m_str;
};

AsciiString Rva00564E0D::rva00564E0D()
{
	return m_str;
}
