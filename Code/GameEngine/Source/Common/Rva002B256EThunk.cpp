// cl: /MD
// ?Rva002B256EGet@@YAPAXXZ @0x002B256E 11B.
// Global-to-method tail jump: mov ecx,[0x00E02D6C]; jmp 0x003B8BAA.
// Evidence: retail 8B 0D 6C 2D E0 00 E9 ...; callee is rowed
// ?rva003B8BAA@Rva003B8BAA@@QAEPAXXZ; callers at 0x0020EBD5 0x003F4FF5 0x0057443C
// 0x00574464 0x00574F2F use eax as vtable object. Tail return gives jmp at /O1.
class Rva00E02D6C; extern Rva00E02D6C *TheCampaignManager;

struct Rva003B8BAAElem
{
	char m_pad[0x20];
	void *m_ptr20;
};
class Rva003B8BAA
{
	char m_pad[0x10];
	int m_index10;
	Rva003B8BAAElem **m_array14;
public:
	void *rva003B8BAA();
};
#define TheRva00E02D6C ((Rva003B8BAA *)TheCampaignManager)

void *Rva002B256EGet(void)
{
	return TheRva00E02D6C->rva003B8BAA();
}
