// cl: /O1 /EHsc
// Open-BFME5: FXParticleSystem::ParticleSystemInfo destructor.  The three
// StringBase<char> members are at +0x10, +0x68, and +0x78 in BFME2.

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

// Snapshot.cpp supplies this same four-slot base vtable at 0x00BBB554.
// ParticleSystemInfo has twelve bytes of scalar state before its first
// StringBase member, so the prefix keeps that member at the constructor-proven
// +0x10 while retaining Snapshot's real identity.
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

class __declspec(novtable) ParticleSystemInfo : public Snapshot
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

// ??1ParticleSystemInfo@FXParticleSystem@@UAE@XZ
ParticleSystemInfo::~ParticleSystemInfo()
{
}

}
