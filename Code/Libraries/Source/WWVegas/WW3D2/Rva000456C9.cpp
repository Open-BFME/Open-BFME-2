// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Texture-holder setter at 0x000456C9 (39B): reassigns the RefCountPtr at
// +0x40 through the rowed 0x000424D0 operator= when the referent changes,
// then records -(ptr != 0) at +0x44. W3DDisplay vtable 0x00BC3C80 slot 31
// at 0x00046734 (93B) clears the +0x168 Render2DClass texture via a temporary
// RefCountPtr<TextureClass>(0), calls Render2DClass::Reset (0x00119F00), and
// iterates the +0x2A4..+0x2A8 array calling slot 11 (+0x2C); defining
// rva000456C9 and RefCountPtr::operator= in the same unit lets MSVC prove the
// temporary's Referent stays null across 0x000456C9 and elide the normal-path
// release while keeping the 0x0075CFEB unwind funclet (to 0x0017098D).
class TextureBaseClass
{
public:
	void Add_Ref() { ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4); }
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
};

template<class T>
class RefCountPtr
{
public:
	RefCountPtr(T *p = 0) : Referent(p) {}
	~RefCountPtr()
	{
		if (Referent != 0)
			Referent->Release_Ref();
	}
	RefCountPtr const &operator=(RefCountPtr const &other)
	{
		if (other.Referent != 0)
			other.Referent->Add_Ref();
		if (Referent != 0)
			Referent->Release_Ref();
		Referent = other.Referent;
		return *this;
	}
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

class Render2DClass
{
public:
	void Reset();
};

class Rva00046791Item
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10();
	virtual void rva00046779Slot();
	virtual void rva000467A5Slot();
};

class W3DDisplay
{
public:
	void rva00046734();
private:
	char m_pad00[0x168];
	Rva000456C9 *m_168;
	char m_pad16C[0x2a4 - 0x16c];
	Rva00046791Item **m_2a4;
	Rva00046791Item **m_2a8;
};

void W3DDisplay::rva00046734()
{
	m_168->rva000456C9(&RefCountPtr<TextureClass>(0));
	((Render2DClass *)m_168)->Reset();
	for (Rva00046791Item **it = m_2a4; it != m_2a8; ++it)
		(*it)->rva00046779Slot();
}
