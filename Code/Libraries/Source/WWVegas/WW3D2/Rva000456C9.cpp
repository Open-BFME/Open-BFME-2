// cl: /DNDEBUG /MD
// Texture-holder setter at 0x000456C9 (39B): reassigns the RefCountPtr at
// +0x40 through the rowed 0x000424D0 operator= when the referent changes,
// then records -(ptr != 0) at +0x44. The free-function operator!= (inlined,
// no row) plus /O1 is what orders the head as load-arg, lea, mem-cmp;
// /O2 keeps the referent in a register and emits reg-reg instead. The
// (p != 0) ? -1 : 0 ternary is what selects neg/sbb for the flag.
class TextureBaseClass
{
public:
	void Add_Ref();
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
};

template<class T>
class RefCountPtr
{
public:
	RefCountPtr const &operator=(RefCountPtr const &other);
	T *peek() const { return Referent; }
	T *Referent;
};

template<class T>
bool operator!=(RefCountPtr<T> const &a, RefCountPtr<T> const &b) { return a.Referent != b.Referent; }

class Rva000456C9
{
public:
	char m_pad[0x40];
	RefCountPtr<TextureClass> m_tex40;
	int m_44;
	void rva000456C9(RefCountPtr<TextureClass> const *arg);
};

void Rva000456C9::rva000456C9(RefCountPtr<TextureClass> const *arg)
{
	RefCountPtr<TextureClass> *t = &m_tex40;
	if (*arg != *t)
	{
		*t = *arg;
		TextureClass *p = t->peek();
		m_44 = (p != 0) ? -1 : 0;
	}
}
