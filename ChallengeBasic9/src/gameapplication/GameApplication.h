#pragma once
#include "resource\Resource.h"
#include "scene\SceneManager.h"
#include "Uncopyable.h"

//========================================
//ゲームアプリケーションクラス
//========================================

class CGameApplication : private Uncopyable{
public:
	CGameApplication();

	//　更新
	void Update();

private:
	std::shared_ptr<AppEnv>m_app_env;								//　アプリイベント
	std::unique_ptr<CSceneManager>m_scene_manager;					//　シーンマネージャー
	CResource& m_res;												//　リソース

	//　起動条件
	bool LaunchCondition();
};

