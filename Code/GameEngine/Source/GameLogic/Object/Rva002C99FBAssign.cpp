// cl: /DNDEBUG /MD /EHs-c-
// ??4Rva002C99FB@@QAEAAU0@ABU0@@Z @0x002C99FB 29B
// Honest struct assignment: dword at +0 plus OpaqueRefElement4 at +4 via rowed 0x00239099.
// Evidence: callers 0x002CD82A 0x002CD83C 0x002CF5EB 0x0031BA31; unblocks 8 (6 ready);
// prev ObjectRva002C97E8 +0x38 layout, next WeaponComputeBonus flags; no vtable, ret 4 returns this.
struct OpaqueRefElement4 {
  OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};
struct Rva002C99FB {
  int m_first;
  OpaqueRefElement4 m_second;
  Rva002C99FB &operator=(const Rva002C99FB &other);
};
Rva002C99FB &Rva002C99FB::operator=(const Rva002C99FB &other)
{
  m_first = other.m_first;
  m_second = other.m_second;
  return *this;
}
