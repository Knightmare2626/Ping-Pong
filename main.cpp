#include "include/raylib.h"
// #include <iostream>
// #include <string>
using namespace std;

struct Ball
{
	float x, y;
	float xspeed, yspeed;
	float rad;
	void Draw()
	{
		DrawCircle(int (x), int (y), rad, WHITE);
	}
};


struct Paddles
{
	int speed;
	int x, y;
	int width, height;

	Rectangle GetRect()
	{
		return Rectangle { (float) x - width / 2, (float) y - height / 2, (float) width, (float) height };
	}

	void Draw()
	{
		DrawRectangleRec(GetRect(), WHITE);
	}
};


int main()
{


	InitWindow(800, 600, "Ping Pong");
    SetWindowState(FLAG_VSYNC_HINT);
	
	const char * WindowText = nullptr;

	Ball ball;
	ball.x = GetScreenWidth() / 2.0;
	ball.y = GetScreenHeight() / 2.0;
	ball.rad = 7;
	ball.xspeed = 200;
	ball.yspeed = 200;
	
	Paddles left;
	left.x = 50;
	left.y = GetScreenHeight() / 2 - 50;
	left.width = 10;
	left.height = 100;
	left.speed = 500;

	Paddles right;
	right.x = GetScreenWidth() - 50 - 10;
	right.y = GetScreenHeight() / 2 - 50;
	right.width = 10;
	right.height = 100;
	right.speed = 500;

	while (!WindowShouldClose())
	{
		ball.x += ball.xspeed * GetFrameTime();
		ball.y += ball.yspeed * GetFrameTime();


		
	
		if (ball.y > GetScreenHeight())
		{
			ball.y = GetScreenHeight();
			ball.yspeed *= -1;
		}
		if (ball.y < 0)
		{
			ball.y = 0;
			ball.yspeed *= -1; 
		}

		if (IsKeyDown(KEY_W))
		{
			left.y -= left.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_S))
		{
			left.y += left.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_UP))
		{
			right.y -= right.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_DOWN))
		{
			right.y += right.speed * GetFrameTime();
		}

		if (CheckCollisionCircleRec(Vector2 {ball.x, ball.y}, ball.rad, left.GetRect()))
		{
			ball.xspeed *= -1;
		}

		if (CheckCollisionCircleRec(Vector2 {ball.x, ball.y}, ball.rad, right.GetRect()))
		{
			if (ball.xspeed > 0) 
			{
				ball.xspeed *= -1;
			}
		}
		
		if (ball.x > GetScreenWidth())
		{
			WindowText = "Left Player Wins!  ";
		}
		if (ball.x < 0)
		{
			WindowText = "Right Player Wins!  ";
		}

		if (WindowText)
		{
			int textWidth = MeasureText(WindowText, 60);
			DrawText(WindowText, GetScreenWidth() - textWidth, GetScreenHeight() - textWidth, 60, YELLOW);
		}

		if (WindowText && IsKeyPressed(KEY_SPACE))
		{
			WindowText = nullptr;
			ball.x = GetScreenWidth() / 2.0;
			ball.y = GetScreenHeight() / 2.0;
			ball.xspeed = 200;
			ball.yspeed = 200;
		}


		BeginDrawing();
			ClearBackground(BLACK);
			ball.Draw();
			left.Draw();
			right.Draw();
        	DrawFPS(10, 10);
		EndDrawing();

	} 

	CloseWindow();
	return 0;
}
