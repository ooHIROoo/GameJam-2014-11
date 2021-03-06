#include "Result.h"
#include <fstream>

CResult::CResult(std::shared_ptr<AppEnv>app_env) :
CScene(app_env),
m_font(std::make_unique<Font>(60))
{
	update = false;
	rank = (Texture("res/graph/rank.png"));
	ranking = (Texture("res/graph/ranking.png"));
	result = (Texture("res/graph/result.png"));
	for (i = 0; i < 3; ++i) { time[i] = 120 * 60; }
	m_change_scene = Type::RESULT;

	std::ifstream lead("res/clear.txt");
	if (lead){
		for (int i = 0; i < 3; i++){
			lead >> m_is[i];
		}
	}

	if (m_is[0]) {
		std::ifstream load("res/stage01.txt");
		if (load) {
			load >> count;
		}
	}

	if (m_is[1]) {
		std::ifstream load("res/stage02.txt");
		if (load) {
			load >> count;
		}
	}

	if (m_is[2]) {
		std::ifstream load("res/stage03.txt");
		if (load) {
			load >> count;
		}
	}
}

//　更新
CScene::Type CResult::Update(){
	if (m_app_env->isPushKey(GLFW_KEY_ENTER)){
		m_change_scene = Type::STAGE;
	}
	return m_change_scene;
}

void CResult::Draw(){
	bg_switch(false);
	disp_result(count);
}

/* public */
//////////////////////////////////////////////////////////////////////

// アップデート
void CResult::data_update(const int clear) {
	temp_time = clear;
	for (i = 0; i < 3; ++i) {
		if (temp_time < time[i] && !update) { update = true; }
		if (update) { std::swap(temp_time, time[i]); }
	}
}

// 読み込み
void CResult::data_load() {
	std::ifstream load("res/score.txt");
	if (load) {
		for (i = 0; i < 3; ++i) { load >> time[i]; }
		return;
	}
}

// 書き込み
void CResult::data_save() {
	if (update) {
		std::ofstream save("res/score.txt");
		if (save) {
			for (i = 0; i < 3; ++i) { save << time[i] << std::endl; }
			update = false;
		}
	}
}

// 描画
void CResult::draw(const bool sw, const int clear) {
	bg_switch(sw);
	sw ? disp_ranking() : disp_result(clear);
}


/* private */
//////////////////////////////////////////////////////////////////////

// 背景切り替え
void CResult::bg_switch(const bool& sw) {
	drawTextureBox(-500, -350, 1000, 700,
		0, 0, 1000, 700,
		sw ? ranking : result, Color(1, 1, 1));
}

// ランキング表示
void CResult::disp_ranking() {
	for (i = 0; i < 3; ++i) {
		rank_ = get_rank();

		num.init_value(time[i] / 60);
		num.disp_value(0, 110 * -i + 50, 1.0f, Color(1, 1, 1));

		drawTextureBox(250, 110 * -i, 128, 128,
			128 * rank_, 0, 128, 128,
			rank, Color(1, 1, 1),
			0, Vec2f(0.75f, 0.75f), Vec2f(0, 0));
	}
}

// リザルト表示
void CResult::disp_result(const int& clear) {
	rank_ = (clear / 60) / 15;
	if (rank_ < 0) { rank_ = 0; }

	num.init_value(clear / 60);
	num.disp_value(300, 40, 1.0f, Color(1, 1, 1));

	drawTextureBox(230, -165, 128, 128,
		128 * rank_, 0, 128, 128,
		rank, Color(1, 1, 1),
		0, Vec2f(0.75f, 0.75f), Vec2f(0, 0));
}

// ランク決定
int CResult::get_rank() {
	if (time[i] < 60 * 60) { return 0; }    // S
	if (time[i] < 90 * 60) { return 1; }    // A
	if (time[i] < 120 * 60) { return 2; }   // B
	return 3;                               // C
}