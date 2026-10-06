// cl: /Oy- /DNDEBUG /MD /GX
//
// Value-returning STLport-string getters with the RVO idiom proven by
// AsciiStringRvoGetters.cpp (retail 0x00274DB6 etc., 30 bytes):
// each returns the string member at its offset via the hidden return
// pointer; the member copy-constructs directly into it (RVO) through
// the STLport copy bodies at 0x9170 (narrow) / 0xEA90 (wide), both
// matched rows, and the function returns the hidden pointer. The copy
// constructor is declared only so the call resolves to the ledger row
// (split-TU rule: caller here, body in stlport_*_string_copy_ctor.cpp).
// Class names are address-derived (identity unrecoverable from 30
// bytes); member names positional.

namespace _STL
{

template <class T>
class char_traits {};

template <class T>
class allocator {};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	Pointer _M_data;
};

template <class CharT, class Alloc>
class _String_base
{
public:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
class basic_string : public _String_base<CharT, Alloc>
{
public:
	basic_string(const basic_string<CharT, Traits, Alloc> &that);
	~basic_string();
};

}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > StlportNarrowString;
typedef unsigned short WideChar;
typedef _STL::basic_string<WideChar, _STL::char_traits<WideChar>, _STL::allocator<WideChar> > StlportWideString;

class Rva00389E2DNarrowField
{
public:
	StlportNarrowString get() const;

private:
	char m_pad[0xB4];
	StlportNarrowString m_value; // +0xB4
};

// ?get@Rva00389E2DNarrowField@@QBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@XZ
StlportNarrowString Rva00389E2DNarrowField::get() const
{
	return m_value;
}

class Rva00389E4BNarrowField
{
public:
	StlportNarrowString get() const;

private:
	char m_pad[0xC4];
	StlportNarrowString m_value; // +0xC4
};

// ?get@Rva00389E4BNarrowField@@QBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@XZ
StlportNarrowString Rva00389E4BNarrowField::get() const
{
	return m_value;
}

class Rva00389E87NarrowField
{
public:
	StlportNarrowString get() const;

private:
	char m_pad[0x160];
	StlportNarrowString m_value; // +0x160
};

// ?get@Rva00389E87NarrowField@@QBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@XZ
StlportNarrowString Rva00389E87NarrowField::get() const
{
	return m_value;
}

class Rva00389F2CNarrowField
{
public:
	StlportNarrowString get() const;

private:
	char m_pad[0x490];
	StlportNarrowString m_value; // +0x490
};

// ?get@Rva00389F2CNarrowField@@QBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@XZ
StlportNarrowString Rva00389F2CNarrowField::get() const
{
	return m_value;
}

class Rva00389E69WideField
{
public:
	StlportWideString get() const;

private:
	char m_pad[0x284];
	StlportWideString m_value; // +0x284
};

// ?get@Rva00389E69WideField@@QBE?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@XZ
StlportWideString Rva00389E69WideField::get() const
{
	return m_value;
}
