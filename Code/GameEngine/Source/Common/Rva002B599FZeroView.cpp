// ?rva002B599F@Rva002B599FZeroView@@QAEPAV1@XZ @0x002B599F 11B
// cl: /O1 /Ob1
// Retail 0x002B599F 11B gap between 0x002B598E end and 0x002B59AA start.
// mov eax ecx and [eax+0xC] 0 and [eax+0x10] 0 ret. TU-local honest view.
// Donor Whole BFME1 game/GameEngine/Source/Common/S1ZeroingConstructors.cpp
// revision 5cc75ddda6455c338a5068307e587a793f96d6b3 blob b187205c78b391e963d12db299c952caf0cfa20f.
// No callers. Boundary proved by neighbours. No original class asserted.
class Rva002B599FZeroView
{
public:
	Rva002B599FZeroView *rva002B599F();
private:
	unsigned char head[12];
	unsigned int a, b;
};
Rva002B599FZeroView *Rva002B599FZeroView::rva002B599F()
{
	a = 0; b = 0;
	return this;
}
