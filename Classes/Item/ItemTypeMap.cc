#include "ItemTypeMap.h"
#include "Public/PublicHeader.h"

namespace Item = ::Faded::Item;
using namespace Item;

ItemTypeMap* ItemTypeMap::itemTypeInstance{nullptr};

bool ItemTypeMap::init(void) { return true; }

ItemTypeMap* ItemTypeMap::getInstance(void){
  if(!itemTypeInstance){
    makeInstance();
  }
  return itemTypeInstance;
}

ItemTypeMap*ItemTypeMap::makeInstance(void){
  if(!itemTypeInstance){
    itemTypeInstance = ItemTypeMap::create();
  }
  return itemTypeInstance;
}

void ItemTypeMap::removeInstance(void){
  itemTypeInstance=nullptr;
}

bool ItemTypeMap::ifExistInstance(void){
  return itemTypeInstance?true:false;
}

void ItemTypeMap::addType(std::string typeName, ::Faded::Public::id_t typeID) {
  this->m_typeMap[typeName]=typeID;
  this->m_totalTypeNum++;
}

void ItemTypeMap::addType(std::string typeName) {
  this->m_typeMap[typeName]=++this->m_totalTypeNum;
  // 默认以当前类型总数记
}
