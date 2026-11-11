// StatsReporter: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_STATSREPORTER_H
#define CANONICAL_STATSREPORTER_H

class LivingWorldPlayer;
class Player;

class StatsReporter
{
public:
	static void ProcessOnlineGameResults(Player *player);
	static void ProcessStrategicSinglePlayerGame(LivingWorldPlayer *player);
};

#endif // CANONICAL_STATSREPORTER_H
