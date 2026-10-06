// Zero Hour profile_funclevel.h, unchanged in BFME2: the function-level
// profiler's public handles. BFME2 ships the !HAS_PROFILE build, so every
// accessor returns empty data (profile_funclevel.cpp).

#ifndef PROFILE_FUNCLEVEL_H
#define PROFILE_FUNCLEVEL_H

class ProfileFuncLevel
{
	friend class Profile;
	ProfileFuncLevel(const ProfileFuncLevel &);
	ProfileFuncLevel &operator=(const ProfileFuncLevel &);

public:
	class Id;
	class Thread;

	class IdList
	{
		friend Id;

	public:
		IdList(void) : m_ptr(0) {}
		bool Enum(unsigned index, Id &id, unsigned *countPtr = 0) const;

	private:
		void *m_ptr;
	};

	class Id
	{
		friend IdList;
		friend Thread;

	public:
		Id(void) : m_funcPtr(0) {}

		enum
		{
			Total = 0xffffffff
		};

		const char *GetSource(void) const;
		const char *GetFunction(void) const;
		unsigned GetAddress(void) const;
		unsigned GetLine(void) const;
		unsigned __int64 GetCalls(unsigned frame) const;
		unsigned __int64 GetTime(unsigned frame) const;
		unsigned __int64 GetFunctionTime(unsigned frame) const;
		IdList GetCaller(unsigned frame) const;

	private:
		void *m_funcPtr;
	};

	class Thread
	{
		friend ProfileFuncLevel;

	public:
		Thread(void) : m_threadID(0) {}
		bool EnumProfile(unsigned index, Id &id) const;
		unsigned GetId(void) const
		{
			return unsigned(m_threadID);
		}

	private:
		class ProfileFuncLevelTracer *m_threadID;
	};

	static bool EnumThreads(unsigned index, Thread &thread);

private:
	ProfileFuncLevel(void);
};

#endif // PROFILE_FUNCLEVEL_H
