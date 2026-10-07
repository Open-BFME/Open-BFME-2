// cl: /O1 /arch:SSE /MD
// ?rva002B2757@Rva002B2757@@QAEXPAVRva00318C79Owner@@PAMPAX@Z @0x002B2757 94B.
// Pair-probe forward (thiscall, ret 0xC): bail when the owner is null;
// stage the position pair plus a zero float on the stack, probe through
// pinned 0x0020FAEA (int, float*) on the +0xB0 helper, and when the rowed
// 0x00318C32 owner tag mismatches the probe result, forward position,
// probe and extra into pinned 0x0031A591 on the owner.
//
// Target evidence (game.dat, read-only, capstone): ebp frame, leading null
// guard, SSE pair fill with xorps zero, callee mix (pinned 20FAEA, rowed
// 318C32, pinned 31A591 with (pos, probe, extra)), pop edi/esi, leave,
// ret 0xC. 20FAEA arity (int, float*) from its four call sites all pushing
// (X, buf). Identity unproven: honest address-derived names.
class Rva00318C32Ret;
class Rva00318C79Owner
{
public:
	Rva00318C32Ret *rva00318C32();
	void rva0031A591(float *pair, void *key, void *extra);
};

class Rva002B2757B0
{
public:
	void *rva0020FAEA(float *buf, int mode);
};

class Rva002B2757
{
public:
	void rva002B2757(Rva00318C79Owner *owner, float *pos, void *extra);

private:
	unsigned char m_pad00[0xB0];
	Rva002B2757B0 *m_b0;
};

void Rva002B2757::rva002B2757(Rva00318C79Owner *owner, float *pos, void *extra)
{
	float buf[3];
	if (owner == 0)
		return;
	buf[0] = pos[0];
	buf[1] = pos[1];
	buf[2] = 0.0f;
	void *r = m_b0->rva0020FAEA(buf, 0);
	if (owner->rva00318C32() != (Rva00318C32Ret *)r)
		owner->rva0031A591(pos, r, extra);
}
