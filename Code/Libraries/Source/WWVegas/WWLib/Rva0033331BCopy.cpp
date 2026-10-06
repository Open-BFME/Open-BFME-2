// cl: /DNDEBUG /MD
// ?Rva0033331BCopy@@YAPAVRva00332EC8@@PAV1@00PBX@Z @0x0033331B 38B
// retail 0x0033331B 38 bytes chain uninitialized_copy loop via rowed Construct 0x00333295 stride 0x24
// callers 0x00336207 0x00336252 unblocks 0x003361C6 neighbours prev 0x003332D6 fill_n and next 0x00333374 Get

class BfmeObject872Header
{
public:
	BfmeObject872Header(const BfmeObject872Header &that) throw();
private:
	char m_data[16];
};

class Rva00332EC8
{
public:
	Rva00332EC8(const Rva00332EC8 &that) throw();
private:
	unsigned int m_key;
	BfmeObject872Header m_a;
	BfmeObject872Header m_b;
};

void Rva00333295Construct(Rva00332EC8 *dest, const Rva00332EC8 &src) throw();

Rva00332EC8 *Rva0033331BCopy(Rva00332EC8 *p1, Rva00332EC8 *p2, Rva00332EC8 *p3, const void *ignored)
{
	Rva00332EC8 *d = p3;
	Rva00332EC8 *s = p1;
	Rva00332EC8 *e = p2;
	while (s != e)
	{
		Rva00333295Construct(d, *s);
		++s;
		++d;
	}
	return d;
}
