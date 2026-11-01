// cl: /DNDEBUG /MD /EHsc
// Two accessors into the first array.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/Gen_000cd680.cpp); trimmed to the two T1
// bodies the sweep places.

typedef int Int;
typedef short Short;

struct Gen_000cd680_Element
{
	Short m_key;
	char m_unknown02[10];
	void *m_pointer;
};

class Gen_000cd680
{
public:
	Int firstKeyA( void ) const;
	Int keyAtA( Int index ) const;
	void **pointerAtA( Int index ) const;

	Int firstKeyB( void ) const;
	Int keyAtB( Int index ) const;
	void **pointerAtB( Int index ) const;

	Int firstKeyC( void ) const;
	Int keyAtC( Int index ) const;
	void **pointerAtC( Int index ) const;

private:
	char m_unknown00[0x0C];
	Gen_000cd680_Element *m_arrayA;			// +0x0C
	char m_unknown10[0x63C - 0x10];
	Gen_000cd680_Element *m_arrayB;			// +0x63C
	char m_unknown640[0x658 - 0x640];
	Gen_000cd680_Element *m_arrayC;			// +0x658
};

Int Gen_000cd680::keyAtA( Int index ) const { return m_arrayA[index].m_key; }
