// cl: /O1 /DNDEBUG /MD /EHsc
//
// Vector deleting destructors (??_E), batch V03: 75-byte bodies that, for
// an array delete (flag bit 1), run the eh vector destructor iterator
// (0x00629110) over the count stored before the array with the destructor's
// address and the element size, then free the block from its count word with
// operator delete[] (0x0002FD80); otherwise they call the destructor and free
// through operator delete (0x0002FD60). The element size is the class size.
// Each class's destructor is declared, not defined (pinned); the anchor below
// (no retail counterpart) news an array of each class so this TU emits the
// vector deleting destructor. Owners are opaque unless the destructor already
// carried a ledger name.
//
//   ??_E        dtor        size  vtable#slot
//   0x003A64F0  0x003A6201  0x10  0x00C1BAF0#0
//   0x003A679D  0x003A6201  0x1C  0x00C1BB50#0
//   0x003A690D  0x003A6201  0x14  0x00C1BB80#0
//   0x003A71D4  0x003A6201  0x30  0x00C1BC10#0
//   0x003A73AD  0x003A6201  0x18  0x00C1BC40#0
//   0x003A7853  0x003A6201  0x2C  0x00C1BCC0#0
//   0x003A7A06  0x003A6201  0x70  0x00C1BCF0#0
//   0x003A7B9F  0x003A6201  0x0C  0x00C1BD60#0

// Declared so the array path frees through operator delete[] (0x0002FD80)
// as retail does; left undeclared, cl falls back to scalar operator delete.
#include <new>

class __declspec(novtable) Rva003A64F0VecBase0
{
public:
	virtual ~Rva003A64F0VecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class __declspec(novtable) Rva003A64F0VecBase8
{
public:
	virtual ~Rva003A64F0VecBase8();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

class Rva003A64F0Vec : public Rva003A64F0VecBase0, public Rva003A64F0VecBase8
{
public:
	virtual ~Rva003A64F0Vec();
};


class __declspec(novtable) Rva003A679DVecBase0
{
public:
	virtual ~Rva003A679DVecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class __declspec(novtable) Rva003A679DVecBase8
{
public:
	virtual ~Rva003A679DVecBase8();
private:
	char m_unmodelled_04[0x14 - 0x04];
};

class Rva003A679DVec : public Rva003A679DVecBase0, public Rva003A679DVecBase8
{
public:
	virtual ~Rva003A679DVec();
};


class __declspec(novtable) Rva003A690DVecBase0
{
public:
	virtual ~Rva003A690DVecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class __declspec(novtable) Rva003A690DVecBase8
{
public:
	virtual ~Rva003A690DVecBase8();
private:
	char m_unmodelled_04[0xC - 0x04];
};

class Rva003A690DVec : public Rva003A690DVecBase0, public Rva003A690DVecBase8
{
public:
	virtual ~Rva003A690DVec();
};



class __declspec(novtable) Rva003A71D4VecBase0
{
public:
	virtual ~Rva003A71D4VecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class __declspec(novtable) Rva003A71D4VecBase8
{
public:
	virtual ~Rva003A71D4VecBase8();
private:
	char m_unmodelled_04[0x28 - 0x04];
};

class Rva003A71D4Vec : public Rva003A71D4VecBase0, public Rva003A71D4VecBase8
{
public:
	virtual ~Rva003A71D4Vec();
};

namespace FXParticleSystem
{
// OrthoEmissionVelocityModuleTemplate's class tables name this deleting destructor (slot 0 at +0) and its -8
// thunk (slot 0 at +8). The class is abstract, so its own constructor units
// cannot new an array of it; this view keeps only the size and the +8
// secondary base, and novtable keeps its partial table out of the image.
class __declspec(novtable) OrthoEmissionVelocityModuleTemplate : public Rva003A71D4VecBase0, public Rva003A71D4VecBase8
{
public:
	virtual ~OrthoEmissionVelocityModuleTemplate();
};
}


class __declspec(novtable) Rva003A73ADVecBase0
{
public:
	virtual ~Rva003A73ADVecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class __declspec(novtable) Rva003A73ADVecBase8
{
public:
	virtual ~Rva003A73ADVecBase8();
private:
	char m_unmodelled_04[0x10 - 0x04];
};

class Rva003A73ADVec : public Rva003A73ADVecBase0, public Rva003A73ADVecBase8
{
public:
	virtual ~Rva003A73ADVec();
};

namespace FXParticleSystem
{
// SphericalEmissionVelocityModuleTemplate's class tables name this deleting destructor (slot 0 at +0) and its -8
// thunk (slot 0 at +8). The class is abstract, so its own constructor units
// cannot new an array of it; this view keeps only the size and the +8
// secondary base, and novtable keeps its partial table out of the image.
class __declspec(novtable) SphericalEmissionVelocityModuleTemplate : public Rva003A73ADVecBase0, public Rva003A73ADVecBase8
{
public:
	virtual ~SphericalEmissionVelocityModuleTemplate();
};
}



class __declspec(novtable) Rva003A7853VecBase0
{
public:
	virtual ~Rva003A7853VecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class __declspec(novtable) Rva003A7853VecBase8
{
public:
	virtual ~Rva003A7853VecBase8();
private:
	char m_unmodelled_04[0x24 - 0x04];
};

class Rva003A7853Vec : public Rva003A7853VecBase0, public Rva003A7853VecBase8
{
public:
	virtual ~Rva003A7853Vec();
};

namespace FXParticleSystem
{
template <int Category> class DefaultModuleTemplate;

// DefaultModuleTemplate<3>'s class tables (0x0081BCC0 slot 0, 0x0081BCD0 slot 0)
// name this deleting destructor and its -8 thunk. The class is abstract, so its
// own constructor units cannot new an array of it; this view keeps only the size
// and the +8 secondary base, and novtable keeps its partial table out of the image.
template <>
class __declspec(novtable) DefaultModuleTemplate<3> : public Rva003A7853VecBase0, public Rva003A7853VecBase8
{
public:
	virtual ~DefaultModuleTemplate();
};
}


class __declspec(novtable) Rva003A7A06VecBase0
{
public:
	virtual ~Rva003A7A06VecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class __declspec(novtable) Rva003A7A06VecBase8
{
public:
	virtual ~Rva003A7A06VecBase8();
private:
	char m_unmodelled_04[0x68 - 0x04];
};

class Rva003A7A06Vec : public Rva003A7A06VecBase0, public Rva003A7A06VecBase8
{
public:
	virtual ~Rva003A7A06Vec();
};

namespace FXParticleSystem
{
template <int Category> class DefaultModuleTemplate;

// DefaultModuleTemplate<2>'s class tables (0x0081BCF0 slot 0, 0x0081BD00 slot 0)
// name this deleting destructor and its -8 thunk. The class is abstract, so its
// own constructor units cannot new an array of it; this view keeps only the size
// and the +8 secondary base, and novtable keeps its partial table out of the image.
template <>
class __declspec(novtable) DefaultModuleTemplate<2> : public Rva003A7A06VecBase0, public Rva003A7A06VecBase8
{
public:
	virtual ~DefaultModuleTemplate();
};
}

class __declspec(novtable) Rva003A7B9FVecBase0
{
public:
	virtual ~Rva003A7B9FVecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class __declspec(novtable) Rva003A7B9FVecBase8
{
public:
	virtual ~Rva003A7B9FVecBase8();
};

class Rva003A7B9FVec : public Rva003A7B9FVecBase0, public Rva003A7B9FVecBase8
{
public:
	virtual ~Rva003A7B9FVec();
};

namespace FXParticleSystem
{
// StreakDrawModuleTemplate's class tables name this deleting destructor (slot 0 at +0) and its -8
// thunk (slot 0 at +8). The class is abstract, so its own constructor units
// cannot new an array of it; this view keeps only the size and the +8
// secondary base, and novtable keeps its partial table out of the image.
class __declspec(novtable) StreakDrawModuleTemplate : public Rva003A7B9FVecBase0, public Rva003A7B9FVecBase8
{
public:
	virtual ~StreakDrawModuleTemplate();
};
}

namespace FXParticleSystem
{
// QuadDrawModuleTemplate's class tables name this deleting destructor (slot 0 at +0) and its -8
// thunk (slot 0 at +8). The class is abstract, so its own constructor units
// cannot new an array of it; this view keeps only the size and the +8
// secondary base, and novtable keeps its partial table out of the image.
class __declspec(novtable) QuadDrawModuleTemplate : public Rva003A7B9FVecBase0, public Rva003A7B9FVecBase8
{
public:
	virtual ~QuadDrawModuleTemplate();
};
}

namespace FXParticleSystem
{
template <int Category> class DefaultModuleTemplate;

// DefaultModuleTemplate<6>'s class tables (0x0081BD60 slot 0, 0x0081BAD0 slot 0)
// name this deleting destructor and its -8 thunk. The class is abstract, so its
// own constructor units cannot new an array of it; this view keeps only the size
// and the +8 secondary base, and novtable keeps its partial table out of the image.
template <>
class __declspec(novtable) DefaultModuleTemplate<6> : public Rva003A7B9FVecBase0, public Rva003A7B9FVecBase8
{
public:
	virtual ~DefaultModuleTemplate();
};
}


// ?<bfmeVectorDeleteAnchorV03Unresolved> absent-from-retail
void bfmeVectorDeleteAnchorV03Unresolved()
{
	new Rva003A64F0Vec[2];
	new Rva003A679DVec[2];
	new Rva003A690DVec[2];
	new Rva003A71D4Vec[2];
	new FXParticleSystem::OrthoEmissionVelocityModuleTemplate[2];
	new Rva003A73ADVec[2];
	new FXParticleSystem::SphericalEmissionVelocityModuleTemplate[2];
	new Rva003A7853Vec[2];
	new FXParticleSystem::DefaultModuleTemplate<3>[2];
	new Rva003A7A06Vec[2];
	new FXParticleSystem::DefaultModuleTemplate<2>[2];
	new Rva003A7B9FVec[2];
	new FXParticleSystem::StreakDrawModuleTemplate[2];
	new FXParticleSystem::QuadDrawModuleTemplate[2];
	new FXParticleSystem::DefaultModuleTemplate<6>[2];
}

// Complete destructors: retail folds each onto the row at its pinned
// address (bindings derived by tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:??1Rva003A64F0Vec@@UAE@XZ=??1?$CategoryModuleTemplate@$06@FXParticleSystem@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva003A679DVec@@UAE@XZ=??1?$CategoryModuleTemplate@$06@FXParticleSystem@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva003A690DVec@@UAE@XZ=??1?$CategoryModuleTemplate@$06@FXParticleSystem@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva003A71D4Vec@@UAE@XZ=??1?$CategoryModuleTemplate@$06@FXParticleSystem@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva003A73ADVec@@UAE@XZ=??1?$CategoryModuleTemplate@$06@FXParticleSystem@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva003A7853Vec@@UAE@XZ=??1?$CategoryModuleTemplate@$06@FXParticleSystem@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva003A7A06Vec@@UAE@XZ=??1?$CategoryModuleTemplate@$06@FXParticleSystem@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva003A7B9FVec@@UAE@XZ=??1?$CategoryModuleTemplate@$06@FXParticleSystem@@UAE@XZ")
