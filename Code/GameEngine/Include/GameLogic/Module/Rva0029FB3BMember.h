// Target facts: retail 0x0029FB3B initializes only the sentinel pointer at +0 through 0x0014F3C4, links the node at +0/+4, and returns this (ret 4); 0x0026549E drains and relinks that sentinel. No virtual functions or vtable stores occur in this class.
// Retail 0x00331EAD constructs it at record+8; 0x00332926 advances those records by 12, proving sizeof 4 with no separate parent storage. The node pool is VA 0x00DA60E8 and its free head is VA 0x00DA60F0 (0x002393FE, 0x00268911); 0x00490A89/0x00490A8F tests head->next == head inline.
// Retail 0x002A12A5 is the void-pointer constructor wrapper calling 0x0029FB3B; 0x00490B64 calls the allocator-reference constructor at 0x0029FB3B, and 0x00490C7B calls the nonvirtual destructor at 0x00268902. Lifetimes remain declared out of line.

#pragma once

struct Rva0029FB3BAlloc;

class Rva0029FB3BMember
{
public:
	Rva0029FB3BMember(void *context);
	Rva0029FB3BMember(const Rva0029FB3BAlloc &alloc);
	~Rva0029FB3BMember() throw();

	void *init(void *context);
	void reset();
	bool empty() const { return *(void *const *)m_head == m_head; }

	void *m_head;
};

typedef char Rva0029FB3BMemberSizeCheck[sizeof(Rva0029FB3BMember) == 4 ? 1 : -1];
