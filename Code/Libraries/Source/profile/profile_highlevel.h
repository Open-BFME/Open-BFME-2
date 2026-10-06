// Zero Hour profile_highlevel.h: the high-level profiler's public handles.

#ifndef PROFILE_HIGHLEVEL_H
#define PROFILE_HIGHLEVEL_H

class ProfileId;

class ProfileHighLevel
{
	friend class Profile;
	ProfileHighLevel(const ProfileHighLevel &);
	ProfileHighLevel &operator=(const ProfileHighLevel &);

public:
	class Id
	{
		friend ProfileHighLevel;

	public:
		Id(void) : m_idPtr(0) {}
		void Increment(double add = 1.0);
		void SetMax(double max);
		const char *GetName(void) const;
		const char *GetDescr(void) const;
		const char *GetUnit(void) const;
		const char *GetCurrentValue(void) const;
		const char *GetValue(unsigned frame) const;
		const char *GetTotalValue(void) const;

	private:
		ProfileId *m_idPtr;
	};

	static Id AddProfile(const char *name, const char *descr, const char *unit, int precision, int exp10 = 0);
	static bool EnumProfile(unsigned index, Id &id);
	static bool FindProfile(const char *name, Id &id);

private:
	ProfileHighLevel(void);
};

#endif // PROFILE_HIGHLEVEL_H
