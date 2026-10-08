// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// InGameUI::FormationPreviewPoolObject::dismiss / assign (WorldBuilder names, InGameUI.cpp lines 8200 and 8189: hide/show the +0x00 drawable through 0x002707FA and set +0x08 to 0 / 1).
// was ?rva0029B1C2@Rva0029B1C2@@QAEXXZ 0x0029B1C2 22B evidence: chain via rowed 0x002707FA; clears byte at +8 after forwarding 0
class Rva002707FA
{
public:
	void rva002707FA(unsigned char value);
};

class InGameUI
{
public:
	class FormationPreviewPoolObject;
};
class InGameUI::FormationPreviewPoolObject
{
	Rva002707FA *m00;
	char _p04[4];
	unsigned char m08;
public:
	__declspec(noinline) void dismiss();
	void assign();
	void releaseAssets();
};

void InGameUI::FormationPreviewPoolObject::dismiss()
{
	if (m00 != 0)
		m00->rva002707FA(0);
	m08 = 0;
}

void InGameUI::FormationPreviewPoolObject::assign()
{
	if (m00 != 0)
		m00->rva002707FA(1);
	m08 = 1;
}

// Borrowed owner view: identity and original member names remain unresolved.
// Native81: four nullable pool pointers +5B4 and 12-byte entry vector +5A0.
// Only nonnull slots are dismissed/cleared. The vector end is captured before
// forming its address; after dismissing each +8 pointer the native calls the
// independently rowed 12-byte vector erase. No allocation layout is asserted.
#include <vector>
#include <map>

struct Gen_p12pod
{
	int unknown[2];
	InGameUI::FormationPreviewPoolObject *pool;
};
extern template class _STL::vector<Gen_p12pod>;

struct FormationVectorView
{
	Gen_p12pod *begin;
	Gen_p12pod *end;
	Gen_p12pod *capacity;
};

class Rva0029B63A
{
public:
	_STL::_Rb_tree_node_base *head;
	int count;
	void rva0029E015();
};

class Rva002A3DD3
{
	char unknown[0x590];
	Rva0029B63A tree;
	char gap598[8];
	FormationVectorView entries;
	char gap[8];
	InGameUI::FormationPreviewPoolObject *slots[4];
public:
	__declspec(noinline) void rva002A3DD3();
	void rva002A3E24();
};

void Rva002A3DD3::rva002A3DD3()
{
	InGameUI::FormationPreviewPoolObject **p = slots;
	for (int n = 4; n != 0; --n, ++p) {
		if (*p) {
			(*p)->dismiss();
			*p = 0;
		}
	}
	Gen_p12pod *end = entries.end;
	FormationVectorView &range = entries;
	for (Gen_p12pod *it = range.begin; it != end; ++it)
		it->pool->dismiss();
	_STL::vector<Gen_p12pod> &vector =
		*reinterpret_cast<_STL::vector<Gen_p12pod> *>(&range);
	vector.erase(vector.begin(), vector.end());
}

// Native54 2A3E24..2A3E5A: same owner as the dismiss method, then tree+590
// node payload+14 invokes named FormationPreviewPoolObject::releaseAssets.
// The iterator and tree clear both resolve to independently rowed providers.
void Rva002A3DD3::rva002A3E24()
{
	rva002A3DD3();
	Rva0029B63A &pool = tree;
	for (_STL::_Rb_tree_node_base *it = pool.head->_M_left; it != pool.head;
		it = _STL::_Rb_global<bool>::_M_increment(it)) {
		reinterpret_cast<InGameUI::FormationPreviewPoolObject *>(
			reinterpret_cast<char *>(it) + 0x14)->releaseAssets();
	}
	pool.rva0029E015();
}
