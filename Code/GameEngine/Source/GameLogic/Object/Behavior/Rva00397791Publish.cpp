// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva00397791@Rva00397791@@QAEXH@Z @0x00397791 101B: publishes the int arg
// to +0x90, resolves the +0x2c id through rowed GameLogic::findObjectByID,
// forwards found objects with the arg to pinned 0x0023D0C2, then runs the
// pinned 0x00397756 outer sweep over the +0x44/+0x68/+0x50/+0x5c ranges.
// Evidence: ecx=esi-0xc outer for the sweep calls (pinned method form),
// TheGameLogic hoisted into ebx, ranges pushed in 44/68/50/5c order with the
// last via adjusted esi; flags and decls follow neighbouring Behavior TUs.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object;
class GameLogic;

struct IdRange
{
	ObjectID *first;
	ObjectID *last;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	void rva0023D0C2(Object *obj, int arg);
};

class Rva00397756
{
public:
	void rva00397756(IdRange *range, int arg);
};

extern GameLogic *TheGameLogic;

class Rva00397791
{
public:
	void rva00397791(int x);

private:
	char m_pad00[0x2c];
	ObjectID m_id2c;
	char m_pad30[0x14];
	IdRange m_range44;
	char m_pad4c[4];
	IdRange m_range50;
	char m_pad58[4];
	IdRange m_range5c;
	char m_pad64[4];
	IdRange m_range68;
	char m_pad70[0x20];
	int m_arg90;
};

void Rva00397791::rva00397791(int x)
{
	m_arg90 = x;
	GameLogic *g = TheGameLogic;
	Object *o = g->findObjectByID(m_id2c);
	if (o != 0)
		g->rva0023D0C2(o, x);
	Rva00397756 *outer = (Rva00397756 *)((char *)this - 0xc);
	outer->rva00397756(&m_range44, x);
	outer->rva00397756(&m_range68, x);
	outer->rva00397756(&m_range50, x);
	outer->rva00397756(&m_range5c, x);
}
