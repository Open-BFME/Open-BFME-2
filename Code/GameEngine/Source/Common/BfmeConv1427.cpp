// cl: /Od

class BfmeStrVME
{
public:
	void bfmeResizeVME(unsigned newLength, char fillCharacter);
	void bfmeEraseVME(char *a, char *b);
	void bfmeAppendVME(unsigned n, char c);
	char *m_bfme00;
	char *m_bfme04;
};

void BfmeStrVME::bfmeResizeVME(unsigned newLength, char fillCharacter)
{
	if (newLength <= (unsigned)(m_bfme04 - m_bfme00))
	{
		char *n1 = m_bfme04;
		char *n2;
		char *n3;
		char *n4 = m_bfme00;
		bfmeEraseVME(n4 + newLength, n1);
	}
	else
		bfmeAppendVME(newLength - (unsigned)(m_bfme04 - m_bfme00), fillCharacter);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeFwdTwoSVA@BfmeThingSVA@@QAEXHH@Z=?bfmeResizeVME@BfmeStrVME@@QAEXID@Z")

// The retail call in this body reads 0x00029380, an address the ledger already
// carries as ?append@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@ID@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?bfmeAppendVME@BfmeStrVME@@QAEXID@Z=?append@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@ID@Z")
