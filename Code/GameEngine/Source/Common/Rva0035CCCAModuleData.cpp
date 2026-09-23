// cl: /O1 /DNDEBUG /MD /EHsc
//
// Destructor and scalar deleting destructor of an unidentified module-data
// class with vtable 0x00C16394, built by the constructor at 0x0035CC36. It
// owns a string at +0x10 and an AsciiString list at +0x3C, and its base
// destructor is the opaque Rva001E3624. These bodies were first claimed as
// CreateCrateDieModuleData's, but the class the CreateCrateDie factory builds
// uses vtable 0x00BF40A8 and has no string at +0x10, so this one stays
// address-named until identified. The list and string teardown resolve to the
// ModuleFactory-owned _List_base<AsciiString> rows and the 0x00036410 pin.

// stlport (replica idiom: TU-local _STL list over a forward-declared
// AsciiString emits calls mangled exactly like the ModuleFactory-owned
// _List_base<AsciiString> clear/dtor rows, resolving to them with no pins
// and no local emission beyond the implicit list dtor itself).
namespace _STL {
template <class T> class allocator {};
template <class T, class A = allocator<T> > class _List_base
{
public:
	void *_M_nodeNext;
	void *_M_nodePrev;
	void clear();
	~_List_base();
};
template <class T, class A = allocator<T> > class list : public _List_base<T, A>
{
};
}

class AsciiString;

// Fold-shared AsciiString member teardown (never defined; resolves through
// the symbols.csv pin at 0x36410 like the Bucket/ FoldDeleters bodies).
class AsciiStringMember
{
public:
	~AsciiStringMember();
};

// Opaque ModuleData base (never defined; base-dtor call resolves through
// the symbols.csv pin at 0x1E3624). Retail base body keeps a conditional
// delete pointer at +0x04; +0x08/+0x0C ride as data.
class Rva001E3624
{
public:
	virtual ~Rva001E3624();
	void *m_unk04;
	int m_unk08;
	int m_unk0C;
};

class Rva0035CCCAModuleData : public Rva001E3624
{
public:
	virtual ~Rva0035CCCAModuleData();
	AsciiStringMember m_unkString10;
	float m_unk14;
	int m_unk18;
	char m_pad1C[0x20];
	_STL::list<AsciiString> m_nameList3C;
};

// ??1Rva0035CCCAModuleData@@UAE@XZ
Rva0035CCCAModuleData::~Rva0035CCCAModuleData()
{
	m_nameList3C.clear();
}
// ??_GRva0035CCCAModuleData@@UAEPAXI@Z
