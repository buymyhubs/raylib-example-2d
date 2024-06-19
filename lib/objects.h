#ifndef OBJECTS_H
#define OBJECTS_H

#include <cmath>
#include <string>
#include <utility>
#include <vector>
#include <iostream>

#include "raylib.h"
#include "check_collision.h"

using std::string, std::vector, std::round;

inline vector<Rectangle> solids;
inline int solid_count = 0;

inline int normalize(const float value) {
    return static_cast<int>(round(value));
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
    string text_value;
    Rectangle collision_rectangle{};

    Color color = BLUE;

    int solid_collision_index;

public:
    object(
        const float x,
        const float y,
        const bool sprite,
        const bool text,
        string text_value,
        const int width,
        const int height,
        const bool solid,
        bool hurts
    ) {
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
    string get_text_value() { return text_value; }
    [[nodiscard]] Rectangle get_collision_rectangle() const { return collision_rectangle; }

    [[nodiscard]] int get_rendered_x() const { return rendered_x; }
    [[nodiscard]] int get_rendered_y() const { return rendered_y; }


    void set_x(const float x_new) {
        this->x = x_new;
        set_collision_rectangle_x(x);
        this->rendered_x = normalize(x);
    }

    void set_y(const float y_new) {
        this->y = y_new;
        set_collision_rectangle_y(y);
        this->rendered_y = normalize(y);
    }

    void set_sprite(const bool sprite) { this->sprite = sprite; }
    void set_text(const bool text) { this->text = text; }
    void set_text_value(const string &text_value) { this->text_value = text_value; }
    void set_color(const Color color) { this->color = color; }

    void set_collision_rectangle_x(const float x) { this->collision_rectangle.x = x; }
    void set_collision_rectangle_y(const float y) { this->collision_rectangle.y = y; }
    void set_collision_rectangle_width(const float width) { this->collision_rectangle.width = collision_width; }
    void set_collision_rectangle_height(const float height) { this->collision_rectangle.height = collision_height; }

    void draw() const {
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
        const int collision_width,
        const int collision_height,
        const bool solid,
        const bool hurts)
        : object(
            x,
            y,
            true,
            false,
            "",
            collision_width,
            collision_height,
            solid,
            hurts
        ) {
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
    void set_entity_x(const float x) {
        const int direction = x > get_x() ? 1 : -1;
        const Rectangle check_rectangle = {
            x, get_y(), get_collision_rectangle().width, get_collision_rectangle().height
        };

        if (auto [can_move, closest_location] = check_all_collision(check_rectangle, solids, direction, true);
            can_move) {
            set_x(x);
        } else {
            set_x(closest_location);
        }
    }

    // same as setting y with set_y, but with collision against solid objects
    void set_entity_y(const float y) {
        const int direction = y > get_y() ? 1 : -1;
        const Rectangle check_rectangle = {
            get_x(), y, get_collision_rectangle().width, get_collision_rectangle().height
        };


        if (auto [can_move, closest_location] = check_all_collision(check_rectangle, solids, direction, false);
            can_move) {
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

public:
    game_player(const float start_position_x, const float start_position_y) : entity(
        start_position_x,
        start_position_y,
        100,
        0.5f,
        4,
        4,
        false,
        false
    ) {
        set_color(WHITE);
    }

    void set_player_x(const float x) { set_entity_x(x); }
    void set_player_y(const float y) { set_entity_y(y); }

    void check_on_ground() {
        const Rectangle check_rectangle = {
            get_x(), get_y() - get_collision_rectangle().height, get_collision_rectangle().width, 1
        };
        for (int i = 0; i < solid_count; i++) {
            if (CheckCollisionRecs(check_rectangle, solids[i])) {
                on_ground = true;
                break;
            }
        }
        on_ground = false;
    }

    void update_player(const float deltaTime) {
        set_player_y(get_y() + deltaTime);

        if (IsKeyDown(KEY_D)) {
            set_player_x(get_x() + get_speed() * deltaTime);
        }
        if (IsKeyDown(KEY_A)) {
            set_player_x(get_x() - get_speed() * deltaTime);
        }

        if (IsKeyPressed(KEY_SPACE) && on_ground) {
            y_velocity = -3.5f;
            jumping = true;
        }

        if (y_velocity < 0.0f) {
            set_player_y(get_y() + y_velocity * deltaTime);
            y_velocity += 0.1f * deltaTime;
        } else {
            y_velocity = 0.0f;
            falling = true;
        }
    }
};

inline auto player = game_player(100, 50);


#endif //OBJECTS_H
