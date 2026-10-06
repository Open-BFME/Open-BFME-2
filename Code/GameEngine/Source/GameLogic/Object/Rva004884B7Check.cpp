// cl: /DNDEBUG /MD /EHsc
// ?rva004884B7@@YA_NPAVObject@@@Z @0x4884B7 (37B): predicate over an Object's
// AIUpdateInterface (+0x258, retail-measured): false when null, false when the
// slot-0x174 check fails, otherwise the slot-0x190 result normalized. Both
// callees are virtual (slots 93/100, no REL32, no pins); the replica carries
// pads. Opaque free-function name: the reloc-row ctor identity is refuted by
// the shape (bool-returning predicate, not a constructor).

class AIUpdateInterface
{
public:
	virtual void _V00() = 0;
	virtual void _V01() = 0;
	virtual void _V02() = 0;
	virtual void _V03() = 0;
	virtual void _V04() = 0;
	virtual void _V05() = 0;
	virtual void _V06() = 0;
	virtual void _V07() = 0;
	virtual void _V08() = 0;
	virtual void _V09() = 0;
	virtual void _V10() = 0;
	virtual void _V11() = 0;
	virtual void _V12() = 0;
	virtual void _V13() = 0;
	virtual void _V14() = 0;
	virtual void _V15() = 0;
	virtual void _V16() = 0;
	virtual void _V17() = 0;
	virtual void _V18() = 0;
	virtual void _V19() = 0;
	virtual void _V20() = 0;
	virtual void _V21() = 0;
	virtual void _V22() = 0;
	virtual void _V23() = 0;
	virtual void _V24() = 0;
	virtual void _V25() = 0;
	virtual void _V26() = 0;
	virtual void _V27() = 0;
	virtual void _V28() = 0;
	virtual void _V29() = 0;
	virtual void _V30() = 0;
	virtual void _V31() = 0;
	virtual void _V32() = 0;
	virtual void _V33() = 0;
	virtual void _V34() = 0;
	virtual void _V35() = 0;
	virtual void _V36() = 0;
	virtual void _V37() = 0;
	virtual void _V38() = 0;
	virtual void _V39() = 0;
	virtual void _V40() = 0;
	virtual void _V41() = 0;
	virtual void _V42() = 0;
	virtual void _V43() = 0;
	virtual void _V44() = 0;
	virtual void _V45() = 0;
	virtual void _V46() = 0;
	virtual void _V47() = 0;
	virtual void _V48() = 0;
	virtual void _V49() = 0;
	virtual void _V50() = 0;
	virtual void _V51() = 0;
	virtual void _V52() = 0;
	virtual void _V53() = 0;
	virtual void _V54() = 0;
	virtual void _V55() = 0;
	virtual void _V56() = 0;
	virtual void _V57() = 0;
	virtual void _V58() = 0;
	virtual void _V59() = 0;
	virtual void _V60() = 0;
	virtual void _V61() = 0;
	virtual void _V62() = 0;
	virtual void _V63() = 0;
	virtual void _V64() = 0;
	virtual void _V65() = 0;
	virtual void _V66() = 0;
	virtual void _V67() = 0;
	virtual void _V68() = 0;
	virtual void _V69() = 0;
	virtual void _V70() = 0;
	virtual void _V71() = 0;
	virtual void _V72() = 0;
	virtual void _V73() = 0;
	virtual void _V74() = 0;
	virtual void _V75() = 0;
	virtual void _V76() = 0;
	virtual void _V77() = 0;
	virtual void _V78() = 0;
	virtual void _V79() = 0;
	virtual void _V80() = 0;
	virtual void _V81() = 0;
	virtual void _V82() = 0;
	virtual void _V83() = 0;
	virtual void _V84() = 0;
	virtual void _V85() = 0;
	virtual void _V86() = 0;
	virtual void _V87() = 0;
	virtual void _V88() = 0;
	virtual void _V89() = 0;
	virtual void _V90() = 0;
	virtual void _V91() = 0;
	virtual void _V92() = 0;
	virtual int isFirstCheck() = 0;			// slot 93 (0x174)
	virtual void _V94() = 0;
	virtual void _V95() = 0;
	virtual void _V96() = 0;
	virtual void _V97() = 0;
	virtual void _V98() = 0;
	virtual void _V99() = 0;
	virtual int isSecondCheck() = 0;		// slot 100 (0x190)
};

class Object
{
public:
	unsigned char m_pad[0x258];
	AIUpdateInterface *m_aiUpdate;			// +0x258 (retail-measured)
};

// ?rva004884B7@@YA_NPAVObject@@@Z
bool rva004884B7(Object *obj)
{
	int ok = 0;
	AIUpdateInterface *ai = obj->m_aiUpdate;
	if (ai != 0) {
		if (ai->isFirstCheck() != 0)
			ok = ai->isSecondCheck();
	}
	return ok != 0;
}
