// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?rva005952C4@Rva00594DC0@@QAE_NPAXGPAG@Z, retail 0x005952C4 134B.
// Chain of landed Rva00594DC0 convert 0x00594DC0: memcpy 20B, CRC16,
// htonl check, convert, htons key check at +0x88, word extract.
// Callers 0x004D4D7A, prev 0x0059517F send, next 0x0059534A cleanup.
// Else after first guard keeps shared false tail early (jne over xor at +0xd).

extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long hostlong);
extern "C" __declspec(dllimport) unsigned short __stdcall htons(unsigned short hostshort);
unsigned int ComputeCRC(const unsigned char *data, unsigned int length, unsigned int crc);

struct Rva00594DC0Msg
{
	unsigned long m_00;
	unsigned short m_04;
	unsigned short m_06;
	unsigned short m_08;
	unsigned short m_0a;
};

class Rva00594DC0
{
public:
	void rva00594DC0(Rva00594DC0Msg *msg);
	bool rva005952C4(void *src, unsigned short len, unsigned short *out);

private:
	char m_pad[0x88];
	unsigned short m_88;
};

bool Rva00594DC0::rva005952C4(void *src, unsigned short len, unsigned short *out)
{
	unsigned char buf[0x14];
	volatile int keep[3];

	if (src == 0)
		return false;
	else {
		if (len > 0x14)
			return false;
		memcpy(buf, src, 0x14);
		unsigned int crc = ComputeCRC(buf + 4, 0x10, 0);
		if (crc != htonl(*(unsigned long *)buf))
			return false;
		rva00594DC0((Rva00594DC0Msg *)buf);
		keep[0] = len;
		Rva00594DC0Msg *msg = (Rva00594DC0Msg *)buf;
		if (msg->m_06 == m_88 || htons(msg->m_06) == m_88)
			*out = msg->m_08;
		return true;
	}
}
