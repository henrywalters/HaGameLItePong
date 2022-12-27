//
// Created by henry on 12/22/22.
//

#ifndef PONG_BALL_H
#define PONG_BALL_H

#include "hagame/graphics/primitives/disc.h"
#include "hagame/core/gameObject.h"

using namespace hg;
using namespace hg::graphics;

struct Ball : public hg::GameObject {
    std::unique_ptr<Mesh> mesh;
    std::unique_ptr<MeshInstance> meshInstance;

    float speed = 250;
    float radius;

    Vec3 direction = Vec3(1, 1, 0);

    Ball(float _radius):
        radius(_radius)
    {
        mesh = std::make_unique<primitives::Disc>(radius, 100);
        meshInstance = std::make_unique<MeshInstance>(mesh.get());
    }

    void move(double dt, Vec2 windowSize) {

        transform.move(direction * speed * dt);

        if (transform.position[0] <= radius || transform.position[0] >= windowSize[0] - radius) {
            transform.position[0] = std::clamp(transform.position[0], radius, windowSize[0] - radius);
            speed *= 1.1;
            direction[0] *= -1;
        }

        if (transform.position[1] <= radius || transform.position[1] >= windowSize[1] - radius) {
            transform.position[1] = std::clamp(transform.position[1], radius, windowSize[1] - radius);
            speed *= 1.1;
            direction[1] *= -1;
        }
    }

    void onUpdate(double dt) override {
        meshInstance->render();
    }
};

#endif //PONG_BALL_H
