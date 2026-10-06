// cl: /DNDEBUG /MD
// ?rva0052DA63@Rva0052DA63@@QAEXPAX@Z, retail 0x0052DA63, 50 bytes.
// Slot link/clear via rowed set@Rva0027C306DwordSlot 0x0027C306.
// Evidence: unlock lane; callees rowed; callers 0x002E8F78 0x002E901F 0x002E907C.
class Rva0027C306DwordSlot
{
public:
	void set(int value);
};

class Rva0052DA63
{
public:
	void rva0052DA63(void *arg);
private:
	char _pad00[4];
	Rva0027C306DwordSlot *m_4;
};

void Rva0052DA63::rva0052DA63(void *arg)
{
	if (arg)
	{
		if (!m_4)
		{
			m_4 = (Rva0027C306DwordSlot *)arg;
			((Rva0027C306DwordSlot *)arg)->set((int)this);
		}
	}
	else
	{
		if (m_4)
			m_4->set(0);
		m_4 = 0;
	}
}
