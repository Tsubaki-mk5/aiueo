#pragma once
#include"../Base/Base.h"
std::list<Base*> Base::m_list;
CVector2D Base::m_scroll(0, 0);
Base::Base(int type) : m_type(type), m_kill(false), m_vec(0, 0), m_rad(0) {

}
CVector2D Base::GetScreenPos(const CVector2D& pos) {
	
	return pos - m_scroll;
}

Base::~Base() {

}
void Base::Update() {

}
void Base::Draw() {

}
void Base::Collision(Base* b) {

}

void Base::UpdateAll() {
	//全てのオブジェクトの更新
	for (auto& b : m_list) {
		b->Update();
	}
}
void Base::DrawAll() {
	//全てのオブジェクトの描画処理
	for (auto& b : m_list) {
		b->Draw();
	}
}
void Base::Add(Base* b) {
	//Type順によるソート
	auto itr = m_list.begin();
	while (itr != m_list.end()) {
		if ((*itr)->m_type > b->m_type) {
			m_list.insert(itr, b);
			return;
		}
		itr++;
	}
	//オブジェクトbを末尾に追加
	m_list.push_back(b);
}
void Base::KillAll() {
	std::list<Base*> ret;
	for (auto& b : m_list) {
		b->SetKill();
	}
}


bool Base::CollisionCircle(Base* b1, Base* b2) {
	CVector2D v = b1->m_pos - b2->m_pos;
	float l = v.Length();
	if (l < b1->m_rad + b2->m_rad) {
		return true;
	}

	return false;

}
void Base::CollisionAll() {
	auto it1 = m_list.begin();
	auto last = m_list.end();
	while (it1 != last) {
		auto it2 = it1;
		it2++;
		while (it2 != last) {
			(*it1)->Collision(*it2);
			(*it2)->Collision(*it1);
			it2++;
		}
		it1++;
	}
}
void Base::CheckKillAll()
{
	auto it = m_list.begin();
	auto last = m_list.end();
	while (it != last) {
		if ((*it)->m_kill) {
			delete (*it);
			it = m_list.erase(it);
		}
		else {
			//次へ
			it++;
		}
	}
}

Base* Base::FindObject(int type) {
	//先頭の要素
	auto it = m_list.begin();
	//末尾の要素
	auto last = m_list.end();
	//itが末尾でなければ
	while (it != last) {
		if ((*it)->m_type == type) {
			//見つけたオブジェクトの数
			return(*it);
		}
		it++;
	}
	return nullptr;
}
void Base::DrawRect()
{
	
}
std::list<Base*>Base::FindObjects(int type) {
	std::list<Base*>ret;
	for (auto& b : m_list) {
		if (b->m_type == type)
			ret.push_back(b);
	}
	return ret;
}