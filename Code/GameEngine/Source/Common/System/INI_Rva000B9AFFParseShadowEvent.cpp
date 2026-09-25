// cl: /O1 /GX- /DNDEBUG /MD
// Rva000B9AFF_ParseShadowEvent (retail 0x000B9AFF, 75 bytes). Parses a
// 16-bit flag set through the rowed parseBitString16 at 0x002F21A; when
// nonzero it news a 0x28-byte AudioEventRTS (rowed ctor 0x00079514, whose
// layout below mirrors its TU: string pair, int m_unknown8 at +0x08, five
// zero floats, 20.0f, flags), stores the pointer at instance+0xDC and the
// flag value at m_unknown8, leaving a zero-flag slot untouched. Serves the
// Shadow table entry. Frameless (/GX-): retail keeps no unwind state around
// the news. The AudioEvent role comes from the rowed ctor callee; the
// callback name stays address-derived.

typedef int Int;

class AsciiString
{
public:
	AsciiString() : m_data(0) {}

private:
	void *m_data;
};

class AudioEventRTS
{
public:
	AudioEventRTS();

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

struct Rva000B9AFF_Store
{
	char m_pad[0xDC];
	AudioEventRTS *m_event;
};

class INI
{
public:
	static void parseBitString16(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000B9AFF_ParseShadowEvent(INI *ini, void *instance, void *store, const void *userData);
};

// ?Rva000B9AFF_ParseShadowEvent@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva000B9AFF_ParseShadowEvent(INI *ini, void *instance, void *store, const void *userData)
{
	unsigned int bits = 0;
	INI::parseBitString16(ini, instance, &bits, userData);
	if (bits != 0)
	{
		AudioEventRTS *event = new AudioEventRTS();
		Rva000B9AFF_Store *target = (Rva000B9AFF_Store *)instance;
		target->m_event = event;
		event->m_unknown8 = (Int)bits;
	}
}
