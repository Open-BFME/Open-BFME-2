// cl: /Oy- /DNDEBUG /MD
//
// ?rva00361624@Rva00361624@@QAEPAVRva0036105B@@PAV2@0@Z, retail 0x00361624,
// 51 bytes. Vector erase(first, last) over 148-byte Rva0036105B elements:
// copies [last, finish) down to first through the 0x00361594 assign wrapper
// (pointer-returning twin, pinned), destroys the stale tail through the
// rowed 0x003615CD _Destroy (Rva0036105B instantiation, pinned), updates
// finish, returns first. Evidence: chain from 0x00361594 which muse-05 just
// landed; byte-identical 51B shape and push order to the landed
// ?erase@CameraMarkerVec@@QAEPAVCameraMarker@@PAV2@0@Z at 0x0048D042
// (lea eax,[ebp+0xb] is the same (char*)&first+3 dummy, mov edi,eax proves
// the wrapper's pointer return); callers at 0x0036167A and 0x00361750.

class Rva0036105B;

Rva0036105B *Rva00361594Assign(Rva0036105B *first, Rva0036105B *last, Rva0036105B *dest, void *unused);

namespace _STL
{

template <class _Tp>
void _Destroy(_Tp first, _Tp last);

}

// Link: nothing defines _Destroy<Rva0036105B *>. Retail's 0x003615CD is the
// rowed _Destroy<Rva003615E5Record *> (Rva003615E5VectorDtor.cpp, the same
// 148-byte element); an inline forwarder reaches it with the same pushes.
struct Rva003615E5Record;

namespace _STL
{

template <> void _Destroy<Rva003615E5Record *>(Rva003615E5Record *first, Rva003615E5Record *last);
template <> __declspec(dllimport) __forceinline void _Destroy<Rva0036105B *>(Rva0036105B *first, Rva0036105B *last)
{ _Destroy((Rva003615E5Record *)first, (Rva003615E5Record *)last); }

}

class Rva00361624
{
public:
	Rva0036105B *rva00361624(Rva0036105B *first, Rva0036105B *last);
	void rva00361675();

	Rva0036105B *m_start;
	Rva0036105B *m_finish;
	Rva0036105B *m_end;
};

Rva0036105B *Rva00361624::rva00361624(Rva0036105B *first, Rva0036105B *last)
{
	Rva0036105B *newFinish = Rva00361594Assign(last, m_finish, first, (void *)((char *)&first + 3));
	_STL::_Destroy(newFinish, m_finish);
	m_finish = newFinish;
	return first;
}

// ?rva00361675@Rva00361624@@QAEXXZ, retail 0x00361675, 11 bytes: clear() -
// the erase above over [start, finish) (its call at 0x0036167A). Skeleton
// twin of STLport vector clear 0x000BCFB8.
void Rva00361624::rva00361675()
{
	rva00361624(m_start, m_finish);
}
