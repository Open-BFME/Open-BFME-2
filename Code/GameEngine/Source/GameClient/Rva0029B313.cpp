// cl: /MD
// ?rva0029B313@Rva0029B313@@QAEXH@Z @0x0029B313 26B. Two flag bytes at +0x7F9 +0x7F8 then tail-jmp to rowed Rva0029A5D6::rva0029A5D6. Evidence: callees rowed, callers in 0x002A3273, offsets match Rva0029A5D6 pad before +0x7FC.
class Rva0029A5D6
{
public:
	void rva0029A5D6(int arg);
};
class Rva0029B313
{
public:
	void rva0029B313(int arg);
private:
	unsigned char m_pad[0x7F8];
	unsigned char m_7F8;
	unsigned char m_7F9;
	unsigned char m_pad2[2];
};
void Rva0029B313::rva0029B313(int arg)
{
	if (m_7F9 != 0)
		return;
	if (m_7F8 != 0)
		return;
	((Rva0029A5D6 *)this)->rva0029A5D6(arg);
}
