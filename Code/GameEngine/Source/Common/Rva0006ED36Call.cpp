// cl: /MD
//
// RTS3DScene/RTS2DScene::doRender @0x0006ED36/0x0006EE27 (31B each).
// Evidence: 7 callers in W3DView::draw; ecx+0x814 (+0x118) store plus ecx+0x108
// vtable call at +0x30 plus and [esi] 0 clear; ret 4 one pointer arg.

class Rva0006ED36Sub
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
	virtual void draw();
};

// RTS3DScene::doRender (0x0006ED36) and RTS2DScene::doRender (0x0006EE27):
// Zero Hour's "m_camera = cam; DRAW(); m_camera = NULL;" (W3DScene.cpp). Seven
// calls in W3DView::draw (0x00087DA0) render through them. DRAW() is the
// subsystem draw, slot 12 of the subsystem base at +0x108 (0x0006ED55 below
// for the 3D scene); the camera sits at +0x814 (3D) and +0x118 (2D).
class CameraClass;

class RTS3DScene
{
public:
	void doRender(CameraClass *cam);
private:
	char m_pad00[0x108];
	Rva0006ED36Sub m_subsystem;
	char m_pad10C[0x814 - 0x108 - 4];
	CameraClass *m_camera;
};

class RTS2DScene
{
public:
	void doRender(CameraClass *cam);
private:
	char m_pad00[0x108];
	Rva0006ED36Sub m_subsystem;
	char m_pad10C[0x118 - 0x108 - 4];
	CameraClass *m_camera;
};

void RTS3DScene::doRender(CameraClass *cam)
{
	m_camera = cam;
	m_subsystem.draw();
	m_camera = 0;
}

void RTS2DScene::doRender(CameraClass *cam)
{
	m_camera = cam;
	m_subsystem.draw();
	m_camera = 0;
}

// ?draw@Rva0006ED55@@UAEXXZ @0x0006ED55 (26B): that slot 12 itself,
// compiled against the +0x108 subobject. When the +0x814 pointer the
// callers above set is non-null, it hands the whole object and that pointer
// to the rowed 0x00118660 render call. Same object as above, viewed through
// its two bases (the primary one with its own table at offset 0).
bool Rva00118660Call(void *owner, void *camera);

class Rva0006ED55Primary
{
public:
	virtual void p00();
private:
	char m_pad04[0x108 - 4];
};

class Rva0006ED55 : public Rva0006ED55Primary, public Rva0006ED36Sub
{
public:
	virtual void draw();
private:
	char m_pad10C[0x814 - 0x10C];
	void *m_slot814;
};

void Rva0006ED55::draw()
{
	if (m_slot814)
		Rva00118660Call(this, m_slot814);
}
