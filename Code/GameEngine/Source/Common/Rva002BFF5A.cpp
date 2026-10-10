// cl: /O1 /arch:SSE /G7 /Oy- /MD /EHsc /Ireference/shims/bfme2_ascii
// Ghidra 2BFF5A..2BFF9F RET4. This is an opaque table search; the
// original class and table specialization remain unresolved. Target bytes
// establish table+AC, node payload+8, embedded OVERRIDE-like view+8 and key+10.
#include "ascii_string.h"

class Rva003FA835;
struct Rva002BFFD4Template {void *primary;AsciiString name;};
class Rva000411084 {
public:
    void *next();
    void *current;
    void *owner;
};
class Rva000427195 {
public:
    void *first(Rva000411084 *);
};
struct Rva002BFF5AData { char unknown[0x10]; int key; };
class Rva0035C95FView {
public:
    const Rva002BFF5AData *rva0035C95F() const;
    void *head;
};
struct Rva002BFF5AEntry { char unknown[8]; Rva0035C95FView version; };
struct Rva002BFF5ANode { void *next; void *key; Rva002BFF5AEntry *value; };
class Rva002BFF5A {
public:
    Rva002BFF5AEntry *rva002BFF5A(int key);
    void rva002BFF9F();
    void rva002BFFD4(Rva002BFFD4Template *,int kind,unsigned word);
private:
    char unknown[0xac];
    Rva000427195 table;
};
Rva002BFF5AEntry *Rva002BFF5A::rva002BFF5A(int key)
{
    Rva000411084 it;
    table.first(&it);
    while (it.current) {
        Rva002BFF5ANode *node = static_cast<Rva002BFF5ANode *>(it.current);
        if (node->value->version.rva0035C95F()->key == key)
            return node->value;
        it.next();
    }
    return 0;
}

// Complete 0x24-byte target view from the owned 166B constructor unit.
class LocomotorTemplate;
template<class T> class OVERRIDE {public:OVERRIDE():head(0) {} const T *head;const T *operator->()const;};
struct Rva00539926Base {unsigned references;Rva00539926Base():references(0) {} virtual ~Rva00539926Base();};
class Rva003FA835 : public Rva00539926Base
{
public:
 Rva003FA835(int kind,void *target,unsigned word);
 virtual ~Rva003FA835() {}
 void rva003FA878();
 void rva003FA781(int enabled);void rva003FA7D3(int enabled);void rva003FA705(void*,float);
private:
 OVERRIDE<LocomotorTemplate> m_template;
 unsigned m_unknown0C;void *m_target;bool m_enabled;char m_pad15[3];
 float m_elapsed,m_unknown1C,m_20;
};
typedef char Effect24Size[sizeof(Rva003FA835)==0x24 ? 1 : -1];
class Rva00056F61;
struct Rva0041534BIter {void *m_node;Rva00056F61 *m_table;};
class Rva00056F61 {public:Rva0041534BIter rva0041534B(const AsciiString*);};
struct TargetRef00217D4C;
class Rva002BED91 {public:void set(TargetRef00217D4C*);};
struct TreeHintRef002BF0D6 {
 TargetRef00217D4C *value;
};
class Rva002BFC59 {public:TreeHintRef002BF0D6 &rva002BFC59(const AsciiString&);};
// Native2BFFD4..2C004F RET12; find by template name+4, create36B counted
// effect only for an absent key, then attach it through the existing holder.
void Rva002BFF5A::rva002BFFD4(Rva002BFFD4Template *entry,int kind,unsigned word)
{
 if(entry) {
  Rva0041534BIter found=((Rva00056F61*)&table)->rva0041534B(&entry->name);
  if(!found.m_node) {
   ((Rva002BED91*)&((Rva002BFC59*)&table)->rva002BFC59(entry->name))->set((TargetRef00217D4C*)new Rva003FA835(kind,entry,word));
  }
 }
}

// Complete native53B2BFF9F..2BFFD4 RET0; same tableAC and node payload8
// as the owned lookup above. The optional value is the36B glow object
// established by this unit's creation path; its359B tick is now owned.
void Rva002BFF5A::rva002BFF9F()
{
 Rva000411084 it;
 table.first(&it);
 while(it.current) {
  Rva002BFF5ANode* node=static_cast<Rva002BFF5ANode*>(it.current);
  if(node->value) reinterpret_cast<Rva003FA835*>(node->value)->rva003FA878();
  it.next();
 }
}
