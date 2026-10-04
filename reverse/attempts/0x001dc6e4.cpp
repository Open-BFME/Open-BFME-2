// ??1AudioManager@@UAE@XZ
// partial score=0.98 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ??0AudioManager@@QAE@XZ @0x001DCBC3 124B evidence: caller 0x002C0A30 stores result to TheAudio AudioManager; vtable g_00BDBC30; base SubsystemInterface 0x001B4E63; members Rva001DCBA4 +0x0C list<int> +0x20
#include <hash_map>
#include <list>
#include <cstddef>

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

namespace rts
{

template <typename T> struct hash
{
	size_t operator()(const T &value) const;
};

template <typename T> struct equal_to
{
	bool operator()(const T &a, const T &b) const;
};

}

class ArmorTemplate
{
public:
	float m_damageCoefficient[38];
};

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;

// The +0x0C table's dtor is the copy at 0x001DC636 (the _STL::equal_to
// instantiation), which the dtor below calls; 0x0060CC99 is the rts one.
typedef _STL::hashtable<
	ArmorTemplateMap::value_type,
	NameKeyType,
	rts::hash<NameKeyType>,
	_STL::_Select1st<ArmorTemplateMap::value_type>,
	_STL::equal_to<NameKeyType>,
	_STL::allocator<ArmorTemplateMap::value_type> > ArmorHashtable;

class Rva001DCBA4
{
public:
	Rva001DCBA4();
private:
	ArmorHashtable m_table;
};

extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void *cs);

// TransitionGroup (0x14 bytes): its rowed dtor 0x001DC0EC and the rowed
// list walk rva001DBE17.
class Rva001DC0EC
{
public:
	~Rva001DC0EC();
};
class Rva001DBDA4
{
public:
	void rva001DBE17();
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	unsigned char m_bfme04[8];
};

class AudioManager : public SubsystemInterface
{
public:
	AudioManager();
	virtual ~AudioManager();
	void init() { }
	void reset() { }
	void update() { }

private:
	Rva001DCBA4 m_unk0C;
	std::list<int> m_list0x20;
	int m_unk24;
	int m_unk28;
	int m_unk2C;
	int m_unk30;
	int m_unk34;
	char m_pad38[0x50 - 0x38];
	unsigned char m_unk50;
	unsigned char m_unk51;
	char m_pad52[0x64 - 0x52];
	int m_unk64;
	unsigned char m_unk68;
	unsigned char m_unk69;
	char m_pad6A[0x6C - 0x6A];
};

AudioManager::AudioManager()
{
	m_unk24 = 0;
	m_unk28 = 0;
	m_unk2C = 0;
	m_unk30 = 0;
	m_unk64 = 0x21;
	m_unk69 = 0;
	m_unk68 = 0;
	m_unk50 = 0;
	m_unk51 = 0;
	m_unk34 = 0;
	m_list0x20.clear();
}

// ??1AudioManager@@UAE@XZ @0x001DC6E4 225B (pinned; ??_G 0x001DC7C5 above
// calls it). The body is Zero Hour's ~GameWindowTransitionsHandler: this
// class is the transitions handler (group list at +0x20, current/pending/
// draw/secondary groups at +0x24..+0x30, its INI parser 0x001DC66F reads
// the same 0x00DFDC14 singleton). BFME 2 additions from the target: each
// group pointer gets the rowed rva001DBE17 and is cleared, and the critical
// section at +0x38 is deleted when its +0x50 flag is set; then every group
// is deleted (rowed dtor 0x001DC0EC) and erased (STLport erase 0x00838539).
AudioManager::~AudioManager()
{
	if( m_unk24 )
	{
		((Rva001DBDA4 *)m_unk24)->rva001DBE17();
		m_unk24 = 0;
	}
	if( m_unk28 )
	{
		((Rva001DBDA4 *)m_unk28)->rva001DBE17();
		m_unk28 = 0;
	}
	if( m_unk2C )
	{
		((Rva001DBDA4 *)m_unk2C)->rva001DBE17();
		m_unk2C = 0;
	}
	if( m_unk30 )
	{
		((Rva001DBDA4 *)m_unk30)->rva001DBE17();
		m_unk30 = 0;
	}
	if( m_unk50 )
	{
		DeleteCriticalSection( m_pad38 );
		m_unk50 = 0;
	}

	std::list<int>::iterator it = m_list0x20.begin();
	while( it != m_list0x20.end() )
	{
		Rva001DC0EC *g = (Rva001DC0EC *)*it;
		delete g;
		it = m_list0x20.erase( it );
	}
}
