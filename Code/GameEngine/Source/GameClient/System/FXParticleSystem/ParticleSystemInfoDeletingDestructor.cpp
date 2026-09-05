// cl: /O1 /EHsc
// The retail vtable's scalar deleting destructor is emitted from a separate
// translation unit.  Keep the complete destructor's novtable model in the
// sibling source; this TU gives MSVC the vftable use that emits ??_G.

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	void releaseBuffer();
	Header *m_data;
};

class AsciiString
{
public:
	~AsciiString()
	{
		m_data.releaseBuffer();
	}

private:
	StringBase<char> m_data;
};

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void crc(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
	virtual void xfer(Xfer *xfer) = 0;
};

namespace FXParticleSystem
{

class ParticleSystemInfo : public Snapshot
{
public:
	virtual ~ParticleSystemInfo();

private:
	unsigned char m_prefix[0xc];
	AsciiString m_particleTypeName;
	unsigned char m_gap[0x54];
	AsciiString m_slaveSystemName;
	unsigned char m_gap2[0xc];
	AsciiString m_attachedSystemName;
};

ParticleSystemInfo::~ParticleSystemInfo()
{
}

// ?forceParticleSystemInfoDelete@FXParticleSystem@@YAXPAVParticleSystemInfo@1@@Z absent-from-retail
void forceParticleSystemInfoDelete(ParticleSystemInfo *particleSystemInfo)
{
	delete particleSystemInfo;
}

}
