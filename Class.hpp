#ifndef SJTU_SPIM_CLASS_HPP
#define SJTU_SPIM_CLASS_HPP

#include <iostream>
#include <map>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <unordered_map>

using namespace std;

int stacktop = 1000000000;

int nowdata = 0, nowheap = 300000000;

char *data; // datatop up, stacktop down

void Prework(){
	data = (char *)malloc(1000000006 * sizeof(char));
}

struct code{
	int op, A, B, C;
	string lab;
	
public:
	
	code(int _op = 0, int _A = 0, int _B = 0, int _C = 0, string _lab = "") : op(_op), A(_A), B(_B), C(_C), lab(_lab) {}
	
	print(){
		cout << op << " " << A << " " << B << " " << C << " " << lab << endl;
	}	
	
};

struct label{
	int ty, x; //ty: 0 -> .data, 1 -> .text
	label(int _ty = 0, int _x = 0) : ty(_ty), x(_x) {}
};

std::unordered_map<string, int> label_to_num;
std::vector<code> Code;
std::vector<label> Code_label;

int TS[36]; // register, high:32, low:33, 35: 1 the program ends
int lock[36], retu;
char Read_string[3000010];

struct flow{
	int op, A, B, C, top;
	int to_ts[3], to_data[3];
	string lab;
	bool exist, isjump;
	flow(int _op = 0, int _A = 0, int _B = 0, int _C = 0, string _lab = "") : op(_op), A(_A), B(_B), C(_C), lab(_lab) {
		top = 0; exist = 0; isjump = 0;
		memset(to_ts, 0, sizeof(to_ts));
		memset(to_data, 0, sizeof(to_data));
	}
}F[5];
//0: IF, 1:Decode && Getdata, 2:Calc, 3:Memory Access, 4:Write Back

#endif

