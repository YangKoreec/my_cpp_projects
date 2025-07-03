#include <graphics.h>
#include <fstream>
#include <iostream>

/*
	План действий(Пафосно звучит):
	1)Структура, массив, заполнение(+)
	2)Доска(+)
	3)Фигуры(+)
	4)Правила(+)
	5)Управление(+)
	6)Разный цвет курсора(+)
	7)Показ возможных клеток хода после выбора фигуры(+)
	Возможно:
	1)Замена пешки на другую фигуру(+)
*/

// i - Вверх / Вниз
// ii - Влево / Вправо

struct Figures
{
	char Color[2];
	char Type[1];
	int x, y;
};

struct Hod
{
	int i1, ii1, i2, ii2;
	bool Enter_No_Press;
};

class Chest_Game {
	private:
	Figures Chest_Figures[8][8], Level_Up[4];
	Hod Cell;
	bool Black_turn, White_turn, G_Cells[8][8], File_Not_Found;
	int Cursor_i, Cursor_ii;
	public:
		
		Chest_Game()
		{
			if(Figures_Initialization())
			{
				G_Cells_Zeroing();
				Cursor_i = 0;
				Cursor_ii = 0;
				Black_turn = false;
				White_turn = true;
				Cell.Enter_No_Press = true;
				initwindow(510, 415);
				Desk_Creat();
				Hod_Cursor(Cursor_i, Cursor_ii, false);
				File_Not_Found = false;
				system("DEL Figures.txt");
			}
			else
			{
				File_Not_Found = true;
			}
		}
		
		~Chest_Game()
		{
			if(File_Not_Found)
			{
				std::cout << "File not found\nPlease press any key to exit\n";
				system("PAUSE");
			}
		}
		
		void Play()
		{
			if(!File_Not_Found)
			{
				while(Win_Or_Lose() == 1)
				{
					Hod_Move();
				}
				if(Win_Or_Lose() == 2)
				{
					std::cout << "Black Win\nPlease press any key to exit\n";
					closegraph();
				}
				if(Win_Or_Lose() == 3)
				{
					std::cout << "White Win\nPlease press any key to exit\n";
					closegraph();
				}
				system("PAUSE");
			}
		}
		
		void Peshka_Level_Up(int j, int jj, int Color)
		{
			setcolor(BLACK);
			for(int i=0; i<4; ++i)
			{
				setfillstyle(1, Color);
				//Ладья
				if(Level_Up[i].Type[0] == 'L')
				{
					bar3d(Level_Up[i].x+15, Level_Up[i].y-20, Level_Up[i].x-15, Level_Up[i].y-5, 0, 0);
					bar3d(Level_Up[i].x-7, Level_Up[i].y-5, Level_Up[i].x+7, Level_Up[i].y+13, 0, 0);
					bar3d(Level_Up[i].x-15, Level_Up[i].y+13, Level_Up[i].x+15, Level_Up[i].y+18, 0, 0);
				}
				//Слон
				if(Level_Up[i].Type[0] == 'S')
				{
					fillellipse(Level_Up[i].x, Level_Up[i].y-8, 10, 14);
					fillellipse(Level_Up[i].x, Level_Up[i].y+5, 8, 8);
					pieslice(Level_Up[i].x, Level_Up[i].y+23, 0, 180, 16);
				}
				//Конь(Флажок)
				if(Level_Up[i].Type[0] == 'H')
				{
					int Horse_Points[8];
					Horse_Points[0] = Level_Up[i].x;
					Horse_Points[1] = Level_Up[i].y;
					Horse_Points[2] = Level_Up[i].x;
					Horse_Points[3] = Level_Up[i].y-20;
					Horse_Points[4] = Level_Up[i].x-20;
					Horse_Points[5] = Level_Up[i].y-10;
					Horse_Points[6] = Horse_Points[0];
					Horse_Points[7] = Horse_Points[1];
					fillpoly(4, Horse_Points);
					bar3d(Level_Up[i].x, Level_Up[i].y-20, Level_Up[i].x+10, Level_Up[i].y+13, 0, 0);
					bar3d(Level_Up[i].x-10, Level_Up[i].y+13, Level_Up[i].x+20, Level_Up[i].y+18, 0, 0);
				}
				//Королева
				if(Level_Up[i].Type[0] == 'Q')
				{
					int Crown_Points[16];
					Crown_Points[0] = Level_Up[i].x-12;
					Crown_Points[1] = Level_Up[i].y-4;
					Crown_Points[2] = Level_Up[i].x-12;
					Crown_Points[3] = Level_Up[i].y-18;
					Crown_Points[4] = Level_Up[i].x-6;
					Crown_Points[5] = Level_Up[i].y-12;
					Crown_Points[6] = Level_Up[i].x;
					Crown_Points[7] = Level_Up[i].y-18;
					Crown_Points[8] = Level_Up[i].x+6;
					Crown_Points[9] = Level_Up[i].y-12;
					Crown_Points[10] = Level_Up[i].x+12;
					Crown_Points[11] = Level_Up[i].y-18;
					Crown_Points[12] = Level_Up[i].x+12;	
					Crown_Points[13] = Level_Up[i].y-4;
					Crown_Points[14] = Crown_Points[0];
					Crown_Points[15] = 	Crown_Points[1];
					pieslice(Level_Up[i].x+1, Level_Up[i].y+8, 0, 180, 13);
					pieslice(Level_Up[i].x+1, Level_Up[i].y+23, 0, 180, 16);
					setcolor(MAGENTA);
					setfillstyle(1, MAGENTA);
					fillpoly(8, Crown_Points);
				}
			}
			int i=0;
			bool Enter_No_Press_2 = true;
			setcolor(GREEN);
			rectangle(Level_Up[i].x - 25, Level_Up[i].y - 25, Level_Up[i].x + 25, Level_Up[i].y + 25);
			rectangle(Level_Up[i].x - 24, Level_Up[i].y - 24, Level_Up[i].x + 24, Level_Up[i].y + 24);
			rectangle(Level_Up[i].x - 23, Level_Up[i].y - 23, Level_Up[i].x + 23, Level_Up[i].y + 23);
			while(Enter_No_Press_2)
			{
				switch(getch())
				{
					case 'w' : Peshka_Level_Up_Past_Cursor_Delete(i); i-=1; break;
					case 'W' : Peshka_Level_Up_Past_Cursor_Delete(i); i-=1; break;
					case 72 : Peshka_Level_Up_Past_Cursor_Delete(i); i-=1; break;
					case 's' : Peshka_Level_Up_Past_Cursor_Delete(i); i+=1; break;
					case 'S' : Peshka_Level_Up_Past_Cursor_Delete(i); i+=1; break;
					case 80 : Peshka_Level_Up_Past_Cursor_Delete(i); i+=1; break;
					case 13 : Enter_No_Press_2 = false; break;
				}
				if(i < 0 && Enter_No_Press_2)
				{
					i=0;
				}
				if(i > 3 && Enter_No_Press_2)
				{
					i=3;
				}
				if(Enter_No_Press_2)
				{
					setcolor(GREEN);
					rectangle(Level_Up[i].x - 25, Level_Up[i].y - 25, Level_Up[i].x + 25, Level_Up[i].y + 25);
					rectangle(Level_Up[i].x - 24, Level_Up[i].y - 24, Level_Up[i].x + 24, Level_Up[i].y + 24);
					rectangle(Level_Up[i].x - 23, Level_Up[i].y - 23, Level_Up[i].x + 23, Level_Up[i].y + 23);
				}
			}
			Chest_Figures[j][jj].Type[0] = Level_Up[i].Type[0];
		}
		
		void Peshka_Level_Up_Past_Cursor_Delete(int i)
		{
			setcolor(getpixel(Level_Up[i].x - 22, Level_Up[i].y + 22));
			rectangle(Level_Up[i].x - 25, Level_Up[i].y - 25, Level_Up[i].x + 25, Level_Up[i].y + 25);
			rectangle(Level_Up[i].x - 24, Level_Up[i].y - 24, Level_Up[i].x + 24, Level_Up[i].y + 24);
			rectangle(Level_Up[i].x - 23, Level_Up[i].y - 23, Level_Up[i].x + 23, Level_Up[i].y + 23);
		}
		
		void Figures_Swap(int i1, int ii1, int i2, int ii2)
		{
			if(Chest_Figures[i1][ii1].Color[0] != Chest_Figures[i2][ii2].Color[0])
			{
				Chest_Figures[i2][ii2].Color[0] = Chest_Figures[i1][ii1].Color[0];
				Chest_Figures[i2][ii2].Type[0] = Chest_Figures[i1][ii1].Type[0];
				Chest_Figures[i1][ii1].Color[0] = '-';
				Chest_Figures[i1][ii1].Type[0] = '-';
				if(White_turn)
				{
					White_turn = false;
					Black_turn = true;
				}
				else
				{
					Black_turn = false;
					White_turn = true;
				}
			}
			Desk_Creat();
			if(Chest_Figures[i2][ii2].Color[0] == 'B' && Chest_Figures[i2][ii2].Type[0] == 'P' && i2 == 7)
			{
				Peshka_Level_Up(i2, ii2, BLACK);
			}
			if(Chest_Figures[i2][ii2].Color[0] == 'W' && Chest_Figures[i2][ii2].Type[0] == 'P' && i2 == 0)
			{
				Peshka_Level_Up(i2, ii2, WHITE);
			}
			
		}
		
		void Figures_Move(int i1, int ii1, int i2, int ii2) // i1, ii1, i2, ii2 - Номера фигур 
		{
			if(Chest_Figures[i1][ii1].Type[0] == 'P') // Пешка
			{
				if(Chest_Figures[i1][ii1].Color[0] == 'W')
				{
					if(Chest_Figures[i2][ii2].Type[0] == '-')
					{
						if(((i1 == 6 && i1 == i2+2 && Chest_Figures[i2+1][ii2].Type[0] == '-') || (i1 == i2+1)) && ii1 == ii2)
						{
							Figures_Swap(i1, ii1, i2, ii2);
						}
					}
					if((i1 == i2+1 && (ii1 == ii2+1 || ii1 == ii2-1)) && Chest_Figures[i2][ii2].Color[0] == 'B')
					{
						Figures_Swap(i1, ii1, i2, ii2);
					}
				}
				if(Chest_Figures[i1][ii1].Color[0] == 'B')
				{
					if(Chest_Figures[i2][ii2].Type[0] == '-')
					{
						if(((i1 == 1 && i1 == i2-2 && Chest_Figures[i2-1][ii2].Type[0] == '-') || (i1 == i2-1)) && ii1 == ii2)
						{
							Figures_Swap(i1, ii1, i2, ii2);
						}
					}
					if((i1 == i2-1 && (ii1 == ii2+1 || ii1 == ii2-1)) && Chest_Figures[i2][ii2].Color[0] == 'W')
					{
						Figures_Swap(i1, ii1, i2, ii2);
					}
				}
			}
			
			if(Chest_Figures[i1][ii1].Type[0] == 'H') // Конь
			{
				if((i1 == i2 - 2 || i1 == i2 + 2) && (ii1 == ii2 + 1 || ii1 == ii2 - 1))
				{
					Figures_Swap(i1, ii1, i2, ii2);
				}
				if((i1 == i2 - 1 || i1 == i2 + 1) && (ii1 == ii2 + 2 || ii1 == ii2 - 2))
				{
					Figures_Swap(i1, ii1, i2, ii2);
				}
			}
			
			if(Chest_Figures[i1][ii1].Type[0] == 'S' || Chest_Figures[i1][ii1].Type[0] == 'Q') // Слон и Королева
			{
				if(abs(i1-i2) == abs(ii1-ii2))
				{
					bool Nothing = true;
					for(int i=1; i<abs(i1-i2); ++i)
					{
						if(i1 < i2)
						{
							if(ii1 < ii2)
							{
								if(Chest_Figures[i1+i][ii1+i].Type[0] != '-')
								{
									Nothing = false;
								}
							}
							if(ii1 > ii2)
							{
								if(Chest_Figures[i1+i][ii1-i].Type[0] != '-')
								{
									Nothing = false;
								}
							}
						}
						if(i1 > i2)
						{
							if(ii1 < ii2)
							{
								if(Chest_Figures[i1-i][ii1+i].Type[0] != '-')
								{
									Nothing = false;
								}
							}
							if(ii1 > ii2)
							{
								if(Chest_Figures[i1-i][ii1-i].Type[0] != '-')
								{
									Nothing = false;
								}
							}
						}
					}
					if(Nothing)
					{
						Figures_Swap(i1, ii1, i2, ii2);
					}	
				}
			}
			
			if(Chest_Figures[i1][ii1].Type[0] == 'L' || Chest_Figures[i1][ii1].Type[0] == 'Q') // Ладья и Королева
			{
				if(i1 == i2 || ii1 == ii2)
				{
					bool Nothing = true;
					if(i1 == i2)
					{
						for(int i=1; i<abs(ii1-ii2); ++i)
						{
							if(ii1 > ii2)
							{
								if(Chest_Figures[i1][ii1-i].Type[0] != '-')
								{
									Nothing = false;
								}
							}
							if(ii1 < ii2)
							{
								if(Chest_Figures[i1][ii1+i].Type[0] != '-')
								{
									Nothing = false;
								}
							}
						}
					}
					if(ii1 == ii2)
					{
						for(int i=1; i<abs(i1-i2); ++i)
						{
							if(i1 < i2)
							{
								if(Chest_Figures[i1+i][ii1].Type[0] != '-')
								{
									Nothing = false;
								}
							}
							if(i1 > i2)
							{
								if(Chest_Figures[i1-i][ii1].Type[0] != '-')
								{
									Nothing = false;
								}
							}
						}
					}
					if(Nothing)
					{
						Figures_Swap(i1, ii1, i2, ii2);
					}
				}
			}
			
			if(Chest_Figures[i1][ii1].Type[0] == 'K') // Король
			{
				if((i1 == i2) || (i1 == i2+1) || (i1 == i2-1) || (ii1 == ii2) || (ii1 == ii2+1) || (ii1 == ii2-1))
				{
					Figures_Swap(i1, ii1, i2, ii2);
				}
			}
		}
		
		void Green_Cells(int i, int ii)
		{
			int Cell_Points[10];
			if(Chest_Figures[i][ii].Type[0] == 'P') // Пешка
			{
				// 1
				if(Chest_Figures[i][ii].Color[0] == 'W')
				{
					if(Chest_Figures[i-1][ii].Type[0] == '-')
					{
						G_Cells[i-1][ii] = true;
					}
					if(i == 6 && Chest_Figures[i-2][ii].Type[0] == '-' && Chest_Figures[i-1][ii].Type[0] == '-')
					{
						G_Cells[i-2][ii] = true;
					}
					if(Chest_Figures[i-1][ii-1].Color[0] == 'B' && (ii != 0))
					{
						G_Cells[i-1][ii-1] = true;
					}
					if(Chest_Figures[i-1][ii+1].Color[0] == 'B' && (ii != 7))
					{
						G_Cells[i-1][ii+1] = true;
					}
				}
				// 2
				if(Chest_Figures[i][ii].Color[0] == 'B')
				{
					if(Chest_Figures[i+1][ii].Type[0] == '-')
					{
						G_Cells[i+1][ii] = true;
					}
					if(i == 1 && Chest_Figures[i+2][ii].Type[0] == '-' && Chest_Figures[i+1][ii].Type[0] == '-')
					{
						G_Cells[i+2][ii] = true;
					}
					if(Chest_Figures[i+1][ii-1].Color[0] == 'W' && (ii != 0))
					{
						G_Cells[i+1][ii-1] = true;
					}
					if(Chest_Figures[i+1][ii+1].Color[0] == 'W' && (ii != 7))
					{
						G_Cells[i+1][ii+1] = true;
					}
				}
			}
			
			if(Chest_Figures[i][ii].Type[0] == 'S' || Chest_Figures[i][ii].Type[0] == 'Q') // Слон и Королева
			{
				int N = 1;
				// 1
				while(Chest_Figures[i+N][ii+N].Type[0] == '-' && i+N < 8  && ii+N < 8)
				{
					G_Cells[i+N][ii+N] = true;
					N+=1;
				}
				if(Chest_Figures[i+N][ii+N].Color[0] != Chest_Figures[i][ii].Color[0] && i+N < 8  && ii+N < 8)
				{
					G_Cells[i+N][ii+N] = true;
				}
				N=1;
				// 2
				while(Chest_Figures[i+N][ii-N].Type[0] == '-' && i+N < 8  && ii-N > -1)
				{
					G_Cells[i+N][ii-N] = true;
					N+=1;
				}
				if(Chest_Figures[i+N][ii-N].Color[0] != Chest_Figures[i][ii].Color[0] && i+N < 8  && ii-N > -1)
				{
					G_Cells[i+N][ii-N] = true;
				}
				N=1;
				// 3
				while(Chest_Figures[i-N][ii-N].Type[0] == '-' && i+N > -1  && ii-N > -1)
				{
					G_Cells[i-N][ii-N] = true;
					N+=1;
				}
				if(Chest_Figures[i-N][ii-N].Color[0] != Chest_Figures[i][ii].Color[0] && i-N > -1  && ii-N > -1)
				{
					G_Cells[i-N][ii-N] = true;
				}
				N=1;
				// 4
				while(Chest_Figures[i-N][ii+N].Type[0] == '-' && i+N > -1  && ii+N < 8)
				{
					G_Cells[i-N][ii+N] = true;
					N+=1;
				}
				if(Chest_Figures[i-N][ii+N].Color[0] != Chest_Figures[i][ii].Color[0] && i-N > -1  && ii+N < 8)
				{
					G_Cells[i-N][ii+N] = true;
				}
			}
			
			if(Chest_Figures[i][ii].Type[0] == 'H') // Конь
			{
				// 1
				if(Chest_Figures[i-1][ii+2].Color[0] != Chest_Figures[i][ii].Color[0] && i-1 > -1 && ii+2 < 8)
				{
					G_Cells[i-1][ii+2] = true;
				}
				// 2
				if(Chest_Figures[i-1][ii-2].Color[0] != Chest_Figures[i][ii].Color[0] && i-1 > -1 && ii-2 > -1)
				{
					G_Cells[i-1][ii-2] = true;
				}
				// 3
				if(Chest_Figures[i+1][ii+2].Color[0] != Chest_Figures[i][ii].Color[0] && i+1 < 8 && ii+2 < 8)
				{
					G_Cells[i+1][ii+2] = true;
				}
				// 4
				if(Chest_Figures[i+1][ii-2].Color[0] != Chest_Figures[i][ii].Color[0] && i+1 < 8 && ii-2 > -1)
				{
					G_Cells[i+1][ii-2] = true;
				}
				// 5
				if(Chest_Figures[i-2][ii+1].Color[0] != Chest_Figures[i][ii].Color[0] && i-2 > -1 && ii+1 < 8)
				{
					G_Cells[i-2][ii+1] = true;
				}
				// 6
				if(Chest_Figures[i-2][ii-1].Color[0] != Chest_Figures[i][ii].Color[0] && i-2 > -1 && ii-1 > -1)
				{
					G_Cells[i-2][ii-1] = true;
				}
				// 7
				if(Chest_Figures[i+2][ii+1].Color[0] != Chest_Figures[i][ii].Color[0] && i+2 < 8 && ii+1 < 8)
				{
					G_Cells[i+2][ii+1] = true;
				}
				// 8
				if(Chest_Figures[i+2][ii-1].Color[0] != Chest_Figures[i][ii].Color[0] && i+2 < 8 && ii-1 > -1)
				{
					G_Cells[i+2][ii-1] = true;
				}
			}
			
			if(Chest_Figures[i][ii].Type[0] == 'L' || Chest_Figures[i][ii].Type[0] == 'Q') // Ладья и Королева
			{
				int N=1;
				// 1
				while(Chest_Figures[i+N][ii].Type[0] == '-' && i+N < 8)
				{
					G_Cells[i+N][ii] = true;
					N+=1;
				}
				if(Chest_Figures[i+N][ii].Color[0] != Chest_Figures[i][ii].Color[0] && i+N < 8)
				{
					G_Cells[i+N][ii] = true;
				}
				N=1;
				// 2
				while(Chest_Figures[i-N][ii].Type[0] == '-' && i-N > -1)
				{
					G_Cells[i-N][ii] = true;
					N+=1;
				}
				if(Chest_Figures[i-N][ii].Color[0] != Chest_Figures[i][ii].Color[0] && i-N > -1)
				{
					G_Cells[i-N][ii] = true;
				}
				N=1;
				// 3
				while(Chest_Figures[i][ii+N].Type[0] == '-' && ii+N < 8)
				{
					G_Cells[i][ii+N] = true;
					N+=1;
				}
				if(Chest_Figures[i][ii+N].Color[0] != Chest_Figures[i][ii].Color[0] && ii+N < 8)
				{
					G_Cells[i][ii+N] = true;
				}
				N=1;
				// 4
				while(Chest_Figures[i][ii-N].Type[0] == '-' && ii-N > -1)
				{
					G_Cells[i][ii-N] = true;
					N+=1;
				}
				if(Chest_Figures[i][ii-N].Color[0] != Chest_Figures[i][ii].Color[0] && ii-N > -1)
				{
					G_Cells[i][ii-N] = true;
				}
			}
			
			if(Chest_Figures[i][ii].Type[0] == 'K') // Король
			{
				// 1
				if(Chest_Figures[i+1][ii].Color[0] != Chest_Figures[i][ii].Color[0] && i+1 < 8)
				{
					G_Cells[i+1][ii] = true;
				}
				// 2
				if(Chest_Figures[i-1][ii].Color[0] != Chest_Figures[i][ii].Color[0] && i-1 > -1)
				{
					G_Cells[i-1][ii] = true;
				}
				// 3
				if(Chest_Figures[i][ii+1].Color[0] != Chest_Figures[i][ii].Color[0] && ii+1 < 8)
				{
					G_Cells[i][ii+1] = true;
				}
				// 4
				if(Chest_Figures[i][ii-1].Color[0] != Chest_Figures[i][ii].Color[0] && ii-1 > -1)
				{
					G_Cells[i][ii-1] = true;
				}
				// 5
				if(Chest_Figures[i+1][ii+1].Color[0] != Chest_Figures[i][ii].Color[0] && i+1 < 8 && ii+1 < 8)
				{
					G_Cells[i+1][ii+1] = true;
				}
				// 6
				if(Chest_Figures[i+1][ii-1].Color[0] != Chest_Figures[i][ii].Color[0] && i+1 < 8 && ii-1 > -1)
				{
					G_Cells[i+1][ii-1] = true;
				}
				// 7
				if(Chest_Figures[i-1][ii+1].Color[0] != Chest_Figures[i][ii].Color[0] && i-1 > -1 && ii+1 < 8)
				{
					G_Cells[i-1][ii+1] = true;
				}
				// 8
				if(Chest_Figures[i-1][ii-1].Color[0] != Chest_Figures[i][ii].Color[0] && i-1 > -1 && ii-1 > -1)
				{
					G_Cells[i-1][ii-1] = true;
				}
			}
			for(int j=0; j<8; ++j)
			{
				for(int jj=0; jj<8; ++jj)
				{
					if(G_Cells[j][jj])
					{
						Cell_Points[0] = Chest_Figures[j][jj].x - 25;
						Cell_Points[1] = Chest_Figures[j][jj].y - 25;
						Cell_Points[2] = Chest_Figures[j][jj].x + 25;
						Cell_Points[3] = Chest_Figures[j][jj].y - 25;
						Cell_Points[4] = Chest_Figures[j][jj].x + 25;
						Cell_Points[5] = Chest_Figures[j][jj].y + 25;
						Cell_Points[6] = Chest_Figures[j][jj].x - 25;
						Cell_Points[7] = Chest_Figures[j][jj].y + 25;
						Cell_Points[8] = Cell_Points[0];
						Cell_Points[9] = Cell_Points[1];
						setcolor(BLACK);
						setfillstyle(1, GREEN);
						fillpoly(5, Cell_Points);
					}
				}
			}
			Figures_Creat();
		}
		
		void Hod_Cursor(int i, int ii, bool Enter_Press)
		{
			if(Enter_Press)
			{
				if(G_Cells[i][ii])
				{
					setcolor(BLUE);
				}
				else
				{
					setcolor(RED);
				}
			}
			else
			{
				if(Chest_Figures[i][ii].Color[0] == 'W' && White_turn)
				{
					Cursor_Color(i, ii);
				}
				else
				{
					if(Chest_Figures[i][ii].Color[0] == 'B' && Black_turn)
					{
						Cursor_Color(i, ii);
					}
					else
					{
						setcolor(RED);
					}
				}
			}
			rectangle(Chest_Figures[i][ii].x - 25, Chest_Figures[i][ii].y - 25, Chest_Figures[i][ii].x + 25, Chest_Figures[i][ii].y + 25);
			rectangle(Chest_Figures[i][ii].x - 24, Chest_Figures[i][ii].y - 24, Chest_Figures[i][ii].x + 24, Chest_Figures[i][ii].y + 24);
			rectangle(Chest_Figures[i][ii].x - 23, Chest_Figures[i][ii].y - 23, Chest_Figures[i][ii].x + 23, Chest_Figures[i][ii].y + 23);
		}
		
		void Cursor_Color(int i, int ii)
		{
			int Color = 0;
			if(Chest_Figures[i][ii].Type[0] == 'H') // Конь
			{
				// 1
				if(Chest_Figures[i-1][ii+2].Color[0] != Chest_Figures[i][ii].Color[0] && i-1 > -1 && ii+2 < 8)
				{
					Color+=1;
				}
				// 2
				if(Chest_Figures[i-1][ii-2].Color[0] != Chest_Figures[i][ii].Color[0] && i-1 > -1 && ii-2 > -1)
				{
					Color+=1;
				}
				// 3
				if(Chest_Figures[i+1][ii+2].Color[0] != Chest_Figures[i][ii].Color[0] && i+1 < 8 && ii+2 < 8)
				{
					Color+=1;
				}
				// 4
				if(Chest_Figures[i+1][ii-2].Color[0] != Chest_Figures[i][ii].Color[0] && i+1 < 8 && ii-2 > -1)
				{
					Color+=1;
				}
				// 5
				if(Chest_Figures[i-2][ii+1].Color[0] != Chest_Figures[i][ii].Color[0] && i-2 > -1 && ii+1 < 8)
				{
					Color+=1;
				}
				// 6
				if(Chest_Figures[i-2][ii-1].Color[0] != Chest_Figures[i][ii].Color[0] && i-2 > -1 && ii-1 > -1)
				{
					Color+=1;
				}
				// 7
				if(Chest_Figures[i+2][ii+1].Color[0] != Chest_Figures[i][ii].Color[0] && i+2 < 8 && ii+1 < 8)
				{
					Color+=1;
				}
				// 8
				if(Chest_Figures[i+2][ii-1].Color[0] != Chest_Figures[i][ii].Color[0] && i+2 < 8 && ii-1 > -1)
				{
					Color+=1;
				}
			}
			
			if(Chest_Figures[i][ii].Type[0] == 'P') // Пешка
			{
				// 1
				if(Chest_Figures[i][ii].Color[0] == 'W')
				{
					if(Chest_Figures[i-1][ii].Type[0] == '-')
					{
						Color+=1;
					}
					if(i == 6 && Chest_Figures[i-2][ii].Type[0] == '-' && Chest_Figures[i-1][ii].Type[0] == '-')
					{
						Color+=1;
					}
					if(Chest_Figures[i-1][ii-1].Color[0] == 'B')
					{
						Color+=1;
					}
					if(Chest_Figures[i-1][ii+1].Color[0] == 'B')
					{
						Color+=1;
					}
				}
				// 2
				if(Chest_Figures[i][ii].Color[0] == 'B')
				{
					if(Chest_Figures[i+1][ii].Type[0] == '-')
					{
						Color+=1;
					}
					if(i == 1 && Chest_Figures[i+2][ii].Type[0] == '-' && Chest_Figures[i+1][ii].Type[0] == '-')
					{
						Color+=1;
					}
					if(Chest_Figures[i+1][ii-1].Color[0] == 'W')
					{
						Color+=1;
					}
					if(Chest_Figures[i+1][ii+1].Color[0] == 'W')
					{
						Color+=1;
					}
				}
			}
			
			if(Chest_Figures[i][ii].Type[0] == 'L' || Chest_Figures[i][ii].Type[0] == 'K' || Chest_Figures[i][ii].Type[0] == 'Q') // Ладья и Король и Королева
			{
				// 1
				if(Chest_Figures[i+1][ii].Color[0] != Chest_Figures[i][ii].Color[0] && i+1 < 8)
				{
					Color+=1;
				}
				// 2
				if(Chest_Figures[i-1][ii].Color[0] != Chest_Figures[i][ii].Color[0] && i-1 > -1)
				{
					Color+=1;
				}
				// 3
				if(Chest_Figures[i][ii+1].Color[0] != Chest_Figures[i][ii].Color[0] && ii+1 < 8)
				{
					Color+=1;
				}
				// 4
				if(Chest_Figures[i][ii-1].Color[0] != Chest_Figures[i][ii].Color[0] && ii-1 > -1)
				{
					Color+=1;
				}
			}
			
			if(Chest_Figures[i][ii].Type[0] == 'K' || Chest_Figures[i][ii].Type[0] == 'Q' || Chest_Figures[i][ii].Type[0] == 'S') // Король и Королева и Слон
			{
				// 1
				if(Chest_Figures[i+1][ii+1].Color[0] != Chest_Figures[i][ii].Color[0] && i+1 < 8 && ii+1 < 8)
				{
					Color+=1;
				}
				// 2
				if(Chest_Figures[i+1][ii-1].Color[0] != Chest_Figures[i][ii].Color[0] && i+1 < 8 && ii-1 > -1)
				{
					Color+=1;
				}
				// 3
				if(Chest_Figures[i-1][ii+1].Color[0] != Chest_Figures[i][ii].Color[0] && i-1 > -1 && ii+1 < 8)
				{
					Color+=1;
				}
				// 4
				if(Chest_Figures[i-1][ii-1].Color[0] != Chest_Figures[i][ii].Color[0] && i-1 > -1 && ii-1 > -1)
				{
					Color+=1;
				}
			}
			if(Color >= 1)
			{
				setcolor(GREEN);
			}
			else
			{
				setcolor(RED);
			}
		}
		
		int Win_Or_Lose()
		{
			bool White_King = false, Black_King = false;
			for(int i=0; i<8; ++i)
			{
				for(int ii=0; ii<8; ++ii)
				{
					if(Chest_Figures[i][ii].Type[0] == 'K')
					{
						if(Chest_Figures[i][ii].Color[0] == 'W')
						{
							White_King = true;
						}
						if(Chest_Figures[i][ii].Color[0] == 'B')
						{
							Black_King = true;
						}
					}
				}
			}
			if(Black_King && White_King)
			{
				return 1;
			}
			else
			{
				if(Black_King)
				{
					return 2;
				}
				if(White_King)
				{
					return 3;
				}
			}
		}
		
		void Figures_Give()
		{
			if(Cell.Enter_No_Press)
			{
				Cell.i1 = Cursor_i;
				Cell.ii1 = Cursor_ii;
				Cell.Enter_No_Press = false;
				if(Chest_Figures[Cursor_i][Cursor_ii].Type[0] == '-')
				{
					Cell.Enter_No_Press = true;
				}
				if((Chest_Figures[Cursor_i][Cursor_ii].Color[0] == 'W') && Black_turn)
				{
					Cell.Enter_No_Press = true;
				}
				if((Chest_Figures[Cursor_i][Cursor_ii].Color[0] == 'B') && White_turn)
				{
					Cell.Enter_No_Press = true;
				}
				if(Cell.Enter_No_Press == false)
				{
					Green_Cells(Cell.i1, Cell.ii1);
				}
			}
			else
			{
				Cell.i2 = Cursor_i;
				Cell.ii2 = Cursor_ii;
				Cell.Enter_No_Press = true;
				Figures_Move(Cell.i1, Cell.ii1, Cell.i2, Cell.ii2);
				G_Cells_Zeroing();
				Desk_Creat();
			}
		}
		
		void Hod_Move()
		{
			bool Enter_Press = false;
			int Past_i = Cursor_i, Past_ii = Cursor_ii;  
			switch(getch())
			{
				case 'w': Cursor_i -= 1; break;
				case 'a': Cursor_ii -= 1; break;
				case 's': Cursor_i += 1; break;
				case 'd': Cursor_ii += 1; break;
				case 'W': Cursor_i -= 1; break;
				case 'A': Cursor_ii -= 1; break;
				case 'S': Cursor_i += 1; break;
				case 'D': Cursor_ii += 1; break;
				case 72 : Cursor_i -= 1; break;
				case 75 : Cursor_ii -= 1; break;
				case 80 : Cursor_i += 1; break;
				case 77 : Cursor_ii += 1; break;
				case 13: Figures_Give();
			}
			if(Cursor_i > 7)
			{
				Cursor_i = 7;
			}
			if(Cursor_i < 0)
			{
				Cursor_i = 0;
			}
			if(Cursor_ii > 7)
			{
				Cursor_ii = 7;
			}
			if(Cursor_ii < 0)
			{
				Cursor_ii = 0;
			}
			if(Cell.Enter_No_Press == false)
			{
				Enter_Press = true;
			}
			setcolor(BLACK);
			rectangle(Chest_Figures[Past_i][Past_ii].x - 25, Chest_Figures[Past_i][Past_ii].y - 25, Chest_Figures[Past_i][Past_ii].x + 25,Chest_Figures[Past_i][Past_ii].y + 25);
			setcolor(getpixel(Chest_Figures[Past_i][Past_ii].x-22,Chest_Figures[Past_i][Past_ii].y-22));
			rectangle(Chest_Figures[Past_i][Past_ii].x - 24, Chest_Figures[Past_i][Past_ii].y - 24, Chest_Figures[Past_i][Past_ii].x + 24,Chest_Figures[Past_i][Past_ii].y + 24);
			rectangle(Chest_Figures[Past_i][Past_ii].x - 23, Chest_Figures[Past_i][Past_ii].y - 23, Chest_Figures[Past_i][Past_ii].x + 23,Chest_Figures[Past_i][Past_ii].y + 23);
			Hod_Cursor(Cursor_i, Cursor_ii, Enter_Press);
		}
		
		bool Figures_Initialization()
		{
			std::ofstream f("Figures.txt", std::ios::out);
			f << "B L 25 25\nB H 75 25\nB S 125 25\nB K 175 25\nB Q 225 25\nB S 275 25\nB H 325 25\nB L 375 25\n";
			for(int i=25; i<=375; i+=50)
			{
				f << "B P " << i << " 75\n";
			}
			for(int i=125; i<=275; i+=50)
			{
				for(int ii=25; ii<=375; ii+=50)
				{
					f << "- - " << ii << " " << i << "\n";
				}
			}
			for(int i=25; i<=375; i+=50)
			{
				f << "W P " << i << " 325\n";
			}
			f << "W L 25 375\nW H 75 375\nW S 125 375\nW K 175 375\nW Q 225 375\nW S 275 375\nW H 325 375\nW L 375 375\n";
			f << "- L 475 25\n- S 475 75\n- H 475 125\n- Q 475 175";
			f.close();
			std::ifstream Creat("Figures.txt", std::ios::in);
			if(Creat)
			{
				for(int i=0; i<8; ++i)
				{
					for(int ii=0; ii<8; ++ii)
					{
						Creat >> Chest_Figures[i][ii].Color >> Chest_Figures[i][ii].Type >> Chest_Figures[i][ii].x >> Chest_Figures[i][ii].y;
					}
				}
				for(int i=0; i<4; ++i)
				{
					Creat >> Level_Up[i].Color >> Level_Up[i].Type >> Level_Up[i].x >> Level_Up[i].y;
				}
				return true;
			}
			else
			{
				return false;
			}
			Creat.close();
		}
		
		void G_Cells_Zeroing()
		{
			for(int i=0; i<8; ++i)
			{
				for(int ii=0; ii<8; ++ii)
				{
					G_Cells[i][ii] = false; // G_Cells = Green_Cells
				}
			}
		}
		
		void Desk_Creat()
		{
			setcolor(BLACK);
			int Cell_Color=1, Cell_Points[10];
			Cell_Color+=1;
			for(int i=0; i<4; ++i)
			{
				Cell_Points[0] = Level_Up[i].x - 25;
				Cell_Points[1] = Level_Up[i].y - 25;
				Cell_Points[2] = Level_Up[i].x + 25;
				Cell_Points[3] = Level_Up[i].y - 25;
				Cell_Points[4] = Level_Up[i].x + 25;
				Cell_Points[5] = Level_Up[i].y + 25;
				Cell_Points[6] = Level_Up[i].x - 25;
				Cell_Points[7] = Level_Up[i].y + 25;
				Cell_Points[8] = Cell_Points[0];
				Cell_Points[9] = Cell_Points[1];
				if(Cell_Color%2 == 0)
				{		
					setfillstyle(1, BROWN);
					fillpoly(5, Cell_Points);
					Cell_Color+=1;
				}
				else
				{
					setfillstyle(1, WHITE);
					fillpoly(5, Cell_Points);
					Cell_Color+=1;
				}
			}
			Cell_Color = 1;
			setcolor(BLACK);
			for(int i=0; i<8; ++i)
			{
				Cell_Color+=1;
				for(int ii=0; ii<8; ++ii)
				{
					Cell_Points[0] = Chest_Figures[i][ii].x - 25;
					Cell_Points[1] = Chest_Figures[i][ii].y - 25;
					Cell_Points[2] = Chest_Figures[i][ii].x + 25;
					Cell_Points[3] = Chest_Figures[i][ii].y - 25;
					Cell_Points[4] = Chest_Figures[i][ii].x + 25;
					Cell_Points[5] = Chest_Figures[i][ii].y + 25;
					Cell_Points[6] = Chest_Figures[i][ii].x - 25;
					Cell_Points[7] = Chest_Figures[i][ii].y + 25;
					Cell_Points[8] = Cell_Points[0];
					Cell_Points[9] = Cell_Points[1];
					if(Cell_Color%2 == 0)
					{		
						setfillstyle(1, BROWN);
						fillpoly(5, Cell_Points);
						Cell_Color+=1;
					}
					else
					{
						setfillstyle(1, WHITE);
						fillpoly(5, Cell_Points);
						Cell_Color+=1;
					}
				}
			}
			Figures_Creat();
		}
		
		void Figures_Creat()
		{
			for(int i=0; i<8; ++i)
			{
				for(int ii=0; ii<8; ++ii)
				{
					setcolor(BLACK);
					//Цвет
					if(Chest_Figures[i][ii].Color[0] == 'W')
					{
						setfillstyle(1, WHITE);
					}
					if(Chest_Figures[i][ii].Color[0] == 'B')
					{
						setfillstyle(1, BLACK);
					}
					//Пешка
					if(Chest_Figures[i][ii].Type[0] == 'P')
					{
						pieslice(Chest_Figures[i][ii].x, Chest_Figures[i][ii].y+8, 0, 180, 13);
						pieslice(Chest_Figures[i][ii].x, Chest_Figures[i][ii].y+23, 0, 180, 16);
						fillellipse(Chest_Figures[i][ii].x, Chest_Figures[i][ii].y-12, 10, 10);
					}
					//Ладья
					if(Chest_Figures[i][ii].Type[0] == 'L')
					{
						bar3d(Chest_Figures[i][ii].x+15, Chest_Figures[i][ii].y-20, Chest_Figures[i][ii].x-15, Chest_Figures[i][ii].y-5, 0, 0);
						bar3d(Chest_Figures[i][ii].x-7, Chest_Figures[i][ii].y-5, Chest_Figures[i][ii].x+7, Chest_Figures[i][ii].y+13, 0, 0);
						bar3d(Chest_Figures[i][ii].x-15, Chest_Figures[i][ii].y+13, Chest_Figures[i][ii].x+15, Chest_Figures[i][ii].y+18, 0, 0);
					}
					//Слон
					if(Chest_Figures[i][ii].Type[0] == 'S')
					{
						fillellipse(Chest_Figures[i][ii].x, Chest_Figures[i][ii].y-8, 10, 14);
						fillellipse(Chest_Figures[i][ii].x, Chest_Figures[i][ii].y+5, 8, 8);
						pieslice(Chest_Figures[i][ii].x, Chest_Figures[i][ii].y+23, 0, 180, 16);
					}
					//Конь(Флажок)
					if(Chest_Figures[i][ii].Type[0] == 'H')
					{
						int Horse_Points[8];
						Horse_Points[0] = Chest_Figures[i][ii].x;
						Horse_Points[1] = Chest_Figures[i][ii].y;
						Horse_Points[2] = Chest_Figures[i][ii].x;
						Horse_Points[3] = Chest_Figures[i][ii].y-20;
						Horse_Points[4] = Chest_Figures[i][ii].x-20;
						Horse_Points[5] = Chest_Figures[i][ii].y-10;
						Horse_Points[6] = Horse_Points[0];
						Horse_Points[7] = Horse_Points[1];
						fillpoly(4, Horse_Points);
						bar3d(Chest_Figures[i][ii].x, Chest_Figures[i][ii].y-20, Chest_Figures[i][ii].x+10, Chest_Figures[i][ii].y+13, 0, 0);
						bar3d(Chest_Figures[i][ii].x-10, Chest_Figures[i][ii].y+13, Chest_Figures[i][ii].x+20, Chest_Figures[i][ii].y+18, 0, 0);
					}
					//Королева и Король
					if(Chest_Figures[i][ii].Type[0] == 'Q' || Chest_Figures[i][ii].Type[0] == 'K')
					{
						int Crown_Points[16];
						Crown_Points[0] = Chest_Figures[i][ii].x-12;
						Crown_Points[1] = Chest_Figures[i][ii].y-4;
						Crown_Points[2] = Chest_Figures[i][ii].x-12;
						Crown_Points[3] = Chest_Figures[i][ii].y-18;
						Crown_Points[4] = Chest_Figures[i][ii].x-6;
						Crown_Points[5] = Chest_Figures[i][ii].y-12;
						Crown_Points[6] = Chest_Figures[i][ii].x;
						Crown_Points[7] = Chest_Figures[i][ii].y-18;
						Crown_Points[8] = Chest_Figures[i][ii].x+6;
						Crown_Points[9] = Chest_Figures[i][ii].y-12;
						Crown_Points[10] = Chest_Figures[i][ii].x+12;
						Crown_Points[11] = Chest_Figures[i][ii].y-18;
						Crown_Points[12] = Chest_Figures[i][ii].x+12;	
						Crown_Points[13] = Chest_Figures[i][ii].y-4;
						Crown_Points[14] = Crown_Points[0];
						Crown_Points[15] = 	Crown_Points[1];
						pieslice(Chest_Figures[i][ii].x+1, Chest_Figures[i][ii].y+8, 0, 180, 13);
						pieslice(Chest_Figures[i][ii].x+1, Chest_Figures[i][ii].y+23, 0, 180, 16);
						if(Chest_Figures[i][ii].Type[0] == 'Q')
						{
							setcolor(MAGENTA);
							setfillstyle(1, MAGENTA);
							fillpoly(8, Crown_Points);
						}
						if(Chest_Figures[i][ii].Type[0] == 'K')
						{
							setfillstyle(1, YELLOW);
							setcolor(YELLOW);
							fillpoly(8, Crown_Points);
							setfillstyle(1, RED);
							setcolor(RED);
							fillellipse(Chest_Figures[i][ii].x-5, Chest_Figures[i][ii].y-8, 4, 3);
							fillellipse(Chest_Figures[i][ii].x+6, Chest_Figures[i][ii].y-8, 4, 3);
						}
					}
				}
			}
		}
};

int main()
{
	Chest_Game Chest;
	Chest.Play();
	return 0;
}
