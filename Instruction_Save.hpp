#ifndef SJTU_SPIM_OPSAVE_HPP
#define SJTU_SPIM_OPSAVE_HPP

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

#include "Class.hpp"
#include "String_option.hpp"

using namespace std;

int readtype; // 0: .data, 1: .text

void op_data_save(string op){ // .xxxx
	int pos = 0, len = op.size();
	while(pos < len && (op[pos] == ' ' || op[pos] == '\t')) pos++;
	pos++;
	if(op[pos] == 'd') readtype = 0; else //.data
	if(op[pos] == 't') readtype = 1; else //.text
	if(op[pos] == 'b'){ //.byte
	} else 
	if(op[pos] == 'h'){ //.half
		pos += 4;
		op += ',';
		short Num = Atoi(Split_next(op, pos, ','));
		while(pos != -1){
			short *P = reinterpret_cast<short*>(data + nowdata);
			*P = Num;
			nowdata += 2;
			Num = Atoi(Split_next(op, pos, ','));
		}
	} else
	if(op[pos] == 's'){ //.space
		pos += 5;
		op += ' ';
		int n = Atoi(Split_next(op, pos, ' '));
		nowdata += n;
	} else
	if(op[pos] == 'w'){ //.word
		pos += 4;
		op += ',';
		int Num = Atoi(Split_next(op, pos, ','));
		while(pos != -1){
			int *P = reinterpret_cast<int*>(data + nowdata);
			*P = Num;
			nowdata += 4;
			Num = Atoi(Split_next(op, pos, ','));
		}
	} else
	if(op[pos] == 'a'){ 
		if(op[pos + 1] == 'l'){ //.align
			op += ' ';
			pos += 5;
			int n = Atoi(Split_next(op, pos, ' '));
			n = (1 << n);
			if(nowdata % n) 
				nowdata = (nowdata / n + 1) * n;
		} else
		if(op[pos + 5] == 'z'){ //.asciiz
			op += ' ';
			pos += 6;
			string Q = Split_string(op, pos);
			int len = Q.size();
			for(int j = 0; j < len; j++){
				if(Q[j] == '\\'){
					if(Q[j + 1] == '\\') data[nowdata++] = Q[j + 1]; 
					else if(Q[j + 1] == '\"') data[nowdata++] = Q[j + 1]; 
					else if(Q[j + 1] == 'n') data[nowdata++] = '\n';
					else if(Q[j + 1] == 't') data[nowdata++] = '\t';
					else if(Q[j + 1] == '0') data[nowdata++] = '\0';
					j++;
				}
				else data[nowdata++] = Q[j];
			}
			data[nowdata++] = '\0';
		} 
		else{ //.ascii
			op += ' ';
			pos += 5;
			string Q = Split_string(op, pos);
			int len = Q.size();
			for(int j = 0; j < len; j++){
				if(Q[j] == '\\'){
					if(Q[j + 1] == '\\') data[nowdata++] = Q[j + 1];
					else if(Q[j + 1] == '\"') data[nowdata++] = Q[j + 1];
					else if(Q[j + 1] == 'n') data[nowdata++] = '\n';
					else if(Q[j + 1] == 't') data[nowdata++] = '\t';
					else if(Q[j + 1] == '0') data[nowdata++] = '\0';
					j++;
				}
				else data[nowdata++] = Q[j];
			}
		}
	}	
}

void op_text_save(string op){ // Code
	int pos = 0, len = op.size(), top = 0;
	for(int i = 0; i < len; i++) if(op[i] == ',' || op[i] == '\t') op[i] = ' ';
	op += ' ';
	while(pos < len && (op[pos] == ' ' || op[pos] == '\t')) pos++;
	string option[6]; 
	while(pos != -1){
		option[top++] = Split_next(op, pos, ' ');
	}
	top--;
	code Q;
	string address, dx;
	if(option[0] == "add"){
		if(option[3][0] == '$') Q = code(1001, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3]));
		else Q = code(1002, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	}
	else if(option[0] == "addi") Q = code(1002, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	else if(option[0] == "and"){
		if(option[3][0] == '$') Q = code(3001, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3]));
		else  Q = code(3002, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	}
	else if(option[0] == "andi") Q = code(3002, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	else if(option[0] == "div"){
		if(top == 4){
			if(option[3][0] == '$')	Q = code(5001, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
			else Q = code(5002, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
		}	
		else Q = code(6, ts_to_num(option[1]), ts_to_num(option[2]));
	}
	else if(option[0] == "mul"){
		if(option[3][0] == '$') Q = code(7001, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3]));
		else Q = code(7002, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	}
	else if(option[0] == "mult") Q = code(8, ts_to_num(option[1]), ts_to_num(option[2])); 
	
	else if(option[0] == "neg") Q = code(9, ts_to_num(option[1]), ts_to_num(option[2])); 
	else if(option[0] == "nor"){
		if(option[3][0] == '$') Q = code(101, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3]));
		else Q = code(102, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	}
	else if(option[0] == "not") Q = code(11, ts_to_num(option[1]), ts_to_num(option[2])); 
	else if(option[0] == "or"){
		if(option[3][0] == '$') Q = code(121, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3]));
		else Q = code(122, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	}
	else if(option[0] == "ori") Q = code(13, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	else if(option[0] == "rem"){
		if(option[3][0] == '$') Q = code(141, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(142, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	else if(option[0] == "sub"){
		if(option[3][0] == '$') Q = code(151, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3]));
		else Q = code(152, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	} 
	else if(option[0] == "xor"){
		if(option[3][0] == '$') Q = code(161, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3]));
		else  Q = code(162, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	}
	else if(option[0] == "xori") Q = code(162, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	else if(option[0] == "li") Q = code(18, ts_to_num(option[1]), Atoi(option[2])); 
		
	else if(option[0] == "seq"){
		if(option[3][0] == '$') Q = code(191, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3]));
		else  Q = code(192, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	}
	else if(option[0] == "sge"){
		if(option[3][0] == '$') Q = code(201, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(202, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	else if(option[0] == "sgt"){
		if(option[3][0] == '$') Q = code(211, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(212, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	else if(option[0] == "sle"){
		if(option[3][0] == '$') Q = code(221, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3]));
		else Q = code(222, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	} 
	else if(option[0] == "slt"){
		if(option[3][0] == '$') Q = code(231, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(232, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	else if(option[0] == "slti") Q = code(232, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	else if(option[0] == "sne"){
		if(option[3][0] == '$') Q = code(251, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(252, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	
	else if(option[0] == "b") Q = code(26, 0, 0, 0, option[1]); 
	else if(option[0] == "beq"){
		if(option[2][0] == '$') Q = code(271, ts_to_num(option[1]), ts_to_num(option[2]), 0, option[3]); 
		else Q = code(272, ts_to_num(option[1]), Atoi(option[2]), 0, option[3]); 
	}
	else if(option[0] == "beqz") Q = code(272, ts_to_num(option[1]), 0, 0, option[2]); 
	else if(option[0] == "bge"){
		if(option[2][0] == '$') Q = code(291, ts_to_num(option[1]), ts_to_num(option[2]), 0, option[3]); 
		else Q = code(292, ts_to_num(option[1]), Atoi(option[2]), 0, option[3]); 
	}
	else if(option[0] == "bgez") Q = code(292, ts_to_num(option[1]), 0, 0, option[2]); 
	else if(option[0] == "bgezal") Q = code(31, ts_to_num(option[1]), 0, 0, option[2]);
	else if(option[0] == "bgt"){
		if(option[2][0] == '$') Q = code(321, ts_to_num(option[1]), ts_to_num(option[2]), 0, option[3]);
		else Q = code(322, ts_to_num(option[1]), Atoi(option[2]), 0, option[3]);
	}
	else if(option[0] == "bgtz") Q = code(322, ts_to_num(option[1]), 0, 0, option[2]);
	else if(option[0] == "ble"){
		if(option[2][0] == '$') Q = code(341, ts_to_num(option[1]), ts_to_num(option[2]), 0, option[3]); 
		else Q = code(342, ts_to_num(option[1]), Atoi(option[2]), 0, option[3]); 
	}
	else if(option[0] == "blez") Q = code(342, ts_to_num(option[1]), 0, 0, option[2]); 
	else if(option[0] == "bgezal") Q = code(36, ts_to_num(option[1]), 0, 0, option[2]); 
	else if(option[0] == "bltzal") Q = code(37, ts_to_num(option[1]), 0, 0, option[2]); 
	else if(option[0] == "blt"){
		if(option[2][0] == '$') Q = code(381, ts_to_num(option[1]), ts_to_num(option[2]), 0, option[3]); 
		else  Q = code(382, ts_to_num(option[1]), Atoi(option[2]), 0, option[3]); 
	}
	else if(option[0] == "bltz") Q = code(382, ts_to_num(option[1]), 0, 0, option[2]); 
	else if(option[0] == "bne"){
		if(option[2][0] == '$') Q = code(401, ts_to_num(option[1]), ts_to_num(option[2]), 0, option[3]); 
		else  Q = code(402, ts_to_num(option[1]), Atoi(option[2]), 0, option[3]); 
	}
	else if(option[0] == "bnez") Q = code(402, ts_to_num(option[1]), 0, 0, option[2]); 
	else if(option[0] == "j") Q = code(42, 0, 0, 0, option[1]); 
	else if(option[0] == "jal") Q = code(43, 0, 0, 0, option[1]); 
	else if(option[0] == "jalr") Q = code(44, ts_to_num(option[1])); 
	else if(option[0] == "jr") Q = code(45, ts_to_num(option[1]));
		
	else if(option[0] == "la") Q = code(46, ts_to_num(option[1]), 0, 0, option[2]); 
	else if(option[0] == "lb"){
		pos = 0; dx = Split_next(option[2], pos, '(');
		if(pos != -1){
			address = Split_next(option[2], pos, ')');
			Q = code(471, ts_to_num(option[1]), ts_to_num(address), Atoi(dx)); 
		}
		else Q = code(472, ts_to_num(option[1]), 0, 0, option[2]);
	}
	else if(option[0] == "lh"){
		pos = 0; dx = Split_next(option[2], pos, '(');
		if(pos != -1){
			address = Split_next(option[2], pos, ')');
			Q = code(481, ts_to_num(option[1]), ts_to_num(address), Atoi(dx)); 
		}
		else Q = code(482, ts_to_num(option[1]), 0, 0, option[2]);
	}
	else if(option[0] == "lw"){
		pos = 0; dx = Split_next(option[2], pos, '(');
		if(pos != -1){
			address = Split_next(option[2], pos, ')');
			Q = code(491, ts_to_num(option[1]), ts_to_num(address), Atoi(dx)); 
		}
		else Q = code(492, ts_to_num(option[1]), 0, 0, option[2]);
	}
	else if(option[0] == "sb"){
		pos = 0; dx = Split_next(option[2], pos, '(');
		if(pos != -1){
			address = Split_next(option[2], pos, ')');
			Q = code(501, ts_to_num(option[1]), ts_to_num(address), Atoi(dx)); 
		}
		else Q = code(502, ts_to_num(option[1]), 0, 0, option[2]);
	}
	else if(option[0] == "sw"){
		pos = 0; dx = Split_next(option[2], pos, '(');
		if(pos != -1){
			address = Split_next(option[2], pos, ')');
			Q = code(511, ts_to_num(option[1]), ts_to_num(address), Atoi(dx)); 
		}
		else Q = code(512, ts_to_num(option[1]), 0, 0, option[2]);
	}
	
	else if(option[0] == "move") Q = code(52, ts_to_num(option[1]), ts_to_num(option[2])); 
	else if(option[0] == "mfhi") Q = code(53, ts_to_num(option[1])); 
	else if(option[0] == "mflo") Q = code(54, ts_to_num(option[1])); 
	else if(option[0] == "nop") Q = code(55); 
	else if(option[0] == "syscall") Q = code(56); 
	
	else if(option[0] == "sll"){
		if(option[3][0] == '$') Q = code(571, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(572, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	else if(option[0] == "sra"){
		if(option[3][0] == '$') Q = code(581, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(582, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	else if(option[0] == "srl"){
		if(option[3][0] == '$') Q = code(591, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(592, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	
	else if(option[0] == "subu"){
		if(option[3][0] == '$') Q = code(601, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(602, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	
	else if(option[0] == "addu"){
		if(option[3][0] == '$') Q = code(611, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(612, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}

	Code.push_back(Q);
}

void op_save(string op){
	int pos = 0, len = op.size();
	while(pos < len && (op[pos] == ' ' || op[pos] == '\t')) pos++;
	if(pos >= len || op[pos] == '#') return;
	if(op[pos] != '.' && Find(op, ':')){
		string lab = "";
		for(int i = pos; i < len; i++){
			if(op[i] == ':'){
				pos = i; break;
			}
			lab += op[i];
		}
		label_to_num[lab] = Code_label.size();
		if(readtype == 0) Code_label.push_back(label(0, nowdata));
		else Code_label.push_back(label(1, Code.size()));
		lab = "";
		for(int i = pos + 1; i < len; i++) lab += op[i];
		op_save(lab); 
		return;
	}
	if(op[pos] == '.') op_data_save(op);
	else op_text_save(op);
}

#endif

