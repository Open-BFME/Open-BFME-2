// ?notifyDozerDead@AIBuilder@@QAEXPAURva005996FFArg@@@Z @ 0x004EC869 139B chain via 0x005996FF.
// Evidence: calls rowed 0x005996FF Rva005996FFListErase plus rowed predicate 0x004E9378 plus rowed list<int> erase 0x00438539 plus rowed vector<ModuleData*> push_back 0x004DFCB0; caller 0x004EC8F4.
// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Use the verified unsigned max provider at retail RVA 0x00013740.
#include <stl/_algobase.h>
namespace _STL {
template <> const unsigned int& max<unsigned int>(const unsigned int&, const unsigned int&);
}

#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

#include <vector>

struct Inner64;
struct Rva005996FFArg
{
	char m_pad00[4];
	Inner64 *m_04;
	char m_pad08[0x6C];
	int m_74;
};

class Rva005996FF
{
public:
	void rva005996FF(Rva005996FFArg *arg, bool flag);
};

class AIDozerManager
{
public:
	void rva00599825(int id);
};

class Rva004E9378
{
	char m_pad[0x10];
	int m_state;
public:
	bool rva004E9378();
};

class ModuleData
{
public:
  virtual ~ModuleData();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void virt(int x);
public:
  char m_pad04[4];
	int m_08;
	char m_pad0C[4];
	int m_10;
	char m_pad14[0x0C];
	unsigned char m_20;
};

// ??0AIBuilder@@QAE@PAVPlayer@@@Z retail 0x004EC430 (239 bytes, ret 4): the
// player at +0 then each sub-builder built from it -- AIBaseBuilder
// 0x005070E9 (+0x04), 0x00598E85 (+0x38, unrowed, pinned), 0x0059A85C
// (+0x90), 0x004EAAF3 (+0xB4), 0x004E9B46 (+0xE4), 0x00598F3F (+0xFC), a new
// 0x40-byte 0x00597693 object (+0x12C), the module-data vector and id list,
// the dozer manager 0x00599784 (+0x140), a cleared flag (+0x154) and thirty
// times the frame-rate word at 0x00DBA4E4 (+0x158). Member spellings follow
// the rowed constructors; their identities are unproven.
class Player;
class AIBaseBuilder { public: AIBaseBuilder(void *player); ~AIBaseBuilder(); char m_data[0x34]; };
class Rva00598E85 { public: Rva00598E85(void *player); ~Rva00598E85(); char m_data[0x58]; };
class Rva0059A85C { public: Rva0059A85C(void *player); ~Rva0059A85C(); char m_data[0x24]; };
class Rva004EA3B8 { public: Rva004EA3B8(void *player); ~Rva004EA3B8(); char m_data[0x30]; };
class Rva004E9B46 { public: Rva004E9B46(int player); ~Rva004E9B46(); char m_data[0x18]; };
class Rva005990DF { public: Rva005990DF(int player); ~Rva005990DF(); char m_data[0x30]; };
class Rva00597693 { public: Rva00597693(void *player); char m_data[0x40]; };
class Rva005997CD { public: Rva005997CD(int player); ~Rva005997CD(); char m_data[0x14]; };
extern int g_Va00DBA4E4;

class AIBuilder
{
public:
	AIBuilder(Player *player);
	void notifyDozerDead(Rva005996FFArg *arg);
	void rva004EC2D4(int value);
private:
	Player *m_player;			// +0x00
	AIBaseBuilder m_base;			// +0x04
	Rva00598E85 m_38;
	Rva0059A85C m_90;
	Rva004EA3B8 m_B4;
	Rva004E9B46 m_E4;
	Rva005990DF m_FC;
	Rva00597693 *m_12C;
	_STL::vector<const ModuleData *> m_vec;	// +0x130
	_STL::list<int> m_list;			// +0x13C
	Rva005997CD m_dozers;			// +0x140
	bool m_154;
	int m_158;
};

AIBuilder::AIBuilder(Player *player)
	: m_player(player), m_base(player), m_38(player), m_90(player), m_B4(player),
	  m_E4((int)player), m_FC((int)player), m_12C(new Rva00597693(player)),
	  m_dozers((int)player), m_154(false), m_158(g_Va00DBA4E4 * 30)
{
}

void AIBuilder::notifyDozerDead(Rva005996FFArg *arg)
{
	((Rva005996FF *)((char *)this + 0x140))->rva005996FF(arg, true);
	_STL::list<int>::iterator it = m_list.begin();
	if (it == m_list.end())
		return;
	{
		int value = arg->m_74;
		ModuleData *cur;
		while (it != m_list.end()) {
			cur = (ModuleData *)(*it);
			if (cur->m_08 == value)
				goto found;
			++it;
		}
		return;
found:
		;
		if (((Rva004E9378 *)cur)->rva004E9378())
			return;
		if (cur->m_20) {
			cur->virt(0);
			cur->m_08 = 0;
			m_list.erase(it);
			m_vec.push_back(cur);
		} else {
			cur->virt(3);
		}
	}
}

void AIBuilder::rva004EC2D4(int value)
{
	((AIDozerManager *)((char *)this + 0x140))->rva00599825(value);
	_STL::list<int>::iterator it = m_list.begin();
	if (it == m_list.end())
		return;
	{
		ModuleData *cur;
		while (it != m_list.end()) {
			cur = (ModuleData *)(*it);
			if (cur->m_08 == value)
				goto found;
			++it;
		}
		return;
found:
		;
		cur->virt(2);
	}
}
