// WWLib synchronization classes, including the spin lock BFME2's profile
// library uses where Zero Hour had its own ProfileFastCS.
//
// Layout and ABI from retail: the lock word is the only member (+0); the
// out-of-line spin is __fastcall with the flag address in ECX
// (?spin@LockClass@FastCriticalSectionClass@@CIXPAX@Z, 0x006C5EF0); the
// lock constructor (0x006C5F40) stores the section reference and spins;
// the destructor is inlined everywhere as a plain store of 0 to the flag.

#ifndef MUTEX_H
#define MUTEX_H

// The local header also shadows WWLib's donor mutex.h for mutex.cpp and
// mixfile.cpp. Retain its two OS-backed classes as well as the profile lock.
// Declarations from GeneralsMD WWLib/mutex.h at BFME1 d6db6bfa4f (EA,
// GPL-3.0-or-later); BFME2 mutex.cpp verifies the handle/locked layout and
// guard ABI in its ten matched bodies at RVA 0x006139F0..0x00613B80.
class MutexClass
{
	void *handle;
	unsigned locked;
	bool Lock(int time);
	void Unlock();

public:
	MutexClass(const char *name = 0);
	~MutexClass();
	enum { WAIT_INFINITE = -1 };

	class LockClass
	{
		MutexClass &mutex;
		bool failed;
	public:
		LockClass(MutexClass &m, int time = MutexClass::WAIT_INFINITE);
		~LockClass();
		bool Failed() { return failed; }
	private:
		LockClass &operator=(const LockClass &) { return *this; }
	};
	friend class LockClass;
};

class CriticalSectionClass
{
	void *handle;
	unsigned locked;
	void Lock();
	void Unlock();

public:
	CriticalSectionClass();
	~CriticalSectionClass();

	class LockClass
	{
		CriticalSectionClass &CriticalSection;
	public:
		LockClass(CriticalSectionClass &c);
		~LockClass();
	private:
		LockClass &operator=(const LockClass &) { return *this; }
	};
	friend class LockClass;
};

// This canonical class also owns the donor fast-section include guard.
#define BFME_FASTCRITICALSECTION_DEFINED
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
