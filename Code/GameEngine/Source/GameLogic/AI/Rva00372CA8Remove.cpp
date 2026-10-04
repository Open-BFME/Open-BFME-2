// cl: /O1 /DNDEBUG /MD /GX
//
// ?rva00372CA8@Rva00372CA8@@QAEXH@Z retail 0x00372CA8 68 bytes.
// Honest-address __thiscall method: fixed 8-slot dword array at +0x20 with count at +0x4C.
// Removes first slot equal to arg then shifts tail down via rep movsd clears +0x3C and dec count.
// Evidence: callers at 0x00373193 and 0x0037319D call it symmetrically on each other's object
// plus caller at 0x00373238 with TerrainLogic +0x8C result as this; arrays hold object pointers
// compared as dwords. Unsigned indices give retail jb/jae and zero inside break gives
// retail and-before-cmp with jmp-over-and shape. /O1 gives push-8/pop-ecx inc and and-m-0 idioms.
// Owner unknown so padded Rva00372CA8 holder class.
class Rva00372CA8
{
public:
	void rva00372CA8(int val);
	bool rva00372CEC(int val);
private:
	char m_pad00[0x20];
	int m_slots[8];
	char m_pad40[0x0C];
	int m_count;
};
void Rva00372CA8::rva00372CA8(int val)
{
	unsigned int i;
	for (i = 0; i < 8; ++i) {
		if (m_slots[i] == val) {
			m_slots[i] = 0;
			break;
		}
	}
	if (i >= 8)
		return;
	++i;
	if (i < 8) {
		for (unsigned int j = i; j < 8; ++j)
			m_slots[j - 1] = m_slots[j];
	}
	m_slots[7] = 0;
	--m_count;
}
bool Rva00372CA8::rva00372CEC(int val)
{
	unsigned int n = (unsigned int)m_count;
	for (unsigned int i = 0; i < n; ++i) {
		if (m_slots[i] == val)
			return true;
	}
	return false;
}
