// ?reset@ScriptEngine@@UAEXXZ
// partial score=0.9 date=2026-09-24
// Banked partial: ScriptEngine::reset, retail 0x00209ABE (855 bytes).
// Build: 859 bytes, instruction stream aligned 1:1 with retail (ratio 0.71 only
// because of register names). Member layout = ScriptEngine_dtor.cpp.
//
// Sole wall: register allocation. Retail keeps constant 0 in edi (so bool
// false stores are immediates) and gives ebx to the breeze pointer, the
// constant 1 and the object-type/per-player pointers; it rematerializes 0 in
// the sides loop (EH state via and [ebp-4],0). This build gives 0 to ebx for
// the whole body, spills one per-player pointer and ends up with a 4-byte
// larger frame.
// Refuted: store order (20 random permutations), TRUE/FALSE/NULL spelling,
// typed pointers, bool vs int params, unsigned char flags, loop-var scoping,
// /EHs /EHsc /GX, /G5 /G6 /G7 /arch:SSE /arch:SSE2, /O2 /Os /Ox decompositions,
// inline ScriptList::reset (EH functions never inline), ablations of the zero
// uses (zero keeps ebx regardless).
//
// Pins this body needs (none exist yet):
//   ?rva0029AB35@Rva0029AB35Owner@@QAEX_N@Z          0x0029AB35 (global 0x00DFEDF0)
//   ?_bfme_rva001EE5D6@Mouse@@QAEX_N@Z               0x001EE5D6 (TheMouse 0x00DFDCA0)
//   ?clear@Rva002075F3Map@@QAEXXZ .. Rva002076E7Map  0x00206EC7 0x00206EF0 0x00206F19 0x00206F42 0x00206F6B
//   ?cleanupSequentialScript@ScriptEngine@@QAEXPAPAVSequentialScript@@_N1@Z  0x00204733
//   ?removeObjectTypes@ScriptEngine@@QAEXPAVObjectTypes@@@Z  0x002046E4
//   ?erase@ObjectTypesVector@@QAEPAPAVObjectTypes@@PAPAV2@@Z  0x001FF51F
//   ?erase@Rva00207E65Vector@@QAEPAXPAX0@Z  0x00207F40   ?erase@Rva00207E26Vector@@QAEPAXPAX0@Z  0x00207F0D
//   ?erase@Rva0007FAB3Vector@@QAEPAHPAH0@Z  0x00532803   ?clear@Rva004EC395List@@QAEXXZ  0x0023DAA5
//   ??0ScriptList@@QAE@XZ 0x003B7720  ??1ScriptList@@UAE@XZ 0x003B774B
//   ?setScriptList@SidesInfo@@QAEXABVScriptList@@@Z 0x003297F3  ?clear@Rva00205AF8Record@@QAEXXZ 0x00204984
// ?reset@ScriptEngine@@UAEXXZ
// partial score=0.9 date=2026-09-24
// cl: /O1 /EHs /G7 /arch:SSE

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
	void clear();

private:
	void *m_header;
	int m_nodeCount;
	int m_compare;
};
class Rva00207630Map
{
public:
	~Rva00207630Map();
	void clear();

private:
	void *m_header;
	int m_nodeCount;
	int m_compare;
};
class Rva0020766DMap
{
public:
	~Rva0020766DMap();
	void clear();

private:
	void *m_header;
	int m_nodeCount;
	int m_compare;
};
class Rva002076AAMap
{
public:
	~Rva002076AAMap();
	void clear();

private:
	void *m_header;
	int m_nodeCount;
	int m_compare;
};
class Rva002076E7Map
{
public:
	~Rva002076E7Map();
	void clear();

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
	void *erase(void *first, void *last);
	void *begin() { return m_start; }
	void *end() { return m_finish; }
	void clear() { erase(begin(), end()); }

private:
	void *m_start;
	void *m_finish;
	void *m_endOfStorage;
};
class Rva00207E65Vector
{
public:
	~Rva00207E65Vector();
	void *erase(void *first, void *last);
	void *begin() { return m_start; }
	void *end() { return m_finish; }
	void clear() { erase(begin(), end()); }

private:
	void *m_start;
	void *m_finish;
	void *m_endOfStorage;
};
class Rva004EC395List
{
public:
	~Rva004EC395List();
	void clear();

private:
	void *m_node;
};

class Rva00205AF8Record
{
public:
	~Rva00205AF8Record();
	void clear();

private:
	char m_body[12];
};

class Rva0007FAB3Vector
{
public:
	~Rva0007FAB3Vector();
	int *erase(int *first, int *last);
	int *begin() { return (int *)m_start; }
	int *end() { return (int *)m_finish; }
	void clear() { erase(begin(), end()); }

private:
	void *m_start;
	void *m_finish;
	void *m_endOfStorage;
};

class BfmeOwnedStringState
{
public:
	~BfmeOwnedStringState();
	void resetOwnedObject();

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


class ObjectTypes;
class SequentialScript;

class ObjectTypesVector
{
public:
	~ObjectTypesVector()
	{
		if (m_start)
			free(m_start);
	}
	ObjectTypes **begin() { return m_start; }
	ObjectTypes **end() { return m_finish; }
	ObjectTypes **erase(ObjectTypes **it);

private:
	ObjectTypes **m_start;
	ObjectTypes **m_finish;
	ObjectTypes **m_endOfStorage;
};

class SequentialScriptVector
{
public:
	~SequentialScriptVector()
	{
		if (m_start)
			free(m_start);
	}
	SequentialScript **begin() { return m_start; }
	SequentialScript **end() { return m_finish; }

private:
	SequentialScript **m_start;
	SequentialScript **m_finish;
	SequentialScript **m_endOfStorage;
};

class ScriptList
{
public:
	ScriptList();
	virtual ~ScriptList();

private:
	char m_body[0x48];
};

struct SidesInfo
{
	void setScriptList(const ScriptList &list);
};

class SidesList
{
public:
	SidesInfo *getSideInfo(int side);
	int getNumSides() { return m_numSides; }

private:
	char m_pad[0x3C];
	int m_numSides; // +0x3C
};
extern SidesList *TheSidesList;

class GameEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17();
	virtual void setFramesPerSecondLimit(int fps);
};
extern GameEngine *TheGameEngine;

class GlobalData
{
public:
	char m_pad0[0x28];
	int m_framesPerSecondLimit; // +0x28
};
extern GlobalData *TheGlobalData;

class Rva0029AB35Owner
{
public:
	void rva0029AB35(bool enable);
};
extern Rva0029AB35Owner *TheRva00DFEDF0;

class Mouse
{
public:
	void _bfme_rva001EE5D6(bool enable);
};
extern Mouse *TheMouse;

class ScriptSubsystem
{
public:
	virtual ~ScriptSubsystem();
	virtual void init();
	virtual void slot2(); virtual void slot3(); virtual void slot4(); virtual void slot5();
	virtual void slot6(); virtual void slot7(); virtual void slot8();
	virtual void reset();
};
extern ScriptSubsystem *TheScriptActions;
extern ScriptSubsystem *TheScriptConditions;

extern int g_Va00DBA4E4;
float Sin(float x);
float Cos(float x);
#define PI 3.14159265359f

struct Coord2D
{
	float x;
	float y;
};

struct BreezeInfo
{
	float   m_direction;     // +0x1A4A8
	Coord2D m_directionVec;  // +0x1A4AC
	float   m_intensity;     // +0x1A4B4
	float   m_lean;          // +0x1A4B8
	float   m_randomness;    // +0x1A4BC
	short   m_breezePeriod;  // +0x1A4C0
	short   m_breezeVersion; // +0x1A4C2
};

class ScriptEngine : public SubsystemInterface, public Snapshot
{
public:
	virtual ~ScriptEngine();
	virtual void crc();
	virtual void reset();

	void cleanupSequentialScript(SequentialScript **it, bool cleanDanglers, bool removeScript);
	void removeObjectTypes(ObjectTypes *typesToRemove);

private:
	SequentialScriptVector m_sequentialScripts;     // +0x10
	int m_pad1C;                                    // +0x1C
	Template m_actionTemplates[599];                // +0x20
	ConditionTemplate m_conditionTemplates[202];    // +0x12BA0
	Rva002075F3Map m_map190A0;                      // +0x190A0
	Rva00207630Map m_map190AC;                      // +0x190AC
	Rva0020766DMap m_map190B8;                      // +0x190B8
	Rva002076AAMap m_map190C4;                      // +0x190C4
	Rva002076E7Map m_map190D0;                      // +0x190D0
	Rva00207724Map m_map190DC;                      // +0x190DC
	Rva00207761Map m_map190E8;                      // +0x190E8
	Rva0020779EMap m_map190F4;                      // +0x190F4
	BfmeOwnedStringState m_attackPriorityInfo[256]; // +0x19100
	int m_numAttackInfo;                            // +0x1A100
	int m_endGameTimer;                             // +0x1A104
	int m_closeWindowTimer;                         // +0x1A108
	AsciiString m_string1A10C;                      // +0x1A10C
	void *m_callingTeam;                            // +0x1A110
	void *m_callingObject;                          // +0x1A114
	void *m_conditionTeam;                          // +0x1A118
	void *m_conditionObject;                        // +0x1A11C
	Rva00207E26Vector m_namedObjects;               // +0x1A120
	bool m_flag1A12C;                               // +0x1A12C
	void *m_currentPlayer;                          // +0x1A130
	void *m_skirmishHumanPlayer;                    // +0x1A134
	int m_frameObjectCountChanged;                  // +0x1A138
	bool m_shownMPLocalDefeatWindow;                // +0x1A13C
	float m_float1A140;                             // +0x1A140
	float m_float1A144;                             // +0x1A144
	float m_float1A148;                             // +0x1A148
	int m_int1A14C;                                 // +0x1A14C
	int m_int1A150;                                 // +0x1A150
	int m_int1A154;                                 // +0x1A154
	int m_int1A158;                                 // +0x1A158
	int m_int1A15C;                                 // +0x1A15C
	int m_int1A160;                                 // +0x1A160
	Rva00205AF8Record m_objectCounts[20];           // +0x1A164
	Rva004EC395List m_completedVideo;               // +0x1A254
	Rva004EC395List m_testingSpeech;                // +0x1A258
	Rva004EC395List m_testingAudio;                 // +0x1A25C
	Rva004EC395List m_uiInteractions;               // +0x1A260
	Rva004EC395List m_list1A264;                    // +0x1A264
	Rva004EC395List m_triggeredSpecialPowers[20];   // +0x1A268
	Rva004EC395List m_midwaySpecialPowers[20];      // +0x1A2B8
	Rva004EC395List m_finishedSpecialPowers[20];    // +0x1A308
	Rva004EC395List m_completedUpgrades[20];        // +0x1A358
	Rva0007FAB3Vector m_acquiredSciences[20];       // +0x1A3A8
	Rva004EC395List m_toppleDirections;             // +0x1A498
	Rva00207E65Vector m_namedReveals;               // +0x1A49C
	BreezeInfo m_breezeInfo;                        // +0x1A4A8
	int m_int1A4C4;                                 // +0x1A4C4
	ObjectTypesVector m_allObjectTypeLists;         // +0x1A4C8
	bool m_freezeByScript;                          // +0x1A4D4
	bool m_objectsShouldReceiveDifficultyBonus;     // +0x1A4D5
	bool m_ChooseVictimAlwaysUsesNormal;            // +0x1A4D6
	bool m_flag1A4D7;                               // +0x1A4D7
};

void ScriptEngine::reset()
{
	if (TheGameEngine && TheGlobalData)
		TheGameEngine->setFramesPerSecondLimit(TheGlobalData->m_framesPerSecondLimit);
	if (TheRva00DFEDF0)
		TheRva00DFEDF0->rva0029AB35(true);
	if (TheMouse)
		TheMouse->_bfme_rva001EE5D6(true);
	if (TheScriptActions) {
		TheScriptActions->reset();
	}
	if (TheScriptConditions) {
		TheScriptConditions->reset();
	}
	m_endGameTimer = -1;
	m_closeWindowTimer = -1;
	m_float1A140 = 1.0f;
	m_numAttackInfo = 1;
	m_flag1A12C = true;
	m_callingTeam = 0;
	m_callingObject = 0;
	m_conditionTeam = 0;
	m_conditionObject = 0;
	m_currentPlayer = 0;
	m_skirmishHumanPlayer = 0;
	m_int1A15C = 0;
	m_int1A160 = 0;
	m_frameObjectCountChanged = 0;
	m_int1A14C = 0;
	m_float1A144 = 0.0f;
	m_int1A150 = 0;
	m_int1A154 = 0;
	m_int1A158 = 0;
	m_float1A148 = 0.0f;
	m_shownMPLocalDefeatWindow = false;
	m_flag1A4D7 = false;
	m_map190A0.clear();
	m_map190AC.clear();
	m_map190B8.clear();
	m_map190C4.clear();
	m_map190D0.clear();

	m_breezeInfo.m_direction = PI/3;
	m_breezeInfo.m_directionVec.x = Sin(m_breezeInfo.m_direction);
	m_breezeInfo.m_directionVec.y = Cos(m_breezeInfo.m_direction);
	m_breezeInfo.m_intensity = 0.035f*PI/4;
	m_breezeInfo.m_lean = 0.02f*PI/4;
	m_breezeInfo.m_breezePeriod = g_Va00DBA4E4 * 10;
	m_breezeInfo.m_randomness = 0.2f;
	m_breezeInfo.m_breezeVersion = 0;
	m_freezeByScript = false;
	m_int1A4C4 = 1;
	m_objectsShouldReceiveDifficultyBonus = true;
	m_ChooseVictimAlwaysUsesNormal = false;

	while (m_sequentialScripts.begin() != m_sequentialScripts.end()) {
		cleanupSequentialScript(m_sequentialScripts.begin(), true, true);
	}

	for (ObjectTypes **it = m_allObjectTypeLists.begin(); it != m_allObjectTypeLists.end(); it = m_allObjectTypeLists.begin()) {
		if (*it) {
			removeObjectTypes(*it);
		} else {
			m_allObjectTypeLists.erase(it);
		}
	}

	m_namedReveals.clear();
	m_namedObjects.clear();
	m_completedVideo.clear();
	m_uiInteractions.clear();
	m_testingSpeech.clear();
	m_testingAudio.clear();
	m_list1A264.clear();

	int i;
	for (i = 0; i < 20; ++i) {
		m_triggeredSpecialPowers[i].clear();
		m_midwaySpecialPowers[i].clear();
		m_finishedSpecialPowers[i].clear();
		m_acquiredSciences[i].clear();
		m_completedUpgrades[i].clear();
	}

	if (TheSidesList) {
		int numSides = TheSidesList->getNumSides();
		for (i = 0; i < numSides; ++i) {
			TheSidesList->getSideInfo(i)->setScriptList(ScriptList());
		}
	}

	for (i = 0; i < 256; ++i)
		m_attackPriorityInfo[i].resetOwnedObject();

	for (i = 0; i < 20; ++i)
		m_objectCounts[i].clear();

	m_toppleDirections.clear();
}
