// cl: /O1 /DNDEBUG /MD
// stlport
//
// ?Rva006F2890RegisterVideoBuffer@Display@@QAEXPAVVideoBuffer@@@Z,
// retail 0x0004B180, 19 bytes. Display video-buffer registry: appends the
// buffer to the buffer list at +0x2A4 through the rowed vector push_back
// at 0x004DFCB0 (fold-shared STL shell; the VideoBuffer spelling rides as
// an alias pin). Sole raw caller is 0x0007270C, the site the BFME1 donor
// (W3DVideoBufferCtorBfme.cpp) calls this method from. Row supersedes the
// same-name pin.

// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

class VideoBuffer;

class Display
{
public:
	void Rva006F2890RegisterVideoBuffer(VideoBuffer *buffer);

private:
	unsigned char m_pad[0x2A4];
	_STL::vector<VideoBuffer *> m_buffers; // +0x2A4
};

// ?Rva006F2890RegisterVideoBuffer@Display@@QAEXPAVVideoBuffer@@@Z @0x0004B180
void Display::Rva006F2890RegisterVideoBuffer(VideoBuffer *buffer)
{
	m_buffers.push_back(buffer);
}
