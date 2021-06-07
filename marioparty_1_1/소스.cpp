#define _CRT_SECURE_NO_WARNINGS

#define Swap(x, y) temp = x, x = y, y = temp

#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <windows.h>

/* 주의 사항 -- 일종의 바라는 것 or 매뉴얼이라고 생각해주면 좋겠슴니당..
* 혹시 더 추가할 사항 있으시다면 카톡 방에 말하고 추가해줍시당- 한번 보고 안볼거같아서 ㅎㅎ..
1. 마우스 콜백 그대로 가져다 쓰면  mousecallback_~~game처럼
	 달아줬으면 좋겠어용
2. 솔직히 제가 바라는 것이기는 한데 게임을 만들때 main 함수 위에 마리오 파티의
   큰 틀에서만 움직이는 함수만 선언과 동시에 작성해주면 좋겠습니다.
   즉 main함수 위에서는 다른 게임들에 필요한 함수가 있다면
   주석을 달고
   //~~게임에 필요한 함수들
   그리고 그 아래에
   mouscallback();
   timercallback();
   void ~~();
   //여기까지 무슨무슨 게임에 필요한 함수 라고 적고
   main함수 아래에 동작기능 넣어주시길 권유합니다.
   여기서 만약 mousecallback_pm_game()이런 식으로 만들었다면
   mousecallback_mario_party안에
   mousecallback_pm_game();를 넣어주세요 따로 setmousecallback하면 절대 안됩니다!!
3. 만약 게임을 합치실 때 이미지파일에 사진을 넣지 않으셨다면 이미지파일에
   사진을 넣은 후 합치시는걸 권유드립니다. - 아니라면 너무 복잡해져요
   혹시 이미지 파일에 사진을 넣으셨더라도 조금 번거로우시겠지만 각각 게임별 이미지를
   구분하기 위해서 Images/이렇게 된 것을 그 게임 이미지파일 명을 ~~game_Images라고
   변경해주신 후 합치시는걸 추천드립니다. -이렇게 될 경우 각각 코드내에서
   Images/ -> ~~game_Images/라고 변경하시는건 당연하겠죠?
*/

/*해야할 내용을 적는 장소 필요시 적을것 !!번호가 꼭 우선 순위는 아님!!/ 다하면 삭제 필수!!
1. 카드의 효과에 따라서 어떤 작용을 할 것인지 넣어주는 작업 -- 430번째 줄
여기까지가 해야할 내용입니당.*/


//마리오 파티 큰 틀에서의 장면들과 오브젝트
SceneID mario_game_description, game_board, card_draw_place, dice_roll_place, mario_party_final_cal;
ObjectID mario_party_next, run_dice, Game_end;
ObjectID player1_object, player2_object, player3_object;
SoundID mario_party_sound1;
//마리오파티 플레이어 움직이는 타이머 12개!
//0->1 ~~~~~~~~~~~~~~~~~~ 11~12
TimerID moving_timer_1, moving_timer_2, moving_timer_3, moving_timer_4;
TimerID moving_timer_5, moving_timer_6, moving_timer_7, moving_timer_8;
TimerID moving_timer_9, moving_timer_10, moving_timer_11, moving_timer_12;
//각각의 미니게임에 진입할 때 필요한 타이머 9개
TimerID enter_1_1, enter_1_2, enter_1_3, enter_1_4;
TimerID enter_2_1, enter_2_2, enter_2_3, enter_2_4;
TimerID enter_3_1, enter_3_2, enter_3_3, enter_3_4;
//주사위 굴리는 장소에서의 물체들(임의로 주사위로 칭함 숫자는 1-3까지 있음)-그냥 슬롯머신임 ㅇㅇ
ObjectID dice_slot, dice_num, run_dice_in;
//주사위 굴리는 장소에서의 타이머 설정
TimerID rolling_time, rolling_dice_timer, rolling_dice_escape_timer;
//주사위 굴리는 장소에서의 player를 움직일 마지막 나온 숫자
int random_result;
// card_draw_place에서 사용할 물체들
ObjectID choice_card[5], card_back[5];
//1-3,2-3,3-3에서의 카드 뽑을 때 사용할 타이머
TimerID drawing_card_escape_timer;
//card_draw_place에서 사용할 전역변수
int card_random_num;
//플레이어의 위치를 통해서 진입할 미니게임을 결정
//start에서의 위치가 0이고 1-1에서의 위치가 1 / 즉, 위치는 12(3-4)까지가 한계
//과거의 위치를 기억해서 타이머를 통해서 움직여줄 예정
int player_future_location = 0;
int player1_future_location = 0;
int player1_location = 0;
int player2_future_location = 0;
int player2_location = 0;
int player3_future_location = 0;
int player3_location = 0;

//마리오파티 전체에서의 플레이어 점수 - 게임의 승패를 결정
//후에 시간이 된다면 메세지를 통해서 미니게임이 끝나고 보드로 들어올때 메세지로 점수 표기//
int mario_party_player1_score = 0;
int mario_party_player2_score = 0;
int mario_party_player3_score = 0;

//마리오 게임의 시작
bool in_game_board = false;

//임시 각각 스테이지별 bool형 -- 아래에 dice_on과 card_on이 존재하므로 1-3,2-3,3-3은 생성 x
bool stage_1_1 = false, stage_1_2 = false, stage_1_4 = false;
bool stage_2_1 = false, stage_2_2 = false, stage_2_4 = false;
bool stage_3_1 = false, stage_3_2 = false, stage_3_4 = false;
//모든 스테이지는 한번만 운영
bool stage_1_2_finish = false, stage_3_1_finish = false;
bool stage_2_2_finish = false, stage_3_2_finish = false;
bool stage_1_4_finish = false, stage_2_4_finish = false, stage_3_4_finish = false;
bool final_cal = false;
//bool형으로 player중 누가 이동할 차례인지 알아봄
bool player1 = false;
bool player2 = false;
bool player3 = false;

//bool형을 통한 run_dice를 누른 후 dice_roll_place 진입
//그 후 dice가 돌아갈 수 있게 만들어주는 변수 하나 설정
bool dice_on = false;

//bool 형을 통한 1-3,2-3,3-3에서의 카드 진입 확인
//1-3,2-3,3-3 진입시 필수로 card_on = true 깔아주고 
// board로 진입시 in_game_board = true 와 card_on = false 해줄것 
bool card_on = false;

//점수확인용 임시 플레이어 점수 출력
void check_player_score() {
	printf("\n%d ", mario_party_player1_score);
	printf("%d ", mario_party_player2_score);
	printf("%d\n", mario_party_player3_score);
	char buff1[300];
	char buff2[100];
	char buff3[100];
	sprintf(buff1, "player1: %d 점\n", mario_party_player1_score);
	sprintf(buff2, "player2: %d 점\n", mario_party_player2_score);
	sprintf(buff3, "player3: %d 점", mario_party_player3_score);
	strcat(buff1, buff2);
	strcat(buff1, buff3);
	showMessage(buff1);
}


//1-1 스테이지에 들어갈 +,- 게임에 대한 전역변수와 여러가지 등등
SceneID pmdescription, pm_1, pm_2, pm_3, pm_game_final_cal;

ObjectID pm_game_number1[4], pm_game_number2[4];
ObjectID pm_game_Next1;
ObjectID pm_game_pm[3];
ObjectID pm_game_little_white[3];

TimerID pm_timer1, pm_timer2, pm_timer3, pm_enter_game_board_timer;
TimerID pm_enter_2, pm_enter_3, pm_enter_final;

bool pm_game_choice1 = false;
bool pm_game_choice1_1 = false, pm_game_choice1_2 = false, pm_game_choice1_3 = false;
bool pm_game_choice2 = false;
bool pm_game_choice2_1 = false, pm_game_choice2_2 = false, pm_game_choice2_3 = false;
bool pm_game_choice3 = false;
bool pm_game_choice3_1 = false, pm_game_choice3_2 = false, pm_game_choice3_3 = false;

bool pm_player1 = false;
bool pm_player2 = false;
bool pm_player3 = false;
// +, - 결정
int pm_game_random_pm[3];
// 숫자 결정
int pm_game_random_num[4];

//각자 수 계산된 것 저장
int pm_game_cal[3];

void pm_game_create_pm();
void pm_game_create_number();
void pm_game_create();
void pm_game_simul();
void pm_game_simul_2();
void pm_game_simul_3();
int pm_game_calculation(int* pm, int* num);

void mouseCallback_pm_game(ObjectID object, int x, int y, MouseAction action);
void timerCallback_pm_game(TimerID timer);
//여기까지 1-1 전역변수 및 함수

//여기부터 1-2 달리기게임 전역변수 및 함수
SceneID scene_running_playground, scene_running_explain, scene_running_end;
ObjectID startbutton_running, pitch1_running, mario1_running, mush1_running;
TimerID running_game_escape_timer;
int pitch1X = 0, pitch1Y = 360;
int mario1X = 0, mario1Y = 190;
int mush1X = 0, mush1Y = 40;
void mouseCallback_running_game(ObjectID object, int x, int y, MouseAction action);
void keyboardCallback_running_game(KeyCode code, KeyState state);
void timerCallback_running_game(TimerID timer);
//여기까지 1-2 달리기게임 전역변수 및 함수

//여기부터 1-4 스테이지 전역변수 및 함수
SceneID puzzle_game_scene1;
ObjectID puzzle_game_next;
ObjectID puzzle_game_s[10];
TimerID puzzle_game_timer1, puzzle_game_timer2, puzzle_game_escape_timer;
int puzzle_game_X[5] = { 0,340,540,740,0 };
int puzzle_game_Y[5] = { 0,460,260,60,0 };
int puzzle_game_YX[5][5] = { {-1,-1,-1,-1,-1},
							{-1,1,2,3,-1},
							{-1,4,5,6,-1},
							{-1,7,8,9,-1},
							{-1,-1,-1,-1,-1} };
int puzzle_game_cx, puzzle_game_cy, puzzle_game_snum = 1, puzzle_game_success = 0;
int puzzle_game_r_num, puzzle_game_x0, puzzle_game_y0;
int puzzle_game_dif = 50;
float puzzle_game_t, puzzle_game_t1, puzzle_game_t2, puzzle_game_t3;
int puzzle_game_pT = 1;
void puzzle_game_setS();
void puzzle_game_move1(int num1, int x1, int y1, int x2, int y2);
void puzzle_game_move2(int x1, int y1, int x2, int y2);
void puzzle_game_moveS(int num);
void puzzle_game_arrangeS();
void mouseCallback_puzzle_game(ObjectID object, int x, int y, MouseAction action);
void timerCallback_puzzle_game(TimerID timer);
//여기까지 1-4 스테이지 전역변수 및 함수


//2-1 스테이지에 들어갈 카드맞추기 게임에 대한 전역 변수
SceneID card_match_card_description, card_match_card_game, card_match_card_final_cal;
ObjectID card_match_Next, card_match_go;
ObjectID card[20], swap_card[20];
TimerID card_match_move_timer, card_match_go_timer, card_match_reverse_timer, card_match_show_timer, card_match_escape_timer;

bool card_game_start = false;
bool card_game_card_no_choice = true;
bool card_game_card_second_choice = false;

int card_game_first = 100;
int card_game_card_first = 100;
int card_game_show = 100;
int card_game_find_pair = 0;
int card_game_card_match_score[3] = { 0 , 0 , 0 };
int min;

bool card_game_card_player1 = true;
bool card_game_card_player2 = false;
bool card_game_card_player3 = false;

void create_card();
void reverse();
void card_move(int i, int blank);
void change_turn();
void find_change_turn();
void card_match_game_reset();
void card_match_check_score(int* card_in_score);
void mouseCallback_card_match(ObjectID object, int x, int y, MouseAction action);
void timerCallback_card_match(TimerID timer);
//여기까지 카드 맞추기 함수와 전역변수 끝~

//2-2 스테이지에 들어간 전역변수와 함수들
SceneID scene_escape_explain, scene_escape_playground, scene_escape_end;
ObjectID player1_escape, player2_escape, player3_escape, startbutton_escape, endbutton_escape;
TimerID timer1_escape, timer2_escape, timer3_escape, escaping_game_escape_timer;
int speed_escape = 0;
int speed1_escape = 0;
int speed2_escape = 0;
int x_escape = 600;
int x1_escape = 300;
int x2_escape = 900;
int foesspeed = 1;
int score_escape = 0;
ObjectID foes[100];
int foesX[100];
int foesY[100];
float foesSize[100];

void escaping_game_createFoes();
void escaping_game_foesmove();
bool escaping_game_pointInRect(int x, int y, int rx, int ry, int size);
bool escaping_game_pointInRect1(int x1, int y1, int rx1, int ry1, int size);
bool escaping_game_pointInRect2(int x2, int y2, int rx2, int ry2, int size);
bool escaping_game_collided(int x, int y, int rx, int ry, int size);
bool escaping_game_collided2(int x1, int y1, int rx1, int ry1, int size);
bool escaping_game_collided3(int x2, int y2, int rx2, int ry2, int size);
bool escaping_game_checkCollision();
bool escaping_game_checkCollision1();
bool escaping_game_checkCollision2();
void keyboardCallback_escaping_game(KeyCode code, KeyState state);
void escaping_game_player1move();
void escaping_game_player2move();
void escaping_game_player3move();
void mouseCallback_escaping_game(ObjectID object, int x, int y, MouseAction action);
void timerCallback_escaping_game(TimerID timer);
//여기까지 2-2 스테이지에 들어갈 전역변수와 함수들

//2-4 스테이지에 들어갈 전역변수와 함수들
SceneID slot_game_slot_description, slot_game_board, slot_game_final_cal;
ObjectID slot_game_Next, slot_game_player;
ObjectID slot_game_slot_picture[3], slot_game_slot_lever;

TimerID slotgame_timer, slot_game_slot_timer, slot_game_enter_cal_scene;
TimerID slot_game_player1_timer, slot_game_player2_timer, slot_game_player3_timer;
TimerID slot_game_escape_timer;

//잭팟인지 아닌지 체크 - 3개 다 같은 것인지
int slot_game_jackpot_check[3];
//등수로 이 score를 사용
int slot_game_score[3] = { 3, 3, 3 };

bool slot_game_start = false;

bool slot_lever_running = false;

bool slot_game_player1 = false;
bool slot_game_player1_success = false;
bool slot_game_player2 = false;
bool slot_game_player2_success = false;
bool slot_game_player3 = false;
bool slot_game_player3_success = false;

void slot_game_create_slot_Image();
void slot_game_slot_score_check();
void slot_game_game_reset();
void mouseCallback_slot_game(ObjectID object, int x, int y, MouseAction action);
void timerCallback_slot_game(TimerID timer);
//여기까지 2-4스테이지 슬롯머신 함수들

//여기부터 3-1 스테이지 미로 전역변수 및 함수들
int maze_game_block[18][32] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
							    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,1,0,1,0,0,0,1},
							    {1,0,0,0,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0,0,0,1,1,0,0,0,0,1,0,1,0,1},
							    {1,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,1,1,0,0,0,1,1,1,0,1,0,1},
							    {1,1,0,0,1,1,1,1,0,1,1,1,0,1,1,0,1,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1},
							    {1,1,0,0,1,1,1,1,0,1,1,1,0,0,0,0,1,1,0,1,1,0,0,1,0,1,1,1,1,1,0,1},
							    {1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,1,0,1,1,0,1,0,0,0,0,0,1},
							    {1,0,0,0,0,0,1,1,0,1,1,1,0,1,0,0,0,1,0,0,0,0,1,1,0,1,0,0,0,0,0,1},
							    {1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,0,1,1,0,1,1,0,1,0,2,2,2,0,1},
							    {1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,1,0,2,2,2,0,1},
							    {1,0,0,0,0,0,1,0,1,1,0,1,1,1,0,0,0,1,0,1,1,1,1,0,0,1,0,0,0,0,0,1},
							    {1,0,0,0,0,0,1,0,1,1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,1},
							    {1,1,0,0,1,1,1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
							    {1,1,0,0,1,1,1,0,1,1,0,1,0,1,1,0,1,1,1,0,1,1,1,0,1,0,0,0,0,0,0,1},
							    {1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,1,1,0,1,0,1,1,1,1,0,1},
							    {1,0,1,1,1,0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,0,1},
							    {1,0,0,0,1,0,1,1,1,1,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
							    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };
SceneID maze_game_scene1;
ObjectID maze_game_p1, maze_game_p2, maze_game_p3, maze_game_M, maze_game_light, maze_game_success, maze_game_next;
TimerID maze_game_timer1, maze_game_escape_timer;
int maze_game_IX = 80, maze_game_IY = 300;
int maze_game_p1dx, maze_game_p1dy, maze_game_p2dx, maze_game_p2dy, maze_game_p3dx, maze_game_p3dy;
int maze_game_RN;
int maze_game_speed = 2, maze_game_lt = 1;
float maze_game_bm = 2;
float maze_game_t = 0;
float maze_game_p1x = maze_game_IX, maze_game_p1y = maze_game_IY, maze_game_p2x = maze_game_IX + 30;
float maze_game_p2y = maze_game_IY, maze_game_p3x = maze_game_IX + 60, maze_game_p3y = maze_game_IY;
float maze_game_MX = 604, maze_game_MY = 324;

int maze_game_direction(int dx, int dy);
void maze_game_backmove(float* x, float* y, int dir);
void maze_game_isBlocked(ObjectID object, int x, int y, int dir);
void maze_game_checkBlock(ObjectID object, int x, int y, int dir, int size);
void maze_game_setImageD(ObjectID object1, int id, int dir);
void timerCallback_maze_game(TimerID timer);
void keyboardCallback_maze_game(KeyCode code, KeyState state);
void mouseCallback_maze_game(ObjectID object, int x, int y, MouseAction action);
//여기까지 3-1 스테이지 미로 전역변수 및 함수들

//여기부터 3-2 숨은 그림 찾기 전역변수 및 함수들
int find_game_block[18][32] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
							    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
						  	    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
						  	    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };
SceneID find_game_scene1;
ObjectID find_game_p1, find_game_p2, find_game_p3, find_game_O[22], find_game_X[22], find_game_next;
TimerID find_game_timer1, find_game_escape_timer;

int find_game_IX = 630, find_game_IY = 400;
int find_game_p1dx, find_game_p1dy, find_game_p2dx, find_game_p2dy, find_game_p3dx, find_game_p3dy;
int find_game_speed = 2;

float find_game_bm = 2;
float find_game_t = 0;
float find_game_p1x = find_game_IX, find_game_p1y = find_game_IY, find_game_p2x = find_game_IX, find_game_p2y = find_game_IY + 50, find_game_p3x = find_game_IX, find_game_p3y = find_game_IY + 100;

int find_game_p1score, find_game_p2score, find_game_p3score;

int find_game_direction(int dx, int dy);
void find_game_backmove(float* x, float* y, int dir);
void find_game_isBlocked(ObjectID object, int x, int y, int dir);
void find_game_checkBlock(ObjectID object, int x, int y, int dir, int size);
void find_game_setboard();
void timerCallback_find_game(TimerID timer);
void find_game_checkFinish();
void keyboardCallback_find_game(KeyCode code, KeyState state);
void mouseCallback_find_game(ObjectID object, int x, int y, MouseAction action);
// 3-2 스테이지 전역변수 및 함수 설정 끝


//여기부터 3-4 스테이지 area battle 전역변수 및 함수들
int area_game_board1[6][14] = { {4,4,4,4,4,4,4,4,4,4,4,4,4,4},
							    {4,5,5,5,5,4,4,5,4,5,4,4,5,5},
								{4,5,6,5,5,5,5,5,5,5,5,5,5,5},
								{4,4,6,5,6,6,6,5,5,6,6,6,6,6},
								{4,4,6,6,6,5,5,5,5,6,6,6,6,6},
								{4,4,4,4,6,6,6,6,6,6,6,6,6,6} };
int area_game_board2[6][14] = { {4,5,5,5,5,5,5,6,6,6,6,6,6,6},
								{4,5,5,5,5,5,5,6,6,5,6,5,6,6},
								{4,4,4,4,4,5,5,5,5,5,5,5,6,6},
								{4,4,4,4,4,5,5,4,4,4,4,5,6,6},
								{4,4,4,4,4,4,4,4,5,5,5,5,5,6},
								{4,4,4,4,6,6,6,6,6,6,6,6,6,6} };
int area_game_board3[6][14] = { {4,4,5,5,5,5,5,5,5,5,5,5,5,6},
								{4,4,5,5,4,4,4,4,4,4,5,5,6,6},
								{4,4,5,5,4,4,6,6,6,4,5,5,5,6},
								{4,4,5,5,4,4,6,6,6,4,5,5,5,6},
								{4,4,4,4,4,4,6,6,6,4,5,5,5,6},
								{6,6,6,6,6,6,6,6,6,6,6,6,6,6} };


SceneID area_game_scene1;
ObjectID area_game_p1, area_game_p2, area_game_p3, area_game_p1B[29], area_game_p2B[29], area_game_p3B[29], area_game_next;
TimerID area_game_timer1, area_game_timer2, area_game_timer3;
TimerID area_game_escape_timer;

int area_game_score[3] = { 0,0,0 };

int area_game_IX = 550, area_game_IY = 650;

int area_game_p1dx, area_game_p1dy;
int area_game_p2dx, area_game_p2dy;
int area_game_p3dx, area_game_p3dy;

int area_game_N, area_game_n1, area_game_n2, area_game_n3, area_game_j;

int area_game_speed = 5, area_game_k1 = 0, area_game_k2 = 0, area_game_k3 = 0;

float area_game_sc1 = 0, area_game_sc2 = 0, area_game_sc3 = 0;

float area_game_p1x = area_game_IX, area_game_p1y = area_game_IY, area_game_p2x = area_game_IX + 100;
float area_game_p2y = area_game_IY, area_game_p3x = area_game_IX + 200, area_game_p3y = area_game_IY;

int area_game_B1X, area_game_B1Y, area_game_B2X, area_game_B2Y, area_game_B3X, area_game_B3Y;
int area_game_R1 = 1, area_game_winnerN = 0, area_game_winner[3];

bool area_game_P1T = true, area_game_P2T = true, area_game_P3T = true;

void area_game_reset();
void area_game_chooseBlock(int BX, int BY, int* n, int type);
void mouseCallback_area_game(ObjectID object, int x, int y, MouseAction action);
void timerCallback_area_game(TimerID timer);
void keyboardCallback_area_game(KeyCode code, KeyState state);


//player1, player2, player3를 번갈아서 돌아갈 수 있도록 만듬
//각 스테이지 미니게임이 끝날때마다 이 함수 써주는거 필수!!!!!!!
void change_player() {
	//만약 위치가 3-4일때 경우의 수 따져줘야함
	if (player1 == true) {
		player1 = false;
		player2 = true;
	}
	else if (player2 == true) {
		player2 = false;
		player3 = true;
	}
	else if (player3 == true) {
		player3 = false;
		player1 = true;
	}
}
//일단 움직이는건 이 아래 함수들로 만드는데 진입 할때를 적절히 정해줘야할듯

void showMessagewinner(int score1, int score2, int score3) {
	char buff1[300];
	char buff2[100];
	char buff3[100];
	sprintf(buff1, "Player1: %d등\n", score1);
	sprintf(buff2, "Player2: %d등\n", score2);
	sprintf(buff3, "Player3: %d등\n", score3);
	strcat(buff1, buff2);
	strcat(buff1, buff3);
	showMessage(buff1);
}

void check_mario_party_winner() {
	int player1_score = mario_party_player1_score;
	int player2_score = mario_party_player2_score;
	int player3_score = mario_party_player3_score;
	if (player1_score > player2_score && player1_score > player3_score) {
		if (player2_score > player3_score) {
			showMessagewinner(1, 2, 3);
		}
		else if (player2_score < player3_score) {
			showMessagewinner(1, 3, 2);
		}
	}
	else if (player2_score > player1_score && player2_score > player3_score) {
		if (player1_score > player3_score) {
			showMessagewinner(2, 1, 3);
		}
		else if (player1_score < player3_score) {
			showMessagewinner(3, 1, 2);
		}
	}
	else if (player3_score > player1_score && player3_score > player2_score) {
		if (player1_score > player2_score) {
			showMessagewinner(2, 3, 1);
		}
		else if (player1_score < player2_score) {
			showMessagewinner(3, 2, 1);
		}
	}
	else if (player1_score == player2_score) {
		if (player1_score < player3_score) {
			showMessagewinner(3, 3, 1);
		}
		else if (player1_score > player3_score) {
			showMessagewinner(1, 1, 3);
		}
	}
	else if (player1_score == player3_score) {
		if (player1_score < player2_score) {
			showMessagewinner(3, 1, 3);
		}
		else if (player1_score > player2_score) {
			showMessagewinner(1, 3, 1);
		}
	}
	else if (player2_score == player3_score) {
		if (player1_score < player2_score) {
			showMessagewinner(3, 1, 1);
		}
		else if (player1_score > player2_score) {
			showMessagewinner(1, 3, 3);
		}
	}
	else if (player1_score == player2_score && player2_score == player3_score) {
		showMessagewinner(1, 1, 1);
	}
}

//주사위를 통해서 플레이어 위치를 변경시켜주는 함수
void create_dice_number() {
	int random_create = rand() % 3 + 1;
	char buff[100];
	sprintf(buff, "Images/roll_dice%d.png", random_create);
	setObjectImage(dice_num, buff);
	random_result = random_create;
}



void move_player(int dice_result) {
	int random_move = dice_result;
	if (player1 == true) {
		player1_future_location = player1_location;
		player1_location += random_move;
		if (player1_location >= 12) {
			player1_location = 12;
		}
	}
	else if (player2 == true) {
		player2_future_location = player2_location;
		player2_location += random_move;
		if (player2_location >= 12) {
			player2_location = 12;
		}
	}
	else if (player3 == true) {
		player3_future_location = player3_location;
		player3_location += random_move;
		if (player3_location >= 12) {
			player3_location = 12;
		}
	}
}

void future_location_check() {
	if (player1 == true) {
		player_future_location = player1_future_location;
	}
	else if (player2 == true) {
		player_future_location = player2_future_location;
	}
	else if (player3 == true) {
		player_future_location = player3_future_location;
	}
}

void random_result_1() {
	future_location_check();
	switch (player_future_location) {
	case 0:
		startTimer(moving_timer_1);
		startTimer(enter_1_1);
		break;
	case 1:
		startTimer(moving_timer_2);
		startTimer(enter_1_2);
		break;
	case 2:
		startTimer(moving_timer_3);
		startTimer(enter_1_3);
		break;
	case 3:
		startTimer(moving_timer_4);
		startTimer(enter_1_4);
		break;
	case 4:
		startTimer(moving_timer_5);
		startTimer(enter_2_1);
		break;
	case 5:
		startTimer(moving_timer_6);
		startTimer(enter_2_2);
		break;
	case 6:
		startTimer(moving_timer_7);
		startTimer(enter_2_3);
		break;
	case 7:
		startTimer(moving_timer_8);
		startTimer(enter_2_4);
		break;
	case 8:
		startTimer(moving_timer_9);
		startTimer(enter_3_1);
		break;
	case 9:
		startTimer(moving_timer_10);
		startTimer(enter_3_2);
		break;
	case 10:
		startTimer(moving_timer_11);
		startTimer(enter_3_3);
		break;
	case 11:
		startTimer(moving_timer_12);
		startTimer(enter_3_4);
		break;
	}
}

void random_result_2() {
	future_location_check();
	switch (player_future_location) {
	case 0:
		setTimer(moving_timer_2, 2.f);
		setTimer(enter_1_2, 3.f);
		startTimer(moving_timer_1);
		startTimer(moving_timer_2);
		startTimer(enter_1_2);
		break;
	case 1:
		setTimer(moving_timer_3, 2.f);
		setTimer(enter_1_3, 3.f);
		startTimer(moving_timer_2);
		startTimer(moving_timer_3);
		startTimer(enter_1_3);
		break;
	case 2:
		setTimer(moving_timer_4, 2.f);
		setTimer(enter_1_4, 3.f);
		startTimer(moving_timer_3);
		startTimer(moving_timer_4);
		startTimer(enter_1_4);
		break;
	case 3:
		setTimer(moving_timer_5, 2.f);
		setTimer(enter_2_1, 3.f);
		startTimer(moving_timer_4);
		startTimer(moving_timer_5);
		startTimer(enter_2_1);
		break;
	case 4:
		setTimer(moving_timer_6, 2.f);
		setTimer(enter_2_2, 3.f);
		startTimer(moving_timer_5);
		startTimer(moving_timer_6);
		startTimer(enter_2_2);
		break;
	case 5:
		setTimer(moving_timer_7, 2.f);
		setTimer(enter_2_3, 3.f);
		startTimer(moving_timer_6);
		startTimer(moving_timer_7);
		startTimer(enter_2_3);
		break;
	case 6:
		setTimer(moving_timer_8, 2.f);
		setTimer(enter_2_4, 3.f);
		startTimer(moving_timer_7);
		startTimer(moving_timer_8);
		startTimer(enter_2_4);
		break;
	case 7:
		setTimer(moving_timer_9, 2.f);
		setTimer(enter_3_1, 3.f);
		startTimer(moving_timer_8);
		startTimer(moving_timer_9);
		startTimer(enter_3_1);
		break;
	case 8:
		setTimer(moving_timer_10, 2.f);
		setTimer(enter_3_2, 3.f);
		startTimer(moving_timer_9);
		startTimer(moving_timer_10);
		startTimer(enter_3_2);
		break;
	case 9:
		setTimer(moving_timer_11, 2.f);
		setTimer(enter_3_3, 3.f);
		startTimer(moving_timer_10);
		startTimer(moving_timer_11);
		startTimer(enter_3_3);
		break;
	case 10:
		setTimer(moving_timer_12, 2.f);
		setTimer(enter_3_4, 3.f);
		startTimer(moving_timer_11);
		startTimer(moving_timer_12);
		startTimer(enter_3_4);
		break;
	case 11:
		startTimer(moving_timer_12);
		startTimer(enter_3_4);
		break;
	}
}

void random_result_3() {
	future_location_check();
	switch (player_future_location) {
	case 0:
		setTimer(moving_timer_2, 2.f);
		setTimer(moving_timer_3, 3.f);
		setTimer(enter_1_3, 4.f);
		startTimer(moving_timer_1);
		startTimer(moving_timer_2);
		startTimer(moving_timer_3);
		startTimer(enter_1_3);
		break;
	case 1:
		setTimer(moving_timer_3, 2.f);
		setTimer(moving_timer_4, 3.f);
		setTimer(enter_1_4, 4.f);
		startTimer(moving_timer_2);
		startTimer(moving_timer_3);
		startTimer(moving_timer_4);
		startTimer(enter_1_4);
		break;
	case 2:
		setTimer(moving_timer_4, 2.f);
		setTimer(moving_timer_5, 3.f);
		setTimer(enter_2_1, 4.f);
		startTimer(moving_timer_3);
		startTimer(moving_timer_4);
		startTimer(moving_timer_5);
		startTimer(enter_2_1);
		break;
	case 3:
		setTimer(moving_timer_5, 2.f);
		setTimer(moving_timer_6, 3.f);
		setTimer(enter_2_2, 4.f);
		startTimer(moving_timer_4);
		startTimer(moving_timer_5);
		startTimer(moving_timer_6);
		startTimer(enter_2_2);
		break;
	case 4:
		setTimer(moving_timer_6, 2.f);
		setTimer(moving_timer_7, 3.f);
		setTimer(enter_2_3, 4.f);
		startTimer(moving_timer_5);
		startTimer(moving_timer_6);
		startTimer(moving_timer_7);
		startTimer(enter_2_3);
		break;
	case 5:
		setTimer(moving_timer_7, 2.f);
		setTimer(moving_timer_8, 3.f);
		setTimer(enter_2_4, 4.f);
		startTimer(moving_timer_6);
		startTimer(moving_timer_7);
		startTimer(moving_timer_8);
		startTimer(enter_2_4);
		break;
	case 6:
		setTimer(moving_timer_8, 2.f);
		setTimer(moving_timer_9, 3.f);
		setTimer(enter_3_1, 4.f);
		startTimer(moving_timer_7);
		startTimer(moving_timer_8);
		startTimer(moving_timer_9);
		startTimer(enter_3_1);
		break;
	case 7:
		setTimer(moving_timer_9, 2.f);
		setTimer(moving_timer_10, 3.f);
		setTimer(enter_3_2, 4.f);
		startTimer(moving_timer_8);
		startTimer(moving_timer_9);
		startTimer(moving_timer_10);
		startTimer(enter_3_2);
		break;
	case 8:
		setTimer(moving_timer_10, 2.f);
		setTimer(moving_timer_11, 3.f);
		setTimer(enter_3_3, 4.f);
		startTimer(moving_timer_9);
		startTimer(moving_timer_10);
		startTimer(moving_timer_11);
		startTimer(enter_3_3);
		break;
	case 9:
		setTimer(moving_timer_11, 2.f);
		setTimer(moving_timer_12, 3.f);
		setTimer(enter_3_4, 4.f);
		startTimer(moving_timer_10);
		startTimer(moving_timer_11);
		startTimer(moving_timer_12);
		startTimer(enter_3_4);
		break;
	case 10:
		setTimer(moving_timer_12, 2.f);
		setTimer(enter_3_4, 3.f);
		startTimer(moving_timer_11);
		startTimer(moving_timer_12);
		startTimer(enter_3_4);
		break;
	case 11:
		startTimer(moving_timer_12);
		startTimer(enter_3_4);
		break;
	}
}

void player_move_random_result() {
	switch (random_result) {
	case 1:
		random_result_1();
		break;
	case 2:
		random_result_2();
		break;
	case 3:
		random_result_3();
		break;
	}
}

//가장 근간이 되는 캐릭터의 이동 한칸씩 이동 
void player_move_in_board() {
	if (in_game_board == true) {
		//random_result를 통해서 player가 몇 번 이동할지 받아주고
		//각각의 위치로 이동하는 타이머 설정해놓은거 써줌
		player_move_random_result();
	}
}
//여기까지 일단 플레이어 game_board에서 움직이는 함수들


//1-3,2-3,3-3에서 뽑을 수 있는 카드의 종류는 총 5가지
//그 5가지를 랜덤으로 뽑은 후 보여주는 것을 설정한 함수
void draw_card() {
	int random_num = rand() % 5;
	for (int i = 0; i < 5; i++) {
		char temp[100];
		sprintf(temp, "Images/card_back%d.png", i % 5);
		card_back[i] = createObject(temp);
		locateObject(card_back[i], card_draw_place, 200 + 200 * i, 200);
		showObject(card_back[i]);
		char buff[100];
		sprintf(buff, "Images/chance_card%d.png", i % 5);
		choice_card[i] = createObject(buff);
	}
	card_random_num = random_num;
}

void card_choice_1() {
	if (player1 == true) mario_party_player1_score *= 2;
	else if (player2 == true) mario_party_player2_score *= 2;
	else if (player3 == true) mario_party_player3_score *= 2;
	startTimer(drawing_card_escape_timer);
}

void card_choice_2() {
	if (player1 == true) mario_party_player1_score /= 2;
	else if (player2 == true) mario_party_player2_score /= 2;
	else if (player3 == true) mario_party_player3_score /= 2;
	startTimer(drawing_card_escape_timer);
}

void card_choice_3() {
	if (player1 == true) mario_party_player1_score -= 10;
	else if (player2 == true) mario_party_player2_score -= 10;
	else if (player3 == true) mario_party_player3_score -= 10;
	startTimer(drawing_card_escape_timer);
}

void card_choice_4() {
	if (player1 == true) mario_party_player1_score += 10;
	else if (player2 == true) mario_party_player2_score += 10;
	else if (player3 == true) mario_party_player3_score += 10;
	startTimer(drawing_card_escape_timer);
}

void card_choice_5() {
	if (player1 == true) mario_party_player1_score = 0;
	else if (player2 == true) mario_party_player2_score = 0;
	else if (player3 == true) mario_party_player3_score = 0;
	startTimer(drawing_card_escape_timer);
}

// 카드 선택 할때 나오는 효과들 
void mousecallback_choose_card(ObjectID object, int x, int y, MouseAction action) {
	if (card_on == true) {
		switch (card_random_num) {
		case 0:
			if (object == card_back[0]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[0], card_draw_place, 500, 200);
				showObject(choice_card[0]);
				card_choice_1();
			}
			else if (object == card_back[1]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[1], card_draw_place, 500, 200);
				showObject(choice_card[1]);
				card_choice_2();
			}
			else if (object == card_back[2]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[2], card_draw_place, 500, 200);
				showObject(choice_card[2]);
				card_choice_3();
			}
			else if (object == card_back[3]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[3], card_draw_place, 500, 200);
				showObject(choice_card[3]);
				card_choice_4();
			}
			else if (object == card_back[4]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[4], card_draw_place, 500, 200);
				showObject(choice_card[4]);
				card_choice_5();
			}
			break;
		case 1:
			if (object == card_back[0]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[1], card_draw_place, 500, 200);
				showObject(choice_card[1]);
				card_choice_2();
			}
			else if (object == card_back[1]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[2], card_draw_place, 500, 200);
				showObject(choice_card[2]);
				card_choice_3();
			}
			else if (object == card_back[2]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[3], card_draw_place, 500, 200);
				showObject(choice_card[3]);
				card_choice_4();
			}
			else if (object == card_back[3]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[4], card_draw_place, 500, 200);
				showObject(choice_card[4]);
				card_choice_5();
			}
			else if (object == card_back[4]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[0], card_draw_place, 500, 200);
				showObject(choice_card[0]);
				card_choice_1();
			}
			break;
		case 2:
			if (object == card_back[0]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[2], card_draw_place, 500, 200);
				showObject(choice_card[2]);
				card_choice_3();
			}
			else if (object == card_back[1]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[3], card_draw_place, 500, 200);
				showObject(choice_card[3]);
				card_choice_4();
			}
			else if (object == card_back[2]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[4], card_draw_place, 500, 200);
				showObject(choice_card[4]);
				card_choice_5();
			}
			else if (object == card_back[3]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[0], card_draw_place, 500, 200);
				showObject(choice_card[0]);
				card_choice_1();
			}
			else if (object == card_back[4]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[1], card_draw_place, 500, 200);
				showObject(choice_card[1]);
				card_choice_2();
			}
			break;
		case 3:
			if (object == card_back[0]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[3], card_draw_place, 500, 200);
				showObject(choice_card[3]);
				card_choice_4();
			}
			else if (object == card_back[1]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[4], card_draw_place, 500, 200);
				showObject(choice_card[4]);
				card_choice_5();
			}
			else if (object == card_back[2]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[0], card_draw_place, 500, 200);
				showObject(choice_card[0]);
				card_choice_1();
			}
			else if (object == card_back[3]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[1], card_draw_place, 500, 200);
				showObject(choice_card[1]);
				card_choice_2();
			}
			else if (object == card_back[4]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[2], card_draw_place, 500, 200);
				showObject(choice_card[2]);
				card_choice_3();
			}
			break;
		case 4:
			if (object == card_back[0]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[4], card_draw_place, 500, 200);
				showObject(choice_card[4]);
				card_choice_5();
			}
			else if (object == card_back[1]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[0], card_draw_place, 500, 200);
				showObject(choice_card[0]);
				card_choice_1();
			}
			else if (object == card_back[2]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[1], card_draw_place, 500, 200);
				showObject(choice_card[1]);
				card_choice_2();
			}
			else if (object == card_back[3]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[2], card_draw_place, 500, 200);
				showObject(choice_card[2]);
				card_choice_3();
			}
			else if (object == card_back[4]) {
				for (int i = 0; i < 5; i++) hideObject(card_back[i]);
				locateObject(choice_card[3], card_draw_place, 500, 200);
				showObject(choice_card[3]);
				card_choice_4();
			}
			break;
		}
	}
}

//마리오 파티라는 큰 게임틀에서만의 mousecallback 다른 클릭은 다른 mousecallback 생성 권유
void mouseCallback_mario_party(ObjectID object, int x, int y, MouseAction action) {
	mousecallback_choose_card(object, x, y, action);
	mouseCallback_card_match(object, x, y, action);
	mouseCallback_pm_game(object, x, y, action);
	mouseCallback_slot_game(object, x, y, action);
	mouseCallback_area_game(object, x, y, action);
	mouseCallback_find_game(object, x, y, action);
	mouseCallback_maze_game(object, x, y, action);
	mouseCallback_running_game(object, x, y, action);
	mouseCallback_puzzle_game(object, x, y, action);
	mouseCallback_escaping_game(object, x, y, action);
	// 처음 시작장면 - 설명에서의 mouseCallback
	if (object == mario_party_next) {
		enterScene(game_board);
		player1 = true;
		in_game_board = true;
	}
	//게임 보드 위에서의 클릭
	if (in_game_board == true) {
		if (object == run_dice) {
			enterScene(dice_roll_place);
			showObject(run_dice_in);
			showObject(dice_num);
			dice_on = true;
			in_game_board = false;
		}
	}
	//dice_roll_place에서의 클릭
	else if (dice_on == true) {
		if (object == run_dice_in) {
			startTimer(rolling_time);
			startTimer(rolling_dice_timer);
			hideObject(run_dice_in);
		}
	}
	if (final_cal == true) {
		if (object == Game_end) {
			endGame();
		}
	}
}

//플레이어를 움직이는 타이머
void timerCallback_mario_party_player_moving(TimerID timer) {
	if (in_game_board == true) {
		if (timer == moving_timer_1) {
			if (player1 == true) locateObject(player1_object, game_board, 110, 150);
			else if (player2 == true) locateObject(player2_object, game_board, 150, 170);
			else if (player3 == true) locateObject(player3_object, game_board, 135, 110);
			setTimer(moving_timer_1, 1.f);
		}
		else if (timer == moving_timer_2) {
			if (player1 == true) locateObject(player1_object, game_board, 420, 170);
			else if (player2 == true) locateObject(player2_object, game_board, 420, 170);
			else if (player3 == true) locateObject(player3_object, game_board, 420, 170);
			setTimer(moving_timer_2, 1.f);
		}
		else if (timer == moving_timer_3) {
			if (player1 == true) locateObject(player1_object, game_board, 730, 170);
			else if (player2 == true) locateObject(player2_object, game_board, 730, 170);
			else if (player3 == true) locateObject(player3_object, game_board, 730, 170);
			setTimer(moving_timer_3, 1.f);
		}
		else if (timer == moving_timer_4) {
			if (player1 == true) locateObject(player1_object, game_board, 1060, 170);
			else if (player2 == true) locateObject(player2_object, game_board, 1060, 170);
			else if (player3 == true) locateObject(player3_object, game_board, 1060, 170);
			setTimer(moving_timer_4, 1.f);
		}
		else if (timer == moving_timer_5) {
			if (player1 == true) locateObject(player1_object, game_board, 1060, 350);
			else if (player2 == true) locateObject(player2_object, game_board, 1060, 350);
			else if (player3 == true) locateObject(player3_object, game_board, 1060, 350);
			setTimer(moving_timer_5, 1.f);
		}
		else if (timer == moving_timer_6) {
			if (player1 == true) locateObject(player1_object, game_board, 730, 350);
			else if (player2 == true) locateObject(player2_object, game_board, 730, 350);
			else if (player3 == true) locateObject(player3_object, game_board, 730, 350);
			setTimer(moving_timer_6, 1.f);
		}
		else if (timer == moving_timer_7) {
			if (player1 == true) locateObject(player1_object, game_board, 420, 350);
			else if (player2 == true) locateObject(player2_object, game_board, 420, 350);
			else if (player3 == true) locateObject(player3_object, game_board, 420, 350);
			setTimer(moving_timer_7, 1.f);
		}
		else if (timer == moving_timer_8) {
			if (player1 == true) locateObject(player1_object, game_board, 110, 370);
			else if (player2 == true) locateObject(player2_object, game_board, 150, 370);
			else if (player3 == true) locateObject(player3_object, game_board, 135, 320);
			setTimer(moving_timer_8, 1.f);
		}
		else if (timer == moving_timer_9) {
			if (player1 == true) locateObject(player1_object, game_board, 110, 595);
			else if (player2 == true) locateObject(player2_object, game_board, 150, 595);
			else if (player3 == true) locateObject(player3_object, game_board, 135, 540);
			setTimer(moving_timer_9, 1.f);
		}
		else if (timer == moving_timer_10) {
			if (player1 == true) locateObject(player1_object, game_board, 420, 570);
			else if (player2 == true) locateObject(player2_object, game_board, 420, 570);
			else if (player3 == true) locateObject(player3_object, game_board, 420, 570);
			setTimer(moving_timer_10, 1.f);
		}
		else if (timer == moving_timer_11) {
			if (player1 == true) locateObject(player1_object, game_board, 730, 570);
			else if (player2 == true) locateObject(player2_object, game_board, 730, 570);
			else if (player3 == true) locateObject(player3_object, game_board, 730, 570);
			setTimer(moving_timer_11, 1.f);
		}
		else if (timer == moving_timer_12) {
			if (player1 == true) locateObject(player1_object, game_board, 1060, 570);
			else if (player2 == true) locateObject(player2_object, game_board, 1060, 570);
			else if (player3 == true) locateObject(player3_object, game_board, 1060, 570);
			setTimer(moving_timer_12, 1.f);
		}
	}
}
// 플레이어가 움직임이 끝나고 미니게임에 들어가게 해주는 타이머
void timerCallback_mario_party_enter_Scene(TimerID timer) {
	if (in_game_board == true) {
		if (timer == enter_1_1) {
			enterScene(pmdescription);
			setTimer(enter_1_1, 2.f);
			in_game_board = false;
			stage_1_1 = true;
		}
		else if (timer == enter_1_2 && stage_1_2_finish == false) {
			enterScene(scene_running_explain);
			setTimer(enter_1_2, 2.f);
			in_game_board = false;
			stage_1_2 = true;
		}
		else if (timer == enter_1_2 && stage_1_2_finish == true) {
			setTimer(enter_1_2, 2.f);
			showObject(run_dice);
			change_player();
		}
		else if (timer == enter_1_3) {
			enterScene(card_draw_place);
			draw_card();
			setTimer(enter_1_3, 2.f);
			in_game_board = false;
			card_on = true;
		}
		else if (timer == enter_1_4 && stage_1_4_finish == false) {
			enterScene(puzzle_game_scene1);
			setTimer(enter_1_4, 2.f);
			in_game_board = false;
			stage_1_4 = true;
		}
		else if (timer == enter_1_4 && stage_1_4_finish == true) {
			setTimer(enter_1_4, 2.f);
			showObject(run_dice);
			change_player();
		}
		else if (timer == enter_2_1) {
			enterScene(card_match_card_description);
			setTimer(enter_2_1, 2.f);
			in_game_board = false;
			stage_2_1 = true;
		}
		else if (timer == enter_2_2 && stage_2_2_finish == false) {
			enterScene(scene_escape_explain);
			setTimer(enter_2_2, 2.f);
			in_game_board = false;
			stage_2_2 = true;
		}
		else if (timer == enter_2_2 && stage_2_2_finish == true) {
			setTimer(enter_2_2, 2.f);
			showObject(run_dice);
			change_player();
		}
		else if (timer == enter_2_3) {
			enterScene(card_draw_place);
			setTimer(enter_2_3, 2.f);
			draw_card();
			in_game_board = false;
			card_on = true;
		}
		else if (timer == enter_2_4 && stage_2_4_finish == false) {
			enterScene(slot_game_slot_description);
			setTimer(enter_2_4, 2.f);
			in_game_board = false;
			stage_2_4 = true;
		}
		else if (timer == enter_2_4 && stage_2_4_finish == true) {
			setTimer(enter_2_4, 2.f);
			showObject(run_dice);
			change_player();
		}
		else if (timer == enter_3_1 && stage_3_1_finish == false) {
			enterScene(maze_game_scene1);
			setTimer(enter_3_1, 2.f);
			in_game_board = false;
			stage_3_1 = true;
		}
		else if (timer == enter_3_1 && stage_3_1_finish == true) {
			setTimer(enter_3_1, 2.f);
			showObject(run_dice);
			change_player();
		}
		else if (timer == enter_3_2 && stage_3_2_finish == false) {
			enterScene(find_game_scene1);
			setTimer(enter_3_2, 2.f);
			in_game_board = false;
			stage_3_2 = true;
		}
		else if (timer == enter_3_2 && stage_3_2_finish == true) {
			setTimer(enter_3_2, 2.f);
			showObject(run_dice);
			change_player();
		}
		else if (timer == enter_3_3) {
			enterScene(card_draw_place);
			setTimer(enter_3_3, 2.f);
			draw_card();
			in_game_board = false;
			card_on = true;
		}
		else if (timer == enter_3_4 && stage_3_4_finish == false) {
			enterScene(area_game_scene1);
			setTimer(enter_3_4, 2.f);
			in_game_board = false;
			stage_3_4 = true;
		}
		else if (timer == enter_3_4 && stage_3_4_finish == true) {
			setTimer(enter_3_4, 2.f);
			showObject(run_dice);
			change_player();
		}
	}
}

//mousecallback과 마찬가지로 각각 게임마다 timercallback을 만들어주시는것을 권유합니다.
void timerCallback_mario_party(TimerID timer) {
	timerCallback_card_match(timer);
	timerCallback_pm_game(timer);
	timerCallback_slot_game(timer);
	timerCallback_area_game(timer);
	timerCallback_find_game(timer);
	timerCallback_maze_game(timer);
	timerCallback_running_game(timer);
	timerCallback_puzzle_game(timer);
	timerCallback_escaping_game(timer);
	//dice_roll_place에서의 타이머
	if (dice_on == true) {
		if (timer == rolling_time) {
			stopTimer(rolling_dice_timer);
			setTimer(rolling_time, 5.f);
			startTimer(rolling_dice_escape_timer);
		}
		else if (timer == rolling_dice_timer) {
			create_dice_number();
			startTimer(rolling_dice_timer);
		}
		else if (timer == rolling_dice_escape_timer) {
			dice_on = false;
			in_game_board = true;
			setTimer(rolling_dice_escape_timer, 1.f);
			hideObject(dice_num);
			hideObject(run_dice); //각 스테이지가 끝나고 showObject 필수
			enterScene(game_board);
			move_player(random_result);
			player_move_in_board();
		}
	}
	//카드 뽑는 스테이지에서의 타이머
	else if (card_on == true) {
		if (timer == drawing_card_escape_timer) {
			card_on = false;
			in_game_board = true;
			enterScene(game_board);
			setTimer(drawing_card_escape_timer, 3.f);
			change_player();
			showObject(run_dice);
			check_player_score();
		}
	}
	//플레이어 움직이는 타이머
	timerCallback_mario_party_player_moving(timer);
	timerCallback_mario_party_enter_Scene(timer);
}

void keyboardCallback_mario_party(KeyCode code, KeyState state) {
	keyboardCallback_area_game(code, state);
	keyboardCallback_find_game(code, state);
	keyboardCallback_maze_game(code, state);
	keyboardCallback_running_game(code, state);
	keyboardCallback_escaping_game(code, state);
}

int main() {

	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setMouseCallback(mouseCallback_mario_party);
	setTimerCallback(timerCallback_mario_party);
	setKeyboardCallback(keyboardCallback_mario_party);
	srand(time(NULL));
	//마리오 게임 큰 틀
	mario_game_description = createScene("게임 설명", "Images/mario_description.png");
	game_board = createScene("게임판", "Images/game_board.png");
	card_draw_place = createScene("카드 뽑기", "Images/draw_card_board.png");
	dice_roll_place = createScene("주사위 굴리기", "Images/dice_board.png");
	mario_party_final_cal = createScene("게임 정산", "Images/final_cal.png");

	mario_party_sound1 = createSound("sounds/Paper Mario Medley.mp3");
	playSound(mario_party_sound1, 1);

	Game_end = createObject("Images/end.png");
	locateObject(Game_end, mario_party_final_cal, 540, 30);
	showObject(Game_end);

	//설명 때의 물체
	mario_party_next = createObject("Images/Next.png");
	locateObject(mario_party_next, mario_game_description, 540, 80);
	showObject(mario_party_next);

	//게임판에서의 물체
	run_dice = createObject("Images/Run_dice.png");
	locateObject(run_dice, game_board, 1000, 10);
	showObject(run_dice);

	player1_object = createObject("Images/player1.png");
	locateObject(player1_object, game_board, 105, 20);
	showObject(player1_object);
	player2_object = createObject("Images/player2.png");
	locateObject(player2_object, game_board, 115, 20);
	showObject(player2_object);
	player3_object = createObject("Images/player3.png");
	locateObject(player3_object, game_board, 125, 20);
	showObject(player3_object);

	moving_timer_1 = createTimer(1.f); moving_timer_2 = createTimer(1.f);
	moving_timer_3 = createTimer(1.f); moving_timer_4 = createTimer(1.f);
	moving_timer_5 = createTimer(1.f); moving_timer_6 = createTimer(1.f);
	moving_timer_7 = createTimer(1.f); moving_timer_8 = createTimer(1.f);
	moving_timer_9 = createTimer(1.f); moving_timer_10 = createTimer(1.f);
	moving_timer_11 = createTimer(1.f); moving_timer_12 = createTimer(1.f);

	enter_1_1 = createTimer(2.f); enter_2_1 = createTimer(2.f); enter_3_1 = createTimer(2.f);
	enter_1_2 = createTimer(2.f); enter_2_2 = createTimer(2.f); enter_3_2 = createTimer(2.f);
	enter_1_3 = createTimer(2.f); enter_2_3 = createTimer(2.f); enter_3_3 = createTimer(2.f);
	enter_1_4 = createTimer(2.f); enter_2_4 = createTimer(2.f); enter_3_4 = createTimer(2.f);

	//dice_roll_place에서의 타이머 / 물체

	run_dice_in = createObject("Images/Run_dice.png");
	locateObject(run_dice_in, dice_roll_place, 540, 30);
	showObject(run_dice_in);

	dice_num = createObject("Images/roll_dice1.png");
	locateObject(dice_num, dice_roll_place, 540, 260);


	rolling_time = createTimer(5.f);
	rolling_dice_timer = createTimer(0.1f);
	rolling_dice_escape_timer = createTimer(1.f);

	//card_draw_place에서의 타이머

	drawing_card_escape_timer = createTimer(3.f);

	//1-1스테이지에 사용하는 이미지들
	pmdescription = createScene("설명", "pm_game_Images/game_background.png");

	pm_1 = createScene("백색 배경", "pm_game_Images/white.png");
	pm_2 = createScene("백색 배경", "pm_game_Images/white.png");
	pm_3 = createScene("백색 배경", "pm_game_Images/white.png");

	pm_game_final_cal = createScene("마지막 점수 보기", "pm_game_Images/final.png");

	pm_game_Next1 = createObject("pm_game_Images/Next.png");
	locateObject(pm_game_Next1, pmdescription, 825, 220);
	showObject(pm_game_Next1);

	pm_timer1 = createTimer(5.f);
	pm_enter_2 = createTimer(1.f);
	pm_timer2 = createTimer(5.f);
	pm_enter_3 = createTimer(1.f);
	pm_timer3 = createTimer(5.f);
	pm_enter_final = createTimer(1.f);
	pm_enter_game_board_timer = createTimer(5.f);
	// 여기까지 1-1 스테이지에 나오는 이미지 및 타이머 

	//여기부터 1-2 스테이지에 나오는 이미지 및 타이머
	scene_running_explain = createScene("게임설명", "running_game_Images/런닝겜설명.png");
	scene_running_playground = createScene("scene1", "running_game_Images/육상경기장.png");
	scene_running_end = createScene("겜끝", "running_game_Images/일다시이.png");
	//런 캐릭터//
	pitch1_running = createObject("running_game_Images/pitch1.png");
	locateObject(pitch1_running, scene_running_playground, pitch1X, pitch1Y);
	showObject(pitch1_running);
	mario1_running = createObject("running_game_Images/mario1.png");
	locateObject(mario1_running, scene_running_playground, mario1X, mario1Y);
	showObject(mario1_running);
	mush1_running = createObject("running_game_Images/mush1.png");
	locateObject(mush1_running, scene_running_playground, mush1X, mush1Y);
	showObject(mush1_running);
	startbutton_running = createObject("running_game_Images/startbutton.png");
	locateObject(startbutton_running, scene_running_explain, 600, 0);
	showObject(startbutton_running);
	running_game_escape_timer = createTimer(3.f);
	//여기까지 1-2스테이지에 나오는 이미지 및 타이머
	
	//여기부터 1-4 스테이지에 나오는 이미지 및 타이머
	puzzle_game_scene1 = createScene("퍼즐 맞추기", "puzzle_game_Images/B.png");
	puzzle_game_next = createObject("puzzle_game_Images/next.png");
	locateObject(puzzle_game_next, puzzle_game_scene1, 500, 50);
	scaleObject(puzzle_game_next, 0.15f);
	showObject(puzzle_game_next);
	puzzle_game_setS();
	puzzle_game_escape_timer = createTimer(3.f);
	//여기까지 1-4스테이지에 나오는 이미지 및 타이머

	//2-1 스테이지의 카드맞추기 함수에 사용되는 이미지들
	card_match_card_description = createScene("카드 설명", "card_match_Images/설명.png");
	card_match_card_game = createScene("카드 게임", "card_match_Images/background.png");
	card_match_card_final_cal = createScene("카드 게임 끝", "card_match_Images/white.png");

	card_match_Next = createObject("card_match_Images/Next.png");
	locateObject(card_match_Next, card_match_card_description, 1060, 500);
	showObject(card_match_Next);

	card_match_go = createObject("card_match_Images/go.png");
	locateObject(card_match_go, card_match_card_game, 600, 10);


	card_match_go_timer = createTimer(10.f);
	card_match_move_timer = createTimer(0.1f);
	card_match_reverse_timer = createTimer(1.f);
	card_match_show_timer = createTimer(1.f);
	card_match_escape_timer = createTimer(3.f);
	// 여기까지 카드맞추기 사용하는 이미지와 타이머

	// 여기부터 2-2 스테이지에 사용하는 이미지와 타이머

	scene_escape_playground = createScene("scene1", "escaping_game_Images/배경1.png");
	scene_escape_explain = createScene("피하기겜설명", "escaping_game_Images/피하기겜설명.png");
	scene_escape_end = createScene("피하기겜끝", "escaping_game_Images/이다시이.png");

	player1_escape = createObject("escaping_game_Images/player1.png");
	locateObject(player1_escape, scene_escape_playground, 600, 0);
	showObject(player1_escape);
	player2_escape = createObject("escaping_game_Images/player2.png");
	locateObject(player2_escape, scene_escape_playground, 300, 0);
	showObject(player2_escape);
	player3_escape = createObject("escaping_game_Images/player3.png");
	locateObject(player3_escape, scene_escape_playground, 900, 0);
	showObject(player3_escape);

	startbutton_escape = createObject("escaping_game_Images/startbutton_escape.png");
	locateObject(startbutton_escape, scene_escape_explain, 600, 0);
	showObject(startbutton_escape);

	timer1_escape = createTimer(0.01f);
	timer2_escape = createTimer(0.01f);
	timer3_escape = createTimer(0.01f);

	escaping_game_escape_timer = createTimer(3.f);

	//여기까지 2-2 스테이지에 사용하는 이미지와 타이머

	//2-4 슬롯머신에 사용하는 이미지와 타이머
	slot_game_slot_description = createScene("설명", "slot_game_Images/설명.png");

	slot_game_board = createScene("게임판", "slot_game_Images/background.png");

	slot_game_final_cal = createScene("마지막 점수 보기", "slot_game_Images/white.png");

	slot_game_Next = createObject("slot_game_Images/Next.png");
	locateObject(slot_game_Next, slot_game_slot_description, 280, 20);
	showObject(slot_game_Next);

	slot_game_slot_lever = createObject("slot_game_Images/slot_lever.png");
	locateObject(slot_game_slot_lever, slot_game_board, 1045, 300);
	showObject(slot_game_slot_lever);

	slot_game_player = createObject("slot_game_Images/player1.png");
	locateObject(slot_game_player, slot_game_board, 545, 490);

	slot_game_slot_picture[0] = createObject("slot_game_Images/slot_picture4.png");
	slot_game_slot_picture[1] = createObject("slot_game_Images/slot_picture4.png");
	slot_game_slot_picture[2] = createObject("slot_game_Images/slot_picture4.png");

	locateObject(slot_game_slot_picture[0], slot_game_board, 284, 249);
	locateObject(slot_game_slot_picture[1], slot_game_board, 536, 249);
	locateObject(slot_game_slot_picture[2], slot_game_board, 786, 249);

	showObject(slot_game_slot_picture[0]);
	showObject(slot_game_slot_picture[1]);
	showObject(slot_game_slot_picture[2]);

	slotgame_timer = createTimer(180.f);
	slot_game_slot_timer = createTimer(0.1f);
	slot_game_player1_timer = createTimer(4.f);
	slot_game_player2_timer = createTimer(4.f);
	slot_game_player3_timer = createTimer(4.f);
	slot_game_enter_cal_scene = createTimer(2.f);
	slot_game_escape_timer = createTimer(3.f);

	//여기까지 2-4 이미지와 타이머

	//여기부터 3-1 이미지와 타이머
	maze_game_scene1 = createScene("Maze", "maze_game_Images/B.png");

	maze_game_next = createObject("maze_game_Images/next.png");

	scaleObject(maze_game_next, 0.1f);
	locateObject(maze_game_next, maze_game_scene1, 1100, 20);
	showObject(maze_game_next);
	
	maze_game_timer1 = createTimer(0.01f);
	maze_game_escape_timer = createTimer(3.f);
	//여기까지 3-1 이미지와 타이머

	//여기부터 3-2 이미지와 타이머
	find_game_scene1 = createScene("Find Game", "find_game_Images/B.png");
	find_game_next = createObject("find_game_Images/next.png");

	scaleObject(find_game_next, 0.15f);
	locateObject(find_game_next, find_game_scene1, 1100, 20);
	showObject(find_game_next);

	find_game_escape_timer = createTimer(3.f);
	//여기까지 3-2 이미지와 타이머

	//여기부터 3-4 스테이지 이미지와 타이머
	area_game_scene1 = createScene("Area Battle", "area_battle_Images/B.png");
	area_game_next = createObject("area_battle_Images/next.png");
	scaleObject(area_game_next, 0.15f);
	locateObject(area_game_next, area_game_scene1, 1100, 20);
	showObject(area_game_next);
	area_game_escape_timer = createTimer(3.f);
	//여기까지 3-4 스테이지 이미지와 타이머


	//게임 시작
	startGame(mario_game_description);
}

//1-1 스테이지 +,- 게임에 사용되는 함수 동작 기능
//+, - 생성
void pm_game_create_pm() {

	char temp[100] = { 0 };

	for (int i = 0; i < 3; i++) {
		pm_game_random_pm[i] = rand() % 2;
		sprintf(temp, "pm_game_Images/ffao%d.png", pm_game_random_pm[i]);
		if (pm_player1 == true) {
			pm_game_pm[i] = createObject(temp);
			locateObject(pm_game_pm[i], pm_1, 300 + 300 * i, 100);
			showObject(pm_game_pm[i]);
		}
		else if (pm_player2 == true) {
			pm_game_pm[i] = createObject(temp);
			locateObject(pm_game_pm[i], pm_2, 300 + 300 * i, 100);
			showObject(pm_game_pm[i]);
		}
		else if (pm_player3 == true) {
			pm_game_pm[i] = createObject(temp);
			locateObject(pm_game_pm[i], pm_3, 300 + 300 * i, 100);
			showObject(pm_game_pm[i]);
		}
	}
}

void pm_game_create_number() {
	// 숫자 이미지 생성
	int random1;
	int random2;

	char s1[100];
	char s2[100];

	for (int i = 0; i < 4; i++) {
		random1 = rand() % 10;
		random2 = rand() % 10;

		sprintf(s1, "pm_game_Images/%d.png", random1);
		sprintf(s2, "pm_game_Images/%d.png", random2);

		if (pm_player1 == true) {
			pm_game_number1[i] = createObject(s1);
			locateObject(pm_game_number1[i], pm_1, 150 + 300 * i, 300);
			showObject(pm_game_number1[i]);

			pm_game_number2[i] = createObject(s2);
			locateObject(pm_game_number2[i], pm_1, 200 + 300 * i, 300);
			showObject(pm_game_number2[i]);
		}
		else if (pm_player2 == true) {
			pm_game_number1[i] = createObject(s1);
			locateObject(pm_game_number1[i], pm_2, 150 + 300 * i, 300);
			showObject(pm_game_number1[i]);

			pm_game_number2[i] = createObject(s2);
			locateObject(pm_game_number2[i], pm_2, 200 + 300 * i, 300);
			showObject(pm_game_number2[i]);
		}
		else if (pm_player3 == true) {
			pm_game_number1[i] = createObject(s1);
			locateObject(pm_game_number1[i], pm_3, 150 + 300 * i, 300);
			showObject(pm_game_number1[i]);

			pm_game_number2[i] = createObject(s2);
			locateObject(pm_game_number2[i], pm_3, 200 + 300 * i, 300);
			showObject(pm_game_number2[i]);
		}
		pm_game_random_num[i] = 10 * random1 + random2;
	}
}

void pm_game_create_little_white() {

	char buff[100];
	sprintf(buff, "pm_game_Images/little_white.png");
	if (pm_player1 == true) {
		for (int i = 0; i < 3; i++) {
			pm_game_little_white[i] = createObject(buff);
			locateObject(pm_game_little_white[i], pm_1, 300 + 300 * i, 300);
			showObject(pm_game_little_white[i]);
		}
	}
	else if (pm_player2 == true) {
		for (int i = 0; i < 3; i++) {
			pm_game_little_white[i] = createObject(buff);
			locateObject(pm_game_little_white[i], pm_2, 300 + 300 * i, 300);
			showObject(pm_game_little_white[i]);
		}
	}
	else if (pm_player3 == true) {
		for (int i = 0; i < 3; i++) {
			pm_game_little_white[i] = createObject(buff);
			locateObject(pm_game_little_white[i], pm_3, 300 + 300 * i, 300);
			showObject(pm_game_little_white[i]);
		}
	}
}

void pm_game_create() {
	pm_game_create_number();
	pm_game_create_pm();
}

void pm_game_simul() {
	pm_game_create_little_white();
	hideTimer();
	enterScene(pm_2);
	stopTimer(pm_timer1);
	setTimer(pm_timer1, 5.f);
	showTimer(pm_timer2);
	startTimer(pm_timer2);
	pm_player2 = true;
	pm_player1 = false;
	pm_game_choice2 = true;
}

void pm_game_simul_2() {
	pm_game_create_little_white();
	hideTimer();
	enterScene(pm_3);
	stopTimer(pm_timer2);
	setTimer(pm_timer2, 5.f);
	showTimer(pm_timer3);
	startTimer(pm_timer3);
	pm_player2 = false;
	pm_player3 = true;
	pm_game_choice3 = true;
}

void pm_game_simul_3() {
	char buff_1[300] = { 0 };
	char buff_2[300] = { 0 };
	char buff_3[300] = { 0 };
	char buff[100] = { 0 };
	pm_game_create_little_white();
	hideTimer();
	stopTimer(pm_timer3);
	setTimer(pm_timer3, 5.f);
	enterScene(pm_game_final_cal);
	startTimer(pm_enter_game_board_timer);
	pm_player3 = false;
	int score[3] = { 0 };
	if (pm_game_cal[0] > pm_game_cal[1] && pm_game_cal[0] > pm_game_cal[2]) {
		if (pm_game_cal[1] > pm_game_cal[2]) {
			mario_party_player1_score += 3;
			mario_party_player2_score += 2;
			mario_party_player3_score += 1;
			score[0] = 3;
			score[1] = 2;
			score[2] = 1;
		}
		else if (pm_game_cal[1] < pm_game_cal[2]) {
			mario_party_player1_score += 3;
			mario_party_player2_score += 1;
			mario_party_player3_score += 2;
			score[0] = 3;
			score[1] = 1;
			score[2] = 2;
		}
	}
	else if (pm_game_cal[1] > pm_game_cal[0] && pm_game_cal[1] > pm_game_cal[2]) {
		if (pm_game_cal[0] > pm_game_cal[2]) {
			mario_party_player1_score += 2;
			mario_party_player2_score += 3;
			mario_party_player3_score += 1;
			score[0] = 2;
			score[1] = 3;
			score[2] = 1;
		}
		else if (pm_game_cal[0] < pm_game_cal[2]) {
			mario_party_player1_score += 1;
			mario_party_player2_score += 3;
			mario_party_player3_score += 2;
			score[0] = 1;
			score[1] = 3;
			score[2] = 2;
		}
	}
	else if (pm_game_cal[2] > pm_game_cal[0] && pm_game_cal[2] > pm_game_cal[1]) {
		if (pm_game_cal[0] > pm_game_cal[1]) {
			mario_party_player1_score += 2;
			mario_party_player2_score += 1;
			mario_party_player3_score += 3;
			score[0] = 2;
			score[1] = 1;
			score[2] = 3;
		}
		else if (pm_game_cal[0] < pm_game_cal[1]) {
			mario_party_player1_score += 1;
			mario_party_player2_score += 2;
			mario_party_player3_score += 3;
			score[0] = 1;
			score[1] = 2;
			score[2] = 3;
		}
	}
	else if (pm_game_cal[0] == pm_game_cal[1] && pm_game_cal[0] > pm_game_cal[2]) {
		mario_party_player1_score += 3;
		mario_party_player2_score += 3;
		mario_party_player3_score += 1;
		score[0] = 3;
		score[1] = 3;
		score[2] = 1;
	}
	else if (pm_game_cal[0] == pm_game_cal[2] && pm_game_cal[0] > pm_game_cal[1]) {
		mario_party_player1_score += 3;
		mario_party_player2_score += 1;
		mario_party_player3_score += 3;
		score[0] = 3;
		score[1] = 1;
		score[2] = 3;
	}
	else if (pm_game_cal[2] == pm_game_cal[1] && pm_game_cal[2] > pm_game_cal[0]) {
		mario_party_player1_score += 1;
		mario_party_player2_score += 3;
		mario_party_player3_score += 3;
		score[0] = 1;
		score[1] = 3;
		score[2] = 3;
	}
	else if (pm_game_cal[0] == pm_game_cal[1] && pm_game_cal[1] == pm_game_cal[2]) {
		mario_party_player1_score += 3;
		mario_party_player2_score += 3;
		mario_party_player3_score += 3;
		score[0] = 3;
		score[1] = 3;
		score[2] = 3;
	}
	sprintf(buff_1, "player%d의 결과값: %d  전체게임 점수 + %d\n", 1, pm_game_cal[0], score[0]);
	sprintf(buff_2, "player%d의 결과값: %d  전체게임 점수 + %d\n", 2, pm_game_cal[1], score[1]);
	sprintf(buff_3, "player%d의 결과값: %d  전체게임 점수 + %d", 3, pm_game_cal[2], score[2]);
	strcat(buff_1, buff_2);
	strcat(buff_1, buff_3);
	showMessage(buff_1);
	for (int i = 0; i < 3; i++) {
		pm_game_cal[i] = 0;
	}
}

int pm_game_calculation(int* pm, int* num) {
	int cal = num[0];
	for (int i = 0; i < 3; i++) {
		if (pm[i] == 0) cal += num[i + 1];
		else if (pm[i] == 1) cal -= num[i + 1];
	}
	return cal;
}

void mouseCallback_pm_game(ObjectID object, int x, int y, MouseAction action) {
	if (stage_1_1 == true) {
		int temp = 0;
		if (object == pm_game_Next1) {
			enterScene(pm_1);
			showTimer(pm_timer1);
			startTimer(pm_timer1);
			pm_player1 = true;
			pm_game_choice1 = true;
			pm_game_create();
		}
		// +, - 가 모두 배치되면 계산된 것은 저장하고 넘어감
		if (pm_player1 == true) {
			if (pm_game_choice1 == true) {
				if (object == pm_game_pm[0]) {
					locateObject(pm_game_pm[0], pm_1, 300, 300);
					pm_game_choice1 = false;
					pm_game_choice1_1 = true;
				}
				else if (object == pm_game_pm[1]) {
					locateObject(pm_game_pm[1], pm_1, 300, 300);
					pm_game_choice1 = false;
					pm_game_choice1_2 = true;
				}
				else if (object == pm_game_pm[2]) {
					locateObject(pm_game_pm[2], pm_1, 300, 300);
					pm_game_choice1 = false;
					pm_game_choice1_3 = true;
				}
			}
			if (pm_game_choice1_1 == true) {
				if (object == pm_game_pm[1]) {
					locateObject(pm_game_pm[1], pm_1, 600, 300);
					locateObject(pm_game_pm[2], pm_1, 900, 300);
					pm_game_cal[0] = pm_game_calculation(pm_game_random_pm, pm_game_random_num);
					startTimer(pm_enter_2);
					pm_game_choice1_1 = false;
				}
				else if (object == pm_game_pm[2]) {
					locateObject(pm_game_pm[2], pm_1, 600, 300);
					locateObject(pm_game_pm[1], pm_1, 900, 300);
					Swap(pm_game_random_pm[1], pm_game_random_pm[2]);
					pm_game_cal[0] = pm_game_calculation(pm_game_random_pm, pm_game_random_num);
					startTimer(pm_enter_2);
					pm_game_choice1_1 = false;
				}
			}
			else if (pm_game_choice1_2 == true) {
				if (object == pm_game_pm[0]) {
					locateObject(pm_game_pm[0], pm_1, 600, 300);
					locateObject(pm_game_pm[2], pm_1, 900, 300);
					Swap(pm_game_random_pm[0], pm_game_random_pm[1]);
					pm_game_cal[0] = pm_game_calculation(pm_game_random_pm, pm_game_random_num);
					startTimer(pm_enter_2);
					pm_game_choice1_2 = false;
				}
				else if (object == pm_game_pm[2]) {
					locateObject(pm_game_pm[2], pm_1, 600, 300);
					locateObject(pm_game_pm[0], pm_1, 900, 300);
					Swap(pm_game_random_pm[0], pm_game_random_pm[1]);
					Swap(pm_game_random_pm[1], pm_game_random_pm[2]);
					pm_game_cal[0] = pm_game_calculation(pm_game_random_pm, pm_game_random_num);
					startTimer(pm_enter_2);
					pm_game_choice1_2 = false;
				}
			}
			else if (pm_game_choice1_3 == true) {
				if (object == pm_game_pm[0]) {
					locateObject(pm_game_pm[0], pm_1, 600, 300);
					locateObject(pm_game_pm[1], pm_1, 900, 300);
					Swap(pm_game_random_pm[1], pm_game_random_pm[2]);
					Swap(pm_game_random_pm[0], pm_game_random_pm[2]);
					pm_game_cal[0] = pm_game_calculation(pm_game_random_pm, pm_game_random_num);
					startTimer(pm_enter_2);
					pm_game_choice1_3 = false;
				}
				else if (object == pm_game_pm[1]) {
					locateObject(pm_game_pm[1], pm_1, 600, 300);
					locateObject(pm_game_pm[0], pm_1, 900, 300);
					Swap(pm_game_random_pm[1], pm_game_random_pm[2]);
					Swap(pm_game_random_pm[0], pm_game_random_pm[1]);
					Swap(pm_game_random_pm[1], pm_game_random_pm[2]);
					pm_game_cal[0] = pm_game_calculation(pm_game_random_pm, pm_game_random_num);
					startTimer(pm_enter_2);
					pm_game_choice1_3 = false;
				}
			}
		}
		else if (pm_player2 == true) {
			if (pm_game_choice2 == true) {
				if (object == pm_game_pm[0]) {
					locateObject(pm_game_pm[0], pm_2, 300, 300);
					pm_game_choice2 = false;
					pm_game_choice2_1 = true;
				}
				else if (object == pm_game_pm[1]) {
					locateObject(pm_game_pm[1], pm_2, 300, 300);
					pm_game_choice2 = false;
					pm_game_choice2_2 = true;
				}
				else if (object == pm_game_pm[2]) {
					locateObject(pm_game_pm[2], pm_2, 300, 300);
					pm_game_choice2 = false;
					pm_game_choice2_3 = true;
				}
			}
			if (pm_game_choice2_1 == true) {
				if (object == pm_game_pm[1]) {
					locateObject(pm_game_pm[1], pm_2, 600, 300);
					locateObject(pm_game_pm[2], pm_2, 900, 300);
					pm_game_cal[1] = pm_game_calculation(pm_game_random_pm, pm_game_random_num);
					startTimer(pm_enter_3);
					pm_game_choice2_1 = false;
				}
				else if (object == pm_game_pm[2]) {
					locateObject(pm_game_pm[2], pm_2, 600, 300);
					locateObject(pm_game_pm[1], pm_2, 900, 300);
					Swap(pm_game_random_pm[1], pm_game_random_pm[2]);
					pm_game_cal[1] = pm_game_calculation(pm_game_random_pm, pm_game_random_num);
					startTimer(pm_enter_3);
					pm_game_choice2_1 = false;
				}
			}
			else if (pm_game_choice2_2 == true) {
				if (object == pm_game_pm[0]) {
					locateObject(pm_game_pm[0], pm_2, 600, 300);
					locateObject(pm_game_pm[2], pm_2, 900, 300);
					Swap(pm_game_random_pm[0], pm_game_random_pm[1]);
					pm_game_cal[1] = pm_game_calculation(pm_game_random_pm, pm_game_random_num);
					startTimer(pm_enter_3);
					pm_game_choice2_2 = false;
				}
				else if (object == pm_game_pm[2]) {
					locateObject(pm_game_pm[2], pm_2, 600, 300);
					locateObject(pm_game_pm[0], pm_2, 900, 300);
					Swap(pm_game_random_pm[0], pm_game_random_pm[1]);
					Swap(pm_game_random_pm[1], pm_game_random_pm[2]);
					pm_game_cal[1] = pm_game_calculation(pm_game_random_pm, pm_game_random_num);
					startTimer(pm_enter_3);
					pm_game_choice2_2 = false;
				}
			}
			else if (pm_game_choice2_3 == true) {
				if (object == pm_game_pm[0]) {
					locateObject(pm_game_pm[0], pm_2, 600, 300);
					locateObject(pm_game_pm[1], pm_2, 900, 300);
					Swap(pm_game_random_pm[1], pm_game_random_pm[2]);
					Swap(pm_game_random_pm[0], pm_game_random_pm[2]);
					pm_game_cal[1] = pm_game_calculation(pm_game_random_pm, pm_game_random_num);
					startTimer(pm_enter_3);
					pm_game_choice2_3 = false;
				}
				else if (object == pm_game_pm[1]) {
					locateObject(pm_game_pm[1], pm_2, 600, 300);
					locateObject(pm_game_pm[0], pm_2, 900, 300);
					Swap(pm_game_random_pm[1], pm_game_random_pm[2]);
					Swap(pm_game_random_pm[0], pm_game_random_pm[1]);
					Swap(pm_game_random_pm[1], pm_game_random_pm[2]);
					pm_game_cal[1] = pm_game_calculation(pm_game_random_pm, pm_game_random_num);
					startTimer(pm_enter_3);
					pm_game_choice2_3 = false;
				}
			}
		}
		else if (pm_player3 == true) {
			if (pm_game_choice3 == true) {
				if (object == pm_game_pm[0]) {
					locateObject(pm_game_pm[0], pm_3, 300, 300);
					pm_game_choice3 = false;
					pm_game_choice3_1 = true;
				}
				else if (object == pm_game_pm[1]) {
					locateObject(pm_game_pm[1], pm_3, 300, 300);
					pm_game_choice3 = false;
					pm_game_choice3_2 = true;
				}
				else if (object == pm_game_pm[2]) {
					locateObject(pm_game_pm[2], pm_3, 300, 300);
					pm_game_choice3 = false;
					pm_game_choice3_3 = true;
				}
			}
			if (pm_game_choice3_1 == true) {
				if (object == pm_game_pm[1]) {
					locateObject(pm_game_pm[1], pm_3, 600, 300);
					locateObject(pm_game_pm[2], pm_3, 900, 300);
					pm_game_cal[2] = pm_game_calculation(pm_game_random_pm, pm_game_random_num);
					startTimer(pm_enter_final);
					pm_game_choice3_1 = false;
				}
				else if (object == pm_game_pm[2]) {
					locateObject(pm_game_pm[2], pm_3, 600, 300);
					locateObject(pm_game_pm[1], pm_3, 900, 300);
					Swap(pm_game_random_pm[1], pm_game_random_pm[2]);
					pm_game_cal[2] = pm_game_calculation(pm_game_random_pm, pm_game_random_num);
					startTimer(pm_enter_final);
					pm_game_choice3_1 = false;
				}
			}
			else if (pm_game_choice3_2 == true) {
				if (object == pm_game_pm[0]) {
					locateObject(pm_game_pm[0], pm_3, 600, 300);
					locateObject(pm_game_pm[2], pm_3, 900, 300);
					Swap(pm_game_random_pm[0], pm_game_random_pm[1]);
					pm_game_cal[2] = pm_game_calculation(pm_game_random_pm, pm_game_random_num);
					startTimer(pm_enter_final);
					pm_game_choice3_2 = false;
				}
				else if (object == pm_game_pm[2]) {
					locateObject(pm_game_pm[2], pm_3, 600, 300);
					locateObject(pm_game_pm[0], pm_3, 900, 300);
					Swap(pm_game_random_pm[0], pm_game_random_pm[1]);
					Swap(pm_game_random_pm[1], pm_game_random_pm[2]);
					pm_game_cal[2] = pm_game_calculation(pm_game_random_pm, pm_game_random_num);
					startTimer(pm_enter_final);
					pm_game_choice3_2 = false;
				}
			}
			else if (pm_game_choice3_3 == true) {
				if (object == pm_game_pm[0]) {
					locateObject(pm_game_pm[0], pm_3, 600, 300);
					locateObject(pm_game_pm[1], pm_3, 900, 300);
					Swap(pm_game_random_pm[1], pm_game_random_pm[2]);
					Swap(pm_game_random_pm[0], pm_game_random_pm[2]);
					pm_game_cal[2] = pm_game_calculation(pm_game_random_pm, pm_game_random_num);
					startTimer(pm_enter_final);
					pm_game_choice3_3 = false;
				}
				else if (object == pm_game_pm[1]) {
					locateObject(pm_game_pm[1], pm_3, 600, 300);
					locateObject(pm_game_pm[0], pm_3, 900, 300);
					Swap(pm_game_random_pm[1], pm_game_random_pm[2]);
					Swap(pm_game_random_pm[0], pm_game_random_pm[1]);
					Swap(pm_game_random_pm[1], pm_game_random_pm[2]);
					pm_game_cal[2] = pm_game_calculation(pm_game_random_pm, pm_game_random_num);
					startTimer(pm_enter_final);
					pm_game_choice3_3 = false;
				}
			}
		}
	}
}

void timerCallback_pm_game(TimerID timer) {
	if (stage_1_1 == true) {
		// 5초 이내에 모두 배치 안하면 0으로 계산해버리고 다음으로 넘어감
		if (timer == pm_timer1) {
			pm_game_simul();
			setTimer(pm_timer1, 5.f);
			pm_game_cal[0] = 0;
			for (int i = 0; i < 4; i++) {
				hideObject(pm_game_number1[i]);
				hideObject(pm_game_number2[i]);
			}
			printf("%d", pm_game_cal[0]);
		}
		else if (timer == pm_enter_2) {
			setTimer(pm_enter_2, 1.f);
			pm_game_simul();
			for (int i = 0; i < 4; i++) {
				hideObject(pm_game_number1[i]);
				hideObject(pm_game_number2[i]);
			}
			pm_game_create();
		}
		else if (timer == pm_timer2) {
			pm_game_simul_2();
			setTimer(pm_timer2, 5.f);
			pm_game_cal[1] = 0;
			for (int i = 0; i < 4; i++) {
				hideObject(pm_game_number1[i]);
				hideObject(pm_game_number2[i]);
			}
		}
		else if (timer == pm_enter_3) {
			setTimer(pm_enter_3, 1.f);
			pm_game_simul_2();
			for (int i = 0; i < 4; i++) {
				hideObject(pm_game_number1[i]);
				hideObject(pm_game_number2[i]);
			}
			pm_game_create();
		}
		else if (timer == pm_timer3) {
			pm_game_simul_3();
			pm_game_cal[2] = 0;
			for (int i = 0; i < 4; i++) {
				hideObject(pm_game_number1[i]);
				hideObject(pm_game_number2[i]);
			}
		}
		else if (timer == pm_enter_final) {
			setTimer(pm_enter_final, 1.f);
			pm_game_simul_3();
			for (int i = 0; i < 4; i++) {
				hideObject(pm_game_number1[i]);
				hideObject(pm_game_number2[i]);
			}
		}
		else if (timer == pm_enter_game_board_timer) {
			stage_1_1 = false;
			in_game_board = true;
			enterScene(game_board);
			showObject(run_dice);
			setTimer(pm_enter_game_board_timer, 3.f);
			change_player();
			check_player_score();
		}
	}
}
// 여기까지 1-1 함수 동작 기능

//1-2 스테이지에 사용하는 함수 동작기능
void mouseCallback_running_game(ObjectID object, int x, int y, MouseAction action) {
	if (stage_1_2 == true) {
		if (object == startbutton_running) {
			enterScene(scene_running_playground);
			hideObject(startbutton_running);
		}
	}
}

void keyboardCallback_running_game(KeyCode code, KeyState state)
{
	if (stage_1_2 == true) {
		if (code == KeyCode::KEY_DOWN_ARROW) {      // DOWN
			mario1X = mario1X + 30;
			locateObject(mario1_running, scene_running_playground, mario1X, mario1Y);
			if (mario1X > 1280) {
				mario1X = 0;
				pitch1X = 0;
				mush1X = 0;
				enterScene(scene_running_end);
				showMessage("우승자는 player1! 5점 추가");
				mario_party_player1_score += 5;
				startTimer(running_game_escape_timer);
			}
		}
		else if (code == KeyCode::KEY_RIGHT_ARROW) {      // RIGHT
			pitch1X = pitch1X + 30;
			locateObject(pitch1_running, scene_running_playground, pitch1X, pitch1Y);
			if (pitch1X > 1280) {
				mario1X = 0;
				pitch1X = 0;
				mush1X = 0;
				enterScene(scene_running_end);
				showMessage("우승자는 player2! 5점 추가");
				mario_party_player2_score += 5;
				startTimer(running_game_escape_timer);
			}
		}
		else if (code == KeyCode::KEY_LEFT_ARROW) {      // LEFT
			mush1X = mush1X + 30;
			locateObject(mush1_running, scene_running_playground, mush1X, mush1Y);
			if (mush1X > 1280) {
				mario1X = 0;
				pitch1X = 0;
				mush1X = 0;
				enterScene(scene_running_end);
				showMessage("우승자는 player3! 5점 추가");
				mario_party_player3_score += 5;
				startTimer(running_game_escape_timer);
			}
		}
	}
}

void timerCallback_running_game(TimerID timer) {
	if (timer == running_game_escape_timer) {
		stage_1_2 = false;
		stage_1_2_finish = true;
		in_game_board = true;
		enterScene(game_board);
		showObject(run_dice);
		showObject(startbutton_running);
		setTimer(running_game_escape_timer, 3.f);
		change_player();
		check_player_score();
	}
}
//여기까지 1-2 스테이지 함수 동작 기능

//여기부터 1-4 스테이지 함수 동작 기능
void puzzle_game_setS() {
	puzzle_game_s[1] = createObject("puzzle_game_Images/1.jpg");
	puzzle_game_s[2] = createObject("puzzle_game_Images/2.jpg");
	puzzle_game_s[3] = createObject("puzzle_game_Images/3.jpg");
	puzzle_game_s[4] = createObject("puzzle_game_Images/4.jpg");
	puzzle_game_s[5] = createObject("puzzle_game_Images/5.jpg");
	puzzle_game_s[6] = createObject("puzzle_game_Images/6.jpg");
	puzzle_game_s[7] = createObject("puzzle_game_Images/7.jpg");
	puzzle_game_s[8] = createObject("puzzle_game_Images/8.jpg");
	puzzle_game_s[9] = createObject("puzzle_game_Images/9.png");
}

void puzzle_game_move1(int num1, int x1, int y1, int x2, int y2) {
	puzzle_game_YX[y2][x2] = num1;
	puzzle_game_YX[y1][x1] = 9;
	locateObject(puzzle_game_s[num1], puzzle_game_scene1, puzzle_game_X[x2], puzzle_game_Y[y2]);
	locateObject(puzzle_game_s[9], puzzle_game_scene1, puzzle_game_X[x1], puzzle_game_Y[y1]);
}

void puzzle_game_move2(int x1, int y1, int x2, int y2) {
	puzzle_game_YX[y1][x1] = puzzle_game_YX[y2][x2];
	puzzle_game_YX[y2][x2] = 9;
	locateObject(puzzle_game_s[puzzle_game_YX[y1][x1]], puzzle_game_scene1, puzzle_game_X[x1], puzzle_game_Y[y1]);
	locateObject(puzzle_game_s[9], puzzle_game_scene1, puzzle_game_X[x2], puzzle_game_Y[y2]);
}

void puzzle_game_moveS(int num) {
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			if (puzzle_game_YX[i][j] == num) {
				puzzle_game_cy = i;
				puzzle_game_cx = j;
			}
		}
	}
	if (puzzle_game_YX[puzzle_game_cy - 1][puzzle_game_cx] == 9) {
		puzzle_game_move1(num, puzzle_game_cx, puzzle_game_cy, puzzle_game_cx, puzzle_game_cy - 1);
	}
	else if (puzzle_game_YX[puzzle_game_cy + 1][puzzle_game_cx] == 9) {
		puzzle_game_move1(num, puzzle_game_cx, puzzle_game_cy, puzzle_game_cx, puzzle_game_cy + 1);
	}
	else if (puzzle_game_YX[puzzle_game_cy][puzzle_game_cx + 1] == 9) {
		puzzle_game_move1(num, puzzle_game_cx, puzzle_game_cy, puzzle_game_cx + 1, puzzle_game_cy);
	}
	else if (puzzle_game_YX[puzzle_game_cy][puzzle_game_cx - 1] == 9) {
		puzzle_game_move1(num, puzzle_game_cx, puzzle_game_cy, puzzle_game_cx - 1, puzzle_game_cy);
	}
}

void puzzle_game_arrangeS() {
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			locateObject(puzzle_game_s[puzzle_game_YX[i][j]], puzzle_game_scene1, puzzle_game_X[j], puzzle_game_Y[i]);
			showObject(puzzle_game_s[puzzle_game_YX[i][j]]);
		}
	}
	for (int i = 0; i <= puzzle_game_dif; i++) {
		puzzle_game_r_num = rand() % 4;
		if (puzzle_game_r_num == 0) {
			if (puzzle_game_YX[puzzle_game_y0 - 1][puzzle_game_x0] > 0) {
				puzzle_game_move2(puzzle_game_x0, puzzle_game_y0, puzzle_game_x0, puzzle_game_y0 - 1);
				puzzle_game_y0--;
			}
			else {
				i--;
			}
		}
		else if (puzzle_game_r_num == 1) {
			if (puzzle_game_YX[puzzle_game_y0][puzzle_game_x0 + 1] > 0) {
				puzzle_game_move2(puzzle_game_x0, puzzle_game_y0, puzzle_game_x0 + 1, puzzle_game_y0);
				puzzle_game_x0++;
			}
			else {
				i--;
			}
		}
		else if (puzzle_game_r_num == 2) {
			if (puzzle_game_YX[puzzle_game_y0][puzzle_game_x0 - 1] > 0) {
				puzzle_game_move2(puzzle_game_x0, puzzle_game_y0, puzzle_game_x0 - 1, puzzle_game_y0);
				puzzle_game_x0--;
			}
			else {
				i--;
			}
		}
		else {
			if (puzzle_game_YX[puzzle_game_y0 + 1][puzzle_game_x0] > 0) {
				puzzle_game_move2(puzzle_game_x0, puzzle_game_y0, puzzle_game_x0, puzzle_game_y0 + 1);
				puzzle_game_y0++;
			}
			else {
				i--;
			}
		}
	}
}

void mouseCallback_puzzle_game(ObjectID object, int x, int y, MouseAction action) {
	if (stage_1_4 == true) {
		if (object == puzzle_game_next) {
			for (int i = 1; i <= 3; i++) {
				for (int j = 1; j <= 3; j++) {
					puzzle_game_YX[i][j] = puzzle_game_snum;
					puzzle_game_snum++;
				}
			}
			setSceneImage(puzzle_game_scene1, "puzzle_game_Images/background.png");
			puzzle_game_x0 = 3;
			puzzle_game_y0 = 3;
			puzzle_game_t = 0;
			puzzle_game_timer1 = createTimer(1.0f);
			puzzle_game_timer2 = createTimer(puzzle_game_t);
			showTimer(puzzle_game_timer2);
			startTimer(puzzle_game_timer1);
			hideObject(puzzle_game_next);
			puzzle_game_arrangeS();
		}
		for (int k = 1; k <= 8; k++) {
			if (object == puzzle_game_s[k]) {
				puzzle_game_moveS(k);
			}
		}
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 3; j++) {
				if (puzzle_game_YX[i][j] == puzzle_game_snum) {
					puzzle_game_success++;
				}
				puzzle_game_snum++;
			}
		}
		if (puzzle_game_success >= 9) {
			stopTimer(puzzle_game_timer1);
			showMessage("다음 플레이어 차례");
			showObject(puzzle_game_next);
			for (int i = 1; i <= 9; i++) {
				hideObject(puzzle_game_s[i]);
			}
			if (puzzle_game_pT == 1) puzzle_game_t1 = puzzle_game_t;
			else if (puzzle_game_pT == 2) puzzle_game_t2 = puzzle_game_t;
			else if (puzzle_game_pT == 3) {
				puzzle_game_t3 = puzzle_game_t;
				char text[100];
				sprintf_s(text, 100, "player 1 : %.2f player 2 : %.2f player 3 : %.2f", puzzle_game_t1, puzzle_game_t2, puzzle_game_t3);
				showMessage(text);
				float puzzle_game_score[3] = { puzzle_game_t1, puzzle_game_t2, puzzle_game_t3 };
				int m = puzzle_game_score[0];
				for (int i = 0; i <= 1; i++) if (puzzle_game_score[i] > puzzle_game_score[i + 1]) m = puzzle_game_score[i + 1];
				for (int i = 0; i <= 2; i++) {
					if (puzzle_game_score[i] == m) {
						if (i == 0) {
							if (puzzle_game_score[1] < puzzle_game_score[2]) {
								mario_party_player1_score += 5;
								mario_party_player2_score += 3;
								mario_party_player3_score += 1;
								startTimer(puzzle_game_escape_timer);
							}
							else if (puzzle_game_score[1] > puzzle_game_score[2]) {
								mario_party_player1_score += 5;
								mario_party_player2_score += 1;
								mario_party_player3_score += 3;
								startTimer(puzzle_game_escape_timer);
							}
						}
						else if (i == 1) {
							if (puzzle_game_score[0] < puzzle_game_score[2]) {
								mario_party_player1_score += 3;
								mario_party_player2_score += 5;
								mario_party_player3_score += 1;
								startTimer(puzzle_game_escape_timer);
							}
							else if (puzzle_game_score[0] > puzzle_game_score[2]) {
								mario_party_player1_score += 1;
								mario_party_player2_score += 5;
								mario_party_player3_score += 3;
								startTimer(puzzle_game_escape_timer);
							}
						}
						else if (i == 2) {
							if (puzzle_game_score[0] < puzzle_game_score[1]) {
								mario_party_player1_score += 3;
								mario_party_player2_score += 1;
								mario_party_player3_score += 5;
								startTimer(puzzle_game_escape_timer);
							}
							else if (puzzle_game_score[0] > puzzle_game_score[1]) {
								mario_party_player1_score += 1;
								mario_party_player2_score += 3;
								mario_party_player3_score += 5;
								startTimer(puzzle_game_escape_timer);
							}
						}
					}
				}
				hideObject(puzzle_game_next);
				setSceneImage(puzzle_game_scene1, "puzzle_game_Images/end.png");
				hideTimer();
				startTimer(puzzle_game_escape_timer);
			}
			puzzle_game_pT++;
		}
		puzzle_game_snum = 1;
		puzzle_game_success = 0;
	}
}

void timerCallback_puzzle_game(TimerID timer) {
	if (stage_1_4 == true) {
		if (timer == puzzle_game_timer1) {
			puzzle_game_t++;
			setTimer(puzzle_game_timer1, 1.0f);
			startTimer(puzzle_game_timer1);
			setTimer(puzzle_game_timer2, puzzle_game_t);
		}
		if (timer == puzzle_game_escape_timer) {
			stage_1_4 = false;
			stage_1_4_finish = true;
			in_game_board = true;
			enterScene(game_board);
			showObject(run_dice);
			setTimer(puzzle_game_escape_timer, 3.f);
			change_player();
			check_player_score();
		}
	}
}
//여기까지 1-4 퍼즐맞추기 함수 동작 기능

// 2-1 카드 맞추기에 사용되는 함수 동작 기능
void create_card() {
	char buff[100];
	for (int i = 0; i < 10; i++) {
		sprintf(buff, "card_match_Images/card%d.png", i);
		card[2 * i] = createObject(buff);
		card[2 * i + 1] = createObject(buff);
		locateObject(card[2 * i], card_match_card_game, 136 + 572 * (i % 2), 576 - 144 * (i / 2));
		locateObject(card[2 * i + 1], card_match_card_game, 422 + 572 * (i % 2), 576 - 144 * (i / 2));
		showObject(card[2 * i]);
		showObject(card[2 * i + 1]);
	}
	char path[100];
	for (int i = 0; i < 20; i++) {
		sprintf(path, "card_match_Images/reverse.png");
		swap_card[i] = createObject(path);
		locateObject(swap_card[i], card_match_card_game, 136 + 286 * (i % 4), 576 - 144 * (i / 4));
	}
	min = swap_card[0];
}

void reverse() {
	for (int i = 0; i < 20; i++) {
		showObject(swap_card[i]);
	}
}

// 카드 섞기
void card_move(int i, int blank) {

	ObjectID object = card[i];
	ObjectID object1 = swap_card[i];
	card[i] = card[blank];
	swap_card[i] = swap_card[blank];
	locateObject(card[i], card_match_card_game, 136 + 286 * (i % 4), 576 - 144 * (i / 4));
	locateObject(swap_card[i], card_match_card_game, 136 + 286 * (i % 4), 576 - 144 * (i / 4));
	card[blank] = object;
	swap_card[blank] = object1;
	locateObject(card[blank], card_match_card_game, 136 + 286 * (blank % 4), 576 - 144 * (blank / 4));
	locateObject(swap_card[blank], card_match_card_game, 136 + 286 * (blank % 4), 576 - 144 * (blank / 4));

	blank = i;
}

void change_turn() {
	if (card_game_card_player1 == true) {
		card_game_card_player1 = false;
		card_game_card_player2 = true;
	}
	else if (card_game_card_player2 == true) {
		card_game_card_player2 = false;
		card_game_card_player3 = true;
	}
	else if (card_game_card_player3 == true) {
		card_game_card_player3 = false;
		card_game_card_player1 = true;
	}
}

void find_change_turn() {
	if (card_game_card_player1 == true) {
		card_game_card_match_score[0]++;
		card_game_card_player1 = false;
		card_game_card_player2 = true;
	}
	else if (card_game_card_player2 == true) {
		card_game_card_match_score[1]++;
		card_game_card_player2 = false;
		card_game_card_player3 = true;
	}
	else if (card_game_card_player3 == true) {
		card_game_card_match_score[2]++;
		card_game_card_player3 = false;
		card_game_card_player1 = true;
	}
}

void card_match_game_reset() {
	card_game_start = false;
	card_game_card_no_choice = true;
	card_game_card_second_choice = false;
	card_game_card_player1 = true;
	card_game_card_player2 = false;
	card_game_card_player3 = false;
}

void card_match_check_score(int* card_in_score) {
	int score[3] = { 0 };
	if (card_in_score[0] > card_in_score[1] && card_in_score[0] > card_in_score[2]) {
		if (card_in_score[1] > card_in_score[2]) {
			mario_party_player1_score += 5;
			mario_party_player2_score += 3;
			mario_party_player3_score += 1;
			score[0] = 5;
			score[1] = 3;
			score[2] = 1;
		}
		else if (card_in_score[2] > card_in_score[1]) {
			mario_party_player1_score += 5;
			mario_party_player2_score += 1;
			mario_party_player3_score += 3;
			score[0] = 5;
			score[1] = 1;
			score[2] = 3;
		}
		else if (card_in_score[1] == card_in_score[2]) {
			mario_party_player1_score += 5;
			mario_party_player2_score += 3;
			mario_party_player3_score += 3;
			score[0] = 5;
			score[1] = 3;
			score[2] = 3;
		}
	}
	else if (card_in_score[1] > card_in_score[0] && card_in_score[1] > card_in_score[2]) {
		if (card_in_score[0] > card_in_score[2]) {
			mario_party_player1_score += 3;
			mario_party_player2_score += 5;
			mario_party_player3_score += 1;
			score[0] = 3;
			score[1] = 5;
			score[2] = 1;
		}
		else if (card_in_score[2] > card_in_score[0]) {
			mario_party_player1_score += 1;
			mario_party_player2_score += 5;
			mario_party_player3_score += 3;
			score[0] = 1;
			score[1] = 5;
			score[2] = 3;
		}
		else if (card_in_score[0] == card_in_score[2]) {
			mario_party_player1_score += 3;
			mario_party_player2_score += 5;
			mario_party_player3_score += 3;
			score[0] = 3;
			score[1] = 5;
			score[2] = 3;
		}
	}
	else if (card_in_score[2] > card_in_score[0] && card_in_score[2] > card_in_score[1]) {
		if (card_in_score[0] > card_in_score[1]) {
			mario_party_player1_score += 3;
			mario_party_player2_score += 1;
			mario_party_player3_score += 5;
			score[0] = 3;
			score[1] = 1;
			score[2] = 5;
		}
		else if (card_in_score[1] > card_in_score[0]) {
			mario_party_player1_score += 1;
			mario_party_player2_score += 3;
			mario_party_player3_score += 5;
			score[0] = 1;
			score[1] = 3;
			score[2] = 5;
		}
		else if (card_in_score[1] == card_in_score[0]) {
			mario_party_player1_score += 3;
			mario_party_player2_score += 3;
			mario_party_player3_score += 5;
			score[0] = 3;
			score[1] = 3;
			score[2] = 5;
		}
	}
	else if (card_in_score[0] == card_in_score[1] && card_in_score[0] > card_in_score[2]) {
		mario_party_player1_score += 5;
		mario_party_player2_score += 5;
		mario_party_player3_score += 1;
		score[0] = 5;
		score[1] = 5;
		score[2] = 1;
	}
	else if (card_in_score[0] == card_in_score[2] && card_in_score[0] > card_in_score[1]) {
		mario_party_player1_score += 5;
		mario_party_player2_score += 1;
		mario_party_player3_score += 5;
		score[0] = 5;
		score[1] = 1;
		score[2] = 5;
	}
	else if (card_in_score[1] == card_in_score[2] && card_in_score[1] > card_in_score[0]) {
		mario_party_player1_score += 1;
		mario_party_player2_score += 5;
		mario_party_player3_score += 5;
		score[0] = 1;
		score[1] = 5;
		score[2] = 5;
	}
	char buff1[300];
	char buff2[100];
	char buff3[100];
	sprintf(buff1, "player1의 점수: %d    전체 점수 +%d\n", card_in_score[0], score[0]);
	sprintf(buff2, "player2의 점수: %d    전체 점수 +%d\n", card_in_score[1], score[1]);
	sprintf(buff3, "player3의 점수: %d    전체 점수 +%d\n", card_in_score[2], score[2]);
	strcat(buff1, buff2);
	strcat(buff1, buff3);
	showMessage(buff1);
}

void mouseCallback_card_match(ObjectID object, int x, int y, MouseAction action) {
	if (stage_2_1 == true) {
		if (object == card_match_Next) {
			enterScene(card_match_card_game);
			create_card();
			showObject(card_match_go);
		}
		else if (object == card_match_go) {
			startTimer(card_match_go_timer);
			startTimer(card_match_move_timer);
			hideObject(card_match_go);
		}
		else if (card_game_card_no_choice == true) {
			for (int i = 0; i < 20; i++) {
				if (object == swap_card[i]) {
					hideObject(swap_card[i]);
					card_game_first = i;
					card_game_card_first = swap_card[i];
					card_game_card_second_choice = true;
					card_game_card_no_choice = false;
				}
			}
		}
		else if (card_game_card_second_choice == true) {
			for (int i = 0; i < 20; i++) {
				if (object == swap_card[i]) {
					card_game_show = i;
					hideObject(swap_card[card_game_show]);
					card_game_card_second_choice = false;
					//swap_card[0]을 min이라는 것으로 받아서 
					if (min % 2 == 0) {
						if (swap_card[i] % 2 == 0) {
							if (swap_card[i] + 1 == card_game_card_first) {
								hideObject(swap_card[i]);
								card_game_card_no_choice = true;
								card_game_find_pair++;
								find_change_turn();
							}
							else {
								startTimer(card_match_show_timer);
								change_turn();
							}
						}
						else if (swap_card[i] % 2 == 1) {
							if (swap_card[i] - 1 == card_game_card_first) {
								hideObject(swap_card[i]);
								card_game_card_no_choice = true;
								card_game_find_pair++;
								find_change_turn();
							}
							else {
								startTimer(card_match_show_timer);
								change_turn();
							}
						}
					}
					else if (min % 2 == 1) {
						if (swap_card[i] % 2 == 0) {
							if (swap_card[i] - 1 == card_game_card_first) {
								hideObject(swap_card[i]);
								card_game_card_no_choice = true;
								card_game_find_pair++;
								find_change_turn();
							}
							else {
								startTimer(card_match_show_timer);
								change_turn();
							}
						}
						else if (swap_card[i] % 2 == 1) {
							if (swap_card[i] + 1 == card_game_card_first) {
								hideObject(swap_card[i]);
								card_game_card_no_choice = true;
								card_game_find_pair++;
								find_change_turn();
							}
							else {
								startTimer(card_match_show_timer);
								change_turn();
							}
						}
					}
					if (card_game_find_pair == 10) {
						//카드 쌍이 10쌍이면 스코어를 통해서 확인 후 점수 각각 올려주기 
						//showMessage 아래에 써주는거 필요
						enterScene(card_match_card_final_cal);
						startTimer(card_match_escape_timer);
						card_game_find_pair = 0;
						card_match_check_score(card_game_card_match_score);
					}
				}
			}
		}
	}
}

void timerCallback_card_match(TimerID timer) {
	if (stage_2_1 == true) {
		if (timer == card_match_go_timer) {
			setTimer(card_match_go_timer, 10.f);
			stopTimer(card_match_move_timer);
			startTimer(card_match_reverse_timer);
		}
		else if (timer == card_match_move_timer) {
			startTimer(card_match_move_timer);
			int blank = rand() % 20;
			int j = rand() % 20;
			card_move(j, blank);
		}
		else if (timer == card_match_reverse_timer) {
			setTimer(card_match_reverse_timer, 1.f);
			reverse();
		}
		else if (timer == card_match_show_timer) {
			setTimer(card_match_show_timer, 1.0f);
			card_game_card_no_choice = true;
			showObject(swap_card[card_game_show]);
			showObject(swap_card[card_game_first]);
		}
		else if (timer == card_match_escape_timer) {
			setTimer(card_match_escape_timer, 3.f);
			for (int i = 0; i < 3; i++) {
				card_game_card_match_score[i] = 0;
			}
			card_match_game_reset();
			enterScene(game_board);
			stage_2_1 = false;
			in_game_board = true;
			showObject(run_dice);
			change_player();
			check_player_score();
		}
	}
}
//여기까지 카드 맞추기 함수

//2-2 스테이지 함수 동작 기능
void escaping_game_createFoes() {
	char buf[50];
	for (int i = 0; i < 100; i++) {
		sprintf(buf, "escaping_game_Images/box1.png");
		foesX[i] = rand() % 1280;
		foesY[i] = (rand() % 100) * i + 720;
		foesSize[i] = 1.f / (rand() % 10 + 1);
		foes[i] = createObject(buf);
		locateObject(foes[i], scene_escape_playground, foesX[i], foesY[i]);
		scaleObject(foes[i], foesSize[i]);
		showObject(foes[i]);
	}
}

void escaping_game_foesmove() {
	for (int i = 0; i < 100; i++) {
		foesY[i] -= foesspeed;
		locateObject(foes[i], scene_escape_playground, foesX[i], foesY[i]);
		if (foesY[i] < -200 * foesSize[i]) {
			score_escape++;
			foesspeed = score_escape / 100 + 1;
			foesX[i] = rand() % 1280;
			foesY[i] = (rand() % (1000 - score_escape)) + 1000;
			foesSize[i] = 1.f / (rand() % 10 + 1);
			locateObject(foes[i], scene_escape_playground, foesX[i], foesY[i]);
		}
	}
}

bool escaping_game_pointInRect(int x, int y, int rx, int ry, int size) {
	if (x < rx) return false;
	if (x > rx + size) return false;
	if (y < ry) return false;
	if (y > ry + size) return false;
	return true;
}

bool escaping_game_pointInRect1(int x1, int y1, int rx1, int ry1, int size) {
	if (x1 < rx1) return false;
	if (x1 > rx1 + size) return false;
	if (y1 < ry1) return false;
	if (y1 > ry1 + size) return false;
	return true;
}

bool escaping_game_pointInRect2(int x2, int y2, int rx2, int ry2, int size) {
	if (x2 < rx2) return false;
	if (x2 > rx2 + size) return false;
	if (y2 < ry2) return false;
	if (y2 > ry2 + size) return false;
	return true;
}

bool escaping_game_collided(int x, int y, int rx, int ry, int size) {
	return escaping_game_pointInRect(x + 10, y + 20, rx, ry, size)
		|| escaping_game_pointInRect(x + 40, y + 20, rx, ry, size)
		|| escaping_game_pointInRect(x + 25, y + 45, rx, ry, size);
}

bool escaping_game_collided2(int x1, int y1, int rx1, int ry1, int size) {
	return escaping_game_pointInRect(x1 + 10, y1 + 20, rx1, ry1, size)
		|| escaping_game_pointInRect(x1 + 40, y1 + 20, rx1, ry1, size)
		|| escaping_game_pointInRect(x1 + 25, y1 + 45, rx1, ry1, size);
}

bool escaping_game_collided3(int x2, int y2, int rx2, int ry2, int size) {
	return escaping_game_pointInRect(x2 + 10, y2 + 20, rx2, ry2, size)
		|| escaping_game_pointInRect(x2 + 40, y2 + 20, rx2, ry2, size)
		|| escaping_game_pointInRect(x2 + 25, y2 + 45, rx2, ry2, size);
}

bool escaping_game_checkCollision() {
	for (int i = 0; i < 100; i++) {
		if (escaping_game_collided(x_escape, 0, foesX[i], foesY[i], foesSize[i] * 200)) return true;
	}
	return false;
}

bool escaping_game_checkCollision1() {
	for (int i = 0; i < 100; i++) {
		if (escaping_game_collided(x1_escape, 0, foesX[i], foesY[i], foesSize[i] * 200)) return true;
	}
	return false;
}

bool escaping_game_checkCollision2() {
	for (int i = 0; i < 100; i++) {
		if (escaping_game_collided(x2_escape, 0, foesX[i], foesY[i], foesSize[i] * 200)) return true;
	}
	return false;
}

void keyboardCallback_escaping_game(KeyCode code, KeyState state) {
	if (stage_2_2 == true) {
		if (state == KeyState::KEY_PRESSED) {
			if (code == KeyCode::KEY_LEFT_ARROW) speed_escape--;
			else if (code == KeyCode::KEY_RIGHT_ARROW)speed_escape++;
			else if (code == KeyCode::KEY_DOWN_ARROW) speed1_escape--;
			else if (code == KeyCode::KEY_UP_ARROW)speed1_escape++;
			else if (code == KeyCode::KEY_F5) speed2_escape--;
			else if (code == KeyCode::KEY_F6)speed2_escape++;
		}
	}
}

void escaping_game_player1move() {
	x_escape += speed_escape;
	if (x_escape < 0) x_escape = 0;
	if (x_escape > 1230) x_escape = 1230;
	locateObject(player1_escape, scene_escape_playground, x_escape, 0);
}

void escaping_game_player2move() {
	x1_escape += speed1_escape;
	if (x1_escape < 0) x1_escape = 0;
	if (x1_escape > 1230) x1_escape = 1230;
	locateObject(player2_escape, scene_escape_playground, x1_escape, 0);
}

void escaping_game_player3move() {
	x2_escape += speed2_escape;
	if (x2_escape < 0) x2_escape = 0;
	if (x2_escape > 1230) x2_escape = 1230;
	locateObject(player3_escape, scene_escape_playground, x2_escape, 0);
}

void mouseCallback_escaping_game(ObjectID object, int x, int y, MouseAction action) {
	if (stage_2_2 == true) {
		if (object == startbutton_escape) {
			enterScene(scene_escape_playground);
			hideObject(startbutton_escape);
			escaping_game_createFoes();
			startTimer(timer1_escape);
			startTimer(timer2_escape);
			startTimer(timer3_escape);
		}
	}
}

void timerCallback_escaping_game(TimerID timer) {
	if (stage_2_2 == true) {
		if (timer == timer1_escape) {
			escaping_game_player1move();
			escaping_game_foesmove();
			if (escaping_game_checkCollision()) {
				enterScene(scene_escape_end);
				char buf[256];
				sprintf(buf, "꼴찌는 player1\n피한 박스수: %d\n 감점", score_escape);
				mario_party_player1_score -= 5;
				showMessage(buf);
				stage_2_2 = false;
				startTimer(escaping_game_escape_timer);
			}
			setTimer(timer1_escape, 0.01f);
			startTimer(timer1_escape);
		}
		if (timer == timer1_escape) {
			escaping_game_player2move();
			escaping_game_foesmove();
			if (escaping_game_checkCollision1()) {
				enterScene(scene_escape_end);
				char buf[256];
				sprintf(buf, "꼴찌는 player2\n피한 박스수: %d\n 감점", score_escape);
				mario_party_player2_score -= 5;
				showMessage(buf);
				stage_2_2 = false;
				startTimer(escaping_game_escape_timer);
			}
			setTimer(timer2_escape, 0.01f);
			startTimer(timer2_escape);
		}
		if (timer == timer3_escape) {
			escaping_game_player3move();
			escaping_game_foesmove();
			if (escaping_game_checkCollision2()) {
				enterScene(scene_escape_end);
				char buf[256];
				sprintf(buf, "꼴찌는 player3\n피한 박스수: %d\n 감점", score_escape);
				mario_party_player3_score -= 5;
				showMessage(buf);
				stage_2_2 = false;
				startTimer(escaping_game_escape_timer);
			}
			setTimer(timer3_escape, 0.01f);
			startTimer(timer3_escape);
		}
	}
	if (timer == escaping_game_escape_timer) {
		enterScene(game_board);
		in_game_board = true;
		stage_2_2_finish = true;
		showObject(run_dice);
		change_player();
		check_player_score();
	}
}
//여기까지 2-2 함수 동작 기능

//여기부터 2-4스테이지 함수 동작기능
void slot_game_create_slot_Image() {
	char buff_1[100];
	char buff_2[100];
	char buff_3[100];

	int random_num_1 = rand() % 5;
	int random_num_2 = rand() % 5;
	int random_num_3 = rand() % 5;

	sprintf(buff_1, "slot_game_Images/slot_picture%d.png", random_num_1);
	sprintf(buff_2, "slot_game_Images/slot_picture%d.png", random_num_2);
	sprintf(buff_3, "slot_game_Images/slot_picture%d.png", random_num_3);

	setObjectImage(slot_game_slot_picture[0], buff_1);
	setObjectImage(slot_game_slot_picture[1], buff_2);
	setObjectImage(slot_game_slot_picture[2], buff_3);

	slot_game_jackpot_check[0] = random_num_1;
	slot_game_jackpot_check[1] = random_num_2;
	slot_game_jackpot_check[2] = random_num_3;
}

void slot_game_slot_score_check() {
	int score[3] = { 0 };
	if (slot_game_score[0] < slot_game_score[1] && slot_game_score[0] < slot_game_score[2]) {
		if (slot_game_score[1] < slot_game_score[2]) {
			mario_party_player1_score += 7;
			mario_party_player2_score += 5;
			mario_party_player3_score += 3;
			score[0] = 7;
			score[1] = 5;
			score[2] = 3;
		}
		else if (slot_game_score[1] > slot_game_score[2]) {
			mario_party_player1_score += 7;
			mario_party_player2_score += 3;
			mario_party_player3_score += 5;
			score[0] = 7;
			score[1] = 3;
			score[2] = 5;
		}
		else if (slot_game_score[1] == slot_game_score[2]) {
			mario_party_player1_score += 7;
			mario_party_player2_score += 5;
			mario_party_player3_score += 5;
			score[0] = 7;
			score[1] = 5;
			score[2] = 5;
		}
	}
	else if (slot_game_score[1] < slot_game_score[0] && slot_game_score[1] < slot_game_score[2]) {
		if (slot_game_score[0] < slot_game_score[2]) {
			mario_party_player1_score += 5;
			mario_party_player2_score += 7;
			mario_party_player3_score += 3;
			score[0] = 5;
			score[1] = 7;
			score[2] = 3;
		}
		else if (slot_game_score[2] > slot_game_score[0]) {
			mario_party_player1_score += 3;
			mario_party_player2_score += 7;
			mario_party_player3_score += 5;
			score[0] = 3;
			score[1] = 7;
			score[2] = 5;
		}
		else if (slot_game_score[0] == slot_game_score[2]) {
			mario_party_player1_score += 5;
			mario_party_player2_score += 7;
			mario_party_player3_score += 5;
			score[0] = 5;
			score[1] = 7;
			score[2] = 5;
		}
	}
	else if (slot_game_score[2] < slot_game_score[0] && slot_game_score[2] < slot_game_score[1]) {
		if (slot_game_score[0] < slot_game_score[1]) {
			mario_party_player1_score += 5;
			mario_party_player2_score += 3;
			mario_party_player3_score += 7;
			score[0] = 5;
			score[1] = 3;
			score[2] = 7;
		}
		else if (slot_game_score[0] > slot_game_score[1]) {
			mario_party_player1_score += 3;
			mario_party_player2_score += 5;
			mario_party_player3_score += 7;
			score[0] = 3;
			score[1] = 5;
			score[2] = 7;
		}
		else if (slot_game_score[0] == slot_game_score[1]) {
			mario_party_player1_score += 5;
			mario_party_player2_score += 5;
			mario_party_player3_score += 7;
			score[0] = 5;
			score[1] = 5;
			score[2] = 7;
		}
	}
	else if (slot_game_score[0] < slot_game_score[1] && slot_game_score[1] == slot_game_score[2]) {
		mario_party_player1_score += 7;
		mario_party_player2_score += 5;
		mario_party_player3_score += 5;
		score[0] = 7;
		score[1] = 5;
		score[2] = 5;
	}
	else if (slot_game_score[1] < slot_game_score[0] && slot_game_score[0] == slot_game_score[2]) {
		mario_party_player1_score += 5;
		mario_party_player2_score += 7;
		mario_party_player3_score += 5;
		score[0] = 5;
		score[1] = 7;
		score[2] = 5;
	}
	else if (slot_game_score[2] < slot_game_score[0] && slot_game_score[0] == slot_game_score[1]) {
		mario_party_player1_score += 5;
		mario_party_player2_score += 5;
		mario_party_player3_score += 7;
		score[0] = 5;
		score[1] = 5;
		score[2] = 7;
	}
	else if (slot_game_score[0] == slot_game_score[1] && slot_game_score[0] == slot_game_score[2]) {
		mario_party_player1_score += 7;
		mario_party_player2_score += 7;
		mario_party_player3_score += 7;
		score[0] = 7;
		score[1] = 7;
		score[2] = 7;
	}
	char buff1[300];
	char buff2[100];
	char buff3[100];
	sprintf(buff1, "player1: %d등    전체 점수:+%d\n", slot_game_score[0], score[0]);
	sprintf(buff2, "player2: %d등    전체 점수:+%d\n", slot_game_score[1], score[1]);
	sprintf(buff3, "player3: %d등    전체 점수:+%d\n", slot_game_score[2], score[2]);
	strcat(buff1, buff2);
	strcat(buff1, buff3);
	showMessage(buff1);
}

// 마지막에 게임판으로 들어갈때 해주면 됨 -- bool형 초기화
void slot_game_game_reset() {
	slot_game_player1 = false;
	slot_game_player2 = false;
	slot_game_player3 = false;
	slot_game_player1_success = false;
	slot_game_player2_success = false;
	slot_game_player3_success = false;
	slot_lever_running = false;
}

void mouseCallback_slot_game(ObjectID object, int x, int y, MouseAction action) {
	if (stage_2_4 == true) {
		if (object == slot_game_Next) {
			enterScene(slot_game_board);
			startTimer(slotgame_timer);
			showTimer(slotgame_timer);
			showObject(slot_game_player);
			slot_game_start = true;
			slot_game_player1 = true;
			//두 번 이상 스테이지가 나올 가능성을 위해서 3으로 초기화 해줌 
			slot_game_score[0] = 3;
			slot_game_score[1] = 3;
			slot_game_score[2] = 3;
		}
		if (slot_game_start == true) {
			if (slot_lever_running == false) {
				if (object == slot_game_slot_lever) {
					if (slot_game_player1 == true) {
						slot_lever_running = true;
						setObjectImage(slot_game_player, "slot_game_Images/player1.png");
						startTimer(slot_game_player1_timer);
						startTimer(slot_game_slot_timer);
					}
					else if (slot_game_player2 == true) {
						slot_lever_running = true;
						setObjectImage(slot_game_player, "slot_game_Images/player2.png");
						startTimer(slot_game_player2_timer);
						startTimer(slot_game_slot_timer);
					}
					else if (slot_game_player3 == true) {
						slot_lever_running = true;
						setObjectImage(slot_game_player, "slot_game_Images/player3.png");
						startTimer(slot_game_player3_timer);
						startTimer(slot_game_slot_timer);
					}
				}
			}
		}
	}
}

void timerCallback_slot_game(TimerID timer) {
	if (stage_2_4 == true) {
		if (slot_game_start == true) {
			//slotgame_timer는 나중에 게임 합치고나서 점수 판별할 때 사용 
			if (timer == slotgame_timer) {
				enterScene(slot_game_final_cal);
				startTimer(slot_game_escape_timer);
				slot_game_slot_score_check();
			}
			else if (timer == slot_game_slot_timer) {
				slot_game_create_slot_Image();
				startTimer(slot_game_slot_timer);
			}
			else if (timer == slot_game_player1_timer) {
				stopTimer(slot_game_slot_timer);
				if (slot_game_jackpot_check[0] == slot_game_jackpot_check[1] && slot_game_jackpot_check[1] == slot_game_jackpot_check[2]) {
					slot_game_player1_success = true;
					if (slot_game_player2_success == false && slot_game_player3_success == false) {
						slot_game_score[0] = 1;
					}
					else if (slot_game_player2_success == false && slot_game_player3_success == true) {
						slot_game_score[0] = 2;
						slot_game_score[1] = 3;
						startTimer(slot_game_enter_cal_scene);
					}
					else if (slot_game_player2_success == true && slot_game_player3_success == false) {
						slot_game_score[0] = 2;
						slot_game_score[2] = 3;
						startTimer(slot_game_enter_cal_scene);
					}
					showMessage("PLAYER1 Jackpot!");
				}
				setTimer(slot_game_player1_timer, 4.f);
				slot_lever_running = false;
				if (slot_game_player1_success == true && slot_game_player2_success == true && slot_game_player3_success == true) {
					enterScene(slot_game_final_cal);
					slot_game_slot_score_check();
				}
				if (slot_game_player2_success == false) {
					slot_game_player1 = false;
					slot_game_player2 = true;
				}
				else if (slot_game_player2_success == true) {
					if (slot_game_player3_success == true) {
						slot_game_player1 = true;
					}
					else if (slot_game_player3_success == false) {
						slot_game_player1 = false;
						slot_game_player3 = true;
					}
				}
				slot_lever_running = false;
			}
			else if (timer == slot_game_player2_timer) {
				stopTimer(slot_game_slot_timer);
				if (slot_game_jackpot_check[0] == slot_game_jackpot_check[1] && slot_game_jackpot_check[1] == slot_game_jackpot_check[2]) {
					slot_game_player2_success = true;
					if (slot_game_player1_success == false && slot_game_player3_success == false) {
						slot_game_score[1] = 1;
					}
					else if (slot_game_player1_success == false && slot_game_player3_success == true) {
						slot_game_score[1] = 2;
						slot_game_score[0] = 3;
						startTimer(slot_game_enter_cal_scene);
					}
					else if (slot_game_player1_success == true && slot_game_player3_success == false) {
						slot_game_score[1] = 2;
						slot_game_score[2] = 3;
						startTimer(slot_game_enter_cal_scene);
					}
					showMessage("PLAYER2 Jackpot!");
				}
				slot_lever_running = false;
				if (slot_game_player1_success == true && slot_game_player2_success == true && slot_game_player3_success == true) {
					enterScene(slot_game_final_cal);
					slot_game_slot_score_check();
				}
				if (slot_game_player3_success == false) {
					slot_game_player2 = false;
					slot_game_player3 = true;
				}
				else if (slot_game_player3_success == true) {
					if (slot_game_player1_success == true) {
						slot_game_player2 = true;
					}
					else if (slot_game_player1_success == false) {
						slot_game_player2 = false;
						slot_game_player1 = true;
					}
				}
				setTimer(slot_game_player2_timer, 4.f);
			}
			else if (timer == slot_game_player3_timer) {
				stopTimer(slot_game_slot_timer);
				if (slot_game_jackpot_check[0] == slot_game_jackpot_check[1] && slot_game_jackpot_check[1] == slot_game_jackpot_check[2]) {
					slot_game_player3_success = true;
					if (slot_game_player2_success == false && slot_game_player1_success == false) {
						slot_game_score[2] = 1;
					}
					else if (slot_game_player2_success == false && slot_game_player1_success == true) {
						slot_game_score[2] = 2;
						slot_game_score[0] = 3;
						startTimer(slot_game_enter_cal_scene);
					}
					else if (slot_game_player2_success == true && slot_game_player1_success == false) {
						slot_game_score[2] = 2;
						slot_game_score[1] = 3;
						startTimer(slot_game_enter_cal_scene);
					}
					showMessage("PLAYER3 Jackpot!");
				}
				slot_lever_running = false;
				if (slot_game_player1_success == true && slot_game_player2_success == true && slot_game_player3_success == true) {
					enterScene(slot_game_final_cal);
					slot_game_slot_score_check();
				}
				if (slot_game_player1_success == false) {
					slot_game_player3 = false;
					slot_game_player1 = true;
				}
				else if (slot_game_player1_success == true) {
					if (slot_game_player2_success == true) {
						slot_game_player3 = true;
					}
					else if (slot_game_player2_success == false) {
						slot_game_player3 = false;
						slot_game_player2 = true;
					}
				}
				setTimer(slot_game_player3_timer, 4.f);
			}
			else if (timer == slot_game_enter_cal_scene) {
				setTimer(slotgame_timer, 180.f);
				hideTimer();
				setTimer(slot_game_enter_cal_scene, 2.f);
				startTimer(slot_game_escape_timer);
				enterScene(slot_game_final_cal);
				slot_game_slot_score_check();
			}
			else if (timer == slot_game_escape_timer) {
				setTimer(slot_game_escape_timer, 3.f);
				enterScene(game_board);
				hideTimer();
				stage_2_4 = false;
				stage_2_4_finish = true;
				in_game_board = true;
				slot_game_game_reset();
				showObject(run_dice);
				change_player();
				check_player_score();
			}
		}
	}
}
//여기까지 2-4스테이지 함수 동작 기능

//여기부터 3-1스테이지 함수 동작 기능
int maze_game_direction(int dx, int dy) {
	if (dx > 0 && dy > 0) return 2;
	else if (dx > 0 && dy < 0) return 4;
	else if (dx < 0 && dy > 0) return 8;
	else if (dx < 0 && dy < 0) return 6;
	else if (dy > 0 && dx == 0) return 1;
	else if (dx > 0 && dy == 0) return 3;
	else if (dy < 0 && dx == 0) return 5;
	else if (dx < 0 && dy == 0) return 7;
}

void maze_game_backmove(float* x, float* y, int dir) {
	if (dir == 1) {
		*y -= maze_game_bm;
	}
	else if (dir == 2) {
		*x -= maze_game_bm;
		*y -= maze_game_bm;
	}
	else if (dir == 3) {
		*x -= maze_game_bm;
	}
	else if (dir == 4) {
		*x -= maze_game_bm;
		*y += maze_game_bm;
	}
	else if (dir == 5) {
		*y += maze_game_bm;
	}
	else if (dir == 6) {
		*x += maze_game_bm;
		*y += maze_game_bm;
	}
	else if (dir == 7) {
		*x += maze_game_bm;
	}
	else if (dir == 8) {
		*x += maze_game_bm;
		*y -= maze_game_bm;
	}
}

void maze_game_isBlocked(ObjectID object, int x, int y, int dir) {
	if (maze_game_block[17 - (y / 40)][x / 40] == 1) {
		if (object == maze_game_p1) {
			maze_game_backmove(&maze_game_p1x, &maze_game_p1y, dir);
		}
		else if (object == maze_game_p2) {
			maze_game_backmove(&maze_game_p2x, &maze_game_p2y, dir);
		}
		else if (object == maze_game_p3) {
			maze_game_backmove(&maze_game_p3x, &maze_game_p3y, dir);
		}
		else if (object == maze_game_M) {
			maze_game_backmove(&maze_game_MX, &maze_game_MY, dir);
		}
	}
	else if (maze_game_block[17 - (y / 40)][x / 40] == 2) { 
		if (object == maze_game_p1) {
			showMessage("1번 플레이어 우승");
			mario_party_player1_score += 10;
		}
		if (object == maze_game_p2) {
			showMessage("2번 플레이어 우승");
			mario_party_player2_score += 10;
		}
		if (object == maze_game_p3) {
			showMessage("3번 플레이어 우승");
			mario_party_player3_score += 10;
		}
		setSceneImage(maze_game_scene1, "maze_game_Images/end.png");
		hideObject(maze_game_light);
		hideObject(maze_game_M);
		hideObject(maze_game_p1);
		hideObject(maze_game_p2);
		hideObject(maze_game_p3);
		maze_game_block[8][27] = 0;
		maze_game_block[8][28] = 0;
		maze_game_block[8][29] = 0;
		maze_game_block[9][27] = 0;
		maze_game_block[9][28] = 0;
		maze_game_block[9][29] = 0;
		stage_3_1_finish = true;
		startTimer(maze_game_escape_timer);
		////여기서 끝
	}
}

void maze_game_checkBlock(ObjectID object, int x, int y, int dir, int size) {
	maze_game_isBlocked(object, x, y, dir);
	maze_game_isBlocked(object, x + size, y, dir);
	maze_game_isBlocked(object, x, y + size, dir);
	maze_game_isBlocked(object, x + size, y + size, dir);
}

void maze_game_setImageD(ObjectID object1, int id, int dir) {
	char maze_game_pim[40];
	if (dir == 1) {
		sprintf_s(maze_game_pim, 40, "maze_game_Images/%dU.png", id);
		setObjectImage(object1, maze_game_pim);
	}
	else if (dir == 2) {
		sprintf_s(maze_game_pim, 40, "maze_game_Images/%dRU.png", id);
		setObjectImage(object1, maze_game_pim);
	}
	else if (dir == 3) {
		sprintf_s(maze_game_pim, 40, "maze_game_Images/%dR.png", id);
		setObjectImage(object1, maze_game_pim);
	}
	else if (dir == 4) {
		sprintf_s(maze_game_pim, 40, "maze_game_Images/%dRD.png", id);
		setObjectImage(object1, maze_game_pim);
	}
	else if (dir == 5) {
		sprintf_s(maze_game_pim, 40, "maze_game_Images/%dD.png", id);
		setObjectImage(object1, maze_game_pim);
	}
	else if (dir == 6) {
		sprintf_s(maze_game_pim, 40, "maze_game_Images/%dLD.png", id);
		setObjectImage(object1, maze_game_pim);
	}
	else if (dir == 7) {
		sprintf_s(maze_game_pim, 40, "maze_game_Images/%dL.png", id);
		setObjectImage(object1, maze_game_pim);
	}
	else if (dir == 8) {
		sprintf_s(maze_game_pim, 40, "maze_game_Images/%dLU.png", id);
		setObjectImage(object1, maze_game_pim);
	}
}

void timerCallback_maze_game(TimerID timer) {
	if (stage_3_1 == true) {
		if (timer == maze_game_timer1) {
			maze_game_p1x += maze_game_p1dx;
			maze_game_p1y += maze_game_p1dy;
			maze_game_p2x += maze_game_p2dx;
			maze_game_p2y += maze_game_p2dy;
			maze_game_p3x += maze_game_p3dx;
			maze_game_p3y += maze_game_p3dy;
			maze_game_t += 0.01;
			maze_game_checkBlock(maze_game_p2, maze_game_p2x, maze_game_p2y, maze_game_direction(maze_game_p2dx, maze_game_p2dy), 24);
			maze_game_checkBlock(maze_game_p1, maze_game_p1x, maze_game_p1y, maze_game_direction(maze_game_p1dx, maze_game_p1dy), 24);
			maze_game_checkBlock(maze_game_p3, maze_game_p3x, maze_game_p3y, maze_game_direction(maze_game_p3dx, maze_game_p3dy), 24);
			maze_game_setImageD(maze_game_p2, 2, maze_game_direction(maze_game_p2dx, maze_game_p2dy));
			maze_game_setImageD(maze_game_p1, 1, maze_game_direction(maze_game_p1dx, maze_game_p1dy));
			maze_game_setImageD(maze_game_p3, 3, maze_game_direction(maze_game_p3dx, maze_game_p3dy));
			if (maze_game_lt == 1) {
				locateObject(maze_game_light, maze_game_scene1, maze_game_p1x - 1910, maze_game_p1y - 1070);
				maze_game_lt++;
			}
			else if (maze_game_lt == 2) {
				locateObject(maze_game_light, maze_game_scene1, maze_game_p2x - 1910, maze_game_p2y - 1070);
				maze_game_lt++;
			}
			else if (maze_game_lt == 3) {
				locateObject(maze_game_light, maze_game_scene1, maze_game_p3x - 1910, maze_game_p3y - 1070);
				maze_game_lt = 1;
			}
			locateObject(maze_game_M, maze_game_scene1, maze_game_MX, maze_game_MY);
			if (((maze_game_p1x >= maze_game_MX && maze_game_p1x <= maze_game_MX + 32) && (maze_game_p1y >= maze_game_MY && maze_game_p1y <= maze_game_MY + 32)) || ((maze_game_p1x + 24 >= maze_game_MX && maze_game_p1x + 24 <= maze_game_MX + 32) && (maze_game_p1y >= maze_game_MY && maze_game_p1y <= maze_game_MY + 32)) || ((maze_game_p1x >= maze_game_MX && maze_game_p1x <= maze_game_MX + 32) && (maze_game_p1y + 24 >= maze_game_MY && maze_game_p1y + 24 <= maze_game_MY + 32)) || ((maze_game_p1x + 24 >= maze_game_MX && maze_game_p1x + 24 <= maze_game_MX + 32) && (maze_game_p1y + 24 >= maze_game_MY && maze_game_p1y + 24 <= maze_game_MY + 32))) {
				maze_game_p1x = maze_game_IX;
				maze_game_p1y = maze_game_IY;
			}
			if (((maze_game_p2x >= maze_game_MX && maze_game_p2x <= maze_game_MX + 32) && (maze_game_p2y >= maze_game_MY && maze_game_p2y <= maze_game_MY + 32)) || ((maze_game_p2x + 24 >= maze_game_MX && maze_game_p2x + 24 <= maze_game_MX + 32) && (maze_game_p2y >= maze_game_MY && maze_game_p2y <= maze_game_MY + 32)) || ((maze_game_p2x >= maze_game_MX && maze_game_p2x <= maze_game_MX + 32) && (maze_game_p2y + 24 >= maze_game_MY && maze_game_p2y + 24 <= maze_game_MY + 32)) || ((maze_game_p2x + 24 >= maze_game_MX && maze_game_p2x + 24 <= maze_game_MX + 32) && (maze_game_p2y + 24 >= maze_game_MY && maze_game_p2y + 24 <= maze_game_MY + 32))) {
				maze_game_p2x = maze_game_IX + 30;
				maze_game_p2y = maze_game_IY;
			}
			if (((maze_game_p3x >= maze_game_MX && maze_game_p3x <= maze_game_MX + 32) && (maze_game_p3y >= maze_game_MY && maze_game_p3y <= maze_game_MY + 32)) || ((maze_game_p3x + 24 >= maze_game_MX && maze_game_p3x + 24 <= maze_game_MX + 32) && (maze_game_p3y >= maze_game_MY && maze_game_p3y <= maze_game_MY + 32)) || ((maze_game_p3x >= maze_game_MX && maze_game_p3x <= maze_game_MX + 32) && (maze_game_p3y + 24 >= maze_game_MY && maze_game_p3y + 24 <= maze_game_MY + 32)) || ((maze_game_p3x + 24 >= maze_game_MX && maze_game_p3x + 24 <= maze_game_MX + 32) && (maze_game_p3y + 24 >= maze_game_MY && maze_game_p3y + 24 <= maze_game_MY + 32))) {
				maze_game_p3x = maze_game_IX + 60;
				maze_game_p3y = maze_game_IY;
			}
			if (maze_game_t >= 0.2) {
				maze_game_RN = rand() % 4;
				maze_game_t = 0;
			}
			if (maze_game_RN == 0) {
				maze_game_MY += maze_game_speed;
				maze_game_checkBlock(maze_game_M, maze_game_MX, maze_game_MY, 1, 32);
				setObjectImage(maze_game_M, "maze_game_Images/4U.png");
			}
			else if (maze_game_RN == 1) {
				maze_game_MX += maze_game_speed;
				maze_game_checkBlock(maze_game_M, maze_game_MX, maze_game_MY, 3, 32);
				setObjectImage(maze_game_M, "maze_game_Images/4R.png");
			}
			else if (maze_game_RN == 2) {
				maze_game_MX -= maze_game_speed;
				maze_game_checkBlock(maze_game_M, maze_game_MX, maze_game_MY, 7, 32);
				setObjectImage(maze_game_M, "maze_game_Images/4L.png");
			}
			else if (maze_game_RN == 3) {
				maze_game_MY -= maze_game_speed;
				maze_game_checkBlock(maze_game_M, maze_game_MX, maze_game_MY, 5, 32);
				setObjectImage(maze_game_M, "maze_game_Images/4D.png");
			}
			locateObject(maze_game_p1, maze_game_scene1, maze_game_p1x, maze_game_p1y);
			locateObject(maze_game_p2, maze_game_scene1, maze_game_p2x, maze_game_p2y);
			locateObject(maze_game_p3, maze_game_scene1, maze_game_p3x, maze_game_p3y);
			setTimer(maze_game_timer1, 0.01f);
			startTimer(maze_game_timer1);
		}
		if (timer == maze_game_escape_timer) {
			setTimer(maze_game_escape_timer, 3.f);
			enterScene(game_board);
			stage_3_1 = false;
			stage_3_1_finish = true;
			in_game_board = true;
			showObject(run_dice);
			change_player();
			check_player_score();
		}
	}
}

void keyboardCallback_maze_game(KeyCode code, KeyState state)
{
	if (stage_3_1 == true) {
		if (code == KeyCode::KEY_D) {
			maze_game_p1dx += (state == KeyState::KEY_PRESSED ? maze_game_speed : -maze_game_speed);
		}
		else if (code == KeyCode::KEY_A) {
			maze_game_p1dx -= (state == KeyState::KEY_PRESSED ? maze_game_speed : -maze_game_speed);
		}
		else if (code == KeyCode::KEY_W) {
			maze_game_p1dy += (state == KeyState::KEY_PRESSED ? maze_game_speed : -maze_game_speed);
		}
		else if (code == KeyCode::KEY_S) {
			maze_game_p1dy -= (state == KeyState::KEY_PRESSED ? maze_game_speed : -maze_game_speed);
		}

		if (code == KeyCode::KEY_L) {
			maze_game_p2dx += (state == KeyState::KEY_PRESSED ? maze_game_speed : -maze_game_speed);
		}
		else if (code == KeyCode::KEY_J) {
			maze_game_p2dx -= (state == KeyState::KEY_PRESSED ? maze_game_speed : -maze_game_speed);
		}
		else if (code == KeyCode::KEY_I) {
			maze_game_p2dy += (state == KeyState::KEY_PRESSED ? maze_game_speed : -maze_game_speed);
		}
		else if (code == KeyCode::KEY_K) {
			maze_game_p2dy -= (state == KeyState::KEY_PRESSED ? maze_game_speed : -maze_game_speed);
		}

		if (code == KeyCode::KEY_RIGHT_ARROW) {
			maze_game_p3dx += (state == KeyState::KEY_PRESSED ? maze_game_speed : -maze_game_speed);
		}
		else if (code == KeyCode::KEY_LEFT_ARROW) {
			maze_game_p3dx -= (state == KeyState::KEY_PRESSED ? maze_game_speed : -maze_game_speed);
		}
		else if (code == KeyCode::KEY_UP_ARROW) {
			maze_game_p3dy += (state == KeyState::KEY_PRESSED ? maze_game_speed : -maze_game_speed);
		}
		else if (code == KeyCode::KEY_DOWN_ARROW) {
			maze_game_p3dy -= (state == KeyState::KEY_PRESSED ? maze_game_speed : -maze_game_speed);
		}
	}
}

void mouseCallback_maze_game(ObjectID object, int x, int y, MouseAction action) {
	if (stage_3_1 == true) {
		if (object == maze_game_next) {
			maze_game_RN = rand() % 4;
			hideObject(maze_game_next);
			startTimer(maze_game_timer1);
			setSceneImage(maze_game_scene1, "maze_game_Images/background.png");
			maze_game_light = createObject("maze_game_Images/LIGHT.png");
			maze_game_p1 = createObject("maze_game_Images/1D.png");
			maze_game_p2 = createObject("maze_game_Images/2D.png");
			maze_game_p3 = createObject("maze_game_Images/3D.png");
			maze_game_M = createObject("maze_game_Images/4D.png");
			scaleObject(maze_game_M, 0.08f);
			showObject(maze_game_M);
			locateObject(maze_game_M, maze_game_scene1, maze_game_MX, maze_game_MY);
			locateObject(maze_game_light, maze_game_scene1, maze_game_p1x - 1910, maze_game_p1y - 1070);
			scaleObject(maze_game_p2, 0.03f);
			scaleObject(maze_game_p1, 0.03f);
			scaleObject(maze_game_p3, 0.03f);
			showObject(maze_game_light);
			showObject(maze_game_p1);
			showObject(maze_game_p2);
			showObject(maze_game_p3);
		}
	}
}
//여기까지 3-1 스테이지 함수 동작 기능

//여기부터 3-2 스테이지 함수 동작 기능
int find_game_direction(int dx, int dy) {
	if (dx > 0 && dy > 0) return 2;
	else if (dx > 0 && dy < 0) return 4;
	else if (dx < 0 && dy > 0) return 8;
	else if (dx < 0 && dy < 0) return 6;
	else if (dy > 0 && dx == 0) return 1;
	else if (dx > 0 && dy == 0) return 3;
	else if (dy < 0 && dx == 0) return 5;
	else if (dx < 0 && dy == 0) return 7;
}

void find_game_backmove(float* x, float* y, int dir) {
	if (dir == 1) {
		*y -= find_game_bm;
	}
	else if (dir == 2) {
		*x -= find_game_bm;
		*y -= find_game_bm;
	}
	else if (dir == 3) {
		*x -= find_game_bm;
	}
	else if (dir == 4) {
		*x -= find_game_bm;
		*y += find_game_bm;
	}
	else if (dir == 5) {
		*y += find_game_bm;
	}
	else if (dir == 6) {
		*x += find_game_bm;
		*y += find_game_bm;
	}
	else if (dir == 7) {
		*x += find_game_bm;
	}
	else if (dir == 8) {
		*x += find_game_bm;
		*y -= find_game_bm;
	}
}

void find_game_isBlocked(ObjectID object, int x, int y, int dir) {
	if (find_game_block[17 - (y / 40)][x / 40] == 1) {
		if (object == find_game_p1) {
			find_game_backmove(&find_game_p1x, &find_game_p1y, dir);
		}
		else if (object == find_game_p2) {
			find_game_backmove(&find_game_p2x, &find_game_p2y, dir);
		}
		else if (object == find_game_p3) {
			find_game_backmove(&find_game_p3x, &find_game_p3y, dir);
		}
	}
}

void find_game_checkBlock(ObjectID object, int x, int y, int dir, int size) {
	find_game_isBlocked(object, x, y, dir);
	find_game_isBlocked(object, x + size, y, dir);
	find_game_isBlocked(object, x, y + size, dir);
	find_game_isBlocked(object, x + size, y + size, dir);
}

void find_game_setboard() {
	find_game_block[5][5] = 2; //block[4][5] = 2; block[5][4] = 2;
	find_game_block[3][3] = 3; //block[3][4] = 3;
	find_game_block[9][11] = 4;
	find_game_block[9][7] = 5; //block[9][6] = 5;
	find_game_block[9][5] = 6;
	find_game_block[3][6] = 7;
	find_game_block[11][9] = 8;
	find_game_block[6][7] = 9;
	find_game_block[3][10] = 10;
	find_game_block[10][3] = 11;

	find_game_block[6][25] = 12;
	find_game_block[10][28] = 13;
	find_game_block[3][24] = 14;
	find_game_block[12][23] = 15;
	find_game_block[11][22] = 16;
	find_game_block[8][20] = 17;// block[8][21] = 17;
	find_game_block[8][26] = 18;
	find_game_block[3][20] = 19;
	find_game_block[10][29] = 20; //block[11][29] = 20;
	find_game_block[10][19] = 21;
}
////그림 좌표

void timerCallback_find_game(TimerID timer) {
	if (stage_3_2 == true) {
		if (timer == find_game_timer1) {
			find_game_p1x += find_game_p1dx;
			find_game_p1y += find_game_p1dy;
			find_game_p2x += find_game_p2dx;
			find_game_p2y += find_game_p2dy;
			find_game_p3x += find_game_p3dx;
			find_game_p3y += find_game_p3dy;
			find_game_t += 0.01;
			find_game_checkBlock(find_game_p2, find_game_p2x, find_game_p2y, find_game_direction(find_game_p2dx, find_game_p2dy), 40);
			find_game_checkBlock(find_game_p1, find_game_p1x, find_game_p1y, find_game_direction(find_game_p1dx, find_game_p1dy), 40);
			find_game_checkBlock(find_game_p3, find_game_p3x, find_game_p3y, find_game_direction(find_game_p3dx, find_game_p3dy), 40);
			locateObject(find_game_p1, find_game_scene1, find_game_p1x, find_game_p1y);
			locateObject(find_game_p2, find_game_scene1, find_game_p2x, find_game_p2y);
			locateObject(find_game_p3, find_game_scene1, find_game_p3x, find_game_p3y);
			setTimer(find_game_timer1, 0.01f);
			startTimer(find_game_timer1);
		}
		if (timer == find_game_escape_timer) {
			setTimer(find_game_escape_timer, 3.f);
			enterScene(game_board);
			stage_3_2 = false;
			stage_3_2_finish = true;
			in_game_board = true;
			showObject(run_dice);
			change_player();
			check_player_score();
		}
	}
}

void find_game_checkFinish() {
	char end[50];
	if (find_game_p1score + find_game_p2score + find_game_p3score == 20) {
		sprintf_s(end, 50, "P1 : %d\nP2 : %d\nP3 : %d", find_game_p1score, find_game_p2score, find_game_p3score);
		showMessage(end);
		setSceneImage(find_game_scene1, "find_game_Images/end.png");
		hideObject(find_game_p1);
		hideObject(find_game_p2);
		hideObject(find_game_p3);
		for (int i = 2; i <= 21; i++) {
			hideObject(find_game_O[i]);
			hideObject(find_game_X[i]);
		}
		int find_game_score[3] = { find_game_p1score, find_game_p2score, find_game_p3score };
		int M = find_game_score[0], find_game_winnerN = 0, find_game_winner[3] = { 0 };
		for (int i = 0; i <= 1; i++) {
			if (find_game_score[i + 1] > find_game_score[i]) M = find_game_score[i + 1];
		}
		for (int i = 0; i <= 2; i++) {
			if (find_game_score[i] == M) {
				find_game_winnerN++;
				find_game_winner[i] = 1;
			}
		}
		if (find_game_winnerN == 1) {
			if (find_game_winner[0] == 1) {
				mario_party_player1_score += 10;
			}
			else if (find_game_winner[1] == 1) {
				mario_party_player2_score += 10;
			}
			else if (find_game_winner[2] == 1) {
				mario_party_player3_score += 10;
			}
		}
		else if (find_game_winnerN == 2) {
			if (find_game_winner[0] == 1 && find_game_winner[1] == 1) {
				mario_party_player1_score += 7;
				mario_party_player2_score += 7;
			}
			else if (find_game_winner[1] == 1 && find_game_winner[2] == 1) {
				mario_party_player2_score += 7;
				mario_party_player3_score += 7;
			}
			else if (find_game_winner[0] == 1 && find_game_winner[2] == 1) {
				mario_party_player1_score += 7;
				mario_party_player3_score += 7;
			}
		}
		else if (find_game_winnerN == 3) {
			mario_party_player1_score += 10;
			mario_party_player2_score += 10;
			mario_party_player3_score += 10;
		}
		startTimer(find_game_escape_timer);
	}
}

void keyboardCallback_find_game(KeyCode code, KeyState state)
{
	if (stage_3_2 == true) {
		if (code == KeyCode::KEY_D) {
			find_game_p1dx += (state == KeyState::KEY_PRESSED ? find_game_speed : -find_game_speed);
		}
		else if (code == KeyCode::KEY_A) {
			find_game_p1dx -= (state == KeyState::KEY_PRESSED ? find_game_speed : -find_game_speed);
		}
		else if (code == KeyCode::KEY_W) {
			find_game_p1dy += (state == KeyState::KEY_PRESSED ? find_game_speed : -find_game_speed);
		}
		else if (code == KeyCode::KEY_S) {
			find_game_p1dy -= (state == KeyState::KEY_PRESSED ? find_game_speed : -find_game_speed);
		}
		else if (code == KeyCode::KEY_E) {
			if (state == KeyState::KEY_PRESSED && find_game_block[int(17 - (find_game_p1y / 40))][int(find_game_p1x / 40)] > 1) {
				locateObject(find_game_O[find_game_block[int(17 - (find_game_p1y / 40))][int(find_game_p1x / 40)]], find_game_scene1, find_game_p1x, find_game_p1y);
				showObject(find_game_O[find_game_block[int(17 - (find_game_p1y / 40))][int(find_game_p1x / 40)]]);
				showObject(find_game_X[find_game_block[int(17 - (find_game_p1y / 40))][int(find_game_p1x / 40)]]);
				find_game_block[int(17 - (find_game_p1y / 40))][int(find_game_p1x / 40)] = 0;
				find_game_p1score++;
				find_game_checkFinish();
			}
		}

		if (code == KeyCode::KEY_L) {
			find_game_p2dx += (state == KeyState::KEY_PRESSED ? find_game_speed : -find_game_speed);
		}
		else if (code == KeyCode::KEY_J) {
			find_game_p2dx -= (state == KeyState::KEY_PRESSED ? find_game_speed : -find_game_speed);
		}
		else if (code == KeyCode::KEY_I) {
			find_game_p2dy += (state == KeyState::KEY_PRESSED ? find_game_speed : -find_game_speed);
		}
		else if (code == KeyCode::KEY_K) {
			find_game_p2dy -= (state == KeyState::KEY_PRESSED ? find_game_speed : -find_game_speed);
		}
		else if (code == KeyCode::KEY_O) {
			if (state == KeyState::KEY_PRESSED && find_game_block[int(17 - (find_game_p2y / 40))][int(find_game_p2x / 40)] > 1) {
				locateObject(find_game_O[find_game_block[int(17 - (find_game_p2y / 40))][int(find_game_p2x / 40)]], find_game_scene1, find_game_p2x, find_game_p2y);
				showObject(find_game_O[find_game_block[int(17 - (find_game_p2y / 40))][int(find_game_p2x / 40)]]);
				showObject(find_game_X[find_game_block[int(17 - (find_game_p2y / 40))][int(find_game_p2x / 40)]]);
				find_game_block[int(17 - (find_game_p2y / 40))][int(find_game_p2x / 40)] = 0;
				find_game_p2score++;
				find_game_checkFinish();
			}
		}

		if (code == KeyCode::KEY_RIGHT_ARROW) {
			find_game_p3dx += (state == KeyState::KEY_PRESSED ? find_game_speed : -find_game_speed);
		}
		else if (code == KeyCode::KEY_LEFT_ARROW) {
			find_game_p3dx -= (state == KeyState::KEY_PRESSED ? find_game_speed : -find_game_speed);
		}
		else if (code == KeyCode::KEY_UP_ARROW) {
			find_game_p3dy += (state == KeyState::KEY_PRESSED ? find_game_speed : -find_game_speed);
		}
		else if (code == KeyCode::KEY_DOWN_ARROW) {
			find_game_p3dy -= (state == KeyState::KEY_PRESSED ? find_game_speed : -find_game_speed);
		}
		else if (code == KeyCode::KEY_RIGHT_SHIFT) {
			if (state == KeyState::KEY_PRESSED && find_game_block[int(17 - (find_game_p3y / 40))][int(find_game_p3x / 40)] > 1) {
				locateObject(find_game_O[find_game_block[int(17 - (find_game_p3y / 40))][int(find_game_p3x / 40)]], find_game_scene1, find_game_p3x, find_game_p3y);
				showObject(find_game_O[find_game_block[int(17 - (find_game_p3y / 40))][int(find_game_p3x / 40)]]);
				showObject(find_game_X[find_game_block[int(17 - (find_game_p3y / 40))][int(find_game_p3x / 40)]]);
				find_game_block[int(17 - (find_game_p3y / 40))][int(find_game_p3x / 40)] = 0;
				find_game_p3score++;
				find_game_checkFinish();
			}
		}
	}
}

void mouseCallback_find_game(ObjectID object, int x, int y, MouseAction action) {
	if (stage_3_2 == true) {
		if (object == find_game_next) {
			hideObject(find_game_next);
			find_game_setboard();
			setSceneImage(find_game_scene1, "find_game_Images/background.png");
			find_game_timer1 = createTimer(0.01f);
			startTimer(find_game_timer1);
			find_game_p1 = createObject("find_game_Images/p1.png");
			find_game_p2 = createObject("find_game_Images/p2.png");
			find_game_p3 = createObject("find_game_Images/p3.png");
			for (int i = 2; i <= 21; i++) {
				find_game_O[i] = createObject("find_game_Images/check.png");
				scaleObject(find_game_O[i], 0.15f);
			}
			for (int i = 2; i <= 11; i++) {
				find_game_X[i] = createObject("find_game_Images/check2.png");
				scaleObject(find_game_X[i], 0.15f);
				locateObject(find_game_X[i], find_game_scene1, 100 + 43 * (i - 2), 110);
			}
			for (int i = 12; i <= 21; i++) {
				find_game_X[i] = createObject("find_game_Images/check2.png");
				scaleObject(find_game_X[i], 0.15f);
				locateObject(find_game_X[i], find_game_scene1, 350 + 43 * (i - 2), 110);
			}
			scaleObject(find_game_p2, 0.2f);
			scaleObject(find_game_p1, 0.2f);
			scaleObject(find_game_p3, 0.2f);
			showObject(find_game_p1);
			showObject(find_game_p2);
			showObject(find_game_p3);
		}
	}
}
//여기까지 3-2 함수 동작 기능

//여기부터 3-4 스테이지 함수 동작 기능
void area_game_reset() {
	area_game_R1++;
	if (area_game_R1 == 2) setSceneImage(area_game_scene1, "area_battle_Images/R2.png");
	if (area_game_R1 == 3) setSceneImage(area_game_scene1, "area_battle_Images/R3.png");
	if (area_game_R1 == 4) {
		int M = area_game_score[0];      //////////////////////////////////////////////////// 종료
		char area_game_endscore[100];
		for (int i = 0; i <= 1; i++) if (area_game_score[i] > area_game_score[i + 1]) M = area_game_score[i];
		for (int i = 0; i <= 2; i++) {
			if (area_game_score[i] == M) {
				area_game_winnerN++;
				area_game_winner[i] = 1;
			}
		}
		if (area_game_winnerN == 1) {
			if (area_game_winner[0] == 1) {
				sprintf_s(area_game_endscore, 100, "%d번 플레이어 우승", 1);
				showMessage(area_game_endscore);
				mario_party_player1_score += 10;
			}
			else if (area_game_winner[0] == 1) {
				sprintf_s(area_game_endscore, 100, "%d번 플레이어 우승", 2);
				showMessage(area_game_endscore);
				mario_party_player2_score += 10;
			}
			else if (area_game_winner[0] == 1) {
				sprintf_s(area_game_endscore, 100, "%d번 플레이어 우승", 3);
				showMessage(area_game_endscore);
				mario_party_player3_score += 10;
			}
		}
		else if (area_game_winnerN == 2) {
			if (area_game_winner[0] == 1 && area_game_winner[1] == 1) {
				showMessage(" 1번 2번 플레이어 우승!");
				mario_party_player1_score += 10;
				mario_party_player2_score += 10;
				mario_party_player3_score += 0;
			}
			else if (area_game_winner[1] == 1 && area_game_winner[2] == 1) {
				showMessage(" 2번 3번 플레이어 우승!");
				mario_party_player1_score += 0;
				mario_party_player2_score += 10;
				mario_party_player3_score += 10;
			}
			else if (area_game_winner[0] == 1 && area_game_winner[2] == 1) {
				showMessage(" 1번 3번 플레이어 우승!");
				mario_party_player1_score += 10;
				mario_party_player2_score += 0;
				mario_party_player3_score += 10;
			}
		}
		else if (area_game_winnerN == 3) {
			showMessage("모두 우승!");
			mario_party_player1_score += 10;
			mario_party_player2_score += 10;
			mario_party_player3_score += 10;
		}
		setSceneImage(area_game_scene1, "area_battle_Images/end.png");
		hideObject(area_game_p1);
		hideObject(area_game_p2);
		hideObject(area_game_p3);
		startTimer(area_game_escape_timer);
	}
	area_game_P1T = true, area_game_P2T = true, area_game_P3T = true, area_game_k1 = 0, area_game_k2 = 0, area_game_k3 = 0, area_game_j = 0;
	area_game_sc1 = 0, area_game_sc2 = 0, area_game_sc3 = 0;
	area_game_p1x = area_game_IX, area_game_p1y = area_game_IY, area_game_p2x = area_game_IX + 100, area_game_p2y = area_game_IY, area_game_p3x = area_game_IX + 200, area_game_p3y = area_game_IY;
	stopTimer(area_game_timer2);
	setTimer(area_game_timer2, 0.01f);
	setTimer(area_game_timer3, 5.0f);
	for (int i = 0; i <= 28; i++) {
		scaleObject(area_game_p1B[i], 0);
		scaleObject(area_game_p2B[i], 0);
		scaleObject(area_game_p3B[i], 0);
	}
}

void timerCallback_area_game(TimerID timer) {
	if (stage_3_4 == true) {
		if (timer == area_game_timer1) {
			area_game_B1X = int((area_game_p1x + 30 - 85) / 70);
			area_game_B1Y = 7 - int((area_game_p1y + 30 - 85) / 70);
			area_game_B2X = int((area_game_p2x + 30 - 85) / 70);
			area_game_B2Y = 7 - int((area_game_p2y + 30 - 85) / 70);
			area_game_B3X = int((area_game_p3x + 30 - 85) / 70);
			area_game_B3Y = 7 - int((area_game_p3y + 30 - 85) / 70);
			area_game_p1x += area_game_p1dx;
			area_game_p1y += area_game_p1dy;
			area_game_p2x += area_game_p2dx;
			area_game_p2y += area_game_p2dy;
			area_game_p3x += area_game_p3dx;
			area_game_p3y += area_game_p3dy;
			locateObject(area_game_p1, area_game_scene1, area_game_p1x, area_game_p1y);
			locateObject(area_game_p2, area_game_scene1, area_game_p2x, area_game_p2y);
			locateObject(area_game_p3, area_game_scene1, area_game_p3x, area_game_p3y);
			if (!area_game_P1T && !area_game_P2T && !area_game_P3T) startTimer(area_game_timer3);
			setTimer(area_game_timer1, 0.01f);
			startTimer(area_game_timer1);
		}
		if (timer == area_game_timer2 && area_game_P1T == false) {
			if (area_game_sc1 <= 1.05) {
				scaleObject(area_game_p1B[area_game_k1], area_game_sc1);
				area_game_sc1 += 0.25;
			}
			else if (area_game_k1 < 29) {
				area_game_k1++;
				area_game_sc1 = 0;
			}
			setTimer(area_game_timer2, 0.01f);
			startTimer(area_game_timer2);
		}
		if (timer == area_game_timer2 && area_game_P2T == false) {
			if (area_game_sc2 <= 1.05) {
				scaleObject(area_game_p2B[area_game_k2], area_game_sc2);
				area_game_sc2 += 0.25;
			}
			else if (area_game_k2 < 29) {
				area_game_k2++;
				area_game_sc2 = 0;
			}
			setTimer(area_game_timer2, 0.01f);
			startTimer(area_game_timer2);
		}
		if (timer == area_game_timer2 && area_game_P3T == false) {
			if (area_game_sc3 <= 1.05) {
				scaleObject(area_game_p3B[area_game_k3], area_game_sc3);
				area_game_sc3 += 0.25;
			}
			else if (area_game_k3 < 29) {
				area_game_k3++;
				area_game_sc3 = 0;
			}
			setTimer(area_game_timer2, 0.01f);
			startTimer(area_game_timer2);
		}
		if (timer == area_game_timer3) {
			hideObject(area_game_p1B[area_game_j]);
			hideObject(area_game_p2B[area_game_j]);
			hideObject(area_game_p3B[area_game_j]);
			setTimer(area_game_timer3, 0.7f);
			startTimer(area_game_timer3);
			if (area_game_j < 29) {
				area_game_j++;
			}
			else {
				int area_game_BN[3] = { area_game_n1,area_game_n2,area_game_n3 };
				for (int i = 0; i <= 2; i++) {
					if (area_game_BN[i] == 29) {
						area_game_score[i] += 5;
					}
					else if (area_game_BN[i] == 28) {
						area_game_score[i] += 3;
					}
				}
				char area_game_end[100];
				sprintf_s(area_game_end, 100, "Player1 %d점\nPlayer2 %d점\nPlayer3 %d점", area_game_score[0], area_game_score[1], area_game_score[2]);
				showMessage(area_game_end);
				area_game_reset();
				stopTimer(area_game_timer3);
			}
		}
		if (timer == area_game_escape_timer) {
			enterScene(mario_party_final_cal);
			stage_3_4 = false;
			stage_3_4_finish = true;
			final_cal = true;
			check_mario_party_winner();
		}
	}
}

void area_game_chooseBlock(int BX, int BY, int* n, int type) {
	if (stage_3_4 == true) {
		if (area_game_R1 == 1 && BX >= 1 && BX <= 16 && BY >= 1 && BY <= 6 && area_game_board1[BY - 1][BX - 1] >= 4) {
			area_game_N = area_game_board1[BY - 1][BX - 1];
			*n = 0;
			for (int i = 0; i <= 5; i++) {
				for (int j = 0; j <= 13; j++) {
					if (area_game_board1[i][j] == area_game_N) {
						if (type == 1) {
							locateObject(area_game_p1B[*n], area_game_scene1, 85 + 70 + j * 69, 650 - (85 + 70 + i * 68));
							showObject(area_game_p1B[*n]);
							area_game_board1[i][j] = 1;
							area_game_P1T = false;
						}
						if (type == 2) {
							locateObject(area_game_p2B[*n], area_game_scene1, 85 + 70 + j * 69, 650 - (85 + 70 + i * 68));
							showObject(area_game_p2B[*n]);
							area_game_board1[i][j] = 2;
							area_game_P2T = false;
						}
						if (type == 3) {
							locateObject(area_game_p3B[*n], area_game_scene1, 85 + 70 + j * 69, 650 - (85 + 70 + i * 68));
							showObject(area_game_p3B[*n]);
							area_game_board1[i][j] = 3;
							area_game_P3T = false;
						}
						(*n)++;
					}
				}
			}
		}
		if (area_game_R1 == 2 && BX >= 1 && BX <= 16 && BY >= 1 && BY <= 6 && area_game_board2[BY - 1][BX - 1] >= 4) {
			area_game_N = area_game_board2[BY - 1][BX - 1];
			*n = 0;
			for (int i = 0; i <= 5; i++) {
				for (int j = 0; j <= 13; j++) {
					if (area_game_board2[i][j] == area_game_N) {
						if (type == 1) {
							locateObject(area_game_p1B[*n], area_game_scene1, 85 + 70 + j * 69.5, 652 - (85 + 70 + i * 70));
							showObject(area_game_p1B[*n]);
							area_game_board2[i][j] = 1;
							area_game_P1T = false;
						}
						if (type == 2) {
							locateObject(area_game_p2B[*n], area_game_scene1, 85 + 70 + j * 69.5, 652 - (85 + 70 + i * 70));
							showObject(area_game_p2B[*n]);
							area_game_board2[i][j] = 2;
							area_game_P2T = false;
						}
						if (type == 3) {
							locateObject(area_game_p3B[*n], area_game_scene1, 85 + 70 + j * 69.5, 652 - (85 + 70 + i * 70));
							showObject(area_game_p3B[*n]);
							area_game_board2[i][j] = 3;
							area_game_P3T = false;
						}
						(*n)++;
					}
				}
			}
		}
		if (area_game_R1 == 3 && BX >= 1 && BX <= 16 && BY >= 1 && BY <= 6 && area_game_board3[BY - 1][BX - 1] >= 4) {
			area_game_N = area_game_board3[BY - 1][BX - 1];
			*n = 0;
			for (int i = 0; i <= 5; i++) {
				for (int j = 0; j <= 13; j++) {
					if (area_game_board3[i][j] == area_game_N) {
						if (type == 1) {
							locateObject(area_game_p1B[*n], area_game_scene1, 85 + 70 + j * 69.5, 650 - (85 + 70 + i * 68));
							showObject(area_game_p1B[*n]);
							area_game_board3[i][j] = 1;
							area_game_P1T = false;
						}
						if (type == 2) {
							locateObject(area_game_p2B[*n], area_game_scene1, 85 + 70 + j * 69.5, 650 - (85 + 70 + i * 68));
							showObject(area_game_p2B[*n]);
							area_game_board3[i][j] = 2;
							area_game_P2T = false;
						}
						if (type == 3) {
							locateObject(area_game_p3B[*n], area_game_scene1, 85 + 70 + j * 69.5, 650 - (85 + 70 + i * 68));
							showObject(area_game_p3B[*n]);
							area_game_board3[i][j] = 3;
							area_game_P3T = false;
						}
						(*n)++;
					}
				}
			}
		}
	}
}

void keyboardCallback_area_game(KeyCode code, KeyState state)
{
	if (stage_3_4 == true) {
		if (code == KeyCode::KEY_D) {
			area_game_p1dx += (state == KeyState::KEY_PRESSED ? area_game_speed : -area_game_speed);
		}
		else if (code == KeyCode::KEY_A) {
			area_game_p1dx -= (state == KeyState::KEY_PRESSED ? area_game_speed : -area_game_speed);
		}
		else if (code == KeyCode::KEY_W) {
			area_game_p1dy += (state == KeyState::KEY_PRESSED ? area_game_speed : -area_game_speed);
		}
		else if (code == KeyCode::KEY_S) {
			area_game_p1dy -= (state == KeyState::KEY_PRESSED ? area_game_speed : -area_game_speed);
		}
		else if (code == KeyCode::KEY_E && area_game_P1T) {
			area_game_chooseBlock(area_game_B1X, area_game_B1Y, &area_game_n1, 1);
			startTimer(area_game_timer2);
		}

		if (code == KeyCode::KEY_L) {
			area_game_p2dx += (state == KeyState::KEY_PRESSED ? area_game_speed : -area_game_speed);
		}
		else if (code == KeyCode::KEY_J) {
			area_game_p2dx -= (state == KeyState::KEY_PRESSED ? area_game_speed : -area_game_speed);
		}
		else if (code == KeyCode::KEY_I) {
			area_game_p2dy += (state == KeyState::KEY_PRESSED ? area_game_speed : -area_game_speed);
		}
		else if (code == KeyCode::KEY_K) {
			area_game_p2dy -= (state == KeyState::KEY_PRESSED ? area_game_speed : -area_game_speed);
		}
		else if (code == KeyCode::KEY_O && area_game_P2T) {
			area_game_chooseBlock(area_game_B2X, area_game_B2Y, &area_game_n2, 2);
			startTimer(area_game_timer2);
		}

		if (code == KeyCode::KEY_RIGHT_ARROW) {
			area_game_p3dx += (state == KeyState::KEY_PRESSED ? area_game_speed : -area_game_speed);
		}
		else if (code == KeyCode::KEY_LEFT_ARROW) {
			area_game_p3dx -= (state == KeyState::KEY_PRESSED ? area_game_speed : -area_game_speed);
		}
		else if (code == KeyCode::KEY_UP_ARROW) {
			area_game_p3dy += (state == KeyState::KEY_PRESSED ? area_game_speed : -area_game_speed);
		}
		else if (code == KeyCode::KEY_DOWN_ARROW) {
			area_game_p3dy -= (state == KeyState::KEY_PRESSED ? area_game_speed : -area_game_speed);
		}
		else if (code == KeyCode::KEY_RIGHT_SHIFT && area_game_P3T) {
			area_game_chooseBlock(area_game_B3X, area_game_B3Y, &area_game_n3, 3);
			startTimer(area_game_timer2);
		}
	}
}

void mouseCallback_area_game(ObjectID object, int x, int y, MouseAction action) {
	if (stage_3_4 == true) {
		if (object == area_game_next) {
			hideObject(area_game_next);
			area_game_timer1 = createTimer(0.01f);
			area_game_timer2 = createTimer(0.01f);
			area_game_timer3 = createTimer(5.0f);
			startTimer(area_game_timer1);
			area_game_p1 = createObject("area_battle_Images/P1.png");
			area_game_p2 = createObject("area_battle_Images/P2.png");
			area_game_p3 = createObject("area_battle_Images/P3.png");
			scaleObject(area_game_p2, 0.3f);
			scaleObject(area_game_p1, 0.3f);
			scaleObject(area_game_p3, 0.3f);
			showObject(area_game_p1);
			showObject(area_game_p2);
			showObject(area_game_p3);
			for (int i = 0; i <= 28; i++) {
				area_game_p1B[i] = createObject("area_battle_Images/P1C.png");
				scaleObject(area_game_p1B[i], 0);
				area_game_p2B[i] = createObject("area_battle_Images/P2C.png");
				scaleObject(area_game_p2B[i], 0);
				area_game_p3B[i] = createObject("area_battle_Images/P3C.png");
				scaleObject(area_game_p3B[i], 0);
			}
			setSceneImage(area_game_scene1, "area_battle_Images/R1.png");
		}
	}
}
//여기까지 3-4 스테이지 함수들