// cl: /Ireference/shims/bfme2_ascii
// ?rva003F3F83@Rva003F3F83@@QAEHXZ @0x003F3F83 20B
// Predicate over +0x2c: return 0 when 1 or 4, else 1. Evidence: retail
// mov eax,[ecx+0x2c], cmp 1/4 je, xor/inc, ret, no callees.
struct Rva003F3F83
{
	int rva003F3F83();
	unsigned char m_pad[0x2c];
	int m_val;
};
int Rva003F3F83::rva003F3F83()
{
	if (m_val == 1 || m_val == 4)
		return 0;
	return 1;
}
