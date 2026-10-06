// cl: /O1 /arch:SSE /G7 /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// ??0Rva0030C95C@@QAE@HPAVTargetRef00217D4C@@@Z @0x0030C95C 34B.
// Caller 0x0028343D constructs a local with an integer and a retained target reference.
struct TargetRef00217D4C
{
public:
	void *object;
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class Rva0030C95C
{
public:
	Rva0030C95C(int value, TargetRef00217D4C *target);
private:
	int m_value;
	TargetRef00217D4C *m_target;
};

Rva0030C95C::Rva0030C95C(int value, TargetRef00217D4C *target)
	: m_value(value), m_target(target)
{
	if (target != 0)
	{
		++target->references;
		ReleaseTreeHintRef00217D4C(target);
	}
}
