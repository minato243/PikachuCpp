#ifndef BasePopupDialog_h__
#define BasePopupDialog_h__

#include "cocos2d.h"

USING_NS_CC;

class BasePopupDialog : public Layer{
public:
	BasePopupDialog();
	~BasePopupDialog();

	virtual void onEnter();
	virtual void onExit();

	void closeDialog();
	void _removeFromParent();

	static BasePopupDialog *getInstance();

};

#endif