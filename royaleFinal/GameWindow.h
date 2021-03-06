#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <list>
#include <time.h>
#include "global.h"
#include "Classmates.h"
#include "button.h"
#include "Tower.h"
#include "TowerBigRed.h"
#include "TowerBigBlue.h"
#include "TowerSmallRed.h"
#include "TowerSmallBlue.h"
#include "Slider.h"

#define GAME_INIT -1
#define GAME_START 0
#define GAME_FIGHT 1
#define GAME_SHOP 2
#define GAME_CARD 3
#define GAME_SOCIAL 4
#define GAME_ACTIVITY 5
#define GAME_SETTING 6
#define GAME_DATA 7
#define GAME_PLAYING 8
#define GAME_FAIL 9
#define GAME_EXIT 10

// clock rate
const float FPS = 60;

// total number of level
const int LevelNum = 4;

// 1 coin every 2 seconds
const int CoinSpeed = FPS * 2;
const int Coin_Time_Gain = 1;

class GameWindow
{
public:
    // constructor
    GameWindow();
    // each process of scene
    void game_init();
    void game_reset();
    void game_play();
    void game_begin();

    int game_run();
    int game_update();

    void show_err_msg(int msg);
    void game_destroy();

    // draw running game map
    void draw_start_scene();
    void draw_playing_scene();
    void draw_fight_scene(int);
    
    // draw pause scene
    void draw_pause_scene();
    
    // process of updated event
    int start_process_event();
    int fight_process_event();
    int setting_process_event();
    int playing_process_event();
    
    // detect if mouse hovers over a rectangle
    bool mouse_hover(int, int, int, int);
    // detect if a tower will be constructed on road
    bool isOnRoad();


public:
    bool initial = true;

private:
    ALLEGRO_BITMAP *icon;
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_BITMAP *loading = NULL;
    ALLEGRO_BITMAP *start_scene = NULL;
    ALLEGRO_BITMAP *playing_background = NULL;
    ALLEGRO_BITMAP *tower_small_blue = NULL;
    ALLEGRO_BITMAP *tower_small_red = NULL;
    ALLEGRO_BITMAP *tower_big_blue = NULL;
    ALLEGRO_BITMAP *tower_big_red = NULL;
    ALLEGRO_BITMAP *floor = NULL;
    ALLEGRO_BITMAP *money_bar = NULL;
    ALLEGRO_BITMAP *jewel_bar = NULL;
    ALLEGRO_BITMAP *cup_bar = NULL;
    ALLEGRO_BITMAP *treasure = NULL, *treasure1 = NULL;
    ALLEGRO_BITMAP *cardBoard = NULL;

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *Medium_font = NULL;
    ALLEGRO_FONT *Large_font = NULL;
    ALLEGRO_FONT *Hint_font = NULL;
    ALLEGRO_FONT *Super_large_font = NULL;

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    
    ALLEGRO_TIMER *start_timer = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *monster_pro = NULL;

    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *startSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *clearSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *failSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *backgroundSound = NULL;
    
    std::vector<Classmates*> cmSet;
    std::vector<Tower*> towerSet;
    
    Classmates *one;
    Classmates *mate;
    
    Tower *towerSmallBlueTop;
    Tower *towerSmallBlueBottom;
    Tower *towerSmallRedTop;
    Tower *towerSmallRedBottom;
    
    Tower *towerBigBlue;
    Tower *towerBigRed;
    
    int nowLevel = 1;
    
    int mouse_x, mouse_y;

    bool redraw = false;
    bool mute = false;
    bool pause = false;
    
    int mon = 500;
    int money = 100;
    int jewel = 20;
    int cup = 0;
    bool treasureLock[3] = {false, false, false};
    
    float volume = 1.0;
    
    int t = 0; //to control the loading bar;
    button *start = NULL;
    button *playing = NULL;
    button *setting = NULL;
    button *exit_button = NULL;
    button *chr[6];
    //int start_x = window_width/2, start_y = window_height*2/3, start_w = 100, start_h = 50;
    
    Slider *volumer = NULL;
};


#endif // MAINWINDOW_H_INCLUDED
