// cl: /O1 /MD
// ?rva0055ADBA@Rva00506FE9Hit@@QAEXPAX@Z retail 0x0055ADBA 30B: wrapper loads global 0x00DFEEF8 to get record for arg then removes this via rowed 0x004EC276; evidence pin plus callees rowed plus 6 matched callers
struct Rva002A8AB1Record;
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *x);
};

class Rva004EC276
{
public:
	void rva004EC276(void *x);
};

extern Rva002A8F24 *g_00DFEEF8;

class Rva00506FE9Hit
{
public:
	void rva0055ADBA(void *x);
};

void Rva00506FE9Hit::rva0055ADBA(void *x)
{
	Rva002A8F24 *mgr = g_00DFEEF8;
	Rva002A8AB1Record *rec = mgr->rva002A8AB1(x);
	((Rva004EC276 *)rec)->rva004EC276(this);
}
