// cl: /MD /Op
//
// ?rva0028E8D4@Rva0028E8D4@@QBEXPAM@Z, retail 0x0028e8d4, 41 bytes. Banked partial (score 0.9) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
//
// Chain from just-landed ?get@Rva002722AA@@QBEPAXXZ: calls the branched
// matrix getter then copies its translation floats at +0xC/+0x1C/+0x2C to
// the 3-float out pointer. Evidence: caller 0x0028E8FD passes a 12-byte
// local and reads it with SSE; callee 0x002722AA now rowed.

class Rva002722AA
{
public:
	void *get() const;
};

struct Rva0028E8D4Matrix
{
	float m[12];
};

class Rva0028E8D4
{
public:
	void rva0028E8D4(float *out) const;
};

void Rva0028E8D4::rva0028E8D4(float *out) const
{
	const Rva0028E8D4Matrix *m =
		(const Rva0028E8D4Matrix *)((const Rva002722AA *)this)->get();
	const float x = m->m[3];
	const float y = m->m[7];
	const float z = m->m[11];
	out[0] = x;
	out[1] = y;
	out[2] = z;
}
