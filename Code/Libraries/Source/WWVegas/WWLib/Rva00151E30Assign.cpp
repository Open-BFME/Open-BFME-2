// cl: /MD
// ??4Rva00151DAB@@QAEAAV0@ABV0@@Z at 0x00151E30 (29B).
// Copy assign: copy +0 dword then RefCountPtr<TextureClass> assign at +4.
// Evidence: RefCountPtr assign row 0x424D0, single caller 0x15201D,
// prev/next stlport record bodies.

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

Rva00151DAB &Rva00151DAB::operator=(Rva00151DAB const &rhs)
{
	m_parameter = rhs.m_parameter;
	m_texture = rhs.m_texture;
	return *this;
}
