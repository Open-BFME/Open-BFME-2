// ??0W3DDisplay@@QAE@XZ
// partial score=0.97 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?0W3DDisplay@@QAE@XZ, retail 0x00049DEA, 293 bytes.
// W3DDisplay constructor (ZH W3DDisplay::W3DDisplay twin). Identity: stores vtable 0x7C3C80 whose
// init is the W3DDisplay::init at 0x00046A50 (same +0x144 initialized byte, +0x148/+0x158 light
// arrays, +0x168 Render2D, +0x27C debug display and the three scene globals it fills), and zeroes
// those globals. Base constructor 0x0025D489 is the Display ctor (see W3DDisplayRva0025D2F6.cpp).
// Layout beyond the stores below is unmeasured and left as padding.

namespace _STL
{
template <class T> class allocator { public: allocator() {} };
template <class T, class A> class _Vector_base
{
public:
	_Vector_base(const A &a);
	~_Vector_base();
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};
template <class T, class A = allocator<T> > class vector : public _Vector_base<T, A>
{
public:
	vector(const A &a = A()) : _Vector_base<T, A>(a) {}
};
}

class Rva00043511
{
public:
	void rva00043511() throw();
	Rva00043511 *rva00045984();
	Rva00043511() { rva00045984(); }
	char data[0x24];
};

class Rva0065CA4
{
public:
	Rva0065CA4();
	virtual ~Rva0065CA4();
	char data[0x14];
};

struct GlobalDataView
{
	char pad00[0x28];
	int value28;
};

class Display
{
public:
	Display();
	virtual ~Display();
	virtual void slot04();
	char data[0x13c];
	char pad140[4];
};

class W3DDisplay : public Display
{
public:
	W3DDisplay();
	bool m_initialized;
	char pad145[3];
	void *m_lightA[4];
	void *m_lightB[4];
	void *m_2DRender;
	int m_16c;
	int m_170;
	int m_174;
	int m_178;
	bool m_17c;
	char pad17d[3];
	float m_180;
	int m_184;
	int m_188;
	int m_arr18c[16];
	int m_1cc;
	int m_arr1d0[25];
	int m_arr234[17];
	int m_278;
	int m_27c;
	Rva00043511 m_280;
	_STL::vector<int> m_2a4;
};

extern GlobalDataView *TheWritableGlobalData;
extern void *TheScene3D;
extern void *TheScene3DInterface;
extern void *TheScene2D;
extern Rva0065CA4 *TheRva0065CA4List;

W3DDisplay::W3DDisplay()
{
	m_184 = 0;
	m_188 = 0;
	m_initialized = false;
	TheScene3D = 0;
	TheScene3DInterface = 0;
	TheScene2D = 0;
	m_180 = (float)TheWritableGlobalData->value28;
	for (int i = 0; i < 4; i++)
	{
		m_lightA[i] = 0;
		m_lightB[i] = 0;
	}
	m_2DRender = 0;
	m_17c = false;
	m_16c = 0;
	m_170 = 0;
	m_174 = 0;
	m_178 = 0;
	for (int i = 0; i < 16; i++)
		m_arr18c[i] = 0;
	for (int i = 0; i < 25; i++)
		m_arr1d0[i] = 0;
	for (int i = 0; i < 17; i++)
		m_arr234[i] = 0;
	m_1cc = 0;
	m_278 = 0;
	m_27c = 0;
	TheRva0065CA4List = new Rva0065CA4;
	m_280.rva00043511();
}
