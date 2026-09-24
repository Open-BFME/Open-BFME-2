// cl: /O1 /EHsc
//
// ScriptEngine::init, retail 0x00205AFD (406 bytes, including the catch(...)
// block Ghidra splits off at 0x00205BEF). Vtable slot 1 of the table at
// 0x007E3D70; the virtual called last is slot 9.
//
// Donor: Zero Hour ScriptEngine::init (GeneralsMD ScriptEngine.cpp) for the
// debug-window load, the CreateDebugDialog call, the profiling-counter reset,
// the ScriptActions/ScriptConditions init calls and the closing reset(). The
// BFME2 additions are read from retail:
//   * both subsystems are created here (operator new 0x10 / 0xC);
//   * the debug window load picks DebugWindowLite.dll when the bool at
//     0x00E02D7A is set, and everything sits under m_windowed;
//   * the particle editor is a loader object (FXParticleEditorI.dll, class
//     BfmeDualVtableReleaseDtor) built as a temporary and swapped into the
//     global at 0x00DFE180 inside try/catch(...), since its base constructor
//     throws when LoadLibrary fails;
//   * a missing CreateDebugDialog frees the library, and a present one is
//     followed by the sides-list hand-off (0x00203C21);
//   * the template tables are filled by the three out-of-line helpers.
// GlobalData field names follow ZH; their offsets are target-derived.

typedef void *HMODULE;
typedef int (__stdcall *FARPROC)();
extern "C" __declspec(dllimport) HMODULE __stdcall LoadLibraryA(const char *name);
extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE module, const char *name);
extern "C" __declspec(dllimport) int __stdcall FreeLibrary(HMODULE module);

class GlobalData
{
public:
	char m_pad0[0x2C];
	bool m_windowed;        // +0x2C
	char m_pad1[0x9C1 - 0x2D];
	bool m_scriptDebug;     // +0x9C1
	bool m_particleEdit;    // +0x9C2
};
extern GlobalData *TheGlobalData;
extern bool TheDebugWindowLite;

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init();
};

class ScriptActions : public SubsystemInterface
{
public:
	ScriptActions();

private:
	char m_body[0x0C];
};

class ScriptConditions : public SubsystemInterface
{
public:
	ScriptConditions();

private:
	char m_body[0x08];
};

extern ScriptActions *TheScriptActions;
extern ScriptConditions *TheScriptConditions;

template <class T>
inline void swapValues(T &a, T &b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

class BfmeDualVtableReleaseBase
{
public:
	__forceinline ~BfmeDualVtableReleaseBase(void) {}
	virtual void bfmeKeepVtable(void) {}
};

class BfmeDualVtableReleaseDtor : public BfmeDualVtableReleaseBase
{
public:
	BfmeDualVtableReleaseDtor(int unused);
	virtual ~BfmeDualVtableReleaseDtor(void);

	void swap(BfmeDualVtableReleaseDtor &that)
	{
		swapValues(m_guard, that.m_guard);
		swapValues(m_target, that.m_target);
	}

private:
	void *m_guard;   // +0x04
	void *m_target;  // +0x08
};

extern BfmeDualVtableReleaseDtor TheFXParticleEditor;

void rva00203C21();

static HMODULE st_DebugDLL;

class ScriptEngine
{
public:
	virtual ~ScriptEngine();
	virtual void init();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void reset();

	void initActionTemplates();
	void initConditionTemplates();
	void initTemplateNameKeys();

private:
	char   m_pre[0x1A4E0 - 8];
	double m_numFrames;        // +0x1A4E0
	double m_totalUpdateTime;  // +0x1A4E8
	double m_maxUpdateTime;    // +0x1A4F0
};

void ScriptEngine::init()
{
	TheScriptActions = new ScriptActions;
	TheScriptConditions = new ScriptConditions;

	if (TheGlobalData->m_windowed) {
		if (TheGlobalData->m_scriptDebug) {
			if (TheDebugWindowLite)
				st_DebugDLL = LoadLibraryA("DebugWindowLite.dll");
			else
				st_DebugDLL = LoadLibraryA("DebugWindow.dll");
		} else {
			st_DebugDLL = 0;
		}

		if (TheGlobalData->m_particleEdit) {
			try {
				BfmeDualVtableReleaseDtor(0).swap(TheFXParticleEditor);
			} catch (...) {
			}
		}

		if (st_DebugDLL) {
			FARPROC proc = GetProcAddress(st_DebugDLL, "CreateDebugDialog");
			if (proc) {
				proc();
				rva00203C21();
			} else {
				FreeLibrary(st_DebugDLL);
				st_DebugDLL = 0;
			}
		}
	}

	m_numFrames = 0;
	m_totalUpdateTime = 0;
	m_maxUpdateTime = 0;

	if (TheScriptActions) {
		TheScriptActions->init();
	}
	if (TheScriptConditions) {
		TheScriptConditions->init();
	}

	initActionTemplates();
	initConditionTemplates();
	initTemplateNameKeys();

	reset();
}
