// cl: /G7 /arch:SSE /Ireference/shims/bfmecamera /DNDEBUG /MD /EHs-c- /Ireference/open-bfme-1/Code/GameEngine/Source/Common
// Open-BFME-1: two small value-type bodies out of d_0001466e.asm.
//
// 0x000643C0 opens with `mov eax,ecx`, which is the constructor tell, and takes
// one argument (`ret 4`). It writes seven consecutive dwords in ASCENDING order
// -- and MSVC 7.1 does not reorder straight-line constant stores, so that is
// source order: four zeros, two copies of 0x3F000000, then the argument. The
// two 0x3F000000 stores go through ONE register loaded once, which is what says
// they are the same constant written twice rather than two unrelated values,
// and 0x3F000000 is 0.5f -- an integer move of a float constant is how MSVC 7.1
// spells a float initialiser whose bit pattern it already knows.
//
// 0x000643F0 copies three consecutive dwords out of the object into a caller
// supplied block, again in ascending order. It leaves eax alone, so it is NOT a
// by-value return through a hidden pointer (which would have to return that
// pointer) -- it is a void member taking a destination.
//
// Identity is address-derived: the offsets are what retail writes, the member
// names are the offsets.

typedef float Real;

class Rva000643C0Value
{
public:
	Rva000643C0Value(void *owner);

	Real m_real00;										///< retail this+0x00
	Real m_real04;										///< retail this+0x04
	Real m_real08;										///< retail this+0x08
	Real m_real0C;										///< retail this+0x0C
	Real m_real10;										///< retail this+0x10
	Real m_real14;										///< retail this+0x14
	void *m_owner18;									///< retail this+0x18
};

Rva000643C0Value::Rva000643C0Value(void *owner)
{
	m_real00 = 0.0f;
	m_real04 = 0.0f;
	m_real08 = 0.0f;
	m_real0C = 0.0f;
	m_real10 = 0.5f;
	m_real14 = 0.5f;
	m_owner18 = owner;
}

struct Rva000643F0Triple
{
	int m_value00;										///< block+0x00
	int m_value04;										///< block+0x04
	int m_value08;										///< block+0x08
};

class Rva000643F0Value
{
public:
	void copyTo(Rva000643F0Triple *destination) const;

	int m_value00;										///< retail this+0x00
	int m_value04;										///< retail this+0x04
	int m_value08;										///< retail this+0x08
};

// ?copyTo@Rva000643F0Value@@ present-unmatched
void Rva000643F0Value::copyTo(Rva000643F0Triple *destination) const
{
	destination->m_value00 = m_value00;
	destination->m_value04 = m_value04;
	destination->m_value08 = m_value08;
}

// Clean BF1 f98983a7d3 Common/BfmeHostESMDo.cpp emits the collision-header
// constructor as a source guide under /O1 /SSE /G6. That donor identity and
// its pointer/type interpretation are not proved for this target entry.
// Native6E27D..6E293 starts after the rowed SceneClass setter's RET4 at6E27A
// and ends with RET8 before rowed6E293. It writes raw stackwords to receiver
// words0/4, clears word8 and retains the receiver in full EAX. Both separate
// stackword loads and receiver use establish this minimum callable contract;
// RET8 alone is not the prototype evidence. No direct/literal references
// were found in all eight image sections. Original class, constructor role,
// field purpose and complete object size remain unknown. This ordinary
// consumed-prefix initializer preserves only the witnessed stores/result.
class Rva0006E27DWords
{
public:
    Rva0006E27DWords *initialize(unsigned int first, unsigned int second);
private:
    unsigned int word0, word4, word8;
};
Rva0006E27DWords *Rva0006E27DWords::initialize(unsigned int first, unsigned int second)
{
    word0 = first;
    word4 = second;
    word8 = 0;
    return this;
}
