#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int Wolf;
	int Sheep;
	int Cabbage;
	int Boat;
}State;

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

int LoseState(State state)
{
	return((state.Sheep == state.Wolf && state.Sheep != state.Boat) ||
		(state.Cabbage == state.Sheep && state.Cabbage != state.Boat));
}

void CreateChildren(State parentState, State nextState[4])
{
	for (int i = 0; i < 4; i++)
		nextState[i] = parentState;

	if (parentState.Wolf == parentState.Boat) {
		nextState[0].Wolf = !parentState.Wolf;
		nextState[0].Boat = !parentState.Boat;
	}
	if (parentState.Sheep == parentState.Boat) {
		nextState[1].Sheep = !parentState.Sheep;
		nextState[1].Boat = !parentState.Boat;
	}
	if (parentState.Cabbage == parentState.Boat) {
		nextState[2].Cabbage = !parentState.Cabbage;
		nextState[2].Boat = !parentState.Boat;
	}
	nextState[3].Boat = !parentState.Boat;
}

int GetMoves(State beginningState, int iteration)
{
	if (WinState(beginningState)) {
		PrintState(beginningState);
		return 1;
	}
	if (!iteration || LoseState(beginningState))
		return 0;
	
	State nextState[4];
	CreateChildren(beginningState, nextState);

	for (int i = 0; i < 4; i++) {
		if (GetMoves(nextState[i], iteration - 1)) {
			PrintState(beginningState);
			return 1;
		}
	}
	
	return 0;
}

void main()
{
	State startState = { 0 };
	for(int i = 0; !GetMoves(startState, i); i++)
		GetMoves(startState, i);

	system("pause");
}