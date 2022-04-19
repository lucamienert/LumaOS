#include "../include/gui/renderer.h"

renderer_t *init_renderer()
{
    renderer_t *renderer = malloc(sizeof(struct Renderer));
    return renderer;
}