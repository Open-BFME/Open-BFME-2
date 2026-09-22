// cl: /EHsc /O1 /DNDEBUG /MD
// stlport
// ??1GeometryInfo@@UAE@XZ retail 0x00050B2A 63 bytes.
// GeometryInfo destructor: destroys the record vector at 38 through the
// rowed 0x50AB8 and the shape vector at 2C through the rowed 0x50A79, then
// restores the Snapshot vtable. The members carry declared-only wrapper
// dtors so the rowed bodies resolve; the inline Snapshot base dtor performs
// the vtable restore after the members fall. novtable suppresses the entry
// vtable store retail lacks; the restore to BBB554 stays explicit. The next
// 11 bytes are a separate push-push-call-ret tail, not claimed here.

#include <vector>

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

struct GeometryShapeVector
{
	~GeometryShapeVector();

	void *m_head[3];
};

struct GeometryRecordVector
{
	~GeometryRecordVector();

	void *m_head[3];
};

class __declspec(novtable) GeometryInfo : public Snapshot
{
public:
	virtual ~GeometryInfo();

private:
	char m_pad04[0x28];
	GeometryShapeVector m_shapes;
	GeometryRecordVector m_records;
};
// ??1GeometryInfo@@UAE@XZ @0x00050B2A
GeometryInfo::~GeometryInfo()
{
}
