// cl: /GX- /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes), batch V. As in VslotSmallBodiesA-U, each class and
// method is address-derived unless the ledger already names it, and models
// only what its body touches. Meanings are not recovered.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

// 0x000FBA0F (tables from VA 0x00BCF36C on): clears the flag out, starts the
// pinned W3DShaderManager render-to-texture and answers true.
class W3DShaderManager
{
public:
	static void startRenderToTexture();
};
class Rva000FBA0F
{
public:
	bool rva000FBA0F(bool *out, Int unused);
};
bool Rva000FBA0F::rva000FBA0F(bool *out, Int)
{
	*out = false;
	W3DShaderManager::startRenderToTexture();
	return true;
}

// 0x00131CA5 and 0x00131D54 (texture tables beside 0x00131CDB): a new
// 0x58-byte surface (rowed constructor 0x0013107A) at +0x14, then either the
// +0x30/+0x34 words into its +0x44/+0x4C or the rowed loader 0x00131259 with
// the +0x3C name.
class Rva00131259
{
public:
	virtual ~Rva00131259();
	void rva00131259(const char *name);
};
class Rva0013107A : public Rva00131259
{
public:
	Rva0013107A();
	char m_pad04[0x40];
	Int m_44;
	Int m_48;
	Int m_4C;
	char m_pad50[0x08];
};
//
// Names: WorldBuilder's texture.cpp defines these three as the PreLoad of
// TextureAsset's nested factories (Factory :1031, MissingFactory :1041,
// RecolorFactoryDecal :1115), each asserting m_impl (+0x14) is NULL before
// creating the impl; retail keeps them in that order (0x00131C63, 0x00131CA5,
// 0x00131D54) and RecolorFactoryDecal's sits in its factory vftable.
class TextureAsset
{
public:
	class Factory;
	class MissingFactory
	{
	public:
		void PreLoad();
	private:
		char m_pad00[0x14];
		Rva0013107A *m_impl;
		char m_pad18[0x18];
		Int m_30;
		Int m_34;
	};
	class RecolorFactoryDecal
	{
	public:
		void PreLoad();
	private:
		char m_pad00[0x14];
		Rva0013107A *m_impl;
		char m_pad18[0x24];
		const char *m_3C;
	};
};
void TextureAsset::MissingFactory::PreLoad()
{
	m_impl = new Rva0013107A;
	m_impl->m_44 = m_30;
	m_impl->m_4C = m_34;
}
void TextureAsset::RecolorFactoryDecal::PreLoad()
{
	m_impl = new Rva0013107A;
	m_impl->rva00131259(m_3C);
}

// 0x001E30F5: unless +0x14C is set, looks up the +0x154 key in the registry
// at VA 0x00DFF000 and forwards both arguments to the pinned notify.
struct Rva0020AA00Target
{
	void notify(Int a, Int b);
};
class Rva0020AA00Registry
{
public:
	Rva0020AA00Target *lookup(const Int &key);
};
extern class ThingFactory *TheThingFactory;
class Rva001E30F5
{
public:
	void rva001E30F5(Int a, Int b);
private:
	char m_pad00[0x14C];
	bool m_14C;
	char m_pad14D[0x07];
	Int m_154;
};
void Rva001E30F5::rva001E30F5(Int a, Int b)
{
	if (!m_14C)
	{
		Rva0020AA00Target *t = (*(Rva0020AA00Registry **)&TheThingFactory)->lookup(m_154);
		if (t)
			t->notify(a, b);
	}
}

// An STLport-shaped vector view.
template <class T>
struct Rva0020EB07Vector
{
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
	Int size() const { return _M_finish - _M_start; }
	T &operator[](UnsignedInt i) { return _M_start[i]; }
};

// 0x0020EB07: the rowed 0x003F1044 with both arguments on every pointer of
// the vector at +0x2C of the +0x04 object.
class Rva003F055A
{
public:
	void rva003F1044(Int a, Int b);
};
struct Rva0020EB07Info
{
	char m_pad00[0x2C];
	Rva0020EB07Vector<Rva003F055A *> m_2C;
};
class Rva0020EB07
{
public:
	void rva0020EB07(Int a, Int b);
private:
	Int m_00;
	Rva0020EB07Info *m_04;
};
void Rva0020EB07::rva0020EB07(Int a, Int b)
{
	Rva0020EB07Vector<Rva003F055A *> &v = m_04->m_2C;
	for (UnsignedInt i = 0; i < (UnsignedInt)v.size(); i++)
		v[i]->rva003F1044(a, b);
}

// 0x00235736: destroys the chain from the head at VA 0x00DFE758 up to the
// end marker at VA 0x00DFE75C (next link at +0x1250) with global delete.
class Rva00235736Node
{
public:
	virtual ~Rva00235736Node();
	char m_pad04[0x124C];
	Rva00235736Node *m_next;
};
extern class GlobalData *TheWritableGlobalData;
extern Rva00235736Node *g_rva00235736End;
class Rva00235736
{
public:
	void rva00235736();
};
void Rva00235736::rva00235736()
{
	while ((*(Rva00235736Node **)&TheWritableGlobalData) != g_rva00235736End)
	{
		Rva00235736Node *next = (*(Rva00235736Node **)&TheWritableGlobalData)->m_next;
		::delete (*(Rva00235736Node **)&TheWritableGlobalData);
		(*(Rva00235736Node **)&TheWritableGlobalData) = next;
	}
}

// 0x002616D1 and 0x002616EB (tables at VA 0x00C1796C, 0x00C071D0): the rowed dual-mask
// test 0x0026157E of the argument's +0x94 masks against this object's
// +0x08/+0x18, resp. its negation.
class Rva0026157E
{
public:
	bool testMasks(const void *a, const void *b) const;
};
struct Rva002616D1Arg
{
	char m_pad00[0x94];
	Rva0026157E m_94;
};
class Rva002616D1
{
public:
	bool rva002616D1(const Rva002616D1Arg *arg) const;
	Int rva002616EB(const Rva002616D1Arg *arg) const;
private:
	char m_pad00[0x08];
	char m_08[0x10];
	char m_18[0x10];
};
bool Rva002616D1::rva002616D1(const Rva002616D1Arg *arg) const
{
	return arg->m_94.testMasks(m_08, m_18);
}
Int Rva002616D1::rva002616EB(const Rva002616D1Arg *arg) const
{
	return !arg->m_94.testMasks(m_08, m_18);
}

// 0x00131C63 (texture tables beside 0x00131CA5): a new 0x58-byte surface at
// +0x14 taking the +0x30/+0x34/+0x38 words, then the rowed loader 0x00131259
// with the +0x18 name.
class TextureAsset::Factory
{
public:
	void PreLoad();
private:
	char m_pad00[0x14];
	Rva0013107A *m_impl;
	const char *m_18;
	char m_pad1C[0x14];
	Int m_30;
	Int m_34;
	Int m_38;
};
void TextureAsset::Factory::PreLoad()
{
	m_impl = new Rva0013107A;
	m_impl->m_44 = m_30;
	m_impl->m_4C = m_34;
	m_impl->m_48 = m_38;
	m_impl->rva00131259(m_18);
}

// 0x00105FE4 and 0x00106036: the rowed 0x00154320 (resp. 0x00154370) with
// both Reals on the +0xD8 and +0x14 members, each success setting +0x1A2.
class Rva00154320
{
public:
	bool rva00154320(Real a, Real b);
};
class Rva00154370
{
public:
	bool rva00154370(Real a, Real b);
};
class Rva00105FE4
{
public:
	void rva00105FE4(Real a, Real b);
private:
	char m_pad00[0x14];
	Rva00154320 m_14;
	char m_pad15[0xC3];
	Rva00154320 m_D8;
	char m_padD9[0xC9];
	bool m_1A2;
};
void Rva00105FE4::rva00105FE4(Real a, Real b)
{
	if (m_D8.rva00154320(a, b))
		m_1A2 = true;
	if (m_14.rva00154320(a, b))
		m_1A2 = true;
}
class Rva00106036
{
public:
	void rva00106036(Real a, Real b);
private:
	char m_pad00[0x14];
	Rva00154370 m_14;
	char m_pad15[0xC3];
	Rva00154370 m_D8;
	char m_padD9[0xC9];
	bool m_1A2;
};
void Rva00106036::rva00106036(Real a, Real b)
{
	if (m_D8.rva00154370(a, b))
		m_1A2 = true;
	if (m_14.rva00154370(a, b))
		m_1A2 = true;
}
