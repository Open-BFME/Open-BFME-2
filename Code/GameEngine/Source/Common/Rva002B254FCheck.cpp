// cl: /MD
// ?rva002B254F@Rva002B254F@@QAEHXZ @0x002B254F 31B.
// Guard on own +0xB4 then global Rva003B8BAA bool chase; returns 1/0 int.
// Evidence: retail cmp [ecx+0xB4],0; je; mov ecx,[0x00E02D6C]; call 0x003B8B85 rowed bool;
// test al,al; je; xor eax,eax; inc eax; ret; else xor eax,eax; ret. Chain from 0x003B8B85.
// Global type matches Rva002B256EThunk.cpp and definition in Rva002B47B1Get.cpp.
class Rva00E02D6C; extern Rva00E02D6C *TheCampaignManager;

class Rva003B8BAA
{
public:
	bool rva003B8B85();
};

class Rva002B254F
{
	char m_pad[0xB4];
	unsigned char m_flagB4;
public:
	int rva002B254F();
};

int Rva002B254F::rva002B254F()
{
	if (m_flagB4 != 0 && ((Rva003B8BAA *)TheCampaignManager)->rva003B8B85() != 0)
		return 1;
	return 0;
}
