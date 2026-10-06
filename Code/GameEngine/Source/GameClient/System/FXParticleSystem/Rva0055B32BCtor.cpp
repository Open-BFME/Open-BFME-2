// cl: /MD /EHsc
// ??0Rva0055B32B@@QAE@XZ @0x0055B32B 60B
// Default EH ctor with 8 Keyframes at +4 and vtable 0x0081D134.
// Evidence: thiscall 0 args ret void; __EH_prolog row 0x629188 plus state 0;
// vector ctor iterator row 0x1423 with Keyframe ctor row 0x5993CD count 8 size 8;
// vtable store VA 0x00C1D134 before members; caller 0x0055B552; neighbours 0x0055B30F and 0x0055B367.
struct Keyframe
{
	Keyframe();
	float m_value;
	unsigned int m_frame;
};

class EmptyBase0055B32B
{
public:
	EmptyBase0055B32B() {}
	virtual ~EmptyBase0055B32B();
};

class Rva0055B32B : public EmptyBase0055B32B
{
public:
	Rva0055B32B();
private:
	Keyframe m_keys[8];
};

Rva0055B32B::Rva0055B32B()
{
}
