// cl: /O1 /EHsc /MD /arch:SSE
// AptMessenger.cpp -- AptMessenger members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function; retail
// supplies the bytes. The per-list player selections are an array of
// pointers at +0x280; each answers through 0x005AFEF7 (unnamed).

typedef int Int;

class Rva005AFEF7List
{
public:
	void rva005AFEF7(Int a, Int b);		// 0x005AFEF7
};

class AptMessenger
{
public:
	void GetSelectedPlayers(Int listIndex, Int a, Int b);

private:
	unsigned char m_pad000[0x280];
	Rva005AFEF7List **m_lists;		// +0x280
};

// AptMessenger::GetSelectedPlayers, retail 0x00511C19.
void AptMessenger::GetSelectedPlayers(Int listIndex, Int a, Int b)
{
	Rva005AFEF7List *list = m_lists[listIndex];
	if (list)
		list->rva005AFEF7(a, b);
}
