// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002B8767@Rva002B8767@@QAEXUBfmePairWI@@ABVAsciiStringWI@@_N1@Z @ 0x002B8767 121B unlock.
// Evidence: pinned callees Gen_003BEA30 0x002B59AA and push_back 0x004DFCB0;
// TheLivingWorldManager extern; caller 0x00564F9C unblocks 0x00564EC0;
// prev 0x002B86AA next 0x002B87E0 same WWLib dir.
#include <vector>

struct BfmePairWI
{
	int m_bfmeA;
	int m_bfmeB;
};

class AsciiStringWI
{
public:
	AsciiStringWI(const AsciiStringWI &other);
	~AsciiStringWI(void);
private:
	char *m_bfmeData;
};

class BfmeStrWI : private AsciiStringWI
{
public:
	BfmeStrWI(const AsciiStringWI &other) : AsciiStringWI(other) {}
	~BfmeStrWI(void) {}
};

class Gen_003BEA30
{
public:
	Gen_003BEA30(const BfmePairWI &pair, int kind, const AsciiStringWI &first, bool flag, const AsciiStringWI &second);
	BfmePairWI m_bfmePair;
	int m_bfmeKind;
	BfmeStrWI m_bfmeFirst;
	BfmeStrWI m_bfmeSecond;
	bool m_bfmeFlag;
};

class ModuleData;

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

class Rva00DFE1C8Host
{
public:
	void rva00213171(int a, void *b, int c);
};

struct Rva002B8767Counter
{
	char m_pad[0x2C];
	int m_count;
};

class Rva002B8767
{
public:
	void rva002B8767(BfmePairWI pair, const AsciiStringWI &a, bool b, const AsciiStringWI &c);
private:
	char m_pad00[0xB0];
	Rva002B8767Counter *volatile m_00B0;
	char m_padB4[0xBC - 0xB4];
	_STL::vector<const ModuleData *> m_00BC;
};

void Rva002B8767::rva002B8767(BfmePairWI pair, const AsciiStringWI &a, bool b, const AsciiStringWI &c)
{
	Gen_003BEA30 *obj = new Gen_003BEA30(pair, ++m_00B0->m_count, a, b, c);
	const ModuleData *tmp = (const ModuleData *)obj;
	((Rva00DFE1C8Host *)TheLivingWorldManager)->rva00213171(obj->m_bfmeKind, obj, 2);
	m_00BC.push_back(tmp);
}
