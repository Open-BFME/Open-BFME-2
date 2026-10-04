// cl: /O1 /GX /DNDEBUG /MD
// ??1Rva0026E7EA@@UAE@XZ @0x0026E7EA 48B
// ModuleData dtor: tears down the Rva0026E5B9 member at +0x04 through the rowed
// dtor at 0x0026E5B9, then restores the Snapshot base vtable 0x00BBB554.
// Empty derived body with EH state 0. Shape follows StructureTopple precedent.
class Rva0026E5B9
{
public:
	~Rva0026E5B9();
private:
	void *m_pad[3];
};
class Xfer;
class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
};
extern const void *const g_00BBB554[];
inline Snapshot::~Snapshot() { *(const void **)this = g_00BBB554; }
class __declspec(novtable) Rva0026E7EA : public Snapshot
{
public:
	virtual ~Rva0026E7EA();
private:
	Rva0026E5B9 m_member04;
};
Rva0026E7EA::~Rva0026E7EA()
{
}
