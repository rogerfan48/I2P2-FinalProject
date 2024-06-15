#include "PlayScene.hpp"
#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_audio.h>
#include <vector>

#include "Engine/IScene.hpp"
#include "Engine/Group.hpp"
#include "Engine/AudioHelper.hpp"
#include "UI/Component/Rectangle.hpp"

const int PlayScene::BlockSize = 50;
const int PlayScene::MapBlockWidth = 32, PlayScene::MapBlockHeight = 18;
const int PlayScene::CardSetHeight = 6;
const int PlayScene::MapDiff = 100;
std::map<int, ALLEGRO_COLOR> PlayScene::TileColor;
std::vector<std::string> PlayScene::MapTile;

void PlayScene::Initialize() {
    MapTile.push_back("01010101010101044010101010101010");
    MapTile.push_back("10101010101010144101010101010101");
    MapTile.push_back("01010555010101044010101015551010");
    MapTile.push_back("10133555333333322333333335553101");
    MapTile.push_back("01030555010101044010101015553010");
    MapTile.push_back("10131010101010144101010101013101");
    MapTile.push_back("01030101010101044010101010103010");
    MapTile.push_back("15555010101010144101010101055551");
    MapTile.push_back("05555101010101044010101010155550");
    MapTile.push_back("15555010101010144101010101055551");
    MapTile.push_back("05555101010101044010101010155550");
    MapTile.push_back("10131010101010144101010101013101");
    MapTile.push_back("01030101010101044010101010103010");
    MapTile.push_back("10131555101010144101010155513101");
    MapTile.push_back("01033555333333322333333355533010");
    MapTile.push_back("10101555101010144101010155510101");
    MapTile.push_back("01010101010101044010101010101010");
    MapTile.push_back("10101010101010144101010101010101");
    TileColor.insert({ GRASS1, al_map_rgb(40, 180, 99) });
    TileColor.insert({ GRASS2, al_map_rgb(39, 174, 96) });
    TileColor.insert({ BRIDGE, al_map_rgb(230, 160, 80) });
    TileColor.insert({ ROAD,   al_map_rgb(250, 190, 130) });
    TileColor.insert({ RIVER,  al_map_rgb(70, 210, 240) });
    TileColor.insert({ TOWER,  al_map_rgb(170, 170, 170) });
    TileColor.insert({ ROCK,   al_map_rgb(140, 140, 130) });
    TileColor.insert({ CARD,   al_map_rgb(190, 160, 140) });

    AddNewObject(TileMapGroup = new Group());
    TileMapGroup->AddNewObject(new Engine::Rectangle(0, 0, 2*MapDiff+MapBlockWidth*BlockSize, 2*MapDiff+MapBlockHeight*BlockSize, TileColor[ROCK]));
    TileMapGroup->AddNewObject(new Engine::Rectangle(0, 2*MapDiff+MapBlockHeight*BlockSize, 2*MapDiff+MapBlockWidth*BlockSize, CardSetHeight*BlockSize, TileColor[CARD]));
    for (int i=0; i<MapBlockHeight; i++) {
        for (int j=0; j<MapBlockWidth; j++) {
            TileMapGroup->AddNewObject(new Engine::Rectangle(
                MapDiff+j*BlockSize, MapDiff+i*BlockSize, BlockSize, BlockSize, TileColor[MapTile[i][j]-'0']
            ));
        }
    }

    bgmInstance = AudioHelper::PlaySample("bgm/playBGMw321.ogg", false, AudioHelper::BGMVolume);
}
void PlayScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
void PlayScene::Update(float deltaTime) {
    IScene::Update(deltaTime);
}
void PlayScene::Draw() const {
    IScene::Draw();
}
void PlayScene::OnMouseDown(int button, int mx, int my) {
    IScene::OnMouseDown(button, mx, my);
}
void PlayScene::OnMouseMove(int mx, int my) {
    IScene::OnMouseMove(mx, my);
}
void PlayScene::OnMouseUp(int button, int mx, int my) {
    IScene::OnMouseUp(button, mx, my);
}
void PlayScene::OnKeyDown(int keyCode) {
    IScene::OnKeyDown(keyCode);
}