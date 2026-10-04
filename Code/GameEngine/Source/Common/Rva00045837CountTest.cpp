// cl: /O1
// BFME1 donor1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/Common/Bfme5TinyTwentyNine.cpp, compiled /O1.
// Target Ghidra00045837/22B proves control word+14, pointers+8/+C,
// arithmetic division by8, and EAX result0 only when control==1 and count0.
// The element payload and original names remain unknown. Constness and
// the unsigned count expression are donor/source inferences. The whole
// donor unit places only this body under these settings.
struct Rva00045837Element
{
	unsigned int opaque[2];
};

class Rva00045837
{
public:
	int test() const;
private:
	// ?Rva00045837::count present-unmatched
	unsigned int count() const { return finish - begin; }
	unsigned int reserved[2];
	Rva00045837Element *begin;
	Rva00045837Element *finish;
	unsigned int reserved10;
	int control;
};

int Rva00045837::test() const
{
	int result = 1;
	if (control == 1 && !(count() > 0))
		result = 0;
	return result;
}
