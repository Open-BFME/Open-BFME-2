// cl: /O1 /DNDEBUG /MD
// ?rva0004232F@Rva0004232FNullTarget@@QAEXXZ @0x0004232F 5B
// LINK target for VslotNullCheckedForwarders2 forwarder 0x005CCB23.
// Forwards to vtable slot 0x30 (v12). Same shape as in-file attempt which
// inlined into the forwarder and broke it, so it lives here alone.
class Rva0004232FNullTarget
{
public:
	virtual ~Rva0004232FNullTarget();
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
	void rva0004232F();
};

void Rva0004232FNullTarget::rva0004232F()
{
	return v12();
}
