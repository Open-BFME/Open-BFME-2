// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// 12 scalar deleting destructors of the ??_G?$basic_filebuf@DV?$char_traits@D@_STL@@@_STL@@UAEPAXI@Z
// shape (30 B). Each retail body calls its class dtor then the rowed scalar operator delete
// 0x0002FD60 under the (this, flags) ABI. The class identities are unproven, so each is an
// address-derived local model whose dtor symbol is pinned to the retail call target; the
// deleting destructor is compiler-emitted and names that model.
//
// 0x00118640 -> dtor 0x006C5930
// 0x00122110 -> dtor 0x00120FB0
// 0x00141C10 -> dtor 0x00141C30
// 0x00156840 -> dtor 0x00155330
// 0x00157110 -> dtor 0x00156750
// 0x00157E60 -> dtor 0x00157C20 (now rowed as DynamicVectorClass<PendingSurfaceStruct>'s in render2dsentence.cpp)
// 0x00188320 -> dtor 0x001880D0 (non-virtual; see Rva001880D0Dtor below)
// 0x00616490 -> dtor 0x006162B0 (now rowed as Node<INIEntry*>'s in ini.cpp)
// 0x00626D90 -> dtor 0x00625800
// 0x00663410 -> dtor 0x0066C730
// 0x0073AAC0 -> dtor 0x0073A900
// 0x007581C0 -> dtor 0x0075A080 (non-virtual; see Rva009A4620CollisionData below)

class Rva006C5930Dtor
{
public:
	virtual ~Rva006C5930Dtor();
};

__declspec(noinline) Rva006C5930Dtor::~Rva006C5930Dtor()
{
}

class Rva00120FB0Dtor
{
public:
	virtual ~Rva00120FB0Dtor();
};

__declspec(noinline) Rva00120FB0Dtor::~Rva00120FB0Dtor()
{
}

class Rva00141C30Dtor
{
public:
	virtual ~Rva00141C30Dtor();
};

__declspec(noinline) Rva00141C30Dtor::~Rva00141C30Dtor()
{
}

class Rva00155330Dtor
{
public:
	virtual ~Rva00155330Dtor();
};

__declspec(noinline) Rva00155330Dtor::~Rva00155330Dtor()
{
}

class Rva00156750Dtor
{
public:
	virtual ~Rva00156750Dtor();
};

__declspec(noinline) Rva00156750Dtor::~Rva00156750Dtor()
{
}

// 0x00188320 is not a virtual deleting destructor: no vtable in the image
// holds its address, so it is the non-virtual scalar form a delete
// expression emits. Its destructor (0x001880D0, 5 bytes) is a bare tail
// jump to StringClass::Free_String (0x00610A40): the class's only member is
// a StringClass at +0 and the destructor is that member's inline teardown.
class StringClass
{
	friend class Rva001880D0Dtor;

private:
	void Free_String(void);
};

class Rva001880D0Dtor
{
public:
	__declspec(noinline) ~Rva001880D0Dtor() { m_string.Free_String(); }

private:
	StringClass m_string;
};

// ?forceRva001880D0Delete@@YAXPAVRva001880D0Dtor@@@Z absent-from-retail
void forceRva001880D0Delete(Rva001880D0Dtor *object) { delete object; }

class Rva00625800Dtor
{
public:
	virtual ~Rva00625800Dtor();
};

__declspec(noinline) Rva00625800Dtor::~Rva00625800Dtor()
{
}

class Rva0066C730Dtor
{
public:
	virtual ~Rva0066C730Dtor();
};

__declspec(noinline) Rva0066C730Dtor::~Rva0066C730Dtor()
{
}

class Rva0073A900Dtor
{
public:
	virtual ~Rva0073A900Dtor();
};

__declspec(noinline) Rva0073A900Dtor::~Rva0073A900Dtor()
{
}

// 0x007581C0 is likewise non-virtual (no DIR32 holds its address): it is the
// scalar deleting destructor of the collision data record whose destructor
// 0x0075A080 is rowed in CollisionManagerImpl.cpp.
class Rva009A4620CollisionData
{
public:
	~Rva009A4620CollisionData();
};

// ?forceRva009A4620CollisionDataDelete@@YAXPAVRva009A4620CollisionData@@@Z absent-from-retail
void forceRva009A4620CollisionDataDelete(Rva009A4620CollisionData *object) { delete object; }
