// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??1Rva005ECA91@@MAE@XZ @ 0x005ECAD0 (60B): vtable store then two member dtors.
// Evidence: vtable 0x008785B0 at [this]; member +0x10 dtor 0x005242D7; member +0x4 dtor 0x005EC9BA;
// EH prolog with handler 0x007A4611; unblocks 0x005ECFE4 0x005ED152 0x005ECB0C; callers include Unwind funclets.
class Rva005242D7
{
	void *m_s0;
	void *m_s4;
	void *m_s8;
public:
	~Rva005242D7();
};

class Rva005EC9BA
{
	void *m_s0;
	void *m_s4;
	void *m_s8;
public:
	~Rva005EC9BA();
};

class Rva005ECA91
{
	Rva005EC9BA m_vec04;
	Rva005242D7 m_ocl10;
protected:
	virtual ~Rva005ECA91();
};

Rva005ECA91::~Rva005ECA91()
{
}
