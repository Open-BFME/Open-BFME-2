// cl: /O1 /MD
// Copy constructor (43B) of the stride-0x10 element destroyed by
// ??$_Destroy@PAVRva00297360Element@@ in StlportVectorDtorChains.cpp: an int
// key, an AsciiString at +4 (copied via the rowed operator= 0x366F0) and two
// trailing ints. Body assignments reproduce the retail member order; the
// inline-empty AsciiString default ctor keeps the implicit member init free
// of stores. Application identity unknown, so an Rva owner name is used.
class AsciiString {
public:
  AsciiString() {}
  AsciiString &operator=(const AsciiString &other);
private:
  void *m_data;
};

class Rva00297360Element {
public:
  ~Rva00297360Element();
  Rva00297360Element(const Rva00297360Element &other);
private:
  int m_00;
  AsciiString m_04;
  int m_08;
  int m_0C;
};

Rva00297360Element::Rva00297360Element(const Rva00297360Element &other)
{
  m_00 = other.m_00;
  m_04 = other.m_04;
  m_08 = other.m_08;
  m_0C = other.m_0C;
}
