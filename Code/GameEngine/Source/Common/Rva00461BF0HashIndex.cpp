// cl: /Ireference/open-bfme-1/inputs/reference/shims/stringinline
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/Rva00461BF0HashIndex.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// ??A?$hash_map@VAsciiString@@VRva0045EF90 0x00411205 (155B). Callee addresses
// are read off retail's call sites (reverse/symbols.csv). Only the placed
// bodies are carried; the donor's other definitions are omitted.
// Open-BFME: STLport hash_map index for the Rva0045EF90Object value.
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "StringInline.h"

class Rva0045EF90Base
{
public:
	Rva0045EF90Base() : m_value( -1 ) {}
	Rva0045EF90Base( const Rva0045EF90Base &source ) : m_value( source.m_value ) {}
	virtual ~Rva0045EF90Base();

private:
	unsigned m_value;
};

class Rva0045EF90Object : public Rva0045EF90Base
{
public:
	Rva0045EF90Object();
	Rva0045EF90Object( const Rva0045EF90Object &source );
	virtual ~Rva0045EF90Object();

private:
	AsciiString m_first;
	AsciiString m_second;
	unsigned m_handle;
	float m_value14;
	float m_value18;
	float m_value1c;
	float m_value20;
	unsigned char m_value24;
	unsigned char m_padding25[ 3 ];
	AsciiString m_last;
};


namespace rts
{
	template <class T> struct hash
	{
		unsigned int operator()( T value ) const;
	};

	template <class T> struct equal_to
	{
		bool operator()( const T &left, const T &right ) const;
	};
}

typedef _STL::hash_map<AsciiString, Rva0045EF90Object,
	rts::hash<AsciiString>, rts::equal_to<AsciiString> > Rva00461BF0Map;

template Rva0045EF90Object &Rva00461BF0Map::operator[]( const AsciiString &key );
