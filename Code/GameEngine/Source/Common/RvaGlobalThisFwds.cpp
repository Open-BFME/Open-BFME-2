// Three global-this forwards (11B each): mov ecx, [global], jmp <run>.
// Each loads a singleton pointer into this and tail-jumps its parameterless
// run method.
// 0x003BBEDE (global 0x00DFE16C -> 0x00203AD5),
// 0x003BBEE9 (global 0x00DFE16C -> 0x00203ADD),
// 0x003BD424 (global 0x00DFF028 -> 0x002D37BD).
// Global/callee identities unproven (opaque pins); the wrapper names are
// address-derived. One ledger row per forward.

class Rva00203AD5Run
{
public:
	void run();
};

class Rva00203ADDRun
{
public:
	void run();
};

class Rva002D37BDRun
{
public:
	void run();
};

extern class ScriptEngine *TheScriptEngine;
extern Rva002D37BDRun *g_pRva003BD424;

void Rva003BBEDE()
{
	(*(Rva00203AD5Run **)&TheScriptEngine)->run();
}

void Rva003BBEE9()
{
	((Rva00203ADDRun *)(*(Rva00203AD5Run **)&TheScriptEngine))->run();
}

void Rva003BD424()
{
	g_pRva003BD424->run();
}
