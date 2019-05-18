#ifndef DataStruct_h__
#define DataStruct_h__

typedef struct PosStruct{
	int x;
	int y;
} Pos;

enum GameStatus{
	PREPARE,
	PLAYING,
	PAUSING
};

#endif
