// cl: /O1 /MD /EHsc
// ?Rva002220DCInit@@YAXXZ @0x002220DC 99B: singleton ensure for Rva00222061.
// If holder g_00DFE4C4 empty, news 0x34 via rowed 0x0002FDA0 and rowed ctor
// 0x00222061, stores via rowed setter 0x00575674, then virtuals +4/+8 on the
// stored object. Callers 0x00222150/0x00222177/0x002221B2/0x0023AB55. Size 0x34
// from push in this body; chain packet calls just-landed 0x00222061.
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

Rva00575674 g_00DFE4C4;

class Rva00222061
{
public:
	Rva00222061();
private:
	char m_data[0x34];
};

void Rva002220DCInit()
{
	if (g_00DFE4C4.m_ptr == 0) {
		Rva00222061 *p = new Rva00222061;
		g_00DFE4C4.rva00575674((Object *)p);
		g_00DFE4C4.m_ptr->v01();
		g_00DFE4C4.m_ptr->v02();
	}
}
