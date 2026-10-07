// cl: /O1 /MD
struct Rva0027F13CBuf
{
	unsigned char m_pad[0x14];
	int m_14;
	unsigned char m_tail[4];
};
class Rva0027D244Host
{
public:
	void rva0027D244(int v);
};
class Rva0027DF9DHost
{
public:
	void rva0027DF9D(int a, float b, void *c, int d, int e);
};
class Rva0027F13CHost
{
public:
	int rva0027F13C(int a, int b, float c);
};
// ?rva0027F13C@Rva0027F13CHost@@QAEHHHM@Z
int Rva0027F13CHost::rva0027F13C(int a, int b, float c)
{
	Rva0027F13CBuf buf;
	((Rva0027D244Host *)&buf)->rva0027D244(a);
	((Rva0027DF9DHost *)this)->rva0027DF9D(b, c, &buf, 0, 2);
	return buf.m_14;
}
