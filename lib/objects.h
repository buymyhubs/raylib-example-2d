#ifndef OBJECTS_H
#define OBJECTS_H

#include <string>
#include <utility>
#include <vector>

#include "raylib.h"

inline std::vector<Rectangle> solids;
inline int solid_count = 0;

class object {
    private:
        float x;
        float y;
        bool sprite;
        bool text;
        std::string text_value;
        Rectangle collision_rectangle;

        int solid_collision_index;


    public:
        object(
            const float x,
            const float y,
            const bool sprite,
            const bool text,
            std::string text_value,
            int collision_height,
            int collision_width,
            bool solid,
            bool hurts
            )
        {
            this->x = x;
            this->y = y;
            this->sprite = sprite;
            this->text = text;
            this->text_value = std::move(text_value);

            this->collision_rectangle.x = x;
            this->collision_rectangle.y = y;
            this->collision_rectangle.width = collision_width;
            this->collision_rectangle.height = collision_height;

            if (solid) {
                this->solid_collision_index = solid_count++;
                solids.push_back(this->collision_rectangle);
            }
        }

        [[nodiscard]] float get_x() const { return x; }
        [[nodiscard]] float get_y() const { return y; }
        [[nodiscard]] bool get_sprite() const { return sprite; }
        [[nodiscard]] bool get_text() const { return text; }
        std::string get_text_value() { return text_value; }
        [[nodiscard]] Rectangle get_collision_rectangle() const { return collision_rectangle; }


        void set_x(const float x) {
            set_collision_rectangle_x(x);
            this->x = x;
        }
        void set_y(const float y) {
            set_collision_rectangle_y(y);
            this->y = y;
        }
        void set_sprite(const bool sprite) { this->sprite = sprite; }
        void set_text(const bool text) { this->text = text; }
        void set_text_value(const std::string& text_value) { this->text_value = text_value; }

        void set_collision_rectangle_x(const float x) { this->collision_rectangle.x = x; }
        void set_collision_rectangle_y(const float y) { this->collision_rectangle.y = y; }
        void set_collision_rectangle_width(const float width) { this->collision_rectangle.width = width; }
        void set_collision_rectangle_height(const float height) { this->collision_rectangle.height = height; }

        void draw() {
            if (sprite) {
                DrawRectangle(x, y, collision_rectangle.width, collision_rectangle.height, DARKGREEN);
            }
            if (text) {
                DrawText(text_value.c_str(), x, y, 4, RED);
            }
        }
};

class entity : public object {
    private:
        int health;
        int base_speed;

        int current_speed = 0;
    public:
        entity(
            const float x,
            const float y,
            const int health,
            const int base_speed,
            const int collision_height,
            const int collision_width,
            const bool solid,
            const bool hurts)
                :   object(
                    x,
                    y,
                    true,
                    false,
                    "",
                    collision_height,
                    collision_width,
                    solid,
                    hurts
                )
        {
            this->health = health;
            this->base_speed = base_speed;
        }

        [[nodiscard]] int get_health() const { return health; }
        [[nodiscard]] int get_speed() const { return base_speed; }
        [[nodiscard]] bool alive() const { return health > 0; }


        void set_health(const int health) { this->health = health; }
        void set_speed(const int speed) { this->base_speed = speed; }
        void damage(const int damage) { health -= damage; }

        // same as setting x with set_x, but with collision against solid objects
        void set_entity_x(const float x) {
            Rectangle check_rectangle = { x, get_y(), get_collision_rectangle().width, get_collision_rectangle().height };
            for (int i = 0; i < solid_count; i++) {
                if (!CheckCollisionRecs(check_rectangle, solids[i])) {
                    set_x(x);
                }
            }
        }

        // same as setting y with set_y, but with collision against solid objects
        void set_entity_y(const float y) {
            int direction = y > get_y() ? 1 : -1;
            Rectangle check_rectangle = { get_x(), y, get_collision_rectangle().width, get_collision_rectangle().height };
            for (int i = 0; i < solid_count; i++) {
                if (!CheckCollisionRecs(check_rectangle, solids[i])) {
                    set_y(y);
                }
            }
        }

};

class game_player : public entity {
    private:
        float velocity = 0;
        float current_speed = 0;
        const float acceleration = 0.5;

    public: game_player(float start_postion_x, float start_position_y) : entity(
        start_postion_x,
        start_position_y,
        100,
        1,
        8,
        8,
        false,
        false
        ) {

        }
    void set_player_x(const float x) { set_entity_x(x); }
    void set_player_y(const float y) { set_entity_y(y); }
};


#endif //OBJECTS_H
