// You can modify the prototypes and update them in game.h.

#include <array>
#include <string>

#include "clockint.h"
#include "card.h"
#include "rule.h"
#include "game.h"

using namespace std;

template <int np> CardSet WinnerBasedGame<np>::playout_robot(ci<np> k) const {
	// int flag_ = 0, prim_ = 0, kick_ = 0, len_ = 0, val_;
	// int counter2 = 0;
	// int counter3 = 0;

	// int ok1 = 0;
	// int ok2 = 0;
	// //int prim = 0;
	// //int len = 0;
	// //int kick = 0;

	// CardSet c;

	// int sum[15] = {};                          //����ÿ�ֵ������м��ţ�sum[4]������Ϊ 4 ���Ƶ�������
	// for (int i = 1; i < 14; i++) {
	// 	for (int j = 0; j < 4; j++) {
	// 		sum[i] += cards[k].GetNum(j, i);
	// 	}
	// }
	// sum[0] = cards[k].GetNum(4, 0);
	// sum[14] = cards[k].GetNum(4, 14);

	// int fail = 0;

	// if (last.GetVal() + last.GetLen() < 15) {                         //�ж��ܷ񲻸ı� flag��ֻͨ���ı� val ��С������ 
	// 	for (val_ = last.GetVal() + 1; val_ + last.GetLen() <= 15; val_++) {              //�ı�valֵ 
	// 		int ok1 = 1;
	// 		for (int i = 0; i < last.GetLen(); i++) {                   //���� val��len��prim���ж� cards[k]���Ƿ����㹻���Ƴ䵱���� 
	// 			if (sum[val_ + i] < last.GetPrim()) {
	// 				ok1 = 0; break;                        //���ж�ѭ���У�����һ�β����㣬�������ж�ѭ��
	// 			}
	// 		}

	// 		//�����ж�ѭ����1.  �� val_ Ϊĳһֵʱ��cards[k]�����㹻���Ƴ䵱���ƣ���ѭ��ʱѭ��ȫ���꣬ ok1 = 1��
	// 		//              2.  �� val_ Ϊĳһֵʱ��cards[k]��û���㹻���Ƴ䵱���ƣ���ѭ��ʱѭ����һ��ȫ���� ��ok1 = 0��

	// 		if (ok1) {                              //����ok1ֵ�жϣ��� val_ Ϊĳһֵʱ�� cards[k]���Ƿ����㹻���Ƴ䵱����
	// 			int ok2 = 0; int k[2] = {};
	// 			if (!last.GetKick())break;          //��һ�������Ƿ��и��� ��1. �޸��ƣ���������ok����������� val_ ѭ���� 
	// 			else {                                         //2. �и��ƣ� ��������ok��ǰ���£��ж� cards[k]���Ƿ����㹻���Ƴ䵱���ƣ��������еĵ�����k[]��¼ 
	// 				for (int i = 1; i!= val_ && i < 14; i++) {
	// 					if (sum[i] >= last.GetPrim()) {
	// 						k[ok2] = i; ok2 = ok2 + 1;
	// 					}
	// 					if (ok2 == 2)break;
	// 				}
	// 			}
	// 			if (ok1 && ok2 == 2)break;           //2. �и��ƣ�����ok������ok�� ���� val_ ѭ����
	// 		}
	// 	}

	// 	//����val_ѭ�� ��1.  cards[k]�����㹻���Ƴ䵱���ƣ��޸��ƣ� ok1 = 1��ok2 = 0 ���ж�ѭ�����꣬δ���� ok1 �ж�
	// 	//               2.  cards[k]�����㹻���Ƴ䵱���ƣ��и��ƣ�cards[k]�����㹻���Ƴ䵱���ơ� ok1 = 1��ok2 = 2���ж�ѭ�����꣬���� ok1 �ж�
	// 	//               3.  cards[k]�����㹻���Ƴ䵱���ƣ��и��ƣ�cards[k]��û���㹻���Ƴ䵱���ơ� ok1 = 1��ok2 = 0 �� 1���ж�ѭ�����꣬���� ok1 �ж�
	// 	//               4.  cards[k]��û���㹻���Ƴ䵱���ƣ� ok1 = 0���ж�ѭ����һ�����꣬û�н� ok1 �ж�

	// 	if (ok1 && (ok2 == 0 && kick_ == 0 || ok2 == 2 && kick_)) {
	// 		flag_ = last.GetFlag();
	// 		prim_ = last.GetPrim();
	// 		kick_ = last.GetKick();
	// 		len_ = last.GetLen();

	// 		if (ok1 && ok2 == 0 && kick_ == 0) {                                      //�޸��ƣ�������� 
	// 			for (int i = val_; i < val_ + len_; i++) {
	// 				int counter1 = 0;
	// 				for (int j = 0; j < 4 && counter1 <= prim_; i++) {
	// 					c.Insert(j, i);
	// 					counter1++;
	// 				}
	// 			}
	// 		}
	// 		else {
	// 			for (int i = val_; i < val_ + len_; i++) {                               //�и��ƣ�������� 
	// 				int counter1 = 0, counter2 = 0, counter3 = 0;
	// 				for (int j =0 ; j < 4 && counter1 <= prim_; i++) {
	// 					c.Insert(j, i);
	// 					counter1++;
	// 				}
	// 			}
	// 			for (int j = 0; j < 4 && counter2 <= kick_; j++) { c.Insert(j, k); counter2++; }   //��ϸ���1 
	// 			for (int l = 0; l < 4 && counter3 <= kick_; l++) { c.Insert(l, k); counter3++; }   //��ϸ���2 
	// 		}
	// 	}
	// 	else fail = 1;
	// }

	// else if (last.GetVal() + last.GetLen() == 15 || fail == 1) {         //һ��ֻ��ͨ���ı� flag ��С������ 
	// 	switch (last.GetFlag()) {
	// 	case 1:
	// 		for (int i = 1; i < 14; i++) {             //���Ƿ����㹻�����ܹ���� bomb��4 
	// 			if (sum[i] == 4) {
	// 				flag_ = 4;
	// 				prim_ = 4;
	// 				kick_ = 0;
	// 				len_ = 1;
	// 				val_ = i; break;
	// 			}
	// 		}
	// 		if (len_)break;                     //�ҵ��ˣ������� switch-case ѭ�� ��û���ҵ�������� case 4
	// 	case 4:
	// 		for (int i = 1; i < 14; i++) {             //���Ƿ����㹻�����ܹ���� bomb��5 
	// 			if (sum[i] == 5) {
	// 				flag_ = 5;
	// 				prim_ = 5;
	// 				kick_ = 0;
	// 				len_ = 1;
	// 				val_ = i; break;
	// 			}
	// 		}
	// 		if (len_)break;                     //�ҵ��ˣ������� switch-case ѭ�� ��û���ҵ�������� case 5 

	// 	case 5:
	// 		for (int i = 1; i < 14; i++) {            //���Ƿ����㹻�����ܹ���� bomb��6 
	// 			if (sum[i] == 6) {
	// 				flag_ = 6;
	// 				prim_ = 6;
	// 				kick_ = 0;
	// 				len_ = 1;
	// 				val_ = i; break;
	// 			}
	// 		}
	// 		if (len_)break;
	// 		if (sum[0] >= 1 && sum[14] >= 1) {         //���Ƿ����㹻�����ܹ���� rocket 
	// 			flag_ = 6;
	// 			prim_ = 1;
	// 			kick_ = 0;
	// 			len_ = 2;
	// 			val_ = 16; break;
	// 		}
	// 		if (len_)break;
	// 	case 6:
	// 		for (int i = 1; i < 14; i++) {
	// 			if (sum[i] == 7) {
	// 				flag_ = 7;
	// 				prim_ = 7;
	// 				kick_ = 0;
	// 				len_ = 1;
	// 				val_ = i; break;
	// 			}
	// 		}
	// 		if (len_)break;                     //�ҵ��ˣ������� switch-case ѭ�� 
	// 	case 7:
	// 		for (int i = 1; i < 14; i++) {
	// 			if (sum[i] == 8) {
	// 				flag_ = 8;
	// 				prim_ = 8;
	// 				kick_ = 0;
	// 				len_ = 1;
	// 				val_ = i; break;
	// 			}
	// 		}
	// 		if (len_)break;                     //�ҵ��ˣ������� switch-case ѭ�� 
	// 	case 8:
	// 		if (sum[0] >= 2 && sum[14] >= 2) {         //���Ƿ����㹻�����ܹ���� nuke 
	// 			flag_ = 9;
	// 			prim_ = 1;
	// 			kick_ = 0;
	// 			len_ = 2;
	// 			val_ = 16; break;
	// 		}
	// 		if (len_)break;                      //�ҵ��ˣ������� switch-case ѭ�� 
	// 	case 9:
	// 		flag_ = pass; break;                   //�Ҳ����ɳ����ƣ�ѡ�񲻳��� ���� switch-case ѭ��
	// 	}
	// 	if (len_) {
	// 		for (int i = val_; i < val_ + len_; i++) {               //����� 
	// 			int counter = 0;
	// 			for (int j = 0; j < 4 && counter <= prim_; i++) {
	// 				c.Insert(j, i);
	// 				counter++;
	// 			}
	// 		}
	// 	}
	// }

	// return c;
	return CardSet();
}
// or make it pure virtual and implement the robots individually

int DouDizhuGame::bid_robot(ci<3> k) const { return 0; }

int SirenDouDizhuGame::bid_robot(ci<4> k) const { return 0; }
