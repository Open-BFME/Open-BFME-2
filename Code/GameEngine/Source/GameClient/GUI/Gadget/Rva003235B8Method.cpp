// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?rva003235B8@Rva003235B8@@QAEHPBVImage@@HHH@Z @0x003235B8 97B
// __thiscall int method with 4 stack args (Image*, width, height, color), ret 0x10.
// Null-guards this+0 GameWindow*, fetches listbox via rowed winGetUserData 0x005C4ACD
// userData+8, fetches ListboxData via second winGetUserData + listbox winGetUserData,
// grows via rowed GadgetListBoxSetListLength 0x00326E21 when endPos(+0x2C) >= listLength(+0),
// returns rowed GadgetListBoxAddEntryImage 0x00324380 (listbox, image, -1, 0, height, width, true, color).
// Evidence: callees all rowed; callers 0x00323D72 0x00440365 0x00440427 0x005BA8E5; adjacent to
// Rva00323619Setter.cpp (0x00323619) with same userData+8 listbox pattern; LINK BONUS via 0x005BA803.
class GameWindow
{
public:
	void *winGetUserData();
};

class Image;

void GadgetListBoxSetListLength(GameWindow *listbox, int newLength);
int GadgetListBoxAddEntryImage(GameWindow *listbox, const Image *image, int row, int column, int hight, int width, bool overwrite, int color);

struct ListboxData
{
	short m_listLength;
	char m_pad02[0x2A];
	short m_endPos;
};

class Rva003235B8
{
public:
	int rva003235B8(const Image *image, int width, int height, int color);
private:
	GameWindow *m_window;
};

int Rva003235B8::rva003235B8(const Image *image, int width, int height, int color)
{
	if (m_window == 0)
		return -1;
	GameWindow *listBox = *(GameWindow **)((char *)m_window->winGetUserData() + 8);
	ListboxData *listData = (ListboxData *)((GameWindow *)*(GameWindow **)((char *)m_window->winGetUserData() + 8))->winGetUserData();
	if (listData->m_endPos >= listData->m_listLength)
		GadgetListBoxSetListLength(listBox, listData->m_listLength * 2);
	return GadgetListBoxAddEntryImage(listBox, image, -1, 0, height, width, true, color);
}
