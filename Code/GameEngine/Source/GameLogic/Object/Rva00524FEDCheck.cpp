// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// ?Rva00524FEDCheck@@YGEPAVObject@@@Z @0x00524FED (83B).
// Free-function Object validity gate (chain lane: calls the rowed
// ?isSelectable@Object@@QBE_NXZ at 0x0028D7FD, which this session landed).
// Returns 0 when the Object is null, when the +0x84 int reads 0 through the
// rowed ?getDesiredGatherers@BuildListInfo@@QAEHXZ (7B mov eax,[ecx+0x84]; ret,
// ICF-shared with the Object +0x84 sub-pointer null check per
// ObjectRva0028AE9BSetter.cpp), when private status +0x438 bit0
// (EFFECTIVELY_DEAD) is set, when isSelectable is false, when AI at +0x258 is
// null, when AI slot92 (virtual +0x170) returns null, else returns the inverse
// of slot8 (virtual +0x20). Callers at 0x0052606D and 0x00526480; landing this
// unblocks 0x00526008/169 and 0x00526421/142 per the packet.
// The UChar (E) return is codegen-proven: retail ends neg al / sbb al,al /
// inc al (byte), not the bool dword shape, per the STL recipe note.

typedef bool Bool;
typedef unsigned char UChar;

class Object;
class BuildListInfo
{
public:
	int getDesiredGatherers();
};

class RetVal
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual UChar s08();
};

class AIUpdate
{
public:
	virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
	virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
	virtual void a08(); virtual void a09(); virtual void a10(); virtual void a11();
	virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
	virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
	virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23();
	virtual void a24(); virtual void a25(); virtual void a26(); virtual void a27();
	virtual void a28(); virtual void a29(); virtual void a30(); virtual void a31();
	virtual void a32(); virtual void a33(); virtual void a34(); virtual void a35();
	virtual void a36(); virtual void a37(); virtual void a38(); virtual void a39();
	virtual void a40(); virtual void a41(); virtual void a42(); virtual void a43();
	virtual void a44(); virtual void a45(); virtual void a46(); virtual void a47();
	virtual void a48(); virtual void a49(); virtual void a50(); virtual void a51();
	virtual void a52(); virtual void a53(); virtual void a54(); virtual void a55();
	virtual void a56(); virtual void a57(); virtual void a58(); virtual void a59();
	virtual void a60(); virtual void a61(); virtual void a62(); virtual void a63();
	virtual void a64(); virtual void a65(); virtual void a66(); virtual void a67();
	virtual void a68(); virtual void a69(); virtual void a70(); virtual void a71();
	virtual void a72(); virtual void a73(); virtual void a74(); virtual void a75();
	virtual void a76(); virtual void a77(); virtual void a78(); virtual void a79();
	virtual void a80(); virtual void a81(); virtual void a82(); virtual void a83();
	virtual void a84(); virtual void a85(); virtual void a86(); virtual void a87();
	virtual void a88(); virtual void a89(); virtual void a90(); virtual void a91();
	virtual RetVal *a92();
};

class Object
{
public:
	Bool isSelectable() const;

	char m_p00[0x258];
	AIUpdate *m_ai;
	char m_p25C[0x438 - 0x25C];
	unsigned char m_priv;
};

UChar __stdcall Rva00524FEDCheck(Object *o)
{
	if (!o)
		return 0;
	if (((BuildListInfo *)o)->getDesiredGatherers() == 0)
		return 0;
	if ((o->m_priv & 1) != 0)
		return 0;
	if (!o->isSelectable())
		return 0;
	AIUpdate *ai = o->m_ai;
	if (!ai)
		return 0;
	RetVal *r = ai->a92();
	if (r)
		return !r->s08();
	return 0;
}
