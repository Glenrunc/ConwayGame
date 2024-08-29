#ifndef __CONWAY_H__
#define __CONWAY_H__

#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 800
#define SIZE_CELL 10.0f
#define NUMBER_OF_CELLS_AROUND 8

typedef struct Cells {

	Rectangle cell;
	struct Cells *next;
	struct Cells *previous;

} CellsChained;

void AddCell(CellsChained* newCell,CellsChained* Cells);

void PrintGame(CellsChained* cells);

int IsAlive(CellsChained *cells, Vector2 coordinate);

Vector2 *GetCoordinateAroundCell(int x, int y);

CellsChained *SuppCell(int x , int y, CellsChained *cells);

CellsChained *Iteration(CellsChained* cells);

void freeChained(CellsChained *chained);

bool IsIn(Vector2 *coordinate, int x,int y, int size);

#endif