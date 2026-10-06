// cl: /DNDEBUG /MD
// ?rva005310E3@Rva005310E3@@QAEHXZ, retail 0x005310E3, 30 bytes.
// Unlock lane: sits right after 0x0053104A (ends 0x005310E3) before 0x00531113.
// Reads dword [ecx+8] as signed count, bytes [ecx+4] [ecx+5] as flags; returns doubled sum.
// Callers 0x005318F4 and 0x00531FFC (both unclaimed); unblocks 0x00531FE6. No donor; honest address name.
class Rva005310E3
{
public:
	int rva005310E3();
private:
	char m_lead[4];
	unsigned char m_4;
	unsigned char m_5;
	char m_pad[2];
	int m_8;
};
int Rva005310E3::rva005310E3()
{
	int v = m_8;
	if (v < 0)
		v = 0;
	else
		++v;
	if (m_4)
		++v;
	if (m_5) {
		++v;
		++v;
	}
	return v + v;
}
