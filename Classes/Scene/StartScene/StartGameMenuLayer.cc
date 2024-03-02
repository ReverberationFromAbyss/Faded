#include "StartGameMenuLayer.h"

#include "Configuration/Video/Screen/ConfigurationScreen.h"
#include "Utils/Macros/Configuration/VideoConfiguration.h"

using namespace ::Faded::Scene::Primary;

StartGameMenuLayer* StartGameMenuLayer::startGameMenuLayerInstance{nullptr};

bool StartGameMenuLayer::init(void) {
  if (!cocos2d::LayerColor::init()) {
    return false;
  }

  auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
  auto originPoint = cocos2d::Director::getInstance()->getVisibleOrigin();

  // configure layer base attributes
  this->setVisible(true);
  this->_touchEnabled = true;
  this->_swallowsTouches = true;
  this->_touchMode = cocos2d::Touch::DispatchMode::ONE_BY_ONE;
  this->setContentSize(
      cocos2d::Size(visibleSize.width / 3, visibleSize.height));
  this->setAnchorPoint(cocos2d::Vec2::ZERO);
  this->setPosition(cocos2d::Vec2::ZERO);

  initBackground();
  initMenu();

  return true;
}

void StartGameMenuLayer::initBackground(void) {
  // Layer Background
  auto backgroundMenu = cocos2d::Menu::create();
  backgroundMenu->setContentSize(this->getContentSize());
  backgroundMenu->setPosition(this->getContentSize() / 2);
  {
    auto backgroundSprite =
        cocos2d::Sprite::create(FADED__GET_RESOLUTION_SPECIFIED_RCPATH(
            "res/UI/Scene/StartScene/Menu/", "startMenu.menuBackground.png"));

    backgroundSprite->setContentSize(this->getContentSize());
    auto backgroundSwallower =
        cocos2d::MenuItemSprite::create(backgroundSprite, nullptr);
    backgroundSwallower->setContentSize(this->getContentSize());
    backgroundMenu->addChild(backgroundSwallower);
  }
  this->addChild(backgroundMenu);
}

void StartGameMenuLayer::initMenu(void) {
  // Menu
  auto startGameMenu = cocos2d::Menu::create();
  startGameMenu->setAnchorPoint(cocos2d::Vec2::ZERO);
  startGameMenu->setContentSize(
      cocos2d::Size(this->getContentSize().width * 6 / 8,
                    this->getContentSize().height * 8 / 10));
  startGameMenu->setPosition(
      cocos2d::Vec2(this->getContentSize().width / 8,
                    this->getContentSize().height * 1 / 10));

  // Background for startGameMenu
  auto menuBackground =
      cocos2d::Sprite::create(FADED__GET_RESOLUTION_SPECIFIED_RCPATH(
          "res/UI/Scene/StartScene/Menu/",
          "startMenu.menuGameStartMenuBackground.png"));
  menuBackground->setAnchorPoint(startGameMenu->getAnchorPoint());
  menuBackground->setContentSize(startGameMenu->getContentSize());
  menuBackground->setPosition(startGameMenu->getPosition());
  this->addChild(menuBackground);

  // For startScene startGameMenu
#define START_INTERNAL__NEW_BUTTON_SET(buttonName, resPath, targetMenu, pos, \
                                       callback)                             \
  {                                                                          \
    auto buttonName##Normal =                                                \
        cocos2d::Sprite::create(FADED__GET_RESOLUTION_SPECIFIED_RCPATH(      \
            resPath, "startMenu." #buttonName "_normal.png"));               \
    buttonName##Normal->setContentSize(                                      \
        cocos2d::Size(targetMenu->getContentSize().width * 8 / 10,           \
                      targetMenu->getContentSize().height / 16));            \
    auto buttonName##Selected =                                              \
        cocos2d::Sprite::create(FADED__GET_RESOLUTION_SPECIFIED_RCPATH(      \
            resPath, "startMenu." #buttonName "_selected.png"));             \
    buttonName##Selected->setContentSize(                                    \
        cocos2d::Size(targetMenu->getContentSize().width * 8 / 10,           \
                      targetMenu->getContentSize().height / 16));            \
    auto buttonName##Disabled =                                              \
        cocos2d::Sprite::create(FADED__GET_RESOLUTION_SPECIFIED_RCPATH(      \
            resPath, "startMenu." #buttonName "_disabled.png"));             \
    buttonName##Disabled->setContentSize(                                    \
        cocos2d::Size(targetMenu->getContentSize().width * 8 / 10,           \
                      targetMenu->getContentSize().height / 16));            \
    auto buttonName##Button = cocos2d::MenuItemSprite::create(               \
        buttonName##Normal, buttonName##Selected, buttonName##Disabled,      \
        callback);                                                           \
    buttonName##Button->setContentSize(                                      \
        cocos2d::Size(targetMenu->getContentSize().width * 8 / 10,           \
                      targetMenu->getContentSize().height / 16));            \
    buttonName##Button->setPosition(                                         \
        cocos2d::Vec2(targetMenu->getContentSize().width / 2.0f,             \
                      targetMenu->getContentSize().height * pos / 10));      \
    targetMenu->addChild(buttonName##Button);                                \
  }

  {
    START_INTERNAL__NEW_BUTTON_SET(startGame, "res/UI/Scene/StartScene/Menu/",
                                   startGameMenu, 9, nullptr);
    START_INTERNAL__NEW_BUTTON_SET(continueGame,
                                   "res/UI/Scene/StartScene/Menu/",
                                   startGameMenu, 8, nullptr);
    START_INTERNAL__NEW_BUTTON_SET(option, "res/UI/Scene/StartScene/Menu/",
                                   startGameMenu, 7, nullptr);
    START_INTERNAL__NEW_BUTTON_SET(
        exitGame, "res/UI/Scene/StartScene/Menu/", startGameMenu, 1,
        CC_CALLBACK_1(StartGameMenuLayer::menuExitGameCallBack, this));
  }
  this->addChild(startGameMenu);
}

StartGameMenuLayer* StartGameMenuLayer::getInstance(void) {
  if (!StartGameMenuLayer::startGameMenuLayerInstance) {
    StartGameMenuLayer::makeInstance();
  }
  return StartGameMenuLayer::startGameMenuLayerInstance;
}

StartGameMenuLayer* StartGameMenuLayer::makeInstance(void) {
  if (!StartGameMenuLayer::startGameMenuLayerInstance) {
    StartGameMenuLayer::startGameMenuLayerInstance =
        StartGameMenuLayer::create();
  }
  return StartGameMenuLayer::startGameMenuLayerInstance;
}

void StartGameMenuLayer::removeInstance(void) {
  StartGameMenuLayer::startGameMenuLayerInstance = nullptr;
}

bool StartGameMenuLayer::ifExistInstance(void) {
  return StartGameMenuLayer::startGameMenuLayerInstance ? true : false;
}

void StartGameMenuLayer::menuExitGameCallBack(cocos2d::Ref* pSender) {
  // Close the cocos2d-x game scene and quit the application
  cocos2d::Director::getInstance()->end();
}