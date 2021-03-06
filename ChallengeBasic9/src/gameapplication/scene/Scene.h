#pragma once
#include "../Uncopyable.h"
#include "../resource/Resource.h"
#include "../../lib/appEnv.hpp"
#include <memory>

class CSceneManager;

//========================================
//シーンクラス(基底クラス)
//========================================

class CScene : private Uncopyable{
public:
	CScene(const std::shared_ptr<AppEnv>app_env) :
		m_app_env(app_env),
		m_res(CResource::GetInstance()){}

	//　シーンの種類
	enum class Type{
		TITLE,
		STAGE,
		RESULT,
		RULE,
		RANKING,
		MENU
	};

	virtual ~CScene() = default;

	virtual Type Update() = 0;
	virtual void Draw() = 0;

	//　チェンジするシーンを取得
	Type ChangeScene()const{ return m_change_scene; }

	//　画面のサイズ
	static const int WIDTH = 1000;
	static const int HEIGHT = 700;

protected:
	std::shared_ptr<AppEnv>m_app_env;									//　アプリイベント
	CResource& m_res;													//　リソース
	Type m_change_scene;												//　遷移するシーン
};