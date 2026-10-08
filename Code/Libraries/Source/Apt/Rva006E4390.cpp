// cl: /O2 /MD
// ?_tickNewInsts@AptAnimationPoolData@@QAEXXZ @0x006E4390 240B
// Unlock lane. Container of AptCIH pointers (array at +0 count at +4).
// Per element: null-this assert AptCIH.h:181 then type 0xE defined path via
// rowed get/isUndefined and rowed AptCIH::rva006E1090 button field (+0x18==0
// then pinned AptCIH::rva006E1F00(1)); else null-this assert AptCIH.h:171
// then type 0xD defined path via rowed Rva006E3C80 sprite field (+0x18==-1
// then pinned AptCIH::rva006E2D60); then virtual slot1 call. Count reset.
// Evidence: callers 0x006E6540/0x006ED490/0x007092F0; file string 0x008E8C60
// AptCIH.h and this 0x008E7764; same assert spellings as AptCIHLevel006E0B80
// and Rva006E3C80 neighbours.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class Rva006DBB30SarDwordField
{
public:
	int get() const;
};

class BfmeAptValue006DCD20
{
public:
	bool isUndefined() const;
};

class AptCIH
{
public:
	virtual void v0();
	virtual void v1();
	void *rva006E1090() const;
	void rva006E1F00(int);
	void rva006E2D60();
};

class Rva006E3C80
{
public:
	int rva006E3C80();
};

class AptAnimationPoolData
{
public:
	void _tickNewInsts();
private:
	AptCIH **m_arr;
	int m_count;
};

void AptAnimationPoolData::_tickNewInsts()
{
	for (int i = 0; i < m_count; ++i) {
		AptCIH *e = m_arr[i];
		if (!e) {
			g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xB5);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		if (((const Rva006DBB30SarDwordField *)e)->get() == 0xE
			&& !((const BfmeAptValue006DCD20 *)e)->isUndefined()) {
			void *p = ((const AptCIH *)m_arr[i])->rva006E1090();
			if (*(int *)((char *)p + 0x18) == 0)
				m_arr[i]->rva006E1F00(1);
		} else {
			AptCIH *e2 = m_arr[i];
			if (!e2) {
				g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xAB);
				if (g_bfmeAptBreakOnAssertAtDDC01C)
					__debugbreak();
			}
			if (((const Rva006DBB30SarDwordField *)e2)->get() == 0xD
				&& !((const BfmeAptValue006DCD20 *)e2)->isUndefined()) {
				int v = ((Rva006E3C80 *)m_arr[i])->rva006E3C80();
				if (*(int *)(v + 0x18) == -1)
					m_arr[i]->rva006E2D60();
			}
		}
		m_arr[i]->v1();
	}
	m_count = 0;
}
