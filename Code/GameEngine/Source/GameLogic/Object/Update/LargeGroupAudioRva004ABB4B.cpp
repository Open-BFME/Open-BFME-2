// cl: /O1 /Oy- /DNDEBUG /MD /arch:SSE
// LargeGroupAudioUpdate::update, retail 004ABB4B..004ABC5C (273 bytes).
// Identity: WB 01222A00 names update in LargeGroupAudioUpdate.cpp;
// the retail ctor004AB811 installs C548F0 at owner+10, whose update slot
// reaches this body. Native and WB accesses prove data at this-0C and object
// at this-08. The multiple-inheritance semantic donor is BFME1
// ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f, game/GameEngine/Source/
// GameLogic/Object/Update/LargeGroupAudioUpdate_update.cpp.
// Target layout is independent: two extra interfaces at+20/+24, 19 words
// at+30, four words at+7C and the frame word+90 (ctor and sibling slots).
// LGAU interface names below are structural stand-ins; their purposes are
// not claimed. The delay helper keeps its established ledger spelling,
// although this body calls it on module data. Other callee names remain neutral.
// Replaces the exact address-named view; this is identity repair, not new bytes.

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

#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

bool Rva000B3EECNotEqual(const void *a, const void *b);
bool Rva002634F8NotEqual(const void *a, const void *b);

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
class LGAUDeepBase {
public: virtual void baseAnchor();
protected: const void *m_moduleData; Object *m_object;
};
class LGAUBehaviorInterface { public: virtual void behaviorAnchor(); };
class LGAUUpdateInterface { public: virtual UpdateSleepTime update() = 0; };
class LGAUUpdateBase : public LGAUDeepBase, public LGAUBehaviorInterface, public LGAUUpdateInterface {
private: unsigned int nextFrame; int logicIndex; int state;
};
class LGAUInterface20 { public: virtual void anchor20(); };
class LGAUInterface24 { public: virtual void anchor24(); };
class LargeGroupAudioUpdate : public LGAUUpdateBase, public LGAUInterface20, public LGAUInterface24 {
public:
    virtual UpdateSleepTime update();
    int rva004AB7C8() const;
private:
    int m_28; int m_2C; Block19 m_30; Block4 m_7C;
    bool m_8C; bool m_8D; char pad8E[2]; int m_90;
};

struct FloatPair
{
	float x;
	float y;
};

UpdateSleepTime LargeGroupAudioUpdate::update()
{
	const LargeGroupAudioUpdate *mod =
		(const LargeGroupAudioUpdate *)m_moduleData;
	if (!m_8D)
		return (UpdateSleepTime)mod->rva004AB7C8();

	Object *obj = m_object;
	if (!obj)
		return (UpdateSleepTime)mod->rva004AB7C8();

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
			this;
		int slot = parent ? (int)((char *)this + 0x24) : 0;
		((Rva0020DXXX *)g_00DFE1A8)->rva0020D8F1(slot);
		FloatPair pair;
		pair.x = obj->m_f38;
		pair.y = obj->m_f3C;
		m_28 = *(int *)&pair.x;
		m_2C = *(int *)&pair.y;
		m_30 = *block19;
		m_7C = *block4;
		m_8C = fresh;
		m_90 = TheGameLogic->getFrame();
	}
	return (UpdateSleepTime)mod->rva004AB7C8();
}
