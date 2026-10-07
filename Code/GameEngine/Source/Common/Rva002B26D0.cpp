// cl: /O1 /arch:SSE /MD
// ?rva002B26D0@Rva002B26D0@@QAEXPAVRva00318C79Owner@@PAXMM1@Z @0x002B26D0 50B.
// ?rva002B2702@Rva002B26D0@@QAEXPAVRva00318C79Owner@@PAX1@Z @0x002B2702 85B.
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
	void rva002B2702(Rva00318C79Owner *owner, void *key, void *extra);

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

// ?rva002B2702@Rva002B26D0@@QAEXPAVRva00318C79Owner@@PAX1@Z present-unmatched
void Rva002B26D0::rva002B2702(Rva00318C79Owner *owner, void *key, void *extra)
{
	float buf[2];
	if (owner == 0)
		return;
	if (key == 0)
		return;
	m_b0->rva0020EA58(key, buf);
	rva002B26D0(owner, key, *(RvaFloatPair *)buf, extra);
}
