// PoolMember: canonical declarations for the members units call through private views of it.
// Retail 0x00268902 reads the pointer at +0 and 0x0026E1DE steps 12-byte records holding it at +8 (size 4).
// Retail 0x0049122C (a /GX destructor) calls 0x00268902 with no EH state around it, so it is throw().
#ifndef CANONICAL_POOLMEMBER_H
#define CANONICAL_POOLMEMBER_H

class PoolMember
{
public:
	void Rva00268902() throw();
	void Rva0050ED3();

private:
	void *m_head;
};

#endif // CANONICAL_POOLMEMBER_H
