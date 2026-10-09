// cl: /O1 /arch:SSE /G7 /Oy- /EHsc /MD /Ireference/shims/bfme2_ascii
// Native 002C004F..002C00C1: erase a non-null C-string key from the
// table at owner+AC. WB D28E60 calls find then iterator-copy erase;
// STLport's hashtable erase-by-iterator is the semantic reference.
// Original application owner and mapped value type remain unresolved.
#include "ascii_string.h"
class Rva00056F61;
struct Rva0041534BIter {
 void *m_node;
 Rva00056F61 *m_table;
 Rva0041534BIter(void *n, Rva00056F61 *t) : m_node(n), m_table(t) {}
};
class Rva00056F61 {
public:
 __declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *key);
};
struct TwoInts002BFCF5 {
 int x, y;
 TwoInts002BFCF5(const Rva0041534BIter &other) : x((int)other.m_node), y((int)other.m_table) {}
 TwoInts002BFCF5(const TwoInts002BFCF5 &other) : x(other.x), y(other.y) {}
 ~TwoInts002BFCF5() {}
};
class Rva002BFCF5 { public: void erase(TwoInts002BFCF5); };
class Rva002BFF5A {
public:
 void rva002C004F(const char *name);
private:
 char unknown[0xAC];
 Rva00056F61 table;
};
void Rva002BFF5A::rva002C004F(const char *name) {
 if (name) {
  AsciiString key(name);
  Rva0041534BIter it = table.rva0041534B(&key);
  if (it.m_node)
   reinterpret_cast<Rva002BFCF5 *>(&table)->erase(TwoInts002BFCF5(it));
 }
}
