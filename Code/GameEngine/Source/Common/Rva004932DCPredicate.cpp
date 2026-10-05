// cl: /O1 /MD
// ?rva004932DC@Rva004932DC@@QAEEXZ @0x004932DC 19B: null-checked byte predicate.
// Evidence: caller 0x0049466D; reads ecx __thiscall; ptr+4 then byte+0x74.
struct Rva004932DCInner {
	unsigned char pad[0x74];
	unsigned char flag;
};
class Rva004932DC {
public:
	unsigned char rva004932DC();
	unsigned char prefix[4];
	Rva004932DCInner *m_ptr;
};
unsigned char Rva004932DC::rva004932DC()
{
	if (m_ptr) {
		if (m_ptr->flag)
			return 1;
	}
	return 0;
}
