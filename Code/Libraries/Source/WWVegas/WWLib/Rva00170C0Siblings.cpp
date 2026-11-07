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

// The empty body was not retail's 0x006C5930; declared only, so its pin binds the call.
void Rva006C5930Dtor_Anchor()
{
	Rva006C5930Dtor *p = new Rva006C5930Dtor;
	delete p;
}

class Rva00120FB0Dtor
{
public:
	virtual ~Rva00120FB0Dtor();
};

// The empty body was not retail's 0x00120FB0; declared only, so its pin binds the call.
void Rva00120FB0Dtor_Anchor()
{
	Rva00120FB0Dtor *p = new Rva00120FB0Dtor;
	delete p;
}

class Rva00141C30Dtor
{
public:
	virtual ~Rva00141C30Dtor();
};

// The empty body was not retail's 0x00141C30; declared only, so its pin binds the call.
void Rva00141C30Dtor_Anchor()
{
	Rva00141C30Dtor *p = new Rva00141C30Dtor;
	delete p;
}

class Rva00155330Dtor
{
public:
	virtual ~Rva00155330Dtor();
};

// The empty body was not retail's 0x00155330; declared only, so its pin binds the call.
void Rva00155330Dtor_Anchor()
{
	Rva00155330Dtor *p = new Rva00155330Dtor;
	delete p;
}

class Rva00156750Dtor
{
public:
	virtual ~Rva00156750Dtor();
};

// The empty body was not retail's 0x00156750; declared only, so its pin binds the call.
void Rva00156750Dtor_Anchor()
{
	Rva00156750Dtor *p = new Rva00156750Dtor;
	delete p;
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

// The empty body was not retail's 0x00625800; declared only, so its pin binds the call.
void Rva00625800Dtor_Anchor()
{
	Rva00625800Dtor *p = new Rva00625800Dtor;
	delete p;
}

class Rva0066C730Dtor
{
public:
	virtual ~Rva0066C730Dtor();
};

// Retail's 0x0066C730 is a 35-byte reset body (rowed in Fesl/util.cpp), not an
// empty destructor: declare it only so the pin binds the call, and emit the
// deleting destructor from a devirtualized new/delete (the anchor is unclaimed).
void Rva0066C730Dtor_Anchor()
{
	Rva0066C730Dtor *p = new Rva0066C730Dtor;
	delete p;
}

class Rva0073A900Dtor
{
public:
	virtual ~Rva0073A900Dtor();
};

// The empty body was not retail's 0x0073A900; declared only, so its pin binds the call.
void Rva0073A900Dtor_Anchor()
{
	Rva0073A900Dtor *p = new Rva0073A900Dtor;
	delete p;
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
