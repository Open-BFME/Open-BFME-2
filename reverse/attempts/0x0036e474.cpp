// ?rva0036E474@Rva0036ListOwner@@QAEXVRva0036E474Ref@@@Z
// partial score=0.85 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva0036E474@Rva0036ListOwner@@QAEXVRva0036E474Ref@@@Z @0x0036E474 83B
// EH functor sweep (parked here while its try-shape is worked out; siblings
// 0x0036DC46/0x0036D6B4 stay home). See the home TU for the family note.

typedef unsigned int UnsignedInt;
#define NULL 0

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};

struct RvaListNode
{
	RvaListNode *m_next;
	char m_pad04[4];
	void *m_payload; // +0x08
};

class Rva0057CC15Op;

class Rva0036E474Ref
{
public:
	bool invoke(int a);
	~Rva0036E474Ref() {}
	Rva0057CC15Op *m_op;
};

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class Rva0036ListOwner
{
public:
	void rva0036E474(Rva0036E474Ref ref);

private:
	char m_pad00[4];
	RvaListNode *m_head; // +0x04
};

// ?rva0036E474@Rva0036ListOwner@@QAEXVRva0036E474Ref@@@Z, retail 0x0036E474, 83 bytes.
void Rva0036ListOwner::rva0036E474(Rva0036E474Ref ref)
{
	if (ref.m_op != NULL) {
		for (RvaListNode *node = m_head->m_next; node != m_head; node = node->m_next) {
			if (!ref.invoke((int)node->m_payload))
				break;
		}
	}
	ReleaseTreeHintRef00217D4C((struct TargetRef00217D4C *)ref.m_op);
}
