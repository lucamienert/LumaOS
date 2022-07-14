#include <gui/widgets/button.h>

button_t *ltk_button_new(char *text)
{
    button_t *button = malloc(sizeof(struct Button));

    button->text = text;
    button->is_clicked = false;
    button->widget.bounds.w = strlen(text) * 8 + 4 * DEFAULT_PADDING;
    button->widget.bounds.h = 16 + 2 * DEFAULT_PADDING;
    button->widget.on_draw = (widget_draw_t) button_on_draw;
    button->widget.on_click = (widget_clicked_t) button_on_click;
    button->widget.on_mouse_release = (widget_mouse_released_t) button_on_release;

    return button;
}

void ltk_button_on_draw(button_t *button, fb_t fb)
{
    color_scheme_t *color_scheme = ltk_get_color_scheme(&button->widget);
    rect_t rect = ltk_get_absolute_bounds((widget_t*) button);

    if(button->is_clicked)
        ltk_draw_rect(fb, rect.x, rect.y, rect.width, rect.height, color_scheme->base_color + color_scheme->highlight);
    else
        ltk_draw_rect(fb, rect.x, rect.y, rect.width, rect.height, color_scheme->base_colo);

    ltk_draw_border(fb, rect.x, rect.y, rect.width, rect.height, color_scheme->border_color);

    uint32_t x = rect.x + rect.width / 2 - strlen(button->text) * 8 / 2;
    uint32_t y = rect.y + rect.height / 2 - 16 / 2;

    ltk_draw_string(fb, button->text, x, y, color_scheme->text_color);
}

void ltk_button_on_click(button_t *button, point_t p)
{
    (void) p;

    button->is_clicked = true;

    if(button->on_click)
        button->on_click(button);
}

void ltk_button_on_release(button_t *button, point_t p)
{
    (void) p;

    button->is_clicked = false;

    if(button->on_release)
        button->on_release(button);
}

void ltk_button_set_on_click(button_t *button, void (*callback)(button_t*))
{
    button->on_click = callback;
}

void ltk_button_set_text(button_t *button, const char *text)
{
    if(button->text)
        free(button->text);

    button->text = strdup(text);   
}
