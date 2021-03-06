#pragma once
#include "../Object.h"
#include "../character/enemy/Girl.h"
#include <unordered_map>

class CEnemyFactory{
public:

	enum class Type{
		GIRL
	};

	CEnemyFactory(){
		m_object_create_list.emplace(Type::GIRL, [](){return std::make_unique<CGirl>(); });
	}

	//　オブジェクトを取得
	std::shared_ptr<Object> Getobject(const Type name)const{
		return (m_object_create_list.find(name)->second)();
	}

private:
	std::unordered_map < Type, std::function < std::shared_ptr<Object>() >> m_object_create_list;			//　シーン生成リスト

};

