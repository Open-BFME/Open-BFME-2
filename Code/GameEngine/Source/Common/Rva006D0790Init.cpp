// Native70B at6D0790 RET8 initializes count0 counted key4 borrowed name8 and flagC.
// Call6D1DCE follows16B pool allocation and constructs a copied counted argument.
// Rename the prior raw-pointer initializer view to its C++ constructor ABI;
// exact body unchanged. Original retail class name remains unknown.
class Rva006DB270 {public:void freeBlock(void*,int);};
extern Rva006DB270 *g_pChainBlockAllocator;
struct Rva006D0280 {~Rva006D0280();int m_useCount;};
class Rva006D07E0Key {public:
 Rva006D07E0Key(Rva006D0280*p=0):m_object(p){if(p)++p->m_useCount;}
 Rva006D07E0Key(const Rva006D07E0Key&key):m_object(key.m_object){if(m_object)++m_object->m_useCount;}
 ~Rva006D07E0Key(){Rva006D0280*p=m_object;if(p&&--p->m_useCount==0){p->~Rva006D0280();g_pChainBlockAllocator->freeBlock(p,0x1c);}}
 Rva006D0280*m_object;
};
class Rva006D0790 {public:Rva006D0790(Rva006D07E0Key,void*);int count;Rva006D07E0Key key;void *name;bool flag;};
Rva006D0790::Rva006D0790(Rva006D07E0Key p,void*q):count(0),key(p),name(q),flag(false){}
