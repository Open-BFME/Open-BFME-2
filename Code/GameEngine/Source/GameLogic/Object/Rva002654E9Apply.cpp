// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva002654E9@Rva002654E9@@QAEXXZ @ 0x002654E9 (19B)
// Applies a stored Object status with false: when the stored Object is
// non-null, forwards the stored status and false to rowed Object::setStatus
// 0x0023DB0E. Evidence: reached via its stored address with a caller jmp at
// 0x0026893A; body abuts the next row 0x002654FC in this directory.
enum ObjectStatusTypes;

class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool flag);
};

class Rva002654E9
{
public:
	void rva002654E9();
private:
	Object *m_object;
	int m_status;
};

// ?rva002654E9@Rva002654E9@@QAEXXZ @0x002654E9
void Rva002654E9::rva002654E9()
{
	if (m_object)
		m_object->setStatus((ObjectStatusTypes)m_status, false);
}
