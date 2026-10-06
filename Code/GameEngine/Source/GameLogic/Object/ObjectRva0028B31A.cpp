// cl: /DNDEBUG /MD /EHsc
// ?rva0028B31A@Object@@QAEXH@Z @ 0x0028B31A 65B: clears 8-byte entries at +0x3C5 whose dword matches arg then compacts via rva0028B2BF
// Evidence: chain from just-landed 0x0028B2BF; same +0x3C5 +0x43A layout as neighbours ObjectRva0028B2BF/0028B38D; caller 0x0023D670 passes through dword arg.
class Object
{
public:
	void rva0028B31A(int val);
	void rva0028B2BF();
	char m_pad[0x43B];
};

void Object::rva0028B31A(int val)
{
	int i = 0;
	if (*(signed char *)(m_pad + 0x43A) > 0) {
		unsigned char *p = (unsigned char *)(m_pad + 0x3C5);
		do {
			if (*(int *)(p - 5) == val) {
				p[-1] = 0;
				p[0] = 0;
				p[1] = 0;
				*(int *)(p - 5) = 0;
			}
			i++;
			p += 8;
		} while (i < *(signed char *)(m_pad + 0x43A));
	}
	rva0028B2BF();
}
