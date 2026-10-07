// ?setInitialHealth@ActiveBody@@UAEXM_N@Z
// partial score=0.9 date=2026-10-07
// Banked near miss for ActiveBody::setInitialHealth 0x004C0642 (319B), ActiveBody.cpp views as of this commit.
// Only diff: retail copies the Object position's z through xmm0 (movss, evicting the factor to [ebp+0xc]); this source copies z through eax.
// Every other byte (factor spill slot, x in-place then copied after call 2, y/z straight into the passed point, #line 1279 file string) matches.
struct ActiveBodySidePoint
{
	ActiveBodySidePoint() {}
	ActiveBodySidePoint(const ActiveBodySidePoint &that)
	{
		x = that.x;
		y = that.y;
		z = that.z;
	}
	Real x, y, z;
};

extern Real GetGameLogicRandomValueReal(Real low, Real high, char *file, Int line);
#define GameLogicRandomValueReal(lo, hi) \
	GetGameLogicRandomValueReal((lo), (hi), __FILE__, __LINE__)

// ActiveBody, retail 0x004BFCD4 (83B): attemptDamage's directional branch
// (damage type 4). Spread the damage over the sides facing the source's
// position (its transform translation) through 0x004BFB1C.
void ActiveBody::rva004BFCD4(Real amount, DamageInfo *damageInfo)
{
	Object *source = TheGameLogic->findObjectByID(damageInfo->in.m_sourceID);
	if (source)
	{
		ActiveBodySidePoint pos;
		pos.x = source->m_transform[0][3];
		pos.y = source->m_transform[1][3];
		pos.z = source->m_transform[2][3];
		rva004BFB1C(amount, (const Coord3D *)&pos);
	}
}
void ActiveBody::setInitialHealth(Real initialPercent, Bool directional)
{
	if (initialPercent > 100.0f)
		m_maxHealth = m_maxHealth * initialPercent * 0.01f;
	Real factor = initialPercent * 0.01f;
	if (directional)
	{
		m_prevHealth = m_currentHealth;
		m_currentHealth += m_maxHealth * (initialPercent * 0.01f) - m_currentHealth;
		const Coord3D *objPos = getObject()->getPosition();
		ActiveBodySidePoint pos;
		pos.x = objPos->x;
		pos.y = objPos->y;
		pos.z = objPos->z;
		ActiveBodySidePoint jittered;
#line 1279 "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Body\\ActiveBody.cpp"
		pos.x += GameLogicRandomValueReal(-1.0f, 1.0f);
		jittered.y = pos.y + GameLogicRandomValueReal(-1.0f, 1.0f); jittered.x = pos.x;
		jittered.z = pos.z + GameLogicRandomValueReal(-1.0f, 1.0f);
		rva004BFB1C((1.0f - initialPercent * 0.01f) * m_maxHealth, (const Coord3D *)&jittered);
	}
	else
	{
		internalChangeHealth(factor * m_initialHealth - m_currentHealth, 0);
	}
}
