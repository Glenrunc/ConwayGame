#include "conway.h"

CellsChained* AddCell(CellsChained* chained,CellsChained* newCell){
	
	CellsChained* temp = NULL;

	temp = chained;
	if(temp != NULL){
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newCell;
		newCell->next = NULL;
		newCell->previous = temp;
		return chained;
	}else{
		temp = newCell;
	}
	
	return temp;
}

void PrintGame(CellsChained* cells){

	CellsChained *temp = cells;

	while(temp != NULL){
		DrawRectangleRec(temp->cell,BLACK);
		temp = temp->next;
	}
}

// Will be use in 2 way. Verify dead cells and alive cells
int IsAlive(CellsChained *cells, Vector2 coordinate){
	
	CellsChained *temp = NULL;
	temp = cells;
	int i = 0;

	while(temp != NULL){
		if(((float)(coordinate.x*SIZE_CELL) == temp->cell.x) && ((float)(coordinate.y *SIZE_CELL)== temp->cell.y)) return i;
		temp = temp->next;
		i++;
	}

	return -1;
}

//WARNING: (float) Coordinate
Vector2 *GetCoordinateAroundCell(int x, int y){

	Vector2 *coordinate = (Vector2*)malloc(sizeof(Vector2)*8);

	coordinate[0] = (Vector2){x,(y+1.0f)};
	coordinate[1] = (Vector2){(x+1.0f),(y+1.0f)};
	coordinate[2] = (Vector2){(x+1.0f),(y)};
	coordinate[3] = (Vector2){(x+1.0f),(y-1.0f)};
	coordinate[4] = (Vector2){x,(y-1.0f)};
	coordinate[5] = (Vector2){(x-1.0f),(y-1.0f)};
	coordinate[6] = (Vector2){(x-1.0f),y};
	coordinate[7] = (Vector2){(x-1.0f),(y+1.0f)};

	return coordinate;
}


CellsChained *SuppCell(int x , int y, CellsChained *cells){

	int i = IsAlive(cells,(Vector2){x,y});

	if(i == 0){
		CellsChained *newCells = NULL;
		if(cells->next !=NULL){
			newCells = cells->next;
			newCells->previous = NULL;
		}

		free(cells);
		return newCells;
	}
	else if(i == -1)
	{
		return cells;
	}
	else
	{
		CellsChained *temp = cells;
		for(int n = 0; n<i;n++){
			temp= temp->next;
		}
		if(temp->next != NULL){
			temp->previous->next = temp->next;
			temp->next->previous = temp->previous;
		}else{
			temp->previous->next = NULL;
		}
		free(temp);

	}

	return cells;
}

bool IsIn(Vector2 *coordinate, int x,int y, int size){
	for (int i = 0; i<size; i++){
		if((int)(coordinate[i].x) == x && (int)(coordinate[i].y) == y) return true;
	}

	return false;
}

CellsChained *Iteration(CellsChained* cells){
	
	int sizeToBeDistroy = 0;
	Vector2 *toBeDistroy = NULL;
	int sizeToBeAdd = 0;
	Vector2 *toBeAdd = NULL;

	CellsChained *temp = cells;

	while(temp != NULL){

		int numberAlive = 0;
		
		Vector2 *getCellsAroundLiveCells = GetCoordinateAroundCell((int)(temp->cell.x/SIZE_CELL),(int)(temp->cell.y/SIZE_CELL));

		for(int i = 0 ; i<NUMBER_OF_CELLS_AROUND;i++){
			if(IsAlive(cells,(Vector2){(int)(getCellsAroundLiveCells[i].x),(int)(getCellsAroundLiveCells[i].y)}) != -1){
				numberAlive++;
			}else{
				int n = 0;
				Vector2 *getLiveCells = GetCoordinateAroundCell((int)(getCellsAroundLiveCells[i].x),(int)(getCellsAroundLiveCells[i].y));
				for (int j = 0 ; j<NUMBER_OF_CELLS_AROUND;j++){
					if(IsAlive(cells,(Vector2){(int)(getLiveCells[j].x),(int)(getLiveCells[j].y)}) != -1){
						n++;
					}
				}
				//toBeChange
				if(n == 3){
					if(toBeAdd != NULL){
						if(!IsIn(toBeAdd,(int)(getCellsAroundLiveCells[i].x),(int)(getCellsAroundLiveCells[i].y),sizeToBeAdd)){
							sizeToBeAdd++;
							toBeAdd = (Vector2*)realloc(toBeAdd,sizeToBeAdd*sizeof(Vector2));
							toBeAdd[sizeToBeAdd-1].x = getCellsAroundLiveCells[i].x;
							toBeAdd[sizeToBeAdd-1].y = getCellsAroundLiveCells[i].y;
						}
					}else{
						sizeToBeAdd++;
						toBeAdd = (Vector2*)realloc(toBeAdd,sizeToBeAdd*sizeof(Vector2));
						toBeAdd[sizeToBeAdd-1].x = getCellsAroundLiveCells[i].x;
						toBeAdd[sizeToBeAdd-1].y = getCellsAroundLiveCells[i].y;
					}
				}

				free(getLiveCells);
			}
		}

		//To change
		if(numberAlive<2 || numberAlive >3){
			if(toBeDistroy!=NULL){
				if(!IsIn(toBeDistroy,(int)(temp->cell.x/SIZE_CELL),(int)(temp->cell.y/SIZE_CELL),sizeToBeDistroy)){
					sizeToBeDistroy++;
					toBeDistroy = (Vector2*)realloc(toBeDistroy,sizeToBeDistroy*sizeof(Vector2));
					toBeDistroy[sizeToBeDistroy-1].x = temp->cell.x/SIZE_CELL;
					toBeDistroy[sizeToBeDistroy-1].y = temp->cell.y/SIZE_CELL;
				}
			}else{
				sizeToBeDistroy++;
				toBeDistroy = (Vector2*)realloc(toBeDistroy,sizeToBeDistroy*sizeof(Vector2));
				toBeDistroy[sizeToBeDistroy-1].x = temp->cell.x/SIZE_CELL;
				toBeDistroy[sizeToBeDistroy-1].y = temp->cell.y/SIZE_CELL;
			}
			
		}
		free(getCellsAroundLiveCells);
		temp = temp->next;
	}

	for(int i = 0 ; i<sizeToBeDistroy;i++){
		cells = SuppCell((int)(toBeDistroy[i].x),(int)(toBeDistroy[i].y),cells);
	}

	free(toBeDistroy);


	for(int i= 0; i<sizeToBeAdd;i++){
		CellsChained* newCell = (CellsChained*)malloc(sizeof(CellsChained)); 
		newCell->next = NULL;
		newCell->previous = NULL;
		newCell->cell = (Rectangle){toBeAdd[i].x*SIZE_CELL,toBeAdd[i].y*SIZE_CELL,SIZE_CELL,SIZE_CELL};

		AddCell(cells,newCell);
	}

	free(toBeAdd);

	return cells;

}


CellsChained* freeChained(CellsChained *chained){
	
	CellsChained *temp = chained;

	while(temp->next != NULL){
		temp =temp->next;
		free(temp->previous);
	}

	free(temp);
	return NULL;
}


int numberOfCell(CellsChained* cells){
	int i = 0;
	if (cells != NULL){
		CellsChained *temp = cells;

		while(temp != NULL){
			i++;
			temp = temp->next;
		}
	}

	return i;
}