#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

class Game_live {
	private:
		bool fm[23][79], sm[23][79];
	public:
		Game_live(int n) {
			Create_first_day(n);
		}
		
		void Create_first_day(int n) {
			srand(time(NULL));
			for(int i=0; i<23; i++)
				for(int ii=0; ii<79; ii++) {
					fm[i][ii] = false;
					sm[i][ii] = false;
				}
			for(int i=0; i<n; i++) {
				int a1 = rand()%23, a2 = rand()%79;
				fm[a1][a2] = true;
			}
			
			ReCreation_world();
		}
		
		bool Destroy_or_not_universe() {
			for(int i=0; i<23; i++)
				for(int ii=0; ii<79; ii++) {
					if(fm[i][ii]) return true;
				}
			return false;
		}
		
		void Create_another_day() {
			int Can_live = 0, *cl = 0;
			cl = &Can_live;
			if(cl) {
				for(int i=0; i<23; i++)
					for(int ii=0; ii<79; ii++) {
						if(i==0) {
							if(ii==0) {
								if(fm[i][ii+1]) *cl+=1;
								if(fm[i+1][ii]) *cl+=1;
								if(fm[i+1][ii+1]) *cl+=1;
							}
							if(ii==78) {
								if(fm[i][ii-1]) *cl+=1;
								if(fm[i+1][ii-1]) *cl+=1;
								if(fm[i+1][ii]) *cl+=1;
							}
							else {
								if(fm[i][ii-1]) *cl+=1;
								if(fm[i][ii+1]) *cl+=1;
								if(fm[i+1][ii-1]) *cl+=1;
								if(fm[i+1][ii]) *cl+=1;
								if(fm[i+1][ii+1]) *cl+=1;
							}
							if(*cl == 3) sm[i][ii] = true;
							if(*cl == 2 && fm[i][ii]) sm[i][ii] = true;
							*cl = 0;
							continue;
						}
						if(i==22) {
							if(ii==0) {
								if(fm[i-1][ii]) *cl+=1;
								if(fm[i-1][ii+1]) *cl+=1;
								if(fm[i][ii+1]) *cl+=1;
							}
							if(ii==(78)) {
								if(fm[i-1][ii-1]) *cl+=1;
								if(fm[i-1][ii]) *cl+=1;
								if(fm[i][ii-1]) *cl+=1;
							}
							else {
								if(fm[i-1][ii-1]) *cl+=1;
								if(fm[i-1][ii]) *cl+=1;
								if(fm[i-1][ii+1]) *cl+=1;
								if(fm[i][ii-1]) *cl+=1;
								if(fm[i][ii+1]) *cl+=1;
							}
							if(*cl == 3) sm[i][ii] = true;
							if(*cl == 2 && fm[i][ii]) sm[i][ii] = true;
							*cl = 0;
							continue;
						}
						if(ii==0) {
							if(fm[i-1][ii]) *cl+=1;
							if(fm[i-1][ii+1]) *cl+=1;
							if(fm[i][ii+1]) *cl+=1;
							if(fm[i+1][ii]) *cl+=1;
							if(fm[i+1][ii+1]) *cl+=1;
							if(*cl == 3) sm[i][ii] = true;
							if(*cl == 2 && fm[i][ii]) sm[i][ii] = true;
							*cl = 0;
							continue;
						}
						if(ii==78) {
							if(fm[i-1][ii-1]) *cl+=1;
							if(fm[i-1][ii]) *cl+=1;
							if(fm[i][ii-1]) *cl+=1;
							if(fm[i+1][ii-1]) *cl+=1;
							if(fm[i+1][ii]) *cl+=1;
							if(*cl == 3) sm[i][ii] = true;
							if(*cl == 2 && fm[i][ii]) sm[i][ii] = true;
							*cl = 0;
							continue;
						}
						else {
							if(fm[i-1][ii-1]) *cl+=1;
							if(fm[i-1][ii]) *cl+=1;
							if(fm[i-1][ii+1]) *cl+=1;
							if(fm[i][ii-1]) *cl+=1;
							if(fm[i][ii+1]) *cl+=1;
							if(fm[i+1][ii-1]) *cl+=1;
							if(fm[i+1][ii]) *cl+=1;
							if(fm[i+1][ii+1]) *cl+=1;
							if(*cl == 3) sm[i][ii] = true;
							if(*cl == 2 && fm[i][ii]) sm[i][ii] = true;
							*cl = 0;
							continue;
						}
					}
				for(int i=0; i<23; i++)
					for(int ii=0; ii<79; ii++) {
						fm[i][ii] = sm[i][ii];
						sm[i][ii] = false;
					}
				ReCreation_world();
			}
		}
		
		void ReCreation_world() {
			system("cls");
			for(int i=0; i<23; i++) {
				for(int ii=0; ii<79; ii++) {
					if(fm[i][ii]) std::cout << '*';
					else std::cout << ' ';
				}
				std::cout << '\n';
			}
		}
		
		~Game_live() {
			std::cout << "All life death\nBye bye\n";
		}
};

int main()
{
	int n;
	std::cin >> n;
	Game_live God(n);
	bool Universe_live = true;
	while(Universe_live) {
		Universe_live = God.Destroy_or_not_universe();
		Sleep(300);
		God.Create_another_day();
	}
	system("cls");
	return 0;
}
