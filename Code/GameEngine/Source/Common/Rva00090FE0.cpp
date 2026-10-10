// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD
//
// ?rva00090FE0@Rva00090FE0@@QAEHI@Z, retail 0x00090FE0, 224 bytes.
// Elapsed units from timeGetTime (IAT 0x00BBA918): (int)(now - start@+0x50) scaled by the
// rate at +0x40 (halved when flags bit 0x800000 is set), divided by the divisor at +0x44
// and by 1000. With the byte global at VA 0x00DE4498 clear and no 0x44 flag bits the plain
// quotient is returned; otherwise the quotient is clamped to the limit at +0x48 plus one
// with a min() that evaluates the time expression twice, as the retail double read shows.
// Evidence: target bytes and the rowed __allmul/__alldiv; field names are neutral views.

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

extern unsigned char g_00DE4498;

class Rva00090FE0
{
public:
	int rva00090FE0(unsigned int flags);
private:
	char m_pad[0x40];
	int m_rate40;
	int m_divisor44;
	int m_limit48;
	int m_pad4C;
	unsigned long m_start50;
};

int Rva00090FE0::rva00090FE0(unsigned int flags)
{
	if (!g_00DE4498 && !(flags & 0x44))
		return (int)((__int64)(int)(timeGetTime() - m_start50) * m_rate40 / m_divisor44 / 1000);
	int rate = m_rate40;
	if (flags & 0x800000)
		rate >>= 1;
#define RVA00090FE0_MIN(a, b) (((a) < (b)) ? (a) : (b))
	unsigned long now;
	return RVA00090FE0_MIN(m_limit48 + 1, (now = timeGetTime(), (int)((__int64)(int)(now - m_start50) * (__int64)rate / m_divisor44 / 1000)));
#undef RVA00090FE0_MIN
}
