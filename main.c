#include "conway.h"

int main(){

	CellsChained *chained = NULL;

	InitWindow(WIDTH,HEIGHT,"Game Of Life");

	Camera2D camera = { 0 };

	camera.offset = (Vector2){0.0f,0.0f};
	camera.target = (Vector2){0.0f,0.0f};
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	bool isRunning = false;
	char  str[100];
	Vector2 mouseDelta = (Vector2){1.0f,1.0f};	
	
	SetTargetFPS(60);
	while(!WindowShouldClose()){
		sprintf(str,"%d",numberOfCell(chained));
		DrawText(str,750,10,20,BLACK);

		// chained = Iteration(chained);
		DrawText("Conway's Game\nLeft click to draw cell\nR to run\nS to stop\nC to clean", 10, 10, 20, BLACK);

		if(isRunning){
			chained = Iteration(chained);
		}

		if( IsKeyPressed(KEY_R)){
			isRunning = true;
		}
		if(IsKeyPressed(KEY_C)){
			if(chained != NULL){
				chained = freeChained(chained);
			}
		}
		if(IsKeyPressed(KEY_S)){
			isRunning = false;
		}

		if(chained == NULL){
			isRunning = false;
		}
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
			Vector2 position = GetMousePosition();
			int isAlive  = IsAlive(chained,(Vector2){(int)(position.x/SIZE_CELL-mouseDelta.x/SIZE_CELL),(int)(position.y/SIZE_CELL-mouseDelta.y/SIZE_CELL)});
			if(isAlive==-1){
				CellsChained *newCell = NULL;
				newCell = (CellsChained*)malloc(sizeof(CellsChained));
				newCell->cell = (Rectangle){(int)(position.x/SIZE_CELL-mouseDelta.x/SIZE_CELL)*SIZE_CELL,(int)(position.y/SIZE_CELL-mouseDelta.y/SIZE_CELL)*SIZE_CELL,SIZE_CELL,SIZE_CELL};
				newCell->next = NULL;
				newCell->previous = NULL;
				chained = AddCell(chained,newCell);
			}
        }

		// if(abs(GetMouseWheelMove())){
		// 	camera.zoom += ((float)GetMouseWheelMove()*0.25f);
		// }

        if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)){
			Vector2 delta = GetMouseDelta();
            camera.offset = Vector2Add(camera.offset, delta);
			mouseDelta = Vector2Add(mouseDelta,delta);
		}

		// if(abs(GetMouseWheelMove())){
		// 	camera.zoom += ((float)GetMouseWheelMove()*0.25f);
		// }

		if(camera.zoom<0.25f) camera.zoom = 0.25f;
		else if(camera.zoom >20.0f) camera.zoom =20.0f;

		BeginDrawing();
			ClearBackground(RAYWHITE);
			BeginMode2D(camera);
				PrintGame(chained);
			EndMode2D();

		EndDrawing();
	}
	
	CloseWindow();

	if(chained != NULL){
		freeChained(chained);
	}


	return 0;
}
