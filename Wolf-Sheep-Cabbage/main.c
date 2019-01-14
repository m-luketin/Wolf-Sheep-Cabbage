#include <stdio.h>
#include <stdlib.h>
#include "RecursionHeader.h"
#include "QueueHeader.h"

void main()
{
	//Recursion
	State startState = { 0 };
	printf("                               Recursion\n");

	for(int i = 0; !GetMoves(startState, i); i++)
		GetMoves(startState, i);
	printf("\n");

	//Queue
	Queue newQueue;
	newQueue.head = 0;
	QueueState queueStartState = { 0 };
	newQueue.stateList[0] = queueStartState;
	newQueue.tail = 1;
	newQueue.filled = 1;

	printf("                                 Queue\n");
	QueueGetMoves(newQueue);

	system("pause");
}