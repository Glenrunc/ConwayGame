#include "conway.h"

int main(){

	CellsChained *chained = NULL;

	chained = (CellsChained*)malloc(sizeof(CellsChained));

	(*chained).cell = (Rectangle){0.0f,0.0f,SIZE_CELL,SIZE_CELL};
	chained->next = NULL;
	chained->previous = NULL;

	CellsChained *test0 = NULL;

	test0 = (CellsChained*)malloc(sizeof(CellsChained));
	(*test0).cell = (Rectangle){0.0f+SIZE_CELL,0.0f+SIZE_CELL,SIZE_CELL,SIZE_CELL};
	test0->next = NULL;
	test0->previous = NULL;

	CellsChained *test1 = NULL;

	test1 = (CellsChained*)malloc(sizeof(CellsChained));
	(*test1).cell = (Rectangle){0.0f+SIZE_CELL*2,0.0f+SIZE_CELL,SIZE_CELL,SIZE_CELL};
	test1->next = NULL;
	test1->previous = NULL;

	CellsChained *test2 = NULL;

	test2 = (CellsChained*)malloc(sizeof(CellsChained));
	(*test2).cell = (Rectangle){0.0f+SIZE_CELL*2,0.0f,SIZE_CELL,SIZE_CELL};
	test2->next = NULL;
	test2->previous = NULL;

	CellsChained *test3 = NULL;

	test3 = (CellsChained*)malloc(sizeof(CellsChained));
	(*test3).cell = (Rectangle){0.0f+SIZE_CELL*2,0.0f+SIZE_CELL*(-1),SIZE_CELL,SIZE_CELL};
	test3->next = NULL;
	test3->previous = NULL;

	CellsChained *test4 = NULL;

	test4 = (CellsChained*)malloc(sizeof(CellsChained));
	(*test4).cell = (Rectangle){0.0f+SIZE_CELL*6,0.0f+SIZE_CELL*1,SIZE_CELL,SIZE_CELL};
	test4->next = NULL;
	test4->previous = NULL;

	CellsChained *test5 = NULL;

	test5 = (CellsChained*)malloc(sizeof(CellsChained));
	(*test5).cell = (Rectangle){0.0f+SIZE_CELL*6,0.0f+SIZE_CELL*2,SIZE_CELL,SIZE_CELL};
	test5->next = NULL;
	test5->previous = NULL;

	CellsChained *test6 = NULL;

	test6 = (CellsChained*)malloc(sizeof(CellsChained));
	(*test6).cell = (Rectangle){0.0f+SIZE_CELL*6,0.0f+SIZE_CELL*3,SIZE_CELL,SIZE_CELL};
	test6->next = NULL;
	test6->previous = NULL;

	AddCell(chained,test0);
	AddCell(chained,test1);
	AddCell(chained,test2);
	AddCell(chained,test3);
	AddCell(chained,test4);
	AddCell(chained,test5);
	AddCell(chained,test6);



	InitWindow(WIDTH,HEIGHT,"Game Of Life");

	Camera2D camera = { 0 };

	camera.offset = (Vector2){0.0f+350.0f,0.0f+350.0f};
	camera.target = (Vector2){0.0f,0.0f};
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	SetTargetFPS(60);
	while(!WindowShouldClose()){

		if(IsKeyDown(KEY_RIGHT)){
			chained = Iteration(chained);
			// player.x += 1.0f;
		}

		if(IsKeyDown(KEY_LEFT)){
			camera.offset.y -= 1.0f;
			// player.x -= 1.0f;

		}

		camera.zoom += ((float)GetMouseWheelMove()*0.25f);

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
