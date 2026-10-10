// cl: /MD /EHsc
// ??1Rva005D1210@@QAE@XZ retail 0x005D1210 61B
// Pointee dtor run by the rowed owning-pointer reset 0x005D127C. Body (EH
// state 0): delete the object at +4 through the rowed safe-delete helper
// ?Rva005EC135Delete 0x005EC135 when set; then the +8 member's inline dtor
// calls the rowed ?clear@Rva000AD6F4 0x000AD6F4. Names address-derived.

void Rva005EC135Delete(void **slot);

class Rva000AD6F4
{
public:
	~Rva000AD6F4();
	void clear();

private:
	int m_ptr;
};

class Rva005D1210
{
public:
	~Rva005D1210();

private:
	int m_00;
	void *m_object; // +0x04
	Rva000AD6F4 m_08; // +0x08
};

Rva005D1210::~Rva005D1210()
{
	if (m_object != 0)
		Rva005EC135Delete(&m_object);
}
