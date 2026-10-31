// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??1Rva0015058E@@UAE@XZ @0x0015058E 63B: dtor destroying Rva0014F699 at +0x10 then vector Rva00150209 at +4, restoring vtable 0x007C6F24 via inline Rva00BC6F24Base base. Evidence: rowed callees 0x0014D1E3 0x00150209, vtable data 0x007C6F24, callers 0x00150614 0x001510A9.
// Retail: mov eax handler / call __EH_prolog / lea ecx [esi+0x10] call ??1Rva0014F699 / lea ecx [esi+4] call ??1Rva00150209 / mov [esi] vtable / EH epilog.
// Not established: owning class identity; address-derived name.

extern "C" const unsigned char __identifier("??_7Base@@6B@")[];

class __declspec(novtable) Rva00BC6F24Base
{
public:
	Rva00BC6F24Base() { *(const void **)this = __identifier("??_7Base@@6B@"); }
	virtual ~Rva00BC6F24Base();
};

// Same one-slot cleanup view as Rva00150558Dtor.cpp: retail resets
// vtable 0x00BC6F24, distinct from canonical Snapshot's 0x00BBB554.
inline Rva00BC6F24Base::~Rva00BC6F24Base()
{
	*(const void **)this = __identifier("??_7Base@@6B@");
}

class TextureBaseClass
{
public:
	void Add_Ref();
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
};

template<class T>
class RefCountPtr
{
public:
	RefCountPtr const &operator=(RefCountPtr const &other);
private:
	T *Referent;
};

// Retail 00150990 calls the established Shadow copy owner at 0014F4E3 and
// 0x00150C74 the Shadow default constructor at 0x0014DB9F. The temporary
// remains an opaque 76-byte view with its rowed destructor.
namespace FXShaderParameterSourceNamespaceSAS {
struct SourceNamespace_Shadow { SourceNamespace_Shadow(); SourceNamespace_Shadow(const SourceNamespace_Shadow&); };
}

class __declspec(novtable) Rva0014F699
{
public:
	__declspec(dllimport) __forceinline Rva0014F699()
	{
		typedef FXShaderParameterSourceNamespaceSAS::SourceNamespace_Shadow T;
		((T*)this)->T::SourceNamespace_Shadow();
	}
	__declspec(dllimport) __forceinline Rva0014F699(const Rva0014F699 &other)
	{
		typedef FXShaderParameterSourceNamespaceSAS::SourceNamespace_Shadow T;
		((T*)this)->T::SourceNamespace_Shadow(*(const T*)&other);
	}
	virtual ~Rva0014F699();
	Rva0014F699 &operator=(const Rva0014F699 &other);
private:
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
	int m_3c;
	int m_40;
	int m_44;
	RefCountPtr<TextureClass> m_48;
};

class Rva0014F3E7;

struct Rva00150209
{
	Rva0014F3E7 *m_start;
	Rva0014F3E7 *m_finish;
	Rva0014F3E7 *m_endOfStorage;
	~Rva00150209();
};

struct EmitVtableTag;
struct EmitDestructorTag;

// The destructor is implicit: retail's ??1 stores no vptr of its own, only the base's.
class Rva0015058E : public Rva00BC6F24Base
{
public:
	Rva0015058E(EmitVtableTag *);
	Rva0015058E(EmitDestructorTag *);
private:
	Rva00150209 m_04;
	Rva0014F699 m_10;
};

// ?<Rva0015058E::Rva0015058E> absent-from-retail
Rva0015058E::Rva0015058E(EmitDestructorTag *) {}
