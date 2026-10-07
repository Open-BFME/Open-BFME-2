// cl: /DNDEBUG /MD /EHs-c-
// ?rva00503E17@Rva00503E17@@QAEMXZ @0x00503E17 56B
// Bezier caller sibling of 0x00503DEB: Evaluate(0.0 g_863BFC 0.5 g_7BB8D8 minus m_14).
// SSE for t computation, x87 for args. Unlocks 0x005042F2.
// Evidence: movss global minus [ecx+0x14] then fldz fld globals pattern, caller 0x005043DF.
float __cdecl Rva00503D26Evaluate(float a, float b, float c, float t);
extern float g_Va00863BFC;
// g_Va00863BFC: matched references place it at VA 0xc63bfc (retail .rdata value 0.41666666f).
float g_Va00863BFC = 0.41666666f;
struct Rva00503E17
{
	char m_pad[0x14];
	float m_14;
	float rva00503E17();
};
float Rva00503E17::rva00503E17()
{
	return Rva00503D26Evaluate(0.0f, g_Va00863BFC, 0.5f, 1.0f - m_14);
}

// ?rva00503E76@Rva00503E76@@QAEXPAURva00503E76Arg1@@@Z @0x00503E76 65B
// Leaf called from 0x00503EBF, unblocks 0x00503EB7, LINK BONUS 196B.
// Evidence: 5 virtual calls on arg1 slots 0x60 0x70 x3 0x78, this+0xC +0x10
// +0x14 +0x18 passed by address, this and arg1 live across calls in edi esi,
// no EH no float no vtable, ret 4.
struct Rva00503E76Arg1
{
	virtual void _slot00() = 0;
	virtual void _slot01() = 0;
	virtual void _slot02() = 0;
	virtual void _slot03() = 0;
	virtual void _slot04() = 0;
	virtual void _slot05() = 0;
	virtual void _slot06() = 0;
	virtual void _slot07() = 0;
	virtual void _slot08() = 0;
	virtual void _slot09() = 0;
	virtual void _slot10() = 0;
	virtual void _slot11() = 0;
	virtual void _slot12() = 0;
	virtual void _slot13() = 0;
	virtual void _slot14() = 0;
	virtual void _slot15() = 0;
	virtual void _slot16() = 0;
	virtual void _slot17() = 0;
	virtual void _slot18() = 0;
	virtual void _slot19() = 0;
	virtual void _slot20() = 0;
	virtual void _slot21() = 0;
	virtual void _slot22() = 0;
	virtual void _slot23() = 0;
	virtual void _slot24(void *) = 0;
	virtual void _slot25() = 0;
	virtual void _slot26() = 0;
	virtual void _slot27() = 0;
	virtual void _slot28(void *) = 0;
	virtual void _slot29() = 0;
	virtual void _slot30(void *) = 0;
};
class Rva00503E76
{
public:
	void rva00503E76(Rva00503E76Arg1 *a1);
private:
	char m_pad00[0x0C];
	char m_0C[4];
	char m_10[4];
	char m_14[4];
	char m_18[4];
};
void Rva00503E76::rva00503E76(Rva00503E76Arg1 *a1)
{
	a1->_slot24(this);
	a1->_slot28(&m_0C);
	a1->_slot28(&m_10);
	a1->_slot28(&m_14);
	a1->_slot30(&m_18);
}

// ?Rva00503EB7Call@@YAPAURva00503E76Arg1@@PAU1@PAVRva00503E76@@@Z @0x00503EB7 18B
// Wrapper call relationship is target evidence; the address-derived name is
// used because the stored callback has no independent semantic name.
Rva00503E76Arg1 *__cdecl Rva00503EB7Call(Rva00503E76Arg1 *a1, Rva00503E76 *self)
{
	self->rva00503E76(a1);
	return a1;
}
