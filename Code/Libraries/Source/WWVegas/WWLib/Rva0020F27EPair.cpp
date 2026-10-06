// cl: /O1 /Ob1 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?rva0020F27E@Rva0020F27EHost@@QAE_NHH@Z @0x0020F27E 36B
// Index-then-forward via rowed 0xEAF6 and pinned 0xEA58: passthrough this for both calls, nullNe->false else EA58 bool.
class Rva0020E89C;
class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int index);
};
class Rva0020EA58
{
public:
	bool rva0020EA58(void *p, int v);
};
class Rva0020F27EHost
{
public:
	bool rva0020F27E(int idx, int v);
};
bool Rva0020F27EHost::rva0020F27E(int idx, int v)
{
	Rva0020E89C *p = ((Rva0020EAF6View *)this)->rva0020EAF6(idx);
	if (p == 0)
		return false;
	return ((Rva0020EA58 *)this)->rva0020EA58(p, v);
}