// cl: /O1 /GX /arch:SSE /MD /DNDEBUG
//
// ??1Rva0031468C@@QAE@XZ, retail 0x0031468C, 80 bytes.
// Non-virtual dtor over four AsciiString members at +0x00/+0x04/+0x08/+0x0C
// through the pinned StringBase<char> body at 0x00036410 with EH states
// 2/1/0/-1. No vptr store and no base call. Callers are the scalar deleting
// dtor at 0x00314926 and the GameWindow dtor at 0x00314A6C (heap slot
// +0x214, explicit dtor plus operator delete). Identity unproven beyond the
// four-string layout, so an honest address name is used.
class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class Rva0031468C
{
public:
	~Rva0031468C();

private:
	AsciiString m_str00; // +0x00
	AsciiString m_str04; // +0x04
	AsciiString m_str08; // +0x08
	AsciiString m_str0C; // +0x0C
};

Rva0031468C::~Rva0031468C()
{
}
