// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
// ?rva0050FF7F@Rva0050F5A6@@QAEHIPAVGameWindow@@I@Z retail 0x0050FF7F 65B
// Message router over Rva0050F5A6 array: forwards msg/window/val to each
// non-null Rva0050F0AB entry via rowed rva0050FED4, returns 1 on first handled,
// else 0. Evidence: rowed callee 0x0050FED4, count at +0x20 stride-8 array at
// +0x28 as in Rva0050F0AB.cpp Rva0050F5A6, caller 0x005101D3, ret 0xC.
class GameWindow;

class Rva0050F0AB
{
public:
	int rva0050FED4(unsigned int msg, GameWindow *window, unsigned int val);
};

class Rva0050F5A6
{
public:
	int rva0050FF7F(unsigned int msg, GameWindow *window, unsigned int val);
private:
	char m_pad00[0x20];
	int m_20;
	char m_pad24[0x28 - 0x24];
	struct Entry
	{
		Rva0050F0AB *m_obj;
		int m_pad04;
	};
	Entry m_entries[1];
};

int Rva0050F5A6::rva0050FF7F(unsigned int msg, GameWindow *window, unsigned int val)
{
	for (int i = 0; i < m_20; ++i)
	{
		Rva0050F0AB *entry = m_entries[i].m_obj;
		if (entry != 0 && entry->rva0050FED4(msg, window, val) == 1)
			return 1;
	}
	return 0;
}
