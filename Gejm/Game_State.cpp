#include "Game_State.hpp"

Game_State::Game_State(Game & game) :
game(game) {}

Main_Menu::Main_Menu(Game & game) :
Game_State(game) {}

In_Game::In_Game(Game & game) :
Game_State(game) {}

Pause_Menu::Pause_Menu(Game & game) :
Game_State(game) {}
