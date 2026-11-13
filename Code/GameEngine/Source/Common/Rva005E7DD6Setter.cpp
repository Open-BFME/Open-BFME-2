// cl: /O1 /MD
// Range-34 dump lane: 33B plain method at 0x005E7DD6 (ret 4).
// Change-notify setter: when the argument differs from +0xC, runs the
// pinned 0x005E7855 pre-hook, stores it, then runs the pinned 0x005E7C56
// post-hook. All identities unproven (address-derived).
#include "../../Include/Common/Rva005E7855.h"

class StrategicInGameUI
{
public:
	class BuildQueueDetailsPanel
	{
	public:
		class Impl
		{
		public:
			class Icon
			{
			public:
				void rva005E7C56();
			};
		};
	};
};

class Rva005E7DD6
{
public:
	int m00;
	int m04;
	int m08;
	int m0c;
	void preChange();
	void postChange();
	void setRva005E7DD6(int v);
};

void Rva005E7DD6::setRva005E7DD6(int v)
{
	if (v == m0c)
		return;
	((Rva005E7855 *)this)->rva005E7855();
	m0c = v;
	((StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon *)this)->rva005E7C56();
}
