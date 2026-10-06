// cl: /O1 /Oy- /DNDEBUG /MD /arch:SSE
//
// ?rva004ABB4B@Rva004ABB4B@@QAEHXZ @0x004ABB4B 273B.
// LargeGroupAudioUpdate+0x10. A clear flag or a missing object returns the
// module delay. Otherwise a changed position, block, or player bit, or a
// frame that is not still ahead of the host clock, copies the object state
// and registers the slot. The delay is the answer either way.

class Player;
class LargeGroupAudioUpdate;
class Rva0020D959Host;

struct Block19
{
	unsigned int v[19];
};

struct Block4
{
	unsigned int v[4];
};

class Object
{
public:
	bool rva002943B2(const Player *player);
	char m_pad00[0x38];
	float m_f38;
	float m_f3C;
	char m_pad40[0x94 - 0x40];
	Block4 m_94;
	char m_padA4[0x10C - 0xA4];
	Block19 m_10C;
};

class LargeGroupAudioUpdate
{
public:
	int rva004AB7C8() const;

	char m_pad[0x24];
	int m_24;
};

class Rva0020DXXX
{
public:
	void rva0020D8F1(int slot);
};

struct HostClock
{
	char m_pad[0x3C];
	int m_3C;
};

extern Rva0020D959Host *g_00DFE1A8;

class GameLogic
{
public:
	char m_pad[0x40];
	int m_40;
};

extern GameLogic *TheGameLogic;

bool Rva000B3EECNotEqual(const void *a, const void *b);
bool Rva002634F8NotEqual(const void *a, const void *b);

class Rva004ABB4B
{
public:
	int rva004ABB4B();

private:
	char m_pad[0x18];
	int m_28;
	int m_2C;
	Block19 m_30;
	Block4 m_7C;
	bool m_8C;
	bool m_8D;
	char m_pad7E[2];
	int m_90;
};

struct FloatPair
{
	float x;
	float y;
};

int Rva004ABB4B::rva004ABB4B()
{
	const LargeGroupAudioUpdate *mod =
		*(const LargeGroupAudioUpdate **)((char *)this - 0x0C);
	if (!m_8D)
		return mod->rva004AB7C8();

	Object *obj = *(Object **)((char *)this - 8);
	if (!obj)
		return mod->rva004AB7C8();

	Block19 *block19 = &obj->m_10C;
	Block4 *block4 = &obj->m_94;
	bool fresh = obj->rva002943B2(0);
	if (obj->m_f38 != *(float *)&m_28 || obj->m_f3C != *(float *)&m_2C
		|| Rva000B3EECNotEqual(block19, &m_30)
		|| Rva002634F8NotEqual(block4, &m_7C)
		|| fresh != m_8C
		|| m_90 <= ((HostClock *)g_00DFE1A8)->m_3C)
	{
		LargeGroupAudioUpdate *parent =
			(LargeGroupAudioUpdate *)((char *)this - 0x10);
		int slot = parent ? (int)((char *)this + 0x14) : 0;
		((Rva0020DXXX *)g_00DFE1A8)->rva0020D8F1(slot);
		FloatPair pair;
		pair.x = obj->m_f38;
		pair.y = obj->m_f3C;
		m_28 = *(int *)&pair.x;
		m_2C = *(int *)&pair.y;
		m_30 = *block19;
		m_7C = *block4;
		m_8C = fresh;
		m_90 = TheGameLogic->m_40;
	}
	return mod->rva004AB7C8();
}
