// cl: /O2 /G6 /MD /EHsc /DNDEBUG
class Rva006DB270 { public: void freeBlock(void *, int); };
extern Rva006DB270 *g_pChainBlockAllocator;
// The independent EAStringC providers prove the 4-byte string ABI used
// by the 6D0660 comparison: C-string ctor6D4C80 equal6D3090 dtor6D3010.
class EAStringC {
public:
 EAStringC(const char *);
 ~EAStringC();
 bool IsEqualTo(const EAStringC *) const;
 void *data;
};
struct Rva006D0280 {
 ~Rva006D0280();
 int m_useCount;
 int unknown4;
 EAStringC name8;
};
class Rva006D07E0Key {
public:
 Rva006D07E0Key(const Rva006D07E0Key &other) {
  Rva006D0280 *p=other.m_object;
  m_object=p;
  if(p) ++p->m_useCount;
 }
 ~Rva006D07E0Key() {
  Rva006D0280 *p=m_object;
  if(p && --p->m_useCount==0) {
   p->~Rva006D0280();
   g_pChainBlockAllocator->freeBlock(p,0x1c);
  }
 }
 Rva006D0280 *m_object;
};
struct Rva006D07E0Entry { int unknown0; Rva006D0280 *key4; };
struct Rva006D07E0Node { Rva006D07E0Entry *entry; Rva006D07E0Node *next; };
struct Rva006D07E0Iterator {
 Rva006D07E0Iterator(Rva006D07E0Node *p):node(p) {}
 Rva006D07E0Iterator &operator++(){node=node->next;return *this;}
 bool operator!=(const Rva006D07E0Iterator&o)const{return node!=o.node;}
 Rva006D07E0Entry *operator->()const{return node->entry;}
 Rva006D07E0Node *node;
};
class Rva006D07E0List {
public:
 Rva006D07E0Iterator find(Rva006D07E0Key key);
 int contains(Rva006D07E0Key key);
 Rva006D07E0Node *head;
};
// Native Ghidra6D0660..6D0766; comparator called by6D0860 with
// counted owner key. The provider is at14; its string table is28/2c
// with10-byte stride (hex). All offsets are target facts; purpose and
// original owner/table names are unknown.
struct Rva006D0660Record { const char *text; char unknown4[12]; };
struct Rva006D0660Table {
 char unknown0[0x28];
 int count28;
 Rva006D0660Record *records2c;
};
class Rva006D0660 {
public:
 int contains(Rva006D07E0Key key);
 char unknown0[0x14];
 Rva006D0660Table *table14;
};
// Native6D0860..6D092B. BFME1 ba7ddda7 Rva008956C0Contains.cpp
// supplies the outer search and by-value handle lifetime guide. Target
// has a28-byte pooled key instead of the donor's24-byte heap key.
// The reinterpretation at entry4 is the exact receiver load in retail;
// Rva006D0280 and Rva006D0660 are partial address-derived ABI views.
int Rva006D07E0List::contains(Rva006D07E0Key key) {
 for(Rva006D07E0Iterator it(head);it!=Rva006D07E0Iterator(0);++it){
  if(((Rva006D0660*)it->key4)->contains(key))return 1;
 }
 return 0;
}
