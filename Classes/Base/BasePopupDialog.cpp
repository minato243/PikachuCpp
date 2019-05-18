#include "deprecated\CCDeprecated.h"
#include "BasePopupDialog.h"


BasePopupDialog::BasePopupDialog(){
	

	/*cc.eventManager.addListener({
		event: cc.EventListener.TOUCH_ONE_BY_ONE,
		swallowTouches : true,
		onTouchBegan : function(touch, event){
		return true;
		}

		onTouchMoved : function(touch, event){

		}
		onTouchEnded : function(touch, evnt)

		}
		} this);*/
}


BasePopupDialog::~BasePopupDialog()
{

}

void BasePopupDialog::onEnter(){
	CCLOG("BasePopupDialog::onEnter");
	Layer::onEnter();
	auto action = CCSequence::create(CCScaleTo::create(0, 0.5), CCScaleTo::create(0.2, 1.2), CCScaleTo::create(0.2, 1), NULL);
	this->runAction(action);
}

void BasePopupDialog::onExit(){
	CCLOG("BasePopupDialog::onExit");
	Layer::onExit();
}

void BasePopupDialog::closeDialog(){
	CCLOG("BasePopupDialog::closeDialog");
	auto action = CCSequence::create(CCScaleTo::create(0.18, 1.12), CCCallFunc::create(this, CC_CALLFUNC_SELECTOR(BasePopupDialog::_removeFromParent)), NULL);
	this->runAction(action);
}

void BasePopupDialog::_removeFromParent(){
	CCLOG("BasePopupDialog::_removeFromParent");
	this->stopAllActions();
	this->removeFromParent();
	//ScreenMgr.getInstance().currentScreen.removeChild(this);
}

BasePopupDialog *dialogInstance = NULL;
BasePopupDialog *BasePopupDialog::getInstance(){
	if (dialogInstance == NULL){
		dialogInstance = new BasePopupDialog();
		dialogInstance->retain();
	}
	return dialogInstance;
}



