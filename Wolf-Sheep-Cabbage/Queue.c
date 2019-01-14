#include "QueueHeader.h"

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
	if (currentGameState.wolf)
		printf("Wolf ");
	else
		printf("     ");
	if (currentGameState.sheep)
		printf("Sheep ");
	else
		printf("      ");
	if (currentGameState.cabbage)
		printf("Cabbage ");
	else
		printf("        ");
	if (currentGameState.boat)
		printf("Boat ");
	else
		printf("     ");

	printf("~~~~~~~~~~~~~~~~~~~~~~~ ");

	if (!currentGameState.wolf)
		printf("Wolf ");
	else
		printf("     ");
	if (!currentGameState.sheep)
		printf("Sheep ");
	else
		printf("      ");
	if (!currentGameState.cabbage)
		printf("Cabbage ");
	else
		printf("        ");
	if (!currentGameState.boat)
		printf("Boat ");
	else
		printf("     ");

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
	while (1)
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