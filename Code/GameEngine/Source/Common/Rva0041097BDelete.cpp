// cl: /O1 /MD
//
// ?rva0041097B@Rva0041097B@@QAEXPAX@Z, retail 0x0041097B, 28 bytes. Chain lane:
// hashtable node delete for Rva004104C9 value (val at +4). Destroys val via
// rowed ??1Rva004104C9@@QAE@XZ then frees node via rowed _free. Callers
// 0x00410A3D and 0x00410AC7 are hashtable clear/iterator-erase bodies (push node; mov ecx tbl).
class Rva004104C9
{
public:
	~Rva004104C9();
};

extern "C" void __cdecl free(void *p);

struct Rva0041097BNode
{
	void *_M_next;
	Rva004104C9 _M_val;
};

class Rva0041097B
{
public:
	void rva0041097B(void *p);
	void rva00410AC7Erase(const void *iterator);
private:
	void *unknown00;
	Rva0041097BNode **buckets;
	Rva0041097BNode **endBuckets;
	unsigned unknown0c;
	unsigned count;
};

void Rva0041097B::rva0041097B(void *p)
{
	((Rva0041097BNode *)p)->_M_val.~Rva004104C9();
	if (p)
		free(p);
}

// Native Ghidra410AC7/80 erases the exact iterator node from a bucket chain.
// The served STLport erase in BfmeConv1292.cpp supplies the algorithm; its
// emitted helper views differ from retail and are deliberately not imported.
// Retail410AD9 calls the rowed bucketIndex223149 with node+4;410B0A calls
// this home unit's rowed node cleanup41097B. Count is the word at table+10.
// Native pair cleanup4104C9 independently proves the AsciiString at node+4.
// This view asserts the observed table/iterator ABI, no original owner name.
class AsciiString;
class Rva000427195 { public: int bucketIndex(const AsciiString *name); };
void Rva0041097B::rva00410AC7Erase(const void *iterator)
{
 Rva0041097BNode *n = *(Rva0041097BNode *const *)iterator;
 if (n) {
  const unsigned bucket = ((Rva000427195 *)this)->bucketIndex((const AsciiString *)&n->_M_val);
  Rva0041097BNode *current = buckets[bucket];
  if (current == n) {
   buckets[bucket] = (Rva0041097BNode *)current->_M_next;
   rva0041097B(current);
   --count;
  } else {
   Rva0041097BNode *next = (Rva0041097BNode *)current->_M_next;
   while (next) {
    if (next == n) {
     current->_M_next = next->_M_next;
     rva0041097B(next);
     --count;
     break;
    } else {
     current = next;
     next = (Rva0041097BNode *)current->_M_next;
    }
   }
  }
 }
}
