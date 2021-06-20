#pragma once
enum {
	mainID_play_single = 1000,
	mainID_play_multi
};

enum {
	singleID_game_select = 2000,
	singleID_username,
	singleID_player_number,
	singleID_confirm,
	singleID_back
};

enum {
	multiID_join_game = 3000,
	multiID_create_game,
	multiID_back
};

enum {
	joinID_username = 4000,
	joinID_IP,
	joinID_passwd,
	joinID_confirm,
	joinID_back
};

enum {
	createID_game_select = 5000,
	createID_username,
	createID_player_number,
	createID_passwd,
	createID_confirm,
	createID_back
};

enum {
	gameID_deal = 6000,
	gameID_pass,
	gameID_count_down
};

enum {
	pendingID_timer = 7000
};

enum {
	overID_back = 8000
};