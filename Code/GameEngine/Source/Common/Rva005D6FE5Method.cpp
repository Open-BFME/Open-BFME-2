// cl: /MD
// ?rva005D6FE5@Rva005D6FE5@@QAEEXZ @0x005D6FE5 15B. Read-and-clear byte at m_base+0x121.
// Evidence: thiscall reads ecx+4 then byte at eax+0x121 returns al and zeroes it;
// callers at 0x0058465A 0x00586400; prev/next in Common.
class Rva005D6FE5
{
public:
	unsigned char rva005D6FE5();
private:
	char m_pad[4];
	unsigned int m_base;
};
unsigned char Rva005D6FE5::rva005D6FE5()
{
	unsigned char value = *(unsigned char *)(m_base + 0x121);
	*(unsigned char *)(m_base + 0x121) = 0;
	return value;
}
