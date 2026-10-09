// cl: /EHsc /DNDEBUG /DWIN32 /MD
// ?rva006C1E20@Rva006C1F60@@QAE_NPBXH@Z @ 0x006C1E20 (139B).
//
// Lock-guarded validator of the Rva006C1F60 family, same prologue and +0x4E4
// lock as the recovered setter 0x006C3840 in Rva006C3840Cluster.cpp, and the
// same /EHsc SEH frame (handler 0x00BA7D58, try levels 0 then -1) that makes
// the lock holder a local RAII object rather than a bare pointer.
//
// Retail tests only the LOW BYTE of the second argument and splits on it:
//   arg2 & 0xFF != 0 -> rva006C1DC0(arg1)          (one stack arg, ret 4)
//   otherwise          -> rva00032830(arg1, 0)      (two stack args, ret 8)
// The hash helper returns full-EAX 0/1; retail keeps the result in al, parks it in bl so
// the guard destructor can run, and returns it in al. 0x00032830 is the rowed
// GeneralAllocator::rva00032830(block, addressType) ValidateAddress-like (it
// reads +0x4E4 and ends `ret 8`), so this is the address-validity test on that
// allocator. 0x006C1DC0 is rowed and address-derived; it reads +0x680,
// +0x684 and +0x68C of this same class and hashes arg1 against a bucket array,
// so it is a secondary validator, but its identity is NOT proven.
//
// The single `result` local is load-bearing, not style. With two early returns
// MSVC keeps `this` in edi and the lock in esi, which is byte-identical to
// retail everywhere except those two register moves; assigning to one local
// and returning it once puts `this` in esi and the lock in edi, as retail does.
struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);

class Rva00030DD0Guard
{
public:
	Rva00030DD0Guard(Rva00030DD0Lock *lock) : m_lock(lock)
	{
		if (m_lock != 0)
			Rva00030DD0AddRef(m_lock);
	}
	~Rva00030DD0Guard()
	{
		if (m_lock != 0)
			Rva00030DF0Release(m_lock);
	}

private:
	Rva00030DD0Lock *m_lock;
};

// 0x00032830 is the rowed EA::Allocator::GeneralAllocator::rva00032830
// (ValidateAddress-like) in memory_pool.cpp; this class derives from that base
// so the inherited call keeps the base's own decorated name.
namespace EA
{
namespace Allocator
{
class GeneralAllocator
{
public:
	bool rva00032830(const void *block, int addressType);
};
}
}

class Rva006C1F60 : public EA::Allocator::GeneralAllocator
{
public:
	bool rva006C1E20(const void *block, int addressType);
	int rva006C1DC0(unsigned int block);

private:
	unsigned char m_pad0[0x4E4];
	Rva00030DD0Lock *m_lock;                               // +0x4E4
};

bool Rva006C1F60::rva006C1E20(const void *block, int addressType)
{
	Rva00030DD0Guard guard(m_lock);
	unsigned char *tag = (unsigned char *)&addressType;
	bool result;
	if (*tag != 0)
	{
		// The owned helper returns full EAX 0/1; native preserves only AL.
		union { int integer; bool low; } value;
		value.integer = rva006C1DC0((unsigned int)block);
		result = value.low;
	}
	else
		result = rva00032830(block, 0);
	return result;
}
