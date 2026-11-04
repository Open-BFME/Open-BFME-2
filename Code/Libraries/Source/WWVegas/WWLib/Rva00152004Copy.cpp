// cl: /MD
// STLport counted copy for the eight-byte texture-reference record.
// The range dispatcher supplies the category and distance arguments.

class TextureClass;
typedef const char *D3DXHANDLE;

template <class T>
class RefCountPtr
{
public:
	RefCountPtr const &operator=(RefCountPtr const &other);
private:
	T *Referent;
};

class Rva00151DAB
{
public:
	Rva00151DAB &operator=(Rva00151DAB const &rhs);
	D3DXHANDLE m_parameter;			// +0
	RefCountPtr<TextureClass> m_texture;	// +4
};

namespace _STL
{
struct random_access_iterator_tag;
template <class Input, class Output, class Distance>
Output __copy(Input, Input, Output, const random_access_iterator_tag &, Distance *);
}

template <>
Rva00151DAB *_STL::__copy<Rva00151DAB *, Rva00151DAB *, int>(
    Rva00151DAB *first, Rva00151DAB *last, Rva00151DAB *dest,
    const _STL::random_access_iterator_tag &, int *)
{
	int n = (int)(last - first);
	if (n <= 0)
		return dest;
	for (; n > 0; --n, ++first, ++dest)
		*dest = *first;
	return dest;
}
