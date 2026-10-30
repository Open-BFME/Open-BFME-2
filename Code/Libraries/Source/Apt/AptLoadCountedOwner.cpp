// Native006D25C0..006D2850 RET16, full656B. WB AptLoad is a semantic guide.
// Target counted-owner/list offsets and relocation/state checks come from retail.
// The list remover is the owned92B 006CFFE0 body, visible for compiler scheduling.
// cl: /MD /EHsc
void __debugbreak();
#pragma intrinsic(__debugbreak)
extern void (__cdecl*g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern void*g_aptFreeConstantTableSlot;
class Rva006DB270{public:void freeBlock(void*,int);};
extern Rva006DB270*g_pChainBlockAllocator;
class Rva006D0280{public:int m_useCount;int unused4;void*name8;int typeC;void*argument10;void*object14;void*buffer18;~Rva006D0280(); __forceinline void setData(void*a,void*b,void*c){argument10=a;object14=b;buffer18=c;} __forceinline int getState()const{return typeC;}};
__forceinline static int dec(int*p){return --*p;}
class Rva006D07E0Key{public:Rva006D0280*m_object;
 Rva006D07E0Key(Rva006D0280*p=0):m_object(p){if(p)++p->m_useCount;}
 Rva006D07E0Key(const Rva006D07E0Key&o):m_object(o.m_object){if(m_object)++m_object->m_useCount;}
 ~Rva006D07E0Key(){Rva006D0280*releasedFile=m_object;if(releasedFile&&dec(&releasedFile->m_useCount)==0){releasedFile->Rva006D0280::~Rva006D0280();g_pChainBlockAllocator->freeBlock(releasedFile,0x1c);}}
};
class Rva008951B0Node{public:Rva006D0280*entry;Rva008951B0Node*next;};
class Rva008951B0Handle{public:Rva008951B0Node*node;};
class Rva008951B0Owner{public:Rva008951B0Node*head;void eraseAfter(const Rva008951B0Handle&);void rva006CFFE0(const Rva008951B0Handle&);void rva006D25C0(Rva006D07E0Key,void*,void*,void*);};
class Rva006D1D10{public:void update(Rva006D07E0Key,Rva006D07E0Key);};
class AptLinker;extern AptLinker*g_bfmeAptLinkerAtE176F8;
class Rva006E58D0{public:void rva006E58D0Body(void*,void*,void*);};
struct ConstFile{char pad[0x14];Rva006E58D0*mainCharacter;};
#define CHECK(c,s,l) if(!(c)){g_bfmeAptAssertAtE17734(s,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptLoad.cpp",l);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
inline __declspec(noinline) void Rva008951B0Owner::rva006CFFE0(const Rva008951B0Handle &h)
{
	Rva008951B0Node *target = h.node;
	Rva008951B0Node *cur = head;
	if (target == cur) {
		if (!cur)
			return;
		Rva008951B0Node *next = cur->next;
		g_pChainBlockAllocator->freeBlock(cur, 8);
		head = next;
		return;
	}
	while (cur) {
		if (cur->next == target)
			break;
		cur = cur->next;
	}
	Rva008951B0Node *victim = cur->next;
	if (victim) {
		cur->next = victim->next;
	}
	g_pChainBlockAllocator->freeBlock(victim, 8);
}

void Rva008951B0Owner::rva006D25C0(Rva006D07E0Key key,void*data,void*constant,void*buffer){
 if(!data)return;
 for(Rva008951B0Node*node=head;node;node=node->next){
  Rva006D07E0Key other(node->entry);
  if(other.m_object->argument10!=(void*)0xcccccccc && data==other.m_object->argument10 && other.m_object!=key.m_object){
   ((Rva006D1D10*)g_bfmeAptLinkerAtE176F8)->update(key,other);
   Rva008951B0Handle i={head};
   for(;i.node;i.node=i.node->next){
    Rva006D07E0Key found(i.node->entry);
    if(found.m_object==key.m_object){rva006CFFE0(i);break;}
   }
   return;
  }
 }
 CHECK(key.m_object->getState()==2,"f->GetState() == AptFile::WaitingForData",293);
 key.m_object->typeC=3;
 ConstFile*constFile=(ConstFile*)constant;
 CHECK((unsigned)constFile->mainCharacter<0xfffff,"(unsigned)pConstFile->pMainCharacter < 0xfffff",299);
 if(constFile->mainCharacter)constFile->mainCharacter=(Rva006E58D0*)((char*)constFile->mainCharacter+(unsigned)data);
 ((Rva006E58D0*)((char*)constFile->mainCharacter+8))->rva006E58D0Body(data,constFile,buffer);
 key.m_object->setData(data,constFile->mainCharacter,buffer);
 if(constFile->mainCharacter)constFile->mainCharacter=(Rva006E58D0*)((char*)constFile->mainCharacter-(unsigned)data);
 ((void(__cdecl*)(void*))g_aptFreeConstantTableSlot)(constFile);
}

// Native6CFFB0..6CFFD3 RET4: erase the node after the handle's node, the same
// unlink-and-free tail the rowed remover 0x006CFFE0 ends with (an 8-byte node
// back to the chain-block pool, freed even when null). The receiver is not
// read. Retail re-reads the link through the handle (mov edx,ecx then
// [edx+4]); naming the victim for the unlink loses that copy. Address name.
void Rva008951B0Owner::eraseAfter(const Rva008951B0Handle &h)
{
	Rva008951B0Node *victim = h.node->next;
	if (h.node->next)
		h.node->next = h.node->next->next;
	g_pChainBlockAllocator->freeBlock(victim, 8);
}

// Native6D2850..6D2872 RET4, directly after the RET16 of rva006D25C0: is the
// pointer inside the block's payload, which starts at +0x0C and spans the
// +0x04 total minus the +0x08 field. Address name and field names.
class Rva006D2850Block{public:int m_0;unsigned m_total;unsigned m_used;char m_data[1];bool contains(const void*)const;};
bool Rva006D2850Block::contains(const void *p) const
{
	if (p >= m_data && p < m_data + (m_total - m_used))
		return true;
	return false;
}
