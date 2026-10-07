// cl: /O1 /arch:SSE /MD
// ?rva002B2858@Rva002B2858@@QAEXPAMH0@Z @0x002B2858 89B.
// Position select (thiscall, ret 0xC): probe (src, mode) through pinned
// 0x0020FAEA on the +0xB0 helper; when the probe mismatches the mode, fill
// a stack pair through pinned 0x0020EA58 on the same helper, else take the
// source pair directly; store the winning pair through the out pointer.
// Both callees share the +0xB0 object; the 0x20EA58 pin names its own view
// and the call goes through a free cast.
//
// Target evidence (game.dat, read-only, capstone): ebp frame with two
// push-ecx temps, cmp/je select, shared SSE store tail with early pop edi,
// leave, ret 0xC. Identity unproven: honest address-derived names.
class Rva002B2757B0
{
public:
	void *rva0020FAEA(float *buf, int mode);
};

class Rva002B2702B0
{
public:
	bool rva0020EA58(void *key, float *buf);
};

class Rva002B2858
{
public:
	void rva002B2858(float *out, int mode, float *src);

private:
	unsigned char m_pad00[0xB0];
	Rva002B2757B0 *m_b0;
};

void Rva002B2858::rva002B2858(float *out, int mode, float *src)
{
	float buf[2];
	float f0;
	float f1;
	if ((int)m_b0->rva0020FAEA(src, mode) != mode)
	{
		((Rva002B2702B0 *)m_b0)->rva0020EA58((void *)mode, buf);
		f1 = buf[1];
		f0 = buf[0];
	}
	else
	{
		f0 = src[0];
		f1 = src[1];
	}
	out[0] = f0;
	out[1] = f1;
}
