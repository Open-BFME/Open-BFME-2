// cl: /O1 /DNDEBUG /MD
// ?rva0006F3B2@Rva0006F3B2@@QAE_NXZ @0x0006F3B2 26B: thiscall bool check of byte flag at +0x114 bit0 or inner byte at +0x108 bit 0x20. Evidence: no callees; caller 0x000713D0; neighbours Rva0006F373 and SubsystemInterface.
struct Rva0006F3B2Inner
{
	unsigned char m_pad[0x108];
	unsigned char m_108;
};
class Rva0006F3B2
{
public:
	bool rva0006F3B2(void);
private:
	void *m_00;
	Rva0006F3B2Inner *m_04;
	unsigned char m_pad[0x114 - 8];
	unsigned char m_114;
};
bool Rva0006F3B2::rva0006F3B2(void)
{
	return (m_114 & 1) || (m_04->m_108 & 0x20);
}
