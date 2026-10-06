// cl: /DNDEBUG /MD /EHsc
//
// ??1Rva00496A63@@QAE@XZ, retail 0x00496A63, 53 bytes.
// Target evidence: called per element of the +0x18 vector by
// BannerCarrierUpdateModuleData dtor 0x00497056 and by the scalar wrapper
// 0x00496B2C; donor BFME1 BannerCarrierUpdateModuleDataDestructors proves a
// two-string element. Destroys AsciiStrings at +0 and +0x54 via pinned
// ??1?$StringBase@D@@QAE@XZ at 0x00036410; no vptr restores so non-virtual.
// Layout follows the Rva0045EF90Dtor StringBase precedent.

template <typename T>
class StringBase
{
public:
	~StringBase();

private:
	void *m_data;
};

typedef StringBase<char> AsciiString;

class Rva00496A63
{
public:
	~Rva00496A63();

private:
	AsciiString m_first; // +0
	unsigned char m_pad04[0x54 - 4];
	AsciiString m_second; // +0x54
};

Rva00496A63::~Rva00496A63()
{
}
