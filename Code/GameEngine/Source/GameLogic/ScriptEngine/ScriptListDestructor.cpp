// ??1ScriptList@@UAE@XZ
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameLogic/ScriptEngine/ScriptListDestructor.cpp (donor
// revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1).
// Compiled that way each body below places uniquely on unclaimed game.dat
// .text by masked whole-.text search, and ./build.sh reproduces it byte for
// byte: ScriptList::~ScriptList 0x003B774B (81B). Callee addresses are read
// off retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// partial score=0.93 date=2026-09-02
// cl: /O1 /DNDEBUG /MD /EHsc

class Gen_0035B8A0
{
public:
	~Gen_0035B8A0();

private:
	unsigned char m_data[0x20];
};

class Gen_0035B960
{
public:
	~Gen_0035B960();

private:
	unsigned char m_data[0x20];
};

class ScriptGroupPoolObject
{
public:
	ScriptGroupPoolObject *next;
	void deleteInstance(int destroy);
};

class ScriptPoolObject
{
public:
	ScriptPoolObject *next;
	void deleteInstance(int destroy);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class ScriptListInterface
{
public:
	virtual void reset();
	~ScriptListInterface() {}
};

class ScriptListBase
{
public:
    ~ScriptListBase();

private:
	ScriptPoolObject *m_firstGroup;
	ScriptGroupPoolObject *m_firstScript;
};


class ScriptList : public ScriptListInterface, public ScriptListBase
{
public:
	~ScriptList();

private:
	Gen_0035B8A0 m_first;
	Gen_0035B960 m_second;
};

// ??1ScriptList@@QAE@XZ
ScriptList::~ScriptList()
{
}
