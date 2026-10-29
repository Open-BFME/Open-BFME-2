// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// stlport46
// Small bodies from .text gaps no Ghidra function covers (twenty-ninth
// batch; see GapBodiesGE01.cpp). Each begins after its neighbour's padding or
// ret and ends in its own ret or tail jump. Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Callees and globals use the
// ledger's existing spellings, including private/protected statics reached
// through a friend view.
#include <math.h>

class AsciiString;
struct Coord3D;
class Xfer;

// --- 0x00056E78 (20B): bucket of a key through the rowed __stdcall
// Rva00055041AsciiHash 0x00055041, modulo the bucket count.
unsigned int __stdcall Rva00055041AsciiHash(const AsciiString *key);

class Rva00056E78
{
public:
	unsigned int rva00056E78(const AsciiString *key, unsigned int n) const;
};

unsigned int Rva00056E78::rva00056E78(const AsciiString *key, unsigned int n) const
{
	return Rva00055041AsciiHash(key) % n;
}

// --- 0x000579D3 (11B): clear a vector by erasing [begin, end) through its
// rowed erase 0x00056B72.
struct BfmeStringTailRecord144;

namespace _STL
{
	template <class T> class allocator;
	template <class T, class A = allocator<T> > class vector
	{
	public:
		T *erase(T *first, T *last);
		void clear() { erase(m_start, m_finish); }
	private:
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};
}

template void _STL::vector<BfmeStringTailRecord144>::clear();

// --- 0x00058ABF / 0x0005B524 (20B each): out-parameter forwarders that
// return their first argument after the rowed callee fills it.
class Rva00057D38Owner
{
public:
	int fwd(int out, int key);								// 0x00057D38
	int *rva00058ABF(int *out, int key);
};

int *Rva00057D38Owner::rva00058ABF(int *out, int key)
{
	fwd((int)out, key);
	return out;
}

struct Pair00058D4A;
struct BfmeStringRecord00054F57;

class Rva00058D4A
{
public:
	Pair00058D4A *rva0005A0EE(Pair00058D4A *out, const BfmeStringRecord00054F57 &record);	// 0x0005A0EE
	Pair00058D4A *rva0005B524(Pair00058D4A *out, const BfmeStringRecord00054F57 &record);
};

Pair00058D4A *Rva00058D4A::rva0005B524(Pair00058D4A *out, const BfmeStringRecord00054F57 &record)
{
	rva0005A0EE(out, record);
	return out;
}

// --- 0x00061A7D / 0x00061A8F (18B each): the rowed
// MilesAudioManager::playSample2DOr3DUsingCallbackBuffers with one of its two
// buffers null.
class PlayingAudioRef;

class MilesAudioManager
{
public:
	bool playSample2DOr3DUsingCallbackBuffers(PlayingAudioRef &ref, void *first, void *second);
	bool rva00061A7D(PlayingAudioRef &ref, void *second);
	bool rva00061A8F(PlayingAudioRef &ref, void *first);
};

bool MilesAudioManager::rva00061A7D(PlayingAudioRef &ref, void *second)
{
	return playSample2DOr3DUsingCallbackBuffers(ref, 0, second);
}

bool MilesAudioManager::rva00061A8F(PlayingAudioRef &ref, void *first)
{
	return playSample2DOr3DUsingCallbackBuffers(ref, first, 0);
}

// --- 0x000628DB (10B) / 0x000628E5 (6B): ShaderOverbrightEnabled set / get.
extern bool ShaderOverbrightEnabled;

void rva000628DB(bool on)
{
	ShaderOverbrightEnabled = on;
}

bool rva000628E5()
{
	return ShaderOverbrightEnabled;
}

// --- 0x0006607A (17B): float tangent through the msvcr71 tan thunk.
float rva0006607A(float x)
{
	return (float)tan((double)x);
}

// --- 0x0006614F (10B) / 0x00066159 (6B): DX8Wrapper's cleanup-hook store
// and fog-enable read; 0x0006E153 (8B) ShaderClass's dirty mark;
// 0x0006E175 (6B) WW3D's shadow-map pass read.
class DX8_CleanupHook;
class Rva0006614F;

class DX8Wrapper
{
	friend class Rva0006614F;
protected:
	static DX8_CleanupHook *m_pCleanupHook;
	static bool FogEnable;
};

class ShaderClass
{
	friend class Rva0006614F;
protected:
	static bool ShaderDirty;
};

class WW3D
{
	friend class Rva0006614F;
	static bool IsCurrentlyRenderingShadowMap;
};

class Rva0006614F
{
public:
	static void rva0006614F(DX8_CleanupHook *hook);
	static bool rva00066159();
	static void rva0006E153();
	static bool rva0006E175();
};

void Rva0006614F::rva0006614F(DX8_CleanupHook *hook)
{
	DX8Wrapper::m_pCleanupHook = hook;
}

bool Rva0006614F::rva00066159()
{
	return DX8Wrapper::FogEnable;
}

void Rva0006614F::rva0006E153()
{
	ShaderClass::ShaderDirty = true;
}

bool Rva0006614F::rva0006E175()
{
	return WW3D::IsCurrentlyRenderingShadowMap;
}

// --- 0x0006E15B / 0x0006E165 / 0x0006E17B (10B each): byte setters of
// ShaderAlphaReferenceOverride, ShaderAlphaReference, bfmeOnlyEmissiveDraws.
extern bool ShaderAlphaReferenceOverride;
extern unsigned char ShaderAlphaReference;
extern bool bfmeOnlyEmissiveDraws;

void rva0006E15B(bool on)
{
	ShaderAlphaReferenceOverride = on;
}

void rva0006E165(unsigned char value)
{
	ShaderAlphaReference = value;
}

void rva0006E17B(bool on)
{
	bfmeOnlyEmissiveDraws = on;
}

// --- 0x0006640C (48B): four floats.
class Rva0006640C
{
public:
	Rva0006640C(float x, float y, float z, float w);
private:
	float m_x;
	float m_y;
	float m_z;
	float m_w;
};

Rva0006640C::Rva0006640C(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w)
{
}

// --- 0x000664F4 (21B), 0x0006657B / 0x0006658C (17B each), 0x00067E8E
// (21B), 0x00067866 / 0x0006830A (18B each), 0x000681AF (36B), 0x000681D3 /
// 0x000681E7 (20B each), 0x000682E1 (25B): accessors of one large object:
// a four-word block at +0x1948, two floats at +0x37E4/+0x37E8, three cleared
// words at +0x3790, and guarded forwards to the members at +0x3850 (the tree
// buffer), +0x3870 and +0x3874. The +0x3870/+0x3874 forwards land on the
// rowed EmissionVelocityInfo::DoXfer body (an identical-code fold) and are
// spelled by that row.
struct GapQuad
{
	int a;
	int b;
	int c;
	int d;
};

class W3DTreeBuffer
{
public:
	bool rva000EA48D(void *a, const Coord3D *b, float c);	// 0x000EA48D
	bool rva000ECF2A(unsigned int a, int b);				// 0x000ECF2A
	bool rva000EA6A7(void *a);								// 0x000EA6A7
};

class Rva000EB08C
{
public:
	bool rva000EB2AC(int a, bool b);						// 0x000EB2AC
};

class Rva006DF050
{
public:
	void eraseKey(int key);									// 0x000D3C4B
};

// The +0x3874 object's add member is rowed under W3DBuffBuffer.
class Drawable;
class TBuff;
struct BuffInfoView;
class W3DBuffBuffer
{
public:
	TBuff *addBuff(Drawable *draw, const BuffInfoView *info);	// 0x000D3B27
};

class FXParticleSystem
{
public:
	class EmissionVelocityInfo
	{
	public:
		virtual void DoXfer(Xfer &xfer);					// 0x0047A69C
	};
};

class Rva000664F4
{
public:
	void rva000664F4(const GapQuad *value);
	void rva0006657B(float value);
	void rva0006658C(float value);
	void rva00067E8E();
	void rva00067866(Xfer &xfer);
	void rva0006830A(Xfer &xfer);
	TBuff *rva0006819B(Drawable *draw, const BuffInfoView *info);
	bool rva000681AF(void *a, const Coord3D *b);
	bool rva000681D3(unsigned int a, int b);
	bool rva000681E7(int a, bool b);
	bool rva000681FB(void *a);
	void rva000682E1(int key);
private:
	char m_pad00[0x1948];
	GapQuad m_1948;
	char m_pad1958[0x3790 - 0x1958];
	int m_3790;
	int m_3794;
	int m_3798;
	char m_pad379C[0x37E4 - 0x379C];
	float m_37E4;
	float m_37E8;
	char m_pad37EC[0x3850 - 0x37EC];
	W3DTreeBuffer *m_trees;									// +0x3850
	char m_pad3854[0x3870 - 0x3854];
	FXParticleSystem::EmissionVelocityInfo *m_3870;
	Rva006DF050 *m_3874;
};

void Rva000664F4::rva000664F4(const GapQuad *value)
{
	m_1948 = *value;
}

void Rva000664F4::rva0006657B(float value)
{
	m_37E4 = value;
}

void Rva000664F4::rva0006658C(float value)
{
	m_37E8 = value;
}

void Rva000664F4::rva00067E8E()
{
	m_3790 = 0;
	m_3794 = 0;
	m_3798 = 0;
}

void Rva000664F4::rva00067866(Xfer &xfer)
{
	if (m_3870)
		m_3870->FXParticleSystem::EmissionVelocityInfo::DoXfer(xfer);
}

void Rva000664F4::rva0006830A(Xfer &xfer)
{
	FXParticleSystem::EmissionVelocityInfo *info = (FXParticleSystem::EmissionVelocityInfo *)m_3874;
	if (info)
		info->FXParticleSystem::EmissionVelocityInfo::DoXfer(xfer);
}

bool Rva000664F4::rva000681AF(void *a, const Coord3D *b)
{
	if (m_trees)
		return m_trees->rva000EA48D(a, b, 0.0f);
	return false;
}

// --- 0x0006819B (20B, RET8): forward to the +0x3874 buff buffer's addBuff
// when there is one, else NULL.
TBuff *Rva000664F4::rva0006819B(Drawable *draw, const BuffInfoView *info)
{
	if (m_3874)
		return ((W3DBuffBuffer *)m_3874)->addBuff(draw, info);
	return 0;
}

bool Rva000664F4::rva000681D3(unsigned int a, int b)
{
	if (m_trees)
		return m_trees->rva000ECF2A(a, b);
	return false;
}

bool Rva000664F4::rva000681E7(int a, bool b)
{
	if (m_trees)
		return ((Rva000EB08C *)m_trees)->rva000EB2AC(a, b);
	return false;
}

// --- 0x000681FB (20B, RET4): forward to the +0x3850 tree buffer's
// 0x000EA6A7 when there is one, else false.
bool Rva000664F4::rva000681FB(void *a)
{
	if (m_trees)
		return m_trees->rva000EA6A7(a);
	return false;
}

void Rva000664F4::rva000682E1(int key)
{
	if (m_3874 && key)
		m_3874->eraseKey(key);
}

// --- 0x0006E039 (17B): the first node's +0x0C payload of the ring rooted at
// +4, or null when empty.
struct GapRingNode
{
	int m_00;
	GapRingNode *m_next;									// +0x04
	int m_08;
	int m_payload;											// +0x0C
};

class Rva0006E039
{
public:
	int rva0006E039() const;
private:
	int m_00;
	GapRingNode m_root;										// +0x04
};

int Rva0006E039::rva0006E039() const
{
	const GapRingNode *first = m_root.m_next;
	if (first == &m_root)
		return 0;
	return first->m_payload;
}

// --- 0x0006F2F8 (17B): a pointer and its +8 word.
struct GapHolder
{
	int m_00;
	int m_04;
	int m_08;
};

class Rva0006F2F8
{
public:
	Rva0006F2F8(const GapHolder *holder);
private:
	const GapHolder *m_holder;
	int m_value;
};

Rva0006F2F8::Rva0006F2F8(const GapHolder *holder) : m_holder(holder), m_value(holder->m_08)
{
}

// --- 0x0006F345 (22B): a float and a word returned by value.
struct GapFloatWord
{
	float f;
	int i;
	GapFloatWord(const float &a, const int &b)
	{
		f = a;
		i = b;
	}
};

GapFloatWord rva0006F345(const float &a, const int &b)
{
	return GapFloatWord(a, b);
}

// --- 0x0006F35B (24B): push a block onto the free list headed at VA
// 0x00DB4254, the head (+8) of the scene node pool Rva0006EFC8Grow.cpp owns.
class Rva0006EFC8
{
public:
	int m_00;
	void *m_04;
	void *m_head;
};
extern Rva0006EFC8 g_BfmeSceneNodePool;

class Rva0006F35B
{
public:
	void rva0006F35B(void *block, int size);
};

void Rva0006F35B::rva0006F35B(void *block, int size)
{
	if (block)
	{
		*(void **)block = g_BfmeSceneNodePool.m_head;
		g_BfmeSceneNodePool.m_head = block;
	}
}
