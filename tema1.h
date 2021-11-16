#pragma once

#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/object2D.h"
#include "components/simple_scene.h"
#include <vector>
#include <iostream>

#include "core/engine.h"
#include "utils/gl_utils.h"
#include <chrono>
#include <vector>
#include <iostream>
#include <string>
#include <string_view>

#define NO_OBSTACLES 80
#define NO_ENEMIES 30
#define AMMO 10
#define LEN 20


namespace m1
{
    class tema1 : public gfxc::SimpleScene
    {
     public:
        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

     public:
        tema1();
        ~tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void DrawScene(glm::mat3 visMatrix);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;

        // Sets the logic space and view space
        // logicSpace: { x, y, width, height }
        // viewSpace: { x, y, width, height }
        glm::mat3 VisualizationTransf2D(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);
        void SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

        // check if hero collides with obstacles
        bool tema1::check_obstacle_collision(float x_hero, float y_hero, float len_hero, float x, float y, float len);
        // dont let moving instances(obstacle, projectile, hero) to go over the map
        bool tema1::check_map_limits(float x_hero, float y_hero, float length);
        // check if enemies are dead
        bool tema1::check_dead(float x_enemy, float y_enemy, float len_enemy, float x_bullet, float y_bullet, float len_bullet);

     protected:
        float length;
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        LogicSpace logicSpace_minimap;
        glm::mat3 modelMatrix, visMatrix;

        float length_hero, length_hand;
        float angularStep;
        float angularStepCopy;

        struct Obstacle {
            int id;
            float x, y, length;
        };

        struct Enemy {
            int id;
            float x, y, length;
            // coord to translate the enemy
            float follow_x, follow_y;
            bool isDead = false;
            float speed;

            // used for respawn
            std::chrono::time_point<std::chrono::steady_clock> start;

            glm::mat3 modelMatrix;
            glm::mat3 modelMatrix_eyel;
            glm::mat3 modelMatrix_eyer;
        };

        struct Hero {
            int id;
            float x, y, length;
            float x_hero, y_hero;
            float health = 100;
            int score = 0;
        }; 
        
        struct Bullet {
            int id;
            float length;
            // coord to translate the bullet
            float follow_x, follow_y;
            bool isShot;
            float max_distance;
            float angularStepCopy;

            glm::mat3 modelMatrix;
        };

        struct Obstacle obstacles[NO_OBSTACLES];
        struct Enemy enemies[NO_ENEMIES];
        struct Hero hero;
        struct Bullet bullets[AMMO];

        // bullet
        int bullet_count;

        // firerate
        std::chrono::time_point<std::chrono::steady_clock> start;
        std::chrono::time_point<std::chrono::steady_clock> end;
        bool cooldown = false;

        // enemy respawn
        int last_id = 0;
        std::chrono::time_point<std::chrono::steady_clock> respawn_time;

        // hero health update
        int last_health;
        // 25 * 4 = 100 damage
        float full_health = 1;

        // map
        float length_map = 45;

        // pickups
        float pickup_health_x, pickup_health_y, pickup_health_taken;
        float pickup_freeze_x, pickup_freeze_y, pickup_freeze_taken;
    };
}   // namespace m1
