// cl: /DNDEBUG /MD
// ?rva005748B7@Rva005748B7@@QAEXPAURva002BED91@@@Z retail 0x005748B7 59B.
// Evidence: callers at 0x005749AF 0x00574A82 0x00574D2F 0x00574D4F; callees rowed get 0x0042D6B4 clear 0x002BED91 forwarder 0x005CB260 plus pin ?rva005CB265@Rva005CB265@@UAEHXZ at 0x005CB265.
class Rva0042D6B4PtrChaseField
{
public:
	int get() const;
};
class Rva005CB265
{
public:
	virtual int rva005CB265();
};
class Rva005CB260
{
public:
	void rva005CB260();
};
struct Rva002BED91
{
	void clear();
	void *m_ptr;
};
class Rva005748B7
{
public:
	void rva005748B7(Rva002BED91 *arg);
private:
	char m_pad[0x20];
	Rva0042D6B4PtrChaseField *m_field;
};
void Rva005748B7::rva005748B7(Rva002BED91 *arg)
{
	if (!arg->m_ptr)
		return;
	int v = m_field->get();
	if (!v)
	{
		arg->clear();
		return;
	}
	void *b = arg->m_ptr;
	Rva005CB265 *q = (Rva005CB265 *)v;
	int r = q->Rva005CB265::rva005CB265();
	if (r != (int)b)
	{
		arg->clear();
		return;
	}
	((Rva005CB260 *)q)->rva005CB260();
	arg->clear();
}
