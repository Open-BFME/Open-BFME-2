// cl: /DNDEBUG /MD
// ?rva0040C4CB@Rva0040C4CB@@QAEEPAXH@Z @0x0040C4CB 51B. Copy via rowed
// 0x0037DE0E plus int param +0xA8 and this +0xC0 to dest +0xAC, return 1/0.
// Evidence: chain of 0x0037DE0E row, ret 8, caller 0x0040D7A8 passes stack
// struct plus dword at +0x1C, neighbours Rva0040C351Ctor and ConstIntGetters4.
class Rva0037DE0E
{
public:
	unsigned char rva0037DE0E(void *dest);
};
class Rva0040C4CB
{
public:
	unsigned char rva0040C4CB(void *dest, int val);
private:
	char m_pad[0xC0];
	int m_c0;
};
unsigned char Rva0040C4CB::rva0040C4CB(void *destPtr, int val)
{
	char *dest = (char *)destPtr;
	char *src = (char *)this;
	if (((Rva0037DE0E *)(void *)this)->rva0037DE0E(dest)) {
		*(int *)(dest + 0xA8) = val;
		*(int *)(dest + 0xAC) = *(int *)(src + 0xC0);
		return 1;
	}
	return 0;
}
