// cl: /O1
// ?rva002D3726@Rva002D3726@@QAEXPAUObj00526309@@@Z @0x002D3726 24B: null-guarded forward.
// Target evidence: null check on stack arg then [this+0x10]+0xc0 tail-jmp to rowed
// ?rva00526333@Rva00526333@@QAEXPAUObj00526309@@@Z 0x00526333; callers 0x00291C64
// and 0x002936F1; prev 0x002D371D next 0x002D3756.
struct Obj00526309;
class Rva00526333
{
public:
	void rva00526333(Obj00526309 *obj);
};

struct Obj00526309
{
	char m_pad[4];
	void *m_4;
};

struct Rva002D3726Mid
{
	char m_pad[0xc0];
	Rva00526333 m_obj;
};

class Rva002D3726
{
public:
	void rva002D3726(Obj00526309 *obj);
private:
	char m_pad[0x10];
	Rva002D3726Mid *m_mid;
};

void Rva002D3726::rva002D3726(Obj00526309 *obj)
{
	if (obj == 0)
		return;
	m_mid->m_obj.rva00526333(obj);
}
