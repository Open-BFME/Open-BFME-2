// ?update@Rva006D1D10@@QAEXVRva006D07E0Key@@0@Z
// partial score=0.8380635624538064 date=2026-10-09
// cl: /MD /EHsc
class Rva006DB270 {public:void freeBlock(void*,int);};
class Rva006DB160 {public:void *allocBlock(int);};
extern Rva006DB270*g_pChainBlockAllocator;
struct Rva006D0280 {void teardown();int m_useCount;};
class Rva006D07E0Key {public:__forceinline static int dec(int*p){return --*p;}
 Rva006D07E0Key(Rva006D0280*p=0):m_object(p){if(p)++p->m_useCount;}
 Rva006D07E0Key(const Rva006D07E0Key&key):m_object(key.m_object){if(m_object)++m_object->m_useCount;}
 ~Rva006D07E0Key(){Rva006D0280*r=m_object;if(r&&dec(&r->m_useCount)==0){Rva006D0280*p=m_object;if(p){p->teardown();g_pChainBlockAllocator->freeBlock(p,0x1c);}}}
 Rva006D0280*m_object;
};
class Rva006D0790 {public:
 Rva006D0790(Rva006D07E0Key,void*);
 static void *operator new(unsigned size){return ((Rva006DB160*)g_pChainBlockAllocator)->allocBlock(size);}
 static void operator delete(void*p){g_pChainBlockAllocator->freeBlock(p,0x10);}
 int count;Rva006D07E0Key key;void *name;bool flag;
};
class Rva006D0790Ref {public:__forceinline static int dec(int*p){return --*p;}
 Rva006D0790Ref(Rva006D0790*p):ptr(p){if(p)++p->count;}
 ~Rva006D0790Ref(){Rva006D0790*p=ptr;if(p&&dec(&p->count)==0){p->key.~Rva006D07E0Key();g_pChainBlockAllocator->freeBlock(p,0x10);}}
 Rva006D0790*ptr;
};
class BfmeNodeVMU {public:Rva006D0790 *entry;BfmeNodeVMU *next;};
class BfmeListVMU {public:void bfmeEraseVMU(BfmeNodeVMU**);BfmeNodeVMU*head;};
struct Rva006D07E0Iterator {Rva006D07E0Iterator(BfmeNodeVMU*p):node(p){} BfmeNodeVMU*node;};
class Rva006D07E0List {public:Rva006D07E0Iterator find(Rva006D07E0Key);BfmeNodeVMU*head;};
class Rva006D1450 {public:void intern(Rva006D07E0Key);};
struct Rva006D1D10Node: BfmeNodeVMU {Rva006D1D10Node(const Rva006D0790Ref&r){entry=r.ptr;if(entry)++entry->count;next=0;}
 static void*operator new(unsigned size){return ((Rva006DB160*)g_pChainBlockAllocator)->allocBlock(size);}
 static void operator delete(void*p){g_pChainBlockAllocator->freeBlock(p,8);}
};
class Rva006D1D10 {public:
 BfmeNodeVMU*head;
 void prepend(const Rva006D0790Ref&r){BfmeNodeVMU*n=new Rva006D1D10Node(r);n->next=head;head=n;}
 void update(Rva006D07E0Key first,Rva006D07E0Key second);
};
void Rva006D1D10::update(Rva006D07E0Key first,Rva006D07E0Key second){
 ((Rva006D1450*)this)->intern(second);
 Rva006D0790Ref found(((Rva006D07E0List*)this)->find(first).node->entry);
 void*name=found.ptr->name;
 BfmeNodeVMU*node=head;
 while(node){if(node->entry->name==name)break;node=node->next;}
 if(!node){Rva006D0790Ref item(new Rva006D0790(first,name));prepend(item);}
 else{BfmeNodeVMU*erase=node;((BfmeListVMU*)this)->bfmeEraseVMU(&erase);Rva006D0790Ref item(new Rva006D0790(first,name));prepend(item);}
}
