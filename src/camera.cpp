#include "camera.h"
#include "render.h"

void Camera::center_on(vec2<int> center) {
    pos.x = (800 / 2 - center.x);
    pos.y = (600 / 2 - center.y);
}

void Camera::render_to_cam(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color) {
    rect.x += pos.x;
    rect.y += pos.y;
    render_rect(renderer, rect, color);
}

void Camera::render_draw_rect(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color) {
    rect.x += pos.x;
    rect.y += pos.y;
    render_outline(renderer, rect, color);
}


vec2i Camera::project(vec2i screen) {
    return screen - pos;
}
