#include "PrimaryScene.h"

#include "Configuration/GameBasic/GameBasicInformation.h"
#include "Configuration/Video/Screen/ConfigurationScreen.h"
#include "GameInformationLayer.h"
#include "StartGameMenuLayer.h"
#include "Utils/Macros/Configuration/VideoConfiguration.h"
#include "Utils/Random/SimpleRandomUtils.h"

namespace Primary = ::Faded::Scene::Primary;
using namespace Primary;

PrimaryScene* PrimaryScene::PrimarySceneInstance{nullptr};
std::string PrimaryScene::userConfigurationPath{"conf/cfg.plist"};

// on "init" you need to initialize your instance
bool PrimaryScene::init() {
  //////////////////////////////
  // 1. super init first
  if (!Scene::init()) {
    return false;
  }

  auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
  auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

  // Background
  initBackgroundTextureCache();
  initBackgroundSprite();
  initBackground();
  initVersionButton();

  // For layerSwitcher
  initLayerSwitcher();

  return true;
}

void PrimaryScene::initBackgroundTextureCache(void) {
  auto plistInfo = cocos2d::FileUtils::getInstance()->getValueMapFromFile(
      "res/config/startScene.plist");
  for (auto& backgroundName : plistInfo.at("backgroundImgae").asValueVector()) {
    this->m_backgroundCachers.push_back(
        cocos2d::Director::getInstance()->getTextureCache()->addImage(
            FADED__GET_RESOLUTION_SPECIFIED_RCPATH(
                "res/UI/Scene/StartScene/background/",
                backgroundName.asString())));
  }
}

void PrimaryScene::initBackgroundSprite(void) {
  auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
  auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

  auto plistInfo = cocos2d::FileUtils::getInstance()->getValueMapFromFile(
      userConfigurationPath);
  if (plistInfo.at("randomBackground").asBool()) {
    this->m_backgroundSprite =
        cocos2d::Sprite::createWithTexture(this->m_backgroundCachers.at(
            ::Faded::Utils::Random::SimpleRandomUtils::getInstance(
                0, this->m_backgroundCachers.size() - 1)
                ->random()
                .int_return));
  } else {
    this->m_backgroundSprite = cocos2d::Sprite::createWithTexture(
        this->m_backgroundCachers.at(plistInfo.at("backgroundIndex").asInt()));
  }
  this->m_backgroundSprite->setContentSize(visibleSize);
}

void PrimaryScene::initLayerSwitcher(void) {
  this->m_layerSwitcher = cocos2d::LayerMultiplex::create();
  this->addChild(this->m_layerSwitcher);
  // TODO: more layers

  auto startMenuLayer = StartGameMenuLayer::getInstance();
  auto gameInfoLayer = GameInformationLayer::getInstance();

  this->m_layerSwitcher->addLayer(startMenuLayer);
  this->m_layerSwitcher->addLayer(gameInfoLayer);
  this->m_layerSwitcher->switchTo(0);
}

void PrimaryScene::initBackground(void) {
  auto backgroundMenu = cocos2d::Menu::create();
  auto backgroundItem = cocos2d::MenuItemSprite::create(
      this->m_backgroundSprite, nullptr, nullptr,
      CC_CALLBACK_1(PrimaryScene::changeBackgroundNextCallBack, this));
  backgroundMenu->addChild(backgroundItem);
  this->addChild(backgroundMenu);
}

void PrimaryScene::initVersionButton(void) {
  auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
  auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

  auto versionMenu = cocos2d::Menu::create();
  versionMenu->setAnchorPoint(cocos2d::Vec2::ZERO);
  versionMenu->setPosition(cocos2d::Vec2::ZERO);

  auto versionLabel = cocos2d::Label::createWithTTF(
      std::string("version: ")
          .append(::Faded::Configuration::GameBasic::GameBasicInformation::
                      getInstance()
                          ->getVersionInfo()),
      "fonts/arial.ttf",
      ::Faded::Configuration::Video::ConfigurationScreen::getInstance()
                  ->getWindowFrameSize()
                  .height /
              32 +
          2);
  auto versionItem = cocos2d::MenuItemLabel::create(
      versionLabel, CC_CALLBACK_1(PrimaryScene::switchMenuCallback, this));
  versionItem->setContentSize(versionLabel->getContentSize());
  versionItem->setPosition(
      cocos2d::Vec2(visibleSize.width - versionItem->getContentSize().width,
                    versionItem->getContentSize().height));

  versionMenu->addChild(versionItem);
  this->addChild(versionMenu);
}

cocos2d::Scene* PrimaryScene::createScene() { return PrimaryScene::create(); }

PrimaryScene* PrimaryScene::getInstance(void) {
  if (!PrimaryScene::PrimarySceneInstance) {
    PrimaryScene::makeInstance();
  }
  return PrimaryScene::PrimarySceneInstance;
}

PrimaryScene* PrimaryScene::makeInstance(void) {
  if (!PrimaryScene::PrimarySceneInstance) {
    PrimaryScene::PrimarySceneInstance = PrimaryScene::create();
  }
  return PrimaryScene::PrimarySceneInstance;
}

void PrimaryScene::removeInstance(void) {
  PrimaryScene::PrimarySceneInstance = nullptr;
}

bool PrimaryScene::ifExistInstance(void) {
  return PrimaryScene::PrimarySceneInstance ? true : false;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename) {
  fprintf(stderr, "Error while loading: %s\n", filename);
}

void PrimaryScene::menuExitGameCallBack(Ref* pSender) {
  // Close the cocos2d-x game scene and quit the application
  cocos2d::Director::getInstance()->end();

  /*To navigate back to native iOS screen(if present) without quitting the
   * application  ,do not use Director::getInstance()->end() as given
   * above,instead trigger a custom event created in RootViewController.mm as
   * below*/

  // EventCustom customEndEvent("game_scene_close_event");
  //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void PrimaryScene::switchMenuCallback(cocos2d::Ref* pSender) {
  static size_t currentMenuLayer{0};
  static size_t totalMenuLayer{2};
  this->m_layerSwitcher->switchTo(++currentMenuLayer >= totalMenuLayer
                                      ? currentMenuLayer = 0
                                      : currentMenuLayer);
}

void PrimaryScene::changeBackgroundNextCallBack(cocos2d::Ref* pSender) {
  this->m_backgroundSprite->setTexture(this->m_backgroundCachers.at(
      ++this->m_currentBackground >= this->m_backgroundCachers.size()
          ? this->m_currentBackground = 0
          : this->m_currentBackground));
}