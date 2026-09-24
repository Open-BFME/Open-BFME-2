// ?bfmeForward@Gen_009EBB60Target@@QAEHXZ
// cl: /O2 /DNDEBUG /MD /EHs-c-
// stlport
//
// BFME1 donor Gen_009EBB60Target_bfmeForward.cpp with the BFME2 +8 header
// growth the Q1Receiver/Gen registry family shows: the lock at +0x68 and
// the m_1e0/m_1e4 counters at +0x1E8/+0x1EC. Found by scanning game.dat
// for the donor's rarest idiom (imul by 99); the sole hit lands inside a
// FREE 268B Ghidra-bounded body whose head, lock, deque sizes, import
// calls and 100/99-percent tail all match.

#define _STLP_NO_EXCEPTIONS 1
#include <deque>

struct CRITICAL_SECTION
{
	unsigned char m_data[0x18];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
	CRITICAL_SECTION *lock);

class Gen_009EBB60Target
{
public:
	int bfmeForward(void);

private:
	char m_pad00[0x68];
	CRITICAL_SECTION m_lock;
	_STL::deque<int> m_q0;
	_STL::deque<int> m_q1;
	_STL::deque<int> m_q2;
	char m_pade8[0x1e8 - 0xf8];
	int m_1e0;
	int m_1e4;
};

int Gen_009EBB60Target::bfmeForward(void)
{
	if (m_1e0 == 0 && m_1e4 == 0)
		return 100;

	EnterCriticalSection(&m_lock);

	int result = m_q0.size() + m_q1.size() + m_q2.size();

	LeaveCriticalSection(&m_lock);

	if (result == 0)
		return 100;

	unsigned int total = (unsigned int)(m_1e0 + m_1e4);
	return 99 - (int)((unsigned int)(result * 99) / total);
}
