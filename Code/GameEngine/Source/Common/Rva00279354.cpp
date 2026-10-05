// cl: /O1 /MD
class Rva002743D7Host
{
public:
	void rva002743D7();
};
class Rva000A8C9BHost
{
public:
	void rva000A8C9B();
};
class Rva002783F6Host
{
public:
	void rva002783F6(int v);
};
struct OpaqueRefElement4
{
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};
class Rva00279354Host
{
public:
	void rva00279354(bool v);
	void rva00279797(const OpaqueRefElement4 &v);
private:
	unsigned char m_pad[0x10C];
	Rva000A8C9BHost m_10C;
};
// ?rva00279354@Rva00279354Host@@QAEX_N@Z
void Rva00279354Host::rva00279354(bool v)
{
	((Rva002743D7Host *)this)->rva002743D7();
	m_10C.rva000A8C9B();
	if (v != 0)
		((Rva002783F6Host *)this)->rva002783F6(0);
}
void Rva00279354Host::rva00279797(const OpaqueRefElement4 &v)
{
	rva00279354(false);
	*(OpaqueRefElement4 *)((char *)this + 0x10C) = v;
	((Rva002783F6Host *)this)->rva002783F6(0);
}
