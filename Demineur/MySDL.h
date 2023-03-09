#ifndef MY_SDL
#define MY_SDL

typedef struct Cell
{
	int num;
	int reveal;
	int flag;
} Cell;

void InitDemineurWindow();
void Drawn();

#endif // !MY_SDL
