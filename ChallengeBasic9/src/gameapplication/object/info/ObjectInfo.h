#pragma once
#include "../regist/ObjectRegist.h"

//========================================
//オブジェクトのデータクラス
//========================================

class CObjectInfo{
	typedef std::unordered_multimap < std::wstring, std::shared_ptr<Object>>::iterator ObjMapIt;
public:
	CObjectInfo() = default;

	//　登録
	void Regist(const std::shared_ptr<CObjectRegist>obj_regist){
		m_obj_regist = obj_regist;
	}
	
	//　オブジェクトを取得
	std::unordered_multimap < std::wstring, std::shared_ptr<Object>> Getobject()const{
		return m_obj_regist.lock()->Getobject();
	}

	//　最初と最後のイテレーターを返す
	std::pair<ObjMapIt, ObjMapIt> GetItr()const{
		return m_obj_regist.lock()->GetItr();
	}
	std::pair<ObjMapIt, ObjMapIt> GetItr(std::wstring name)const{
		return m_obj_regist.lock()->GetItr(name);
	}

	//　最初のイテレーターを返す
	ObjMapIt Begin(const std::wstring name)const{
		return GetItr(name).first;
	}
	ObjMapIt Begin()const{
		return GetItr().first;
	}

	//　最初のイテレーターを返す
	ObjMapIt End()const{
		return GetItr().second;
	}
	ObjMapIt End(const std::wstring name)const{
		return GetItr(name).second;
	}

	//　ポジションを取得
	Vec2f GetHitPos(const ObjMapIt itr)const{
		return itr->second->GetHitPos();
	}

	//　ポジションを取得
	Vec2f GetPos(const ObjMapIt itr)const{
		return itr->second->GetPos();
	}


	//　Xポジションを取得
	float GetPosX(const ObjMapIt itr)const{
		return itr->second->GetPosX();
	}

	//　Yポジションを取得
	float GetPosY(const ObjMapIt itr)const{
		return itr->second->GetPosY();
	}


	//　大きさを取得
	Vec2f GetScale(const ObjMapIt itr)const{
		return itr->second->GetScale();
	}

	//　アクティブかを取得
	bool GetActive(const ObjMapIt itr)const{
		return itr->second->isActive();
	}

	//　ダウンキャスト
	template <class Type>
	std::shared_ptr<Type> DynamicCast(const ObjMapIt itr)const{
		return std::dynamic_pointer_cast<Type>(itr->second);
	}

private:
	std::weak_ptr<CObjectRegist>m_obj_regist;
};

