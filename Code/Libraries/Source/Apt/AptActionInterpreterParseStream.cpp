// cl: /O2 /DNDEBUG /MD /EHs
// Apt action-stream relocate/unrelocate (_BfmeAux006FC670, retail 0x006FC670, 2512B with its tables);
// WB 0x0175B510 (AptActionInterpreter::_parseStream, asserts 0x13E..0x2B7) gives the statement and case structure.

#include "AptValue.h"

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

#define RUNTIME_ASSERT(e, line, text) \
	do { \
		if (!(e)) { \
			g_bfmeAptAssertAtE17734(text, "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", line); \
			if (g_bfmeAptBreakOnAssertAtDDC01C) \
				__debugbreak(); \
		} \
	} while (0)

#include "AptValueVector.h"
extern AptValueVector *g_releaseVectorAtE17710;

#include "../../../GameEngine/Include/Common/AptInteger.h"
#include "AptBoolean.h"
AptValue *Rva008A4EA0MakeFloat(float value);
extern AptValue *gpUndefinedValue;

struct StringNode0070D9F0;
StringNode0070D9F0 *Rva0070DBB0Intern(const char *string);
void Rva0070DDC0Remove(StringNode0070D9F0 *node);

#include "../../../GameEngine/Include/Common/Rva006DB160.h"
#include "../../../GameEngine/Include/Common/Rva006DB270.h"
extern Rva006DB270 *g_pChainBlockAllocator;
// Native sized-delete cleanup calls the same22B pool-free owner at6D8680.
// Expose that real forwarding body so each actual operator delete emits its
// whole proven ICF twin rather than a distinct5B jump to an opaque wrapper.
inline void Rva006D8680Free(void *block, int blockSize)
{
    g_pChainBlockAllocator->freeBlock(block, blockSize);
}

// The two pooled 12-byte value types built from constant types 8 and 4.
class Rva006FB9C0 : public AptValue
{
public:
	Rva006FB9C0(int value);
	virtual bool IsGarbageCollected() const;
	virtual void RegisterReferences() const;
	static void *operator new(unsigned int n) { return ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock(n); }
	static void operator delete(void *p, unsigned int n) { Rva006D8680Free(p, n); }
private:
	int m_value;
};

class Rva006FB960 : public AptValue
{
public:
	Rva006FB960(int value);
	virtual bool IsGarbageCollected() const;
	virtual void RegisterReferences() const;
	static void *operator new(unsigned int n) { return ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock(n); }
	static void operator delete(void *p, unsigned int n) { Rva006D8680Free(p, n); }
private:
	int m_value;
};

struct AptConstantItem
{
	int type;
	union
	{
		const char *szString;
		int nValue;
		float fValue;
	};
};

struct AptConstantFile
{
	char m_pad00[0x1C];
	AptConstantItem *aConstants;		// +0x1C
};

extern "C" void BfmeAux006FC670(const unsigned char *aActionStream, int pBase, AptConstantFile *aConstantFile, int *pnCurrentConstantIndex);

class AptCIH;
struct AptCharacterInst;
struct AptActionInterpreter
{
private:
	friend void BfmeAux006FC670(const unsigned char *, int, AptConstantFile *, int *);
	struct LocalContextT { const unsigned char *pInstruction; AptCIH *pCurrentContext; AptValue *pCurWith; const unsigned char *pRemoveWithAt; AptValue *pSuper; bool bEncounteredReturn; AptCharacterInst *pParentCharacter; };
	struct FunctionTable { int mCheckAlignment; void (__cdecl *mFunctionPointer)(AptActionInterpreter *const,LocalContextT *const); };
	static FunctionTable sGlobalTable[185];
};

struct ActionPushStringData { const char *szStringToBePushed; };
struct ActionItemsData { int nItems; void **apItems; };
struct ActionPushData { ActionItemsData items; };
struct ActionGetURLData { const char *szUrl; const char *szWin; };
struct ActionSetTargetData { const char *szTarget; };
struct ActionGotoLabelData { const char *szLabel; };
struct ActionDefineFunctionData
{
	const char *szName;
	int nParams;
	const char **aszParams;
	int nBodySize;
	int nMarker0;
	int nMarker1;
};
struct ActionParamInfo { int nRegister; const char *szParamName; };
struct ActionDefineFunction2Data
{
	const char *szName;
	int nParams;
	int nFlags;
	ActionParamInfo *aszParams;
	int nBodySize;
	int nMarker0;
	int nMarker1;
};
struct ActionTryData
{
	int nTrySize;
	int nCatchSize;
	int nFinallySize;
	unsigned char flags;
	const char *szCaughtVarName;
};
struct ActionWithData { int nOffset; };

#define ALIGN_STREAM(p) ((const unsigned char *)(((unsigned int)(p) + 3) & ~3))
#define RELOCATE(field) if (field) *(int *)&(field) += pBase
#define UNRELOCATE(field) if (field) *(int *)&(field) -= pBase

// Native parser extent includes its jump table and byte-index table (2512B).
extern "C" void BfmeAux006FC670(const unsigned char *incomingActionStream, int pBase, AptConstantFile *aConstantFile, int *pnCurrentConstantIndex)
{
	int bUnrelocate = (aConstantFile == 0);
	const unsigned char *aActionStream = incomingActionStream;
	g_releaseVectorAtE17710->ReleaseValues();
	for (;;)
	{
		int eAction = *aActionStream++;
		RUNTIME_ASSERT(AptActionInterpreter::sGlobalTable[eAction].mCheckAlignment == eAction, 0x13E, "sGlobalTable[eAction].mCheckAlignment == eAction");
		if (eAction == 0)
			return;

		switch (eAction)
		{
		case 0xB0:
			aActionStream += 1;
			break;

		case 0xA2: case 0xAE: case 0xAF: case 0xB1: case 0xB2: case 0xB3: case 0xB5:
			aActionStream += 1;
			break;

		case 0xA3: case 0xB6:
			aActionStream += 2;
			break;

		case 0xB4: case 0xB7:
			aActionStream += 4;
			break;

		case 0xA1: case 0xA4: case 0xA5: case 0xA6: case 0xA7:
		{
			aActionStream = ALIGN_STREAM(aActionStream);
			ActionPushStringData *pData = (ActionPushStringData *)aActionStream;
			aActionStream += sizeof(ActionPushStringData);
			if (bUnrelocate)
			{
				UNRELOCATE(pData->szStringToBePushed);
			}
			else
			{
				RUNTIME_ASSERT((unsigned)pData->szStringToBePushed < 0xfffff, 0x1AC, "(unsigned)pData->szStringToBePushed < 0xfffff");
				RELOCATE(pData->szStringToBePushed);
			}
			break;
		}

		case 0x88: case 0x96:
		{
			aActionStream = ALIGN_STREAM(aActionStream);
			ActionPushData *pData = (ActionPushData *)aActionStream;
			aActionStream += sizeof(ActionPushData);
			if (!bUnrelocate)
			{
				RUNTIME_ASSERT((unsigned)pData->items.apItems < 0xfffff, 0x1B7, "(unsigned)pData->items.apItems < 0xfffff");
				RELOCATE(pData->items.apItems);
			}
			if (bUnrelocate)
			{
				for (int i = 0; i < pData->items.nItems; i++)
				{
					AptValue *pAtom = (AptValue *)pData->items.apItems[i];
					if (pAtom->isString())
						Rva0070DDC0Remove((StringNode0070D9F0 *)pAtom->c_string());
					else
						pAtom->Release();
					pData->items.apItems[i] = (void *)*pnCurrentConstantIndex;
					(*pnCurrentConstantIndex)++;
					if ((i % 16) == 0)
						g_releaseVectorAtE17710->ReleaseValues();
				}
			}
			else
			{
				for (int i = 0; i < pData->items.nItems; i++)
				{
					int nConstTableIndex = (int)pData->items.apItems[i];
					RUNTIME_ASSERT(nConstTableIndex == *pnCurrentConstantIndex, 0x1D7, "nConstTableIndex == *pnCurrentConstantIndex");
					(*pnCurrentConstantIndex)++;
					int constantType = aConstantFile->aConstants[nConstTableIndex].type;
					AptValue *pAtom = 0;
					if (constantType == 1)
					{
						// String constants are stored relative to the constant file itself.
						int pBase = (int)aConstantFile;
						RUNTIME_ASSERT((unsigned)aConstantFile->aConstants[nConstTableIndex].szString < 0xfffff, 0x1E5, "(unsigned)aConstantFile->aConstants[nConstTableIndex].szString < 0xfffff");
						RELOCATE(aConstantFile->aConstants[nConstTableIndex].szString);
						pAtom = (AptValue *)Rva0070DBB0Intern(aConstantFile->aConstants[nConstTableIndex].szString);
						UNRELOCATE(aConstantFile->aConstants[nConstTableIndex].szString);
					}
					else if (constantType == 6)
						pAtom = Rva008A4EA0MakeFloat(aConstantFile->aConstants[nConstTableIndex].fValue);
					else if (constantType == 7)
						pAtom = AptInteger::Create(aConstantFile->aConstants[nConstTableIndex].nValue);
					else if (constantType == 8)
						pAtom = new Rva006FB9C0(aConstantFile->aConstants[nConstTableIndex].nValue);
					else if (constantType == 5)
						pAtom = AptBoolean::Create(aConstantFile->aConstants[nConstTableIndex].nValue != 0);
					else if (constantType == 4)
						pAtom = new Rva006FB960(aConstantFile->aConstants[nConstTableIndex].nValue);
					else if (constantType == 3)
						pAtom = gpUndefinedValue;
					RUNTIME_ASSERT(pAtom, 0x20B, "pAtom");
					pData->items.apItems[i] = pAtom;
					if (!pAtom->isString())
						pAtom->AddRef();
					if ((i % 16) == 0)
						g_releaseVectorAtE17710->ReleaseValues();
				}
			}
			if (bUnrelocate)
			{
				UNRELOCATE(pData->items.apItems);
			}
			break;
		}

		case 0x99: case 0x9D: case 0xB8:
			aActionStream = ALIGN_STREAM(aActionStream);
			aActionStream += 4;
			break;

		case 0x83:
		{
			aActionStream = ALIGN_STREAM(aActionStream);
			ActionGetURLData *pData = (ActionGetURLData *)aActionStream;
			aActionStream += sizeof(ActionGetURLData);
			if (bUnrelocate)
			{
				UNRELOCATE(pData->szUrl);
			}
			else
			{
				RUNTIME_ASSERT((unsigned)pData->szUrl < 0xfffff, 0x238, "(unsigned)pData->szUrl < 0xfffff");
				RELOCATE(pData->szUrl);
			}
			if (bUnrelocate)
			{
				UNRELOCATE(pData->szWin);
			}
			else
			{
				RUNTIME_ASSERT((unsigned)pData->szWin < 0xfffff, 0x239, "(unsigned)pData->szWin < 0xfffff");
				RELOCATE(pData->szWin);
			}
			break;
		}

		case 0x81:
			aActionStream = ALIGN_STREAM(aActionStream);
			aActionStream += 4;
			break;

		case 0x9F:
			aActionStream = ALIGN_STREAM(aActionStream);
			aActionStream += 4;
			break;

		case 0x8B:
		{
			aActionStream = ALIGN_STREAM(aActionStream);
			ActionSetTargetData *pData = (ActionSetTargetData *)aActionStream;
			aActionStream += sizeof(ActionSetTargetData);
			if (bUnrelocate)
			{
				UNRELOCATE(pData->szTarget);
			}
			else
			{
				RUNTIME_ASSERT((unsigned)pData->szTarget < 0xfffff, 0x24E, "(unsigned)pData->szTarget < 0xfffff");
				RELOCATE(pData->szTarget);
			}
			break;
		}

		case 0x8C:
		{
			aActionStream = ALIGN_STREAM(aActionStream);
			ActionGotoLabelData *pData = (ActionGotoLabelData *)aActionStream;
			aActionStream += sizeof(ActionGotoLabelData);
			if (bUnrelocate)
			{
				UNRELOCATE(pData->szLabel);
			}
			else
			{
				RUNTIME_ASSERT((unsigned)pData->szLabel < 0xfffff, 0x257, "(unsigned)pData->szLabel < 0xfffff");
				RELOCATE(pData->szLabel);
			}
			break;
		}

		case 0x9B:
		{
			aActionStream = ALIGN_STREAM(aActionStream);
			ActionDefineFunctionData *pData = (ActionDefineFunctionData *)aActionStream;
			aActionStream += sizeof(ActionDefineFunctionData);
			if (bUnrelocate)
			{
				UNRELOCATE(pData->szName);
			}
			else
			{
				RUNTIME_ASSERT((unsigned)pData->szName < 0xfffff, 0x261, "(unsigned)pData->szName < 0xfffff");
				RELOCATE(pData->szName);
			}
			if (!bUnrelocate)
			{
				RUNTIME_ASSERT((unsigned)pData->aszParams < 0xfffff, 0x262, "(unsigned)pData->aszParams < 0xfffff");
				RELOCATE(pData->aszParams);
			}
			for (int i = 0; i < pData->nParams; i++)
			{
				if (bUnrelocate)
				{
					UNRELOCATE(pData->aszParams[i]);
				}
				else
				{
					RUNTIME_ASSERT((unsigned)pData->aszParams[i] < 0xfffff, 0x265, "(unsigned)pData->aszParams[i] < 0xfffff");
					RELOCATE(pData->aszParams[i]);
				}
			}
			if (bUnrelocate)
			{
				UNRELOCATE(pData->aszParams);
			}
			if (bUnrelocate)
			{
				pData->nMarker0 = 0x98765432;
				pData->nMarker1 = 0x12345678;
			}
			break;
		}

		case 0x87:
			aActionStream = ALIGN_STREAM(aActionStream);
			aActionStream += 4;
			break;

		case 0x94:
		{
			aActionStream = ALIGN_STREAM(aActionStream);
			ActionWithData *pData = (ActionWithData *)aActionStream;
			aActionStream += sizeof(ActionWithData);
			if (bUnrelocate)
				pData->nOffset = pData->nOffset - (int)aActionStream;
			else
				pData->nOffset = (int)aActionStream + pData->nOffset;
			break;
		}

		case 0x8E:
		{
			aActionStream = ALIGN_STREAM(aActionStream);
			ActionDefineFunction2Data *pData = (ActionDefineFunction2Data *)aActionStream;
			aActionStream += sizeof(ActionDefineFunction2Data);
			if (bUnrelocate)
			{
				UNRELOCATE(pData->szName);
			}
			else
			{
				RUNTIME_ASSERT((unsigned)pData->szName < 0xfffff, 0x297, "(unsigned)pData->szName < 0xfffff");
				RELOCATE(pData->szName);
			}
			if (!bUnrelocate)
			{
				RUNTIME_ASSERT((unsigned)pData->aszParams < 0xfffff, 0x29A, "(unsigned)pData->aszParams < 0xfffff");
				RELOCATE(pData->aszParams);
			}
			for (int i = 0; i < pData->nParams; i++)
			{
				if (bUnrelocate)
				{
					UNRELOCATE(pData->aszParams[i].szParamName);
				}
				else
				{
					RUNTIME_ASSERT((unsigned)pData->aszParams[i].szParamName < 0xfffff, 0x29E, "(unsigned)pData->aszParams[i].szParamName < 0xfffff");
					RELOCATE(pData->aszParams[i].szParamName);
				}
			}
			if (bUnrelocate)
			{
				UNRELOCATE(pData->aszParams);
			}
			if (bUnrelocate)
			{
				pData->nMarker0 = 0x98765432;
				pData->nMarker1 = 0x12345678;
			}
			break;
		}

		case 0x8F:
		{
			aActionStream = ALIGN_STREAM(aActionStream);
			ActionTryData *pData = (ActionTryData *)aActionStream;
			aActionStream += sizeof(ActionTryData);
			if (pData->flags & 4)
				break;
			if (bUnrelocate)
			{
				UNRELOCATE(pData->szCaughtVarName);
			}
			else
			{
				RUNTIME_ASSERT((unsigned)pData->szCaughtVarName < 0xfffff, 0x2B7, "(unsigned)pData->szCaughtVarName < 0xfffff");
				RELOCATE(pData->szCaughtVarName);
			}
			break;
		}
		}

		g_releaseVectorAtE17710->ReleaseValues();
	}
}
