#include "GameBasicInformation.h"

using namespace ::Faded::Configuration::GameBasic;

GameBasicInformation *GameBasicInformation::GameBasicInformationInstance{
    nullptr};
const std::string GameBasicInformation::baseInfoConfPath{
    "res/config/gameBasicInfo.plist"};

// GameBasicInformation::GameBasicInformation(void)
//: m_gameName("Faded.~Memory"), m_gameTitle("Faded"), cocos2d::Ref() {}

bool GameBasicInformation::init(void) {
  auto plistInfo =
      cocos2d::FileUtils::getInstance()->getValueMapFromFile(baseInfoConfPath);
  this->m_gameName = plistInfo.at("name").asString();
  this->m_gameTitle = plistInfo.at("title").asString();
  this->m_versionInformation = plistInfo.at("version").asString();

  auto staffInfo = plistInfo.at("staffList").asValueMap();
  for (auto &val : staffInfo) {
    auto &staffs = val.second.asValueVector();
    for (auto &name : staffs) {
      this->m_staffInfo[val.first].push_back(name.asString());
      this->m_staffList.push_back(name.asString());
    }
  }

  return true;
}

GameBasicInformation *GameBasicInformation::getInstance(void) {
  if (!GameBasicInformationInstance) {
    return makeInstance();
  }
  return GameBasicInformationInstance;
}

GameBasicInformation *GameBasicInformation::makeInstance(void) {
  if (!GameBasicInformationInstance) {
    GameBasicInformationInstance =
        GameBasicInformation::create();
  }
  return GameBasicInformationInstance;
}

void GameBasicInformation::removeInstance(void) {
  GameBasicInformationInstance = nullptr;
}

bool GameBasicInformation::ifExistInstance(void) {
  return GameBasicInformationInstance ? true : false;
}

::Faded::Public::name_t &GameBasicInformation::getGameName(void) {
  return this->m_gameName;
}

::Faded::Public::name_t &GameBasicInformation::getGameTitle(void) {
  return this->m_gameTitle;
}

const std::string &GameBasicInformation::getVersionInfo(void) {
  return this->m_versionInformation;
}

const std::string &GameBasicInformation::getStaff(int n) {
  return this->m_staffList.at(n);
}

const std::vector<std::string> &GameBasicInformation::getStaffList(void) {
  return this->m_staffList;
}
