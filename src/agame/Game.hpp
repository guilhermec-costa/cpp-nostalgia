#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>

namespace sdlgame {
class Game {
private:
  bool is_running;
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Event* m_event;
  Uint32 mouse_buttons;
  int ymouse, xmouse;
  
public:
  Game();
  virtual ~Game();
  bool start();
  void finish();
  bool create_window();
  bool create_window(const char* title, Uint32 , Uint32 ypos, Uint32 width, Uint32 height);
  bool create_window(const char* title, Uint32 width, Uint32 height);
  bool create_window(const char* title);
  bool create_renderer();
  void render();
  void update();
  void treat_events();
  bool get_state() const { return is_running; };
  const static char* src_path;
};
} // namespace sdlgame
#endif
