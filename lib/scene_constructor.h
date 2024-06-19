#ifndef SCENE_CONSTRUCTOR_H
#define SCENE_CONSTRUCTOR_H
#include <fstream>
#include <map>

#include "raylib.h"

using std::map, std::string, std::vector, std::fstream;

enum scene {
    DEBUG_LEVEL,
    MENU,
};

inline map<scene, string> scene_names = {
    {DEBUG_LEVEL, "Level_0"},
    {MENU, "menu"},
};


class scene_manager {
private:
    scene current_scene = DEBUG_LEVEL;
    string scene_directory = "../scenes/main/simplified/" + scene_names[current_scene] + "/";
    vector<Texture2D> scene_textures = vector<Texture2D>();
    vector<bool> scene_collision = vector<bool>();
    int collision_line_length = 0;

public:
    scene_manager() {
        set_scene_index(DEBUG_LEVEL);
    }

    [[nodiscard]] scene get_current_scene_index() const {
        return current_scene;
    }

    [[nodiscard]] int get_collision_line_length() const {
        return collision_line_length;
    }

    [[nodiscard]] vector<bool> get_scene_collision() const {
        return scene_collision;
    }

    void set_scene_index(const scene scene) {
        string scene_directory = "../scenes/main/simplified/" + scene_names[scene] + "/";
        current_scene = scene;
    }

    void load_scene() {
        collision_line_length = 0;
        scene_textures.push_back(LoadTexture((scene_directory + "Debug_tiles.png").c_str()));

        fstream file;
        file.open((scene_directory + "Collision.csv").c_str());

        string line;

        bool get_collision_line_length = true;
        while (std::getline(file, line, ',')) {
            if (line.find('1') != std::string::npos) {
                scene_collision.push_back(true);
            } else if (line.find('0') != std::string::npos) {
                scene_collision.push_back(false);
            }

            if (line.find('\n') != std::string::npos) {
                get_collision_line_length = false;
            }

            if (get_collision_line_length) {
                collision_line_length++;
            }
        }

        file.close();
    }

    void draw_scene() const {
        for (const auto &scene_texture: scene_textures) {
            DrawTexture(scene_texture, 0, 0, WHITE);
        }
    }
};

inline auto scene = scene_manager();

#endif //SCENE_CONSTRUCTOR_H
