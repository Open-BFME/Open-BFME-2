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
// The grid query 0x0027DF9D (Coord3D point, radius, result, flag, mode);
// its body tests the flag as a byte.
struct Coord3D;
class Rva0027D244;
class Rva0027DF9D
{
public:
	void rva0027DF9D(Coord3D *center, float radius, Rva0027D244 *out, bool flag, int mode);
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
	((Rva0027DF9D *)this)->rva0027DF9D((Coord3D *)b, c, (Rva0027D244 *)&buf, false, 2);
	return buf.m_14;
}
