// cl: /MD
// ?rva0028CBFD@Rva0028CBFD@@QAEXXZ @0x0028CBFD 127B.
// Three null-terminated array walks calling virtual slot 0xC/0x40/0x38 then slot 4 on result.
// Evidence: 12 callers including 0x002B0DBA 0x00455B17; prev 0x0028CBE1 adjacent; offsets +0x244 +0x84 +0x154 +0x150.
class Holder0028CBFD
{
public:
	virtual void *s00();
	virtual void *s01();
	virtual void *s02();
	virtual void *s03();
	virtual void *s04();
	virtual void *s05();
	virtual void *s06();
	virtual void *s07();
	virtual void *s08();
	virtual void *s09();
	virtual void *s10();
	virtual void *s11();
	virtual void *s12();
	virtual void *s13();
	virtual void *s14();
	virtual void *s15();
	virtual void *s16();
};

class Inner0028CBFD
{
public:
	char m_pad[0x150];
	void **m_150;
	void **m_154;
};

class Rva0028CBFD
{
public:
	void rva0028CBFD();
private:
	char m_pad[0x84];
	Inner0028CBFD *m_84;
	char m_pad84[0x244 - 0x88];
	void **m_244;
};

void Rva0028CBFD::rva0028CBFD()
{
	for (void **p = m_244; *p != 0; ++p)
	{
		Holder0028CBFD *h = (Holder0028CBFD *)((char *)*p + 0xC);
		void *q = h->s03();
		if (q != 0)
			((Holder0028CBFD *)q)->s01();
	}
	Inner0028CBFD *inner = m_84;
	if (inner != 0)
	{
		if (inner->m_154 != 0)
		{
			for (void **p = inner->m_154; *p != 0; ++p)
			{
				Holder0028CBFD *h = (Holder0028CBFD *)*p;
				void *q = h->s16();
				if (q != 0)
					((Holder0028CBFD *)q)->s01();
			}
		}
		if (inner->m_150 != 0)
		{
			for (void **p = inner->m_150; *p != 0; ++p)
			{
				Holder0028CBFD *h = (Holder0028CBFD *)*p;
				void *q = h->s14();
				if (q != 0)
					((Holder0028CBFD *)q)->s01();
			}
		}
	}
}

// ?rva0028FC18@Object@@QAEXXZ @0x0028FC18 5B: a forwarder that runs the walk
// above on the same object (tail jmp to 0x0028CBFD, `this` unchanged); the
// script actions' object creation calls it after placing the new object.
class Object
{
public:
	void rva0028FC18();
};

void Object::rva0028FC18()
{
	((Rva0028CBFD *)this)->rva0028CBFD();
}
