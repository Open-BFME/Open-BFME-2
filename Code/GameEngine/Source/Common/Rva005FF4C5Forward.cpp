// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva005FF4C5@Rva005FF4C5@@QAEXPBVImage@@@Z @0x005FF4C5 8B
// Forwarder: this+4 holds Rva005FF2AC object; tail-jmps to its rva005FF2AC.
// Evidence: prev 0x005FF4BD and next 0x005FF4CD same +4 forwarder precedent;
// callee rowed 0x005FF2AC; caller 0x005FF057; unlocks 0x005FEFCC.
class Image;

class Rva005FF2AC
{
public:
	void rva005FF2AC(const Image *image);
};

class Rva005FF4C5
{
public:
	void rva005FF4C5(const Image *image);
private:
	char m_pad0[4];
	Rva005FF2AC *m_obj;
};

void Rva005FF4C5::rva005FF4C5(const Image *image)
{
	m_obj->rva005FF2AC(image);
}
