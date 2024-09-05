#ifndef __CONWAY_H__
#define __CONWAY_H__

#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <rlgl.h>
#include <raymath.h>

#define WIDTH 800
#define HEIGHT 800
#define SIZE_CELL 10.0f
#define NUMBER_OF_CELLS_AROUND 8

/**
 * @brief This structure has a Rectangle (Raylib structure)
 * compose of 4 parameters(pos X, pos Y ,size X, size Y)
 * 
 */
typedef struct Cells {

	Rectangle cell;
	struct Cells *next;
	struct Cells *previous;

} CellsChained;

/**
 * @brief Add a cell into a linked list of cell
 * 
 * @param newCell Struct Cell pointer
 * @param Cells Linked list of cells
 * @return CellsChained
 */
CellsChained* AddCell(CellsChained* newCell,CellsChained* Cells);

/**
 * @brief print the using Raylib utilies
 * 
 * @param cells Linked list of cells
 */
void PrintGame(CellsChained* cells);
/**
 * @brief Check if a cell is alive
 * 
 * @param cells Linked list of cells
 * @param coordinate vector of to float coordinate
 * @return int 
 */
int IsAlive(CellsChained *cells, Vector2 coordinate);
/**
 * @brief Get the Coordinate Around Cell object
 * 
 * @param x 
 * @param y 
 * @return Vector2*  is an array of coordinate
 */
Vector2 *GetCoordinateAroundCell(int x, int y);
/**
 * @brief Supp cell into a linked list
 * 
 * @param x 
 * @param y 
 * @param cells Linked list of cells
 * @return CellsChained* 
 */
CellsChained *SuppCell(int x , int y, CellsChained *cells);
/**
 * @brief Algorithm for one step
 * 
 * @param cells Linked list of cells
 * @return CellsChained* 
 */
CellsChained *Iteration(CellsChained* cells);
/**
 * @brief Free memory
 * 
 * @param chained 
 */
CellsChained* freeChained(CellsChained *chained);
/**
 * @brief use for no redondant information when using the two list into Iteration()
 * 
 * @param coordinate 
 * @param x 
 * @param y 
 * @param size 
 * @return true 
 * @return false 
 */
bool IsIn(Vector2 *coordinate, int x,int y, int size);
/**
 * @brief Count the number of cells
 * 
 * @param cells 
 * @return int 
 */
int numberOfCell(CellsChained* cells);
#endif