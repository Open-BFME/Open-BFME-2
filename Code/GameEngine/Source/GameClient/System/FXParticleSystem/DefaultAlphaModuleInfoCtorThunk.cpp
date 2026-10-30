// cl: /DNDEBUG /MD /EHsc /Ob2

// Open-BFME5: DefaultAlphaModuleInfo default constructor @0x55B44D.
// Retail: own vtable, then eight RandomAlphaKeyframe elements at +4 built by
// the rowed vector_constructor_iterator helper through the rowed element
// default at 0x00001E7F. The element's declared (never defined) destructor
// is what carries the EH frame.

class Rva0049B47C
{
public:
	Rva0049B47C() {}
	virtual ~Rva0049B47C();
};

namespace FXParticleSystem
{

class RandomAlphaKeyframe
{
public:
	RandomAlphaKeyframe();

private:
	char m_data[0x10];
};

class DefaultAlphaModuleInfo : public ::Rva0049B47C
{
public:
	DefaultAlphaModuleInfo();
	virtual ~DefaultAlphaModuleInfo();
	virtual void LoadPostProcess(); // slot 1: the exported empty callback FXParticleSystem.cpp rows at 0x000B3FD0
	virtual const char *GetSnapshotName();

private:
	RandomAlphaKeyframe m_keys[8];
};

// ??0DefaultAlphaModuleInfo@FXParticleSystem@@QAE@XZ
DefaultAlphaModuleInfo::DefaultAlphaModuleInfo()
{
}

}
