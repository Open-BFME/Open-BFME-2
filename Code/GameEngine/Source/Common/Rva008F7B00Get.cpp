// cl: /Ob0

class Rva008F7B00
{
	char m_pad[0xC4];
	char m_slots[20];

public:
	char get(int index);
};

char Rva008F7B00::get(int index)
{
	if (index < 0 || index >= 20)
		return 0;
	return m_slots[index];
}
