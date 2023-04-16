#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAZE_SIZE 10
#define MAX_SIZE 400
typedef struct {
	short r;
	short c;
}element;
typedef struct {
	element data[MAX_SIZE];
	int top;
}stacktype;

void init_stack(stacktype* s)
{
	// s가 가르키는 stacktype구조체의 탑의 값을 -1로 지정한다.
	s->top = -1;
}

int is_empty(stacktype* s)
{
	return (s->top == -1);
}
int is_full(stacktype* s)
{
	return (s->top == (MAX_SIZE - 1));
}
void push(stacktype* s, element item)
{
	if (is_full(s))
	{
		fprintf(stderr, "Stack Full!\n");
		return;
	}
	else
	{
		s->data[++s->top] = item;
	}
}
element pop(stacktype* s)
{
	if (is_empty(s))
	{

		exit(1);
	}
	else return s->data[(s->top)--];
}
element peek(stacktype* s)
{
	return s->data[s->top];
}
element here = { 1,0 }, entry = { 1,0 };
char maze[MAZE_SIZE][MAZE_SIZE] = {
		{'1','1','1','1','1','1','1','1','1','1'},
		{'e','1','0','1','0','0','0','1','0','1'},
		{'0','0','0','1','0','0','0','1','0','1'},
		{'0','1','0','0','0','1','1','0','0','1'},
		{'1','0','0','0','1','0','0','0','0','1'},
		{'1','0','0','0','1','0','0','0','0','1'},
		{'1','0','0','0','0','0','1','0','1','1'},
		{'1','0','1','1','1','0','1','1','0','1'},
		{'1','1','0','0','0','0','0','0','0','x'},
		{'1','1','1','1','1','1','1','1','1','1'}
};

int push_loc(stacktype* s, int r, int c) {
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
		return 1;
	}
	return 0;
}

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
	printf("\n");
	for (int r = 0; r < MAZE_SIZE; r++)
	{
		for (int c = 0; c < MAZE_SIZE; c++)
		{
			printf("%c", maze[r][c]);
		}
		printf("\n");
	}
}
int main(void)
{
	int count = 0;
	int path = 0;
	int r, c;
	stacktype s;
	init_stack(&s);
	here = entry;
	while (maze[here.r][here.c] != 'x')
	{
		r = here.r;
		c = here.c;
		maze[r][c] = '.';
		maze_print(maze);

		path = push_loc(&s, r - 1, c);

		path +=push_loc(&s, r + 1, c);

		path +=push_loc(&s, r, c - 1);

		path +=push_loc(&s, r, c + 1);
		if (path == 0)
			count++;
		if (is_empty(&s))
		{
			printf("실패\n");
			return;
		}
		else
		{
			here = pop(&s);
		}
	}
	printf("success!\n");
	printf("%d", count);// 제일 처음 push함수를 사용하면서 peek 
	return 0;
}