#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int Wolf;
	int Sheep;
	int Cabbage;
	int Boat;
}State;

typedef struct
{
	State gameState[100];
	State *head;
	State *tail;
	int NumberOfElements;
}Order;

void StatePrint(State *currentGameState)
{
	printf("V O K B:");
	if (currentGameState->Wolf)
		printf("1");
	else
		printf("0");

	if (currentGameState->Sheep)
		printf("1");
	else
		printf("0");

	if (currentGameState->Cabbage)
		printf("1");
	else
		printf("0");

	if (currentGameState->Boat)
		printf("1");
	else
		printf("0");

	printf("\n");
}

void GetMoves(State *beginningState, int iteration)
{
	if (beginningState->Wolf == 1 && beginningState->Sheep == 1 && beginningState->Cabbage == 1)
		return;

	switch (iteration)
	{
	case (0):
		if (beginningState->Wolf == beginningState->Boat && beginningState->Wolf != beginningState->Sheep) {
			beginningState->Wolf = !beginningState->Wolf;
			beginningState->Boat = !beginningState->Boat;
			StatePrint(beginningState);
		}
		break;
	case(1):
		if ((beginningState->Sheep == beginningState->Boat && beginningState->Sheep == beginningState->Wolf)
			|| (beginningState->Sheep == beginningState->Boat && beginningState->Sheep == beginningState->Cabbage) 
			|| (beginningState->Sheep != beginningState->Wolf && beginningState->Sheep != beginningState->Cabbage && beginningState->Sheep == beginningState->Boat)) {
			beginningState->Sheep = !beginningState->Sheep;
			beginningState->Boat = !beginningState->Boat;
			StatePrint(beginningState);
		}
		break;
	case(2):
		if (beginningState->Cabbage == beginningState->Boat && beginningState->Cabbage == beginningState->Sheep) {
			beginningState->Cabbage = !beginningState->Cabbage;
			beginningState->Boat = !beginningState->Boat;
			StatePrint(beginningState);
		}
		break;
	case(3):
		beginningState->Boat = !beginningState->Boat;
		StatePrint(beginningState);
		break;
	}
	
	GetMoves(beginningState, (iteration + 1) % 4);

}

void main()
{
	State startState = { 0 };
	GetMoves(&startState, 0);

	system("pause");
}