#include "GameWindow.h"
#include <iostream>

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)

#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))

void
GameWindow::game_init()
{
    char buffer[50];
    
    icon = al_load_bitmap("./icon.png");
    loading = al_load_bitmap("./loading_1.png");
    start_button = al_load_bitmap("./start_button.png");
    start_scene = al_load_bitmap("./start_scene.jpeg");
    background = al_load_bitmap("./StartBackground.jpg");
    playing_background = al_load_bitmap("./gamePlayBackground.png");
    
    towerBigBlue = new TowerBigBlue(390, 348);
    towerBigRed = new TowerBigRed(1145, 348);
    
    towerSmallBlueTop = new TowerSmallBlue(510, 170);
    towerSmallBlueBottom = new TowerSmallBlue(510,573);
    
    towerSmallRedTop = new TowerSmallRed(1059, 170);
    towerSmallRedBottom = new TowerSmallRed(1059, 573);
    //    al_draw_bitmap(tower_big_blue, 390, 348, 0);
    //    al_draw_bitmap(tower_small_blue, 510, 170, 0);
    //    al_draw_bitmap(tower_small_blue, 510, 573, 0);
    //
    //    al_draw_bitmap(tower_big_red, 1145, 348, 0);
    //    al_draw_bitmap(tower_small_red, 1059, 170, 0);
    //    al_draw_bitmap(tower_small_red, 1059, 573, 0);
    
    one = new Classmates("zhengyen");
    start = new button("start_button", window_width/2, window_height*5/6, 125, 125, roundType);
    
    al_set_display_icon(display, icon);
    al_reserve_samples(3);
    
//    sample = al_load_sample("growl.wav");
//    startSound = al_create_sample_instance(sample);
//    al_set_sample_instance_playmode(startSound, ALLEGRO_PLAYMODE_ONCE);
//    al_attach_sample_instance_to_mixer(startSound, al_get_default_mixer());
    
}

bool
GameWindow::mouse_hover(int startx, int starty, int width, int height)
{
    if(mouse_x >= startx && mouse_x <= startx + width)
        if(mouse_y >= starty && mouse_y <= starty + height)
            return true;
    
    return false;
}

void
GameWindow::game_play()
{
    int msg;
    srand(time(NULL));
    game_begin();
    
    msg = GAME_START;
    
    while(msg == GAME_START)
        if (!al_is_event_queue_empty(event_queue))
            msg = start_process_event();
    
    while(msg == GAME_FIGHT)
        if (!al_is_event_queue_empty(event_queue))
            msg = fight_process_event();
    
    while(msg == GAME_PLAYING)
        if (!al_is_event_queue_empty(event_queue))
            msg = playing_process_event();
    
    show_err_msg(msg);
}

void
GameWindow::show_err_msg(int msg)
{
    fprintf(stderr, "unexpected msg: %d", msg);
    
    game_destroy();
    exit(9);
}

GameWindow::GameWindow()
{
    if (!al_init())
        show_err_msg(-1);
    
    printf("Game Initializing...\n");
    
    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();
    
    /*
     * Create two timers to control different parts of tower game:
     *    a. timer: control the animation of each object, stopped when game doesn't run.
     *    b. monster_pro: control the production of monster, stooped when there is no need to produce monster.
     */
    timer = al_create_timer(1.0 / FPS);
    monster_pro = al_create_timer(1.0 * 80 / FPS);
    
    if(timer == NULL || monster_pro == NULL)
        show_err_msg(-1);
    
    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);
    
    al_init_primitives_addon();
    al_init_font_addon();  // initialize the font addon
    al_init_ttf_addon();   // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon();// initialize acodec addon
    
    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event
    
    font = al_load_ttf_font("The Brooklyn Smooth Bold Demo.ttf",25,15); // load small font
    Medium_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",24,0); //load medium font
    Large_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",36,0); //load large font
    
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(monster_pro));
    
    // Initializing resources that tower game needs.
    game_init();
}

void
GameWindow::game_begin()
{
    
//    al_play_sample_instance(startSound);
//    while(al_get_sample_instance_playing(startSound));
//    al_play_sample_instance(backgroundSound);
    
    al_start_timer(timer);
    al_start_timer(monster_pro);
}

int
GameWindow::game_update()
{
    unsigned int i, j;
    // Todo..
    one->move();
    return GAME_FIGHT;
}

void
GameWindow::game_reset()
{
    mute = false;
    redraw = false;
    
    //al_stop_sample_instance(backgroundSound);
    //al_stop_sample_instance(startSound);
    
    al_stop_timer(timer);
    al_stop_timer(monster_pro);
}

void
GameWindow::game_destroy()
{
    game_reset();
    
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);
    
    al_destroy_timer(timer);
    al_destroy_timer(monster_pro);
    
    al_destroy_bitmap(icon);
    al_destroy_bitmap(background);
    
    al_destroy_sample(sample);
    al_destroy_sample_instance(startSound);
    al_destroy_sample_instance(backgroundSound);
}

int
GameWindow::start_process_event()
{
    al_wait_for_event(event_queue, &event);
    redraw = false;
    
    if(event.type == ALLEGRO_EVENT_TIMER) {
        if(event.timer.source == timer) {
            redraw = true;
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        return GAME_EXIT;
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if(event.mouse.button == 1) {
            if(start->isHovered(mouse_x, mouse_y))
                return GAME_FIGHT;
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_ENTER:
                return GAME_FIGHT;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
        std::cout << event.mouse.x << " " << event.mouse.y << " * " << mouse_x << " " << mouse_y <<std::endl;
    }

    
    if(start->isHovered(mouse_x, mouse_y)) start->hover();
    else start->notHover();
    
    if(redraw) {
        draw_start_scene();
        redraw = false;
    }
    
    return GAME_START;
}

int
GameWindow::fight_process_event()
{
    int i;
    int instruction = GAME_FIGHT;
    
    al_wait_for_event(event_queue, &event);
    redraw = false;
    
    if(event.type == ALLEGRO_EVENT_TIMER) {
        if(event.timer.source == timer) {
            redraw = true;
            // TODO ..
        }
        else {
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_P:
                // FAKE FOR TESTING
                return GAME_PLAYING;
                break;
            case ALLEGRO_KEY_M:
                mute = !mute;
                if(mute)
                    al_stop_sample_instance(backgroundSound);
                else
                    al_play_sample_instance(backgroundSound);
                break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if(event.mouse.button == 1) {
            // TODO ..
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
    }
    
    if(redraw) {
        // update each object in game
        instruction = game_update();
        
        // Re-draw map
        draw_fight_scene();
        redraw = false;
    }
    
    return instruction;
}

int GameWindow::playing_process_event() {
    int i;
    int instruction = GAME_PLAYING;
    
    al_wait_for_event(event_queue, &event);
    redraw = false;
    
    if(event.type == ALLEGRO_EVENT_TIMER) {
        if(event.timer.source == timer) {
            redraw = true;
            // TODO ..
        }
        else {
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    
    if(redraw) {
        // update each object in game
        instruction = game_update();
        
        // Re-draw map
        draw_playing_scene();
        redraw = false;
    }
    
    return GAME_PLAYING;
}


void
GameWindow::draw_start_scene()
{
    char buffer[50];
    
    al_draw_bitmap(start_scene, 0, 0, 0);
    if(t < window_width/3) {
        al_draw_bitmap(loading, window_width/3-50-3, window_height-220, 0);
        al_draw_filled_rounded_rectangle(window_width/3+t, window_height-133, window_width/3*2, window_height-112, 5, 5, WHITE);
        t+=5;
    } else {
        start->draw();
    }
    
    
    al_flip_display();
}

void
GameWindow::draw_fight_scene()
{
    unsigned int i, j;
    printf("draw\n");
    al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_bitmap(background, 0, 0, 0);
    
    one->draw();
    
    al_flip_display();
}

void GameWindow::draw_playing_scene() {
    al_draw_bitmap(playing_background, 0, 0, 0);
    towerBigBlue->draw();
    towerBigRed->draw();
    
    towerSmallBlueTop->draw();
    towerSmallBlueBottom->draw();
    
    towerSmallRedTop->draw();
    towerSmallRedBottom->draw();

    al_flip_display();
}

