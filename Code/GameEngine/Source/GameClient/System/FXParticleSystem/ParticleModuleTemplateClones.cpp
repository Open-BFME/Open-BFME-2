// cl: /O1 /EHsc
// ?clone@Rva003AE43F@@QBEPAV1@XZ @0x003AE408 55B
// ?clone@Rva003AEB9C@@QBEPAV1@XZ @0x003AEB65 55B
// ?clone@Rva003AECE6@@QBEPAV1@XZ @0x003AECE6 88B
// ?clone@Rva003AE928@@QBEPAV1@XZ @0x003AE8F1 55B
// ??0Rva003AE928@@QAE@ABV0@@Z @0x003AE928 38B
// ??0Rva003AE94E@@QAE@ABV0@@Z @0x003AE94E 105B
//
// Particle-module template clone slots: allocate the class's own size and
// copy-construct it from the receiver, under the EH frame /EHsc gives a
// new-expression whose constructor can throw. The same shape as the rowed
// clones in Rva003AE4E5Clone.cpp and Rva003AE683Clone.cpp; sizes are the `new`
// operands and the copy constructors are the rowed ones in
// ParticleModuleInfoCopyCtors.cpp and ConcreteModuleTemplateCopyCtors.cpp.
//
// 0x003AECE6 constructs a class whose own copy constructor was inlined: one
// call to the rowed 0x003AED3E copy constructor, then its four subobject
// vtables at +0, +0x14, +0x18 and +0x1C. /O1 does not inline a constructor a
// new-expression guards, so it is spelled __forceinline (as in
// ModuleTemplateCloneSlots.cpp).
//
// 0x003AE8F1 (0x00C1CAD4#177) clones a 0x2C-byte class whose two copy
// constructors are unrowed and land here too: 0x003AE928 forwards to 0x003AE94E
// and stamps its three vtables; 0x003AE94E is the GpuDrawModuleInfo sibling of
// the rowed 0x003AE6A9 in Rva003AE6A9CopyCtor.cpp (same rowed 0x003AF50D base,
// same inlined intermediate, the rowed GpuDrawModuleInfo copy at +0x18 instead
// of RenderObjectDrawModuleInfo, and no trailing int).
//
// All are address-named after their copy constructors or their own slot; the
// vtables are 0x00C1CAD4#87, 0x00C1CE54#6 and 0x00C1CE54#43.

class Rva003AE43F
{
public:
	Rva003AE43F( const Rva003AE43F &other );
	Rva003AE43F *clone() const;

private:
	char m_storage[ 0x1c ];
};

Rva003AE43F *Rva003AE43F::clone() const
{
	return new Rva003AE43F( *this );
}

class Rva003AEB9C
{
public:
	Rva003AEB9C( const Rva003AEB9C &other );
	Rva003AEB9C *clone() const;

private:
	char m_storage[ 0x40 ];
};

Rva003AEB9C *Rva003AEB9C::clone() const
{
	return new Rva003AEB9C( *this );
}

class Rva003AECE6Slot0	{ public: virtual void s0(); int m_a[ 4 ]; };
class Rva003AECE6Slot1	{ public: virtual void s0(); };
class Rva003AECE6Slot2	{ public: virtual void s0(); };
class Rva003AECE6Slot3	{ public: virtual void s0(); };

class Rva003AED3E
	: public Rva003AECE6Slot0, public Rva003AECE6Slot1,
	  public Rva003AECE6Slot2, public Rva003AECE6Slot3
{
public:
	Rva003AED3E( const Rva003AED3E &other );
};

class Rva003AECE6 : public Rva003AED3E
{
public:
	__forceinline Rva003AECE6( const Rva003AECE6 &other ) : Rva003AED3E( other ) {}
	Rva003AECE6 *clone() const;

private:
	char m_storage[ 0x64 - sizeof( Rva003AED3E ) ];
};

Rva003AECE6 *Rva003AECE6::clone() const
{
	return new Rva003AECE6( *this );
}

class RvaSmartPtr12_3AE94E
{
public:
	RvaSmartPtr12_3AE94E( const RvaSmartPtr12_3AE94E &that );
	~RvaSmartPtr12_3AE94E();

private:
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};

class ModuleInfoSecondBase_3AE94E
{
public:
	virtual ~ModuleInfoSecondBase_3AE94E();
};

class ModuleInfoHeadBase_3AE94E
{
public:
	ModuleInfoHeadBase_3AE94E( const ModuleInfoHeadBase_3AE94E &other )
		: m_smart( other.m_smart )
		, m_int10( other.m_int10 )
	{
	}
	virtual ~ModuleInfoHeadBase_3AE94E();

	RvaSmartPtr12_3AE94E m_smart;
	int m_int10;
};

class Rva003AF50D : public ModuleInfoHeadBase_3AE94E, public ModuleInfoSecondBase_3AE94E
{
public:
	Rva003AF50D( const Rva003AF50D &other );
	virtual ~Rva003AF50D();
};

class Intermediate3AE94E : public Rva003AF50D
{
public:
	__forceinline Intermediate3AE94E( const Intermediate3AE94E &other )
		: Rva003AF50D( other )
	{
	}
	virtual ~Intermediate3AE94E();
};

namespace FXParticleSystem
{
class GpuDrawModuleInfo
{
public:
	GpuDrawModuleInfo( const GpuDrawModuleInfo &other );
	virtual ~GpuDrawModuleInfo();

private:
	char m_pad[ 0x14 - 4 ];
};
}

class Rva003AE94E : public Intermediate3AE94E, public FXParticleSystem::GpuDrawModuleInfo
{
public:
	Rva003AE94E( const Rva003AE94E &other );
	virtual ~Rva003AE94E();
};

Rva003AE94E::Rva003AE94E( const Rva003AE94E &other )
	: Intermediate3AE94E( other )
	, FXParticleSystem::GpuDrawModuleInfo( (const FXParticleSystem::GpuDrawModuleInfo &)other )
{
}

class Rva003AE928 : public Rva003AE94E
{
public:
	Rva003AE928( const Rva003AE928 &other );
	virtual ~Rva003AE928();
	Rva003AE928 *clone() const;
};

Rva003AE928::Rva003AE928( const Rva003AE928 &other )
	: Rva003AE94E( other )
{
}

Rva003AE928 *Rva003AE928::clone() const
{
	return new Rva003AE928( *this );
}
