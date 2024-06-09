#ifndef OBJECTS_H
#define OBJECTS_H

#include <string>
#include <utility>
#include <vector>
#include <math.h>
#include <iostream>

#include "raylib.h"

inline std::vector<Rectangle> solids;
inline int solid_count = 0;

inline int normalize(const float value) {
    return (int)round(value);
}

class object {
    private:

        float x;
        float y;

        int rendered_x;
        int rendered_y;

        float collision_width;
        float collision_height;

        int width;
        int height;

        bool sprite;
        bool text;
        std::string text_value;
        Rectangle collision_rectangle;

        Color color = BLUE;

        int solid_collision_index;


    public:
        object(
            const float x,
            const float y,
            const bool sprite,
            const bool text,
            std::string text_value,
            int width,
            int height,
            bool solid,
            bool hurts
            )
        {
            this->x = x;
            this->y = y;

            this->rendered_x = normalize(x);
            this->rendered_y = normalize(y);

            this->width = width;
            this->height = height;

            this->collision_width = width;
            this->collision_height = height;

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

        [[nodiscard]] int get_rendered_x() const { return rendered_x; }
        [[nodiscard]] int get_rendered_y() const { return rendered_y; }


        void set_x(const float x_new) {
            this->x=x_new;
            set_collision_rectangle_x(x);
            this->rendered_x = normalize(x);
        }
        void set_y(const float y_new) {
            this->y=y_new;
            set_collision_rectangle_y(y);
            this->rendered_y = normalize(y);
        }
        void set_sprite(const bool sprite) { this->sprite = sprite; }
        void set_text(const bool text) { this->text = text; }
        void set_text_value(const std::string& text_value) { this->text_value = text_value; }
        void set_color(const Color color) { this->color = color; }

        void set_collision_rectangle_x(const float x) { this->collision_rectangle.x = x; }
        void set_collision_rectangle_y(const float y) { this->collision_rectangle.y = y; }
        void set_collision_rectangle_width(const float width) { this->collision_rectangle.width = collision_width; }
        void set_collision_rectangle_height(const float height) { this->collision_rectangle.height = collision_height; }

        void draw() {
            if (sprite) {
                DrawRectangle(rendered_x, rendered_y, width, height, color);
            }
            if (text) {
                DrawText(text_value.c_str(), x, y, 4, RED);
            }
        }
};

class entity : public object {
    private:
        int health;
        float base_speed;

        int current_speed = 0;
    public:
        entity(
            const float x,
            const float y,
            const int health,
            const float base_speed,
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
        [[nodiscard]] float get_speed() const { return base_speed; }
        [[nodiscard]] bool alive() const { return health > 0; }


        void set_health(const int health) { this->health = health; }
        void set_speed(const float speed) { this->base_speed = speed; }
        void damage(const int damage) { health -= damage; }

        // same as setting x with set_x, but with collision against solid objects
        void set_entity_x(float x) {
            int direction = x > get_x() ? 1 : -1;
            Rectangle check_rectangle = { x, get_y(), get_collision_rectangle().width, get_collision_rectangle().height };
            bool can_move = true;
            int closest_location = 0;
            for (int i = 0; i < solid_count; i++) {
                if (CheckCollisionRecs(check_rectangle, solids[i])) {
                    can_move = false;

                    if (direction > 0) {
                        closest_location = solids[i].x - get_collision_rectangle().width;
                    } else {
                        closest_location = solids[i].x + solids[i].width;
                    }
                };
            }

            if (can_move) {
                set_x(x);
            } else {
                set_x(closest_location);
            }
        }

        // same as setting y with set_y, but with collision against solid objects
        void set_entity_y(float y) {
            int direction = y > get_y() ? 1 : -1;
            Rectangle check_rectangle = { get_x(), y, get_collision_rectangle().width, get_collision_rectangle().height };
            bool can_move = true;
            int closest_location = 0;
            for (int i = 0; i < solid_count; i++) {
                if (CheckCollisionRecs(check_rectangle, solids[i])) {
                   can_move = false;

                    if (direction > 0) {
                        closest_location = solids[i].y - get_collision_rectangle().height;
                    } else {
                        closest_location = solids[i].y + solids[i].height;
                    }
                };
            }

            if (can_move) {
                set_y(y);
            } else {
                set_y(closest_location);
            }
        }

};

class game_player : public entity {
    private:
        float x_velocity = 0;
        float y_velocity = 0;

        float current_speed = 0;
        const float acceleration = 0.1f;

        bool jumping = false;
        bool falling = false;
        bool on_ground = true;


    public: game_player(float start_postion_x, float start_position_y) : entity(
        start_postion_x,
        start_position_y,
        100,
        0.5f,
        8,
        8,
        false,
        false
        ) {
            set_color(WHITE);
        }
    void set_player_x(const float x) { set_entity_x(x); }
    void set_player_y(const float y) { set_entity_y(y); }

    void check_on_ground() {
        Rectangle check_rectangle = { get_x(), get_y()-get_collision_rectangle().height, get_collision_rectangle().width, 1 };
        for (int i = 0; i < solid_count; i++) {
            if (CheckCollisionRecs(check_rectangle, solids[i])) {
                on_ground = true;
                break;
            }
        }
        on_ground = false;
    }

    void update_player(float deltaTime) {

        if (deltaTime > 10) {
            deltaTime = 0;
        }

        set_player_y(get_y() + deltaTime);

        if (IsKeyDown(KEY_D)) {
            set_player_x(get_x() + get_speed()*deltaTime);
        }
        if (IsKeyDown(KEY_A)) {
            set_player_x(get_x() - get_speed()*deltaTime);
        }

        if (IsKeyPressed(KEY_SPACE) && on_ground) {
            y_velocity = -3.0f;
            jumping = true;
        }

        if (y_velocity < 0.0f) {
            set_player_y(get_y() + y_velocity*deltaTime);
            y_velocity += 0.1f*deltaTime;
        } else {
            y_velocity = 0.0f;
            falling = true;
        }

    }
};

inline game_player player = game_player(100,50);


#endif //OBJECTS_H
