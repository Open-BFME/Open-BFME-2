// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

// ??1Rva0041F760@@QAE@XZ, retail 0x0041F760, 245 bytes. Non-virtual dtor:
// custom-deletes the StringBase pointer array at +4 then erases three vectors
// plus auto-destroys two AsciiString vectors at +0x8C/+0x98 two MallocPtrs at
// +0x54/+0x60 three AsciiStrings at +0/+0x24/+0x28 and the voidptr vector.
// Target evidence: releaseBuffer row 0x36410 plus operator delete 0x2FD60 plus
// voidptr erase 0x31BD55 plus AsciiString erase 0x2CCFC plus AsciiString vector
// dtor 0x2CC70 plus free 0x30830; deleting-dtor-shaped caller at 0x0041F855.
// Precedents: Rva00416088Dtor plus StlportAsciiStringVectorDtor.

#include <vector>

#include "ascii_string.h"


extern "C" void __cdecl free(void *block);
void __cdecl operator delete(void *block);

struct Rva0041F760FreePtr
{
	char *m_p;
	~Rva0041F760FreePtr()
	{
		if (m_p != 0)
			free(m_p);
	}
};

class ArmyDefinition
{
public:
	~ArmyDefinition();
	void *rva0041F855(unsigned int flags);
private:
	AsciiString m_00;
	_STL::vector<void *, _STL::allocator<void *> > m_04;
	char m_pad10[0x14];
	AsciiString m_24;
	AsciiString m_28;
	char m_pad2C[0x28];
	Rva0041F760FreePtr m_54;
	char m_pad58[0x8];
	Rva0041F760FreePtr m_60;
	char m_pad64[0x28];
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_8C;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_98;
};

ArmyDefinition::~ArmyDefinition()
{
	for (_STL::vector<void *, _STL::allocator<void *> >::iterator it = m_04.begin(); it != m_04.end(); ++it)
	{
		void *elem = *it;
		if (elem != 0)
			delete (AsciiString *)elem;
	}
	_STL::vector<void *, _STL::allocator<void *> > *pv04 = &m_04;
	pv04->erase(pv04->begin(), pv04->end());
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > *pv8C = &m_8C;
	pv8C->erase(pv8C->begin(), pv8C->end());
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > *pv98 = &m_98;
	pv98->erase(pv98->begin(), pv98->end());
}

void *ArmyDefinition::rva0041F855(unsigned int flags)
{
	this->~ArmyDefinition();
	if (flags & 1)
		operator delete(this);
	return this;
}
