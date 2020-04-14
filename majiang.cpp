#include "majiang.h"

Matrix matrix; //手牌标识
vector<Group> groups; 

bool complete(int row, bool group)
{
	//一副花色的牌是否完整 即可分解成N个顺或刻
	if (row< 0 || row> 4) {
        return false;
    }
		
	Card* suits = matrix[row];
	if (suits[0] == 0) {
        return true;
    }	

	//寻找第一张牌
	int j = 1;
	for (; j != NCOLS; ++j) {
		if (suits[j] != 0) {
            break;
        }	
	}

	//刻
	if (suits[j] >= 3)
	{
		suits[j] -= 3;
		suits[0] -= 3;

		if (group) {
            groups.push_back(Group(make_card(row, j), make_card(row, j), make_card(row, j)));
        }
		bool result = complete(row, group);

		suits[j] += 3;
		suits[0] += 3;
		if (!result && group) {
            groups.pop_back();
        }
			
		return result;
	}

	//顺子
	if (row < 3 && j < 8 && suits[j + 1] > 0 && suits[j + 2] > 0)
	{
		suits[j] -= 1;
		suits[j + 1] -= 1;
		suits[j + 2] -= 1;
		suits[0] -= 3;
		if (group) {
            groups.push_back(Group(make_card(row, j), make_card(row, j + 1), make_card(row, j + 2)));
        }
		bool result = complete(row, group);

		suits[j] += 1;
		suits[j + 1] += 1;
		suits[j + 2] += 1;
		suits[0] += 3;
		if (!result && group) {
            groups.pop_back();
        }
			
		return result;
	}
	return false;
}

bool can_hu(bool group, int start_nol) {
	if (group)
		groups.clear();

	int jrow = -1;  //包含将的行

	//满足3,3,3,3,2模型 
	for (int i = 0; i <= 4; ++i) {
		int rem = matrix[i][0] % 3;
		if (rem == 1) {
			return false;
		} else if (rem == 2) {
			if (jrow != -1) {  //除了将以外还有其他的将
                return false;
            }	
			jrow = i;
		}
	}

	//先计算没有将牌的花色
	for (int i = 0; i <=  4  ; ++i) {
		if (i != jrow){
			if (!complete(i, group)) {
                return false;
            }	
		}
	}

	//该列表中包含将牌，采用逐个测试方式
	//除掉将后能否通过
	bool success = false;
	Card* jsuits = matrix[jrow];

	for (int j = 1; j <= 9; ++j)
	{
		if (j <=  start_nol) continue; 

		if (jsuits[j] >= 2)
		{
			jsuits[j] -= 2;
			jsuits[0] -= 2;
			if (group) {
                groups.push_back(Group(make_card(jrow, j), make_card(jrow, j)));
            }

			success = complete(jrow, group);
			jsuits[j] += 2;
			jsuits[0] += 2;
			if (success) {
				break;
			}else {
				if (group) {
                    groups.pop_back();
                }
			}
		}
	}

	return success;
}

int check_hu(int *arr,int len) {
	if (len % 3 != 2)
		return  0;  
	if (len > 14 )
		return 0;

	memset(matrix, 0, sizeof(Matrix));
	for (int i = 0; i < len;  i++)
	{
		int face = get_face( arr[i]);
		int sui = get_suits(arr[i]);
		if (sui< 0 || sui> 4 || face< 0 || face> 9)
			return 0;


		matrix[sui][face]++;
		matrix[sui][0]++;
	}
	int ret = can_hu(true, 0);
	return ret; 
}

bool laizi_complete(int row, bool group, int &n_laizi)
{
	//一副花色的牌是否完整 即可分解成N个顺或刻
	if (row< 0 || row> 4)
		return false;

	Card* suits = matrix[row];
	if (suits[0] == 0)
		return true;

	//寻找第一张牌
	int j = 1;
	for (; j != NCOLS; ++j)
	{
		if (suits[j] != 0)
			break;
	}

	//刻
	if (suits[j] >= 3)
	{
		suits[j] -= 3;
		suits[0] -= 3; 
		if (group) {
            groups.push_back( Group(make_card(row, j), make_card(row, j), make_card(row, j)) );
        }
			
		bool result = laizi_complete(row, group, n_laizi);
		if (!result) {
			suits[j] += 3;
			suits[0] += 3;
			if (group) {
                groups.pop_back();
            }
		} else {
            return result;
        }	
	}

    //2张+1癞子 
	if (suits[j] >= 2 && n_laizi>= 1) {
		suits[j] -= 2;
		suits[0] -= 2; 
		n_laizi--;
		if (group) {
            groups.push_back( Group(make_card(row, j), make_card(row, j), MJ_LAZI));
        }
			
		bool result = laizi_complete(row, group, n_laizi);
		if (!result) {
			suits[j] += 2;
			suits[0] += 2;
			n_laizi++;
			if (group) {
                groups.pop_back();
            }
		} else {
            return result;
        }
	}

	//顺子
	if (row < 3 && j < 8 && suits[j + 1] > 0 && suits[j + 2] > 0)
	{
		suits[j] -= 1;
		suits[j + 1] -= 1;
		suits[j + 2] -= 1;
		suits[0] -= 3;
		if (group) {
            groups.push_back( Group(make_card(row, j), make_card(row, j + 1), make_card(row, j + 2)));
        }
			
		bool result = laizi_complete(row, group, n_laizi);
		if (!result)
		{
			suits[j] += 1;
			suits[j + 1] += 1;
			suits[j + 2] += 1;
			suits[0] += 3;
			if (group) {
                groups.pop_back();
            }
			
			return result;
		} else {
            return result;
        }	
	}

	//顺子 + 癞子
	if (row < 3 && j <= 8 && suits[j + 1] > 0 &&  n_laizi>= 1 )
	{
		suits[j] -= 1;
		suits[j + 1] -= 1; 
		suits[0] -= 2;
		n_laizi--;
		if (group) {
            groups.push_back( Group( make_card(row, j), make_card(row, j + 1),MJ_LAZI ));
        }
			
		bool result = laizi_complete(row, group , n_laizi);
		if (!result)
		{
			suits[j] += 1;
			suits[j + 1] += 1;
			suits[0] += 2;
			n_laizi++;
			if (group) {
                groups.pop_back();
            }
				
			return result;
		} else {
            return result;
        }	
	}


	//顺子+癞子
	if (row < 3 && j < 8 && suits[j + 2] > 0 && n_laizi >= 1)
	{
		suits[j] -= 1;
		suits[j + 2] -= 1;
		suits[0] -= 2;
		n_laizi--;
		if (group) {
            groups.push_back( Group(make_card(row, j), make_card(row, j + 2 ), MJ_LAZI));
        }
			
		bool result = laizi_complete(row, group, n_laizi);
		if (!result)
		{
			suits[j] += 1;
			suits[j + 2] += 1;
			suits[0] += 2;
			n_laizi++;
			if (group) {
                groups.pop_back();
            }
				
			return result;
		} else {
            return result;
        }	
	}

    // 一张+2癞子
	if (suits[j] >= 1 && n_laizi >= 2){
		suits[j] -= 1;
		suits[0] -= 1;
		n_laizi -= 2;
		if (group) {
            groups.push_back( Group( make_card(row, j), MJ_LAZI, MJ_LAZI));
        }
			
		bool result = laizi_complete(row, group, n_laizi);
		if (!result)
		{
			suits[j] += 1;
			suits[0] += 1;
			n_laizi += 2;
			if (group) {
                groups.pop_back();
            }
            
			return result;
		}else {
            return result;
        }
	}

	return false;
}

int laizi_can_hu(int *arr, int len, int n_lazi)
{
	if ((len + n_lazi) % 3 != 2) {
        return 0;
    }	
	
	if (n_lazi== 0 ) {
		memset(matrix, 0, sizeof(Matrix));
		for (int i = 0; i < len; i++)
		{
			int face = get_face(arr[i]);
			int sui = get_suits(arr[i]);
			if (sui< 0 || sui> 4 || face< 0 || face> 9)
				return 0;
			matrix[sui][face]++;
			matrix[sui][0]++;
		}
		return can_hu(1, 0);
	} else {
		map<int, int> all_map;
		for (int i = 0; i < len; i++)
			all_map[arr[i]]++;

		int  first_laizi = n_lazi;
		for (map<int, int>::iterator it = all_map.begin(); it != all_map.end(); ++it)
		{
			memset(matrix, 0, sizeof(Matrix));
			for (int i = 0; i < len; i++) {
				int face = get_face(arr[i]);
				int sui = get_suits(arr[i]);
				if (sui< 0 || sui> 4 || face< 0 || face> 9)
					return 0;
				matrix[sui][face]++;
				matrix[sui][0]++;
			}

            n_lazi = first_laizi;  
			int card = it->first; 
			int ct = it->second;
			if (ct >= 2) {
				int suit = get_suits(card);
				int face = get_face(card);
				matrix[suit][face] -= 2;
				matrix[suit][0] -= 2;

				int row = 0;
				bool canhu = true;
				groups.clear();
				for ( row = 0; row < 5 ; row++)
				{
					int ret = laizi_complete(row, true, n_lazi);
					if (ret <= 0) {
						canhu = 0;
						break;
					}
				} 
				
				if (canhu) {
                    return 1;
                }
					
				matrix[suit][face] += 2;
				matrix[suit][0] += 2;
			}
            // 一张牌+一张癞子作为将
            else if (ct == 1 && n_lazi >= 1)
			{
				int suit = get_suits(card);
				int face = get_face(card);
				matrix[suit][face] -= 1;
				matrix[suit][0] -= 1;
				n_lazi--;
				int row = 0;
				bool canhu = 1;
				groups.clear();
				for (row = 0; row < 5; row++)
				{
					int ret = laizi_complete(row, true, n_lazi);
					if (ret <= 0) { 
						canhu = 0;
						break;
					}
				}
				
				if (canhu ) {
                    return  1;
                }
					
				matrix[suit][face] += 1;
				matrix[suit][0] += 1;
				n_lazi++; 
			}
		}
	}
	return  0;
}