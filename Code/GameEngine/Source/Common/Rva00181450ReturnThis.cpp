// Return-this callback at game.dat 0x181450: `mov eax,ecx / ret`.
// Thirteen `push 0x581450` sites across the image register this address as a
// function pointer, so it is a genuine tiny method rather than a shared
// tail, even though it has no direct E8 callers. It returns its own `this`
// pointer with no displacement, the zero-offset sibling of the disp8 LEA
// getter family (kept in its own unit because the shape and the spelling
// differ). Owner unproven: the holder class is TU-local and address-derived.
// No // cl: line (defaults match the frameless three-byte shape).
class Rva00181450ReturnThis
{
public:
	void *get() const;
};
void *Rva00181450ReturnThis::get() const
{
	return (void *)this;
}
