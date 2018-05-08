#include <iostream>
#include <map>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <fstream>

#include "Class.hpp"
#include "Decode.hpp"
#include "String_option.hpp"
#include "Instruction_Save.hpp"

using namespace std;

void Flow_and_work(){
	bool Canread = 1, havedone, flag;
	int T, ty, LL = Code.size(), now = label_to_num["main"]; // where next instuct is
	now = Code_label[now].x;
	TS[29] = stacktop;
	F[0].exist = 1;	
	/*for(T = 1; ; T++){
		havedone = 0; flag = 0; 
		for(int x = 4; x >= 0; x--){
			if(F[x].exist){
				switch(x){
					case 4:
						for(int i = 0; i < F[4].top; i++){
							TS[F[4].to_ts[i]] = F[4].to_data[i];
							--lock[F[4].to_ts[i]];
						}
						F[4].exist = 0;
						if(F[4].isjump) Canread = 1;
						if(TS[35]) return;
						break;
					case 3:
						ty = Solve_step4(F[3]);
						if(ty != -1){
							if(ty == 1) havedone = 1;
							F[3].exist = 0;			
							F[x + 1] = F[x]; F[x + 1].exist = 1;
						}
						else flag = 1;
						break;
					case 2:
						F[2].exist = 0; F[x + 1] = F[x]; F[x + 1].exist = 1;
						break;
					case 1:
						if(Solve_step2(F[1], Canread, now)){
							F[1].exist = 0; F[x + 1] = F[x]; F[x + 1].exist = 1;
						}
						else flag = 1;
						break;
					case 0:
						if(Canread && !havedone && now < LL){
							code np = Code[now];
							now++;
							F[1] = flow(np.op, np.A, np.B, np.C, np.lab);
							F[1].exist = 1;
						}
						break;	
				}
			}
			if(flag) break;
		}
	}*/
	while(1){
		code np = Code[now];
		now++;
		F[1] = flow(np.op, np.A, np.B, np.C, np.lab);
		if(!Solve_step_Decode(F[1], Canread, now)) break;
		Solve_step_Memory(F[1]);
		for(int i = 0; i < F[1].top; i++){
			TS[F[1].to_ts[i]] = F[1].to_data[i];
			--lock[F[1].to_ts[i]];
		}
		if(TS[35]) return;
	}
}

int main(int argc, char* argv[]){
	Prework();
	string option;	
	//ifstream fin("test.s");
	ifstream fin(argv[1]);		
	while(getline(fin, option)){
		op_save(option);
	}
	fin.close();
	//freopen("test.ans", "w", stdout);
	Flow_and_work();	
	/*for(int i = 0; i < Code.size(); i++){
		Code[i].print();
	}*/
	/*for(int i = 0; i < nowdata; i++){
		cout << i << " " << data[i] << " " << (int)(data[i]) << endl;
	}*/
	/*for(int i = 0; i < Code_label.size(); i++){
		cout << i << " " << Code_label[i].ty << " " << Code_label[i].x << endl;
	}*/
	return retu;
}

