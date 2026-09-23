// cl: /O2 /DNDEBUG /MD
//
// ?Shutdown@INIClass@@AAEXXZ, retail 0x00616AC0, 86 bytes.
// BFME2 diverged from the BFME1 donor (which deletes SectionList,
// SectionIndex and Filename): +0x04 is a virtual-owned list deleted via
// scalar-deleting-dtor slot 0 with flag 0 fed to operator delete
// (Radar deleteInstance precedent), +0x08 is an owned index struct
// null-checked then cleared (+0x00/+0x04/+0x08/+0x10 null, byte +0x0C)
// and deleted, +0x0C is deleted via operator delete. All deletes resolve
// via rowed ??3 @0x2FD60; the virtual deleteInstance is declared-only.
// Shard (not graft) per same-TU visibility: ini.cpp carries the donor
// verbatim present-unmatched def under different flags.
class SectionListNode
{
public:
	virtual void *deleteInstance(int flag);
};
struct IndexEntry
{
	void *m_ptr00;
	int m_int04;
	int m_int08;
	unsigned char m_byte0C;
	int m_int10;
};
class INIClass
{
	void Shutdown();
private:
	unsigned char m_pad00[4];
	SectionListNode *m_sectionList;
	IndexEntry *m_sectionIndex;
	void *m_filename;
};
void __cdecl operator delete(void *);
void INIClass::Shutdown()
{
	SectionListNode *list = m_sectionList;
	::operator delete(list ? list->deleteInstance(0) : 0);
	if (IndexEntry *index = m_sectionIndex)
	{
		void *ptr = index->m_ptr00;
		delete ptr;
		index->m_ptr00 = 0;
		index->m_int04 = 0;
		index->m_int08 = 0;
		index->m_byte0C = 0;
		index->m_int10 = 0;
		delete index;
	}
	delete m_filename;
}
