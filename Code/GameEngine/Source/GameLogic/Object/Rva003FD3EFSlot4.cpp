// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX /Ireference/shims/moduledata /ICode/GameEngine/Include
// ?rva003FD43B@Rva003FD3EF@@UAE_NXZ @0x003FD43B 93B: __thiscall bool method slot 4 offset 0x10 of vtable 0x007FE024. Guards +0x0C referent then BfmeAudioEventPrefix136(ref 1) plus m_b51 1 then g_009FE1C8 Rva0021291F call returns true. Evidence: vtable 0x007FE024 slot 4 plus rowed ctor 0x002D97D6 plus rowed dtor 0x002D9A43 plus rowed 0x0021291F plus g_009FE1C8 plus donor Rva003FD3EFDtor.
#include "Common/Snapshot.h"
#include "Common/BfmeAudioEventPrefix136.h"

class Rva0021291F
{
public:
	void rva0021291F(const void *key);
};

class Rva0021294A;
extern Rva0021294A *g_009FE1C8;

class Rva003FD3EF : public Snapshot
{
public:
	virtual ~Rva003FD3EF();
	virtual bool rva003FD43B();
private:
	char m_pad04[8];
	OpaqueRefElement4 m_0c;
};

bool Rva003FD3EF::rva003FD43B()
{
	if (m_0c.referent == 0)
		return true;
	BfmeAudioEventPrefix136 evt(m_0c, 1);
	evt.m_b51 = 1;
	((Rva0021291F *)g_009FE1C8)->rva0021291F(&evt);
	return true;
}
