// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /EHsc /MD /DNDEBUG
//
// ?rva00499C6C@Rva00499C6C@@QAEXXZ @0x00499C6C 172B.
// Clears +0x28, stores the logic frame at +0x30, and if the object's
// module reports byte +0x31, marks status 0x12 and plays the ref at +0x20.

#include "Common/BfmeAudioEventPrefix136.h"

class AudioManager;
extern AudioManager *TheAudio;

class GameLogic
{
public:
	char m_pad[0x40];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

class Rva00373EC6
{
public:
	void rva00374815();
	char m_pad[0x31];
	unsigned char m_31;
};

class Object
{
public:
	Rva00373EC6 *rva0028F4BC();
	void setStatus(ObjectStatusTypes status, bool set);
	void rva0028EC68(int kind, void *payload, int flag);
	char m_pad[0x74];
	ObjectID m_id;
};

class Rva00499C6CAudio
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();
	virtual void s9();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *evt);
};

class BfmeC987
{
public:
	void bfmeGo987C();
};

struct Rva00499C6CHolder
{
	char m_pad[0x20];
	OpaqueRefElement4 m_ref;
};

class Rva00499C6C
{
public:
	void rva00499C6C();
	char m_pad[4];
	Rva00499C6CHolder *m_holder;
	Object *m_obj;
	char m_gap[0x1C];
	int m_28;
	char m_gap2[4];
	unsigned int m_30;
};

void Rva00499C6C::rva00499C6C()
{
	unsigned int frame = TheGameLogic->m_frame;
	Rva00499C6CHolder *holder = m_holder;
	m_28 = 0;
	Object *obj = m_obj;
	m_30 = frame;
	Rva00373EC6 *mod = obj->rva0028F4BC();
	if (mod != 0 && mod->m_31 != 0)
	{
		mod->rva00374815();
		obj->setStatus((ObjectStatusTypes)0x12, false);
		obj->rva0028EC68(5, 0, 1);
		if (holder->m_ref.referent != 0)
		{
			BfmeAudioEventPrefix136 evt(holder->m_ref, obj->m_id);
			reinterpret_cast<Rva00499C6CAudio *>(TheAudio)->addAudioEvent(&evt);
		}
	}
	reinterpret_cast<BfmeC987 *>(this)->bfmeGo987C();
}
