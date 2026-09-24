// cl: /O1 /EHs
//
// ScriptEngine::~ScriptEngine, retail 0x0020A2B0 (726 bytes). Its scalar
// deleting destructor (0x0020C0C7) is slot 0 of the vtable at 0x007E3D70.
//
// Body donor: Zero Hour ~ScriptEngine (DestroyDebugDialog, FreeLibrary and
// reset()). The BFME2 additions are read from retail: the particle-editor
// loader global is emptied by swapping in a default one, the pointer at
// 0x00DFE16C is cleared, and the debug-window holder at 0x00DFE154 is deleted.
//
// The member layout is what this destructor tears down. Offsets, element
// counts and destructor addresses are target facts; the member names are
// labels, except where the matched init/reset helpers already fix a role.
//
// Shape notes. All are inferences that reproduce retail bytes:
//   * /EHs, not /EHsc. Retail keeps EH states around the two free()-backed
//     vectors, so free() is not assumed nothrow;
//   * the holder pointer is file-static, like ZH's st_DebugDLL. It is deleted
//     through a derived type with an implicit destructor over a base whose
//     inline destructor calls release(). An extern pointer or a user-declared
//     derived destructor produces a ??_G call or other registers;
//   * the condition table's element type is distinct from the action
//     table's. Retail pushes the (ICF-folded) element destructor address
//     twice instead of caching it in a register, which MSVC does only for
//     two different symbols.

typedef void *HMODULE;
typedef int (__stdcall *FARPROC)();
extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE module, const char *name);
extern "C" __declspec(dllimport) int __stdcall FreeLibrary(HMODULE module);
extern "C" void __cdecl free(void *block);

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	bool m_subsystemFlag;  // +0x04
	int  m_subsystemValue; // +0x08
};

class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void crc() = 0;
};

// STLport vector storage released with free(); element type trivially destroyed.
class FreeVector
{
public:
	~FreeVector()
	{
		if (m_start)
			free(m_start);
	}

private:
	void **m_start;
	void **m_finish;
	void **m_endOfStorage;
};
class Rva002075F3Map
{
public:
	~Rva002075F3Map();

private:
	void *m_header;
	int m_nodeCount;
	int m_compare;
};
class Rva00207630Map
{
public:
	~Rva00207630Map();

private:
	void *m_header;
	int m_nodeCount;
	int m_compare;
};
class Rva0020766DMap
{
public:
	~Rva0020766DMap();

private:
	void *m_header;
	int m_nodeCount;
	int m_compare;
};
class Rva002076AAMap
{
public:
	~Rva002076AAMap();

private:
	void *m_header;
	int m_nodeCount;
	int m_compare;
};
class Rva002076E7Map
{
public:
	~Rva002076E7Map();

private:
	void *m_header;
	int m_nodeCount;
	int m_compare;
};
class Rva00207724Map
{
public:
	~Rva00207724Map();

private:
	void *m_header;
	int m_nodeCount;
	int m_compare;
};
class Rva00207761Map
{
public:
	~Rva00207761Map();

private:
	void *m_header;
	int m_nodeCount;
	int m_compare;
};
class Rva0020779EMap
{
public:
	~Rva0020779EMap();

private:
	void *m_header;
	int m_nodeCount;
	int m_compare;
};
class Rva00207E26Vector
{
public:
	~Rva00207E26Vector();

private:
	void *m_start;
	void *m_finish;
	void *m_endOfStorage;
};
class Rva00207E65Vector
{
public:
	~Rva00207E65Vector();

private:
	void *m_start;
	void *m_finish;
	void *m_endOfStorage;
};
class Rva004EC395List
{
public:
	~Rva004EC395List();

private:
	void *m_node;
};

class Rva00205AF8Record
{
public:
	~Rva00205AF8Record();

private:
	char m_body[12];
};

class Rva0007FAB3Vector
{
public:
	~Rva0007FAB3Vector();

private:
	void *m_start;
	void *m_finish;
	void *m_endOfStorage;
};

class BfmeOwnedStringState
{
public:
	~BfmeOwnedStringState();

private:
	char m_body[16];
};

template <typename T>
class StringBase
{
public:
	~StringBase();

private:
	T *m_data;
};

class AsciiString : public StringBase<char>
{
};

class Template
{
public:
	~Template();

private:
	char m_body[0x80];
};

class ConditionTemplate
{
public:
	~ConditionTemplate();

private:
	char m_body[0x80];
};

template <class T>
inline void swapValues(T &a, T &b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

class DllHandle
{
public:
	DllHandle() : m_module(0) {}
	__forceinline ~DllHandle(void) {}
	virtual void bfmeKeepVtable(void) {}

protected:
	HMODULE m_module; // +0x04
};

class BfmeReleaseTarget;

class BfmeDualVtableReleaseDtor : public DllHandle
{
public:
	BfmeDualVtableReleaseDtor() : m_target(0) {}
	virtual ~BfmeDualVtableReleaseDtor(void);

	void swap(BfmeDualVtableReleaseDtor &that)
	{
		swapValues(m_module, that.m_module);
		swapValues(m_target, that.m_target);
	}

private:
	BfmeReleaseTarget *m_target; // +0x08
};

extern BfmeDualVtableReleaseDtor TheFXParticleEditor;

class Rva0020453CHolderBase
{
public:
	~Rva0020453CHolderBase() { release(); }
	virtual void holderSlot0();
	void release();

private:
	void *m_handle; // +0x04
	bool m_active;  // +0x08
};

class Rva0020453CHolder : public Rva0020453CHolderBase
{
public:
	virtual void holderSlot0();
};

static Rva0020453CHolder *TheDebugWindowHolder;
extern void *TheDebugWindowInterface;

static HMODULE st_DebugDLL;

class ScriptEngine : public SubsystemInterface, public Snapshot
{
public:
	virtual ~ScriptEngine();
	virtual void crc();
	virtual void reset();

private:
	FreeVector m_sequentialScripts;               // +0x10
	int m_pad1C;                                  // +0x1C
	Template m_actionTemplates[599];              // +0x20
	ConditionTemplate m_conditionTemplates[202];  // +0x12BA0
	Rva002075F3Map m_map190A0;                 // +0x190A0
	Rva00207630Map m_map190AC;                 // +0x190AC
	Rva0020766DMap m_map190B8;                 // +0x190B8
	Rva002076AAMap m_map190C4;                 // +0x190C4
	Rva002076E7Map m_map190D0;                 // +0x190D0
	Rva00207724Map m_map190DC;                 // +0x190DC
	Rva00207761Map m_map190E8;                 // +0x190E8
	Rva0020779EMap m_map190F4;                 // +0x190F4
	BfmeOwnedStringState m_ownedStrings[256];      // +0x19100
	char m_pad1A100[0x0C];                        // +0x1A100
	AsciiString m_string1A10C;                    // +0x1A10C
	char m_pad1A110[0x10];                        // +0x1A110
	Rva00207E26Vector m_vector1A120;              // +0x1A120
	char m_pad1A12C[0x38];                        // +0x1A12C
	Rva00205AF8Record m_playerRecords[20];        // +0x1A164
	Rva004EC395List m_list1A254;                  // +0x1A254
	Rva004EC395List m_list1A258;                  // +0x1A258
	Rva004EC395List m_list1A25C;                  // +0x1A25C
	Rva004EC395List m_list1A260;                  // +0x1A260
	Rva004EC395List m_list1A264;                  // +0x1A264
	Rva004EC395List m_playerLists1A268[20];       // +0x1A268
	Rva004EC395List m_playerLists1A2B8[20];       // +0x1A2B8
	Rva004EC395List m_playerLists1A308[20];       // +0x1A308
	Rva004EC395List m_playerLists1A358[20];       // +0x1A358
	Rva0007FAB3Vector m_playerVectors[20];        // +0x1A3A8
	Rva004EC395List m_list1A498;                  // +0x1A498
	Rva00207E65Vector m_vector1A49C;              // +0x1A49C
	char m_pad1A4A8[0x20];                        // +0x1A4A8
	FreeVector m_allObjectTypeLists;              // +0x1A4C8
};

ScriptEngine::~ScriptEngine()
{
	TheDebugWindowInterface = 0;
	BfmeDualVtableReleaseDtor().swap(TheFXParticleEditor);

	delete TheDebugWindowHolder;
	TheDebugWindowHolder = 0;

	if (st_DebugDLL) {
		FARPROC proc = GetProcAddress(st_DebugDLL, "DestroyDebugDialog");
		if (proc) {
			proc();
		}

		FreeLibrary(st_DebugDLL);
		st_DebugDLL = 0;
	}

	reset();
}
