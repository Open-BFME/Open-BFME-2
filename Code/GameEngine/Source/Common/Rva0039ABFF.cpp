// cl: /O1 /DNDEBUG /MD
// ?rva0039ABFF@ExperienceTracker@@QBE_NXZ 0x0039ABFF 13: forwards this as int.
// Evidence: pin 0x00288CFA plus callers incl matched VeterancyCrateCollide.
class Rva00288CFA
{
public:
	bool rva00288CFA(int val);
};

extern Rva00288CFA *g_00DFECC4;

class ExperienceTracker
{
public:
	bool rva0039ABFF() const;
};

bool ExperienceTracker::rva0039ABFF() const
{
	return g_00DFECC4->rva00288CFA((int)this);
}
