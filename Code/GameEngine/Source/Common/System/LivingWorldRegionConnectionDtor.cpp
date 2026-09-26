// cl: /O1 /GX /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// LivingWorldRegionConnection destructor + deleting dtor.
//
// ??1LivingWorldRegionConnection@@UAE@XZ (retail 0x003F2517, 69 bytes):
// frees the detour-point storage through the rowed _free at 0x00030830
// when nonzero, tears the region name down through the pinned AsciiString
// dtor at 0x00036410, then restores the Snapshot base vtable 0x00BBB554
// through the TU-local inline base dtor. Two EH states (vector, then
// string) exactly as retail; novtable suppresses the entry derived-vtable
// store retail lacks. The detour member carries a TU-local inline dtor
// doing the null-checked free so no rowed vector dtor is called.
// ??_GLivingWorldRegionConnection@@UAEPAXI@Z (retail 0x003F2A70, 28
// bytes): compiler-emitted scalar deleting dtor wrapping the above plus
// the rowed operator delete at 0x0002FD60.

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &xfer);
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

void free(void *block);

struct DetourPoints
{
	~DetourPoints()
	{
		if (_M_start != 0)
			free(_M_start);
	}

	void *_M_start;
	void *_M_finish;
	void *_M_end_of_storage;
};

class __declspec(novtable) LivingWorldRegionConnection : public Snapshot
{
public:
	virtual ~LivingWorldRegionConnection();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &xfer);

private:
	AsciiString m_regionName; // +0x04
	int m_numberAllowed; // +0x08
	DetourPoints m_detourPoints; // +0x0C
};

typedef char LivingWorldRegionConnectionSizeCheck[sizeof(LivingWorldRegionConnection) == 0x18 ? 1 : -1];

// ??1LivingWorldRegionConnection@@UAE@XZ @0x3F2517
LivingWorldRegionConnection::~LivingWorldRegionConnection()
{
}
