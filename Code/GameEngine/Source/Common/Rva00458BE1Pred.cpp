// cl: /O1 /MD
// ?rva00458BE1@Rva00458BE1@@QAE_NXZ @0x00458BE1 46B
// Predicate over sub at +4 with float at +0x24 and limit at +0x28 via AI query 0x2FEEAD.
// Evidence: early true when limit 0; AI g_Va009FF0F8 plus obj at +8 plus 0x20 plus setge vs limit; caller 0x00458CCB.
class Object;
class AI
{
public:
	int rva002FEEAD(Object *obj, float range, unsigned int flags);
};

extern AI *g_Va009FF0F8;

struct Rva00458BE1Sub
{
	char m_pad[0x24];
	float m_range;
	int m_limit;
};

class Rva00458BE1
{
public:
	unsigned char rva00458BE1();
private:
	char m_pad[4];
	Rva00458BE1Sub *m_sub;
	Object *m_obj;
};

unsigned char Rva00458BE1::rva00458BE1()
{
	Rva00458BE1Sub *sub = m_sub;
	if (sub->m_limit == 0)
		return 1;
	Object *obj = m_obj;
	int found = g_Va009FF0F8->rva002FEEAD(obj, sub->m_range, 0x20);
	return (unsigned char)(found >= sub->m_limit);
}
