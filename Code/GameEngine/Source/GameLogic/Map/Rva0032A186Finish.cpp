// cl: /DNDEBUG /MD /EHsc
//
// ??1BuildListInfo@@MAE@XZ @0x0032A186 120B. BuildListInfo list destructor.
// Each +0x2C link is unlinked then released through the virtual deleteInstance(0)
// slot 0 whose pointer result feeds ::operator delete (??3 @0x2FD60). The
// _ReadWriteBarrier after setNextBuildList keeps retail's and-then-vtable-load
// order inside the loop. Layout: vptr +0, AsciiStrings +4/+8/+0x30,
// m_nextBuildList +0x2C, padding +0xC..+0x2B.
// class-gate: allow AsciiString TU-local 4-byte view matches the proven +4/+8/+0x30 StringBase dtor sites.
// class-gate: allow Snapshot private view puts deleteInstance(0) at slot 0 and restores vptr 0xBBB554.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
extern "C" const void *const vtbl_00BBB554[];
#pragma comment(linker, "/alternatename:_vtbl_00BBB554=??_7BfmeBaseVUQ@@6B@")
template <typename T> class StringBase
{
	friend class AsciiString;
private:
	StringBase() { m_data = 0; }
	StringBase(const StringBase<T> &other);
	void releaseBuffer();
	void *m_data;
};
class AsciiString : private StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() { releaseBuffer(); }
	AsciiString &operator=(const AsciiString &other);
};
// Declared, not defined inline: retail's calls land on the rowed releaseBuffer
// body at 0x00036410, and an inline body here was the tree's only copy of this
// name, so every caller bound to it instead of to that row.
class BFMERetailAsciiString : public AsciiString
{
public:
    ~BFMERetailAsciiString();
};
class Snapshot
{
public:
	virtual void *deleteInstance(int flags);
	virtual ~Snapshot();
	virtual void crc();
	virtual void loadPostProcess();
	virtual void xfer();
};
inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(((unsigned int)vtbl_00BBB554));
}
class BuildListInfo : public Snapshot
{
public:
    BuildListInfo *getNext() const
    {
        return m_nextBuildList;
    }
    void setNextBuildList(BuildListInfo *next)
    {
        m_nextBuildList = next;
    }
    BFMERetailAsciiString m_buildingName;
    BFMERetailAsciiString m_templateName;
    unsigned char m_padding[32];
    BuildListInfo *m_nextBuildList;
    BFMERetailAsciiString m_script;
protected:
    virtual ~BuildListInfo();
};
BuildListInfo::~BuildListInfo()
{
    register BuildListInfo *next;
    if (m_nextBuildList) {
        register BuildListInfo *cur = m_nextBuildList;
        while (cur) {
            next = cur->getNext();
            cur->setNextBuildList(0);
            _ReadWriteBarrier();
            ::operator delete(cur->deleteInstance(0));
            cur = next;
        }
    }
}
