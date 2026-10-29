// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <string.h>

struct Rva00151E4DElement {Rva00151E4DElement();Rva00151E4DElement(const Rva00151E4DElement&);Rva00151E4DElement&operator=(const Rva00151E4DElement&);~Rva00151E4DElement(){}char bytes[36]; bool operator==(const Rva00151E4DElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva00151E4DElement * _STL::__copy<Rva00151E4DElement *, Rva00151E4DElement *, int>(Rva00151E4DElement *, Rva00151E4DElement *, Rva00151E4DElement *, _STL::random_access_iterator_tag const &, int *);

// ICF twin of ??4BfmeAssignRecord36@@QAEAAU0@ABU0@@Z (0x00151336, BfmeAssignRecord36Assign.cpp):
// the same 36-byte record assignment, so the copy loop above binds a definition.

template <typename T>
class StringBase
{
public:
	void set(const T *str);
	const T *str() const { return m_data ? &m_data->data[0] : (const T *)""; }

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};
	Header *m_data;
};

class Rva00151288
{
public:
	void rva00151288(const char *path);

private:
	char m_pad00[8];
	StringBase<char> m_str08;
};

struct Rva00151E4DView
{
	StringBase<char> m_name;
	int m_type;
	StringBase<char> m_s08;
	char m_0c[16];
	int m_intValue;
	unsigned char m_boolValue;
	char m_pad21[3];
};

Rva00151E4DElement &Rva00151E4DElement::operator=(const Rva00151E4DElement &other)
{
	Rva00151E4DView *self = (Rva00151E4DView *)this;
	const Rva00151E4DView &rhs = *(const Rva00151E4DView *)&other;
	self->m_name.set(rhs.m_name.str());
	self->m_type = rhs.m_type;
	((Rva00151288 *)this)->rva00151288(rhs.m_s08.str());
	memcpy(self->m_0c, rhs.m_0c, 16);
	memcpy(&self->m_intValue, &rhs.m_intValue, 4);
	memcpy(&self->m_boolValue, &rhs.m_boolValue, 1);
	return *this;
}
