// cl: /O1 /Ob1 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?rva0020F2A2@Rva0020F2A2Host@@QAE_NHPAX@Z @0x0020F2A2 79B
// Bool dispatch via rowed EAF6: null false; AB set runs rowed 0x20E493 copy via exact Out0020E493 types then int-copy to out and true; else rowed F27E bool. Int copy avoids x87; void out keeps PAX.
class Rva0020E89C;
class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int index);
};
struct Out0020E493
{
	float m_f;
	int m_i;
};
class Rva0020E493
{
public:
	Out0020E493 *rva0020E493(Out0020E493 *out);
private:
	char m_pad[0xB0];
};
class Rva0020F27EHost
{
public:
	bool rva0020F27E(int idx, int v);
};
struct EAF6Elem
{
	char m_pad[0xAB];
	unsigned char m_AB;
};
class Rva0020F2A2Host
{
public:
	bool rva0020F2A2(int idx, void *outRaw);
};
bool Rva0020F2A2Host::rva0020F2A2(int idx, void *outRaw)
{
	Out0020E493 *out = (Out0020E493 *)outRaw;
	Rva0020E89C *p = ((Rva0020EAF6View *)this)->rva0020EAF6(idx);
	if (p == 0)
		return false;
	if (((EAF6Elem *)p)->m_AB != 0)
	{
		Out0020E493 tmp;
		Out0020E493 *r = ((Rva0020E493 *)p)->rva0020E493(&tmp);
		((int *)out)[0] = ((int *)r)[0];
		((int *)out)[1] = ((int *)r)[1];
		return true;
	}
	return ((Rva0020F27EHost *)this)->rva0020F27E(idx, (int)out);
}