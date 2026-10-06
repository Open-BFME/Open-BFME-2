// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHsc

// ?rva005295D5@Rva0052936C@@QAEXH@Z @0x005295D5 83B
// Target evidence: reads the +0xDC indexed global window, compares its button data with slot +0x10,
// refreshes through 0x005294FC on change, dispatches slot 1 through +0x0C, and calls +0x04.
// Structural inference: the six entries at +0x64 with stride 0x14 share the 0x0052936C owner view.
class GameWindow;
void *__cdecl GadgetButtonGetData(GameWindow *window);
extern void *g_00E01CFC;

struct Rva005295D5WindowTable
{
	char m_pad00[0xDC];
	GameWindow *m_windows[6];
};

class Rva005295D5Virtual
{
public:
	virtual void slot00();
	virtual void slot01();
};

class Rva005C3E81
{
public:
	void rva005C3E81();
};

class Rva0052936C
{
private:
	struct Elem
	{
		void *m_00;
		Rva005C3E81 *m_04;
		int m_08;
		Rva005295D5Virtual *m_0C;
		void *m_10;
	};

public:
	void rva005295D5(int index);
	void rva005294FC(int index);

private:
	char m_pad00[0x64];
	Elem m_elems[6];
};

void Rva0052936C::rva005295D5(int index)
{
	Rva005295D5WindowTable *table = (Rva005295D5WindowTable *)g_00E01CFC;
	GameWindow *window = table->m_windows[index];
	Elem *entry = &m_elems[index];
	if (window)
	{
		void *data = GadgetButtonGetData(window);
		if (data != entry->m_10)
			rva005294FC(index);
	}
	Rva005295D5Virtual *callback = entry->m_0C;
	if (callback)
		callback->slot01();
	if (entry->m_04)
		entry->m_04->rva005C3E81();
}
