#include "raylib.h"

struct Ball {
	float x, y;
	float speedx, speedy;
	float radius;

	void Draw() {
		DrawCircle((int)x, (int)y, radius, WHITE);
	}

	void CheckBorders() {
		if (y < 0) {
			y = 0;
			speedy *= -1;
		}
		if (y > GetScreenHeight()) {
			y = (float)GetScreenHeight();
			speedy *= -1;
		}
	}

};

struct Paddle {
	float x, y;
	float speed;
	float width, height;

	Rectangle GetRect() {
		return Rectangle{x, y, width, height};
	}

	void Draw() {
		DrawRectangleRec(GetRect(), WHITE);
		DrawRectangleRec(GetRect(), WHITE);
	}

	void CheckLeft() {
		if (IsKeyDown(KEY_W)) {
			y -= speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_S)) {
			y += speed * GetFrameTime();
		}
	}

	void CheckRight() {
		if (IsKeyDown(KEY_UP)) {
			y -= speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_DOWN)) {
			y += speed * GetFrameTime();
		}
	}

};

struct Counter {
	float x, y;
	float fontSize;
	int count;
};

int main()
{
	int width = 800, height = 700;
	InitWindow(width, height, "Pong");
	SetWindowState(FLAG_VSYNC_HINT);

	Ball ball;
	ball.x = width / 2.0f;
	ball.y = height / 2.0f;
	ball.radius = 5.0f;
	ball.speedx = 200.0f;
	ball.speedy = 300.0f;

	Paddle leftPaddle;
	leftPaddle.x = 20;
	leftPaddle.y = (float)height / 2 - 50;
	leftPaddle.width = 10;
	leftPaddle.height = 100.0f;
	leftPaddle.speed = 700.0f;

	Paddle rightPaddle;
	rightPaddle.x = (float)width - 20;
	rightPaddle.y = (float)height / 2 - 50;
	rightPaddle.width = 10;
	rightPaddle.height = 100;
	rightPaddle.speed = 700.0f;

	Counter counterLeft;
	counterLeft.x = GetScreenWidth() - 50.0f;
	counterLeft.y = 10;
	counterLeft.fontSize = 10;
	counterLeft.count = 0;
	Counter counterRight;
	counterRight.x = GetScreenWidth() + 50.0f;
	counterRight.fontSize = 10;
	counterRight.count = 0;

	const char* winnerText = nullptr;
	
	while (!WindowShouldClose())
	{
		ball.x += ball.speedx * GetFrameTime();
		ball.y += ball.speedy * GetFrameTime();
		
		ball.CheckBorders();

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, leftPaddle.GetRect())) {
			if (ball.speedx < 0) {
				ball.speedx *= -1.1f;
				ball.speedy = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedx;
				counterLeft.count += 1;
			}
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightPaddle.GetRect())) {
			if (ball.speedx > 0) {
				ball.speedx *= -1.1f;
				ball.speedy = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * ball.speedx;
				counterRight.count += 1;
			}
		}

		if (ball.x < 0) {
			winnerText = "Marjvena Motamashem Moigo!";
		}
		if (ball.x > GetScreenWidth()) {
			winnerText = "Marcxena Motamashem Moigo";
		}
		if (winnerText && IsKeyPressed(KEY_SPACE)) {
			ball.x = (float)GetScreenWidth() / 2;
			ball.y = (float)GetScreenHeight() / 2;
			ball.speedx = 300;
			ball.speedy = 300;
			winnerText = nullptr;
			counterLeft.count = 0;
			counterRight.count = 0;
		}
		BeginDrawing();
			ClearBackground(BLACK);	
			
			ball.Draw();

			leftPaddle.Draw();
			leftPaddle.CheckLeft();
			rightPaddle.Draw();
			rightPaddle.CheckRight();

			if (winnerText) {
				DrawText(winnerText, 200, GetScreenHeight() / 2 - 30, 30, WHITE);
			}
			if (counterLeft.count) {
				DrawText(TextFormat("%i", counterLeft.count), GetScreenWidth() / 2 - 50.0f, 20.0f, 30, GREEN);
			}
			if (counterRight.count) {
				DrawText(TextFormat("%i", counterRight.count), GetScreenWidth() / 2 + 40.0f, 20.0f, 30, RED);
			}
			DrawLine(GetScreenWidth()/2, 0, GetScreenWidth() / 2, GetScreenHeight(), WHITE);
			DrawFPS(0,0);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}