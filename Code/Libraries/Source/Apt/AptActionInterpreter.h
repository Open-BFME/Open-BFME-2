// AptActionInterpreter: canonical declarations for the members units call, and its retail layout.
// Target facts (BFME2 1.06): the one instance, g_aptDateInterpreter at VA 0x00E182E0, is 0x6C bytes. Its init
// 0x006FEAF0, called on it from Rva006CF230Initialize (ecx = 0x00E182E0), stores byte +0x68 and dword +0x64;
// AptActionInterpreter.cpp's offsetof asserts give mpCurrentFunction +0x30 and mpThrownValue +0x60. Matched
// bodies reach +0x48 (VA 0x00E18328), +0x4C..+0x5B (0x00E1832C, cleared as four words by 0x006DF470) and
// +0x68 (0x00E18348) by absolute address. Members this header does not name keep their extent as storage.
#ifndef CANONICAL_APTACTIONINTERPRETER_H
#define CANONICAL_APTACTIONINTERPRETER_H

#include "AptBasePtrStack.h"

struct AptActionSetup;
struct AptConstantFile;
struct AptInitParmsT;
class AptCIH;
class AptValue;
class EAStringC;

class AptScriptFunctionBase;

struct AptActionInterpreter
{
	AptActionInterpreter();
	~AptActionInterpreter();
	void CleanupAfterExecution(void *, AptActionSetup *);
	void *PrepareForExecution(AptActionSetup *);
	void callFunction(AptValue *, AptValue *, int);
	static void getName(AptCIH *, EAStringC &);
	AptValue *getVariable(AptValue *, AptValue *, const EAStringC *, int = 1, int = 1, int = 0);
	void loadVariables(AptValue *, AptValue *, const EAStringC *);
	void rva006FEAF0(const AptInitParmsT &);
	void rva006FEB50();
	bool setVariable(AptValue *, AptValue *, const EAStringC *, AptValue *, int, int, int);
	static void _FunctionAptActionBitAnd(AptActionInterpreter *const);
	static void _FunctionAptActionBitOr(AptActionInterpreter *const);
	static void _FunctionAptActionBitXor(AptActionInterpreter *const);
	static void _FunctionAptActionBitLShift(AptActionInterpreter *const);
	static void _FunctionAptActionBitRShift(AptActionInterpreter *const);
private:
	friend void BfmeAux006FC670(const unsigned char *, int, AptConstantFile *, int *);
	struct LocalContextT;
	struct FunctionTable { int mCheckAlignment; void (__cdecl *m_04)(AptActionInterpreter *const, LocalContextT *const); };
	static FunctionTable sGlobalTable[185];
public:

	AptBasePtrStack stack;                        // +0x00
	unsigned char m_valueStacks[0x24];            // +0x0C withStack, setTargetStack, thisStack
	AptScriptFunctionBase *mpCurrentFunction;     // +0x30
	unsigned char m_debugCallStack[0x0C];         // +0x34
	unsigned char m_constantPool[0x08];           // +0x40
	unsigned int mLastKey;                        // +0x48 the event word being dispatched
	int mInitializerCounters[4];                  // +0x4C
	unsigned char m_pad5C[0x04];                  // +0x5C
	AptValue *mpThrownValue;                      // +0x60
	int mnStackFrameBase;                         // +0x64
	unsigned char f68;                            // +0x68
	unsigned char m_pad69[0x03];                  // +0x69
};

#define APTACTIONINTERPRETER_AT(m) ((unsigned int)&((AptActionInterpreter *)0)->m)
typedef char AptActionInterpreterSize[sizeof(AptActionInterpreter) == 0x6C ? 1 : -1];
typedef char AptActionInterpreterLastKeyAt[APTACTIONINTERPRETER_AT(mLastKey) == 0x48 ? 1 : -1];
typedef char AptActionInterpreterCountersAt[APTACTIONINTERPRETER_AT(mInitializerCounters) == 0x4C ? 1 : -1];
typedef char AptActionInterpreterThrownAt[APTACTIONINTERPRETER_AT(mpThrownValue) == 0x60 ? 1 : -1];
typedef char AptActionInterpreterFrameBaseAt[APTACTIONINTERPRETER_AT(mnStackFrameBase) == 0x64 ? 1 : -1];
typedef char AptActionInterpreterF68At[APTACTIONINTERPRETER_AT(f68) == 0x68 ? 1 : -1];
#undef APTACTIONINTERPRETER_AT

#endif // CANONICAL_APTACTIONINTERPRETER_H
