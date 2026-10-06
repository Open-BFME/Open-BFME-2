// cl: /MD /EHsc
// ?Rva00220DCDInit@@YAXXZ @0x00220DCD 99B: singleton ensure for Rva00220CD4.
// If holder g_00DFE490 empty, news 0x1C via rowed 0x0002FDA0 and rowed ctor
// 0x00220C74, stores via rowed setter 0x00575674, then virtuals +4/+8 on the
// stored object. Callers 0x00220E4A/0x0023AB4B/0x00406B9A. Size 0x1C from
// push in this body; vtable 0x007E6A84 from ctor TU.
class Object
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
};

class Rva00575674
{
public:
	void rva00575674(Object *p);
	Object *m_ptr;
};

extern Rva00575674 g_00DFE490;

class Rva00220CD4
{
public:
	Rva00220CD4();
private:
	char m_data[0x1C];
};

void Rva00220DCDInit()
{
	if (g_00DFE490.m_ptr == 0) {
		Rva00220CD4 *p = new Rva00220CD4;
		g_00DFE490.rva00575674((Object *)p);
		g_00DFE490.m_ptr->v01();
		g_00DFE490.m_ptr->v02();
	}
}
// ?g_00DFE490@@3VRva00575674@@A: the global at VA 0xdfe490 is ?g_00DFE490@@3PAXA.
#pragma comment(linker, "/alternatename:?g_00DFE490@@3VRva00575674@@A=?g_00DFE490@@3PAXA")
