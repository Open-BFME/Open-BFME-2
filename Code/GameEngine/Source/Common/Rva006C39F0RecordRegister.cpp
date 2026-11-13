// cl: /DNDEBUG /MD
//
// ?rva006C39E0@Rva006C1F60@@QAEXXZ @ 0x006C39E0 10B, ret
// ?rva006C39F0@Rva006C39F0Owner@@QAE_NIIIPAX@Z @ 0x006C39F0 191B, ret 0x10
//
// 0x006C39E0: unreferenced forwarder that runs the debug allocator's
// delayed-free purge (0x006C33D0) with policy 0 and limit 0; the receiver
// passes through in ecx.
//
// 0x006C39F0: registers an external debug record for a block. With external
// records enabled (+0x680), a key already present in the +0x684 hash keeps
// its record and the call succeeds. Otherwise the caller's record is used,
// or, when it passes none and a non-zero size, a fresh record of that size is
// allocated through 0x006C3940 with its 16-bit total size in the first word
// and a zero terminator word at its end. The record is inserted under the key
// (0x006C21C0); a record this call allocated is released again (0x006C1A50)
// when the insert fails. Returns true on the disabled and found paths and on
// a successful insert.
//
// Evidence: retail body and WorldBuilder's unoptimized twin at 0x0070CD80,
// which carries the asserts "bAllowDuplicate || !bResult" and
// "pDebugBlock || (nDebugBlockSize >= sizeof(DebugDataLengthType))": arg1 is
// the hash key (block address), arg2 the record size, arg3 the record
// pointer, arg4 the allow-duplicate flag retail only reads in that assert.
// WB's hash lookup (0x00708A80) is inlined here. The third parameter keeps
// the unsigned spelling of the pinned name the rowed caller 0x006C3D30 uses.
// Names are address-derived; the original names are not established.

#include "../../Include/Common/Rva006C1F60.h"

void Rva006C1F60::rva006C39E0()
{
	rva006C33D0(0, 0);
}

#include "../../Include/Common/Rva006C17B0Node.h"

class Rva006C17B0
{
public:
	bool rva006C21C0(unsigned int key, void *value);
	__forceinline bool contains(unsigned int key) const
	{
		if (m_table) {
			Rva006C17B0Node *node = m_table[(key >> 3) % m_bucketCount];
			while (node) {
				if (node->m_key == key)
					return true;
				node = node->m_next;
			}
		}
		return false;
	}
private:
	Rva006C17B0Node **m_table;
	bool m_flag;
	char m_pad05[3];
	unsigned int m_bucketCount;
};

class Rva006C1A50Owner
{
public:
	void rva006C1A50(int record);
};

class Rva006C39F0Owner
{
public:
	void *rva006C3940Alloc(unsigned int size);
	bool rva006C39F0(unsigned int key, unsigned int size, unsigned int record, void *allowDuplicate);
private:
	unsigned char m_pad0[0x680];
	bool m_externalRecords;
	unsigned char m_pad681[3];
	Rva006C17B0 m_records;
};

bool Rva006C39F0Owner::rva006C39F0(unsigned int key, unsigned int size, unsigned int record, void *)
{
	bool result = true;
	if (m_externalRecords) {
		if (!m_records.contains(key)) {
			result = false;
			bool created = false;
			if (record == 0 && size != 0) {
				record = (unsigned int)rva006C3940Alloc(size);
				if (record != 0) {
					*(unsigned short *)record = (unsigned short)size;
					*(unsigned short *)(record + size - 2) = 0;
					created = true;
				}
			}
			if (record != 0) {
				if (m_records.rva006C21C0(key, (void *)record))
					result = true;
				else if (created)
					((Rva006C1A50Owner *)this)->rva006C1A50((int)record);
			}
		}
	}
	return result;
}
