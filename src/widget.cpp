#include <uva/widgets/widget.hpp>

#include <uva/xml.hpp>

#if ANDY_USE_SDL3
#   include <SDL3/SDL.h>
#endif

uva::widgets::widget::widget(int x, int y, int w, int h, uva::widgets::widget_style style)
    : x(x), y(y), w(w), h(h), style(style)
{

}

void uva::widgets::widget::parse(void* target, uva::xml::schema& schema, uva::xml& xml) {
    style.background_color = schema.color_attribute(xml, "background-color");

    style.flex = atoi(xml.attribute("flex", "0").data());
    style.padding = atoi(xml.attribute("padding", "0").data());
    style.gap = atoi(xml.attribute("gap", "0").data());
    style.border_radius = atoi(xml.attribute("border-radius", "0").data());

    id = xml.attribute("id", "");
}

void uva::widgets::widget::render(void* target) {
#if ANDY_USE_SDL3
    SDL_Renderer* renderer = (SDL_Renderer*)target;

    SDL_SetRenderDrawColor(renderer, style.background_color.r, style.background_color.g, style.background_color.b, style.background_color.a);
    SDL_FRect rect = { x, y, w, h };
    SDL_RenderFillRect(renderer, &rect);
#endif
    //drawing.fill_rect({x, y, w, h}, style.background_color);
}