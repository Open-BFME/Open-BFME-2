// cl: /O1 /Ob2 /DNDEBUG /MD /EHs-c-
// Twin lead: ObfuscatedValueOperators.cpp rva0022D89D. Target3F3133
// combines this value with the encoded1 E4CD9C42 through rowed3F2947,
// then returns its updated+4 word through a hidden result pointer.
// The existing Gen_00528EC0 caller/copy views establish the8-byte value
// and nontrivial copy ABI. Its original application type name is unknown.
class Rva003F2352 {
public: Rva003F2352 *rva003F2947(Rva003F2352 *src);
private: char m_head[4];unsigned m_value;
};
class Gen_00528EC0 {
public:
 Gen_00528EC0() {}
 Gen_00528EC0(const Gen_00528EC0 &other) : m_value(other.m_value) {}
 Gen_00528EC0 rva003F3133();
private:
 char m_head[4];unsigned m_value;
};
Gen_00528EC0 Gen_00528EC0::rva003F3133() {
 Gen_00528EC0 tmp;
 tmp.m_value=0xE4CD9C42;
 reinterpret_cast<Rva003F2352 *>(this)->rva003F2947(reinterpret_cast<Rva003F2352 *>(&tmp));
 return *this;
}
