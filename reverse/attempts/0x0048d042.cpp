// ?erase@CameraMarkerVec@@QAEPAVCameraMarker@@PAV2@0@Z
// partial score=0.98 date=2026-09-26
// cl: /O1 /DNDEBUG /MD
//
// ?erase@CameraMarkerVec@@QAEXPAVCameraMarker@@0@Z, retail 0x0048D042,
// 51 bytes. CameraMarker vector erase(first, last): copies [last, finish)
// down to first through the 0x00288A5C assign wrapper, destroys the
// stale tail through the rowed 0x0048CE25 _Destroy, updates finish. All
// three retail callers pass (begin, end): the FlammableUpdateModuleData
// ctor at 0x48D5EC plus 0x2895B4 plus 0x289A86. The BFME1 donor keeps the
// same idiom as MemberB::clear() calling erase(m_begin, m_end).
// The wrapper body passes the __copy end pointer through in eax (the rowed
// void spelling cannot name it), so this TU calls a pointer-returning twin
// spelling (pinned); the class key keeps the _Destroy call on the rowed
// PAV spelling with no pin.

class CameraMarker;

CameraMarker *Rva00288A5CAssign(CameraMarker *first, CameraMarker *last, CameraMarker *dest, void *unused);

namespace _STL
{

struct random_access_iterator_tag
{
};

template <class _Tp>
void _Destroy(_Tp *first, _Tp *last);

}

struct CameraMarkerVec
{
	CameraMarker *erase(CameraMarker *first, CameraMarker *last);

	CameraMarker *m_start;
	CameraMarker *m_finish;
	CameraMarker *m_end;
};

CameraMarker *CameraMarkerVec::erase(CameraMarker *first, CameraMarker *last)
{
	CameraMarker *newFinish;
	{
		_STL::random_access_iterator_tag tag;
		newFinish = Rva00288A5CAssign(last, m_finish, first, &tag);
	}
	_STL::_Destroy(newFinish, m_finish);
	m_finish = newFinish;
	return first;
}
