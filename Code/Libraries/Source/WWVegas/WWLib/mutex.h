// WWLib mutex.h: FastCriticalSectionClass, the spin lock BFME2's profile
// library uses where Zero Hour had its own ProfileFastCS.
//
// Layout and ABI from retail: the lock word is the only member (+0); the
// out-of-line spin is __fastcall with the flag address in ECX
// (?spin@LockClass@FastCriticalSectionClass@@CIXPAX@Z, 0x006C5EF0); the
// lock constructor (0x006C5F40) stores the section reference and spins;
// the destructor is inlined everywhere as a plain store of 0 to the flag.

#ifndef MUTEX_H
#define MUTEX_H

class FastCriticalSectionClass
{
public:
	unsigned Flag;

	class LockClass
	{
		FastCriticalSectionClass &cs;
		static void __fastcall spin(void *lock);

	public:
		LockClass(FastCriticalSectionClass &critical_section) : cs(critical_section)
		{
			spin(&cs.Flag);
		}
		~LockClass()
		{
			cs.Flag = 0;
		}
	};
};

#endif // MUTEX_H
