// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /EHsc
//
// ?rva00455076@CastleBehavior@@UAEXABUOpaqueRefElement4@@H@Z 104B @0x00455076:
// slot 13 of CastleBehavior vtable 0x0081A780 (and Rva00455050 0x00840608).
// Builds BfmeAudioEventPrefix136 from OpaqueRefElement4+0, applies int arg
// via rowed CondSetter, submits via TheAudio slot 0x64, stores result at
// +0x24, destroys tail record. Evidence: vtable slots, rowed E8 callees,
// TheAudio/TheEmptyString-style extern names in packet, prev/next WallHub
// neighbours. Owner class proven by vtable; method name stays honest.

#include "Common/BfmeAudioEventPrefix136.h"

class Rva002D9531
{
public:
	void rva002D9531(int v);
};

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
};

extern AudioManager *TheAudio;

class CastleBehavior
{
public:
	virtual void rva00455076(const OpaqueRefElement4 &o, int v);
private:
	char m_pad04[0x24 - 4];
	int m_24;
};

void CastleBehavior::rva00455076(const OpaqueRefElement4 &o, int v)
{
	BfmeAudioEventPrefix136 tmp(o, 0);
	((Rva002D9531 *)&tmp)->rva002D9531(v);
	int r = TheAudio->v25(&tmp);
	m_24 = r;
}
