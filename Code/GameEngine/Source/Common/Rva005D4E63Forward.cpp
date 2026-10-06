// cl: /EHsc
// ?rva005D4E63@Rva005D4E63@@QAEXXZ @0x005D4E63 12B
// Null-guarded tail virtual slot-0 forwarder via member at +0xC.
// Evidence: unlock callee of 0x005D4E84 jmp at 0x005D4E86; ecx is this;
// mov ecx,[ecx+0xC] then test-je then mov eax,[ecx] then jmp [eax].
struct Rva005D4E63Target
{
	virtual void f();
};
class Rva005D4E63
{
public:
	void rva005D4E63();
private:
	char m_pad00[0x0C];
	Rva005D4E63Target *m_target0C;
};
void Rva005D4E63::rva005D4E63()
{
	Rva005D4E63Target *t = m_target0C;
	if (t != 0)
		t->f();
}
