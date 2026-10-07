// ??0AnimationSoundClientBehavior@@QAE@ABV0@@Z
// partial score=0.96 date=2026-10-07
// cl: /DNDEBUG /MD /EHsc
// ??0AnimationSoundClientBehavior@@QAE@ABV0@@Z, retail 0x004CA1C1, 98 bytes.
// Target evidence: FUN_008CA1C1 calls the rowed Rva004CA125 copy constructor,
// restores vtable addresses C5EE80/C5EE74 after that base call, copies +0x10,
// zeros the two links at +0x14/+0x18, and conditionally inserts into the
// global at VA 0x00E032D0 through rowed rva00432F7D at 0x00432F7D.
// Identity inference: the surrounding vtable xrefs, rowed regular constructor
// 0x004CA05A, and destructor 0x004C9DC9 support this as the class copy ctor.

extern "C" const void *const vtbl_00C6FFFC[];
#pragma comment(linker, "/alternatename:_vtbl_00C6FFFC=??_7?$CategoryModuleClass@$00@FXParticleSystem@@6B@")
extern "C" const void *const vtbl_00C5EE74[];
#pragma comment(linker, "/alternatename:_vtbl_00C5EE74=??_7AnimationSoundClientBehavior@@6BRva004C9E33Iface@@@")
extern "C" const void *const vtbl_00C5EE80[];
#pragma comment(linker, "/alternatename:_vtbl_00C5EE80=??_7AnimationSoundClientBehavior@@6BRva004C9DC9Primary@@@")

// This storage view preserves the rowed copy-ctor ABI and the 12-byte base
// extent. Its target vptr is set explicitly below after the base call.
class Rva004CA125
{
public:
	Rva004CA125(const Rva004CA125 &other);
	virtual ~Rva004CA125();

private:
	unsigned int m_field04;
	unsigned int m_field08;
};

class Rva00432F23Node
{
	char m_pad[0x14];
	Rva00432F23Node *m_next;
	Rva00432F23Node *m_prev;
};

class Rva00432F23
{
public:
	void rva00432F7D(Rva00432F23Node *node);
};

extern Rva00432F23 *g_004C9DC9Container;

class AnimationSoundClientBehavior : public Rva004CA125
{
public:
	AnimationSoundClientBehavior(const AnimationSoundClientBehavior &other);

private:
	int m_secondary0C;
	float m_float10;
	Rva00432F23Node *m_next14;
	Rva00432F23Node *m_prev18;
};

AnimationSoundClientBehavior::AnimationSoundClientBehavior(
	const AnimationSoundClientBehavior &other)
	: Rva004CA125(other)
{
	int *slotInit = (int *)&m_secondary0C;
	*slotInit = (int)((unsigned int)vtbl_00C6FFFC);
	int zero = 0;
	int *vtab = (int *)this;
	*vtab = (int)((unsigned int)vtbl_00C5EE80);
	int *sec0C = (int *)&m_secondary0C;
	*sec0C = (int)((unsigned int)vtbl_00C5EE74);
	m_next14 = (Rva00432F23Node *)zero;
	m_prev18 = (Rva00432F23Node *)zero;
	m_float10 = other.m_float10;
	if (g_004C9DC9Container)
		g_004C9DC9Container->rva00432F7D((Rva00432F23Node *)this);
}
