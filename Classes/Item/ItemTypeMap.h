#pragma once

#ifndef FADED_ITEM__ITEM_TYPE_H__
#define FADED_ITEM__ITEM_TYPE_H__

#include <map>
#include <string>

#include "Public/PublicHeader.h"
#include "cocos2d.h"

namespace Faded {
namespace Item {
class ItemTypeMap : private cocos2d::Ref {
 private:
  ItemTypeMap() = default;
  static ItemTypeMap* itemTypeInstance;

  virtual bool init(void);
  CREATE_FUNC(ItemTypeMap);

  std::map<std::string, ::Faded::Public::id_t> m_typeMap{};
  size_t m_totalTypeNum{};

public:
  virtual ~ItemTypeMap() = default;

  /*!
   * @brief Singleton pattern, get instance of this class,
   * ����ģʽ, ��ȡ��ǰ��ʵ��
   * @return pointer to the instance of this class, ��ǰ���ʵ��
   */
  static ItemTypeMap *getInstance(void);
  /*!
   * @brief Singleton pattern, create a new instance of this class,
   * ����ģʽ, ����һ���µ�ʵ��
   * @return pointer to the instance of this class, ��ǰ���ʵ��
   */
  static ItemTypeMap *makeInstance(void);
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
  /*!
   * @brief Singleton pattern, init instance
   * @return if init success
   */
  static bool initInstance(void);

  void addType(std::string typeName, Public::id_t typeID);
  void addType(std::string typeName);
};
}  // namespace Item
}  // namespace Faded

#endif  // !FADED_ITEM__ITEM_TYPE_H__
