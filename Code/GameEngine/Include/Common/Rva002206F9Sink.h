/* Target facts (RVAs): the template-count walk 0x0037DF8D hands each ThingTemplate to its sink's slot 0
and stops when it returns zero. Constructor 0x0059AEE9 installs VA 0x00C70E5C, a one-slot table whose
only entry is 0x0059B14E, then clears +0x04 and stores its argument at +0x08; 0x0059AEFF builds the same
object inline on the stack, runs the walk and returns +0x04. 0x0059B14E (RET 4) looks up the experience
level for its template argument (passed as an int, the rowed signature) and the +0x08 value and adds that level's award to +0x04, returning 1.
Class names are address-derived; the original spellings are unknown. */
#pragma once

#ifndef __BFME2_RVA002206F9SINK_H_
#define __BFME2_RVA002206F9SINK_H_

class Rva002206F9Sink
{
public:
	virtual int add(int value) = 0;
};

// The experience-award visitor. RVA0059AEE9_INLINE_CONSTRUCTOR selects the
// inline constructor for the unit that builds it in place, as retail does.
class Rva0059AEE9 : public Rva002206F9Sink
{
public:
#ifdef RVA0059AEE9_INLINE_CONSTRUCTOR
	__declspec(dllimport) __forceinline Rva0059AEE9(int experience)
		: m_award(0), m_experience(experience) {}
#else
	Rva0059AEE9(int experience);
#endif
	virtual int add(int value);

	int m_award;		// +0x04
	int m_experience;	// +0x08
};

#endif
