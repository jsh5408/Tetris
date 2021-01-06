#include <stdio.h>
#include <Windows.h>
#include <math.h>
#include <time.h>
#include <conio.h>
 
#define UP 72
#define LEFT 75
#define RIGHT 77
#define UP 72
#define SPACE 32
 
#define GBOARD_HEIGHT 20
#define GBOARD_WIDTH 10
 
int gameBoardInfo[GBOARD_HEIGHT+1][GBOARD_WIDTH+2]; 
int Speed;
COORD curPos;
int block_id;
int score=0;
 
char blockModel[][4][4] =	
{
 
    {
        {0, 0, 0, 0}, 
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0} },   
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0} },    
    {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0} },    
    {
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0} },
 
 
    {
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0} },   
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0} },    
    {
        {0, 0, 0, 0},
        {0, 1, 1, 1},
        {0, 1, 0, 0},
        {0, 0, 0, 0} },    
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0} },
 
 
    {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0} },   
    {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 0, 0} },    
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 1, 0, 0} },    
    {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0} },
 
 
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0} },   
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0} },    
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0} },    
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0} },
 
 
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0} },   
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0} },    
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0} },    
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0} },
 
 
 
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0} },   
    {
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0} },    
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0} },   
    {
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0} },  
 
 
    {
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0} },   
    {
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0} }, 
    {   
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0} },   
    {
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0} }
};
///////////////////////////////////////////////////////////////////////////////
void RemoveCursor(void)	//Ŀ�� ������ ����
{
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&curInfo);
    curInfo.bVisible=0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&curInfo);
}
 
void SetCurrentCursorPos(int x, int y) //Ŀ��������set
{
    COORD pos={x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}
 
COORD GetCurrentCursorPos(void) //Ŀ��������get
{
	 COORD curPoint;
     CONSOLE_SCREEN_BUFFER_INFO curInfo;
     GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
     curPoint.X=curInfo.dwCursorPosition.X;
     curPoint.Y=curInfo.dwCursorPosition.Y;
	 
	 return curPoint;
}
//////////////////////////////////////////////////////////////////////////////////
void ShowBlock(char blockInfo[4][4]) //��� �����ֱ�
{
    int x,y;
    curPos=GetCurrentCursorPos();
    for(y=0; y<4; y++)
    {
        for(x=0; x<4; x++)
        {
            SetCurrentCursorPos(curPos.X + (x*2), curPos.Y + y);
          
            if(blockInfo[y][x] == 1)
                printf("��");
        }
    }
    SetCurrentCursorPos(curPos.X, curPos.Y);
}
 
void DeleteBlock(char(*blockInfo)[4]) //��� ���ֱ�
{
	int x, y;
	curPos = GetCurrentCursorPos();
 
    for (y = 0; y < 4; y++)
    {
        for (x = 0; x < 4; x++)
        {
            SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);    
            if (blockInfo[y][x] == 1)
            {
                fputs("  ", stdout);
            }
        }
    }
	
    SetCurrentCursorPos(curPos.X, curPos.Y);
}
////////////////////////////////////////////////////////////////////////////////
int BlockDown() //��� �������� �ϴ°�
{
	if(!DetectCollision(curPos.X, curPos.Y+1, blockModel[block_id]))
	{
		return 0;
	}
 
	DeleteBlock(blockModel[block_id]);
	curPos.Y+=1;
	SetCurrentCursorPos(curPos.X,curPos.Y);
	ShowBlock(blockModel[block_id]);
 
	return 1;
}
 
void ShiftLeft() // �������̵�
{
	if(DetectCollision(curPos.X-2, curPos.Y, blockModel[block_id])==0)
	{
		return;
	}
	DeleteBlock(blockModel[block_id]);
	curPos.X-=2;
	SetCurrentCursorPos(curPos.X,curPos.Y);
	ShowBlock(blockModel[block_id]);
}
 
void ShiftRight() //�������̵�
{
	if(DetectCollision(curPos.X+2, curPos.Y, blockModel[block_id])==0)
	{
		return;
	}
	DeleteBlock(blockModel[block_id]);
	curPos.X+=2;
	SetCurrentCursorPos(curPos.X,curPos.Y);
	ShowBlock(blockModel[block_id]);
}
 
void RotateBlock() //��� �����°�
{
	int block_base = block_id-block_id%4;
	int block_rotated = block_base+(block_id+1)%4;
	if(DetectCollision(curPos.X, curPos.Y, blockModel[block_rotated])==0)
	{
		return;
	}
	DeleteBlock(blockModel[block_id]);
	block_id=block_base+(block_id+1)%4;
	SetCurrentCursorPos(curPos.X,curPos.Y);
 
	ShowBlock(blockModel[block_id]);
}
 
void SpaceDown() //�����̽� Ű ������ �ѹ��� �������°�
{
	while(BlockDown());
}
///////////////////////////////////////////////////////////////////////////////
void ProcessKeyInput()
{
	int key,i;
	for(i=0;i<20;i++)
		{
			if(_kbhit()!=0) //Ű���� �Է��� �߻��ϸ� 1 ��ȯ �Լ�
			{
				key = _getch();//�Էµ� Ű ���� �ƽ�Ű�ڵ� ��ȯ
				switch(key)
				{
				 case RIGHT:
					 ShiftRight();
					 break;
				 case LEFT:
					 ShiftLeft();
					 break;
		         case UP:
		             RotateBlock();
				     break;
				 case SPACE:
					 SpaceDown();
					 break;
				 default:
					 break;
				}
			}
			Sleep(Speed); //���̵�
		}
}
///////////////////////////////////////////////////////////////////////////////
void drawBoard() //������ �׸��°�
{
	int x,y;
 
	for(y=0;y<GBOARD_HEIGHT;y++)
	{
		gameBoardInfo[y][0] = 1;
		gameBoardInfo[y][GBOARD_WIDTH+1] = 1;
	}
 
	for(x=0;x<GBOARD_WIDTH+2;x++)
	{
		gameBoardInfo[GBOARD_HEIGHT][x] = 1;
	}
 
	for(y=0;y<=GBOARD_HEIGHT;y++)
	{
		SetCurrentCursorPos(0,y);
		if(y==GBOARD_HEIGHT)
		{
			printf("��");
		}
		else
		{
			printf("��");
		}
	}
	for(y=0;y<=GBOARD_HEIGHT;y++)
	{
		SetCurrentCursorPos(22,y);
		if(y==GBOARD_HEIGHT)
		{
			printf("��");
		}
		else
		{
			printf("��");
		}
	}
	for(x=2;x<=20;x+=2)
	{
		SetCurrentCursorPos(x,20);
		printf("��");
	}
}
/*
void DrawGameBoard()
{
   int y, x;

   for (y=0; y<=GBOARD_HEIGHT; y++)
   {
      SetCurrentCursorPos(0, y);
      if (y==GBOARD_HEIGHT)
         printf("��");
      else
         printf("��");
   }
   for (y=0; y<=GBOARD_HEIGHT; y++)
   {
      SetCurrentCursorPos((GBOARD_WIDTH+1)*2, y);
      if (y==GBOARD_HEIGHT)
         printf("��");
      else
         printf("��");
   }
   for (x=1; x<GBOARD_WIDTH+1; x++)
   {
      SetCurrentCursorPos(x*2, GBOARD_HEIGHT);
      printf("��");
   }

   for (y=0; y<GBOARD_HEIGHT; y++)
   {
      gameBoardInfo[y][0]=1;
      gameBoardInfo[y][GBOARD_WIDTH+1]=1;
   }
   for (x=0; x<GBOARD_WIDTH+2; x++)
   {
      gameBoardInfo[GBOARD_HEIGHT][x]=1;
   }
}
�̰ų�
void DrawGameBoard(void)
{
    int x, y;
       ������ �κ� ó�� 
    for(y=0; y<GBOARD_HEIGHT; y++){
        gameBoardInfo[y][0]=1;
  gameBoardInfo[y][GBOARD_WIDTH+1]=1;
             
    }
     for(x=0; x<GBOARD_WIDTH+2; x++){
        gameBoardInfo[GBOARD_HEIGHT][x]=1;
    }
     �ð� �κ� ó�� 
  for(y=0; y<=GBOARD_HEIGHT; y++){
    for(x=0; x<GBOARD_WIDTH+2; x++){
      if(gameBoardInfo[y][x] == 1){
        SetCurrentCursorPos(x*2,y);
        printf("��");
  }           
  }
  }
}*/
///////////////////////////////////////////////////////////////////////////////
// 0: �浹
/*�ܼ��� ��ǥ posX, posY
  ����� ��ǥ arrX, arrY
  �� ��� ������� ���� ���
  posX,posY
        10,2 11,2
8,3 9,3 10,3 11,3 12,3 13,3
  arrX,arrY
      5,2
  4,3 5,3 6,3
 �ܼ��� ��ǥ�� �迭�� �ε��� 
 (x,y)=a[y][x];
 */
int DetectCollision(int posX, int posY, char blockModel[4][4]) //�浹 �˻��ϱ�
{
	int x, y;
	int arrX = posX/2;
	int arrY = posY;
	for(x=0;x<4;x++)
	{
		for(y=0;y<4;y++)
		{
			if(gameBoardInfo[arrY+y][arrX+x]==1 && blockModel[y][x]==1)
			{
				return 0;
			}
		}
	}
 
	return 1;
}
void AddBlockToBoard(void) //����� �ڸ��� ����� �� gameBoardInfo�� ������Ʈ ���ִ� ����
{
    int x, y, arrCurX, arrCurY;
    for(y=0; y<4; y++)
    {
        for(x=0; x<4; x++)
        {
            /* Convert X,Y coordinate to array index */
            arrCurX=curPos.X/2;
            arrCurY=curPos.Y;
            if(blockModel[block_id][y][x]==1)
                gameBoardInfo[arrCurY+y][arrCurX+x]=1;
        }
    }
}
int IsGameOver() //���ӿ���
{
	if(DetectCollision(curPos.X, curPos.Y, blockModel[block_id])==0)
	{
		return 1;
	}
 
	return 0;
}
 
void RedrawBlocks(void) //�� �� ����� �� �� ��� �ٽ� �׷��ֱ�
{   int x, y;
    int cursX, cursY;
    for(y=0; y<GBOARD_HEIGHT; y++)
    {   for(x=1; x<GBOARD_WIDTH+1; x++)
        {   cursX= x*2;
            cursY= y;
            SetCurrentCursorPos(cursX, cursY);
            if(gameBoardInfo[y][x]==1)
            {  printf("��");
            }
            else {  printf("  ");    }
        }
    }
}
 
void DrawScore()
{
	SetCurrentCursorPos(50, 10);
	printf("Score: %d", score);
	
	if(score>50)
	{
		Speed--;
	}
}
 
void RemoveFillUpLine()
{
	int line, x, y;
 
	for(y=GBOARD_HEIGHT-1;y>0;y--)
	{
		for(x=1; x<GBOARD_WIDTH+1; x++)
		{
			if(gameBoardInfo[y][x] != 1)
			{
				break;
			}
		}
		if(x==(GBOARD_WIDTH+1))
		{
			for(line = 0;y-line>0;line++)	//0�������� 1�����ο� ��������
			{
				memcpy(&gameBoardInfo[y-line][1],&gameBoardInfo[(y-line)-1][1],GBOARD_WIDTH*sizeof(int));
			}
			//y = line+1;
			y++;
			score += 10;
		}
	}
	RedrawBlocks();
}
///////////////////////////////////////////////////////////////////////////////
void ReverseRotateBlock()
{
	int block_base;
 
	DeleteBlock(blockModel[block_id]);
 
	block_base = block_id-block_id%4;
	block_id=block_base+(block_id+3)%4;
 
	ShowBlock(blockModel[block_id]);
}
 
void Q_output()
{	
	DeleteBlock(blockModel[block_id]);
	curPos.X-=2;
	curPos.Y-=1;
	SetCurrentCursorPos(curPos.X,curPos.Y);
	ShowBlock(blockModel[block_id]);
}
 
void E_output()
{	
	DeleteBlock(blockModel[block_id]);
	curPos.X+=2;
	curPos.Y-=1;
	SetCurrentCursorPos(curPos.X,curPos.Y);
	ShowBlock(blockModel[block_id]);
}
 
void Z_output()
{	
	DeleteBlock(blockModel[block_id]);
	curPos.X-=2;
	curPos.Y+=1;
	SetCurrentCursorPos(curPos.X,curPos.Y);
	ShowBlock(blockModel[block_id]);
}
 
void C_output()
{	
	DeleteBlock(blockModel[block_id]);
	curPos.X+=2;
	curPos.Y+=1;
	SetCurrentCursorPos(curPos.X,curPos.Y);
	ShowBlock(blockModel[block_id]);
}
 
void W_output()
{	
	DeleteBlock(blockModel[block_id]);
	curPos.Y-=1;
	SetCurrentCursorPos(curPos.X,curPos.Y);
	ShowBlock(blockModel[block_id]);
}

void DrawGameBoard(void)
{
    int x, y;
      /* ������ �κ� ó�� */
    for(y=0; y<GBOARD_HEIGHT; y++){
        gameBoardInfo[y][0]=1;
  gameBoardInfo[y][GBOARD_WIDTH+1]=1;
             
    }
     for(x=0; x<GBOARD_WIDTH+2; x++){
        gameBoardInfo[GBOARD_HEIGHT][x]=1;
    }
    /* �ð� �κ� ó�� */
  for(y=0; y<=GBOARD_HEIGHT; y++){
    for(x=0; x<GBOARD_WIDTH+2; x++){
      if(gameBoardInfo[y][x] == 1){
        SetCurrentCursorPos(x*2,y);
        printf("��");
  }           
  }
  }
}
int main()
{
	RemoveCursor();
	drawBoard();
	//score = 0;
 
	while(1)
	{
		DrawScore();
		srand((unsigned int)time(NULL));
		block_id = (rand()%7)*4;
		//���Ӻ���� ��ȣ�� 0,4,8,12,16,20
		//block_id = 16;
		//��ϸ��� 28�� rand%28
		Speed = 25;
		curPos.X=8;
		curPos.Y=0;
		SetCurrentCursorPos(curPos.X, curPos.Y);
 
		if(IsGameOver()==1)
		{
			break;
		}
 
		while(1)
		{
			if(BlockDown()==0)
			{
				AddBlockToBoard();
				RemoveFillUpLine();
				break;	
			}
			ProcessKeyInput();
		}
	
	}
	SetCurrentCursorPos(8,2);
	puts("Game Over!!");
	getchar();
 
	return 0;
}
/* x,yĿ�� ��ġ�� ��ġ�����
int main(void)
{      
	int i; 
	COORD curPos;  
	for(i=0;i<20;i++)  
	{   
		SetCurrentCursorPos(abs(20-2*i)),i);       
		curPos=GetCurrentCursorPos();  
		printf("[%d, %d]", curPos.X,curPos.Y);  
	} 
	getchar();  
	return 0; 
}
*/
/*
int main(void) 
{ 
	int i; 
	int block_id;  
	srand(time());  
	block_id=(rand()%7)*4; 
	for(i=0;i<20;i++)
	{
		ShowBlock(blockModel[block_id+(i%4)]); 
		Sleep(200);
		DeleteBlock(blockModel[block_id+(i%4)]); 
		curPosY+=1;   
		SetCurrentCursorPos(curPosX, curPosY); 
	}  
	getchar();   
	return 0; 
} 
*/
/* ��� ȸ���ϸ鼭 �������°�
int main()
{
	int i,block_id;
	COORD curPos= GetCurrentCursorPos();
	srand((unsigned int)time(NULL));
	block_id= (rand()%7)*4; //0,4,8,12...24
	//���� ��ϸ�rand()%7*4
 
	curPos.X = rand()%40;
	curPos.Y = rand()%20;
 
	for(i=0;i<100;i++)
	{
		SetCurrentCursorPos(curPos.X,curPos.Y);
		ShowBlock(blockModel[block_id+3-(i+3)%4]);
		Sleep(500);
		DeleteBlock(blockModel[block_id+3-(i+3)%4]);
		curPos.Y+=1;
	}
}
int main() //���̾Ƹ�彺������
{
	int x,y;
	COORD curPos =  GetCurrentCursorPos();
	curPos.X+=20;
	SetCurrentCursorPos(curPos.X,curPos.Y);
	
	for(y=0;y<10;y++)
	{	
	ShowBlock(blockModel[8]);
	Sleep(100);
	DeleteBlock(blockModel[8]);
	SetCurrentCursorPos(2*curPos.Y+20, abs(y));
	curPos.Y+=1;
	}
 
	for(y=10;y<20;y++)
	{	
	ShowBlock(blockModel[8]);
	Sleep(100);
	DeleteBlock(blockModel[8]);
	SetCurrentCursorPos(-2*curPos.Y+60, abs(y));
	curPos.Y+=1;
	}
 
	for(y=20;y>10;y--)
	{	
	ShowBlock(blockModel[8]);
	Sleep(100);
	DeleteBlock(blockModel[8]);
	SetCurrentCursorPos(2*curPos.Y-20, abs(y));
	curPos.Y-=1;
	}
 
	for(y=10;y>0;y--)
	{	
	ShowBlock(blockModel[8]);
	Sleep(100);
	DeleteBlock(blockModel[8]);
	SetCurrentCursorPos(-2*curPos.Y+20, abs(y));
	curPos.Y-=1;
	}

	/
	for(i = 0 ; i < 20; i ++) { SetCurrentCursorPos(abs(20 - (2*i)),i); printf("��"); }
	/
 
 
	getchar();
	
	return 0;
}
*/

/* >������� ��ǥ���/�ȳ��ϼ��� 2��
int main(void)
{
	int i, j,  y;
  float x;
  CONSOLE_SCREEN_BUFFER_INFO curInfo;       // structure included in windows.h
 
  HANDLE console;
  console=GetStdHandle(STD_OUTPUT_HANDLE);
 
  for(i=0;i<7;i++)
  {
	 x = - abs((float)(i-3)) + 3;
	 //GetConsoleScreenBufferInfo(console, &curInfo);
	// curInfo.dwCursorPosition.X = x;
	 //curInfo.dwCursorPosition.Y = i;
	 for(j=0;j<x;j++)
	 {
		 printf(" ");
	 }
	 printf("[%d, %d] \n", x, i);
  }
 
  /*
  GetConsoleScreenBufferInfo(console, &curInfo);
  printf("[%d, %d] \n", curInfo.dwCursorPosition.X, curInfo.dwCursorPosition.Y);
  printf("ù��° �ȳ��ϼ���");
   
  GetConsoleScreenBufferInfo(console, &curInfo);
  printf("[%d, %d] \n", curInfo.dwCursorPosition.X, curInfo.dwCursorPosition.Y);
  puts("�ι�° �ȳ��ϼ���");
   
 
  getchar();
  return 0;
}*/

/*

void DrawGameBoard(void)
{
    int x, y;
      / ������ �κ� ó�� /
    for(y=0; y<GBOARD_HEIGHT; y++){
        gameBoardInfo[y][0]=1;
  gameBoardInfo[y][GBOARD_WIDTH+1]=1;
             
    }
     for(x=0; x<GBOARD_WIDTH+2; x++){
        gameBoardInfo[GBOARD_HEIGHT][x]=1;
    }
    / �ð� �κ� ó�� /
  for(y=0; y<=GBOARD_HEIGHT; y++){
    for(x=0; x<GBOARD_WIDTH+2; x++){
      if(gameBoardInfo[y][x] == 1){
        SetCurrentCursorPos(x*2,y);
        printf("��");
  }           
  }
  }
}

void RedrawBlocks(void)
{   int x, y;
    int cursX, cursY;
    for(y=0; y<GBOARD_HEIGHT; y++)
    {   for(x=1; x<GBOARD_WIDTH+1; x++)
        {   cursX= x*2;
            cursY= y;
            SetCurrentCursorPos(cursX, cursY);
            if(gameBoardInfo[y][x]==1)
            {  printf("��");
            }
            else {  printf("  ");    }
        }
    }
}

*/

/* ��ũ�� ���̹�
int main()
{
	int x, y;
	int x1, y1;
	int block_id;
	int direction;
	int r;
	srand((unsigned int)time(NULL));
	while(1)
	{
		x=rand()%60;
		y=rand()%30;
		block_id=(rand()%7)*4;//0~24
		direction=rand()%8;
		r=block_id;
		if (direction==0)
		{
			for (y1=y; y1>=(y-10); y1--)
			{
				if ( block_id>=(r+4) ){
					block_id=r;
				SetCurrentCursorPos(x,y1);
				ShowBlock(blockModel[block_id]);
				Sleep(400);
				DeleteBlock(blockModel[block_id]);
				block_id++;
			}
		}
		else if (direction==1)
		{
			x1=x;
			for (y1=y; y1>=(y-10); y1--)
			{
				if ( block_id>=(r+4) )
					block_id=r;
				SetCurrentCursorPos(x1,y1);
				ShowBlock(blockModel[block_id]);
				Sleep(400);
				DeleteBlock(blockModel[block_id]);
				x1+=2; block_id++;
			}
		}
		else if (direction==2)
		{
			//x1=x;
			for (x1=x; x1<=(x+20); x1+=2)
			{
				if ( block_id>=(r+4) )
					block_id=r;
				SetCurrentCursorPos(x1,y);
				ShowBlock(blockModel[block_id]);
				Sleep(400);
				DeleteBlock(blockModel[block_id]);
				//x1+=2; block_id++;
			}
		}
		else if (direction==3)
		{
			y1=y;
			for (x1=x; x1<=(x+20); x1+=2)
			{
				if ( block_id>=(r+4) )
					block_id=r;
				SetCurrentCursorPos(x1,y1);
				ShowBlock(blockModel[block_id]);
				Sleep(400);
				DeleteBlock(blockModel[block_id]);
				y1++;
				block_id++;
			}
		}
		else if (direction==4)
		{
			for (y1=y; y1<=(y+10); y1++)
			{
				if ( block_id>=(r+4) )
					block_id=r;
				SetCurrentCursorPos(x,y1);
				ShowBlock(blockModel[block_id]);
				Sleep(400);
				DeleteBlock(blockModel[block_id]);
				//x1+=2;
				block_id++;
			}
		}
		else if (direction==5)
		{
			y1=y;
			for (x1=x; x1>=(x-20); x1-=2)
			{
				if ( block_id>=(r+4) )
					block_id=r;
				SetCurrentCursorPos(x1,y1);
				ShowBlock(blockModel[block_id]);
				Sleep(400);
				DeleteBlock(blockModel[block_id]);
				y1++;
				block_id++;
			}
		}
		else if (direction==6)
		{
			for (x1=x; x1>=(x-20); x1-=2)
			{
				if ( block_id>=(r+4) )
					block_id=r;
				SetCurrentCursorPos(x1,y);
				ShowBlock(blockModel[block_id]);
				Sleep(400);
				DeleteBlock(blockModel[block_id]);
				//x1+=2;
				block_id++;
			}
		}
		else
		{
			y1=y;
			for (x1=x; x1>=(x-20); x1-=2)
			{
				if ( block_id>=(r+4) )
					block_id=r;
				SetCurrentCursorPos(x1,y1);
				ShowBlock(blockModel[block_id]);
				Sleep(400);
				DeleteBlock(blockModel[block_id]);
				y1--;
				block_id++;
			}
		}
	}
		//*
		int i;//y
		int j=10;//x
		int block_id;
		int real_block_id;
		srand((unsigned int)time(NULL));
		block_id=(rand()%7)*4;//0~24
		real_block_id=block_id;
		for (i=0; i<20; i++)
		y { if ( block_id>=(real_block_id+4) )
		block_id=real_block_id;
		ShowBlock(blockModel[block_id]);
		Sleep(400);
		DeleteBlock(blockModel[block_id]);
		SetCurrentCursorPos(0,i);
		block_id++;
	}
	return 0;

	*/