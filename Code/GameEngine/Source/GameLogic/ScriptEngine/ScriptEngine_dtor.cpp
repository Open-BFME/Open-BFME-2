// cl: /Ireference/shims/bfme2_ascii /EHs /Ow
// platformsdk
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

#include <stdlib.h>
#include <windows.h>

typedef bool Bool;
#include "../../../../../reference/shims/subsystem_bfme2/subsystem_interface.h"

#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

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
class Rva002075F3
{
public:
	~Rva002075F3();

private:
	void *m_header;
	int m_nodeCount;
	int m_compare;
};
class Rva00207630
{
public:
	~Rva00207630();

private:
	void *m_header;
	int m_nodeCount;
	int m_compare;
};
class Rva0020766D
{
public:
	~Rva0020766D();

private:
	void *m_header;
	int m_nodeCount;
	int m_compare;
};
class Rva002076AA
{
public:
	~Rva002076AA();

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
class Rva00207724
{
public:
	~Rva00207724();

private:
	void *m_header;
	int m_nodeCount;
	int m_compare;
};
class Rva00207761
{
public:
	~Rva00207761();

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
// stlport
#include <list>
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}
// list<int>'s destructor is retail's tail thunk 0x00200667: the unwind
// funclets and the eh vector destructor iterator over the 20-list arrays
// take it, while the normal path expands it into the base destructor call.
typedef _STL::list<int, _STL::allocator<int> > ScriptIntList;

class Rva00205AF8
{
public:
	~Rva00205AF8();

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

#include "ascii_string.h"


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
inline void swapValues(T &lhs, T &rhs)
{
	T tmp = lhs;
	lhs = rhs;
	rhs = tmp;
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

	BfmeReleaseTarget *target() const { return m_target; }

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

protected:
	void *m_handle; // +0x04
	bool m_active;  // +0x08
};

// Retail's particleEditorUpdate stores the base vtable 0x00BE39F4, so the
// holder overrides nothing; the derived view only keeps ~ScriptEngine's
// delete inline (a base-typed delete calls ??_G instead).
class Rva0020453CHolder : public Rva0020453CHolderBase
{
public:
	Rva0020453CHolder() { m_handle = 0; m_active = false; }
};

static Rva0020453CHolder *TheDebugWindowHolder;

// Particle-editor host held at TheFXParticleEditor+8: slot 2 takes the
// particle-system manager's +0x50 value, slot 3 the debug-window holder.
class BfmeReleaseTarget
{
public:
	virtual void hostSlot0();
	virtual void hostSlot1();
	virtual void hostSlot2(int value);
	virtual void hostSlot3(Rva0020453CHolder *holder);
	virtual void hostSlot4();
};

struct Rva009FDD04ManagerView
{
	char m_pad[0x50];
	int m_value; // +0x50
};
extern class ParticleSystemManager *TheParticleSystemManager;
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

// The debug DLL handle: the data ledger's ?st_DebugDLL@@3HA (0x9FE158),
// defined in ScriptEngine_appGate.cpp; read here as the HMODULE it holds.
extern int st_DebugDLL;

class ScriptEngine : public SubsystemInterface, public Snapshot
{
public:
	virtual ~ScriptEngine();
	virtual void init();
	virtual void update();
	virtual void reset();

protected:
	void particleEditorUpdate();

private:
	FreeVector m_sequentialScripts;               // +0x10
	int m_pad1C;                                  // +0x1C
	Template m_actionTemplates[599];              // +0x20
	ConditionTemplate m_conditionTemplates[202];  // +0x12BA0
	Rva002075F3 m_map190A0;                 // +0x190A0
	Rva00207630 m_map190AC;                 // +0x190AC
	Rva0020766D m_map190B8;                 // +0x190B8
	Rva002076AA m_map190C4;                 // +0x190C4
	Rva002076E7Map m_map190D0;                 // +0x190D0
	Rva00207724 m_map190DC;                 // +0x190DC
	Rva00207761 m_map190E8;                 // +0x190E8
	Rva0020779EMap m_map190F4;                 // +0x190F4
	BfmeOwnedStringState m_ownedStrings[256];      // +0x19100
	char m_pad1A100[0x0C];                        // +0x1A100
	AsciiString m_string1A10C;                    // +0x1A10C
	char m_pad1A110[0x10];                        // +0x1A110
	Rva00207E26Vector m_vector1A120;              // +0x1A120
	char m_pad1A12C[0x38];                        // +0x1A12C
	Rva00205AF8 m_playerRecords[20];        // +0x1A164
	ScriptIntList m_list1A254;                  // +0x1A254
	ScriptIntList m_list1A258;                  // +0x1A258
	ScriptIntList m_list1A25C;                  // +0x1A25C
	ScriptIntList m_list1A260;                  // +0x1A260
	ScriptIntList m_list1A264;                  // +0x1A264
	ScriptIntList m_playerLists1A268[20];       // +0x1A268
	ScriptIntList m_playerLists1A2B8[20];       // +0x1A2B8
	ScriptIntList m_playerLists1A308[20];       // +0x1A308
	ScriptIntList m_playerLists1A358[20];       // +0x1A358
	Rva0007FAB3Vector m_playerVectors[20];        // +0x1A3A8
	ScriptIntList m_list1A498;                  // +0x1A498
	Rva00207E65Vector m_vector1A49C;              // +0x1A49C
	char m_pad1A4A8[0x20];                        // +0x1A4A8
	FreeVector m_allObjectTypeLists;              // +0x1A4C8
};

ScriptEngine::~ScriptEngine()
{
	TheScriptEngine = 0;
	BfmeDualVtableReleaseDtor().swap(TheFXParticleEditor);

	delete TheDebugWindowHolder;
	TheDebugWindowHolder = 0;

	if (st_DebugDLL) {
		FARPROC proc = GetProcAddress((HMODULE)st_DebugDLL, "DestroyDebugDialog");
		if (proc) {
			proc();
		}

		FreeLibrary((HMODULE)st_DebugDLL);
		st_DebugDLL = 0;
	}

	reset();
}
// ?TheDebugWindowInterface@@3PAXA: the global at VA 0xdfe16c is ?TheScriptEngine@@3PAVScriptEngine@@A.

void ScriptEngine::particleEditorUpdate()
{
	if (!TheFXParticleEditor.target())
		return;
	if (!TheDebugWindowHolder) {
		Rva0020453CHolder *holder = new Rva0020453CHolder;
		TheDebugWindowHolder = holder;
		TheFXParticleEditor.target()->hostSlot3(holder);
	}
	TheFXParticleEditor.target()->hostSlot2(((Rva009FDD04ManagerView *)TheParticleSystemManager)->m_value);
	return TheFXParticleEditor.target()->hostSlot4();
}
