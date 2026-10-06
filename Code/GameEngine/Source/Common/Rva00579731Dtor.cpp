// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ??1Rva00579731@@QAE@XZ, retail 0x00579731 63B.
// Evidence: chain lane calls just-landed 0x0022167C plus element dtor 0x005796FC with size 8 count 6 at this+8; callers 0x00579CBB 0x007B94CD.
// Rva0022167C is 8B polymorphic holder from Rva0022161BClear.cpp; element is 8B BfmeStringRecord000B94D2 pair.
class Rva0022167C {
public:
	~Rva0022167C();
	virtual void _pure();
private:
	void *m_at4;
};
struct Rva005796FC {
	~Rva005796FC();
private:
	void *m0;
	void *m1;
};
class Rva00579731 {
public:
	~Rva00579731();
private:
	Rva0022167C m_at0;
	Rva005796FC m_at8[6];
};
Rva00579731::~Rva00579731()
{
}
// ??1Rva005796FC@@QAE@XZ: rowed in stlport_vector_stringrecord_b94d2_allocate_copy.cpp but that TU emits ??1BfmeStringRecord000B94D2@@QAE@XZ; bind this spelling.
#pragma comment(linker, "/alternatename:??1Rva005796FC@@QAE@XZ=??1BfmeStringRecord000B94D2@@QAE@XZ")
