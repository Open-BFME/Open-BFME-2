// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?rva0049C67E@Rva0049C67E@@QAEXPAVObject@@@Z @0x0049C67E 99B ret 4.
// Null object returns. Otherwise clear the id via the 71B neighbour, zero
// +0x89, play FXList at [[this+4]+0xD8] from the object's +0x38, set status
// 3, then store 1 at +0x88 and 1.0 at +0x8C.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Matrix3D;

class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *mtx, float speed, const Coord3D *secondary);
};

enum ObjectStatusTypes
{
	OS_3 = 3
};

class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool set);
	char m_pad[0x38];
	Coord3D m_pos;
};

struct Rva0049C67EInner
{
	char m_pad[0xD8];
	FXList *m_fx;
};

class Rva0049C592
{
public:
	void rva0049C592();
};

class Rva0049C67E
{
public:
	void rva0049C67E(Object *obj);

private:
	char m_pad0[4];
	Rva0049C67EInner *m_inner;
	char m_pad8[0x88 - 8];
	unsigned char m_88;
	unsigned char m_89;
	char m_pad8A[2];
	float m_8c;
};

void Rva0049C67E::rva0049C67E(Object *obj)
{
	if (obj == 0)
		return;
	((Rva0049C592 *)this)->rva0049C592();
	Rva0049C67EInner *inner = m_inner;
	m_89 = 0;
	FXList *fx = inner->m_fx;
	if (fx != 0)
		FXList::doFXPos(fx, &obj->m_pos, 0, 0.0f, 0);
	obj->setStatus(OS_3, true);
	m_88 = 1;
	m_8c = 1.0f;
}
