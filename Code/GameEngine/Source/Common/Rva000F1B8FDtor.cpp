// cl: /MD /EHsc
// ??1Rva000F1B8F@@UAE@XZ @0x000F1B8F 54B
// Evidence: dtor lane calls rowed Free_String 0x00610A40 plus vptr stores; deleting dtor 0x000F1B73 rowed in OpaqueScalarDeletingDtorsB01; caller 0x000F1B76.
class StringClass {
	void *m_data;
	void Free_String();
public:
	__forceinline ~StringClass(void) { Free_String(); }
};
struct Rva000F1B8FBase {
	virtual ~Rva000F1B8FBase() {}
};
struct Rva000F1B8F : Rva000F1B8FBase {
	int m_04;
	StringClass m_08;
	virtual ~Rva000F1B8F();
};
Rva000F1B8F::~Rva000F1B8F() {}

// Inline public teardown calls Free_String directly; the standalone destructor is 0x00065F5B.
