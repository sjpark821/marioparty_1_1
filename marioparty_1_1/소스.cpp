#define _CRT_SECURE_NO_WARNINGS

#define Swap(x, y) temp = x, x = y, y = temp

#include <stdio.h>
#include <bangtal.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <windows.h>

/* ���� ���� -- ������ �ٶ�� �� or �Ŵ����̶�� �������ָ� ���ڽ��ϴ�..
* Ȥ�� �� �߰��� ���� �����ôٸ� ī�� �濡 ���ϰ� �߰����ݽô�- �ѹ� ���� �Ⱥ��Ű��Ƽ� ����..
1. ���콺 �ݹ� �״�� ������ ����  mousecallback_~~gameó��
	 �޾������� ���ھ��
2. ������ ���� �ٶ�� ���̱�� �ѵ� ������ ���鶧 main �Լ� ���� ������ ��Ƽ��
   ū Ʋ������ �����̴� �Լ��� ����� ���ÿ� �ۼ����ָ� ���ڽ��ϴ�.
   �� main�Լ� �������� �ٸ� ���ӵ鿡 �ʿ��� �Լ��� �ִٸ�
   �ּ��� �ް�
   //~~���ӿ� �ʿ��� �Լ���
   �׸��� �� �Ʒ���
   mouscallback();
   timercallback();
   void ~~();
   //������� �������� ���ӿ� �ʿ��� �Լ� ��� ����
   main�Լ� �Ʒ��� ���۱�� �־��ֽñ� �����մϴ�.
   ���⼭ ���� mousecallback_pm_game()�̷� ������ ������ٸ�
   mousecallback_mario_party�ȿ�
   mousecallback_pm_game();�� �־��ּ��� ���� setmousecallback�ϸ� ���� �ȵ˴ϴ�!!
3. ���� ������ ��ġ�� �� �̹������Ͽ� ������ ���� �����̴ٸ� �̹������Ͽ�
   ������ ���� �� ��ġ�ô°� �����帳�ϴ�. - �ƴ϶�� �ʹ� ����������
   Ȥ�� �̹��� ���Ͽ� ������ �����̴��� ���� ���ŷο�ð����� ���� ���Ӻ� �̹�����
   �����ϱ� ���ؼ� Images/�̷��� �� ���� �� ���� �̹������� ���� ~~game_Images���
   �������ֽ� �� ��ġ�ô°� ��õ�帳�ϴ�. -�̷��� �� ��� ���� �ڵ峻����
   Images/ -> ~~game_Images/��� �����Ͻô°� �翬�ϰ���?
*/

/*�ؾ��� ������ ���� ��� �ʿ�� ������ !!��ȣ�� �� �켱 ������ �ƴ�!!/ ���ϸ� ���� �ʼ�!!
1. ī���� ȿ���� ���� � �ۿ��� �� ������ �־��ִ� �۾� -- 430��° ��
��������� �ؾ��� �����Դϴ�.*/


//������ ��Ƽ ū Ʋ������ ����� ������Ʈ
SceneID mario_game_description, game_board, card_draw_place, dice_roll_place;
ObjectID mario_party_next, run_dice;
ObjectID player1_object, player2_object, player3_object;
//��������Ƽ �÷��̾� �����̴� Ÿ�̸� 12��!
//0->1 ~~~~~~~~~~~~~~~~~~ 11~12
TimerID moving_timer_1, moving_timer_2, moving_timer_3, moving_timer_4;
TimerID moving_timer_5, moving_timer_6, moving_timer_7, moving_timer_8;
TimerID moving_timer_9, moving_timer_10, moving_timer_11, moving_timer_12;
//������ �̴ϰ��ӿ� ������ �� �ʿ��� Ÿ�̸� 9��
TimerID enter_1_1, enter_1_2, enter_1_3, enter_1_4;
TimerID enter_2_1, enter_2_2, enter_2_3, enter_2_4;
TimerID enter_3_1, enter_3_2, enter_3_3, enter_3_4;
//�ӽ÷� ���� scene�� -- �� 9���� // �̴ϰ��� ���������� ����
SceneID temp_stage_1_2, temp_stage_1_4;
SceneID temp_stage_2_2;
SceneID temp_stage_3_1;
//�ӽ� �����!! back
ObjectID back1, back2, back3, back4, back5, back6, back7, back8, back9, back10, back11, back12;
//�ֻ��� ������ ��ҿ����� ��ü��(���Ƿ� �ֻ����� Ī�� ���ڴ� 1-3���� ����)-�׳� ���Ըӽ��� ����
ObjectID dice_slot, dice_num, run_dice_in;
//�ֻ��� ������ ��ҿ����� Ÿ�̸� ����
TimerID rolling_time, rolling_dice_timer, rolling_dice_escape_timer;
//�ֻ��� ������ ��ҿ����� player�� ������ ������ ���� ����
int random_result;
// card_draw_place���� ����� ��ü��
ObjectID choice_card[5], card_back[5];
//1-3,2-3,3-3������ ī�� ���� �� ����� Ÿ�̸�
TimerID drawing_card_escape_timer;
//card_draw_place���� ����� ��������
int card_random_num;
//�÷��̾��� ��ġ�� ���ؼ� ������ �̴ϰ����� ����
//start������ ��ġ�� 0�̰� 1-1������ ��ġ�� 1 / ��, ��ġ�� 12(3-4)������ �Ѱ�
//������ ��ġ�� ����ؼ� Ÿ�̸Ӹ� ���ؼ� �������� ����
int player_future_location = 0;
int player1_future_location = 0;
int player1_location = 0;
int player2_future_location = 0;
int player2_location = 0;
int player3_future_location = 0;
int player3_location = 0;

//��������Ƽ ��ü������ �÷��̾� ���� - ������ ���и� ����
//�Ŀ� �ð��� �ȴٸ� �޼����� ���ؼ� �̴ϰ����� ������ ����� ���ö� �޼����� ���� ǥ��//
int mario_party_player1_score = 0;
int mario_party_player2_score = 0;
int mario_party_player3_score = 0;

//������ ������ ����
bool in_game_board = false;

//�ӽ� ���� ���������� bool�� -- �Ʒ��� dice_on�� card_on�� �����ϹǷ� 1-3,2-3,3-3�� ���� x
bool stage_1_1 = false, stage_1_2 = false, stage_1_4 = false;
bool stage_2_1 = false, stage_2_2 = false, stage_2_4 = false;
bool stage_3_1 = false, stage_3_2 = false, stage_3_4 = false;
//3-1, 3-2, 3-4�� �ѹ��� �
bool stage_3_1_finish = false;
bool stage_3_2_finish = false;
bool stage_3_4_finish = false;
//bool������ player�� ���� �̵��� �������� �˾ƺ�
bool player1 = false;
bool player2 = false;
bool player3 = false;

//bool���� ���� run_dice�� ���� �� dice_roll_place ����
//�� �� dice�� ���ư� �� �ְ� ������ִ� ���� �ϳ� ����
bool dice_on = false;

//bool ���� ���� 1-3,2-3,3-3������ ī�� ���� Ȯ��
//1-3,2-3,3-3 ���Խ� �ʼ��� card_on = true ����ְ� 
// board�� ���Խ� in_game_board = true �� card_on = false ���ٰ� 
bool card_on = false;

//����Ȯ�ο� �ӽ� �÷��̾� ���� ���
void check_player_score() {
	printf("\n%d ", mario_party_player1_score);
	printf("%d ", mario_party_player2_score);
	printf("%d\n", mario_party_player3_score);
	char buff1[300];
	char buff2[100];
	char buff3[100];
	sprintf(buff1, "player1: %d ��\n", mario_party_player1_score);
	sprintf(buff2, "player2: %d ��\n", mario_party_player2_score);
	sprintf(buff3, "player3: %d ��", mario_party_player3_score);
	strcat(buff1, buff2);
	strcat(buff1, buff3);
	showMessage(buff1);
}


//1-1 ���������� �� +,- ���ӿ� ���� ���������� �������� ���
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
// +, - ����
int pm_game_random_pm[3];
// ���� ����
int pm_game_random_num[4];

//���� �� ���� �� ����
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


//2-1 ���������� �� ī����߱� ���ӿ� ���� ���� ����
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
//������� ī�� ���߱� �Լ��� �������� ��~

//2-4 ���������� �� ���������� �Լ���
SceneID slot_game_slot_description, slot_game_board, slot_game_final_cal;
ObjectID slot_game_Next, slot_game_player;
ObjectID slot_game_slot_picture[3], slot_game_slot_lever;

TimerID slotgame_timer, slot_game_slot_timer, slot_game_enter_cal_scene;
TimerID slot_game_player1_timer, slot_game_player2_timer, slot_game_player3_timer;
TimerID slot_game_escape_timer;

//�������� �ƴ��� üũ - 3�� �� ���� ������
int slot_game_jackpot_check[3];
//����� �� score�� ���
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
//������� 2-4�������� ���Ըӽ� �Լ���

//������� 3-2 ���� �׸� ã�� �������� �� �Լ���
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
// 3-2 �������� �������� �� �Լ� ���� ��


//������� 3-4 �������� area battle �������� �� �Լ���
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


//player1, player2, player3�� �����Ƽ� ���ư� �� �ֵ��� ����
//�� �������� �̴ϰ����� ���������� �� �Լ� ���ִ°� �ʼ�!!!!!!!
void change_player() {
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
//�ϴ� �����̴°� �� �Ʒ� �Լ���� ����µ� ���� �Ҷ��� ������ ��������ҵ�

//�ֻ����� ���ؼ� �÷��̾� ��ġ�� ��������ִ� �Լ�
void create_dice_number() {
	int random_create = rand() % 3 + 1;
	char buff[100];
	sprintf(buff, "Images/roll_dice%d.png", random_create);
	setObjectImage(dice_num, buff);
	random_result = 8;
}

void move_player(int dice_result) {
	int random_move = dice_result;
	if (player1 == true) {
		player1_future_location = player1_location;
		player1_location += random_move;
	}
	else if (player2 == true) {
		player2_future_location = player2_location;
		player2_location += random_move;
	}
	else if (player3 == true) {
		player3_future_location = player3_location;
		player3_location += random_move;
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

void random_result_8() {
	startTimer(enter_1_1);
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
	case 8:
		random_result_8();
		break;
	}
}

//���� �ٰ��� �Ǵ� ĳ������ �̵� ��ĭ�� �̵� 
void player_move_in_board() {
	if (in_game_board == true) {
		//random_result�� ���ؼ� player�� �� �� �̵����� �޾��ְ�
		//������ ��ġ�� �̵��ϴ� Ÿ�̸� �����س����� ����
		player_move_random_result();
	}
}
//������� �ϴ� �÷��̾� game_board���� �����̴� �Լ���


//1-3,2-3,3-3���� ���� �� �ִ� ī���� ������ �� 5����
//�� 5������ �������� ���� �� �����ִ� ���� ������ �Լ�
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

// ī�� ���� �Ҷ� ������ ȿ���� 
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

//�ӽ� back�� ���콺�ݹ�

void mouseCallback_temp_back(ObjectID object, int x, int y, MouseAction action) {
	if (stage_1_2 == true) {
		if (object == back2) {
			stage_1_2 = false;
			in_game_board = true;
			enterScene(game_board);
			change_player();
			showObject(run_dice);
		}
	}
	else if (stage_1_4 == true) {
		if (object == back4) {
			stage_1_4 = false;
			in_game_board = true;
			enterScene(game_board);
			change_player();
			showObject(run_dice);
		}
	}
	else if (stage_2_1 == true) {
		if (object == back5) {
			stage_2_1 = false;
			in_game_board = true;
			enterScene(game_board);
			change_player();
			showObject(run_dice);
		}
	}
	else if (stage_2_2 == true) {
		if (object == back6) {
			stage_2_2 = false;
			in_game_board = true;
			enterScene(game_board);
			change_player();
			showObject(run_dice);
		}
	}
	else if (stage_3_1 == true) {
		if (object == back9) {
			stage_3_1 = false;
			in_game_board = true;
			enterScene(game_board);
			change_player();
			showObject(run_dice);
		}
	}
}

//������ ��Ƽ��� ū ����Ʋ�������� mousecallback �ٸ� Ŭ���� �ٸ� mousecallback ���� ����
void mouseCallback_mario_party(ObjectID object, int x, int y, MouseAction action) {
	mousecallback_choose_card(object, x, y, action);
	mouseCallback_temp_back(object, x, y, action);
	mouseCallback_card_match(object, x, y, action);
	mouseCallback_pm_game(object, x, y, action);
	mouseCallback_slot_game(object, x, y, action);
	mouseCallback_area_game(object, x, y, action);
	mouseCallback_find_game(object, x, y, action);
	// ó�� ������� - �������� mouseCallback
	if (object == mario_party_next) {
		enterScene(game_board);
		player1 = true;
		in_game_board = true;
	}
	//���� ���� �������� Ŭ��
	if (in_game_board == true) {
		if (object == run_dice) {
			enterScene(dice_roll_place);
			showObject(run_dice_in);
			showObject(dice_num);
			dice_on = true;
			in_game_board = false;
		}
	}
	//dice_roll_place������ Ŭ��
	else if (dice_on == true) {
		if (object == run_dice_in) {
			startTimer(rolling_time);
			startTimer(rolling_dice_timer);
			hideObject(run_dice_in);
		}
	}
}

//�÷��̾ �����̴� Ÿ�̸�
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
// �÷��̾ �������� ������ �̴ϰ��ӿ� ���� ���ִ� Ÿ�̸�
void timerCallback_mario_party_enter_Scene(TimerID timer) {
	if (in_game_board == true) {
		if (timer == enter_1_1) {
			enterScene(pmdescription);
			setTimer(enter_1_1, 2.f);
			in_game_board = false;
			stage_1_1 = true;
		}
		else if (timer == enter_1_2) {
			enterScene(temp_stage_1_2);
			setTimer(enter_1_2, 2.f);
			in_game_board = false;
			stage_1_2 = true;
		}
		else if (timer == enter_1_3) {
			enterScene(card_draw_place);
			draw_card();
			setTimer(enter_1_3, 2.f);
			in_game_board = false;
			card_on = true;
		}
		else if (timer == enter_1_4) {
			enterScene(temp_stage_1_4);
			setTimer(enter_1_4, 2.f);
			in_game_board = false;
			stage_1_4 = true;
		}
		else if (timer == enter_2_1) {
			enterScene(card_match_card_description);
			setTimer(enter_2_1, 2.f);
			in_game_board = false;
			stage_2_1 = true;
		}
		else if (timer == enter_2_2) {
			enterScene(temp_stage_2_2);
			setTimer(enter_2_2, 2.f);
			in_game_board = false;
			stage_2_2 = true;
		}
		else if (timer == enter_2_3) {
			enterScene(card_draw_place);
			setTimer(enter_2_3, 2.f);
			draw_card();
			in_game_board = false;
			card_on = true;
		}
		else if (timer == enter_2_4) {
			enterScene(slot_game_slot_description);
			setTimer(enter_2_4, 2.f);
			in_game_board = false;
			stage_2_4 = true;
		}
		else if (timer == enter_3_1) {
			enterScene(temp_stage_3_1);
			setTimer(enter_3_1, 2.f);
			in_game_board = false;
			stage_3_1 = true;
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
		}
	}
}

//mousecallback�� ���������� ���� ���Ӹ��� timercallback�� ������ֽô°��� �����մϴ�.
void timerCallback_mario_party(TimerID timer) {
	timerCallback_card_match(timer);
	timerCallback_pm_game(timer);
	timerCallback_slot_game(timer);
	timerCallback_area_game(timer);
	timerCallback_find_game(timer);
	//dice_roll_place������ Ÿ�̸�
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
			hideObject(run_dice); //�� ���������� ������ showObject �ʼ�
			enterScene(game_board);
			move_player(random_result);
			player_move_in_board();
		}
	}
	//ī�� �̴� �������������� Ÿ�̸�
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
	//�÷��̾� �����̴� Ÿ�̸�
	timerCallback_mario_party_player_moving(timer);
	timerCallback_mario_party_enter_Scene(timer);
}

void keyboardCallback_mario_party(KeyCode code, KeyState state) {
	keyboardCallback_area_game(code, state);
	keyboardCallback_find_game(code, state);
}

int main() {

	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setMouseCallback(mouseCallback_mario_party);
	setTimerCallback(timerCallback_mario_party);
	setKeyboardCallback(keyboardCallback_mario_party);
	srand(time(NULL));
	//������ ���� ū Ʋ
	mario_game_description = createScene("���� ����", "Images/mario_description.png");
	game_board = createScene("������", "Images/game_board.png");
	card_draw_place = createScene("ī�� �̱�", "Images/draw_card_board.png");
	dice_roll_place = createScene("�ֻ��� ������", "Images/dice_board.png");
	//���� �������� 
	temp_stage_1_2 = createScene("�ӽ� 1-2", "Images/dice_board.png");
	temp_stage_1_4 = createScene("�ӽ� 1-4", "Images/dice_board.png");
	temp_stage_2_2 = createScene("�ӽ� 2-2", "Images/dice_board.png");
	temp_stage_3_1 = createScene("�ӽ� 3-1", "Images/dice_board.png");

	//���� ���� ��ü
	mario_party_next = createObject("Images/Next.png");
	locateObject(mario_party_next, mario_game_description, 500, 30);
	showObject(mario_party_next);

	//�����ǿ����� ��ü
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

	//dice_roll_place������ Ÿ�̸� / ��ü

	run_dice_in = createObject("Images/Run_dice.png");
	locateObject(run_dice_in, dice_roll_place, 540, 30);
	showObject(run_dice_in);

	dice_num = createObject("Images/roll_dice1.png");
	locateObject(dice_num, dice_roll_place, 540, 260);


	rolling_time = createTimer(5.f);
	rolling_dice_timer = createTimer(0.1f);
	rolling_dice_escape_timer = createTimer(1.f);

	//card_draw_place������ Ÿ�̸�

	drawing_card_escape_timer = createTimer(3.f);

	//�ӽ� ����� back
	back2 = createObject("Images/back.png");
	locateObject(back2, temp_stage_1_2, 200, 100);
	showObject(back2);
	back4 = createObject("Images/back.png");
	locateObject(back4, temp_stage_1_4, 200, 100);
	showObject(back4);
	back6 = createObject("Images/back.png");
	locateObject(back6, temp_stage_2_2, 200, 100);
	showObject(back6);
	back9 = createObject("Images/back.png");
	locateObject(back9, temp_stage_3_1, 200, 100);
	showObject(back9);

	//1-1���������� ����ϴ� �̹�����
	pmdescription = createScene("����", "pm_game_Images/game_background.png");

	pm_1 = createScene("��� ���", "pm_game_Images/white.png");
	pm_2 = createScene("��� ���", "pm_game_Images/white.png");
	pm_3 = createScene("��� ���", "pm_game_Images/white.png");

	pm_game_final_cal = createScene("������ ���� ����", "pm_game_Images/final.png");

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
	// ������� 1-1 �������� �� ������ �̹��� �� Ÿ�̸� 

	//2-1 ���������� ī����߱� �Լ��� ���Ǵ� �̹�����
	card_match_card_description = createScene("ī�� ����", "card_match_Images/����.png");
	card_match_card_game = createScene("ī�� ����", "card_match_Images/background.png");
	card_match_card_final_cal = createScene("ī�� ���� ��", "card_match_Images/white.png");

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
	// ������� ī����߱� ����ϴ� �̹����� Ÿ�̸�

	//2-4 ���Ըӽſ� ����ϴ� �̹����� Ÿ�̸�
	slot_game_slot_description = createScene("����", "slot_game_Images/����.png");

	slot_game_board = createScene("������", "slot_game_Images/background.png");

	slot_game_final_cal = createScene("������ ���� ����", "slot_game_Images/white.png");

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

	//������� 2-4 �̹����� Ÿ�̸�

	//������� 3-2 �̹����� Ÿ�̸�
	find_game_scene1 = createScene("Find Game", "find_game_Images/B.png");
	find_game_next = createObject("find_game_Images/next.png");

	scaleObject(find_game_next, 0.15f);
	locateObject(find_game_next, find_game_scene1, 1100, 20);
	showObject(find_game_next);

	find_game_escape_timer = createTimer(3.f);
	//������� 3-2 �̹����� Ÿ�̸�

	//������� 3-4 �������� �̹����� Ÿ�̸�
	area_game_scene1 = createScene("Area Battle", "area_battle_Images/B.png");
	area_game_next = createObject("area_battle_Images/next.png");
	scaleObject(area_game_next, 0.15f);
	locateObject(area_game_next, area_game_scene1, 1100, 20);
	showObject(area_game_next);
	area_game_escape_timer = createTimer(3.f);
	//������� 3-4 �������� �̹����� Ÿ�̸�


	//���� ����
	startGame(mario_game_description);
}

//1-1 �������� +,- ���ӿ� ���Ǵ� �Լ� ���� ���
//+, - ����
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
	// ���� �̹��� ����
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
	sprintf(buff_1, "player%d�� �����: %d  ��ü���� ���� + %d\n", 1, pm_game_cal[0], score[0]);
	sprintf(buff_2, "player%d�� �����: %d  ��ü���� ���� + %d\n", 2, pm_game_cal[1], score[1]);
	sprintf(buff_3, "player%d�� �����: %d  ��ü���� ���� + %d", 3, pm_game_cal[2], score[2]);
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
		// +, - �� ��� ��ġ�Ǹ� ���� ���� �����ϰ� �Ѿ
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
		// 5�� �̳��� ��� ��ġ ���ϸ� 0���� ����ع����� �������� �Ѿ
		if (timer == pm_timer1) {
			hideTimer();
			enterScene(pm_2);
			showTimer(pm_timer2);
			startTimer(pm_timer2);
			setTimer(pm_timer1, 5.f);
			pm_game_cal[0] = 0;
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
			hideTimer();
			enterScene(pm_3);
			showTimer(pm_timer3);
			startTimer(pm_timer3);
			setTimer(pm_timer2, 5.f);
			pm_game_cal[1] = 0;
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
			hideTimer();
			setTimer(pm_timer3, 5.f);
			enterScene(pm_game_final_cal);
			pm_game_cal[2] = 0;
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

// ī�� ���߱⿡ ���Ǵ� �Լ� ���� ���
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

// ī�� ����
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
	sprintf(buff1, "player1�� ����: %d    ��ü ���� +%d\n", card_in_score[0], score[0]);
	sprintf(buff2, "player2�� ����: %d    ��ü ���� +%d\n", card_in_score[1], score[1]);
	sprintf(buff3, "player3�� ����: %d    ��ü ���� +%d\n", card_in_score[2], score[2]);
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
					//swap_card[0]�� min�̶�� ������ �޾Ƽ� 
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
						//ī�� ���� 10���̸� ���ھ ���ؼ� Ȯ�� �� ���� ���� �÷��ֱ� 
						//showMessage �Ʒ��� ���ִ°� �ʿ�
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
//������� ī�� ���߱� �Լ�

//������� 2-4�������� �Լ� ���۱��
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
	sprintf(buff1, "player1: %d��    ��ü ����:+%d\n", slot_game_score[0], score[0]);
	sprintf(buff2, "player2: %d��    ��ü ����:+%d\n", slot_game_score[1], score[1]);
	sprintf(buff3, "player3: %d��    ��ü ����:+%d\n", slot_game_score[2], score[2]);
	strcat(buff1, buff2);
	strcat(buff1, buff3);
	showMessage(buff1);
}

// �������� ���������� ���� ���ָ� �� -- bool�� �ʱ�ȭ
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
			//�� �� �̻� ���������� ���� ���ɼ��� ���ؼ� 3���� �ʱ�ȭ ���� 
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
			//slotgame_timer�� ���߿� ���� ��ġ���� ���� �Ǻ��� �� ��� 
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
				stage_2_4 = false;
				in_game_board = true;
				slot_game_game_reset();
				showObject(run_dice);
				change_player();
				check_player_score();
			}
		}
	}
}
//������� 2-4�������� �Լ� ���� ���

//������� 3-2 �������� �Լ� ���� ���
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
////�׸� ��ǥ

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
//������� 3-2 �Լ� ���� ���

//������� 3-4 �������� �Լ� ���� ���
void area_game_reset() {
	area_game_R1++;
	if (area_game_R1 == 2) setSceneImage(area_game_scene1, "area_battle_Images/R2.png");
	if (area_game_R1 == 3) setSceneImage(area_game_scene1, "area_battle_Images/R3.png");
	if (area_game_R1 == 4) {
		int M = area_game_score[0];      //////////////////////////////////////////////////// ����
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
				sprintf_s(area_game_endscore, 100, "%d�� �÷��̾� ���", 1);
				showMessage(area_game_endscore);
				mario_party_player1_score += 10;
			}
			else if (area_game_winner[0] == 1) {
				sprintf_s(area_game_endscore, 100, "%d�� �÷��̾� ���", 2);
				showMessage(area_game_endscore);
				mario_party_player2_score += 10;
			}
			else if (area_game_winner[0] == 1) {
				sprintf_s(area_game_endscore, 100, "%d�� �÷��̾� ���", 3);
				showMessage(area_game_endscore);
				mario_party_player3_score += 10;
			}
		}
		else if (area_game_winnerN == 2) {
			if (area_game_winner[0] == 1 && area_game_winner[1] == 1) {
				showMessage(" 1�� 2�� �÷��̾� ���!");
				mario_party_player1_score += 10;
				mario_party_player2_score += 10;
				mario_party_player3_score += 0;
			}
			else if (area_game_winner[1] == 1 && area_game_winner[2] == 1) {
				showMessage(" 2�� 3�� �÷��̾� ���!");
				mario_party_player1_score += 0;
				mario_party_player2_score += 10;
				mario_party_player3_score += 10;
			}
			else if (area_game_winner[0] == 1 && area_game_winner[2] == 1) {
				showMessage(" 1�� 3�� �÷��̾� ���!");
				mario_party_player1_score += 10;
				mario_party_player2_score += 0;
				mario_party_player3_score += 10;
			}
		}
		else if (area_game_winnerN == 3) {
			showMessage("��� ���!");
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
				sprintf_s(area_game_end, 100, "Player1 %d��\nPlayer2 %d��\nPlayer3 %d��", area_game_score[0], area_game_score[1], area_game_score[2]);
				showMessage(area_game_end);
				area_game_reset();
				stopTimer(area_game_timer3);
			}
		}
		if (timer == area_game_escape_timer) {
			area_game_reset();
			enterScene(game_board);
			stage_3_4 = false;
			stage_3_4_finish = true;
			in_game_board = true;
			showObject(run_dice);
			change_player();
			check_player_score();
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
//������� 3-4 �������� �Լ���