#include "components/collider2d.h"

Collider2D::Collider2D(Cobra_Rect* rect)
	: m_dst_rect(rect), m_outlined(false), m_outline_color(new RGBA())
{}

Collider2D::~Collider2D()
{
	delete m_dst_rect;
	delete m_outline_color;
}

bool Collider2D::is_colliding(const SDL_Rect* other) const
{
	return SDL_HasIntersection(m_dst_rect->get_generated_SDL_rect(), other);
}

void Collider2D::render(SDL_Renderer* renderer) const
{
	if (m_outlined)
	{
		SDL_SetRenderDrawColor(renderer, m_outline_color->R, m_outline_color->G, m_outline_color->B, m_outline_color->A);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
	SDL_RenderDrawRect(renderer, m_dst_rect->get_generated_SDL_rect());
}

void Collider2D::place_outline(RGBA color)
{
	m_outlined = true;
	*m_outline_color = color;
}
