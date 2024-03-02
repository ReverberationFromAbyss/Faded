#pragma once

#ifndef FAEDE_CONFIGURATION_GAMEBASIC__GAME_BASIC_INFOMATION_H__
#define FAEDE_CONFIGURATION_GAMEBASIC__GAME_BASIC_INFOMATION_H__

#include <map>
#include <string>
#include <vector>

#include "Public/PublicHeader.h"
#include "cocos2d.h"

namespace Faded {
namespace Configuration {
namespace GameBasic {
class GameBasicInformation : private cocos2d::Ref {
 protected:
 private:
  GameBasicInformation() = default;
  static GameBasicInformation* GameBasicInformationInstance;

  virtual bool init(void);
  CREATE_FUNC(GameBasicInformation);

  static const std::string
      baseInfoConfPath;     // path to conf file(.plist), 配置文件路径
  std::string m_gameName;   // game name, 游戏名称
  std::string m_gameTitle;  // title presented on game window
  std::string m_versionInformation;      // verison information
  std::vector<std::string> m_staffList;  // all staffs
  std::map<std::string, std::vector<std::string>>
      m_staffInfo;  // all staffs sorted by job

 public:
  virtual ~GameBasicInformation() = default;

  // Sigleton pattern

  /*!
   * @brief Singleton pattern, get instance of this class,
   * 单例模式, 获取当前类实例
   * @return pointer to the instance of this class, 当前类的实例
   */
  static GameBasicInformation* getInstance(void);
  /*!
   * @brief Singleton pattern, create a new instance of this class,
   * 单例模式, 创建一个新的实例
   * @return pointer to the instance of this class, 当前类的实例
   */
  static GameBasicInformation* makeInstance(void);
  /*!
   * @brief Singleton pattern, remove the instance of this class,
   * 单例模式, 移除当前实例
   */
  static void removeInstance(void);
  /*!
   * @brief Singleton pattern, check if the instance exist,
   * 单例模式, 确认实例是否存在
   * @return if exist
   */
  static bool ifExistInstance(void);

  // Get *
  ::Faded::Public::name_t& getGameName(void);
  ::Faded::Public::name_t& getGameTitle(void);
  const std::string& getVersionInfo(void);
  const std::string& getStaff(int n);
  const std::vector<std::string>& getStaffList(void);
  // Set *
  // None
};
}  // namespace GameBasic
}  // namespace Configuration
}  // namespace Faded

#endif  // !FAEDE_CONFIGURATION_GAMEBASIC__GAME_BASIC_INFOMATION_H__
