// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
// ?rva0056394A@Rva0056394A@@QAE?AVAsciiString@@XZ, retail 0x0056394A, 27 bytes.
// AsciiString at +0x24 (detailTexture of embedded GpuDrawModuleInfo at +0x18:
// GpuDraw vptr +4 totalFrames +8 framesPerRow +0xC detailTexture; +0x18+0xC=+0x24).
// Copies via rowed StringBase<char> copy 0x000365F0 and returns hidden out-pointer.
// Neighbours DoXfer 0x0056390A and ctor 0x00563981 (GpuDrawModuleInfo, 0x14).
// Callers in huge printers, no vtable proof so honest Rva name.
#include "ascii_string.h"

struct Pad24
{
	char m_pad[0x24];
};

class Rva0056394A : public Pad24
{
public:
	AsciiString rva0056394A();

private:
	AsciiString m_str;
};

AsciiString Rva0056394A::rva0056394A()
{
	return m_str;
}
