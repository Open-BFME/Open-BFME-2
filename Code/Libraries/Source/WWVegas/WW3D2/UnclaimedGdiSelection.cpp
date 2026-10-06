// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Clean C++ donor: Open-BFME/Open-BFME-1 2791daf5536e4e2147dc3a4aa25c17816828dd69,
// game/Libraries/Source/WWVegas/WW3D2/UnclaimedGdiSelection.cpp, b1 0x0093C310.
// Native BFME2 0x001543C0 has an aligned int3-delimited 30B extent and ret 8.
// It stores the first argument at this+0, calls the PE-proven GDI32 SelectObject
// import with both arguments, stores the returned object at this+4 and returns
// this. Those accesses and ABI are target facts. The donor supplies the C++
// constructor spelling; original class identity remains unknown. The name is
// based on the target address. Handle pointers represent the native four-byte
// values without asserting an original member type or unseen class layout.

extern "C" __declspec(dllimport) void *__stdcall SelectObject( void *dc, void *object );

class Rva001543C0Selection
{
public:
	Rva001543C0Selection( void *dc, void *object );

	void *m_dc;
	void *m_previous;
};

Rva001543C0Selection::Rva001543C0Selection( void *dc, void *object )
	: m_dc( dc )
{
	m_previous = SelectObject( dc, object );
}
