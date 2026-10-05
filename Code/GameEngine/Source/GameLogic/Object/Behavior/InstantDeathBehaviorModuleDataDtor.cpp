// cl: /O1 /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1InstantDeathBehaviorModuleData@@UAE@XZ @0x0045D28D 105B via 3 inline vector frees plus rowed vector dtor, novtable restores g_00BBB554
#include <vector>

extern const void *const g_00BBB554[];

class Rva00253510
{
public:
	virtual ~Rva00253510() { *(const void **)this = g_00BBB554; }
	virtual void Rva00253510_virt00();
private:
	unsigned char m_pad[0x38 - 4];
};

struct Rva0045D137
{
	void *m_start;
	void *m_finish;
	void *m_endOfStorage;
	~Rva0045D137();
};

class __declspec(novtable) InstantDeathBehaviorModuleData : public Rva00253510
{
public:
	virtual ~InstantDeathBehaviorModuleData();
private:
	_STL::vector<int> m_v38;
	_STL::vector<int> m_v44;
	_STL::vector<int> m_v50;
	Rva0045D137 m_v5C;
};

InstantDeathBehaviorModuleData::~InstantDeathBehaviorModuleData()
{
}
