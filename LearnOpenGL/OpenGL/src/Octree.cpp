#include "Octree.h"

bool AABB::intersects(const AABB& other) const
{
    return (minPoint.x <= other.maxPoint.x && maxPoint.x >= other.minPoint.x) &&
        (minPoint.y <= other.maxPoint.y && maxPoint.y >= other.minPoint.y) &&
        (minPoint.z <= other.maxPoint.z && maxPoint.z >= other.minPoint.z);
}

bool AABB::contains(const glm::vec3& point) const
{
    return (point.x >= minPoint.x && point.x <= maxPoint.x) &&
        (point.y >= minPoint.y && point.y <= maxPoint.y) &&
        (point.z >= minPoint.z && point.z <= maxPoint.z);
}

void Octree::subdivide()
{
    // 计算子节点的边界
    glm::vec3 midPoint = glm::vec3(
        (boundary.minPoint.x + boundary.maxPoint.x) / 2,
        (boundary.minPoint.y + boundary.maxPoint.y) / 2,
        (boundary.minPoint.z + boundary.maxPoint.z) / 2
    );

    children[0] = std::make_unique<Octree>(AABB(boundary.minPoint, midPoint), capacity);
    children[1] = std::make_unique<Octree>(AABB(glm::vec3(midPoint.x, boundary.minPoint.y, boundary.minPoint.z), glm::vec3(boundary.maxPoint.x, midPoint.y, midPoint.z)), capacity);
    children[2] = std::make_unique<Octree>(AABB(glm::vec3(boundary.minPoint.x, midPoint.y, boundary.minPoint.z), glm::vec3(midPoint.x, boundary.maxPoint.y, midPoint.z)), capacity);
    children[3] = std::make_unique<Octree>(AABB(glm::vec3(midPoint.x, midPoint.y, boundary.minPoint.z), glm::vec3(boundary.maxPoint.x, boundary.maxPoint.y, midPoint.z)), capacity);
    children[4] = std::make_unique<Octree>(AABB(glm::vec3(boundary.minPoint.x, boundary.minPoint.y, midPoint.z), glm::vec3(midPoint.x, midPoint.y, boundary.maxPoint.z)), capacity);
    children[5] = std::make_unique<Octree>(AABB(glm::vec3(midPoint.x, boundary.minPoint.y, midPoint.z), glm::vec3(boundary.maxPoint.x, midPoint.y, boundary.maxPoint.z)), capacity);
    children[6] = std::make_unique<Octree>(AABB(glm::vec3(boundary.minPoint.x, midPoint.y, midPoint.z), glm::vec3(midPoint.x, boundary.maxPoint.y, boundary.maxPoint.z)), capacity);
    children[7] = std::make_unique<Octree>(AABB(midPoint, boundary.maxPoint), capacity);

    divided = true;
}

bool Octree::insert(const glm::vec3& point)
{
    if (!boundary.contains(point)) return false;

    if (points.size() < capacity) {
        points.push_back(point);
        return true;
    }

    if (!divided) {
        subdivide();
    }

    for (auto& child : children) {
        if (child->insert(point)) {
            return true;
        }
    }

    return false;
}

void Octree::query(const AABB& range, std::vector<glm::vec3>& found) const
{
    if (!boundary.intersects(range)) return;

    for (const auto& point : points) {
        if (range.contains(point)) {
            found.push_back(point);
        }
    }

    if (divided) {
        for (const auto& child : children) {
            child->query(range, found);
        }
    }
}
