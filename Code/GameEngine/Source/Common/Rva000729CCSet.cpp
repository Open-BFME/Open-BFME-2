// cl: /MD
// ?rva000729CC@Rva000729CC@@QAEX_N@Z, RVA 0x000729CC, 14B. Two-byte flag setter:
// [ecx+0x36]=arg byte then [ecx+0x35]=1, ret 4. Evidence: adjacent to 0x000729DA,
// callers in unclaimed 0x0046d58b/0x00444fb9/0x00444ff2; honest address name.
class Rva000729CC
{
public:
	void rva000729CC(bool on);
private:
	unsigned char m_pad[0x35];
	bool m_flag35;
	bool m_flag36;
};
void Rva000729CC::rva000729CC(bool on)
{
	m_flag36 = on;
	m_flag35 = true;
}
