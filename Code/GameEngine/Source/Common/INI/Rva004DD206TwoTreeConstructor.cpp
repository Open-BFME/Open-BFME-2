// cl: /O1 /MD /EHsc /DNDEBUG
// Whole clean BFME1 donor Rva0037BF60TwoTreeCtor.cpp at 1281192 supplies the
// construction shape. Original owner and key/value names remain unknown;
// the donor's integer words describe bit width rather than proved target types.
// Target4DD206/84 has a proven Ghidra boundary and native caller426361 in the
// matched factory spelled EmotionSystem::createEmotion: allocation52B; ECX
// receiver; two4B stack arguments; RET8. Existing Emotion naming is carried
// from that source and candidate pin, not asserted by these address views.
// Stores at+0/+4/+8/+C/+10/+2C/+30 and two12B trees at+14/+20 are native facts.
// Both tree constructors call the full25B33C432 provider; its24B header
// allocation and three-word ABI are independently verified. Key/value meanings
// are opaque. Declared tree methods bind existing proper providers rather than
// recreating STLport private class definitions or its allocator helpers.
// Native EH: handler7916EC -> funcinfo943814 -> one-entry unwind map94380C
// (state0 to-1) -> action7916E1 reads saved receiver[ebp-10] and adds14 ->
// cleanup4638EC/5 -> destructor4636FE/56. Only the first completed tree is
// unwound if the second construction throws. The generated C++ owns that same
// unwind state; the cleanup below is a real tail-calling destructor.
// The old erase TU's whole-class instantiation displaced the exact4636FE
// destructor. Its scoped narrow repair retains both existing45/41B bodies.
// Existing unreferenced malloc-allocator COMDAT debt remains in those old TUs;
// this unit's normal selected constructor/destructor providers are proved.
class Rva004DD206TreeView {
public:
 Rva004DD206TreeView();
 __declspec(noinline) ~Rva004DD206TreeView();
 void releaseNative();
 unsigned int words[3];
};
Rva004DD206TreeView::~Rva004DD206TreeView() { releaseNative(); }
#pragma comment(linker,"/alternatename:??0Rva004DD206TreeView@@QAE@XZ=??0?$map@HPAXU?$less@H@_STL@@V?$allocator@U?$pair@$$CBHPAX@_STL@@@2@@_STL@@QAE@XZ")
#pragma comment(linker,"/alternatename:?releaseNative@Rva004DD206TreeView@@QAEXXZ=??1?$_Rb_tree@HU?$pair@$$CBHURva00462D35Mapped@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00462D35Mapped@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00462D35Mapped@@@_STL@@@2@@_STL@@QAE@XZ")
class Rva004DD206Owner {
public:
 Rva004DD206Owner(unsigned int a,unsigned int b);
 unsigned int word00,word04,word08;
 unsigned short word0C;
 unsigned int word10;
 Rva004DD206TreeView tree14,tree20;
 unsigned int word2C,word30;
};
// ?Rva004DD206Owner::Rva004DD206Owner present-unmatched
Rva004DD206Owner::Rva004DD206Owner(unsigned int a,unsigned int b)
 :word00(a),word04(b),word08(0),word0C(0),word10(0) {word2C=0;word30=0;}
