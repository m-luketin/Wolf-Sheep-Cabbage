#include <stdio.h>
#include <stdlib.h>

//First part - recursive depth search/generation
typedef struct
{
	int Wolf;
	int Sheep;
	int Cabbage;
	int Boat;
}State;

void PrintState(State currentGameState)
{
	printf("Wolf-Sheep-Cabbage-Boat: ");
	if (currentGameState.Wolf)
		printf("1");
	else
		printf("0");
	printf("-");

	if (currentGameState.Sheep)
		printf("1");
	else
		printf("0");
	printf("-");


	if (currentGameState.Cabbage)
		printf("1");
	else
		printf("0");
	printf("-");


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

//Second part - using a queue to preform a width search
typedef struct _QueueState
{
	int wolf;
	int sheep;
	int cabbage;
	int boat;
	int prevState;
}QueueState;

typedef struct
{
	QueueState stateList[100];
	int head;
	int tail;
	int filled;
}Queue;

void QueueCreateChildren(QueueState parentState, Queue *queue)
{
	if (parentState.wolf == parentState.boat) {
		queue->stateList[queue->tail].cabbage = parentState.cabbage;
		queue->stateList[queue->tail].sheep = parentState.sheep;
		queue->stateList[queue->tail].wolf = !parentState.wolf;
		queue->stateList[queue->tail].boat = !parentState.boat;
		queue->stateList[queue->tail].prevState = queue->head;
		queue->filled++;
		queue->tail++;
	}
	if (QueueContainsState(queue->stateList[queue->tail - 1], *queue)) {
		queue->tail--;
		queue->filled--;
	}

	if (parentState.sheep == parentState.boat) {
		queue->stateList[queue->tail].wolf = parentState.wolf;
		queue->stateList[queue->tail].cabbage = parentState.cabbage;
		queue->stateList[queue->tail].sheep = !parentState.sheep;
		queue->stateList[queue->tail].boat = !parentState.boat;
		queue->stateList[queue->tail].prevState = queue->head;
		queue->tail++;
		queue->filled++;
	}
	if (QueueContainsState(queue->stateList[queue->tail - 1], *queue)) {
		queue->tail--;
		queue->filled--;
	}

	if (parentState.cabbage == parentState.boat) {
		queue->stateList[queue->tail].wolf = parentState.wolf;
		queue->stateList[queue->tail].sheep = parentState.sheep;
		queue->stateList[queue->tail].cabbage = !parentState.cabbage;
		queue->stateList[queue->tail].boat = !parentState.boat;
		queue->stateList[queue->tail].prevState = queue->head;
		queue->filled++;
		queue->tail++;
	}
	if (QueueContainsState(queue->stateList[queue->tail - 1], *queue)) {
		queue->tail--;
		queue->filled--;
	}

	queue->stateList[queue->tail].cabbage = parentState.cabbage;
	queue->stateList[queue->tail].sheep = parentState.sheep;
	queue->stateList[queue->tail].wolf = parentState.wolf;
	queue->stateList[queue->tail].boat = !parentState.boat;
	queue->stateList[queue->tail].prevState = queue->head;
	queue->filled++;
	queue->tail++;
	if (QueueContainsState(queue->stateList[queue->tail - 1], *queue)) {
		queue->tail--;
		queue->filled--;
	}
}

void QueuePrintState(QueueState currentGameState)
{
	printf("Wolf-Sheep-Cabbage-Boat: ");
	if (currentGameState.wolf)
		printf("1");
	else
		printf("0");
	printf("-");

	if (currentGameState.sheep)
		printf("1");
	else
		printf("0");
	printf("-");

	if (currentGameState.cabbage)
		printf("1");
	else
		printf("0");
	printf("-");

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

int QueueContainsState(QueueState state, Queue queue)
{
	for (int i = queue.head; i < queue.tail - 1; i++) {
		if ((state.wolf == queue.stateList[i].wolf && state.sheep == queue.stateList[i].sheep &&
			state.cabbage == queue.stateList[i].cabbage && state.boat == queue.stateList[i].boat))
			return 1;
	}
	return 0;
}

void QueueGetMoves(Queue queue)
{
	while(1)
	{
		if (QueueLoseState(queue.stateList[queue.head])) {
			queue.head++;
			continue;
		}
			
		if (QueueWinState(queue.stateList[queue.head]))
		{
			QueuePrintState(queue.stateList[queue.head]);

			while (!QueueStartState(queue.stateList[queue.head]))
			{
				queue.head = queue.stateList[queue.head].prevState;
				QueuePrintState(queue.stateList[queue.head]);
			}
			return;
		}

		QueueCreateChildren(queue.stateList[queue.head], &queue);
		queue.head++;
	}
}

void main()
{
	//First part
	State startState = { 0 };

	for(int i = 0; !GetMoves(startState, i); i++)
		GetMoves(startState, i);
	printf("\n");

	//Second part
	Queue newQueue;
	newQueue.head = 0;
	QueueState queueStartState = { 0 };
	newQueue.stateList[0] = queueStartState;
	newQueue.tail = 1;
	newQueue.filled = 1;

	QueueGetMoves(newQueue);

	system("pause");
}