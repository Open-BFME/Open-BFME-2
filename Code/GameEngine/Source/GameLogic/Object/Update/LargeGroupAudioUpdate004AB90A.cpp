// cl: /DNDEBUG /MD
// ?rva004AB90A@LargeGroupAudioUpdate@@QAEXXZ, retail 0x004AB90A, 152 bytes.
// Target evidence: linkbody LINK BONUS 48B; callers jmp at 0x004ABA7C 0x004ABB40 in LargeGroupAudioUpdateSlots.cpp; callees rowed 0x0020D925 0x004AB7C8 0x0044DF71 0x002943B2; layout +4 moduledata +8 object +0x24 host +0x28 position pair +0x30/+0x7C state +0x8C bool +0x8D flag +0x90 GameLogic from slots and 004AB9A2 precedents.
class Object;
class Player;
class LargeGroupAudioUpdate;
enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
class Rva0020DXXX
{
public:
  void rva0020D925(int v);
};
class Rva0020D959Host;
Rva0020D959Host *g_00DFE1A8;
class Player
{
};
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
	unsigned char m_pad00[0x38];
	int m_38;
	int m_3C;
	unsigned char m_pad40[0x94 - 0x40];
	Block4 m_94;
	unsigned char m_padA4[0x10C - 0xA4];
	Block19 m_10C;
};
class GameLogic
{
public:
	unsigned char m_pad00[0x40];
	int m_40;
};
extern GameLogic *TheGameLogic;
inline unsigned char Inv20(unsigned int v)
{
	return (unsigned char)~(v >> 20);
}
class UpdateModule
{
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime t);
	unsigned char m_pad00[0x04];
	const LargeGroupAudioUpdate *m_04;
	Object *m_object;
	unsigned char m_pad0C[0x24 - 0x0C];
};
class LargeGroupAudioUpdate : public UpdateModule
{
public:
	int rva004AB7C8() const;
	void rva004AB90A();
private:
	int m_24;
	int m_28;
	int m_2C;
	Block19 m_30;
	Block4 m_7C;
	bool m_8C;
	bool m_8D;
	unsigned char m_pad8E[0x90 - 0x8E];
	int m_90;
};
void LargeGroupAudioUpdate::rva004AB90A()
{
	if (m_8D)
		return;
	if (((Inv20(m_object->m_94.v[1]) & 1) == 0))
		return;
	m_8D = true;
	((Rva0020DXXX *)g_00DFE1A8)->rva0020D925((int)&m_24);
	Object *obj = m_object;
	int delay = m_04->rva004AB7C8();
	setWakeFrame(obj, (UpdateSleepTime)delay);
	m_28 = obj->m_38;
	m_2C = obj->m_3C;
	m_30 = obj->m_10C;
	m_7C = obj->m_94;
	m_8C = obj->rva002943B2(0);
	m_90 = TheGameLogic->m_40;
}
