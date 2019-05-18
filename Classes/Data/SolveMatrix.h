#ifndef SolveMatrix_h__
#define SolveMatrix_h__

#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

class SolveMatrix{
public:
	
	static vector<int> createCardCountMatrix(int iconNum, int imageNum);
	static vector<vector<int>> createMatrix(vector<int> cardCount, int imageNo, int height, int width);
};
#endif
