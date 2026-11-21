// AptAnimationPoolData: canonical declarations for the Apt pool behind the global Apt pointer.
// Fields are carved where retail stores and reads prove offset and size; the rest of the
// 0xB4-byte object stays opaque, and each call resolves to the unit's ledger row or pin.
#ifndef CANONICAL_APTANIMATIONPOOLDATA_H
#define CANONICAL_APTANIMATIONPOOLDATA_H

class AptActionQueueC;
class AptCIH;
class AptValue;
struct BfmeMesh1290;
struct BfmeTransform2_1290;
struct AptMatrix;
struct ButtonHitTestRecord;
class Rva006E1E30;

class AptAnimationPoolData
{
public:
	// Sparse instance set, laid out as retail's _AptSet (maElements is named by its asserts).
	struct InstSet
	{
		unsigned short mnCount;
		unsigned short mnSize;
		AptCIH **maElements;
		int GetSize() const { return mnSize; }
	};

	void PreDestroy();
	void ProcessButtonState();
	void _tickNewInsts();
	bool bfmeMeshHitTest1290(BfmeMesh1290 *mesh, const BfmeTransform2_1290 *transform, int pointX, int pointY);
	void appendButtonToBIL(AptCIH *cih, AptMatrix *matrix);
	void clearBIL();
	void removeFromBIL(AptCIH *);
	void removeTimerFunctions(AptCIH *);
	void rva006E6540();
	AptCIH *rva006FA420(int x, int y);
	void rva006FA100(AptCIH *, int);
	void rva006FA7E0(bool first, bool enabled, int value);
	void rva006FB120(int eType, int state, int value, int device, char isFirst);
	void rva006F7720Sub(void *ctx, int arg);
	bool rva006F9FC0(Rva006E1E30 *object, int);
	void rva006FB910();
	void setValidFocusButton();
	void tickIntervalTimers(int);

	AptCIH **apNewInsts;                      // +0x00, named by retail's assert "apNewInsts != NULL"
	int m_04;                                 // +0x04, count of apNewInsts
	InstSet buttonSet;                        // +0x08, buttons walked for focus and key actions
	int mBILCount;                            // +0x10
	ButtonHitTestRecord *aButtonInstanceList; // +0x14, 28-byte records
	char m_opaque18[0x28 - 0x18];
	InstSet inputSet;                         // +0x28, named by retail's assert "inputSet.maElements[i]->isCIH()"
	char m_opaque30[0x68 - 0x30];
	AptValue *m68;                            // +0x68, topmost hit instance
	AptCIH *m_current;                        // +0x6C, focused button instance (AddRef held)
	char m_opaque70[0x74 - 0x70];
	int m_74;
	int m_78;
	char m_opaque7C[0xA0 - 0x7C];
	AptActionQueueC *mpActionQueue;           // +0xA0
	char m_opaqueA4[0xB4 - 0xA4];
};

#endif // CANONICAL_APTANIMATIONPOOLDATA_H
