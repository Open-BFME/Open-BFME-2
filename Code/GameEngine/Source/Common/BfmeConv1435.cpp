// cl: /O1 /Ob0
// Near-miss donor from Open-BFME-1 BfmeConv1435.cpp
// (?bfmeTickVM0@BfmeStrVM0@@QAEXXZ @0x0040FE40):
// retail predicate virtual is at slot +0x114 (not +0xF0).
// ?bfmeGoVM0@BfmeStrVM0@@QAEXH@Z @0x0025D904 (199B):
// BFME2-only watchdog arming. A 64-bit timing base is divided by
// (timer - 2) through __alldiv and a frequency ratio is scaled on the x87
// unit; then two mutexes plus a worker thread are created and the first
// mutex is polled at 1ms until the wait times out.

extern "C" __declspec(dllimport) void *__stdcall CreateMutexA(void *attrs, int owned, void *name);
extern "C" __declspec(dllimport) void *__stdcall CreateThread(void *attrs, unsigned long stack, unsigned long (__stdcall *start)(void *), void *param, unsigned long flags, unsigned long *tid);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *handle, unsigned long timeout);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long ms);

// Watcher thread armed by bfmeGoVM0. Retail's body returns with a plain
// ret: it is cdecl, cast to CreateThread's stdcall start type.
unsigned long __cdecl bfmeVM0WorkerThread(void *param);

extern __int64 g_bfmeVM0Total;
extern __int64 g_bfmeVM0Quotient;
extern double g_bfmeVM0Scale;
// g_bfmeVM0Scale: matched references place it at VA 0xdfea10 (zero-filled .bss).
double g_bfmeVM0Scale;
extern const double g_bfmeVM0Factor;
// g_bfmeVM0Factor: matched references place it at VA 0xbf5d50 (retail .rdata value 0.03333333333333333).
extern const double g_bfmeVM0Factor = 0.03333333333333333;

class BfmeVM0Timer
{
public:
	virtual int v0();
	virtual int v1();
	virtual int v2();
	virtual int v3();
	virtual int v4();
	virtual int v5();
	virtual int v6();
	virtual int v7();
	virtual int v8();
	virtual int v9();
	virtual int v10();
	virtual int v11();
	virtual int v12();
	virtual int v13();
	virtual int v14();
	virtual int v15();
	virtual int readTickCounter();
};

class BfmeStrVM0
{
public:
	virtual int v0();
	virtual int v1();
	virtual int v2();
	virtual int v3();
	virtual int v4();
	virtual int v5();
	virtual int v6();
	virtual int v7();
	virtual int v8();
	virtual int v9();
	virtual int v10();
	virtual int v11();
	virtual int v12();
	virtual int v13();
	virtual int v14();
	virtual int v15();
	virtual int v16();
	virtual int v17();
	virtual int v18();
	virtual int v19();
	virtual int v20();
	virtual int v21();
	virtual int v22();
	virtual int v23();
	virtual int v24();
	virtual int v25();
	virtual int v26();
	virtual int v27();
	virtual int v28();
	virtual int v29();
	virtual int v30();
	virtual int v31();
	virtual int v32();
	virtual int v33();
	virtual int v34();
	virtual int v35();
	virtual int v36();
	virtual int v37();
	virtual int v38();
	virtual int v39();
	virtual int v40();
	virtual int v41();
	virtual int v42();
	virtual int v43();
	virtual int v44();
	virtual int v45();
	virtual int v46();
	virtual int v47();
	virtual int v48();
	virtual int v49();
	virtual int v50();
	virtual int v51();
	virtual int v52();
	virtual int v53();
	virtual int v54();
	virtual int v55();
	virtual int v56();
	virtual int v57();
	virtual int v58();
	virtual int v59();
	virtual int v60();
	virtual int v61();
	virtual int v62();
	virtual int v63();
	virtual int v64();
	virtual int v65();
	virtual int v66();
	virtual int v67();
	virtual int v68();
	virtual bool bfmePredVM0();
	virtual bool bfmeProbeVM0();
	virtual int v71();
	virtual int v72();
	virtual void bfmeKickVM0(int value);
	void bfmeGoVM0(int);
	void bfmeTickVM0();
	void rva0025C46E();
	void rva0025D9CB(bool flag);
	void rva0025D10F();
	int rva0025C4A4(int value);
	char m_pad04[0x34];
	BfmeVM0Timer *m_timer;
	char m_pad3C[0x4];
	void * volatile m_firstMutex;
	void * volatile m_secondMutex;
	char m_pad48[0x18];
	int m_mode;
	char m_pad64[0xD8];
	volatile int m_armed;
};

// ?bfmeVM0WorkerThread@@YAKPAX@Z retail 0x0025D128 (118B), the CreateThread
// start bfmeGoVM0 pushes. It holds the first mutex while it runs and
// polls the second, which the arming thread owns, at the mode's period:
// mode 5 drives rva0025C4A4(1) every 33ms; any other mode probes through
// slot +0x118 until it succeeds (kicking slot +0x124 and retrying after 1ms)
// and then idles at 100ms.
unsigned long __cdecl bfmeVM0WorkerThread(void *param)
{
	BfmeStrVM0 *self = (BfmeStrVM0 *)param;
	bool probing = true;
	WaitForSingleObject(self->m_firstMutex, (unsigned long)-1);
	do {
		if (self->m_mode == 5) {
			self->rva0025C4A4(1);
			Sleep(33);
		} else if (probing) {
			if (!self->bfmeProbeVM0()) {
				self->bfmeKickVM0(1);
				Sleep(1);
			} else {
				probing = false;
				Sleep(100);
			}
		} else {
			Sleep(100);
		}
	} while (WaitForSingleObject(self->m_secondMutex, 0) == 0x102);
	ReleaseMutex(self->m_firstMutex);
	return 0;
}

void BfmeStrVM0::bfmeTickVM0()
{
	if (bfmePredVM0())
		bfmeGoVM0(3);
}

// ?bfmeGoVM0@BfmeStrVM0@@QAEXH@Z
void BfmeStrVM0::bfmeGoVM0(int mode)
{
	if (m_firstMutex == 0 && m_secondMutex == 0) {
		if (mode != 5) {
			int span = m_timer->readTickCounter();
			--span;
			--span;
			g_bfmeVM0Quotient = g_bfmeVM0Total / span;
			g_bfmeVM0Scale = 1000.0 / (double)g_bfmeVM0Total * g_bfmeVM0Factor;
		}
		m_firstMutex = CreateMutexA(0, 0, 0);
		m_secondMutex = CreateMutexA(0, 1, 0);
		m_armed = 0;
		if (m_secondMutex != 0 && m_firstMutex != 0) {
			m_mode = mode;
			CreateThread(0, 0, (unsigned long (__stdcall *)(void *))bfmeVM0WorkerThread, this, 0, 0);
			unsigned long status;
			do {
				status = WaitForSingleObject(m_firstMutex, 1);
				if (status == 0)
					ReleaseMutex(m_firstMutex);
			} while (status != 0x102);
		}
	}
}

//
// ?rva0025C46E@BfmeStrVM0@@QAEXXZ retail 0x0025C46E 54B.
// Mutex release via m_firstMutex +0x40 and m_secondMutex +0x44 tail of BfmeStrVM0.
// Evidence: retail cmp [esi+0x44] 0 je then ReleaseMutex WaitForSingleObject ReleaseMutex and zero both; callers 0x0025D9DB 0x0025D121 with no stack pushes and same this.
void BfmeStrVM0::rva0025C46E()
{
	if (m_secondMutex != 0) {
		ReleaseMutex(m_secondMutex);
		WaitForSingleObject(m_firstMutex, (unsigned long)-1);
		ReleaseMutex(m_firstMutex);
		m_secondMutex = 0;
		m_firstMutex = 0;
	}
}

// ?rva0025D9CB@BfmeStrVM0@@QAEX_N@Z retail 0x0025D9CB 24B.
// Flag selects watchdog arm (bfmeGoVM0 mode 5) versus mutex release
// (rva0025C46E), forwarding this. Callers at 0x0043A30B/0x0043A326 push 0/1.
void BfmeStrVM0::rva0025D9CB(bool flag)
{
	if (flag)
		bfmeGoVM0(5);
	else
		rva0025C46E();
}

// ?rva0025D10F@BfmeStrVM0@@QAEXXZ retail 0x0025D10F 25B.
// Predicate-guarded mutex release: tail-jumps to rva0025C46E when the slot
// 0x114 predicate (bfmePredVM0) is true. Caller at 0x0025D1B3, same class.
void BfmeStrVM0::rva0025D10F()
{
	if (bfmePredVM0())
		rva0025C46E();
}
