#pragma once
#include"Component.h"

class Collision : public Component {
public:
    void Update(float deltaTime) override {
        // ʵ����ײ�߼�
    }

    bool CheckCollision(const Collision& other) const {
        // ��ײ����߼�
    }
};
