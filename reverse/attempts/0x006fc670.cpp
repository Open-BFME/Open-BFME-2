// _BfmeAux006FC670
// partial score=0.91 date=2026-10-09
// cl: /O2 /G6 /arch:SSE /DNDEBUG /MD /EHs
//
// _BfmeAux006FC670 (pinned C name) retail 0x006FC670..0x006FD040 (2512 bytes:
// the 2398-byte body through RET at 0x006FCFCD, two pad bytes, the 14-entry
// jump table at 0x006FCFD0 and its 56-entry byte index at 0x006FD008).
//
// Apt action-stream relocation from AptActionInterpreter.cpp (every assert
// passes that file name; texts and lines copied from retail). It walks the
// action stream checking each action against
// AptActionInterpreter::sGlobalTable[eAction].mCheckAlignment (line 0x13E)
// and stops at action 0. With a constant file it turns the stream's
// pBase-relative string and table offsets into pointers (each asserted below
// 0xFFFFF first) and replaces each ConstantPool/Push item index (checked
// against *pnCurrentConstantIndex and counted) by its atom: a pooled string
// (rowed StringPool intern 0x0070DBB0 with the constant string temporarily
// rebased on the constant file) or a float / integer / boolean / two pooled
// 12-byte value types / the undefined value, add-ref'ing every non-string.
// Without a constant file (the NULL-argument forwarder 0x006FD040) it undoes
// that: strings leave the pool (rowed RemoveFromPool 0x0070DDC0), other atoms
// are released, the indices are renumbered from *pnCurrentConstantIndex and
// the pointers go back to offsets; DefineFunction bodies get the
// 0x98765432/0x12345678 markers. Every 16 items and after each action the
// release vector (rowed AptValueVector::ReleaseValues 0x006E6D90) is drained.
// Callers: the asserting forwarder 0x006FD060 (aActionStream pBase
// aConstantFile) and 0x006FD040.

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

class AptString;

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();
	bool isString() const;
	AptString *c_string() const;
protected:
	unsigned int m_valueFlags;
};

class AptValueVector
{
public:
	void ReleaseValues();
};
extern AptValueVector *g_releaseVectorAtE17710;

class AptInteger { public: static AptValue *Create(int value); };
class AptBoolean { public: static AptValue *Create(bool value); };
AptValue *Rva008A4EA0MakeFloat(float value);
extern AptValue *gpUndefinedValue;

struct StringNode0070D9F0;
StringNode0070D9F0 *Rva0070DBB0Intern(const char *string);
void Rva0070DDC0Remove(StringNode0070D9F0 *node);

class Rva006DB160 { public: void *allocBlock(int blockSize); };
extern Rva006DB160 *g_pChainBlockAllocator;
void Rva006D8680Free(void *block, int blockSize);

// The two pooled 12-byte value types built from constant types 8 and 4.
class Rva006FB9C0 : public AptValue
{
public:
	Rva006FB9C0(int value);
	static void *operator new(unsigned int n) { return g_pChainBlockAllocator->allocBlock(n); }
	static void operator delete(void *p, unsigned int n) { Rva006D8680Free(p, n); }
private:
	int m_value;
};

class Rva006FB960 : public AptValue
{
public:
	Rva006FB960(int value);
	static void *operator new(unsigned int n) { return g_pChainBlockAllocator->allocBlock(n); }
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

class AptActionInterpreter
{
	friend void BfmeAux006FC670(const unsigned char *, int, AptConstantFile *, int *);
	struct FunctionTable
	{
		int mCheckAlignment;
		void *mFunctionPointer;
	};
	static FunctionTable sGlobalTable[];
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

extern "C" void BfmeAux006FC670(const unsigned char *aActionStream, int pBase, AptConstantFile *aConstantFile, int *pnCurrentConstantIndex)
{
	int bUnrelocate = (aConstantFile == 0);
	g_releaseVectorAtE17710->ReleaseValues();
	for (;;)
	{
		int eAction = *aActionStream++;
		RUNTIME_ASSERT(AptActionInterpreter::sGlobalTable[eAction].mCheckAlignment == eAction, 0x13E, "sGlobalTable[eAction].mCheckAlignment == eAction");
		if (eAction == 0)
			return;

		switch (eAction)
		{
		case 0xA2: case 0xAE: case 0xAF: case 0xB0: case 0xB1: case 0xB2: case 0xB3: case 0xB5:
			aActionStream += 1;
			break;

		case 0xA3: case 0xB6:
			aActionStream += 2;
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
				for (int i = 0; i < pData->items.nItems; i++)
				{
					int nConstTableIndex = (int)pData->items.apItems[i];
					RUNTIME_ASSERT(nConstTableIndex == *pnCurrentConstantIndex, 0x1D7, "nConstTableIndex == *pnCurrentConstantIndex");
					(*pnCurrentConstantIndex)++;
					AptValue *pAtom = 0;
					if (aConstantFile->aConstants[nConstTableIndex].type == 1)
					{
						RUNTIME_ASSERT((unsigned)aConstantFile->aConstants[nConstTableIndex].szString < 0xfffff, 0x1E5, "(unsigned)aConstantFile->aConstants[nConstTableIndex].szString < 0xfffff");
						if (aConstantFile->aConstants[nConstTableIndex].szString)
							*(int *)&aConstantFile->aConstants[nConstTableIndex].szString += (int)aConstantFile;
						pAtom = (AptValue *)Rva0070DBB0Intern(aConstantFile->aConstants[nConstTableIndex].szString);
						if (aConstantFile->aConstants[nConstTableIndex].szString)
							*(int *)&aConstantFile->aConstants[nConstTableIndex].szString -= (int)aConstantFile;
					}
					else if (aConstantFile->aConstants[nConstTableIndex].type == 6)
						pAtom = Rva008A4EA0MakeFloat(aConstantFile->aConstants[nConstTableIndex].fValue);
					else if (aConstantFile->aConstants[nConstTableIndex].type == 7)
						pAtom = AptInteger::Create(aConstantFile->aConstants[nConstTableIndex].nValue);
					else if (aConstantFile->aConstants[nConstTableIndex].type == 8)
						pAtom = new Rva006FB9C0(aConstantFile->aConstants[nConstTableIndex].nValue);
					else if (aConstantFile->aConstants[nConstTableIndex].type == 5)
						pAtom = AptBoolean::Create(aConstantFile->aConstants[nConstTableIndex].nValue != 0);
					else if (aConstantFile->aConstants[nConstTableIndex].type == 4)
						pAtom = new Rva006FB960(aConstantFile->aConstants[nConstTableIndex].nValue);
					else if (aConstantFile->aConstants[nConstTableIndex].type == 3)
						pAtom = gpUndefinedValue;
					RUNTIME_ASSERT(pAtom, 0x20B, "pAtom");
					pData->items.apItems[i] = pAtom;
					if (!pAtom->isString())
						pAtom->AddRef();
					if ((i % 16) == 0)
						g_releaseVectorAtE17710->ReleaseValues();
				}
			}
			else
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
				UNRELOCATE(pData->items.apItems);
			}
			break;
		}

		case 0x83:
		{
			aActionStream = ALIGN_STREAM(aActionStream);
			ActionGetURLData *pData = (ActionGetURLData *)aActionStream;
			aActionStream += sizeof(ActionGetURLData);
			if (bUnrelocate)
			{
				UNRELOCATE(pData->szUrl);
				UNRELOCATE(pData->szWin);
			}
			else
			{
				RUNTIME_ASSERT((unsigned)pData->szUrl < 0xfffff, 0x238, "(unsigned)pData->szUrl < 0xfffff");
				RELOCATE(pData->szUrl);
				RUNTIME_ASSERT((unsigned)pData->szWin < 0xfffff, 0x239, "(unsigned)pData->szWin < 0xfffff");
				RELOCATE(pData->szWin);
			}
			break;
		}

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
				pData->nMarker0 = 0x98765432;
				pData->nMarker1 = 0x12345678;
			}
			break;
		}

		case 0x81: case 0x87: case 0x99: case 0x9D: case 0x9F: case 0xB8:
			aActionStream = ALIGN_STREAM(aActionStream);
			aActionStream += 4;
			break;

		case 0xB4: case 0xB7:
			aActionStream += 4;
			break;

		case 0x94:
		{
			aActionStream = ALIGN_STREAM(aActionStream);
			ActionWithData *pData = (ActionWithData *)aActionStream;
			aActionStream += sizeof(ActionWithData);
			if (bUnrelocate)
				pData->nOffset -= (int)aActionStream;
			else
				pData->nOffset += (int)aActionStream;
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
