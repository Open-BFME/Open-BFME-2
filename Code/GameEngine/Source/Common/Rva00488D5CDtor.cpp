// cl: /MD /EHsc
// ??1Rva00488D5C@@UAE@XZ retail 0x00488D5C 79B
// Own vptr C4B5C8; under EH state 0 the object at +0x24 is deleted through its
// slot-0 deleting dtor with flag 0 and the global ??3@YAXPAX@Z (a
// global-scope delete) and cleared; then the rowed base dtor
// ??1OutwardEmissionVelocityInfo@FXParticleSystem@@UAE@XZ 0x0049B47C.
// Names address-derived.

class FXParticleSystem
{
public:
	class OutwardEmissionVelocityInfo
	{
	public:
		virtual ~OutwardEmissionVelocityInfo();

	private:
		unsigned char m_pad04[0x24 - 4];
	};
};

class Rva00488D5COwned
{
public:
	virtual ~Rva00488D5COwned();
};

class Rva00488D5C : public FXParticleSystem::OutwardEmissionVelocityInfo
{
public:
	virtual ~Rva00488D5C();

private:
	Rva00488D5COwned *m_owned; // +0x24
};

Rva00488D5C::~Rva00488D5C()
{
	::delete m_owned;
	m_owned = 0;
}
