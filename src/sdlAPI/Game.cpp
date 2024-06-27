#include "Game.hpp"
#include "texture_handler.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <cstring>
#include <iostream>

namespace sdlAPI {

SDL_Texture *player_texture = nullptr;
SDL_Rect rect;
SDL_Rect a_rect;
SDL_Rect character_rect;
SDL_Surface *screen_surface = nullptr;
SDL_Surface *image = nullptr;
SDL_Texture *img_texture = nullptr;
SDL_Rect filled_rectangle;
SDL_Texture *texture_to_fill_rectangle;
Uint32 *filled_rectangle_pixels;

SDL_Rect rectangle2;
const char *Game::src_path = "/home/guichina/dev/CPP/src/agame/";

Game::Game() : is_running(false), window(nullptr), renderer(nullptr), m_event(nullptr) {}

Game::~Game() {
  // TODO
}

bool Game::start() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "Failed to initialise SDL subsystems" << std::endl;
  }
  m_event = new SDL_Event();
  if (!create_window("my game", 800, 600))
    return false;
  if (!create_renderer())
    return false;
  is_running = true;
  player_texture = TextureHandler::create_texture_from_surface(
      "/home/guichina/dev/CPP/src/agame/assets/player.png", renderer);
  SDL_SetTextureBlendMode(player_texture, SDL_BLENDMODE_ADD);
  screen_surface = SDL_GetWindowSurface(window);
  image = SDL_LoadBMP("/home/guichina/dev/CPP/src/agame/assets/player.bmp");
  img_texture = SDL_CreateTextureFromSurface(renderer, image);

  SDL_FreeSurface(image);
  rect.h = 64;
  rect.w = 64;
  a_rect.h = 32;
  a_rect.w = 64;
  character_rect.h = 64;
  character_rect.w = 64;
  character_rect.x = 105;
  character_rect.y = 105;

  
  filled_rectangle.h = 200;
  filled_rectangle.w = 200;
  filled_rectangle.x = 100;
  filled_rectangle.y = 100;

  rectangle2.h = 200;
  rectangle2.w = 200;
  rectangle2.x = 450;
  rectangle2.y = 300;
  texture_to_fill_rectangle = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 200, 200);
  filled_rectangle_pixels = new Uint32[200 * 200];

  return true;
}

bool Game::create_window(const char *title, Uint32 width, Uint32 height) {
  window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       width, height, SDL_WINDOW_SHOWN);

  if (!window) {
    std::cout << "Failed to create a SDL window" << std::endl;
    return false;
  }

  return true;
}

bool Game::create_renderer() {
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cout << "Failed to initialise SDL renderer" << std::endl;
    return false;
  }
  return true;
}

void Game::update() {
}

void Game::render() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  SDL_RenderDrawRect(renderer, &filled_rectangle);
  for(int y=0; y<200; y++) {
    for(int x=0; x<200; x++) {
      filled_rectangle_pixels[(y * 200) + x] = 0xFF0000FF;
    }
  }

  SDL_UpdateTexture(texture_to_fill_rectangle, NULL, filled_rectangle_pixels, sizeof(Uint32) * 200);
  SDL_RenderCopy(renderer, texture_to_fill_rectangle, NULL, &filled_rectangle);
  SDL_RenderCopy(renderer, player_texture, NULL, &character_rect);

  SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
  SDL_RenderDrawLine(renderer, 120, 120, 150, 150);

  SDL_RenderCopy(renderer, player_texture, NULL, &rectangle2);
  SDL_RenderPresent(renderer);
}

void Game::treat_events() {
  mouse_buttons = SDL_GetMouseState(&xmouse, &ymouse);
  keyboard_state = SDL_GetKeyboardState(NULL);
  while (SDL_PollEvent(m_event)) {
    switch (m_event->type) {
    case SDL_QUIT:
      is_running = false;
      break;

    case SDL_MOUSEMOTION:
      break;

    case SDL_KEYDOWN:
      unsigned int key_pressed = m_event->key.keysym.sym;
      /* std::cout << (char)key_pressed << std::endl; */
      /* std::cout << m_event->key.keysym.scancode << std::endl; */
      if(m_event->key.keysym.scancode == 40) {
        /* SDL_memset(screen_surface->pixels, 0, screen_surface->pitch * screen_surface->h); */
      }
      break;
    }

    if(keyboard_state[SDL_SCANCODE_W] && keyboard_state[SDL_SCANCODE_LCTRL]) {
      /* std::cout << "ctrl + w pressed" << std::endl; */
    }

    if(m_event->button.button == SDL_BUTTON_LEFT) {
      /* set_pixel(screen_surface, 0, 255, 0); */
    }

    if(m_event->button.button == SDL_BUTTON_LEFT) {
      rectangle2.x = xmouse;
      rectangle2.y = ymouse;
    }

    if(m_event->type == SDL_MOUSEWHEEL) {
      std::cout << "mouse wheel" << std::endl;
    }

    /* SDL_UpdateWindowSurface(window); */
  }
}

void Game::set_pixel(SDL_Surface *surface, Uint8 red, Uint8 green, Uint8 blue) {
  SDL_LockSurface(surface);
  Uint8 *pixels = (Uint8*)surface->pixels;
  pixels[(ymouse * surface->pitch) + xmouse*surface->format->BytesPerPixel] = blue;
  pixels[(ymouse * surface->pitch) + xmouse*surface->format->BytesPerPixel+1] = green;
  pixels[(ymouse * surface->pitch) + xmouse*surface->format->BytesPerPixel+2] = red;
  pixels[(ymouse * surface->pitch) + xmouse*surface->format->BytesPerPixel+3] = 255;
  SDL_UnlockSurface(surface);
}

void Game::finish() {
  SDL_DestroyTexture(img_texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

} // namespace sdlgame
