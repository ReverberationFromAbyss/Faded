#pragma once

#ifndef FADED_ITEM__ABSTRACT_ITEMS_H__
#define FADED_ITEM__ABSTRACT_ITEMS_H__

#include "Public/PublicHeader.h"
#include "cocos2d.h"

using numeric_t = ::Faded::Public::numeric_t;
using percentage_t = ::Faded::Public::percentage_t;
using name_t = ::Faded::Public::name_t;
using id_t = ::Faded::Public::id_t;

namespace Faded {
namespace Item {
class AbstractItem : public cocos2d::Ref {
 private:
  virtual bool init(void);
  CREATE_FUNC(AbstractItem);

  static cocos2d::Vector<AbstractItem*> itemList;
  static id_t totalItemsNum;

  id_t m_itemID;       // item id, ��Ʒid��
  name_t m_itemName;   // item name, ��Ʒ����
  bool m_ifStackable;  // if it is stackable, �Ƿ�ɶѻ�

 public:
  AbstractItem() = default;
  virtual ~AbstractItem() = default;
};
}  // namespace Item
}  // namespace Faded

#endif  // !FADED_ITEM__ABSTRACT_ITEMS_H__
