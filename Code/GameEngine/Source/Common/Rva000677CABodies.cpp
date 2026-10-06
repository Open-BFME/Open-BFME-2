// cl: /O1 /DNDEBUG /MD /arch:SSE
class Rva000677CAHost
{
public:
	bool rva000677CA(int a, int b, float f);
	void rva00067494(int a1, int a2, int a3, int a4, int a5, int a6, unsigned char *p, bool *out);
};

bool Rva000677CAHost::rva000677CA(int a, int b, float f)
{
	bool out = false;
	unsigned char *p = &((unsigned char *)&f)[3];
	int fi = (int)f;
	rva00067494(a, b, 0x100, 0, fi, 0, p, &out);
	return out == false;
}
