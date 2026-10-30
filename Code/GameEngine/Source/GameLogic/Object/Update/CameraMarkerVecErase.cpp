// cl: /Oy- /DNDEBUG /MD
// stlport
//
// ?erase@CameraMarkerVec@@QAEPAVCameraMarker@@PAV2@0@Z, retail 0x0048D042,
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

#include <vector>

// Use the vector base already verified in FlammableUpdateModuleDataCtor.cpp.
class CameraMarker { public: ~CameraMarker(); char m_pad[8]; };

CameraMarker *Rva00288A5CAssign(CameraMarker *first, CameraMarker *last, CameraMarker *dest, void *unused);

namespace _STL
{

template<> void _Destroy<CameraMarker*>(CameraMarker*, CameraMarker*);

}

struct CameraMarkerVec : public _STL::vector<CameraMarker>
{
	CameraMarker *erase(CameraMarker *first, CameraMarker *last);
};

CameraMarker *CameraMarkerVec::erase(CameraMarker *first, CameraMarker *last)
{
	CameraMarker *newFinish = Rva00288A5CAssign(last, _M_finish, first, (void *)((char *)&first + 3));
	_STL::_Destroy(newFinish, _M_finish);
	_M_finish = newFinish;
	return first;
}
