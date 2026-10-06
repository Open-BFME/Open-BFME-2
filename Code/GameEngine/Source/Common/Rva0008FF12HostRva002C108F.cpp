// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva002C108F@Rva0008FF12Host@@QAEXXZ, retail 0x002C108F, 185B: slot 41 of vtable 0x007FF658.
// Evidence: vslot slot 41; pin Rva0008FF12Host; caller jmp 0x0008FF1D; callee drawWindow 0x002C0FC9; TheAudio.

class GameWindow
{
public:
	unsigned char m_pad00[0x08];
	unsigned int m_flags8; // +0x08
	unsigned char m_pad0C[0x1F4 - 0x0C];
	int m_1F4; // +0x1F4
	unsigned char m_pad1F8[0x1FC - 0x1F8];
	GameWindow *m_next; // +0x1FC
};

class GameWindowManager
{
protected:
	int drawWindow(GameWindow *window);
	friend class Rva0008FF12Host;
};

template <int N> class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};
template <> class BfmeVirtualSlots<0>
{
};

class AudioManager : public BfmeVirtualSlots<12>
{
public:
	virtual void slot12();
};
extern AudioManager *TheAudio;

class Rva0008FF12Host
{
public:
	void rva002C108F();
	void rva00118A90();
private:
	unsigned char m_pad00[0x10];
	GameWindow *m_head; // +0x10
	unsigned char m_pad14[0x3C - 0x14];
	int m_3C; // +0x3C
};

void Rva0008FF12Host::rva002C108F()
{
	const unsigned int hidden = 0x8000000;
	GameWindow *w = m_head;
	if (w != 0)
	{
		do
		{
			int v = w->m_1F4;
			GameWindow *next = w->m_next;
			if (v == m_3C)
			{
				unsigned int f = w->m_flags8;
				if ((f & hidden) == 0 && (f & 0x40) != 0)
					((GameWindowManager *)this)->drawWindow(w);
			}
			w = next;
		} while (w != 0);
	}
	w = m_head;
	if (w != 0)
	{
		do
		{
			int v = w->m_1F4;
			GameWindow *next = w->m_next;
			if (v == m_3C)
			{
				unsigned int f = w->m_flags8;
				if ((f & hidden) == 0 && (f & 0x60) == 0)
					((GameWindowManager *)this)->drawWindow(w);
			}
			w = next;
		} while (w != 0);
	}
	w = m_head;
	if (w != 0)
	{
		do
		{
			int v = w->m_1F4;
			GameWindow *next = w->m_next;
			if (v == m_3C)
			{
				unsigned int f = w->m_flags8;
				if ((f & hidden) == 0 && (f & 0x20) != 0)
					((GameWindowManager *)this)->drawWindow(w);
			}
			w = next;
		} while (w != 0);
	}
	if (m_3C != 1)
		return;
	AudioManager *audio = TheAudio;
	if (audio != 0)
		audio->slot12();
}
