#ifndef RIGID_RECT_H_
#define RIGID_RECT_H_

#include "color.h"
#include "game/camera.h"
#include "game/level/platforms.h"
#include "math/rect.h"

typedef struct rigid_rect_t rigid_rect_t;

rigid_rect_t *create_rigid_rect(rect_t rect, color_t color);
rigid_rect_t *create_rigid_rect_from_stream(FILE *stream);
void destroy_rigid_rect(rigid_rect_t *rigid_rect);

int rigid_rect_render(const rigid_rect_t *rigid_rect,
                      const camera_t *camera);
int rigid_rect_update(rigid_rect_t * rigid_rect,
                      const platforms_t *platforms,
                      float delta_time);

rect_t rigid_rect_hitbox(const rigid_rect_t *rigid_rect);

void rigid_rect_move(rigid_rect_t *rigid_rect,
                     vec_t movement);
void rigid_rect_jump(rigid_rect_t *rigid_rect,
                     float force);

int rigid_rect_touches_ground(const rigid_rect_t *rigid_rect);

#endif  // RIGID_RECT_H_
