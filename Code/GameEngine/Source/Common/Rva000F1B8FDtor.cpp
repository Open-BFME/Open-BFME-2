// cl: /MD /EHsc
// ??1Rva000F1B8F@@UAE@XZ @0x000F1B8F 54B
// Evidence: dtor lane calls rowed Free_String 0x00610A40 plus vptr stores; deleting dtor 0x000F1B73 rowed in OpaqueScalarDeletingDtorsB01; caller 0x000F1B76.
class StringClass {
	void *m_data;
	void Free_String();
public:
	~StringClass(void);
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

// Native public teardown and Free_String share0x00610A40 (DX8Wrapper call proof).
#pragma comment(linker, "/alternatename:??1StringClass@@QAE@XZ=?Free_String@StringClass@@AAEXXZ")
