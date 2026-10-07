// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// @0x000C3886 114B. If the object is live and bit 0x10 at +0xF4 is clear,
// walk the pointer range and mark the bit, then always forward to the
// three rowed callees.

int Rva000B2CBDGet();

struct Rva000C3886Range
{
	int *m_begin;
	int *m_end;
};

class Rva000C3886;

struct Rva000C3886Obj
{
	void rva000BE775(Rva000C3886 *owner);

	char m_pad[0xF4];
	unsigned char m_flags;
};

class Rva000C3886
{
public:
	void rva000C2AA4(int *element);
	void rva000BE245(void *first, float value, Rva000C3886Obj *obj, void *last);
	void rva000BBE86(Rva000C3886Obj *obj);
	void rva000C3886(void *first, float value, Rva000C3886Range *range,
		Rva000C3886Obj *obj, void *last);
};

void Rva000C3886::rva000C3886(void *first, float value, Rva000C3886Range *range,
	Rva000C3886Obj *obj, void *last)
{
	if (obj == 0)
		return;
	if ((obj->m_flags & 0x10) == 0 && (unsigned char)Rva000B2CBDGet() != 0)
	{
		for (int *cursor = range->m_begin; cursor != range->m_end; ++cursor)
			rva000C2AA4(cursor);
		obj->m_flags |= 0x10;
	}
	rva000BE245(first, value, obj, last);
	rva000BBE86(obj);
	obj->rva000BE775(this);
}
