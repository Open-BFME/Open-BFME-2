// cl: /DNDEBUG /MD /EHsc
//
// ?Rva0018037B@Gen_dtor_00970f60@@UAEPAXXZ, retail 0x0018037B, 38 bytes. Virtual
// slot 15 (offset 0x3C) of vtable 0x007D4F90 (class of ??1Gen_dtor_00970f60@@UAE@XZ).
// Evidence: dtor at 0x0018021C stores vtable 0x7D4F90 and holds m_ptr at +0x14
// with StringClass m_name at +0x18; slot 13 at 0x0018026E returns 'MESH'
// (0x4D455348); slot 14 at 0x0018036C forwards m_ptr to Mesh ram-size
// 0x00149F20; slots 10/11 shared with vtables 0x7D37EC/0x7D4F10/0x7D5010/0x7D5090.
// Body calls slot10, on false calls slot11, returns NULL when m_ptr is null,
// else tail-calls Held slot2. Honest address name since slot-to-method mapping
// is unproven.

class Gen_dtor_00970f60Held
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void *slot08();
	int m_refs;
};

class Gen_dtor_00970f60
{
public:
	virtual void _slot000();
	virtual void _slot001();
	virtual void _slot002();
	virtual void _slot003();
	virtual void _slot004();
	virtual void _slot005();
	virtual void _slot006();
	virtual void _slot007();
	virtual void _slot008();
	virtual void _slot009();
	virtual bool _slot010();
	virtual void _slot011();
	virtual void _slot012();
	virtual void _slot013();
	virtual void _slot014();
	virtual void *Rva0018037B();
private:
	char m_pad[0x10];
	Gen_dtor_00970f60Held *m_ptr;
};

void *Gen_dtor_00970f60::Rva0018037B()
{
	if (!_slot010())
		_slot011();
	if (!m_ptr)
		return 0;
	return m_ptr->slot08();
}
