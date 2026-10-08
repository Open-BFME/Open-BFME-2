// cl: /O1 /arch:SSE /EHsc /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva004AF531@Rva004AF531@@QAEHH@Z @0x004AF531 123B ret 4.
// Probe the int map at +0x10C with the argument, then with key 1.
// A miss returns 1000. A hit returns the dword at node+0x14.

#include <map>

struct Rva004AF531Rec
{
	int m_key;
	int m_a;
	int m_b;
	float m_one;
	unsigned char m_flag;
	Rva004AF531Rec(int key) : m_key(key), m_a(0), m_b(0), m_one(1.0f), m_flag(0) {}
};

struct RespawnRule
{
 unsigned level;
 unsigned cost;
 int time;
 float health;
 bool autoSpawn;
 RespawnRule(unsigned ruleLevel=1):level(ruleLevel),cost(0),time(0),health(1.0f),autoSpawn(false) {}
};
class BFME2RespawnRuleTree
{
public:
 void *find(const unsigned &key) const;
 void *sentinel;
};
struct RespawnRuleNode
{
 char prefix[0x10];
 RespawnRule rule;
};
extern float g_parseDurationMsecScale;

class Rva004AF531
{
public:
	int rva004AF531(int key);
 int rva004AF5AC(unsigned level);
	char m_pad[0x10C];
	_STL::map<int, void *> m_map;
};

int Rva004AF531::rva004AF531(int key)
{
	Rva004AF531Rec rec(key);
	_STL::map<int, void *>::iterator it = m_map.find(rec.m_key);
	_STL::map<int, void *>::iterator end = m_map.end();
	if (it == end)
	{
		Rva004AF531Rec fallback(1);
		it = m_map.find(fallback.m_key);
		if (it == end)
			return 1000;
	}
	return (int)(*it).second;
}

// Native4AF5AC..4AF63E: rule lookup with level1 fallback, node time
// at18 divided by1000. The target uses the same20-byte rule construction
// as rowed RespawnUpdate::triggerDeathBeforeRespawn4AF63E. Native shared
// duration scale DBA4EC=0.005 and literal C556F0=30000 supply the miss.
// Receiver original identity remains unknown; respawn-family relation
// follows the shared tree at10C, rule layout and adjacent death handler.
int Rva004AF531::rva004AF5AC(unsigned level)
{
 RespawnRule rule(level);
 BFME2RespawnRuleTree *rules=(BFME2RespawnRuleTree *)&m_map;
 RespawnRuleNode *found=(RespawnRuleNode *)rules->find(rule.level);
 RespawnRuleNode *end=(RespawnRuleNode *)rules->sentinel;
 if(found==end) {
  rule.RespawnRule::RespawnRule(1);
  found=(RespawnRuleNode *)rules->find(rule.level);
  if(found==end) return (int)(g_parseDurationMsecScale * 30000.0f);
 }
 return found->rule.time / 1000;
}
