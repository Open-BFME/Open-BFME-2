// cl: /O1 /DNDEBUG /MD /EHsc
// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva00232A42@Keyboard@@QAEXXZ @0x00232A42 (166B): Keyboard key-list
// resync over the m_keys vector walked as stride-8 KeyboardIO records.
// Each record refreshes its kind-indexed m_keyStatus slot (flag/key/frame),
// kind 0x0F sets the record flag when either status byte carries bit 2, and
// seven kinds route through the pinned handler 0x00232763; then rowed
// checkKeyRepeat 0x002329D3 runs and nonzero modifiers OR into every
// record. Per-statement kind re-reads (aliasing blocks CSE) plus the direct
// slot indexing reproduce retail. Layout reuses Keyboard.cpp's proven
// Keyboard model; KeyboardIO field roles are structural.
class AsciiStringMember
{
public:
	~AsciiStringMember();
};

class GameEngineDeletingBase
{
public:
	GameEngineDeletingBase() throw();
	virtual ~GameEngineDeletingBase();

private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

struct BfmeE16 { float x; float y; float z; float w; };

namespace _STL
{

template <class Element> class allocator
{
public:
	allocator() {}
};

template <class Item, class Alloc> class _Vector_base
{
public:
	_Vector_base(const Alloc &alloc) throw();
	void *_M_start;
	void *_M_finish;
	void *_M_end;
};

}

struct KeyboardIO
{
	unsigned char m_kind;
	unsigned char m_f1;
	unsigned short m_f2;
	char m_pad[4];
};

struct KeySlot
{
	unsigned char m_pad0;
	unsigned char m_flag;
	unsigned short m_key;
	unsigned int m_frame;
};

class Keyboard : public GameEngineDeletingBase
{
public:
	void rva00232A42();

protected:
	bool checkKeyRepeat();
	void handleKind(unsigned short kind);
	unsigned short m_modifiers; // +0x0C
	unsigned char m_shift2Key; // +0x0E
	_STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > m_keys; // +0x10
	unsigned char m_keyStatus[0x800]; // +0x1C
	unsigned char m_keyNames[0x600]; // +0x81C
	int m_inputFrame; // +0xE1C
};

void Keyboard::rva00232A42()
{
	KeyboardIO *rec = (KeyboardIO *)m_keys._M_start;
	KeyboardIO *end = (KeyboardIO *)m_keys._M_finish;
	while (rec != end) {
		((KeySlot *)&m_keyStatus)[rec->m_kind].m_key = rec->m_f2;
		((KeySlot *)&m_keyStatus)[rec->m_kind].m_flag = rec->m_f1;
		((KeySlot *)&m_keyStatus)[rec->m_kind].m_frame = m_inputFrame;
		unsigned char kind = rec->m_kind;
		if (kind == 0x0F) {
			if (((m_keyStatus[0x1C2] & 2) != 0) || ((m_keyStatus[0x5C2] & 2) != 0))
				rec->m_f1 = 1;
		}
		else if (kind == 0x3A || kind == 0x1D || kind == 0x9D || kind == 0x2A || kind == 0x36 || kind == 0x38 || kind == 0xB8) {
			handleKind((unsigned short)kind);
		}
		++rec;
	}
	checkKeyRepeat();
	if (m_modifiers != 0) {
		KeyboardIO *last = (KeyboardIO *)m_keys._M_finish;
		KeyboardIO *p = (KeyboardIO *)m_keys._M_start;
		while (p != last) {
			p->m_f2 |= m_modifiers;
			++p;
		}
	}
}
