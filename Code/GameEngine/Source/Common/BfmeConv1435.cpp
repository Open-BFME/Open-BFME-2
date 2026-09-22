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

// Watcher thread armed by bfmeGoVM0 (pinned at its pushed start address).
unsigned long __stdcall bfmeVM0WorkerThread(void *param);

extern __int64 g_bfmeVM0Total;
extern __int64 g_bfmeVM0Quotient;
extern double g_bfmeVM0Scale;
extern const double g_bfmeVM0Frequency;
extern const double g_bfmeVM0Factor;

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
	void bfmeGoVM0(int);
	void bfmeTickVM0();
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
			g_bfmeVM0Scale = g_bfmeVM0Frequency / (double)g_bfmeVM0Total * g_bfmeVM0Factor;
		}
		m_firstMutex = CreateMutexA(0, 0, 0);
		m_secondMutex = CreateMutexA(0, 1, 0);
		m_armed = 0;
		if (m_secondMutex != 0 && m_firstMutex != 0) {
			m_mode = mode;
			CreateThread(0, 0, bfmeVM0WorkerThread, this, 0, 0);
			unsigned long status;
			do {
				status = WaitForSingleObject(m_firstMutex, 1);
				if (status == 0)
					ReleaseMutex(m_firstMutex);
			} while (status != 0x102);
		}
	}
}
