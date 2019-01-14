#include "RecursionHeader.h"

void PrintState(State currentGameState)
{
	if (currentGameState.Wolf)
		printf("Wolf ");
	else
		printf("     ");
	if (currentGameState.Sheep)
		printf("Sheep ");
	else
		printf("      ");
	if (currentGameState.Cabbage)
		printf("Cabbage ");
	else
		printf("        ");
	if (currentGameState.Boat)
		printf("Boat ");
	else
		printf("     ");

	printf("~~~~~~~~~~~~~~~~~~~~~~~ ");

	if (!currentGameState.Wolf)
		printf("Wolf ");
	else
		printf("     ");
	if (!currentGameState.Sheep)
		printf("Sheep ");
	else
		printf("      ");
	if (!currentGameState.Cabbage)
		printf("Cabbage ");
	else
		printf("        ");
	if (!currentGameState.Boat)
		printf("Boat ");
	else
		printf("     ");

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