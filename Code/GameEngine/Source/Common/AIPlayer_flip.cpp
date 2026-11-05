// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common

#include "../../Include/GameLogic/AIPlayerClass.h"
#include "../GameLogic/AI/TeamInQueue.h"

void AIPlayer::flip()
{
	TeamInQueue *currentNode = m_teamReadyQueue;
	TeamInQueue *lastNode = 0;
	if (currentNode)
	{
		do
		{
			TeamInQueue *firstLink = currentNode->m_prevReady;
			TeamInQueue *secondLink = currentNode->m_nextReady;
			currentNode->m_nextReady = firstLink;
			currentNode->m_prevReady = secondLink;
			lastNode = currentNode;
			currentNode = secondLink;
		} while (currentNode);
	}
	m_teamReadyQueue = lastNode;
}
