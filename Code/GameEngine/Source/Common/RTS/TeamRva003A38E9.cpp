// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /MD /Oy-
// Native 003A38E9..003A393A RET8. Matched ScriptGlue 003BECCD supplies a
// getTeamNamed receiver and the existing two-word method declaration. Retail
// uses the first word as an AsciiString key and only the low byte of the
// second: zero erases an existing entry; exactly one inserts a missing state.
// Team+48 agrees with the matched state query 003A3717. Lookup/erase are
// already rowed; 003A3763..003A37DC RET4 supplies the mapped-byte address.
#include "ascii_string.h"
class Rva00056F61;
struct Rva0041534BIter
{
 void *m_node;
 Rva00056F61 *m_table;
 Rva0041534BIter(void *node, Rva00056F61 *table) : m_node(node), m_table(table) {}
};
class Rva00056F61
{
public:
 Rva0041534BIter rva0041534B(const AsciiString *key);
 bool *rva003A3763(const AsciiString *key);
};
struct VideoPair
{
 struct { void *first; void *second; } s;
 VideoPair(const Rva0041534BIter &other) { s.first = other.m_node; s.second = other.m_table; }
 VideoPair(const VideoPair &other) { s.first = other.s.first; s.second = other.s.second; }
};
class Rva000427195 { public: void rva003A37DC(VideoPair cursor); };
class Team
{
public:
 void rva003A38E9(int keyWord, int stateWord);
private:
 char m_beforeStates[0x48];
 Rva00056F61 m_states;
};

void Team::rva003A38E9(int keyWord, int stateWord)
{
 const AsciiString *key = (const AsciiString *)keyWord;
 Rva0041534BIter cursor = m_states.rva0041534B(key);
 if (cursor.m_node)
 {
  if ((unsigned char)stateWord == 0)
   ((Rva000427195 *)&m_states)->rva003A37DC(VideoPair(cursor));
 }
 else if ((unsigned char)stateWord == 1)
  *m_states.rva003A3763(key) = true;
}
