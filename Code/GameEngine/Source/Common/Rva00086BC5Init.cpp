// cl: /O1 /GX /MD
//
// ?rva00086BC5@Rva00086BC5@@QAEXH@Z @0x00086BC5 133B: EH re-init via new.
// Frees old [m_235C] via slot0(0) plus delete, news 0x20 via rowed new,
// ctors via pinned 0x30F404(arg1), inits via pinned 0x30F36B, fetches
// slot31 via existing TheGameClient to m_2360, stores 4 to m_2354.
// Honest address-derived names except proven new/delete/global;
// boundary verified (mov eax prologue, ret 4).
class Rva00086BC5Old
{
public:
	virtual void *vslot000(int v);
};
class Rva0030F404
{
public:
	Rva0030F404(int v);
private:
	char m_pad00[0x20];
};
class Rva0030F36B
{
public:
	void rva0030F36B();
};
class GameClient
{
public:
	virtual void vslot000();
	virtual void vslot001();
	virtual void vslot002();
	virtual void vslot003();
	virtual void vslot004();
	virtual void vslot005();
	virtual void vslot006();
	virtual void vslot007();
	virtual void vslot008();
	virtual void vslot009();
	virtual void vslot010();
	virtual void vslot011();
	virtual void vslot012();
	virtual void vslot013();
	virtual void vslot014();
	virtual void vslot015();
	virtual void vslot016();
	virtual void vslot017();
	virtual void vslot018();
	virtual void vslot019();
	virtual void vslot020();
	virtual void vslot021();
	virtual void vslot022();
	virtual void vslot023();
	virtual void vslot024();
	virtual void vslot025();
	virtual void vslot026();
	virtual void vslot027();
	virtual void vslot028();
	virtual void vslot029();
	virtual void vslot030();
	virtual int vslot031();
};
extern GameClient *TheGameClient;
class Rva00086BC5
{
public:
	void rva00086BC5(int v);

private:
	char m_pad00[0x2354];
	int m_2354;
	char m_pad2358[0x235C - 0x2358];
	Rva00086BC5Old *m_235C;
	int m_2360;
};
void Rva00086BC5::rva00086BC5(int v)
{
	Rva00086BC5Old *old = m_235C;
	operator delete(old ? old->vslot000(0) : 0);
	Rva0030F404 *p = new Rva0030F404(v);
	m_235C = (Rva00086BC5Old *)p;
	((Rva0030F36B *)p)->rva0030F36B();
	m_2360 = TheGameClient->vslot031();
	m_2354 = 4;
}
