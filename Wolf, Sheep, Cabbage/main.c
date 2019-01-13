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

void PrintState(State currentGameState)
{
	printf("W S C B:");
	if (currentGameState.Wolf)
		printf("1");
	else
		printf("0");

	if (currentGameState.Sheep)
		printf("1");
	else
		printf("0");

	if (currentGameState.Cabbage)
		printf("1");
	else
		printf("0");

	if (currentGameState.Boat)
		printf("1");
	else
		printf("0");

	printf("\n");
}

int WinState(State state)
{
	return (state.Wolf && state.Sheep && state.Cabbage);
}

int GetMoves(State beginningState, int iteration)
{
	if (WinState(beginningState)) {
		PrintState(beginningState);
		return 1;
	}
	if (!iteration)
		return 0;
	
	State nextState[4];
	for (int i = 0; i < 4; i++)
		nextState[i] = beginningState;

	if (beginningState.Wolf == beginningState.Boat && beginningState.Sheep != beginningState.Cabbage) {
		nextState[0].Wolf = !beginningState.Wolf;
		nextState[0].Boat = !beginningState.Boat;
	}
	if (beginningState.Sheep == beginningState.Boat) {
		nextState[1].Sheep = !beginningState.Sheep;
		nextState[1].Boat = !beginningState.Boat;
	}
	if (beginningState.Cabbage == beginningState.Boat  && beginningState.Sheep != beginningState.Wolf) {
		nextState[2].Cabbage = !beginningState.Cabbage;
		nextState[2].Boat = !beginningState.Boat;
	}
	nextState[3].Boat = !beginningState.Boat;

	for (int i = 0; i < 4; i++) {
		if (GetMoves(nextState[i], iteration - 1)) {
			PrintState(beginningState);
			return 1;
		}
		GetMoves(nextState[i], (iteration - 1));
	}
	
	return 0;
}

void main()
{
	State startState = { 0 };
	GetMoves(startState, 7);

	system("pause");
}