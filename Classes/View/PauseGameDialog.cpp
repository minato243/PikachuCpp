#include "proj.win32\PauseGameDialog.h"
#include "cocostudio\ActionTimeline\CSLoader.h"
#include "SceneManager.h"
#include "Base\GameConstant.h"

PauseGameDialog *pauseGameDialogInstance = NULL;

bool PauseGameDialog::init()
{
	if (!BasePopupDialog::init())
		return false;
	Node* node = CSLoader::createNode("PauseGameDialog.csb");
	this->addChild(node);
	this->bgImage = node->getChildByName("bgImage");
	auto bgImage = this->bgImage;
	auto bgMessage = bgImage->getChildByName("bg_message");

	ui::Button *restartButton = dynamic_cast<ui::Button *>(bgImage->getChildByName("btn_accept"));
	restartButton->addClickEventListener(CC_CALLBACK_1(PauseGameDialog::onRestart, this));
	ui::Button *cancelButton = dynamic_cast<ui::Button *>(bgImage->getChildByName("btn_cancel"));
	cancelButton->addClickEventListener(CC_CALLBACK_1(PauseGameDialog::onCancel, this));
	
	return true;	
}

void PauseGameDialog::startDialog(PlayScene *parent)
{
	this->playLayer = parent;

	if (this->getParent() != NULL) {
		this->_removeFromParent();
	}
	SceneManager::getInstance()->currentScene->addChild(this, LAYER_DIALOG);

}

void PauseGameDialog::_removeFromParent()
{
	BasePopupDialog::_removeFromParent();
}

void PauseGameDialog::setCallBackFunc(CCCallFunc *callBackFunc)
{

}

void PauseGameDialog::onRestart(Ref *obj)
{
	
}

void PauseGameDialog::onCancel(Ref *obj)
{
	this->closeDialog();
}

PauseGameDialog * PauseGameDialog::getInstance()
{
	if (pauseGameDialogInstance == NULL){
		pauseGameDialogInstance = PauseGameDialog::create();
		pauseGameDialogInstance->retain();
	}
	return pauseGameDialogInstance;
}

void PauseGameDialog::destroyInstance()
{
	if (pauseGameDialogInstance != NULL){
		pauseGameDialogInstance->release();
		pauseGameDialogInstance = NULL;
	}
}

