// cl: /O1 /MD
// Native2B2BEC..2B2C12: nullable lookup then region ground placement.
// Return was formerly guessed as a pointer. WB D27970/retail2BF652 assigns
// no pointer result; the sole direct caller2BD2A8 ignores EAX and proceeds
// to unrelated owner fields. Preserve the null gate and correct both views
// to void; address-derived names do not assert original application types.
struct Rva002B2BECArg
{
	unsigned char m_pad00[0x2C];
	void *m_2C;
};

class Rva002104B6
{
public:
	void *rva002104B6(void *slot);
};

class Rva002BF652
{
public:
	void rva002BF652(void *value);
};

// Bind to the existing data-ledger owner; keep the retail access view local.
class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;

class Rva002B2BEC
{
public:
	void rva002B2BEC(Rva002B2BECArg *arg);

private:
	unsigned char m_pad00[0xB0];
	Rva002104B6 *m_b0;
};

void Rva002B2BEC::rva002B2BEC(Rva002B2BECArg *arg)
{
	void *r = m_b0->rva002104B6(&arg->m_2C);
	if (r == 0)
		return;
	((Rva002BF652 *)g_00DFEF18)->rva002BF652(r);
}
