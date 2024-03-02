#pragma once

#ifndef FADED_SCENE_STARTSCENE__START_GAME_MENU_LAYER_H__
#define FADED_SCENE_STARTSCENE__START_GAME_MENU_LAYER_H__

#include "cocos2d.h"

namespace Faded {
namespace Scene {
namespace Primary {
class StartGameMenuLayer : public cocos2d::LayerColor {
 protected:
 private:
  StartGameMenuLayer() = default;
  static StartGameMenuLayer* startGameMenuLayerInstance;

  /*!
   * @brief Initialize singleton StartGameMenuLayer
   * @return If ConfigurationResolution initizlized successfully.
   */
  bool init(void) override;
  CREATE_FUNC(StartGameMenuLayer);

  void initBackground(void);
  void initMenu(void);

 public:
  virtual ~StartGameMenuLayer() = default;

  /*!
   * @brief Singleton pattern, get instance of this class,
   * ����ģʽ, ��ȡ��ǰ��ʵ��
   * @return pointer to the instance of this class, ��ǰ���ʵ��
   */
  static StartGameMenuLayer* getInstance(void);
  /*!
   * @brief Singleton pattern, create a new instance of this class,
   * ����ģʽ, ����һ���µ�ʵ��
   * @return pointer to the instance of this class, ��ǰ���ʵ��
   */
  static StartGameMenuLayer* makeInstance(void);
  /*!
   * @brief Singleton pattern, remove the instance of this class,
   * ����ģʽ, �Ƴ���ǰʵ��
   */
  static void removeInstance(void);
  /*!
   * @brief Singleton pattern, check if the instance exist,
   * ����ģʽ, ȷ��ʵ���Ƿ����
   * @return if exist
   */
  static bool ifExistInstance(void);

  void menuExitGameCallBack(cocos2d::Ref* pSender);
  void menuOptionMenuPopupCallBack(cocos2d::Ref* pSender);
  void menuChangeToBattleFieldScene(cocos2d::Ref* pSender);
};
}  // namespace Primary
}  // namespace Scene
}  // namespace Faded

#endif  // !FADED_SCENE_STARTSCENE__START_GAME_MENU_LAYER_H__
