#include "camera.h"
#include "render.h"

void Camera::center_on(vec2<int> center) {
    pos.x = (800 / 2 - center.x);
    pos.y = (600 / 2 - center.y);
}

void Camera::render_to_cam(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color) {
    rect.x += pos.x - rect.w / 2;
    rect.y += pos.y - rect.h / 2;
    render_rect(renderer, rect, color);
}
