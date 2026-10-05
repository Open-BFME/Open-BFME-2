// cl: /O1 /DNDEBUG /MD
//
// ?staticInitModules@FXParticleSystem@@YAXXZ retail 0x003AE381 135B.
// Runs every FX particle module type's guarded local-static initializer in
// a fixed order and tail-jumps into the last. Target facts: 27 direct calls
// to the rowed Rva*Init latches (each a guarded getInstance plus atexit),
// the last one a jmp; reached by the tail jmp at 0x001F3FFD. The name and
// the call-then-tail-jump shape are carried from the Open-BFME-1 donor
// fx_particle_system.cpp (1281192f68), whose staticInitModules has the same
// structure over BFME 1's module latches less the two leading calls.

void Rva003AD44BInit();
void Rva003AD46CInit();
void Rva003A8314Init();
void Rva003AD48DInit();
void Rva003AD4AEInit();
void Rva003AD4CFInit();
void Rva003AD4F0Init();
void Rva003A8354Init();
void Rva003A8394Init();
void Rva003A83D4Init();
void Rva003A8414Init();
void Rva003A8454Init();
void Rva003A8494Init();
void Rva003AD511Init();
void Rva003AD532Init();
void Rva003AD553Init();
void Rva003AD574Init();
void Rva003AD595Init();
void Rva003AD5B6Init();
void Rva003AD5D7Init();
void Rva003AD5F8Init();
void Rva003AD619Init();
void Rva003AD63AInit();
void Rva003AD65BInit();
void Rva003AD67CInit();
void Rva003AD69DInit();
void Rva003AD6BEInit();

namespace FXParticleSystem
{
void staticInitModules()
{
	Rva003AD44BInit();
	Rva003AD46CInit();
	Rva003A8314Init();
	Rva003AD48DInit();
	Rva003AD4AEInit();
	Rva003AD4CFInit();
	Rva003AD4F0Init();
	Rva003A8354Init();
	Rva003A8394Init();
	Rva003A83D4Init();
	Rva003A8414Init();
	Rva003A8454Init();
	Rva003A8494Init();
	Rva003AD511Init();
	Rva003AD532Init();
	Rva003AD553Init();
	Rva003AD574Init();
	Rva003AD595Init();
	Rva003AD5B6Init();
	Rva003AD5D7Init();
	Rva003AD5F8Init();
	Rva003AD619Init();
	Rva003AD63AInit();
	Rva003AD65BInit();
	Rva003AD67CInit();
	Rva003AD69DInit();
	return Rva003AD6BEInit();
}
}

// ?init@Rva001F3FEA@@UAEXXZ retail 0x001F3FEA 24B. Slot 1 of the vtables at
// 0x00BC4C74 and 0x00BE18CC (slot 0 is each class's scalar deleting dtor):
// clears two seven-pointer tables at +0x10 and +0x2C, then tail-jumps into
// staticInitModules. Owner class and member names are not recovered.
class Rva001F3FEA
{
public:
	virtual ~Rva001F3FEA();
	virtual void init();

	char m_unknown04[0xC];
	void *m_tableA[7];
	void *m_tableB[7];
};

void Rva001F3FEA::init()
{
	for (int i = 0; i < 7; ++i) {
		m_tableA[i] = 0;
		m_tableB[i] = 0;
	}
	FXParticleSystem::staticInitModules();
}
