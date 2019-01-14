#pragma once

typedef struct
{
	int Wolf;
	int Sheep;
	int Cabbage;
	int Boat;
}State;

void PrintState(State currentGameState);

int WinState(State state);

int LoseState(State state);

void CreateChildren(State parentState, State *nextState);

int GetMoves(State beginningState, int iteration);