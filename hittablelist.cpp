#include "hittablelist.hpp"

using namespace strangeloop;

HittableList::HittableList()
{

}

HittableList::HittableList(std::shared_ptr<Hittable> object)
{
    objects.push_back(object);
}

void HittableList::clear()
{
    objects.clear();
}

void HittableList::add(std::shared_ptr<Hittable> object)
{
    objects.push_back(object);
}

bool HittableList::hit(const strangeloop::Ray &r, double tMin, double tMax, strangeloop::HitRecord &rec) const
{
    HitRecord tempRec;
    bool hitAnything = false;
    auto closestSoFar = tMax;

    for (const auto& object: objects) {
        if (object->hit(r,tMin, closestSoFar, tempRec)) {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }

    return hitAnything;
}
