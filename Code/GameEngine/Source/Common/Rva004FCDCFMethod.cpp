// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?QueryRegionsAndNumbers@PlayerDefeatCondition@LivingWorldScenario@@QAEXPAXPAXPAH@Z, retail 0x004FCDCF, 114 bytes.
// Caller 0x004FD4D4 passes player plus vector plus maxOut; duplicate check by +0x12c then push_back plus max update.
// Keep this inlined unsigned max overload local; retail has one external owner.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

class ModuleData
{
public:
	char m_pad[0x12c];
	int m_12c;
};

class Rva002104B6
{
public:
	void *rva002104B6(void *a1);
};

class Rva002BA8F1Logic
{
public:
	char m_pad[0xb0];
	Rva002104B6 *m_B0;
};

class LivingWorldScenario
{
public:
	class PlayerDefeatCondition;
};

class LivingWorldScenario::PlayerDefeatCondition
{
public:
	void QueryRegionsAndNumbers(void *a1, _STL::vector<const ModuleData *> *vec, int *maxOut);
private:
	char m_pad[0x10];
	int m_10;
	unsigned char m_14;
};

void LivingWorldScenario::PlayerDefeatCondition::QueryRegionsAndNumbers(void *a1, _STL::vector<const ModuleData *> *vec, int *maxOut)
{
	if (m_14 != 0) {
		Rva002104B6 *mgr = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_B0;
		const ModuleData *mod = (const ModuleData *)mgr->rva002104B6((char *)a1 + 0x2c);
		struct Vec12
		{
			const ModuleData **m_begin;
			const ModuleData **m_end;
			void *m_endCap;
		};
		Vec12 *vl = (Vec12 *)vec;
		unsigned i = 0;
		int n = ((char *)vl->m_end - (char *)vl->m_begin) >> 2;
		if (n != 0) {
			int key = mod->m_12c;
			const ModuleData **pp = vl->m_begin;
			do {
				if ((*pp)->m_12c == key)
					goto done;
				++i;
				++pp;
			} while (i < (unsigned)n);
		}
		vec->push_back(mod);
done:;
	}
	int v = m_10;
	if (*maxOut < v)
		*maxOut = v;
}
