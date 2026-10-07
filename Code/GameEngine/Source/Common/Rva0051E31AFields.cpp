// cl: /O1 /arch:SSE /G7 /MD
// Native Ghidra entry 0x0051E31A..0x0051E354 (58B, RET 16); the
// preceding rowed method ends at this entry. ECX is the destination and
// two stack pointer arguments supply word/scalar pairs at offsets 0/4.
// The other two stack words populate destination offsets 0x10/0x14.
// All six offsets, scalar SSE accesses and load-before-word-copy ordering
// are independently observed in this body. Names, original return type,
// integer signedness and complete class sizes are not recovered.
// Volatile scalar lvalues encode the observed separate loads/stores;
// they do not assert volatile qualifiers in the original declarations.
struct Pair0051E31A { int word; volatile float scalar; };
class Rva0051E31A {
public:
 void writeFields(const Pair0051E31A &a, const Pair0051E31A &b, int word, float scalar);
private:
 Pair0051E31A m_first,m_second;
 int m_word;
 float m_scalar;
};
void Rva0051E31A::writeFields(const Pair0051E31A &a, const Pair0051E31A &b, int word, float scalar)
{
 float firstScalar=a.scalar;
 m_first.word=a.word; m_first.scalar=firstScalar;
 float secondScalar=b.scalar;
 m_second.word=b.word; m_second.scalar=secondScalar;
 m_word=word; m_scalar=scalar;
}
