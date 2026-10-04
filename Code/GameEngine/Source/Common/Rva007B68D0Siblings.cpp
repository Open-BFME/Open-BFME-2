// cl: /O2 /MD /DNDEBUG
//
// Seven consecutive global-object exit teardowns, 0x007B68D0..0x007B69B0,
// each 28 bytes. They are the compiler-generated `_$E` atexit callbacks for
// statically initialized objects of classes that derive *virtually* from an
// STLport basic_ios. The prologue is the virtual-base vftable fixup, the const
// `this` is the global object, and the tail is the base destructor:
//
//   mov eax,ds:&g            ; vbtable pointer stored at the object
//   mov ecx,[eax+4]          ; offset of the virtual base
//   mov [ecx + &g], vftable  ; patch the virtual base's vftable
//   mov ecx, &g + 4          ; the basic_ios subobject (+8 at 0x7B6990)
//   jmp basic_ios::~basic_ios
//
// The rowed template in the task list, _gpiRemoveProfile, shares only the
// mov/mov/mov/mov/jmp mnemonic shape; these are not GameSpy. The real sibling
// is the rowed derived-destructor family at 0x00013420 (narrow basic_ios) and
// 0x00013440 (wide basic_ios), which are exactly the two tail targets. Three
// of the bodies (0x7B68D0, 0x7B68F0, 0x7B6970) tail-jump to the narrow
// destructor, four (0x7B6910, 0x7B6930, 0x7B6990, 0x7B69B0) to the wide one.
//
// Provenance: the global addresses and the stored vftable are absolute DIR32
// operands, which the byte gate masks, so this TU declares them with honest
// address-derived names and only the REL32 tail needs the rowed destructor.
// The 0x00024750/0x0001E7D0-style matched bodies in this tree prove the
// compiler emits this teardown shape for `Derived : virtual public basic_ios`.
// Each row below names its own object symbol in the notes; the globals are
// ordered so the compiler's `_$E` numbering lands one teardown per address.

namespace _STL
{

template <class T>
class char_traits
{
};

template <class _CharT, class _Traits>
class basic_ios
{
public:
	basic_ios();
	virtual ~basic_ios();
};

}

class Rva007B68D0Obj : virtual public _STL::basic_ios<char, _STL::char_traits<char> >
{
public:
	~Rva007B68D0Obj() {}
};
class Rva007B68F0Obj : virtual public _STL::basic_ios<char, _STL::char_traits<char> >
{
public:
	~Rva007B68F0Obj() {}
};
class Rva007B6970Obj : virtual public _STL::basic_ios<char, _STL::char_traits<char> >
{
public:
	~Rva007B6970Obj() {}
};
class Rva007B6910Obj : virtual public _STL::basic_ios<unsigned short, _STL::char_traits<unsigned short> >
{
public:
	~Rva007B6910Obj() {}
};
class Rva007B6930Obj : virtual public _STL::basic_ios<unsigned short, _STL::char_traits<unsigned short> >
{
public:
	~Rva007B6930Obj() {}
};
class Rva007B6990Obj : virtual public _STL::basic_ios<unsigned short, _STL::char_traits<unsigned short> >
{
public:
	~Rva007B6990Obj() {}
private:
	// Retail ctor 0x16620 clears +4 and constructs basic_ios at +8;
	// teardown 0x7B6990 uses VA 0xDDEE18 + 8. Field purpose is unknown.
	char m_unknown04[4];
};
class Rva007B69B0Obj : virtual public _STL::basic_ios<unsigned short, _STL::char_traits<unsigned short> >
{
public:
	~Rva007B69B0Obj() {}
};

Rva007B68D0Obj g_007b68d0;
Rva007B68F0Obj g_007b68f0;
Rva007B6970Obj g_007b6970;
Rva007B6910Obj g_007b6910;
Rva007B6930Obj g_007b6930;
Rva007B6990Obj g_007b6990;
Rva007B69B0Obj g_007b69b0;
