// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva001FF5C3@Rva003B1546@@UAEXXZ @0x001FF5C3 47B: slot 9 cleanup of the
// vector<void*> at +0x0C via rowed Overridable::deleteOverrides 0x001E35ED
// with conditional rowed voidptr erase 0x001FF51F. Evidence: vtable slot 9
// of 0x0081ED1C (class of ??1Rva003B1546@@UAE@XZ in Rva003B1546Dtor.cpp);
// layout mirrors Rva003B1546Dtor.cpp (GameEngineDeletingBase +0x00,
// vector<void*> +0x0C, int +0x18).
#include <vector>

class Overridable {
public:
	Overridable *deleteOverrides();
};

class AsciiStringMember {
public:
	~AsciiStringMember();
};

class GameEngineDeletingBase {
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

class Rva003B1546 : public GameEngineDeletingBase {
public:
	virtual ~Rva003B1546();
	virtual void rva001FF5C3();
private:
	_STL::vector<void *, _STL::allocator<void *> > m_vec;
	int m_18;
};

void Rva003B1546::rva001FF5C3()
{
	for (void **it = m_vec.begin(); it != m_vec.end(); ) {
		Overridable *stillValid = ((Overridable *)*it)->deleteOverrides();
		if (stillValid == 0)
			it = m_vec.erase(it);
		else
			++it;
	}
}
