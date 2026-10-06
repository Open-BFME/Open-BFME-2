// cl: /DNDEBUG /MD /EHsc
// ?rva0026EE30@UpgradeTemplate@@QAEHPAX0@Z @ 0x0026EE30 (112B) unlock: difficulty-gated cost factor via rowed Rva002A9BF2 plus pinned Rva002A8AB1 record plus float globals. Evidence: caller 0x005974B3 thiscall ecx=UpgradeTemplate proven by calcCostToBuild same edi; ret 8 two args; g_00DFEEF8 plus g_Va00BBB8D8 plus g_Va00DBA4E4; +0x30 factor; +0x854 limit.
class Rva002A9BF2
{
public:
	void *rva002A9BF2();
};

struct Rva002A8AB1Record;
class Rva002A8F24
{
public:
	struct Rva002A8AB1Record *rva002A8AB1(void *);
};

extern class Rva002A8F24 *g_00DFEEF8;
extern float g_Va00BBB8D8;
extern int g_Va00DBA4E4;

class UpgradeTemplate
{
public:
	int rva0026EE30(void *, void *);
private:
	char m_pad[0x30];
	float m_factor30;
};

int UpgradeTemplate::rva0026EE30(void *arg1, void *arg2)
{
	(void)arg2;
	void *diff = ((Rva002A9BF2 *)arg1)->rva002A9BF2();
	if ((int)diff == 3) {
		if (g_00DFEEF8->rva002A8AB1(arg1)) {
			float *limitPtr = (float *)((char *)g_00DFEEF8 + 0x854);
			float base = g_Va00BBB8D8;
			float v;
			if (base > *limitPtr)
				v = *limitPtr;
			else
				v = base;
			float r = base - v;
			r *= m_factor30;
			r *= (float)g_Va00DBA4E4;
			return (int)r;
		}
	}
	float r2 = (float)g_Va00DBA4E4;
	r2 *= m_factor30;
	return (int)r2;
}
