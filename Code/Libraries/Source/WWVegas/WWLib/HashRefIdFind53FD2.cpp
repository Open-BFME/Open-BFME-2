// ?find@Rva00053FD2@@QBEPAURva00053FD2Node@@PAURva00053FD2Key@@@Z
// cl: /O1 /DNDEBUG /MD
// Native 0x00053FD2: reference-id hash at +8, bucket span at +4/+8,
// linked nodes next/key at +0/+4; no original class identity is asserted.
// The existing 0x00050E1C provider ignores ECX and returns with RET 8.
// Its stdcall address is viewed through MSVC's four-byte single-inheritance
// member-pointer ABI to retain retail's unused receiver (this+1). This is a
// target ABI view, not a second provider name or an original comparator type.
// Borrowed volatile bucket-pointer access preserves the post-DIV reload;
// the retail object's original volatile qualification remains unknown.
struct Rva00053FD2Ref
{
	int m_pad0;
	int m_pad4;
	int m_id;
};

struct Rva00053FD2Key
{
	Rva00053FD2Ref *m_ref;
};

struct Rva00053FD2Node
{
	Rva00053FD2Node *m_next;
	Rva00053FD2Ref *m_key;
};

bool __stdcall Rva00050E1CEqual(const void*,const void*);
class Rva00053FD2EqView {};
union Rva00053FD2EqCall {
 bool(__stdcall *plain)(const void*,const void*);
 bool(Rva00053FD2EqView::*member)(const void*,const void*)const;
};
typedef char Rva00053FD2MemberPointerMustBeFourBytes[
 sizeof(bool(Rva00053FD2EqView::*)(const void*,const void*)const)==4?1:-1];

class Rva00053FD2
{
	int m_pad0;
	Rva00053FD2Node **m_first;
	Rva00053FD2Node **m_last;
	int m_padC;
	int m_count;
public:
	
	Rva00053FD2Node *find(Rva00053FD2Key *key) const;
};

Rva00053FD2Node *Rva00053FD2::find(Rva00053FD2Key *key) const
{
	unsigned hash;

	Rva00053FD2Ref *ref = key->m_ref;
	if (ref == 0)
		hash = 0;
	else
		hash = ref->m_id;
	unsigned count = (unsigned)(m_last - m_first);
	unsigned slot = hash % count;
	Rva00053FD2Node *node = (*(Rva00053FD2Node **const volatile *)&m_first)[slot];
	Rva00053FD2EqCall eq;
	eq.plain = Rva00050E1CEqual;
	while (node != 0)
	{
		if ((((const Rva00053FD2EqView *)((const char*)this+1))->*eq.member)(node->m_key,ref))
			break;
		node = node->m_next;
	}
	return node;
}
