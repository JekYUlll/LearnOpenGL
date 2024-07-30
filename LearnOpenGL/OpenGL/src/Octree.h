#pragma once

#include <vector>
#include <memory>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//�����߽��AABB��
struct AABB {
    glm::vec3 minPoint, maxPoint;
    AABB(const glm::vec3& minPoint, const glm::vec3& maxPoint) : minPoint(minPoint), maxPoint(maxPoint) {}

    // �������AABB�Ƿ��ཻ
    bool intersects(const AABB& other) const;

    // ���AABB�Ƿ����һ����
    bool contains(const glm::vec3& point) const;
};

class Octree {
    AABB boundary;
    int capacity;
    std::vector<glm::vec3> points;
    std::unique_ptr<Octree> children[8];
    bool divided = false;

    void subdivide(); 

public:
    Octree(const AABB& boundary, int capacity) : boundary(boundary), capacity(capacity) {}

    bool insert(const glm::vec3& point); 

    void query(const AABB& range, std::vector<glm::vec3>& found) const;
};