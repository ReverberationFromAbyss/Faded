#pragma once

#ifndef FADED_SCENE_STARTSCENE__GAME_INFORMATION_LAUER_H__
#define FADED_SCENE_STARTSCENE__GAME_INFORMATION_LAUER_H__

#include "cocos2d.h"

namespace Faded {
namespace Scene {
namespace Primary {
class GameInformationLayer : private cocos2d::LayerColor {
 protected:
 private:
  GameInformationLayer() = default;
  static GameInformationLayer* gameInformationLayerInstance;

  bool init(void) override;
  CREATE_FUNC(GameInformationLayer);

  void initBackground(void);
  void initMenu(void);

 public:
  virtual ~GameInformationLayer() = default;

  /*!
   * @brief Singleton pattern, get instance of this class,
   * ����ģʽ, ��ȡ��ǰ��ʵ��
   * @return pointer to the instance of this class, ��ǰ���ʵ��
   */
  static cocos2d::Layer* getInstance(void);
  /*!
   * @brief Singleton pattern, create a new instance of this class,
   * ����ģʽ, ����һ���µ�ʵ��
   * @return pointer to the instance of this class, ��ǰ���ʵ��
   */
  static cocos2d::Layer* makeInstance(void);
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

  void menuBackwordCallback(cocos2d::Ref* pSender);
};
}  // namespace Primary
}  // namespace Scene
}  // namespace Faded

#endif  //! FADED_SCENE_STARTSCENE__GAME_INFORMATION_LAUER_H__