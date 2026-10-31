// cl: /O1 /arch:SSE /G7 /Oy- /EHsc /MD /Ireference/shims/bfme2_ascii
// Native 002C004F..002C00C1: erase a non-null C-string key from the
// table at owner+AC. WB D28E60 calls find then iterator-copy erase;
// STLport's hashtable erase-by-iterator is the semantic reference.
// Original application owner and mapped value type remain unresolved.
#include "ascii_string.h"
class Rva00056F61;
struct Rva0041534BIter
{
public:
	Rva0041534BIter(void *n, Rva00056F61 *t) : m_node(n), m_table(t) {}
	void *m_node; // +0x00
	Rva00056F61 *m_table; // +0x04
};
class Rva00056F61
{
public:
	Rva0041534BIter rva0041534B(const AsciiString*);
};
struct TwoInts002BFCF5 {
 int x, y;
 TwoInts002BFCF5(const Rva0041534BIter &other) : x((int)other.m_node), y((int)other.m_table) {}
 TwoInts002BFCF5(const TwoInts002BFCF5 &other) : x(other.x), y(other.y) {}
 ~TwoInts002BFCF5() {}
};
struct pair;
class Rva002BFCF5
{
public:
	void erase(TwoInts002BFCF5 pair);
private:
	void helper(const TwoInts002BFCF5 *pair);
};
struct Rva002BFF5AEntry;
struct Rva002BFFD4Template;
class Rva000411084;
class Rva000427195
{
public:
	void *first(Rva000411084 *);
	int bucketIndex(const AsciiString *name);
	void rva00212858(unsigned int n);
};
class Rva002BFF5A {
public:
    Rva002BFF5AEntry *rva002BFF5A(int key);
    void update();
    void rva002BFFD4(Rva002BFFD4Template *,int kind,unsigned word);
    void rva002C004F(const char *name);
private:
    char unknown[0xac];
    Rva000427195 table;
};
void Rva002BFF5A::rva002C004F(const char *name) {
 if (name) {
  AsciiString key(name);
  Rva0041534BIter it = ((Rva00056F61*)&table)->rva0041534B(&key);
  if (it.m_node)
   reinterpret_cast<Rva002BFCF5 *>(&table)->erase(TwoInts002BFCF5(it));
 }
}
