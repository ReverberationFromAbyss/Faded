#pragma once

#ifndef FADED_SCENE_STARTSCENE__PRIMARY_SCENE_H__
#define FADED_SCENE_STARTSCENE__PRIMARY_SCENE_H__

#include <vector>

#include "cocos2d.h"

namespace Faded {
namespace Scene {
namespace Primary {
class PrimaryScene : public cocos2d::Scene {
 protected:
 private:
  enum LayerScene {
    kStartMenuLayer,
    kVersionMenuLayer,
  };

  PrimaryScene() = default;
  static PrimaryScene* PrimarySceneInstance;
  static std::string userConfigurationPath;

  bool init(void) override;
  // implement the "static create()" method manually
  CREATE_FUNC(PrimaryScene);

  std::vector<cocos2d::Texture2D*> m_backgroundCachers{};
  cocos2d::Sprite* m_backgroundSprite{nullptr};
  std::size_t m_currentBackground{0};
  cocos2d::LayerMultiplex* m_layerSwitcher{
      nullptr};  // layer switcher, ²ãÇÐ»»Æ÷
  LayerScene m_currentLayer{
      kStartMenuLayer};  // current displaying layer, µ±Ç°²ã

  // read background information and pull images into texture caher
  void initBackgroundTextureCache(void);
  // init background according to configuration
  void initBackgroundSprite(void);
  void initBackground(void);
  void initLayerSwitcher(void);
  void initVersionButton(void);

 public:
  virtual ~PrimaryScene() = default;

  [[deprecated]] static cocos2d::Scene* createScene();
  static PrimaryScene* getInstance(void);
  static PrimaryScene* makeInstance(void);
  static void removeInstance(void);
  static bool ifExistInstance(void);

  // a selector callback
  void menuExitGameCallBack(cocos2d::Ref* pSender);
  void switchMenuCallback(cocos2d::Ref* pSender);
  void changeBackgroundNextCallBack(cocos2d::Ref* pSender);
};
}  // namespace Primary
}  // namespace Scene
}  // namespace Faded

#endif  // FADED_SCENE_STARTSCENE__PRIMARY_SCENE_H__
