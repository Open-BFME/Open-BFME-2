// Zero Hour profile_result.h: result function interface. BFME2's vtables
// (DOT 0x00CE84D0, GTT 0x00CE85D8, CSV 0x00CE85E4) put WriteResults at
// slot 0 and Delete at slot 1, then each writer's GetName at slot 2.

#ifndef PROFILE_RESULT_H
#define PROFILE_RESULT_H

class ProfileResultInterface
{
	ProfileResultInterface(const ProfileResultInterface &);
	ProfileResultInterface &operator=(const ProfileResultInterface &);

public:
	virtual void WriteResults(void) = 0;
	virtual void Delete(void) = 0;

protected:
	ProfileResultInterface(void) {}
};

#endif // PROFILE_RESULT_H
