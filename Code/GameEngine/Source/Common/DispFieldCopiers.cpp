// Field copiers: ten-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<SRC>] / mov [ecx+<DST>],eax / ret
//
// One int is read at a fixed displacement from `this` and stored at a
// second displacement. Members before, between and after the accessed ones
// are spelled as lead arrays because their types are not witnessed here,
// only their total size. Identity is not recovered: every name is derived
// from its address.
// No // cl: line (defaults match the frameless ten-byte shape).
#define BFME_FIELD_COPIER(NAME, SRC, DST) \
	class NAME \
	{ \
	public: \
		void copy(); \
		char m_lead[SRC]; \
		int m_src; \
		char m_mid[(DST) - (SRC) - 4]; \
		int m_dst; \
	}; \
	void NAME::copy() \
	{ \
		m_dst = m_src; \
	}

BFME_FIELD_COPIER(Rva0028A5F9FieldCopy, 0x40, 0x180)

// Reference-derived pointer-head copy: BF1 9cbfb551fe20dae985f91f2319d8997287b6a705,
// game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/ClearPosition0027B000.cpp,
// BfmeWideResult::first supplied the lead. That iterator identity is not proven here.
// Target proof: decoding from the known2635C2/137 entry ends at RET26364A;
// independent26364B..263653 loads this->word0 as a pointer, copies pointee word0
// to pointee+C, then RET0 before the next known263653 entry. Original class,
// complete layout and field meanings remain unknown; these are raw word views.
class Rva0026364BFieldCopy
{
public:
    void copyHead();
    unsigned *m_words;
};
void Rva0026364BFieldCopy::copyHead()
{
    m_words[3]=m_words[0];
}
