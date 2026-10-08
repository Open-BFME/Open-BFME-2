// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
// ?rva000EE198@Rva000EE198Owner@@QAEXXZ @0x000EE198 107B: release every ref-counted
// slot of a 0x30-stride array (count at +0x2EE04, reset to 0), then release the
// 0x60 ref+AsciiString pairs at +0x2EE18 (stride 0x18), then clear the flag at
// +0x2F718. Ref release is dec [obj+4] then virtual slot 0 when it reaches zero.
#include "ascii_string.h"

class Rva000EE198Ref
{
public:
	virtual void rva000EE198Free();
	int m_refs;
};

struct Rva000EE198Entry
{
	Rva000EE198Ref *m_ref;
	char m_pad04[0x30 - 4];
};

struct Rva000EE198Pair
{
	Rva000EE198Ref *m_ref;
	AsciiString m_name;
	char m_pad08[0x18 - 8];
};

class Rva000EE198Owner
{
public:
	void rva000EE198();

private:
	char m_pad0[4];
	Rva000EE198Entry m_entries[4000];
	int m_count;
	char m_pad2EE08[0x10];
	Rva000EE198Pair m_pairs[0x60];
	int m_flag;
};

// ?rva000EE198@Rva000EE198Owner@@QAEXXZ @0x000EE198
void Rva000EE198Owner::rva000EE198()
{
	for (int i = 0; i < m_count; ++i) {
		Rva000EE198Ref *ref = m_entries[i].m_ref;
		if (ref) {
			if (--ref->m_refs == 0) {
				ref->rva000EE198Free();
			}
			m_entries[i].m_ref = 0;
		}
	}
	m_count = 0;
	int n = 0x60;
	Rva000EE198Pair *pair = m_pairs;
	do {
		Rva000EE198Ref *ref = pair->m_ref;
		if (ref) {
			if (--ref->m_refs == 0) {
				ref->rva000EE198Free();
			}
			pair->m_ref = 0;
		}
		pair->m_name.~AsciiString();
		++pair;
	} while (--n);
	m_flag = 0;
}
