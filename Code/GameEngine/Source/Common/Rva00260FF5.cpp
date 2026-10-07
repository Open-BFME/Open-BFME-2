// cl: /O1 /DNDEBUG /MD /EHsc
// ??0Rva00260FF5@@QAE@PAVObject@@@Z, retail 0x00260FF5, 81 bytes.
// Target evidence: initializes +4 and +8, installs vftable VA 0x00BF8FD8,
// then follows Object+0x254 and calls virtual slot 15, copying result+8.
// Donor evidence: BFME1 Rva001DCAF0FilterCtor uses the same slot-15 record
// lookup shape; target evidence for the +0x254 body and its slot 15 is in
// ObjectRva0028C264.cpp. The class and the value's meaning remain address-derived.
struct Rva00260FF5Result
{
	char m_unmodelled_00[8];
	void *m_value;
};

extern const void *const g_00BF8FD8[];

class Rva00260FF5Module
{
public:
#define BFME_VIRTUAL_SLOT(n) virtual void _v##n(void) = 0
	BFME_VIRTUAL_SLOT(00); BFME_VIRTUAL_SLOT(01); BFME_VIRTUAL_SLOT(02); BFME_VIRTUAL_SLOT(03);
	BFME_VIRTUAL_SLOT(04); BFME_VIRTUAL_SLOT(05); BFME_VIRTUAL_SLOT(06); BFME_VIRTUAL_SLOT(07);
	BFME_VIRTUAL_SLOT(08); BFME_VIRTUAL_SLOT(09); BFME_VIRTUAL_SLOT(10); BFME_VIRTUAL_SLOT(11);
	BFME_VIRTUAL_SLOT(12); BFME_VIRTUAL_SLOT(13); BFME_VIRTUAL_SLOT(14);
#undef BFME_VIRTUAL_SLOT
	virtual Rva00260FF5Result *slot15() = 0;
};

class Object
{
public:
	char m_unmodelled_00[0x254];
	Rva00260FF5Module *m_body254;
};

class Rva00260FF5Base
{
public:
	Rva00260FF5Base() : m_unmodelled_04(0) {}
	~Rva00260FF5Base();

protected:
	const void *const *m_vftable;
	unsigned int m_unmodelled_04;
};

class Rva00260FF5 : public Rva00260FF5Base
{
public:
	Rva00260FF5(Object *object);

private:
	void *m_value;
};

Rva00260FF5::Rva00260FF5(Object *object) : Rva00260FF5Base()
{
	m_vftable = g_00BF8FD8;
	Rva00260FF5Module *body = 0;
	if (object != 0)
		body = object->m_body254;
	if (body != 0)
		m_value = body->slot15()->m_value;
	else
		m_value = 0;
}
