// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva0028FCD9@Object@@QAEXHH@Z @0x0028FCD9 (380B), native 0028FCD9..0028FE55
// RET8. Object model-condition refresh: the 0x4C-byte set mask takes the
// condition the .rdata table at VA 0x00BFBF34 lists for the first argument,
// and the rowed clear-and-set 0x0028CFB2 applies it against conditions 3..5.
// The +0x84 drawable hook gets the same argument while the logic flag at
// TheGameLogic+0x6D is clear. Table value 5 drives the helper at +0x230 and
// then clears conditions 0x8B..0x8E (0x001E42F2); otherwise KINDOF 4 objects
// select one of those four by the second argument. WB CC6F80 only names the
// inlined BitFlags SetBit; the owner method and enum names remain unknown.
// Both masks are function-scope locals: that gives retail's frame, where the
// first clear-mask temporary shares the slot of the later ones.
#include <string.h>

enum ModelConditionFlagType { MODELCONDITION_014E = 0x14E };
enum KindOfType { KINDOF_04 = 4, KINDOF_45 = 0x45 };
extern const int g_Va00BFBF34[];
// Defined here: nothing else in the tree did. Retail .rdata VA 0x00BFBF34
// (RVA 0x007FBF34) holds -1, 3, 4, 5, 0 up to the next literal at 0x007FBF48.
extern const int g_Va00BFBF34[] = { -1, 3, 4, 5, 0 };
extern int BfmeLogicFramesPerSecond;
class GameLogic; extern GameLogic *TheGameLogic;

struct ConditionMask0028FCD9
{
	unsigned int m_bits[19];
	__forceinline void set(unsigned int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
};
class Rva00265254
{
public:
	Rva00265254(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4);
	unsigned int m_bits[19]; // +0x00
};
struct Rva0028F5C6
{
public:
	Rva0028F5C6(int unused, int b1, int b2, int b3, int b4);
	unsigned m_bits[19]; // +0x00
};
class Rva00278440Host { public: void rva00278440(int); };
class ObjectSMCHelper { public: void setModelConditionState(ModelConditionFlagType, unsigned int); };

class Object
{
public:
	void rva0028FCD9(int type, int level);
	void rva0028CFB2(const int *clear, const int *set);
	void rva001E42F2(const int *clear);
	bool isKindOf(KindOfType) const;
private:
	char m_pad00[0x84];
	Rva00278440Host *m_drawable;		// +0x84
	char m_pad88[0x230 - 0x88];
	ObjectSMCHelper *m_smcHelper;		// +0x230
};

void Object::rva0028FCD9(int type, int level)
{
	ConditionMask0028FCD9 set;
	ConditionMask0028FCD9 levelSet;
	memset(&set, 0, sizeof(set));
	if (g_Va00BFBF34[type] != -1)
		set.set(g_Va00BFBF34[type]);
	rva0028CFB2((const int *)&Rva00265254(0, 3, 4, 5), (const int *)&set);
	if (!*((const unsigned char *)TheGameLogic + 0x6D) && m_drawable)
		m_drawable->rva00278440(type);
	if (g_Va00BFBF34[type] == 5 && isKindOf(KINDOF_45))
		m_smcHelper->setModelConditionState(MODELCONDITION_014E, BfmeLogicFramesPerSecond * 3);
	if (g_Va00BFBF34[type] != 5 && isKindOf(KINDOF_04)) {
		memset(&levelSet, 0, sizeof(levelSet));
		if (level == 1) {
			levelSet.set(0x8B);
			rva0028CFB2((const int *)&Rva00265254(0, 0x8C, 0x8D, 0x8E), (const int *)&levelSet);
		} else if (level == 2) {
			levelSet.set(0x8C);
			rva0028CFB2((const int *)&Rva00265254(0, 0x8B, 0x8D, 0x8E), (const int *)&levelSet);
		} else if (level == 3) {
			levelSet.set(0x8D);
			rva0028CFB2((const int *)&Rva00265254(0, 0x8B, 0x8C, 0x8E), (const int *)&levelSet);
		} else if (level == 4) {
			levelSet.set(0x8E);
			rva0028CFB2((const int *)&Rva00265254(0, 0x8B, 0x8C, 0x8D), (const int *)&levelSet);
		}
	} else {
		rva001E42F2((const int *)&Rva0028F5C6(0, 0x8B, 0x8C, 0x8D, 0x8E));
	}
}
