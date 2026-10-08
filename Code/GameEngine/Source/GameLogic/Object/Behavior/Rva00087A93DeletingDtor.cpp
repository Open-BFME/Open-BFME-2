// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// ??_GRva00087A93@@QAEPAXI@Z @ 0x00087A93 (38B): null-guarded 4-byte
// owning-reference deleting dtor; decrements pointee refcount at +4 and calls
// slot 0 when it reaches zero then conditionally deletes. Evidence: callers
// 0x0008984B and 0x0008A208 plus destroy loop 0x0008A1FD; shape matches
// ??_GAsciiString at 0x00142D40 (41B add) with /O1 dec form per §4.1.

class Rva00087A93 {
	struct Data {
		virtual void slot();
		int ref;
	};
	Data *m_data;
public:
	~Rva00087A93()
	{
		Data *d = m_data;
		if (d && --d->ref == 0)
			d->slot();
	}
};

void Rva00087A93Delete(Rva00087A93 *p)
{
	delete p;
}

// ?Rva0008A1FDDestroy@@YAXPAVRva00087A93@@0@Z @ 0x0008A1FD (27B): the range
// destroy loop over these references. MSVC calls each explicit destructor
// through the scalar deleting destructor above with flags 0.
void Rva0008A1FDDestroy(Rva00087A93 *first, Rva00087A93 *last)
{
	for (; first != last; ++first)
		first->~Rva00087A93();
}
