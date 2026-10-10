// ?rva002AA245@Player@@QBE_NXZ @ 0x002AA245 (18B): null-checked byte flag
// getter (mov eax,[ecx+0x34] / test eax,eax / je null / movzx eax,byte
// [eax+0x151] / ret / xor eax,eax / ret). Callers at 0x0004A1E4, 0x0004AB54,
// 0x00281B3C and 18 more; prev 0x002AA22A and next 0x002AA257 are disp32
// family neighbours in the same dir.
// Target facts: all 21 retail REL32 callers test AL only (test al,al then
// je/jne), so the return type is bool; the receivers are Player pointers
// (getControllingPlayer results at 0x00281B3C and 0x00491BBE, getNthPlayer
// results in the PlayerList scans). The whole-EAX movzx/xor shape is what
// cl emits for a bool return of `ptr ? ptr->boolField : 0` (the int 0 makes
// the conditional an int that is known to be 0 or 1).
// Inference: the field meaning and a real method name are unrecovered, so the
// name stays address-derived (formerly rowed as
// Rva002AA245MovzxByteChaseField::get returning unsigned int).
// No // cl: line (defaults match the frameless shape, like the neighbours).
struct Rva002AA245Part
{
	char m_pad[0x151];
	bool m_flag;
};
class Player
{
public:
	bool rva002AA245() const;
	char m_lead[0x34];
	Rva002AA245Part *m_ptr;
};
bool Player::rva002AA245() const
{
	return m_ptr ? m_ptr->m_flag : 0;
}
