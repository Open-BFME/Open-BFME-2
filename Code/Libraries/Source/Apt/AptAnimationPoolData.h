// AptAnimationPoolData: canonical declarations for the Apt pool behind the global Apt pointer.
// Fields are carved where retail stores and reads prove offset and size; the rest of the
// 0xB4-byte object stays opaque, and each call resolves to the unit's ledger row or pin.
#ifndef CANONICAL_APTANIMATIONPOOLDATA_H
#define CANONICAL_APTANIMATIONPOOLDATA_H

class AptCIH;
struct BfmeMesh1290;
struct BfmeTransform2_1290;
struct AptMatrix;
struct ButtonHitTestRecord;
class Rva006E1E30;

class AptAnimationPoolData
{
public:
	void PreDestroy();
	void _tickNewInsts();
	bool bfmeMeshHitTest1290(BfmeMesh1290 *mesh, const BfmeTransform2_1290 *transform, int pointX, int pointY);
	void appendButtonToBIL(AptCIH *cih, AptMatrix *matrix);
	void clearBIL();
	void removeFromBIL(AptCIH *);
	void removeTimerFunctions(AptCIH *);
	void rva006E6540();
	AptCIH *rva006FA420(int x, int y);
	void rva006FA100(AptCIH *, int);
	void rva006F7720Sub(void *ctx, int arg);
	bool rva006F9FC0(Rva006E1E30 *object, int);
	void rva006FB910();
	void setValidFocusButton();
	void tickIntervalTimers(int);

	AptCIH **apNewInsts;                      // +0x00, named by retail's assert "apNewInsts != NULL"
	int m_04;                                 // +0x04, count of apNewInsts
	unsigned short m_cihCount;                // +0x08, live entries in m_cihEntries
	unsigned short m_cihCapacity;             // +0x0A, slots in m_cihEntries
	AptCIH **m_cihEntries;                    // +0x0C, sparse instance table walked for focus
	int mBILCount;                            // +0x10
	ButtonHitTestRecord *aButtonInstanceList; // +0x14, 28-byte records
	char m_opaque18[0x6C - 0x18];
	AptCIH *m_current;                        // +0x6C, focused button instance (AddRef held)
	char m_opaque70[0x74 - 0x70];
	int m_74;
	int m_78;
	char m_opaque7C[0xB4 - 0x7C];
};

#endif // CANONICAL_APTANIMATIONPOOLDATA_H
