#include "PlayScene.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_audio.h>
#include <vector>
#include <iostream>
#include <string>

#include "Engine/Allegro5Exception.hpp"
#include "Engine/IScene.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Resources.hpp"
#include "Helper/Helper.hpp"
#include "Tower/MainTower.hpp"
#include "Tower/SideTower.hpp"
#include "UI/Component/Rectangle.hpp"
#include "UI/Component/RectangleBorder.hpp"
#include "UI/Component/Label.hpp"
#include "Card/AllCard.hpp"

const int PlayScene::BlockSize = 50;
const int PlayScene::MapBlockWidth = 32, PlayScene::MapBlockHeight = 18;
const int PlayScene::CardSetHeight = 6;
const int PlayScene::MapDiff = 100;
const int PlayScene::ElixirProcessWidth = 800;

std::map<int, ALLEGRO_COLOR> PlayScene::TileColor;
std::vector<std::string> PlayScene::MapTile;

static int halfW, halfH;
MainTower *redMainTower, *blueMainTower;
static Engine::Image* turtle;

void PlayScene::Initialize() {
    tick = 0;
    halfW = Engine::GameEngine::GetInstance().GetScreenSize().x / 2;
    halfH = Engine::GameEngine::GetInstance().GetScreenSize().y / 2;

    gameData.A.initGame();
    selectedCard = nullptr;
    instanceIDCounter = 0;
    mousePos = Engine::GameEngine::GetInstance().GetMousePosition();
    
    initMapTileAndTileColor();
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

    AddNewObject(prohibitedMask = new Engine::Rectangle(2*BlockSize, 2*BlockSize, 17*BlockSize, 18*BlockSize, al_map_rgba(255, 0, 0, 80)));
    AddNewObject(prohibitedMaskBorder = new Engine::RectangleBorder(2*BlockSize+5, 2*BlockSize+5, 17*BlockSize-10, 18*BlockSize-10, al_map_rgba(255, 0, 0, 180), 10));
    prohibitedMask->Enable = false;
    prohibitedMaskBorder->Enable = false;

    bgmInstance = AudioHelper::PlaySample("bgm/playBGMw321.ogg", false, AudioHelper::BGMVolume);

    AddNewControlObject(CardGroup = new Group());
    for (int i=0; i<4; i++) {
        cardPointer.push_back(getCardById(gameData.A.availableCards[i], 100+400*i+10, 1100+10));
        CardGroup->AddNewControlObject(cardPointer.back());
    }
    cardPointer[gameData.A.selectedCard]->selected = true;
    selectedCard = cardPointer[gameData.A.selectedCard];

    AddNewObject(radiusPreview = new Engine::Circle(0, 0, 0, al_map_rgba(255, 255, 255, 40)));
    AddNewObject(radiusPreviewBorder = new Engine::CircleBorder(0, 0, 0, al_map_rgba(255, 255, 255, 160), 6));
    radiusPreview->Enable = false;
    radiusPreviewBorder->Enable = false;

    AddNewObject(TowerGroup = new Group());
    TowerGroup->AddNewObject(new SideTower("Red", MapDiff+5*BlockSize, MapDiff+2*BlockSize));
    TowerGroup->AddNewObject(new SideTower("Red", MapDiff+5*BlockSize, MapDiff+13*BlockSize));
    TowerGroup->AddNewObject(redMainTower = new MainTower("Red", MapDiff+BlockSize, MapDiff+7*BlockSize));
    TowerGroup->AddNewObject(new SideTower("Blue", MapDiff+24*BlockSize, MapDiff+2*BlockSize));
    TowerGroup->AddNewObject(new SideTower("Blue", MapDiff+24*BlockSize, MapDiff+13*BlockSize));
    TowerGroup->AddNewObject(blueMainTower = new MainTower("Blue", MapDiff+27*BlockSize, MapDiff+7*BlockSize));

    AddNewObject(A_ArmyGroup = new Group());

    AddNewObject(placePreview = new Engine::Rectangle(0, 0, BlockSize, BlockSize, al_map_rgba(255, 255, 255, 80)));
    AddNewObject(placePreviewBorder = new Engine::RectangleBorder(0, 0, BlockSize-6, BlockSize-6, al_map_rgba(255, 255, 255, 220), 6));
    AddNewObject(placeReviewName = new Engine::Label("", "recharge.otf", 28, 0, 0, 255, 255, 255, 255));
    placePreview->Enable = false;
    placePreviewBorder->Enable = false;
    placeReviewName->Enable = false;

    // AddNewObject(MapBorderGroup = new Group());
    // MapBorderGroup->AddNewObject(new Engine::Rectangle(0, 0, 2*MapDiff+MapBlockWidth*BlockSize, 2*BlockSize, TileColor[ROCK]));
    // MapBorderGroup->AddNewObject(new Engine::Rectangle(0, 0, 2*BlockSize, 2*MapDiff+MapBlockHeight*BlockSize, TileColor[ROCK]));
    // MapBorderGroup->AddNewObject(new Engine::Rectangle(0, (MapBlockHeight+2)*BlockSize, 2*MapDiff+MapBlockWidth*BlockSize, 2*BlockSize, TileColor[ROCK]));
    // MapBorderGroup->AddNewObject(new Engine::Rectangle((MapBlockWidth+2)*BlockSize, 0, 2*BlockSize, 2*MapDiff+MapBlockHeight*BlockSize, TileColor[ROCK]));

    AddNewObject(ElixirGroup = new Group());
    ElixirGroup->AddNewObject(new Engine::Rectangle(890, 1020, ElixirProcessWidth+10, 60, al_map_rgb(30, 30, 30)));
    ElixirGroup->AddNewObject(new Engine::Rectangle(895, 1025, ElixirProcessWidth, 50, al_map_rgb(100, 100, 100)));
    ElixirGroup->AddNewObject(elixirProcess = new Engine::Rectangle(895, 1025, ElixirProcessWidth, 50, al_map_rgb(255, 0, 255)));
    for (int i=1; i<10; i++)
        ElixirGroup->AddNewObject(new Engine::Rectangle(895+3.5+80*i, 1025, 5, 50, al_map_rgb(60, 60, 60)));
    ElixirGroup->AddNewObject(new Engine::Image("elixir.png", 900-45, 1000+15, 70, 70));
    elixirNumber.resize(5);
    ElixirGroup->AddNewObject(elixirNumber[0] = new Engine::Label(std::to_string((int)gameData.A.elixir), "recharge.otf", 34, 893-2, 1050, 0, 0, 0, 255, 0.5, 0.5));
    ElixirGroup->AddNewObject(elixirNumber[1] = new Engine::Label(std::to_string((int)gameData.A.elixir), "recharge.otf", 34, 893+2, 1050, 0, 0, 0, 255, 0.5, 0.5));
    ElixirGroup->AddNewObject(elixirNumber[2] = new Engine::Label(std::to_string((int)gameData.A.elixir), "recharge.otf", 34, 893, 1050-2, 0, 0, 0, 255, 0.5, 0.5));
    ElixirGroup->AddNewObject(elixirNumber[3] = new Engine::Label(std::to_string((int)gameData.A.elixir), "recharge.otf", 34, 893, 1050+2, 0, 0, 0, 255, 0.5, 0.5));
    ElixirGroup->AddNewObject(elixirNumber[4] = new Engine::Label(std::to_string((int)gameData.A.elixir), "recharge.otf", 34, 893, 1050, 255, 255, 255, 255, 0.5, 0.5));
}
void PlayScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}

void PlayScene::Update(float deltaTime) {
    IScene::Update(deltaTime);
    tick += deltaTime;

    // Elixir:
    gameData.A.elixir += deltaTime * gameData.elixirSpeed;
    if (gameData.A.elixir > 10) gameData.A.elixir = 10;
    elixirProcess->Size.x = (gameData.A.elixir)*ElixirProcessWidth/10;
    for (auto i : elixirNumber) i->Text = std::to_string((int)gameData.A.elixir);
}

void PlayScene::Draw() const {
    Engine::Point nowBlock(pxToBlock(mousePos));
    IScene::Draw();
}

void PlayScene::OnMouseDown(int button, int mx, int my) {
    if ((button & 1) && selectedCard != nullptr && mouseInPlay() && mouseAtValid()) {
        if (gameData.A.elixir < selectedCard->cost) return;
        else gameData.A.elixir -= selectedCard->cost;
        Engine::Point nowBlock(pxToBlock(mousePos));
        if (selectedCard->cardType == ARMY) {
            std::cout << "1" << std::endl;
            A_ArmyGroup->AddNewObject(selectedCard->placeArmy(instanceIDCounter++, nowBlock.x, nowBlock.y));
        } else {

        }
        gameData.A.nextCardQueue.push(selectedCard->ID);
        int pos;
        for (int i=0; i<4; i++) if (cardPointer[i] == selectedCard) pos = i;
        CardGroup->RemoveControlObject(selectedCard->GetControlIterator(), selectedCard->GetObjectIterator());
        gameData.A.availableCards[pos] = gameData.A.nextCardQueue.front();
        gameData.A.nextCardQueue.pop();
        cardPointer[pos] = getCardById(gameData.A.availableCards[pos], 100+400*pos+10, 1100+10);
        CardGroup->AddNewControlObject(cardPointer[pos]);
        cardPointer[pos]->selected = true;
        selectedCard = cardPointer[pos];
    }
    IScene::OnMouseDown(button, mx, my);
}
void PlayScene::OnMouseMove(int mx, int my) {
    mousePos = Engine::Point(mx, my);
    Engine::Point nowBlock(pxToBlock(mousePos));
    if (mouseInPlay()) {
        prohibitedMask->Enable = true;
        prohibitedMaskBorder->Enable = true;
        if (mouseAtValid()) {
            placePreview->Enable = true;
            placePreviewBorder->Enable = true;
            placePreview->Position = blockToPx(nowBlock);
            placePreviewBorder->Position = Engine::Point(blockToPx(nowBlock).x+3, blockToPx(nowBlock).y+3);
            placeReviewName->Enable = true;
            placeReviewName->Text = selectedCard->Name;
            placeReviewName->Position = Engine::Point(blockToPx(nowBlock).x+BlockSize/2-al_get_text_width(placeReviewName->font.get(), placeReviewName->Text.c_str())/2, blockToPx(nowBlock).y-32);
            if (selectedCard->cardType == SPELL) {
                radiusPreview->Enable = true;
                radiusPreviewBorder->Enable = true;
                radiusPreview->Position = radiusPreviewBorder->Position = Engine::Point(blockToPx(nowBlock).x+BlockSize/2, blockToPx(nowBlock).y+BlockSize/2);
                radiusPreview->Size = radiusPreviewBorder->Size = Engine::Point(selectedCard->radius*BlockSize-3, selectedCard->radius*BlockSize-3);
            } else {
                radiusPreview->Enable = false;
                radiusPreviewBorder->Enable = false;
            }
        } else {
            placePreview->Enable = false;
            placePreviewBorder->Enable = false;
            placeReviewName->Enable = false;
            radiusPreview->Enable = false;
            radiusPreviewBorder->Enable = false;
        }
    } else {
        prohibitedMask->Enable = false;
        prohibitedMaskBorder->Enable = false;
        placePreview->Enable = false;
        placePreviewBorder->Enable = false;
        placeReviewName->Enable = false;
        radiusPreview->Enable = false;
        radiusPreviewBorder->Enable = false;
    }
    IScene::OnMouseMove(mx, my);
}
void PlayScene::OnMouseUp(int button, int mx, int my) {
    IScene::OnMouseUp(button, mx, my);
}
void PlayScene::OnKeyDown(int keyCode) {
    IScene::OnKeyDown(keyCode);
}

void PlayScene::initMapTileAndTileColor() {
    MapTile.push_back("01010101010101044010101010101010");
    MapTile.push_back("10101010101010144101010101010101");
    MapTile.push_back("01010555010101044010101055501010");
    MapTile.push_back("10133555333333322333333355533101");
    MapTile.push_back("01030555010101044010101055503010");
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
}

Card* PlayScene::getCardById(int id, float x, float y) {
    if (id == 0)        return new Knight(x, y);
    else if (id == 1)   return new Archers(x, y);
    else if (id == 2)   return new Musketeer(x, y);
    else if (id == 3)   return new Skeletons(x, y);
    else if (id == 4)   return new Giant(x, y);
    else if (id == 5)   return new Pekka(x, y);
    else if (id == 6)   return new Wizard(x, y);
    else if (id == 7)   return new HogRider(x, y);
    else if (id == 8)   return new Barbarians(x, y);
    else if (id == 9)   return new Zap(x, y);
    else if (id == 10)  return new Poison(x, y);
    else if (id == 11)  return new Heal(x, y);
    Engine::Allegro5Exception("Card Id Error");
    return nullptr;
}

bool PlayScene::mouseInPlay() {
    Engine::Point nowBlock(pxToBlock(mousePos));
    return (nowBlock.x>=0 && nowBlock.x<=31 && nowBlock.y>=0 && nowBlock.y<=17);
}
bool PlayScene::mouseAtValid() {
    Engine::Point nowBlock(pxToBlock(mousePos));
    if (MapTile[nowBlock.y][nowBlock.x] == TOWER+'0') return false;
    return (nowBlock.x>=17);
}