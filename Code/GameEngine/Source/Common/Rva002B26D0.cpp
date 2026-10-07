// cl: /O1 /arch:SSE /MD
// ?rva002B26D0@Rva002B26D0@@QAEXPAVRva00318C79Owner@@PAXMM1@Z @0x002B26D0 50B.
// ?rva002B2702@Rva002B2702@@QAEXPAX0H@Z @0x002B2702 85B.
// Owner/key guard pair (both thiscall through the +0xB0 helper host).
// rva002B26D0 (stdcall-shaped body, but callers pass this in ecx, so it is
// a member that never touches this): bail when owner or key is null, resolve
// the owner through rowed 0x00318C32, bail on mismatch, else forward the
// float pair plus key and extra pointer into pinned 0x0031A591.
// rva002B2702: same null guard, fill a stack float pair through pinned
// 0x0020EA58 on the +0xB0 helper, then forward owner, key, the pair by
// value and the extra pointer into rva002B26D0.
//
// Target evidence (game.dat, read-only, capstone): 26D0 is 50B ebp-frame
// with two null checks, thiscall pair, pointer compare and ret 0x14; 2702
// is 85B with the same guard shape, SSE pair fill, reserve-and-fill arg
// block plus a dead esp snapshot into the extra home, ret 0xC. The +0xB0
// helper body (0x20EA58, ret 8) reloads ecx from its first stack param, so
// its true convention is uncertain; the QAEX pin matches what this caller
// emits. Identity unproven: honest address-derived names; owner class
// follows the rowed 0x318C32 pin.
class Rva00318C32Ret;
class Rva00318C79Owner
{
public:
	Rva00318C32Ret *rva00318C32();
	void rva0031A591(float *pair, void *key, void *extra);
};

struct RvaFloatPair
{
	__forceinline RvaFloatPair() {}
	__forceinline ~RvaFloatPair() {}
	__forceinline RvaFloatPair(const RvaFloatPair &that)
	{
		f0 = that.f0;
		f1 = that.f1;
	}
	float f0;
	float f1;
};

class Rva002B2702B0
{
public:
	bool rva0020EA58(void *key, float *buf);
};

class Rva002B26D0
{
public:
	void rva002B26D0(Rva00318C79Owner *owner, void *key, RvaFloatPair pair, void *extra);
	void rva002B4F6C(struct Rva002B4F6CVector *ids, RvaFloatPair *out);

private:
	unsigned char m_pad00[0xB0];
	Rva002B2702B0 *m_b0;
};

void Rva002B26D0::rva002B26D0(Rva00318C79Owner *owner, void *key, RvaFloatPair pair, void *extra)
{
	if (owner == 0)
		return;
	if (key == 0)
		return;
	if (owner->rva00318C32() != key)
		owner->rva0031A591(&pair.f0, key, extra);
}

// Keep the established address-derived pin used by the script-action callers.
// Retail's SSE pair construction supplies evidence for the explicit memberwise
// float copy, rather than the implicit integer copy of a trivial aggregate.
class Rva002B2702
{
public:
	void rva002B2702(void *owner, void *key, int extra);
private:
	unsigned char m_pad00[0xB0];
	Rva002B2702B0 *m_b0;
};

void Rva002B2702::rva002B2702(void *owner, void *key, int extra)
{
	RvaFloatPair buf;
	if (owner == 0)
		return;
	if (key == 0)
		return;
	m_b0->rva0020EA58(key, &buf.f0);
	((Rva002B26D0 *)this)->rva002B26D0((Rva00318C79Owner *)owner,
		key, buf, (void *)extra);
}

struct Rva002B4F6CVector
{
	int *begin;
	int *end;
	int *storageEnd;
};

class Rva0020F27EHost
{
public:
	bool rva0020F27E(int index, int out);
};

// Target 0x002B4F6C..0x002B4FEB, ret 8: fetch the final two indexed
// pairs through the same +0xB0 helper, then return their difference.
// The index-forward helper's existing address-derived declaration carries
// its output pointer as an integer. No semantic name is established here.
void Rva002B26D0::rva002B4F6C(Rva002B4F6CVector *ids, RvaFloatPair *out)
{
	int count = ids->end - ids->begin;
	int lastIndex = count - 1;
	int previousIndex = count - 2;
	if (lastIndex < 0 || previousIndex < 0)
	{
		lastIndex = 0;
		previousIndex = 0;
	}
	RvaFloatPair last, previous;
	((Rva0020F27EHost *)m_b0)->rva0020F27E(ids->begin[lastIndex], (int)&last);
	((Rva0020F27EHost *)m_b0)->rva0020F27E(ids->begin[previousIndex], (int)&previous);
	*out = previous;
	out->f0 -= last.f0;
	out->f1 -= last.f1;
}
