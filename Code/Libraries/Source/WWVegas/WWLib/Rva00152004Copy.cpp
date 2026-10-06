// cl: /MD
// ?Rva00152004Copy@@YAPAVRva00151E30@@PAV1@00@Z at 0x00152004 (47B).
// Array copy for 8-byte Rva00151E30 via its rowed operator= 0x151E30.
// Evidence: sar 3 count, single caller 0x52091, unblocks 0x5207E.

class TextureClass;

template <class T>
class RefCountPtr
{
public:
	RefCountPtr const &operator=(RefCountPtr const &other);
private:
	T *Referent;
};

class Rva00151E30
{
public:
	Rva00151E30 &operator=(Rva00151E30 const &rhs);
private:
	int m_00;
	RefCountPtr<TextureClass> m_04;
};

Rva00151E30 *Rva00152004Copy(Rva00151E30 *first, Rva00151E30 *last, Rva00151E30 *dest);

Rva00151E30 *Rva00152004Copy(Rva00151E30 *first, Rva00151E30 *last, Rva00151E30 *dest)
{
	int n = (int)(last - first);
	if (n <= 0)
		return dest;
	for (; n > 0; --n, ++first, ++dest)
		*dest = *first;
	return dest;
}
