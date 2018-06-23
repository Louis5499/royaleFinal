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
    background = al_load_bitmap("./StartBackground.jpg");
    one = new Classmates("zhengyen");
    
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
    
    msg = -1;
    /*
     *  We start the game by calling game_begin to start timer and play music
     * [TODO]:
     *     You may add some function to create starting scene before calling game_begin
     *     e.g: game_start_scene()
     */
    game_begin();
    
    /*
     *  while game is running, the result of game_run will be returned to msg.
     *  If msg is GAME_EXIT, then tower game will terminate.
     */
    while(msg != GAME_EXIT)
        msg = game_run();
    
    show_err_msg(msg);
}

void
GameWindow::show_err_msg(int msg)
{
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
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
    timer = al_create_timer(3.0 / FPS);
    monster_pro = al_create_timer(1.0 * 80 / FPS);
    
    if(timer == NULL || monster_pro == NULL)
        show_err_msg(-1);
    
    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);
    
    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon
    
    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event
    
    font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",12,0); // load small font
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
    draw_running_map();
    
//    al_play_sample_instance(startSound);
//    while(al_get_sample_instance_playing(startSound));
//    al_play_sample_instance(backgroundSound);
    
    al_start_timer(timer);
    al_start_timer(monster_pro);
}

int
GameWindow::game_run()
{
    int error = GAME_CONTINUE;
    
    if (!al_is_event_queue_empty(event_queue)) {
        
        error = process_event();
    }
    return error;
}

int
GameWindow::game_update()
{
    unsigned int i, j;
    // Todo..
    one->move();
    return GAME_CONTINUE;
}

void
GameWindow::game_reset()
{
    mute = false;
    redraw = false;
    
    // stop sample instance
    al_stop_sample_instance(backgroundSound);
    al_stop_sample_instance(startSound);
    
    // stop timer
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
GameWindow::process_event()
{
    int i;
    int instruction = GAME_CONTINUE;
    
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
                /*
                 * You can add some variable to control if game is paused.
                 * e.g: pause
                 * In addition to add variable, you also have to modify draw_running_map() and game_update()
                 * Or, monsters and towers can still work without being paused
                 */
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
        draw_running_map();
        redraw = false;
    }
    
    return instruction;
}

void
GameWindow::draw_running_map()
{
    unsigned int i, j;
    
    al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_bitmap(background, 0, 0, 0);
    one->draw();
    al_flip_display();
}