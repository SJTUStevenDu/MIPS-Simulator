#ifndef SJTU_SPIM_DECODE_CLASS_HPP
#define SJTU_SPIM_DECODE_CLASS_HPP

#include <iostream>
#include <map>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#include "Class.hpp"

using namespace std;

bool Solve_step_Decode(flow &X, bool &Canread, int &now){
	int lab, *sw, pw, len;
	unsigned int uv, uw;
	char pb;
	short ph, *sh;
	long long sl, pl;
	switch(X.op){
		case 1001: // add TS
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B] + TS[X.C];
			break;
		case 1002: // add i
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B] + X.C;
			break;
		case 3001: // and TS
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (TS[X.B] & TS[X.C]);
			break;
		case 3002: // and i
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (TS[X.B] & X.C);
			break;
		case 5001: // div TS
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B] / TS[X.C];
			break;
		case 5002: // div i
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B] / X.C;
			break;
		case 6: //div tow TS
			if(lock[X.A] || lock[X.B]) return 0;
			++lock[32]; ++lock[33];
			X.to_ts[X.top] = 33; X.to_data[X.top++] = TS[X.A] / TS[X.B];
			X.to_ts[X.top] = 32; X.to_data[X.top++] = TS[X.A] % TS[X.B];
			break;
		case 7001: //mul TS
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B] * TS[X.C];
			break;
		case 7002: //mul i
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B] * X.C;
			break;
		case 9: // neg
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = -TS[X.B];
			break;
		case 141: // rem TS
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B] % TS[X.C];
			break;
		case 142: // rem i
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B] % X.C;
			break;
		case 151: // sub TS
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B] - TS[X.C];
			break;
		case 152: //sub i
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B] - X.C;
			break;
		case 161: // xor TS
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (TS[X.B] ^ TS[X.C]);
			break;
		case 162: // xor i
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (TS[X.B] ^ X.C);
			break;
		case 18: // li
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = X.B;
			break;
			
		case 191: // seq TS
			if(lock[X.B] || lock[X.C]) return 0;
			lab = (TS[X.B] == TS[X.C]) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case 192: // seq i
			if(lock[X.B]) return 0;
			lab = (TS[X.B] == X.C) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case 201: // sge TS
			if(lock[X.B] || lock[X.C]) return 0;
			lab = (TS[X.B] >= TS[X.C]) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case 202: // sge i
			if(lock[X.B]) return 0;
			lab = (TS[X.B] >= X.C) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case 211: // sgt TS
			if(lock[X.B] || lock[X.C]) return 0;
			lab = (TS[X.B] > TS[X.C]) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case 212: // sgt i
			if(lock[X.B]) return 0;
			lab = (TS[X.B] > X.C) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case 221: // sle TS
			if(lock[X.B] || lock[X.C]) return 0;
			lab = (TS[X.B] <= TS[X.C]) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case 222: // sle i
			if(lock[X.B]) return 0;
			lab = (TS[X.B] <= X.C) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case 231: // slt TS
			if(lock[X.B] || lock[X.C]) return 0;
			lab = (TS[X.B] < TS[X.C]) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case 232: // slt i
			if(lock[X.B]) return 0;
			lab = (TS[X.B] < X.C) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case 251: // sne TS
			if(lock[X.B] || lock[X.C]) return 0;
			lab = (TS[X.B] != TS[X.C]) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case 252: // sne i
			if(lock[X.B]) return 0;
			lab = (TS[X.B] != X.C) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
			
		case 26: // b label
			Canread = 0; X.isjump = 1;
			lab = label_to_num[X.lab]; lab = Code_label[lab].x;
			now = lab;
			break;
		case 271: // beq TS
			if(lock[X.A] || lock[X.B]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] == TS[X.B]){
				lab = label_to_num[X.lab]; lab = Code_label[lab].x;
				now = lab;
			}
			break; 
		case 272: // beq i
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] == X.B){
				lab = label_to_num[X.lab]; lab = Code_label[lab].x;
				now = lab;
			}
			break; 
		case 291: // bge TS
			if(lock[X.A] || lock[X.B]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] >= TS[X.B]){
				lab = label_to_num[X.lab]; lab = Code_label[lab].x;
				now = lab;
			}
			break; 
		case 292: // bge i
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] >= X.B){
				lab = label_to_num[X.lab]; lab = Code_label[lab].x;
				now = lab;
			}
			break;
		case 321: // bgt TS
			if(lock[X.A] || lock[X.B]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] > TS[X.B]){
				lab = label_to_num[X.lab]; lab = Code_label[lab].x;
				now = lab;
			}
			break; 
		case 322: // bgt i
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] > X.B){
				lab = label_to_num[X.lab]; lab = Code_label[lab].x;
				now = lab;
			}
			break;
		case 341: // ble TS
			if(lock[X.A] || lock[X.B]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] <= TS[X.B]){
				lab = label_to_num[X.lab]; lab = Code_label[lab].x;
				now = lab;
			}
			break; 
		case 342: // ble i
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] <= X.B){
				lab = label_to_num[X.lab]; lab = Code_label[lab].x;
				now = lab;
			}
			break;
		case 381: // blt TS
			if(lock[X.A] || lock[X.B]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] < TS[X.B]){
				lab = label_to_num[X.lab]; lab = Code_label[lab].x;
				now = lab;
			}
			break; 
		case 382: // blt i
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] < X.B){
				lab = label_to_num[X.lab]; lab = Code_label[lab].x;
				now = lab;
			}
			break;
		case 401: // bne TS
			if(lock[X.A] || lock[X.B]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] != TS[X.B]){
				lab = label_to_num[X.lab]; lab = Code_label[lab].x;
				now = lab;
			}
			break; 
		case 402: // bne i
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] != X.B){
				lab = label_to_num[X.lab]; lab = Code_label[lab].x;
				now = lab;
			}
			break;
		case 42: // j label
			Canread = 0; X.isjump = 1;
			lab = label_to_num[X.lab]; lab = Code_label[lab].x;
			now = lab;
			break;
		case 43: // jal
			Canread = 0; X.isjump = 1;
			++lock[31];
			X.to_ts[X.top] = 31; X.to_data[X.top++] = now;
			lab = label_to_num[X.lab]; lab = Code_label[lab].x;
			now = lab;
			break;
		case 44: // jalr
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			++lock[31];
			X.to_ts[X.top] = 31; X.to_data[X.top++] = now;
			now = TS[X.A];
			break;
		case 45: // jr
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			now = TS[X.A];
			break;
		case 52: // move
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B];
			break;
		case 53: //mfhi
			if(lock[32]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[32];
			break;
		case 54: //mflo
			if(lock[33]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[33];
			break;
		case 56: // syscall
			if(lock[2]) return 0;
			switch(TS[2]){
				case 1: // print word
					if(lock[4]) return 0;
					printf("%d", TS[4]);
					break;
				case 4: // print string
					if(lock[4]) return 0;
					for(int j = TS[4]; ; j++){
						if(data[j] == '\0') break;
						putchar(data[j]);
					}
					break;
				case 5: // read word
					scanf("%d", &pw);
					lock[2]++;
					X.to_ts[X.top] = 2; X.to_data[X.top++] = pw;
					break;
				case 8: // read string
					if(lock[4] || lock[5]) return 0;
					scanf("%s", &Read_string);
					len = strlen(Read_string);
					pw = TS[4];
					for(int j = 0; j < len; j++) 
						data[pw++] = Read_string[j];
					data[pw] = '\0';
					break;
				case 9: // heap memory
					if(lock[4]) return 0;
					lock[2]++;
					X.to_ts[X.top] = 2; X.to_data[X.top++] = nowheap;
					nowheap += TS[4];
					break;
				case 10: // end
					lock[35]++;
					X.to_ts[X.top] = 35; X.to_data[X.top++] = 1;
					break;
				case 17: // end with return num
					if(lock[4]) return 0;
					retu = TS[4];
					lock[35]++;
					X.to_ts[X.top] = 35; X.to_data[X.top++] = 1;
					break;
			}
			Canread = 0; X.isjump = 1;
			break;
			
		case 46: //la 
			++lock[X.A]; break; 
		case 471: //lb dx
			++lock[X.A]; break; 
		case 472: //lb label
			++lock[X.A]; break; 
		case 481: //lh dx
			++lock[X.A]; break; 
		case 482: //lh label
			++lock[X.A]; break; 
		case 491: //lw dx
			++lock[X.A]; break; 
		case 492: //lw label
			++lock[X.A]; break; 
		case 501: //sb dx
			if(lock[X.A] || lock[X.B]) return 0;
			break;
		case 502: //sb label
			if(lock[X.A]) return 0;
			break;
		case 511: //sw dx
			if(lock[X.A] || lock[X.B]) return 0;
			break;
		case 512: //sw label
			if(lock[X.A]) return 0;
			break;
		case 601: //subu TS
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			uv = TS[X.B]; uw = TS[X.C];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = uv - uw;
			break;
		case 602: //subu i
			if(lock[X.B]) return 0;
			++lock[X.A];
			uv = TS[X.B]; uw = X.C;
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = uv - uw;
			break;
		case 611: //addu TS
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			uv = TS[X.B]; uw = TS[X.C];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = uv + uw;
			break;
		case 612: //addu i
			if(lock[X.B]) return 0;
			++lock[X.A];
			uv = TS[X.B]; uw = X.C;
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = uv + uw;
			break;
				
	}
	return 1;
}

int Solve_step_Memory(flow &X){
	int lab, *sw, pw;
	char S;
	short ph, *sh;
	switch(X.op){
		// 46 - 49 load
		case 46: //la 
			lab = label_to_num[X.lab];
			lab = Code_label[lab].x;
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			return 1; 
		case 471: //lb dx
			lab = TS[X.B] + X.C;
			S = data[lab];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = S;
			return 1; 
		case 472: //lb label
			lab = label_to_num[X.lab];
			lab = Code_label[lab].x;
			S = data[lab];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = S;
			return 1;
		case 481: //lh dx
			lab = TS[X.B] + X.C;
			sh = reinterpret_cast<short*>(data + lab);
			ph = *sh;
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = ph;
			return 1;
		case 482: //lh label
			lab = label_to_num[X.lab];
			lab = Code_label[lab].x;
			sh = reinterpret_cast<short*>(data + lab);
			ph = *sh;
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = ph;
			return 1;
		case 491: //lw dx
			lab = TS[X.B] + X.C;
			sw = reinterpret_cast<int*>(data + lab);
			pw = *sw;
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = pw;
			return 1;
		case 492: //lw label
			lab = label_to_num[X.lab];
			lab = Code_label[lab].x;
			sw = reinterpret_cast<int*>(data + lab);
			pw = *sw;
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = pw;
			return 1;
		// 50 - 51 save
		case 501: //sb dx
			lab = TS[X.B] + X.C;
			S = TS[X.A];
			data[lab] = S;
			return 1;
		case 502: //sb label
			lab = label_to_num[X.lab];
			lab = Code_label[lab].x;
			S = TS[X.A];
			data[lab] = S;
			return 1;
		case 511: //sw dx
			lab = TS[X.B] + X.C;
			sw = reinterpret_cast<int*>(data + lab);
			*sw = TS[X.A];
			return 1;
		case 512: //sw label
			lab = label_to_num[X.lab];
			lab = Code_label[lab].x;
			sw = reinterpret_cast<int*>(data + lab);
			*sw = TS[X.A];
			return 1;
	}
	return 0;
}

#endif
