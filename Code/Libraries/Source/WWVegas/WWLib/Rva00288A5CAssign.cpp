// cl: /O1 /DNDEBUG /MD
//
// ?Rva00288A5CAssign@@YAXPAUCameraMarker@@00PAX@Z, retail 0x00288A5C,
// 29 bytes. CameraMarker range-assign wrapper: materializes the
// random_access tag on stack and forwards (first, last, dest, tag, null)
// to the rowed __copy at 0x48C897, cleaning 20 bytes as cdecl. Called by
// the Flammable vector helper at 0x48D056 and by the list manager at
// 0x523EE3 (which also destroys CameraMarkers). The fourth incoming word
// is ignored by the body; the true 4-arity identity is unproven, hence
// the address-derived vehicle name. The __copy template is declared
// (never defined) so the call resolves through the ledger row; the tag
// and element spellings mirror that row.

namespace _STL
{
	struct random_access_iterator_tag
	{
	};
}

struct CameraMarker;

namespace _STL
{
	template <class _InputIter, class _OutputIter, class _Dist>
	_OutputIter __copy(_InputIter first, _InputIter last, _OutputIter dest, const random_access_iterator_tag &tag, _Dist *extra);
}

void Rva00288A5CAssign(CameraMarker *first, CameraMarker *last, CameraMarker *dest, void *unused)
{
	_STL::random_access_iterator_tag tag;
	_STL::__copy(first, last, dest, tag, (int *)0);
}
