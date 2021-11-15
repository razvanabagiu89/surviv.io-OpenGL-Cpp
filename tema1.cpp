#include "lab_m1/tema1/tema1.h"
#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/object2D.h"


using namespace std;
using namespace m1;


tema1::tema1()
{
}


tema1::~tema1()
{
}

// check if bullets kill enemies
bool tema1::check_dead(float x_enemy, float y_enemy, float len_enemy, float x_bullet, float y_bullet, float len_bullet) {

    if (x_enemy < x_bullet + len_enemy && x_enemy + len_enemy > x_bullet && y_enemy < y_bullet + len_bullet && len_enemy + y_enemy > y_bullet) {
        return true;
    }
    else {
        return false;
    }

}

// check if bullets or hero collide with obstacles
bool tema1::check_obstacle_collision(float x_hero, float y_hero, float len_hero, float x, float y, float len) {

    if (x_hero < x + len_hero && x_hero + len_hero > x && y_hero < y + len && len_hero + y_hero > y) {
            return true;
    }
    else {
        return false;
    }

}

// check map limits for every moving instance: hero, bullets, enemies
bool tema1::check_map_limits(float x_hero, float y_hero, float length) {


    x_hero -= length ; 
    y_hero -= length ; 

    if (x_hero + length > 0.0f && x_hero + length < length_map - length && y_hero + length < length_map - length && y_hero + length > 0.0f) {
        return false;
    }
    else {
        return true;
    }
}


void tema1::Init()
{

    using namespace std::literals;
    start = std::chrono::steady_clock::now();  
    respawn_time = std::chrono::steady_clock::now();

    // normal length used
    length = 0.99f;
    // smaller length used for hands, bullets
    length_hand = length/3;


    // map creation

    { // obstacles creation

        // small cube left down
        obstacles[0].id = 0; obstacles[0].x = 5; obstacles[0].y = 5; obstacles[0].length = length;
        obstacles[1].id = 1; obstacles[1].x = 5; obstacles[1].y = 6; obstacles[1].length = length;
        obstacles[2].id = 2; obstacles[2].x = 6; obstacles[2].y = 5; obstacles[2].length = length;
        obstacles[3].id = 3; obstacles[3].x = 6; obstacles[3].y = 6; obstacles[3].length = length;

        // small cube right down
        obstacles[4].id = 4; obstacles[4].x = 35; obstacles[4].y = 5; obstacles[4].length = length;
        obstacles[5].id = 5; obstacles[5].x = 35; obstacles[5].y = 6; obstacles[5].length = length;
        obstacles[6].id = 6; obstacles[6].x = 36; obstacles[6].y = 5; obstacles[6].length = length;
        obstacles[7].id = 7; obstacles[7].x = 36; obstacles[7].y = 6; obstacles[7].length = length;

        // line middle right
        obstacles[8].id = 8; obstacles[8].x = 30; obstacles[8].y = 21; obstacles[8].length = length;
        obstacles[9].id = 9; obstacles[9].x = 31; obstacles[9].y = 21; obstacles[9].length = length;
        obstacles[10].id = 10; obstacles[10].x = 32; obstacles[10].y = 21; obstacles[10].length = length;
        obstacles[11].id = 11; obstacles[11].x = 33; obstacles[11].y = 21; obstacles[11].length = length;
        obstacles[12].id = 12; obstacles[12].x = 29; obstacles[12].y = 21; obstacles[12].length = length;
        obstacles[13].id = 13; obstacles[13].x = 28; obstacles[13].y = 21; obstacles[13].length = length;
        obstacles[14].id = 14; obstacles[14].x = 27; obstacles[14].y = 21; obstacles[14].length = length;
        obstacles[15].id = 15; obstacles[15].x = 26; obstacles[15].y = 21; obstacles[15].length = length;

        // Z 
        obstacles[16].id = 16; obstacles[16].x = 12; obstacles[16].y = 30; obstacles[16].length = length;
        obstacles[17].id = 17; obstacles[17].x = 12; obstacles[17].y = 29; obstacles[17].length = length;
        obstacles[18].id = 18; obstacles[18].x = 12; obstacles[18].y = 28; obstacles[18].length = length;
        obstacles[19].id = 19; obstacles[19].x = 12; obstacles[19].y = 27; obstacles[19].length = length;
        obstacles[20].id = 20; obstacles[20].x = 12; obstacles[20].y = 26; obstacles[20].length = length;
        obstacles[21].id = 21; obstacles[21].x = 12; obstacles[21].y = 25; obstacles[21].length = length;
        obstacles[22].id = 22; obstacles[22].x = 12; obstacles[22].y = 24; obstacles[22].length = length;
        obstacles[23].id = 23; obstacles[23].x = 12; obstacles[23].y = 23; obstacles[23].length = length;
        obstacles[24].id = 24; obstacles[24].x = 13; obstacles[24].y = 23; obstacles[24].length = length;
        obstacles[25].id = 25; obstacles[25].x = 14; obstacles[25].y = 23; obstacles[25].length = length;
        obstacles[26].id = 26; obstacles[26].x = 15; obstacles[26].y = 23; obstacles[26].length = length;
        obstacles[27].id = 27; obstacles[27].x = 11; obstacles[27].y = 30; obstacles[27].length = length;
        obstacles[28].id = 28; obstacles[28].x = 10; obstacles[28].y = 30; obstacles[28].length = length;
        obstacles[29].id = 29; obstacles[29].x = 9;  obstacles[29].y = 30; obstacles[29].length = length;
        obstacles[30].id = 30; obstacles[30].x = 12; obstacles[30].y = 31; obstacles[30].length = length;
        obstacles[31].id = 31; obstacles[31].x = 12; obstacles[31].y = 32; obstacles[31].length = length;
        obstacles[32].id = 32; obstacles[32].x = 12; obstacles[32].y = 33; obstacles[32].length = length;
        obstacles[33].id = 33; obstacles[33].x = 12; obstacles[33].y = 34; obstacles[33].length = length;


        // vertical line left down 
        obstacles[34].id = 34; obstacles[34].x = 21; obstacles[34].y = 11; obstacles[34].length = length;
        obstacles[35].id = 35; obstacles[35].x = 21; obstacles[35].y = 12; obstacles[35].length = length;
        obstacles[36].id = 36; obstacles[36].x = 21; obstacles[36].y = 13; obstacles[36].length = length;
        obstacles[37].id = 37; obstacles[37].x = 21; obstacles[37].y = 14; obstacles[37].length = length;
        obstacles[38].id = 38; obstacles[38].x = 21; obstacles[38].y = 15; obstacles[38].length = length;
        obstacles[39].id = 39; obstacles[39].x = 21; obstacles[39].y = 16; obstacles[39].length = length;

        // fake safehouse 
        obstacles[40].id = 40; obstacles[40].x = 24; obstacles[40].y = 27; obstacles[40].length = length;
        obstacles[41].id = 41; obstacles[41].x = 23; obstacles[41].y = 27; obstacles[41].length = length;
        obstacles[42].id = 42; obstacles[42].x = 23; obstacles[42].y = 28; obstacles[42].length = length;
        obstacles[43].id = 43; obstacles[43].x = 23; obstacles[43].y = 29; obstacles[43].length = length;
        obstacles[44].id = 44; obstacles[44].x = 24; obstacles[44].y = 29; obstacles[44].length = length;
        obstacles[45].id = 45; obstacles[45].x = 25; obstacles[45].y = 29; obstacles[45].length = length;
        obstacles[46].id = 46; obstacles[46].x = 26; obstacles[46].y = 29; obstacles[46].length = length;
        obstacles[47].id = 47; obstacles[47].x = 27; obstacles[47].y = 29; obstacles[47].length = length;
        obstacles[48].id = 48; obstacles[48].x = 27; obstacles[48].y = 28; obstacles[48].length = length;
        obstacles[49].id = 49; obstacles[49].x = 27; obstacles[49].y = 27; obstacles[49].length = length;
        obstacles[50].id = 50; obstacles[50].x = 27; obstacles[50].y = 27; obstacles[50].length = length;
        obstacles[51].id = 51; obstacles[51].x = 26; obstacles[51].y = 27; obstacles[51].length = length;

        // vertical line right up
        obstacles[52].id = 52; obstacles[52].x = 34; obstacles[52].y = 44; obstacles[52].length = length;
        obstacles[53].id = 53; obstacles[53].x = 34; obstacles[53].y = 43; obstacles[53].length = length;
        obstacles[54].id = 54; obstacles[54].x = 34; obstacles[54].y = 42; obstacles[54].length = length;
        obstacles[55].id = 55; obstacles[55].x = 34; obstacles[55].y = 41; obstacles[55].length = length;
        obstacles[56].id = 56; obstacles[56].x = 34; obstacles[56].y = 40; obstacles[56].length = length;
        obstacles[57].id = 57; obstacles[57].x = 34; obstacles[57].y = 39; obstacles[57].length = length;
        obstacles[58].id = 58; obstacles[58].x = 34; obstacles[58].y = 38; obstacles[58].length = length;
        obstacles[59].id = 59; obstacles[59].x = 34; obstacles[59].y = 37; obstacles[59].length = length;

        // vertical line right up 2
        obstacles[60].id = 60; obstacles[60].x = 23; obstacles[60].y = 40; obstacles[60].length = length;
        obstacles[61].id = 61; obstacles[61].x = 23; obstacles[61].y = 39; obstacles[61].length = length;
        obstacles[62].id = 62; obstacles[62].x = 23; obstacles[62].y = 38; obstacles[62].length = length;
        obstacles[63].id = 63; obstacles[63].x = 23; obstacles[63].y = 37; obstacles[63].length = length;
        obstacles[64].id = 64; obstacles[64].x = 23; obstacles[64].y = 36; obstacles[64].length = length;
        obstacles[65].id = 65; obstacles[65].x = 23; obstacles[65].y = 35; obstacles[65].length = length;

        // vertical line right up 3
        obstacles[66].id = 66; obstacles[66].x = 14; obstacles[66].y = 44; obstacles[66].length = length;
        obstacles[67].id = 67; obstacles[67].x = 14; obstacles[67].y = 43; obstacles[67].length = length;
        obstacles[68].id = 68; obstacles[68].x = 14; obstacles[68].y = 42; obstacles[68].length = length;
        obstacles[69].id = 69; obstacles[69].x = 14; obstacles[69].y = 41; obstacles[69].length = length;
        obstacles[70].id = 70; obstacles[70].x = 14; obstacles[70].y = 40; obstacles[70].length = length;
        obstacles[71].id = 71; obstacles[71].x = 14; obstacles[71].y = 39; obstacles[71].length = length;
    }

    /*
    enemies are created randomly on a 2 second interval, and the dead ones are respawned after 5 seconds
    this gives wave enemy behaviour for the game
    */

    { // bullets creation
        for (int i = 0; i < AMMO; i++) {
            bullets[i].id = i; bullets[i].follow_x = 0; bullets[i].follow_y = 0; bullets[i].length = length_hand; bullets[i].isShot = false; bullets[i].max_distance = 4.0f;
        }
        bullet_count = 0;
    }

    // camera 
    {
        auto camera = GetSceneCamera();
        camera->SetPosition(glm::vec3(0, 0, 50));
        camera->SetRotation(glm::vec3(0, 0, 0));
        camera->Update();
        GetCameraInput()->SetActive(false);

        logicSpace.x = 0;       // logic x
        logicSpace.y = 0;       // logic y
        logicSpace.width = LEN;   // logic width
        logicSpace.height = LEN;  // logic height

        // minimap
        logicSpace_minimap.x = 0;
        logicSpace_minimap.y = 0;
        logicSpace_minimap.width = length_map + 1;
        logicSpace_minimap.height = length_map + 1;
    }

    // hero creation
    hero.id = 0; hero.x = 0; hero.y = 0; hero.length = length; hero.health = 100;
    last_health = hero.health;

    // rotation step
    angularStep = 0;

    // pickups
    pickup_health_x = 44; pickup_health_y = 2; pickup_health_taken = false;
    pickup_freeze_x = 42; pickup_freeze_y = 2; pickup_freeze_taken = false;

    glm::vec3 corner = glm::vec3(0.001, 0.001, 0);
    
    Mesh* main_hero = object2D::CreateSquare("main_hero", corner, length, glm::vec3(0, 0.9f, 0.9f), true);
    AddMeshToList(main_hero);

    Mesh* hand = object2D::CreateSquare("hand", corner, length_hand, glm::vec3(0, 0.6f, 0.9f), true);
    AddMeshToList(hand);

    Mesh* obstacle = object2D::CreateSquare("obstacle", corner, length, glm::vec3(0.59f, 0.44f, 0.09f), true);
    AddMeshToList(obstacle);

    Mesh* enemy = object2D::CreateSquare("enemy", corner, length, glm::vec3(0.49f, 0.49f, 0.51f), true);
    AddMeshToList(enemy);

    Mesh* bullet = object2D::CreateSquare("bullet", corner, length_hand, glm::vec3(0, 0, 0), true);
    AddMeshToList(bullet);

    Mesh* map = object2D::CreateSquare("map", corner, length_map, glm::vec3(1, 0.4f, 0.4f), false);
    AddMeshToList(map);

    Mesh* healthbar = object2D::CreateRectangle("healthbar", corner, 0.3, glm::vec3(0, 1, 0), true);
    AddMeshToList(healthbar);
    Mesh* healthbar_grid = object2D::CreateRectangle("healthbar_grid", corner, 0.3, glm::vec3(0, 1, 0), false);
    AddMeshToList(healthbar_grid);

    Mesh* eye = object2D::CreateSquare("eye", corner, length_hand, glm::vec3(1, 0, 0), true);
    AddMeshToList(eye);

    Mesh* pickup_health = object2D::CreateSquare("pickup_health", corner, length, glm::vec3(0, 1, 0), true);
    AddMeshToList(pickup_health);

    Mesh* pickup_freeze = object2D::CreateSquare("pickup_freeze", corner, length, glm::vec3(0, 0, 1), true);
    AddMeshToList(pickup_freeze);
}


// 2D visualization matrix
glm::mat3 tema1::VisualizationTransf2D(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
    float sx, sy, tx, ty;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    tx = viewSpace.x - sx * logicSpace.x;
    ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat3(
        sx, 0.0f, tx,
        0.0f, sy, ty,
        0.0f, 0.0f, 1.0f));
}


// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 tema1::VisualizationTransf2DUnif(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}


void tema1::SetViewportArea(const ViewportSpace & viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}


void tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();
    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0.30, 0.00, 0.20), true);

    // Compute uniform 2D visualization matrix
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);

    DrawScene(visMatrix);

    // minimap
    viewSpace = ViewportSpace(resolution.x - resolution.x / 5, resolution.y - resolution.y / 5, resolution.x / 5, resolution.y / 5);
    SetViewportArea(viewSpace, glm::vec3(0), true);

    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace_minimap, viewSpace);

    // hero is dead -> finish game
    if (hero.health <= 0) {
        exit(0);
    }

    DrawScene(visMatrix);
    
    // pickup_health: gives a +50 boost
    if (pickup_health_taken == false) {
        if (check_obstacle_collision(logicSpace.width / 2 - length / 2 + hero.x, logicSpace.width / 2 - length / 2 + hero.y, length, pickup_health_x, pickup_health_y, length)) {
            pickup_health_taken = true;
            hero.health += 50;
            full_health += 0.5f;
            if (full_health > 1) {
                full_health = 1;
            }
            if (hero.health > 100) {
                hero.health = 100;
            }
            last_health = hero.health;
        }
    }

    // pickup_freeze: sets all current enemies to speed 1
    if (pickup_freeze_taken == false) {
        if (check_obstacle_collision(logicSpace.width / 2 - length / 2 + hero.x, logicSpace.width / 2 - length / 2 + hero.y, length, pickup_freeze_x, pickup_freeze_y, length)) {
            pickup_freeze_taken = true;
            for (int i = 0; i < last_id; i++) {
                enemies[i].speed = 1;
            }
        }
    }

    // test position before applying it -> see in the future behaviour
    float test_pos = 0;
    bool atLimit;
    float modul_x, modul_y;

    for (int i = 0; i < NO_ENEMIES; i++) {

        // try respawn after 5 seconds
        if (enemies[i].isDead == true) {
            if (std::chrono::duration_cast<std::chrono::seconds>(end - enemies[i].start).count() > 5) {
                enemies[i].isDead = false;
            }
        }

        else {
            // test movement with random speeds
            modul_x = enemies[i].x + enemies[i].follow_x - (logicSpace.width / 2 - length / 2 + length + hero.x - length);
            if (modul_x > 0) { // false -> se misca
                test_pos = enemies[i].follow_x - enemies[i].speed * deltaTimeSeconds;
                atLimit = check_map_limits(enemies[i].x + test_pos, enemies[i].y + enemies[i].follow_y, enemies[i].length);
                if (!atLimit) {
                    enemies[i].follow_x -= enemies[i].speed * deltaTimeSeconds;
                }
            }
            else if (modul_x <= 0) {
                test_pos = enemies[i].follow_x + 3.0f * deltaTimeSeconds;
                atLimit = check_map_limits(enemies[i].x + test_pos, enemies[i].y + enemies[i].follow_y, enemies[i].length);
                if (!atLimit) {
                    enemies[i].follow_x += enemies[i].speed * deltaTimeSeconds;
                }
            }
            modul_y = enemies[i].y + enemies[i].follow_y - (logicSpace.width / 2 - length / 2 + length + hero.y - length);
            if (modul_y > 0) {
                test_pos = enemies[i].follow_y - enemies[i].speed * deltaTimeSeconds;
                atLimit = check_map_limits(enemies[i].x + enemies[i].follow_x, enemies[i].y + test_pos, enemies[i].length);
                if (!atLimit) {
                    enemies[i].follow_y -= enemies[i].speed * deltaTimeSeconds;
                }
            }
            else if (modul_y <= 0) {
                test_pos = enemies[i].follow_y + enemies[i].speed * deltaTimeSeconds;
                atLimit = check_map_limits(enemies[i].x + enemies[i].follow_x, enemies[i].y + test_pos, enemies[i].length);
                if (!atLimit) {
                    enemies[i].follow_y += enemies[i].speed * deltaTimeSeconds;
                }
            }

            // test bullet collision
            for (int j = 0; j < AMMO; j++) {
                if (bullets[j].isShot == false) {
                    continue;
                }
                enemies[i].isDead = check_dead(enemies[i].x + enemies[i].follow_x, enemies[i].y + enemies[i].follow_y, enemies[i].length, bullets[j].follow_x + hero.x + logicSpace.width / 2 - length_hand / 2,
                    bullets[j].follow_y + hero.y + logicSpace.height / 2 - length_hand / 2, bullets[j].length);
                if (enemies[i].isDead) {
                    enemies[i].start = std::chrono::steady_clock::now();
                    bullets[j].isShot = false;
                    bullets[j].max_distance = 0;
                    enemies[i].follow_x = 0;
                    enemies[i].follow_y = 0;
                    hero.score += 10;
                    cout << "score: " << hero.score << "\n";
                    break;
                }
            }
            if (enemies[i].isDead) {
                continue;
            }

            // test dead enemy
            enemies[i].isDead = check_dead(enemies[i].x + enemies[i].follow_x, enemies[i].y + enemies[i].follow_y, enemies[i].length, logicSpace.width / 2 - length / 2 + hero.x,
                logicSpace.height / 2 - length / 2 + hero.y, hero.length);
            if (enemies[i].isDead) {
                hero.health -= 25;
                enemies[i].start = std::chrono::steady_clock::now();
                enemies[i].follow_x = 0;
                enemies[i].follow_y = 0;
                break;
            }
        }
    }

    for (int i = 0; i < NO_OBSTACLES; i++) {

        // test bullet collision
        for (int j = 0; j < AMMO; j++) {
            if (bullets[j].isShot == false) {
                continue;
            }
            bool hitObstacle = check_obstacle_collision(obstacles[i].x, obstacles[i].y, obstacles[i].length, bullets[j].follow_x + hero.x + logicSpace.width / 2 - length_hand / 2,
                bullets[j].follow_y + hero.y + logicSpace.height / 2 - length_hand / 2, bullets[j].length);
            
            bool hitMap = check_map_limits(bullets[j].follow_x + hero.x + logicSpace.width / 2 - length_hand / 2, bullets[j].follow_y + hero.y + logicSpace.height / 2 - length_hand / 2, bullets[j].length);
            if (hitObstacle || hitMap) {
                bullets[j].isShot = false;
                bullets[j].max_distance = 0;
                
            }
        }
    }

    // 5 seconds respawn time for enemies, timer also used for cooldown
    end = std::chrono::steady_clock::now();

    // bullets cooldown
    if (std::chrono::duration_cast<std::chrono::seconds>(end - start).count() > 5) {
        start = std::chrono::steady_clock::now();
        cooldown = false;
        bullet_count = 0;
    }

    // spawn enemy after 2 seconds on random positions
    if (std::chrono::duration_cast<std::chrono::seconds>(end - respawn_time).count() > 2) {

        if (last_id == 30) {
            last_id = 0;
        }

        enemies[last_id].id = last_id;
        enemies[last_id].follow_x = 0;
        enemies[last_id].follow_y = 0;
        enemies[last_id].isDead = false;
        enemies[last_id].length = length;

        srand((unsigned)time(0));
        int randomNumber1 = (rand() % ((int)length_map - 1)) + 1;
        int randomNumber2 = (rand() % ((int)length_map - 1)) + 1;

        enemies[last_id].x = randomNumber1;
        enemies[last_id].y = randomNumber2;

        int randomSpeed = (rand() % ((int)10 - 1)) + 1;
        enemies[last_id].speed = randomSpeed * 1.0f;

        respawn_time = std::chrono::steady_clock::now();
        last_id++;
    }
} 


void tema1::FrameEnd()
{
}


void tema1::DrawScene(glm::mat3 visMatrix)
{  

    // map
    modelMatrix = visMatrix * transform2D::Translate(0, 0);
    RenderMesh2D(meshes["map"], shaders["VertexColor"], modelMatrix);

    // enemy
    for (int i = 0; i < last_id; i++) {

        enemies[i].modelMatrix_eyel = visMatrix * transform2D::Translate(enemies[i].x, enemies[i].y + length_hand * 2 - 0.15f);
        enemies[i].modelMatrix_eyer = visMatrix * transform2D::Translate(enemies[i].x + length - length_hand, enemies[i].y + length_hand * 2 - 0.15f);
        enemies[i].modelMatrix = visMatrix * transform2D::Translate(enemies[i].x, enemies[i].y);

        enemies[i].modelMatrix_eyel *= transform2D::Translate(enemies[i].follow_x, enemies[i].follow_y);
        enemies[i].modelMatrix_eyer *= transform2D::Translate(enemies[i].follow_x, enemies[i].follow_y);
        enemies[i].modelMatrix *= transform2D::Translate(enemies[i].follow_x, enemies[i].follow_y);

        if (enemies[i].isDead == false) {

            RenderMesh2D(meshes["eye"], shaders["VertexColor"], enemies[i].modelMatrix_eyel);
            RenderMesh2D(meshes["eye"], shaders["VertexColor"], enemies[i].modelMatrix_eyer);
            RenderMesh2D(meshes["enemy"], shaders["VertexColor"], enemies[i].modelMatrix);
        }
    }

    // obstacole
    for (int i = 0; i < NO_OBSTACLES; i++) {
        modelMatrix = visMatrix * transform2D::Translate(obstacles[i].x, obstacles[i].y);
        RenderMesh2D(meshes["obstacle"], shaders["VertexColor"], modelMatrix);
    }

    // bullet physics
    for (int i = 0; i < AMMO; i++) {

        // if bullet is not shot, dont draw it
        bullets[i].modelMatrix = visMatrix * transform2D::Translate(logicSpace.width / 2 - length_hand / 2, logicSpace.height / 2 - length_hand / 2);
        bullets[i].modelMatrix *= transform2D::Translate(hero.x, hero.y);
        
        // if bullet shot, draw it
        if (bullets[i].isShot && bullets[i].max_distance > 0) {
            bullets[i].follow_x += cos(bullets[i].angularStepCopy) * 0.5;
            bullets[i].follow_y += -sin(bullets[i].angularStepCopy) * 0.5;
            bullets[i].modelMatrix *= transform2D::Translate(bullets[i].follow_x, bullets[i].follow_y);
            bullets[i].modelMatrix *= transform2D::Translate(length_hand / 2, length_hand / 2) * transform2D::Rotate(-bullets[i].angularStepCopy) * transform2D::Translate(-length_hand / 2, -length_hand / 2);

            RenderMesh2D(meshes["bullet"], shaders["VertexColor"], bullets[i].modelMatrix);
             
            bullets[i].max_distance -= 0.15f;
        }

        // reset bullets after distance expires
        if (bullets[i].max_distance <= 0) {
            bullets[i].isShot = false;
            bullets[i].follow_x = 0;
            bullets[i].follow_y = 0;
            bullets[i].max_distance = 4.5f;
        }
    }

    // grid
    modelMatrix = visMatrix * transform2D::Translate(logicSpace.width / 2 + 0.7, logicSpace.height / 2 + 0.7);
    modelMatrix *= transform2D::Translate(hero.x, hero.y);
    RenderMesh2D(meshes["healthbar_grid"], shaders["VertexColor"], modelMatrix);

    // healthbar
    modelMatrix = visMatrix * transform2D::Translate(logicSpace.width / 2 + 0.7, logicSpace.height / 2 + 0.7);
    modelMatrix *= transform2D::Translate(hero.x, hero.y);
    modelMatrix *= transform2D::Scale(full_health, 1);

    // update healthbar
    if (last_health > hero.health) {
        last_health = hero.health;

        full_health -= 0.25f;
    }
    RenderMesh2D(meshes["healthbar"], shaders["VertexColor"], modelMatrix);

    // left hand hero
    modelMatrix = visMatrix * transform2D::Translate(logicSpace.width / 2 - length / 2 + length, logicSpace.height / 2 - length / 2 + 2 * length_hand * length);
    modelMatrix *= transform2D::Translate(hero.x, hero.y);
    modelMatrix *= transform2D::Translate(-1 * length / 2, -1 * length_hand / 2) * transform2D::Rotate(-1 * angularStep) * transform2D::Translate(length/2, length_hand/2);
    RenderMesh2D(meshes["hand"], shaders["VertexColor"], modelMatrix);

    // right hand hero
    modelMatrix = visMatrix * transform2D::Translate(logicSpace.width / 2 - length / 2 + length, logicSpace.height / 2 - length / 2);
    modelMatrix *= transform2D::Translate(hero.x, hero.y);
    modelMatrix *= transform2D::Translate(-1 * length / 2, length / 2) * transform2D::Rotate(-1 * angularStep) * transform2D::Translate(length / 2, -1 * length / 2);
    RenderMesh2D(meshes["hand"], shaders["VertexColor"], modelMatrix);

    // hero
    modelMatrix = visMatrix * transform2D::Translate(logicSpace.width / 2 - length / 2, logicSpace.height / 2 - length / 2);
    modelMatrix *= transform2D::Translate(hero.x, hero.y);
    modelMatrix *= transform2D::Translate(length/2, length/2) * transform2D::Rotate(-1 * angularStep) * transform2D::Translate(-1 * length/2, -1 * length/2);
    RenderMesh2D(meshes["main_hero"], shaders["VertexColor"], modelMatrix);

    // pickup_health
    modelMatrix = visMatrix * transform2D::Translate(pickup_health_x, pickup_health_y);
    if (pickup_health_taken == false) {
        RenderMesh2D(meshes["pickup_health"], shaders["VertexColor"], modelMatrix);
    }

    // pickup_freeze
    modelMatrix = visMatrix * transform2D::Translate(pickup_freeze_x, pickup_freeze_y);
    if (pickup_freeze_taken == false) {
        RenderMesh2D(meshes["pickup_freeze"], shaders["VertexColor"], modelMatrix);
    }
}


void tema1::OnInputUpdate(float deltaTime, int mods)
{

    // test position before applying it -> see in the future behaviour
    float test_pos = 0;
    bool collision_obstacle = false;
    bool collision_map = false;

    if (window->KeyHold(GLFW_KEY_A)) {
        
        test_pos = hero.x - 6 * deltaTime;
        
        for (int i = 0; i < NO_OBSTACLES; i++) {
            if (check_obstacle_collision(logicSpace.width / 2 - length / 2 + test_pos, logicSpace.width / 2 - length / 2 + hero.y, length, obstacles[i].x, obstacles[i].y, obstacles[i].length )) {
                collision_obstacle = true;
            }
        }
        collision_map = check_map_limits(logicSpace.width / 2 - length / 2 + test_pos, logicSpace.width / 2 - length / 2 + hero.y, length);
        if (collision_obstacle == false && collision_map == false) {
            hero.x -= 6 * deltaTime;
            logicSpace.x -= 6 * deltaTime;
        }
    }
    if (window->KeyHold(GLFW_KEY_D)) {

        test_pos = hero.x + 6 * deltaTime;
        
        for (int i = 0; i < NO_OBSTACLES; i++) {
            if (check_obstacle_collision(logicSpace.width / 2 - length / 2 + test_pos, logicSpace.width / 2 - length / 2 + hero.y, length, obstacles[i].x, obstacles[i].y, obstacles[i].length)) {
                collision_obstacle = true;
            }
        }
        collision_map = check_map_limits(logicSpace.width / 2 - length / 2 + test_pos, logicSpace.width / 2 - length / 2 + hero.y, length);
        if (collision_obstacle == false && collision_map == false) {
            hero.x += 6 * deltaTime;
            logicSpace.x += 6 * deltaTime;
        }

    }
    if (window->KeyHold(GLFW_KEY_W)) {

        test_pos = hero.y + 6 * deltaTime;

        for (int i = 0; i < NO_OBSTACLES; i++) {
            if (check_obstacle_collision(logicSpace.width / 2 - length / 2 + hero.x, logicSpace.width / 2 - length / 2 + test_pos, length, obstacles[i].x, obstacles[i].y, obstacles[i].length)) {
                
                collision_obstacle = true;
            }
        }
        collision_map = check_map_limits(logicSpace.width / 2 - length / 2 + hero.x, logicSpace.width / 2 - length / 2 + test_pos, length);
        if (collision_obstacle == false && collision_map == false) {
            hero.y += 6 * deltaTime;
            logicSpace.y += 6 * deltaTime;
        }
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        
        test_pos = hero.y - 6 * deltaTime;
        
        for (int i = 0; i < NO_OBSTACLES; i++) {
            
            if (check_obstacle_collision(logicSpace.width / 2 - length / 2 + hero.x, logicSpace.width / 2 - length / 2 + test_pos, length, obstacles[i].x, obstacles[i].y, obstacles[i].length)) {

                collision_obstacle = true;
            }
        }
        collision_map = check_map_limits(logicSpace.width / 2 - length / 2 + hero.x, logicSpace.width / 2 - length / 2 + test_pos, length);
        if (collision_obstacle == false && collision_map == false) {
            hero.y -= 6 * deltaTime;
            logicSpace.y -= 6 * deltaTime;
        }
    }
}


void tema1::OnKeyPress(int key, int mods)
{

}


void tema1::OnKeyRelease(int key, int mods)
{
}


void tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // rotate player and also rotate bullet
    glm::ivec2 resolution = window->GetResolution();
    angularStep = atan2((mouseY - resolution.y / 2), (mouseX - resolution.x / 2));
}


void tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // fire bullets
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (cooldown == false) {
            bullets[bullet_count].angularStepCopy = angularStep;
            bullets[bullet_count].isShot = true;
            ++bullet_count;

            // out of ammo -> cooldown 5 seconds
            if (bullet_count == AMMO) {
                cooldown = true;
            }
        }
    }
}


void tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}
