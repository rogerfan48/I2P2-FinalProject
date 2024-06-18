#ifndef LOADSCENE_HPP
#define LOADSCENE_HPP

#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
class LoadScene final : public Engine::IScene {
private:
    int halfW, halfH;
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:
    float tick = 0;
    explicit LoadScene() = default;
    void Initialize() override;
    void Update(float deltaTime) override;
    void Draw() const override;
    void Terminate() override;
    void OnKeyDown(int keyCode) override;
};
#endif // LOADSCENE_HPP
