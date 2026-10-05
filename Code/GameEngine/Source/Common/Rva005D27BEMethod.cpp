// cl: /O1 /MD /Oy-
// ?rva005D27BE@Rva005D2664@@QAEXPBD@Z @0x005D27BE 39B
// Evidence: chain from rowed 0x005D2505Get plus rowed 0x005D2664 plus caller shape plus sibling Rva005D2664Method TU.
class Rva000AD6F4
{
public:
	void clear();
};

class Rva005D2664
{
public:
	void rva005D2664(int idx);
	void rva005D27BE(const char *params);
	void rva005D28F4(const char *params);
private:
	char m_header00[0x1C];
};

bool __cdecl Rva005D2505Get(const char *params, int *out);

void Rva005D2664::rva005D27BE(const char *params)
{
	if (Rva005D2505Get(params, (int *)&params))
		rva005D2664((int)params);
}

void Rva005D2664::rva005D28F4(const char *params)
{
	if (Rva005D2505Get(params, (int *)&params))
		((Rva000AD6F4 *)((char *)this + (int)params * 0x1C + 0x20))->clear();
}
