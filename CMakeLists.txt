cmake_minimum_required(VERSION 3.27)
project(ArenaLegends)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Resource)

file(COPY Resource/audios DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource/fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource/images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY allegro_monolith-5.2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(
    ArenaLegends
    main.cpp

    Engine/Allegro5Exception.cpp
    Engine/Allegro5Exception.hpp
    Engine/AudioHelper.cpp
    Engine/AudioHelper.hpp
    Engine/Collider.cpp
    Engine/Collider.hpp
    Engine/GameEngine.cpp
    Engine/GameEngine.hpp
    Engine/Group.cpp
    Engine/Group.hpp
    Engine/IControl.cpp
    Engine/IControl.hpp
    Engine/IObject.cpp
    Engine/IObject.hpp
    Engine/IScene.cpp
    Engine/IScene.hpp
    Engine/LOG.cpp
    Engine/LOG.hpp
    Engine/Point.cpp
    Engine/Point.hpp
    Engine/Resources.cpp
    Engine/Resources.hpp
    Engine/Sprite.cpp
    Engine/Sprite.hpp
    Engine/GameData.cpp
    Engine/GameData.hpp
    Engine/UserData.cpp
    Engine/UserData.hpp

    UI/Component/Image.cpp
    UI/Component/Image.hpp
    UI/Component/ImageButton.cpp
    UI/Component/ImageButton.hpp
    UI/Component/Label.cpp
    UI/Component/Label.hpp
    UI/Component/Slider.cpp
    UI/Component/Slider.hpp
    UI/Component/Rectangle.cpp
    UI/Component/Rectangle.hpp
    UI/Component/RectangleButton.cpp
    UI/Component/RectangleButton.hpp

    Scene/LoadScene.cpp
    Scene/LoadScene.hpp
    Scene/LobbyScene.cpp
    Scene/LobbyScene.hpp
    Scene/CardSetScene.cpp
    Scene/CardSetScene.hpp
    Scene/SettingScene.cpp
    Scene/SettingScene.hpp
    Scene/PlayScene.cpp
    Scene/PlayScene.hpp

    Tower/Tower.cpp
    Tower/Tower.hpp
    Tower/MainTower.cpp
    Tower/MainTower.hpp
    Tower/SideTower.cpp
    Tower/SideTower.hpp

    Card/Card.cpp
    Card/Card.hpp
    Card/Army/Knight.cpp
    Card/Army/Knight.hpp
    Card/Army/Archers.cpp
    Card/Army/Archers.hpp
    Card/Army/Musketeer.cpp
    Card/Army/Musketeer.hpp
    Card/Army/Skeletons.cpp
    Card/Army/Skeletons.hpp
    Card/Army/Giant.cpp
    Card/Army/Giant.hpp
    Card/Army/Pekka.cpp
    Card/Army/Pekka.hpp
    Card/Army/Wizard.cpp
    Card/Army/Wizard.hpp
    Card/Army/HogRider.cpp
    Card/Army/HogRider.hpp
    Card/Army/Barbarians.cpp
    Card/Army/Barbarians.hpp
    Card/Spell/Zap.cpp
    Card/Spell/Zap.hpp
    Card/Spell/Poison.cpp
    Card/Spell/Poison.hpp
    Card/Spell/Heal.cpp
    Card/Spell/Heal.hpp

    Entity/Army/Army.cpp
    Entity/Army/Army.hpp
    Entity/Spell/Spell.cpp
    Entity/Spell/Spell.hpp

    Helper/Helper.cpp
    Helper/Helper.hpp
)

IF (WIN32)
    target_include_directories(ArenaLegends PUBLIC C:/allegro/include)
    target_link_directories(ArenaLegends PUBLIC C:/allegro/lib)
    target_compile_options(ArenaLegends PUBLIC ${ALLEGRO5_CFLAGS_OTHER})
    target_link_libraries(ArenaLegends liballegro_monolith)
ELSE()
    find_package(PkgConfig)
    pkg_check_modules(ALLEGRO5 REQUIRED allegro-5 allegro_main-5 allegro_font-5 allegro_dialog-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5)
    target_include_directories(ArenaLegends PUBLIC lib)
    target_include_directories(ArenaLegends PUBLIC ${ALLEGRO5_INCLUDE_DIRS})
    target_compile_options(ArenaLegends PUBLIC ${ALLEGRO5_INCLUDE_DIRS})
    target_link_libraries(ArenaLegends ${ALLEGRO5_LIBRARIES})
    target_link_directories(ArenaLegends PUBLIC ${ALLEGRO5_LIBRARY_DIRS})
ENDIF()