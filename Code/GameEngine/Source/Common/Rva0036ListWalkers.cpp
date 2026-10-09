// cl: /O1 /DNDEBUG /MD /EHsc
//
// Three +0x04 list walkers sharing one owner (list head at +0x04, node
// next at +0x00, payload at +0x08), landed as a homogeneous batch.
// The owner's real class name remains unknown; the raw member-list
// ABI is established independently by each retail walk.
//
// ?rva0036DC46@Rva0036ListOwner@@QAEXH@Z @0x0036DC46 41B
// Walks the list and calls the g_00A027B8 slot26 virtual on each node's
// +8 payload. The int argument is unused (ret 4). Advances before the
// call (deletion-safe).
//
// ?rva0036D6B4@Rva0036ListOwner@@QAEXXZ @0x0036D6B4 64B
// Walks the list; treats each +8 payload as Object (rowed rva0028AD32),
// then follows its +0x250 interface (vslot 0x7C) and, when non-null,
// that result's vslot 0xD0.
//

typedef unsigned int UnsignedInt;
#define NULL 0

// Native36E474..36E4C7 RET4 consumes a one-word callback reference.
// Native AL test proves a byte-result ABI; Object payloads are established
// by sibling36D6B4. Ref invoke57CC15 has the same complete46B/relocations
// as the old void/int functor owner. The actual template/type name is unknown.
// Guarded intrusive release uses the rowed fastcall7DEEF helper. Early-null
// return lets MSVC place the parameter cleanup inside the native live arm.
class Object;
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
class FunctorNotSet {public: FunctorNotSet(); virtual ~FunctorNotSet(); private: char pad[8];};
class Rva0036E474Op {public: virtual ~Rva0036E474Op(); virtual unsigned char invoke(Object*);};
class Rva0036E474Ref {
public:
 unsigned char invoke(Object*) const;
 Rva0036E474Ref(const Rva0036E474Ref&); // caller-side copying is not recovered here
 ~Rva0036E474Ref() {if(m_op) ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)m_op);}
 Rva0036E474Op* m_op;
};
unsigned char Rva0036E474Ref::invoke(Object*obj) const {Rva0036E474Op*op=m_op;if(!op)throw FunctorNotSet();return op->invoke(obj);}

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};

class Rva00A027B8
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26(void *arg);
};

// Project data ledger binds RVA A027B8 to the defined BuildAssistant global.
// Keep the observed slot26 interface view until its method identity is recovered.
extern class BuildAssistant *TheBuildAssistant;

class Rva0036D6B4Ret : public VSlots<52>
{
public:
	virtual void slotD0();
};

class Rva0036D6B4Iface : public VSlots<31>
{
public:
	virtual Rva0036D6B4Ret *slot7C();
};

class Object
{
public:
	void rva0028AD32();
	unsigned char m_pad00[0x250];
	Rva0036D6B4Iface *m_250; // +0x250 (unproven; positional)
};

struct RvaListNode
{
	RvaListNode *m_next;
	char m_pad04[4];
	void *m_payload; // +0x08
};

class Rva0036ListOwner
{
public:
	void rva0036E474(Rva0036E474Ref ref);
	void rva0036DC46(int unused);
	void rva0036D6B4();

private:
	char m_pad00[4];
	RvaListNode *m_head; // +0x04
};

// ?rva0036DC46@Rva0036ListOwner@@QAEXH@Z, retail 0x0036DC46, 41 bytes.
void Rva0036ListOwner::rva0036DC46(int unused)
{
	(void)unused;
	RvaListNode *node = m_head->m_next;
	while (node != m_head) {
		RvaListNode *cur = node;
		node = node->m_next;
		((Rva00A027B8*)TheBuildAssistant)->slot26(cur->m_payload);
	}
}

// ?rva0036D6B4@Rva0036ListOwner@@QAEXXZ, retail 0x0036D6B4, 64 bytes.
void Rva0036ListOwner::rva0036D6B4()
{
	for (RvaListNode *node = m_head->m_next; node != m_head; node = node->m_next) {
		Object *o = (Object *)node->m_payload;
		o->rva0028AD32();
		Rva0036D6B4Iface *ifc = o->m_250;
		if (ifc != NULL) {
			Rva0036D6B4Ret *r = ifc->slot7C();
			if (r != NULL)
				r->slotD0();
		}
	}
}

void Rva0036ListOwner::rva0036E474(Rva0036E474Ref ref) {
 if(!ref.m_op)return; {
  for(RvaListNode*node=m_head->m_next;node!=m_head;node=node->m_next) {
   if(!ref.invoke((Object*)node->m_payload))break;
  }
 }
}
