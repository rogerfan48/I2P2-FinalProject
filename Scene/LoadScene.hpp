#ifndef LOADSCENE_HPP
#define LOADSCENE_HPP

#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
class LoadScene final : public Engine::IScene {
public:
    float tick = 0;
    explicit LoadScene() = default;
    void Initialize() override;
    void Update(float deltaTime) override;
    void Terminate() override;
};
#endif // LOADSCENE_HPP
