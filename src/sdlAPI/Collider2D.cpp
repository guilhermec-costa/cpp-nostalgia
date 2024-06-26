#include "Collider2D.h"
#include "Textured_Rectangle.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

namespace sdlAPI {
Collider2D::Collider2D() {
  m_collider_rectangle.x = 0;
  m_collider_rectangle.y = 0;
  m_collider_rectangle.w = 0;
  m_collider_rectangle.h = 0;

}

bool Collider2D::is_colliding(Collider2D &collider) {
    const SDL_Rect rectB = collider.m_collider_rectangle;
    return SDL_HasIntersection(&m_collider_rectangle, &rectB);
  };

Collider2D::~Collider2D() {
}
void Collider2D::update() {}

int Collider2D::get_x() const {
  return this->m_collider_rectangle.x;
}

int Collider2D::get_y() const {
  return this->m_collider_rectangle.y;
}

void Collider2D::set_absolute_position(int x, int y) {
  m_collider_rectangle.x = x;
  m_collider_rectangle.y = y;
}

void Collider2D::set_dimensions(int w, int h) {
  m_collider_rectangle.h = h;
  m_collider_rectangle.w = w;
}

void Collider2D::render(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawRect(renderer, &m_collider_rectangle);
}
} // namespace sdlAPI
