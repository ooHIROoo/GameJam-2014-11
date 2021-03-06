#include "CRandom.h"

CRandom::CRandom():
engine(std::mt19937(std::random_device()()))
{
}

//　シードの設定
void CRandom::SetSeed(const unsigned long seed){
	engine.seed(seed);
}

//　一様分布のランダム(実数)
double CRandom::Uniform(const double min, const double max){
	std::uniform_real_distribution<double>random(min, max);
	double result = random(engine);
	return result;
}

//　一様分布のランダム(実数)
float CRandom::Uniform(const float min, const float max){
	std::uniform_real_distribution<float>random(min, max);
	float result = random(engine);
	return result;
}

//　一様分布のランダム(整数)
int CRandom::Uniform(const int min, const int max){
	std::uniform_int_distribution<int>random(min, max);
	int result = random(engine);
	return result;
}

//　ベルヌーイ分布(指定した確率でtrueが出現、0.00~1.00)
bool CRandom::Bernulli(const float probability){
	std::bernoulli_distribution random(probability);
	bool result = random(engine);
	return result;
}

//　正規分布
//　exexpectation：期待値
//　error：標準偏差(誤差)
double CRandom::Gaussian(const double expectation, const double error){
	std::normal_distribution<double>random(expectation, error);
	double result = random(engine);
	return result;
}

int CRandom::Gaussian(const int expectation, const int error){
	std::normal_distribution<double>random(expectation, error);
	int result = static_cast<int>(random(engine));
	return result;
}

//　選択式
int CRandom::Select(const std::vector<int> &select){
	std::uniform_int_distribution<int>random(0,select.size()-1);
	int result = random(engine);
	return select[result];
}