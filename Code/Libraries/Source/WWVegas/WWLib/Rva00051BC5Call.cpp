// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?Rva00051BC5Call@@YAHPAXH@Z, retail 0x00051BC5, 28 bytes.
// Free two-virtual chase wrapper unblocking 0x0005CC28.
// Evidence: leaf lane, callers 2 unclaimed FUN_0045cc28, prev/next same dir,
// callees all rowed or pinned, no donor.
class A27
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void *v27(int x);
};
class B28
{
public:
	virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03();
	virtual void w04(); virtual void w05(); virtual void w06(); virtual void w07();
	virtual void w08(); virtual void w09(); virtual void w10(); virtual void w11();
	virtual void w12(); virtual void w13(); virtual void w14(); virtual void w15();
	virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19();
	virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23();
	virtual void w24(); virtual void w25(); virtual void w26(); virtual void w27();
	virtual int w28(int x);
};
int __cdecl Rva00051BC5Call(void *a, int b)
{
	A27 *p = (A27 *)a;
	void *r = p->v27(b);
	B28 *q = (B28 *)r;
	return q->w28(b + 4);
}
