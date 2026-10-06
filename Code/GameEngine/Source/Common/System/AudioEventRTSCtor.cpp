// cl: /Ireference/shims/bfme2_ascii /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0AudioEventRTS@@QAE@XZ, retail 0x00079514, 64 bytes. Dedicated TU.
//
// AudioEventRTS default-constructs empty: two null strings, a zeroed int,
// five zero floats, a 20.0f default, two zero flags and a set one. The
// retail body is frameless straight-line member stores with no calls.

typedef int Int;

#define NULL 0

#include "ascii_string.h"

class AudioEventRTS
{
public:
	AudioEventRTS();

private:
	AsciiString m_first;
	AsciiString m_second;
	Int m_unknown8;
	float m_floatC;
	float m_float10;
	float m_float14;
	float m_float18;
	float m_float1C;
	float m_float20;
	unsigned char m_byte24;
	unsigned char m_byte25;
	unsigned char m_byte26;
};

// ??0AudioEventRTS@@QAE@XZ
AudioEventRTS::AudioEventRTS()
	: m_unknown8(0),
	  m_floatC(0.0f),
	  m_float10(0.0f),
	  m_float14(0.0f),
	  m_float18(0.0f),
	  m_float1C(0.0f),
	  m_float20(20.0f),
	  m_byte24(0),
	  m_byte25(0),
	  m_byte26(1)
{
}
