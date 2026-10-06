// cl: /DNDEBUG /MD /EHsc
// ?rva0028B2BF@Object@@QAEXXZ @ 0x0028B2BF 91B: compacts 8-byte entries at +0x3C5 skipping zeros counted by signed byte at +0x43A
// Evidence: unlock lane, callers 0x0028B352 0x0029208A, neighbours ObjectRva0028B265/0028B38D share flags.
class Object
{
public:
	void rva0028B2BF();
	char m_pad[0x43B];
};

void Object::rva0028B2BF()
{
	int outCount = 0;
	int i = 0;
	if (*(signed char *)(m_pad + 0x43A) > 0) {
		unsigned char *src = (unsigned char *)(m_pad + 0x3C6);
		unsigned char *dst = (unsigned char *)(m_pad + 0x3C5);
		do {
			if (*src != 0) {
				outCount++;
				dst[-1] = 0;
				dst[0] = 0;
				dst[1] = *src;
				*(int *)(dst - 5) = *(int *)(src - 6);
				dst += 8;
			}
			i++;
			src += 8;
		} while (i < *(signed char *)(m_pad + 0x43A));
	}
	*(unsigned char *)(m_pad + 0x43A) = (unsigned char)outCount;
}
