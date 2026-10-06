// cl: /MD
// ?rva002CEC34@Rva002CEC0A@@QAEXXZ @0x002CEC34 14B
// Clears the vector<AsciiString> at +4 via the rowed erase at 0x0002CCFC.
// Same class and member as Rva002CEC0ADtor (dtor at 0x002CEC0A tail-calls
// the vector dtor; this method erases begin/end). Callers at 0x002297EB
// 0x002458F2 0x002CED4F prove a thiscall void method; honest address name.
class AsciiString;

namespace _STL
{
template <class T> class allocator
{
};

template <class T, typename A = allocator<T> > class vector
{
public:
	typedef T *iterator;
	iterator erase(iterator first, iterator last);

	T *m_start;
	T *m_finish;
	T *m_end;
};
}

class Rva002CEC0A
{
public:
	void rva002CEC34();
	void rva002CED26(class Xfer *xfer);

private:
	int m_00;
	_STL::vector<AsciiString> m_04;
};

void Rva002CEC0A::rva002CEC34()
{
	_STL::vector<AsciiString> *v = &m_04;
	v->erase(v->m_start, v->m_finish);
}

class Xfer
{
public:
	virtual ~Xfer();
	virtual bool isLoading();
	virtual bool isSaving();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05(const char *name);
	virtual void slot06();
};

Xfer *xferAsciiStringVector(Xfer *xfer, _STL::vector<AsciiString> *vec);

void Rva002CEC0A::rva002CED26(Xfer *xfer)
{
	xfer->slot05("CRCParameterCheck");
	xferAsciiStringVector(xfer, &m_04);
	xfer->slot06();
	rva002CEC34();
}
