// ?rva004989F5@Rva004989F5@@QAEXXZ
// partial score=0.96 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD /EHsc
// ?rva004989F5@Rva004989F5@@QAEXXZ @0x004989F5 189B via TheAudio plus OpaqueRef plus ObjectID plus vector-ish branches
// Evidence: callees rowed BfmeAudioEventPrefix136 ctor 0x002DA461 plus TailRecord dtor 0x002D9A43 plus TheAudio; callers 0x00498AF9 plus 0x004996E4 plus 0x004998EC; unblocks 0x00498AB2; offsets +0x44 ObjectID +0x28 mode +0x8 +0xc holders +0x48 flag.
#include "Common/BfmeAudioEventPrefix136.h"

class AudioManager
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual int v25(BfmeAudioEventPrefix136 *p);
	virtual void v26();
	virtual void v27(ObjectID id);
};

extern AudioManager *TheAudio;

struct Holder004989F508
{
	char m_pad[0x20];
	OpaqueRefElement4 m_ref20;
	char m_pad24[0x28 - 0x24];
	OpaqueRefElement4 m_ref28;
};

struct Holder004989F50C
{
	char m_pad[0x74];
	ObjectID m_id74;
};

class Rva004989F5
{
public:
	void rva004989F5();
private:
	char m_pad00[0x08];
	Holder004989F508 *m_ptr08;
	Holder004989F50C *m_ptr0C;
	char m_pad10[0x28 - 0x10];
	int m_mode28;
	char m_pad2C[0x44 - 0x2C];
	ObjectID m_obj44;
	bool m_flag48;
};

// ?rva004989F5@Rva004989F5@@QAEXXZ present-unmatched
void Rva004989F5::rva004989F5()
{
	TheAudio->v27(m_obj44);
	int mode = m_mode28;
	Holder004989F50C *h0C = m_ptr0C;
	Holder004989F508 *h08 = m_ptr08;
	if (mode >= 0)
	{
		if (mode > 1)
		{
			if (mode <= 3)
			{
				OpaqueRefElement4 *ref = &h08->m_ref28;
				if (ref->referent != 0)
				{
					BfmeAudioEventPrefix136 tmp(*ref, h0C->m_id74);
					TheAudio->v25(&tmp);
				}
			}
		}
		else
		{
			OpaqueRefElement4 *ref = &h08->m_ref20;
			if (ref->referent != 0)
			{
				BfmeAudioEventPrefix136 tmp(*ref, h0C->m_id74);
				TheAudio->v25(&tmp);
			}
		}
	}
	m_flag48 = true;
}
