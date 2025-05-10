#include <uva/widgets/text.hpp>

#include <stdexcept>

uva::widgets::text::text(std::string __content, SDL_Renderer* renderer, size_t font_size)
    : content(std::move(__content))
{
    text_style.font_size = font_size;

    //uva::size size = renderer.text_extent(content, text_style.font_size);

    w = size.w;
    h = size.h;
}

void uva::widgets::text::render(SDL_Renderer* renderer)
{
    widget::render(renderer);

    if(content.size()) {
        //renderer.draw_text(content, { x, y }, text_style.font_size, style.color);
    }
}

void uva::widgets::text::parse(SDL_Renderer* renderer, uva::xml::schema& schema, uva::xml& xml)
{
    widget::parse(renderer, schema, xml);
    
    style.color = schema.color_attribute(xml, "color");
    style.cursor = (uva::widgets::widget_cursor)schema.integer_attribute(xml, "cursor");

    text_style.vertical_alignment   = (uva::widgets::text_vertical_alignment)schema.integer_attribute(xml, "vertical-align");
    text_style.horizontal_alignment = (uva::widgets::text_horizontal_alignment)schema.integer_attribute(xml, "horizontal-align");

    std::string_view font_size = schema.string_attribute(xml, "font-size");

    if(!font_size.ends_with("px")) {
        throw std::runtime_error("font-size must be in pixels");
    }

    font_size.remove_suffix(2);

    for(const char& c : font_size) {
        if(!std::isdigit(c)) {
            throw std::runtime_error("font-size must be a number");
        }
    }

    text_style.font_size = atoi(font_size.data());

    //uva::size size = renderer.text_extent(content, text_style.font_size);

    w = size.w;
    h = size.h;
}