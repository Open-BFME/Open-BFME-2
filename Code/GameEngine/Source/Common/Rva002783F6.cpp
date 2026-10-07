// cl: /O1 /MD
class Rva002743D7Host
{
public:
	void rva002743D7();
};
class Rva00278341Host
{
public:
	void rva00278341(int v, int w);
};
class Rva002783F6Virt
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1C();
	virtual int v20();
};
struct Rva002783F6Mid
{
	unsigned char m_pad[0x254];
	Rva002783F6Virt *m_254obj;
};
class Rva002783F6Host
{
public:
	void rva002783F6(int v);
private:
	unsigned char m_padFC[0xFC];
	Rva002783F6Mid *m_FC;
	unsigned char m_pad447[0x447 - 0x100];
	unsigned char m_447;
	unsigned char m_448;
	unsigned char m_449;
	unsigned char m_44A;
};
// ?rva002783F6@Rva002783F6Host@@QAEXH@Z
void Rva002783F6Host::rva002783F6(int v)
{
	if (m_447 == 0 || m_448 == 0 || m_44A == 0)
		return;
	((Rva002743D7Host *)this)->rva002743D7();
	int w = 0;
	Rva002783F6Mid *p = m_FC;
	if (p != 0)
		w = p->m_254obj->v20();
	((Rva00278341Host *)this)->rva00278341(w, v);
}
