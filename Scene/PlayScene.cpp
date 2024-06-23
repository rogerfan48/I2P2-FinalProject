#include "PlayScene.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_audio.h>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

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
#include "Scene/LobbyScene.hpp"
#include "Card/AllCard.hpp"
#include "Entity/Army/Army.hpp"

const int PlayScene::BlockSize = 50;
const int PlayScene::MapBlockWidth = 32, PlayScene::MapBlockHeight = 18;
const int PlayScene::CardSetHeight = 6;
const int PlayScene::MapDiff = 100;
const int PlayScene::ElixirProcessWidth = 800;

std::map<int, ALLEGRO_COLOR> PlayScene::TileColor;
std::vector<std::string> PlayScene::MapTile;

static int halfW, halfH;
static Engine::Sprite* turtle;
static int turtlePicture;

void PlayScene::Initialize() {
    std::cout << onlineMode << std::endl;
    gameTime = 184;
    tick = 0;
    turtlePicture = 1;
    victory = false;
    halfW = Engine::GameEngine::GetInstance().GetScreenSize().x / 2;
    halfH = Engine::GameEngine::GetInstance().GetScreenSize().y / 2;

    gameData.A.initGame();
    selectedCard = nullptr;
    instanceIDCounter = 3;  // 0: Main Tower, 1: Upper Tower, 2: Lower Tower
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

    AddNewObject(A_SpellGroup = new Group());
    AddNewObject(B_SpellGroup = new Group());

    AddNewObject(A_TowerGroup = new Group());
    A_TowerPtrMap.insert({0, new MainTower(-1, 0, 29, 9, 0)});
    A_TowerPtrMap.insert({1, new SideTower(-2, 1, 25, 3, 0)});
    A_TowerPtrMap.insert({2, new SideTower(-2, 2, 25,14, 0)});
    for (int i=0; i<3; i++) A_TowerGroup->AddNewObject(A_TowerPtrMap[i]);
    AddNewObject(B_TowerGroup = new Group());
    B_TowerPtrMap.insert({0, new MainTower(-1, 0,  3, 9, 1)});
    B_TowerPtrMap.insert({1, new SideTower(-2, 1,  6, 3, 1)});
    B_TowerPtrMap.insert({2, new SideTower(-2, 2,  6,14, 1)});
    for (int i=0; i<3; i++) B_TowerGroup->AddNewObject(B_TowerPtrMap[i]);

    AddNewObject(A_ArmyGroup = new Group());
    AddNewObject(B_ArmyGroup = new Group());

    AddNewObject(placePreview = new Engine::Rectangle(0, 0, BlockSize, BlockSize, al_map_rgba(255, 255, 255, 80)));
    AddNewObject(placePreviewBorder = new Engine::RectangleBorder(0, 0, BlockSize-6, BlockSize-6, al_map_rgba(255, 255, 255, 220), 6));
    AddNewObject(placeReviewName = new Engine::Label("", "recharge.otf", 28, 0, 0, 255, 255, 255, 255));
    placePreview->Enable = false;
    placePreviewBorder->Enable = false;
    placeReviewName->Enable = false;
    
    AddNewObject(WeaponGroup  = new Group());

    // AddNewObject(MapBorderGroup = new Group());
    // MapBorderGroup->AddNewObject(new Engine::Rectangle(0, 0, 2*MapDiff+MapBlockWidth*BlockSize, 2*BlockSize, TileColor[ROCK]));
    // MapBorderGroup->AddNewObject(new Engine::Rectangle(0, 0, 2*BlockSize, 2*MapDiff+MapBlockHeight*BlockSize, TileColor[ROCK]));
    // MapBorderGroup->AddNewObject(new Engine::Rectangle(0, (MapBlockHeight+2)*BlockSize, 2*MapDiff+MapBlockWidth*BlockSize, 2*BlockSize, TileColor[ROCK]));
    // MapBorderGroup->AddNewObject(new Engine::Rectangle((MapBlockWidth+2)*BlockSize, 0, 2*BlockSize, 2*MapDiff+MapBlockHeight*BlockSize, TileColor[ROCK]));

    AddNewObject(TimeDisplayGroup = new Group());
    TimeDisplayGroup->AddNewObject(new Engine::Label("", "recharge.otf", 60, 220+3, 1050, 0, 0, 0, 255, 0.5, 0.5, 0));
    TimeDisplayGroup->AddNewObject(new Engine::Label("", "recharge.otf", 60, 220-3, 1050, 0, 0, 0, 255, 0.5, 0.5, 0));
    TimeDisplayGroup->AddNewObject(new Engine::Label("", "recharge.otf", 60, 220, 1050+3, 0, 0, 0, 255, 0.5, 0.5, 0));
    TimeDisplayGroup->AddNewObject(new Engine::Label("", "recharge.otf", 60, 220, 1050-3, 0, 0, 0, 255, 0.5, 0.5, 0));
    TimeDisplayGroup->AddNewObject(new Engine::Label("", "recharge.otf", 60, 220, 1050, 255, 255, 255, 255, 0.5, 0.5, 0));
    isTimeShown = false;
    timeShown = 181;

    AddNewObject(ElixirGroup = new Group());
    ElixirGroup->AddNewObject(new Engine::Rectangle(890, 1020, ElixirProcessWidth+10, 60, al_map_rgb(30, 30, 30)));
    ElixirGroup->AddNewObject(new Engine::Rectangle(895, 1025, ElixirProcessWidth, 50, al_map_rgb(100, 100, 100)));
    ElixirGroup->AddNewObject(elixirProcess = new Engine::Rectangle(895, 1025, ElixirProcessWidth*7/10+5, 50, al_map_rgb(255, 0, 255)));
    for (int i=1; i<10; i++)
        ElixirGroup->AddNewObject(new Engine::Rectangle(895+3.5+80*i, 1025, 5, 50, al_map_rgb(60, 60, 60)));
    ElixirGroup->AddNewObject(new Engine::Image("elixir.png", 900-45, 1000+15, 70, 70));
    elixirNumber.resize(5);
    ElixirGroup->AddNewObject(elixirNumber[0] = new Engine::Label(std::to_string((int)gameData.A.elixir), "recharge.otf", 34, 893-2, 1050, 0, 0, 0, 255, 0.5, 0.5));
    ElixirGroup->AddNewObject(elixirNumber[1] = new Engine::Label(std::to_string((int)gameData.A.elixir), "recharge.otf", 34, 893+2, 1050, 0, 0, 0, 255, 0.5, 0.5));
    ElixirGroup->AddNewObject(elixirNumber[2] = new Engine::Label(std::to_string((int)gameData.A.elixir), "recharge.otf", 34, 893, 1050-2, 0, 0, 0, 255, 0.5, 0.5));
    ElixirGroup->AddNewObject(elixirNumber[3] = new Engine::Label(std::to_string((int)gameData.A.elixir), "recharge.otf", 34, 893, 1050+2, 0, 0, 0, 255, 0.5, 0.5));
    ElixirGroup->AddNewObject(elixirNumber[4] = new Engine::Label(std::to_string((int)gameData.A.elixir), "recharge.otf", 34, 893, 1050, 255, 255, 255, 255, 0.5, 0.5));

    // test : but why it can't use.
    B_ArmyPtrMap.insert({1, new Army(5,1,2,2,"P.E.K.K.A.",0,3760, 816, 1.8, 2, 1.2, 5,0.7,1)});
    B_ArmyToBeDeployed.push({gameTime-0.5, B_ArmyPtrMap[1]});
    for (int i=2; i<17; i++) {
        B_ArmyPtrMap.insert({i, new Army(3, i, 2, 16, "Skeletons", 0, 81, 81, 1, 4, 1.2, 5, 0.5, 1)});
        B_ArmyToBeDeployed.push({gameTime-0.5, B_ArmyPtrMap[i]});
    }
    
    // test
    AddNewObject(turtle = new Engine::Sprite("loading/1.jpg", halfW, halfH, 26*77, 26*54, 0.5, 0.5));
    turtle->Tint = al_map_rgba(255, 255, 255, 0);
}
void PlayScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();

    cardPointer.clear();

    A_TowerPtrMap.clear();
    A_TowerToBeRemoved.clear();
    A_ArmyPtrMap.clear();
    A_ToBeDead.clear();
    while (!A_ArmyToBeDeployed.empty()) A_ArmyToBeDeployed.pop();
    while (!A_SpellToBeDeployed.empty()) A_SpellToBeDeployed.pop();
    B_TowerPtrMap.clear();
    B_TowerToBeRemoved.clear();
    B_ArmyPtrMap.clear();
    B_ToBeDead.clear();
    while (!B_ArmyToBeDeployed.empty()) B_ArmyToBeDeployed.pop();
    while (!B_SpellToBeDeployed.empty()) B_SpellToBeDeployed.pop();

    elixirNumber.clear();
    WeaponToBeDelete.clear();

    gameData.A.availableCards.clear();
    while (!gameData.A.nextCardQueue.empty()) gameData.A.nextCardQueue.pop();
    gameData.B.availableCards.clear();
    while (!gameData.B.nextCardQueue.empty()) gameData.A.nextCardQueue.pop();

    while (!commandFromServer.empty()) commandFromServer.pop();
    while (!commandToServer.empty()) commandToServer.pop();

    IScene::Terminate();
}

void PlayScene::Update(float deltaTime) {
    gameTime -= deltaTime;
    tick += deltaTime;
    if (tick > 500.5 && turtlePicture < (int)((tick-500.5)*30+1)) {
        gameTime = 10000;
        if (victory) {
            turtlePicture = (int)((tick-500.5)*30+1);
            turtle->bmp = Engine::Resources::GetInstance().GetBitmap("loading/" + std::to_string(turtlePicture) + ".jpg", 26*77, 26*54);
        }
        if (tick < 501.6) turtle->Tint = al_map_rgba(255, 255, 255, std::min((int)((tick-500.5)*255), 255));
        turtle->Update(deltaTime);
    }
    if (tick >= 508) Engine::GameEngine::GetInstance().ChangeScene("lobby");
    
    if (gameTime >= 181) return;
    IScene::Update(deltaTime);

    // time:
    if (gameTime < 181 && gameTime >= 0) {
        if (!isTimeShown) {
            for (auto i : TimeDisplayGroup->GetObjects()) {
                Engine::Label* j = dynamic_cast<Engine::Label*>(i);
                j->Enable = true;
            }
            isTimeShown = true;
        }
        if (timeShown > int(gameTime)) {
            timeShown = int(gameTime);
            for (auto i : TimeDisplayGroup->GetObjects()) {
                Engine::Label* j = dynamic_cast<Engine::Label*>(i);
                j->Text = timeString(gameTime);
            }
        }
    } else if (isTimeShown) {
        for (auto i : TimeDisplayGroup->GetObjects()) {
            Engine::Label* j = dynamic_cast<Engine::Label*>(i);
            j->Enable = false;
        }
    }

    // ToBeDeployed:
    if (!A_ArmyToBeDeployed.empty() && A_ArmyToBeDeployed.front().first > gameTime) {
        A_ArmyGroup->AddNewObject(A_ArmyToBeDeployed.front().second);
        A_ArmyToBeDeployed.pop();
    }
    if (!A_SpellToBeDeployed.empty() && A_SpellToBeDeployed.front().first > gameTime) {
        A_SpellGroup->AddNewObject(A_SpellToBeDeployed.front().second);
        A_SpellToBeDeployed.pop();
    }
    if (!B_ArmyToBeDeployed.empty() && B_ArmyToBeDeployed.front().first > gameTime) {
        B_ArmyGroup->AddNewObject(B_ArmyToBeDeployed.front().second);
        B_ArmyToBeDeployed.pop();
    }
    if (!B_SpellToBeDeployed.empty() && B_SpellToBeDeployed.front().first > gameTime) {
        B_SpellGroup->AddNewObject(B_SpellToBeDeployed.front().second);
        B_SpellToBeDeployed.pop();
    }

    // Elixir:
    gameData.A.elixir += deltaTime * gameData.elixirSpeed;
    if (gameData.A.elixir > 10) gameData.A.elixir = 10;
    elixirProcess->Size.x = (gameData.A.elixir)*ElixirProcessWidth/10;
    for (auto i : elixirNumber) i->Text = std::to_string((int)gameData.A.elixir);

    // Spell timeout:
    for (auto i : A_SpellGroup->GetObjects()) {
        Spell* j = dynamic_cast<Spell*>(i);
        if (j->time < 0) A_SpellGroup->RemoveObject(i->GetObjectIterator());
    }
    for (auto i : B_SpellGroup->GetObjects()) {
        Spell* j = dynamic_cast<Spell*>(i);
        if (j->time < 0) A_SpellGroup->RemoveObject(i->GetObjectIterator());
    }

    // ToBeDead:
    for (int i : A_ToBeDead) {
        for (auto k : A_ArmyPtrMap[i]->beTargeted) k->target = nullptr;
        for (auto k : WeaponGroup->GetObjects()) {
            Bullet* j = dynamic_cast<Bullet*>(k);
            if (j->target == A_ArmyPtrMap[i]) WeaponToBeDelete.insert(j);
        }
        A_ArmyGroup->RemoveObject(A_ArmyPtrMap[i]->GetObjectIterator());
        A_ArmyPtrMap.erase(i);
    }
    A_ToBeDead.clear();
    for (int i : B_ToBeDead) {
        for (auto k : B_ArmyPtrMap[i]->beTargeted) k->target = nullptr;
        for (auto k : WeaponGroup->GetObjects()) {
            Bullet* j = dynamic_cast<Bullet*>(k);
            if (j->target == B_ArmyPtrMap[i]) WeaponToBeDelete.insert(j);
        }
        B_ArmyGroup->RemoveObject(B_ArmyPtrMap[i]->GetObjectIterator());
        B_ArmyPtrMap.erase(i);
    }
    B_ToBeDead.clear();
    
    // ToBeRemoved:
    for (int i : A_TowerToBeRemoved) {
        // std::cout<<"start remove\n";
        for (auto k : A_TowerPtrMap[i]->beTargeted) k->target = nullptr;
        // std::cout<<"target remove\n";
        for (auto k : WeaponGroup->GetObjects()) {
            Bullet* j = dynamic_cast<Bullet*>(k);
            if (j->target == A_TowerPtrMap[i]) WeaponToBeDelete.insert(j);
        }
        // std::cout<<"weapon remove\n";
        A_TowerGroup->RemoveObject(A_TowerPtrMap[i]->GetObjectIterator());
        A_TowerPtrMap.erase(i);
    }
    A_TowerToBeRemoved.clear();
    for (int i : B_TowerToBeRemoved) {
        for (auto k : B_TowerPtrMap[i]->beTargeted) k->target = nullptr;
        for (auto k : WeaponGroup->GetObjects()) {
            Bullet* j = dynamic_cast<Bullet*>(k);
            if (j->target == B_TowerPtrMap[i]) WeaponToBeDelete.insert(j);
        }
        B_TowerGroup->RemoveObject(B_TowerPtrMap[i]->GetObjectIterator());
        B_TowerPtrMap.erase(i);
    }
    B_TowerToBeRemoved.clear();

    // WeaponToBeDelete
    for (auto i : WeaponToBeDelete) {
        WeaponGroup->RemoveObject(i->GetObjectIterator());
    }
    WeaponToBeDelete.clear();
}

void PlayScene::Draw() const {
    IScene::Draw();
}

// TODO: TO PLACE B, follow the steps like below A_ArmyPtrMap/A_ArmyToBeDeployed/A_SpellToBeDeployed
void PlayScene::OnMouseDown(int button, int mx, int my) {
    if (gameTime >= 181) return;
    if ((button & 1) && selectedCard != nullptr && mouseInPlay() && 
        ((selectedCard->cardType==ARMY && mouseAtValid()) || (selectedCard->cardType==SPELL))) {
            if (gameData.A.elixir < selectedCard->cost) return;
            else gameData.A.elixir -= selectedCard->cost;
            Engine::Point nowBlock(pxToBlock(mousePos));
            if (selectedCard->cardType == ARMY) {
                selectedCard->placeArmy(nowBlock.x, nowBlock.y);
            } else {
                A_SpellToBeDeployed.push({gameTime-0.5, selectedCard->placeSpell(instanceIDCounter++, nowBlock.x, nowBlock.y)});
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
    if (gameTime >= 181) return;
    mousePos = Engine::Point(mx, my);
    Engine::Point nowBlock(pxToBlock(mousePos));
    if (mouseInPlay()) {
        if (selectedCard->cardType == ARMY) {
            prohibitedMask->Enable = true;
            prohibitedMaskBorder->Enable = true;
        }
        if ((selectedCard->cardType==ARMY && mouseAtValid()) || (selectedCard->cardType==SPELL)) {
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

void PlayScene::launchBullet(Bullet* bullet) {
    WeaponGroup->AddNewObject(bullet);
}

void PlayScene::showWinAnimation() {
    victory = true;
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    bgmInstance = AudioHelper::PlaySample("turtle.ogg", false, AudioHelper::BGMVolume);
}
void PlayScene::showLoseAnimation() {
    turtle->bmp = Engine::Resources::GetInstance().GetBitmap("loading/die.jpg", 26*77, 26*54);
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    bgmInstance = AudioHelper::PlaySample("lose.ogg", false, AudioHelper::BGMVolume);     // I will find new music later.
}

void PlayScene::writeToServer(tcp::socket& socket) {
    PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    if (PS->commandToServer.empty()) return;
    try {
        boost::asio::write(socket, boost::asio::buffer(PS->commandToServer.front()));
        PS->commandToServer.pop();
    } catch (std::exception& e) {
        std::cerr << "Exception in write_to_server: " << e.what() << "\n";
    }
}
void PlayScene::readFromServer(tcp::socket& socket) {
    PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    try {
        boost::asio::streambuf buf;
        boost::asio::read_until(socket, buf, "\n");
        std::istream is(&buf);
        std::string line;
        std::getline(is, line);
        std::cout << "From server: " << line << std::endl;
        // : normal mode
        // !: pair
        // ?: break
        if (line[0] == '!')  {
            LobbyScene* LS = dynamic_cast<LobbyScene*>(Engine::GameEngine::GetInstance().GetScene("lobby"));
            LS->pairSuccessfully = true;
        } else if (line[0] == '?') {
            socket.close();
            PS->commandFromServer.push(line);   // TODO: 對手已離線
        } else PS->commandFromServer.push(line);
    } catch (std::exception& e) {
        std::cerr << "Exception in read_from_server: " << e.what() << "\n";
    }
}