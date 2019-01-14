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

// drugi dio
typedef struct _QueueState
{
	int wolf;
	int sheep;
	int cabbage;
	int boat;
	struct _QueueState* prevState;
}QueueState;

typedef struct
{
	QueueState stateList[1000];
	int head;
	int tail;
	int filled;
}Queue;

void CreateQueueChildren(QueueState parentState, Queue queue)
{
	if (parentState.wolf == parentState.boat) {
		queue.stateList[queue.tail].wolf = !parentState.wolf;
		queue.stateList[queue.tail].boat = !parentState.boat;
		queue.stateList[queue.tail].prevState = &parentState;
		queue.filled++;
		queue.tail++;
	}
	if (parentState.sheep == parentState.boat) {
		queue.stateList[queue.tail].sheep = !parentState.sheep;
		queue.stateList[queue.tail].boat = !parentState.boat;
		queue.stateList[queue.tail].prevState = &parentState;
		queue.tail++;
	}
	if (parentState.cabbage == parentState.boat) {
		queue.stateList[queue.tail].cabbage = !parentState.cabbage;
		queue.stateList[queue.tail].boat = !parentState.boat;
		queue.stateList[queue.tail].prevState = &parentState;
		queue.filled++;
		queue.tail++;
	}
	queue.stateList[queue.tail].boat = !parentState.boat;
	queue.stateList[queue.tail].prevState = &parentState;
	queue.filled++;
	queue.tail++;
}

void QueuePrintState(QueueState currentGameState)
{
	printf("W S C B:");
	if (currentGameState.wolf)
		printf("1");
	else
		printf("0");

	if (currentGameState.sheep)
		printf("1");
	else
		printf("0");

	if (currentGameState.cabbage)
		printf("1");
	else
		printf("0");

	if (currentGameState.boat)
		printf("1");
	else
		printf("0");

	printf("\n");
}

int QueueWinState(QueueState state)
{
	return (state.wolf && state.sheep && state.cabbage);
}

int QueueLoseState(QueueState state)
{
	return((state.sheep == state.wolf && state.sheep != state.boat) ||
		(state.cabbage == state.sheep && state.cabbage != state.boat));
}

int QueueStartState(QueueState state)
{
	return(!state.sheep && !state.wolf && !state.cabbage);
}

void GetQueueMoves(Queue queue)
{
	QueueState tmpState;
	int i = 0;
	while (!QueueWinState(queue.stateList[i])) {
		i++;
	}
	tmpState = queue.stateList[i];
	while (!QueueStartState(tmpState))
	{
		QueuePrintState(tmpState);
		tmpState = *tmpState.prevState;
	}
}

void main()
{
	//prvi dio
	
	QueueState startState = { 0 };

	//for(int i = 0; !GetMoves(startState, i); i++)
		//GetMoves(startState, i);
	
	//drugi dio
	Queue newQueue;
	newQueue.head = 0;
	newQueue.stateList[0] = startState;
	newQueue.tail = 1;
	newQueue.filled = 1;

	for (; !QueueWinState(newQueue.stateList[newQueue.tail]); newQueue.head++) {
		CreateQueueChildren(newQueue.stateList[newQueue.head], newQueue);
	}

	GetQueueMoves(newQueue);

	system("pause");
}