// cl: /O1 /DNDEBUG /MD
//
// ?rva004B0E9C@Rva004B0E9C@@QAEXXZ @0x004B0E9C 32B.
// When the pointer at +0x9C is live and the dword at [that+4]+0x4C is not
// -1, call 0x004DD2C0 on it and clear the slot.

class Rva004DD2C0Inner
{
public:
	char m_pad[0x4C];
	int m_field;
};

struct EmotionEntry;
struct Rva004DD018Arg;

class EmotionNugget
{
public:
    bool CanBeActivatedFor(int,int,Rva004DD018Arg *);
    void OnDeactivation();
    char pad[4]; EmotionEntry *entry;
};

class Rva004B0E9C
{
public:
	void rva004B0E9C();

private:
	char m_pad[0x9C];
	EmotionNugget *m_slot;
};

void Rva004B0E9C::rva004B0E9C()
{
	EmotionNugget *slot = m_slot;
	if (slot != 0 && ((Rva004DD2C0Inner *)slot->entry)->m_field != -1)
	{
		slot->OnDeactivation();
		m_slot = 0;
	}
}
