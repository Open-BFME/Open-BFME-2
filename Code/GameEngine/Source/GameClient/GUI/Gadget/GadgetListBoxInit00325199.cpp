// cl: /DNDEBUG /MD
//
// ?Rva00325199Init@@YAXPAVGameWindow@@@Z, retail 0x00325199, 91 bytes.
// Free-function listbox column init: gets GameWindow user data, bails if
// null or flag +0xB set, allocates count*4 via rowed new[], on failure
// deletes +0x18 via rowed delete[], else memsets new buffer with -1 via
// rowed ji_006291ae thunk, sets flag and input func 0x00324E92 via rowed
// winSetInputFunc. Callers 0x005DD7F1 and 0x00326F8F push one GameWindow*.
// Evidence: callees rowed winGetUserData 0x005C4ACD, new[] 0x0002FDE0,
// delete[] 0x0002FD80, memset thunk 0x006291AE, winSetInputFunc 0x00314147.

typedef unsigned int UnsignedInt;
typedef unsigned int WindowMsgData;

class GameWindow;

enum WindowMsgHandledType
{
	MSG_HANDLED = 0,
	MSG_NOT_HANDLED = 1
};

typedef WindowMsgHandledType (__cdecl *GameWinInputFunc)(GameWindow *, UnsignedInt, WindowMsgData, WindowMsgData);

class GameWindow
{
public:
	void *winGetUserData(void);
	int winSetInputFunc(GameWinInputFunc input);
};

void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *memory);

void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

WindowMsgHandledType Rva00324E92Input(GameWindow *, UnsignedInt, WindowMsgData, WindowMsgData);

struct Rva00325199Data
{
	short m_count;
	char m_pad02[9];
	unsigned char m_flag;
	char m_pad0C[12];
	void *m_old;
	char m_pad1C[28];
	int *m_newBuf;
};

void Rva00325199Init(GameWindow *window)
{
	Rva00325199Data *data = (Rva00325199Data *)window->winGetUserData();
	if (data == 0)
		return;
	if (data->m_flag != 0)
		return;
	int *buf = (int *)operator new[]((unsigned int)(data->m_count * 4));
	data->m_newBuf = buf;
	if (buf == 0)
	{
		operator delete[](data->m_old);
		return;
	}
	ji_006291ae(buf, -1, (unsigned int)(data->m_count * 4));
	data->m_flag = 1;
	window->winSetInputFunc(Rva00324E92Input);
}
