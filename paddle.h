//
// Created by henry on 12/23/22.
//

#ifndef PONG_PADDLE_H
#define PONG_PADDLE_H

#include "hagame/core/gameObject.h"
#include "hagame/graphics/primitives/quad.h"
#include "hagame/core/gameObject.h"

using namespace hg;
using namespace hg::graphics;

struct Paddle : public hg::GameObject {
    std::unique_ptr<Mesh> mesh;
    std::unique_ptr<MeshInstance> meshInstance;
    Vec2 size;
    float speed = 300;

    Paddle(Vec2 _size):
        size(_size) {
        mesh = std::make_unique<Mesh>(primitives::Quad(size));
        meshInstance = std::make_unique<MeshInstance>(mesh.get());
    }

    void move(double dt, float direction, float height) {
        transform.position[1] = std::clamp<float>(transform.position[1] + direction * speed * dt, size[1] * 0.5, height - size[1] * 0.5);
    }

    void onUpdate(double dt) override {
        meshInstance->render();
    }
};

#endif //PONG_PADDLE_H
