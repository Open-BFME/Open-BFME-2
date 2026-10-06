// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// The shared headers declare these members with the access/virtual spelling
// the referring objects use; this TU emits the paired definition spelling.
// Same function, same address: bind the header spelling here.
#pragma comment(linker, "/alternatename:??1AudioEventRTS@@UAE@XZ=??1AudioEventRTS@@QAE@XZ")

//
// ??1AudioEventRTS@@QAE@XZ, retail 0x000793FA, 53 bytes. Dedicated TU.
//
// AudioEventRTS teardown destroys its two strings through the folded string
// teardown (0x36410 pin). The retail body follows that shape with the usual
// cookie and state transitions; the class view matches the constructor TU.

#include "ascii_string.h"

class AudioEventRTS
{
public:
	~AudioEventRTS();

private:
	AsciiString m_first;
	AsciiString m_second;
};

// ??1AudioEventRTS@@QAE@XZ
AudioEventRTS::~AudioEventRTS()
{
}
