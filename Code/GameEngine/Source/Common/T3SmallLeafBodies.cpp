// cl: /DNDEBUG /MD /EHs-c-
// Leaf bodies carrying no relocation (trimmed to the placed 63E50 less-than
// body; the other seven are declared-only here).

typedef int Int;
typedef unsigned int UnsignedInt;

Int __stdcall Rva000695C0Less(const void *a, const void *b);
Int __stdcall Rva000699A0Less(const void *a, const void *b);
Int __stdcall Rva00069AD0Less(const void *a, const void *b);
Int __stdcall Rva00069B50Less(const void *a, const void *b);
void Rva00069520Swap(float &a, float &b);

// the unsigned key compared at +0x18
class Rva00063E50Node
{
public:
	Int isLessThan(const Rva00063E50Node *other) const;

private:
	unsigned char m_unreconstructed_00[0x18];
	UnsignedInt m_key;									///< retail this+0x18
};

// ?isLessThan@Rva00063E50Node@@QBEHPBV1@@Z
Int Rva00063E50Node::isLessThan(const Rva00063E50Node *other) const
{
	return m_key < other->m_key;
}

