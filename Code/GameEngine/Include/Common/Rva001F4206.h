// The cleanup at RVA 0x001F4206 reads the helper pointer at offset zero.
#ifndef CANONICAL_RVA001F4206_H
#define CANONICAL_RVA001F4206_H

struct Rva001F4206Helper;

class Rva001F4206
{
public:
	Rva001F4206Helper *m_ptr;
	__declspec(noinline) void rva001F4206();
};

#endif // CANONICAL_RVA001F4206_H
