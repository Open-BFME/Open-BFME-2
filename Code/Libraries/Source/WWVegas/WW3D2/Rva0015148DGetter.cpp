// cl: /DNDEBUG /MD
// ?rva0015148D@Rva0015148D@@QAEPAXXZ at 0x0015148D (37B).
// Ref-holder getter: null check, ensure via Is_Initialized/Slot_2C virtuals,
// then return inner pointer at +0x14+4. Evidence: slots 0x28/0x2c match
// TexObject Is_Initialized/Slot_2C pattern, 22 callers, unblocks 7.

#define NULL 0

class Inner14
{
public:
	char m_pad00[4];
	void *m_ptr04;
};

class TexLike
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual bool Is_Initialized() = 0;
	virtual void Ensure() = 0;
	char m_pad04[0x10];
	Inner14 *m_field14;
};

class Rva0015148D
{
public:
	void *rva0015148D();
private:
	TexLike *m_ptr;
};

void *Rva0015148D::rva0015148D()
{
	TexLike *obj = m_ptr;
	if (obj == NULL)
		return NULL;
	if (!obj->Is_Initialized())
		obj->Ensure();
	return obj->m_field14->m_ptr04;
}
