#pragma once

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

void QueueCreateChildren(QueueState parentState, Queue *queue);

void QueuePrintState(QueueState currentGameState);

int QueueWinState(QueueState state);

int QueueLoseState(QueueState state);

int QueueStartState(QueueState state);

int QueueContainsState(QueueState state, Queue queue);

void QueueGetMoves(Queue queue);