#include <memory>
#include <iostream>
#include "hagame/graphics/window.h"
#include "hagame/graphics/shaderProgram.h"
#include "hagame/utils/timer.h"
#include "hagame/utils/file.h"
#include "hagame/input/input.h"

#include "ball.h"
#include "paddle.h"

using namespace hg;
using namespace hg::graphics;
using namespace hg::math;

#ifdef __EMSCRIPTEN__
const std::string ASSET_DIR = "./assets/";
#else
const std::string ASSET_DIR = "../assets/";
#endif

std::shared_ptr<Window> window;
std::shared_ptr<ShaderProgram> shader;
std::shared_ptr<Mat4> orthographic;
std::shared_ptr<Ball> ball;
std::shared_ptr<Paddle> paddle1;
std::shared_ptr<Paddle> paddle2;

hg::utils::Timer timer;

void tick() {

    window->clear();

    auto windowSize = window->size();

    auto dt = utils::Clock::ToSeconds(timer.elapsed());
    timer.reset();

    window->title(std::to_string(dt));

    shader->setMat4("model", ball->transform.getModel());

    ball->update(dt);

    shader->setMat4("model", paddle1->transform.getModel());
    paddle1->update(dt);

    window->render();

    ball->move(dt, windowSize.cast<float>());

    //std::cout << input::Input::KeyboardMouse().lAxis << "\n";
    paddle1->move(dt, input::Input::KeyboardMouse().lAxis[1], windowSize[1]);
}

int main() {
    window = std::make_shared<Window>("Pong");
    window->initialize();

    orthographic = std::make_shared<Mat4>(Mat4::Orthographic(0, window->size()[0], 0, window->size()[1], -10, 10));

    ball = std::make_shared<Ball>(25);
    ball->transform.position[0] = window->size()[0] / 2;
    ball->transform.position[1] = window->size()[1] / 2;

    paddle1 = std::make_shared<Paddle>(Vec2(25, 100));
    paddle1->transform.position[0] = 50;
    paddle1->transform.position[1] = (window->size()[0] / 2) - 50;

    auto spriteVert = utils::f_read(ASSET_DIR + "shaders/sprite.vert");
    auto spriteFrag = utils::f_read(ASSET_DIR + "shaders/sprite.frag");
    auto vertex = Shader::LoadVertex(spriteVert);
    auto fragment = Shader::LoadFragment(spriteFrag);

    shader = std::make_shared<ShaderProgram>("test", vertex, fragment);

    shader->use();

    shader->setMat4("projection", *orthographic);
    shader->setMat4("view", Mat4::Identity());

    glfwSwapInterval(0);


#ifdef __EMSCRIPTEN__
    std::cout << "Hey Wasm!" << "\n";
    emscripten_set_main_loop(tick, 0, false);
#else

    while (window->running()) {
        tick();
    }

    window->close();
#endif

    return 0;
}
