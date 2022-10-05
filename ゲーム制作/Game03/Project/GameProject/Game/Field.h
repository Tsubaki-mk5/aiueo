#pragma once
#include"../Base/Base.h"
class Field :public Base {
private:
	//地面の高さ
	float m_ground_y;
public:
	///コンストラクタ
	Field();
	///描画
	void Draw();
	///地面の高さを取得
	float GetGroundY() {
		return m_ground_y;
	}
};