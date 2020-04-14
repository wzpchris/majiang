#ifndef __MAJIANG_H__
#define __MAJIANG_H__
/*
   赖子 和非赖子。胡牌接口。
*/

#include <iostream>
#include <vector> 
#include <map>
#include <stdio.h>
#include <string.h>
using namespace std;


#define  MJ_LAZI   0x70

typedef  int  Card;
typedef unsigned char _uint8;

static const int NROWS = 6;
static const int NCOLS = 10;

typedef Card Matrix[NROWS][NCOLS];  //每行下标为0的表示该行的个数


inline int get_suits(Card c)
{
	return c >> 4;
}

inline int get_face(Card c)
{
	return c & 0x0F;
}

inline Card make_card(int row, int col)
{
	return row * 0x10 + col;
}

class Group {
public:
	Group(Card j1, Card j2) {
		elems.push_back(j1);
		elems.push_back(j2);
	}

	Group(Card c1, Card c2, Card c3) {
		elems.push_back(c1);
		elems.push_back(c2);
		elems.push_back(c3);
	}

	size_t size() const {
		return elems.size();
	}

	Card first() const {
		return elems[0];
	}

	Card second() const {
		return elems[1]; 
	}

	Card third() const {
		return elems[2];
	}

	bool isKe() const {
		size_t  size = elems.size(); 
		map<int,int> mp;
		for(size_t i = 0; i < size; ++i) {
			if(elems[i]== 0x70) continue;
			mp[elems[i]]++; 
		}
		return  mp.size() == 1 && size == 3; 				
	}

	bool isShun() const {
		return elems.size() == 3 && elems.front() != elems.back();
	}

	bool isJiang() const {
		return elems.size() == 2 && elems.front() == elems.back();
	}
private:
	std::vector<Card> elems;
};

int check_hu( int *arr, int len);
// 癞子的接口
int laizi_can_hu( int *arr, int len, int n_lazi);
#endif 