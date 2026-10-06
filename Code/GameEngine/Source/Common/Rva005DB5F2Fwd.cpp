// cl: /O1 /DNDEBUG /MD
// ?rva005DB5F2@Rva005DB5F2@@QAEXHHH@Z @0x005DB5F2 54B interior forwarder.
// this points 0x58 into the container; o = this-0x58, then pinned
// 0x005DB512 (this+3 ints void) as (a,b,c) and (a,c,b), then rowed
// 0x005DB3B3 (this+int void) as (b). Ret 0xC. Address-derived.
class Rva005DB512
{
public:
	void rva005DB512(int a, int b, int c);
};

class Rva005DB3B3
{
public:
	void rva005DB3B3(int b);
};

class Rva005DB5F2
{
public:
	void rva005DB5F2(int a, int b, int c);
};

struct Rva005DB5F2Container : public Rva005DB512
{
	unsigned char m_pad[0x57];
	Rva005DB5F2 in;
};

void Rva005DB5F2::rva005DB5F2(int a, int b, int c)
{
	Rva005DB5F2Container *o = (Rva005DB5F2Container *)((char *)this - 0x58);
	o->rva005DB512(a, b, c);
	o->rva005DB512(a, c, b);
	((Rva005DB3B3 *)o)->rva005DB3B3(b);
}
