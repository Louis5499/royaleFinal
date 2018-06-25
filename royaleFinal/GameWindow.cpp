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
    int i;
    char buffer[50];
    
    icon = al_load_bitmap("./icon.png");
    loading = al_load_bitmap("./loading_1.png");
    start_scene = al_load_bitmap("./start_scene.jpeg");
    background = al_load_bitmap("./StartBackground.jpg");
    playing_background = al_load_bitmap("./gamePlayBackground.png");

    floor = al_load_bitmap("./floor.jpg");
    money_bar = al_load_bitmap("./money_bar.png");
    jewel_bar = al_load_bitmap("./jewel_bar.png");
    cup_bar = al_load_bitmap("./cup_bar.png");
    treasure = al_load_bitmap("./treasure.png");
    treasure1 = al_load_bitmap("./treasure1.png");
    cardBoard = al_load_bitmap("./cardBoard.jpeg");
    
    towerBigBlue = new TowerBigBlue(390, 348);
    towerBigRed = new TowerBigRed(1145, 348);
    
    towerSmallBlueTop = new TowerSmallBlue(510, 170);
    towerSmallBlueBottom = new TowerSmallBlue(510,573);
    
    towerSmallRedTop = new TowerSmallRed(1059, 170);
    towerSmallRedBottom = new TowerSmallRed(1059, 573);

    towerSet.push_back(towerBigBlue);
    towerSet.push_back(towerBigRed);
    towerSet.push_back(towerSmallRedTop);
    towerSet.push_back(towerSmallRedBottom);
    towerSet.push_back(towerSmallBlueTop);
    towerSet.push_back(towerSmallBlueBottom);
    
    al_set_display_icon(display, icon);
    al_reserve_samples(3);
    
    one = new Classmates("zhengyen",100,100,1);
    start = new button("start_button", window_width/2, window_height*5/6, 125, 125, roundType);
    playing = new button("playing_button", window_width - 190, window_height - 120, 300, 160, square);
    setting = new button("setting_button", window_width - 80, 80, 80, 80, square);
    exit_button = new button("exit_button", window_width - 105, 82, 18, 18, roundType);
    for(i=0; i<6; i++) chr[i] = new button(cmName[i], 150, 160 + 200*i, 175, 200, square);
    
    volumer = new Slider(290, 290);
    
    sample = al_load_sample("menu.ogg");
    backgroundSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());
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
    
    while(msg == GAME_FIGHT || msg == GAME_SETTING || msg == GAME_PLAYING) {
        if (!al_is_event_queue_empty(event_queue)) {
            if(msg == GAME_FIGHT) msg = fight_process_event();
            else if(msg == GAME_PLAYING) msg = playing_process_event();
            else msg = setting_process_event();
        }
    }
    
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
    
    font = al_load_ttf_font("Monsterz.ttf",28, 0); // load small font
    Medium_font = al_load_ttf_font("Monsterz.ttf",70, 0); //load medium font
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
    al_play_sample_instance(backgroundSound);
    
    al_start_timer(timer);
    al_start_timer(monster_pro);
}

int
GameWindow::game_update()
{
    unsigned int i, j;
    
    std::list<Tower*>::iterator it;
    
    /*TODO:*/
    /*Allow towers to detect if monster enters its range*/
    /*Hint: Tower::DetectAttack*/
    for(auto tower : towerSet) {
        for(auto mate : cmSet) {
            tower->DetectAttack(mate); // 會回傳 bool ，不確定用途
            mate->DetectAttackTower(tower);
        }
    }
    
    for(auto mateOuter: cmSet) {
        for(auto mateInner: cmSet) {
            if(mateOuter == mateInner) continue;
            mateOuter->DetectAttack(mateInner);
        }
    }
    
    // update every monster
    // check if it is destroyed or reaches end point
    for(i=0; i < cmSet.size(); i++)
    {
        for(auto tower : towerSet) {
            tower->TriggerAttack(cmSet[i]);
            cmSet[i]->TriggerAttackTower(tower);
        }
    }
    
    for(auto mateOuter: cmSet) {
        for(auto mateInner: cmSet) {
            if(mateOuter == mateInner) continue;
            mateOuter->TriggerAttack(mateInner);
        }
    }
    
    /*TODO:*/
    /*1. Update the attack set of each tower*/
    /*Hint: Tower::UpdateAttack*/
    
    for(i=0; i < towerSet.size(); i++) {
        Tower *tower = towerSet[i];
        if(tower->getHealthPoint() <= 0) {
            towerSet.erase(towerSet.begin() + i);
            i--;
            delete tower;
        }
        else tower->UpdateAttack();
    }
    
    for(i=0; i < cmSet.size(); i++) {
        Classmates *m = cmSet[i];
        if(m->attack_set.empty()) printf("Empty\n");
        if(mate->getHealthPoint() <= 0) {
            cmSet.erase(cmSet.begin() + i);
            i--;
            delete m;
        }
        else {
            m->move();
            m->UpdateAttack();
        }
    }
    
    
    return GAME_PLAYING;
}

void
GameWindow::game_reset()
{
    mute = false;
    redraw = false;
    
    al_stop_sample_instance(backgroundSound);
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
    al_wait_for_event(event_queue, &event);
    redraw = false;
    
    if(event.type == ALLEGRO_EVENT_TIMER) {
        if(event.timer.source == timer) {
            redraw = true;
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_P:
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
            if(playing->isHovered(mouse_x, mouse_y))
                return GAME_PLAYING;
            if(setting->isHovered(mouse_x, mouse_y))
                return GAME_SETTING;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
    }
    
    if(playing->isHovered(mouse_x, mouse_y)) playing->hover();
    else playing->notHover();
    if(setting->isHovered(mouse_x, mouse_y)) setting->hover();
    else setting->notHover();
    
    if(redraw) {
        draw_fight_scene(GAME_FIGHT);
        redraw = false;
    }
    
    return GAME_FIGHT;
}

int
GameWindow::setting_process_event()
{
    int i;
    int instruction = GAME_FIGHT;
    
    al_wait_for_event(event_queue, &event);
    redraw = false;
    
    if(event.type == ALLEGRO_EVENT_TIMER) {
        if(event.timer.source == timer) {
            redraw = true;
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_P:
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
            if(volumer->isClicked(event.mouse.x, event.mouse.y)) {
                volume = volumer->Drag(event.mouse.x, event.mouse.y);
                al_set_sample_instance_gain(backgroundSound, volume);
                volumer->toggleDrag();
        }
            if(setting->isHovered(mouse_x, mouse_y))
                return GAME_FIGHT;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
    }
    
    if(volumer->isDragged()) {
        volume = volumer->Drag(mouse_x, mouse_y);
        al_set_sample_instance_gain(backgroundSound, volume);
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) volumer->toggleDrag();
    }
    
    if(redraw) {
        draw_fight_scene(GAME_SETTING);
        redraw = false;
    }
    
    return GAME_SETTING;
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
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_ENTER:
                mate = new Classmates("zhengyen",440,300,1);
                cmSet.push_back(mate);
                break;
            case ALLEGRO_KEY_E:
                mate = new Classmates("zhengyen",1000,300,0);
                cmSet.push_back(mate);
                break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if(event.mouse.button == 1) {
            for(i=0; i<4; i++) {
                if(chr[i]->isHovered(mouse_x, mouse_y)) {
                    mate = new Classmates(cmName[i],440,300,1);
                    cmSet.push_back(mate);
                }
            }
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
        t++;
    } else {
        start->draw();
    }
    
    
    al_flip_display();
}

void
GameWindow::draw_fight_scene(int msg)
{
    char buffer[50], j_buffer[50], c_buffer[50];
    int i, j, count;
    
    for(i=money, count = 0; i>0; i/=10, count++);
    for(i=count-1, j=money; i>=0; i--, j/=10) buffer[i] = j%10+'0';
    buffer[count] = '\0';
    if(count==0) { buffer[0] = '0'; buffer[1] = '\0';}
    
    for(i=jewel, count = 0; i>0; i/=10, count++);
    for(i=count-1, j=jewel; i>=0; i--, j/=10) j_buffer[i] = j%10+'0';
    j_buffer[count] = '\0';
    if(count==0) { j_buffer[0] = '0'; j_buffer[1] = '\0';}
    
    for(i=cup, count = 0; i>0; i/=10, count++);
    for(i=count-1, j=cup; i>=0; i--, j/=10) c_buffer[i] = j%10+'0';
    c_buffer[count] = '\0';
    if(count==0) { c_buffer[0] = '0'; c_buffer[1] = '\0';}
    
    al_draw_bitmap(floor, 0, 0, 0);
    al_draw_bitmap(money_bar, 50, 70, 0);
    al_draw_text(font, WHITE, 180, 90, 1, buffer);
    al_draw_bitmap(jewel_bar, 50, 150, 0);
    al_draw_text(font, WHITE, 180, 170, 1, j_buffer);
    al_draw_bitmap(cup_bar, 50, 230, 0);
    al_draw_text(font, ORANGE_LIGHT, 180, 250, 1, c_buffer);
    
    playing->draw();
    setting->draw();
    
    for(i=0; i<3; i++) {
        if(treasureLock[i] == false) al_draw_bitmap(treasure, 50+i*250, window_height-220, 0);
        else al_draw_bitmap(treasure1, 50+i*180, 230, 0);
    }
    
    if(msg == GAME_SETTING) {
        al_draw_filled_rounded_rectangle(100, 80, window_width - 100, window_height - 80, 20, 20, al_map_rgb(150, 150, 150));
        al_draw_text(Medium_font, al_map_rgb(230, 230, 230), window_width/2, 110, 1, "SETTING");
        al_draw_filled_rounded_rectangle(110, 200, window_width - 110, window_height - 90, 40, 40, al_map_rgb(230, 230, 230));
        exit_button->draw();
        al_draw_text(font, al_map_rgb(41, 31, 40), 140, 270, 0, "VOLUME");
        volumer->draw();
    }
    
//    al_clear_to_color(al_map_rgb(100, 100, 100));
//    al_draw_bitmap(background, 0, 0, 0);
//
//    one->draw();
    
    al_flip_display();
}


void GameWindow::draw_playing_scene() {
    int i;
    al_draw_bitmap(playing_background, 0, 0, 0);
    
    for(auto tower:towerSet) tower->draw();
    
    //al_draw_rectangle(100, 220, 900, 270, al_map_rgb(255, 255, 255), 1);
    al_draw_bitmap(cardBoard, 0, 0, 0);
    for(i=0; i<4; i++) chr[i]->draw();
    
    for(auto i:cmSet) {
        i->draw();
    }
//    printf("Tower: %d\n",towerSmallRedTop->getHealthPoint());
    al_flip_display();
}

